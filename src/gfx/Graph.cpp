//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <stl/algorithm.h>
#include <infra/Copy.h>
#include <pool/Pool.hpp>
#include <tree/Graph.hpp>
#include <pool/ObjectPool.hpp>
#include <math/Math.h>
#include <math/ImageAtlas.h>
#include <math/Vec.hpp>
#include <geom/Geom.h>
#include <geom/Intersect.h>
#include <geom/Symbol.h>
#include <geom/Shapes.h>
#include <gfx/Types.h>
#include <gfx/Graph.h>
#include <gfx/Gfx.h>
#include <gfx/Draw.h>
#include <gfx/Prefab.h>
#include <gfx/Item.h>
#include <gfx/Animated.h>
#include <gfx/Particles.h>
#include <gfx/Scene.h>
#include <gfx/Asset.h>
#include <gfx/Model.h>
#include <gfx/Texture.h> // @kludge : make all this logic private and export_ asset stores
#include <gfx/Blocks/Sky.h>
#include <gfx/GfxSystem.h>
#include <gfx/Pipeline.h>
#endif

#include <cstdio>

namespace mud
{
	template class Graph<Gnode>;

	template class TPool<Node3>;
	template class TPool<Item>;
	template class TPool<Batch>;
	template class TPool<Direct>;
	template class TPool<Mime>;
	template class TPool<Light>;
	template class TPool<Flare>;

	Gnode::Gnode() : Graph() {}
	Gnode::Gnode(Scene& scene, SoundManager* sound_manager) : Graph(), m_scene(&scene), m_attach(&scene.m_root_node), m_sound_manager(sound_manager) {}
	Gnode::Gnode(Gnode* parent, void* identity) : Graph(parent, identity), m_scene(parent->m_scene), m_attach(parent->m_attach), m_sound_manager(parent->m_sound_manager) {}

	Gnode::~Gnode()
	{
		this->clear();
	}

	void Gnode::clear()
	{
		m_nodes.clear();
		if(m_node)
		{
			m_scene->m_pool->pool<Node3>().tdestroy(*m_node);
			m_node = nullptr;
		}
		if(m_item)
		{
			m_scene->m_pool->pool<Item>().tdestroy(*m_item);
			m_item = nullptr;
		}
		if(m_batch)
		{
			m_scene->m_pool->pool<Batch>().tdestroy(*m_batch);
			m_batch = nullptr;
		}
		if(m_direct)
		{
			m_scene->m_pool->pool<Direct>().tdestroy(*m_direct);
			m_direct = nullptr;
		}
		if(m_animated)
		{
			m_scene->m_pool->pool<Mime>().tdestroy(*m_animated);
			m_animated = nullptr;
		}
		if(m_particles)
		{
			m_scene->m_pool->pool<Flare>().tdestroy(*m_particles);
			m_particles = nullptr;
		}
		if(m_light)
		{
			m_scene->m_pool->pool<Light>().tdestroy(*m_light);
			m_light = nullptr;
		}

		if(m_sound)
		{
			m_scene->m_orphan_sounds.push_back(m_sound);
			m_sound = nullptr;
			printf("ERROR: sound goes out of graph but wasn't destroyed\n");
		}
	}

	void debug_tree(Gnode& node, size_t index, size_t depth)
	{
		auto print_depth = [](size_t depth) { for(size_t i = 0; i < depth; ++i) printf("    "); };
		print_depth(depth);
		printf("node %i\n", int(index));
		if(node.m_item)
		{
			print_depth(depth + 1);
			printf("item %s\n", node.m_item->m_model->m_name.c_str());
		}
		for(size_t i = 0; i < node.m_nodes.size(); ++i)
			debug_tree(*node.m_nodes[i], i, depth + 1);
	}

	template <class T, class... Args>
	inline T& create(Scene& scene, Args&&... args)
	{
		return scene.m_pool->pool<T>().construct(static_cast<Args&&>(args)...);
	}

namespace gfx
{
	void setup_pipeline_minimal(GfxSystem& gfx)
	{
		gfx.init_pipeline(pipeline_minimal);
	}

	TPool<Node3>&  nodes(Scene& scene)   { return scene.m_pool->pool<Node3>(); }
	TPool<Item>&   items(Scene& scene)   { return scene.m_pool->pool<Item>(); }
	TPool<Batch>&  batches(Scene& scene) { return scene.m_pool->pool<Batch>(); }
	TPool<Direct>& directs(Scene& scene) { return scene.m_pool->pool<Direct>(); }
	TPool<Mime>&   mimes(Scene& scene)   { return scene.m_pool->pool<Mime>(); }
	TPool<Light>&  lights(Scene& scene)  { return scene.m_pool->pool<Light>(); }
	TPool<Flare>&  flares(Scene& scene)  { return scene.m_pool->pool<Flare>(); }

	Gnode& node(Gnode& parent, Ref object, const mat4& transform)
	{
		Gnode& self = parent.subi(object.m_value);
		if(!self.m_node)
		{
			self.m_node = &create<Node3>(*parent.m_scene);
			self.m_attach = self.m_node;
		}
		self.m_node->m_object = object;
		self.m_node->m_transform = transform;
		return self;
	}

	Gnode& node(Gnode& parent, Ref object, const vec3& position, const quat& rotation, const vec3& scale)
	{
		return node(parent, object, bxTRS(scale, rotation, position));
	}

	Gnode& node(Gnode& parent, Ref object, const Transform& transform)
	{
		return node(parent, object, transform.m_position, transform.m_rotation, transform.m_scale);
	}

	Gnode& transform(Gnode& parent, Ref object, const vec3& position, const quat& rotation, const vec3& scale)
	{
		return node(parent, object, parent.m_attach->m_transform * bxTRS(scale, rotation, position));
	}

	Gnode& transform(Gnode& parent, Ref object, const vec3& position, const quat& rotation)
	{
		return node(parent, object, parent.m_attach->m_transform * bxTRS(vec3(1.f), rotation, position));
	}

	Item& item(Gnode& parent, const Model& model, uint32_t flags, Material* material)
	{
		Gnode& self = parent.suba<Gnode>();
		bool update = (flags & ItemFlag::NoUpdate) == 0;
		if(!self.m_item)
		{
			self.m_item = &create<Item>(*self.m_scene, *self.m_attach, model, flags, material);
			update = true;
		}
		self.m_item->m_model = const_cast<Model*>(&model);
		self.m_item->m_material = material;
		if(update)
		{
			self.m_item->update_aabb();
		}
		return *self.m_item;
	}

	Batch& batch(Gnode& parent, Item& item)
	{
		Gnode& self = parent.suba<Gnode>();
		if(!self.m_batch)
		{
			self.m_batch = &create<Batch>(*self.m_scene, item);
		}
		return *self.m_batch;
	}

	Batch& instances(Gnode& parent, Item& item, span<mat4> transforms)
	{
		Gnode& self = parent.suba<Gnode>();
		if(!self.m_batch)
		{
			self.m_batch = &create<Batch>(*self.m_scene, item);
			item.m_batch = self.m_batch;
		}
		self.m_batch->transforms(transforms);
		self.m_batch->update_aabb(transforms);
		return *self.m_batch;
	}

	void prefab(Gnode& parent, const Prefab& prefab, bool transform, uint32_t flags, Material* material)
	{
		Gnode& self = parent.suba<Gnode>();
		
		for(size_t i = 0; i < prefab.m_items.size(); ++i)
		{
			mat4 tr = transform ? parent.m_attach->m_transform * prefab.m_nodes[i].m_transform
								: prefab.m_nodes[i].m_transform;
			Gnode& no = node(self, {}, tr);
			Item& it = item(no, *prefab.m_items[i].m_model, prefab.m_items[i].m_flags | flags, material);
			//it = prefab.m_items[i];
			//shape(self, Cube(i.m_aabb.m_center, vec3(0.1f)), Symbol::wire(Colour::Red, true));
			//shape(self, submodel->m_aabb, Symbol::wire(Colour::White));
			UNUSED(it);
		}
	}

	Item& shape_item(Gnode& parent, Model& model, const Symbol& symbol, uint32_t flags, Material* material, DrawMode draw_mode)
	{
		Item& self = item(parent, model, flags, material);
		self.m_material = material ? material : &parent.m_scene->m_gfx.symbol_material(symbol, draw_mode);
		return self;
	}

	Item& shape(Gnode& parent, const Shape& shape, const Symbol& symbol, uint32_t flags, Material* material)
	{
		Item* item = nullptr;
		static Symbol white = { Colour::White, Colour::White };
		if(symbol.fill())
			item = &shape_item(parent, parent.m_scene->m_gfx.shape(shape, white, PLAIN), symbol, flags, material, PLAIN);
		if(symbol.outline())
			item = &shape_item(parent, parent.m_scene->m_gfx.shape(shape, white, OUTLINE), symbol, flags, material, OUTLINE);
		return *item;
	}

	void draw(Scene& scene, const mat4& transform, const Shape& shape, const Symbol& symbol, uint32_t flags)
	{
		UNUSED(flags);
		if(symbol.fill())
			scene.m_immediate->shape(transform, { symbol, &shape, PLAIN });
		if(symbol.outline())
			scene.m_immediate->shape(transform, { symbol, &shape, OUTLINE });
	}

	void draw(Gnode& parent, const Shape& shape, const Symbol& symbol, uint32_t flags)
	{
		draw(*parent.m_scene, parent.m_attach->m_transform, shape, symbol, flags);
	}

	Item& sprite(Gnode& parent, const Image256& image, const vec2& size, uint32_t flags, Material* material)
	{
		return shape(parent, Quad(size), { image }, flags, material);
	}

	Item* model(Gnode& parent, const string& name, uint32_t flags, Material* material)
	{
		Model* model = parent.m_scene->m_gfx.models().file(name.c_str());
		if(model)
			return &item(parent, *model, flags, material);
		return nullptr;
	}

	Mime& animated(Gnode& parent, Item& item)
	{
		Gnode& self = parent.suba();
		if(!self.m_animated)
		{
			self.m_animated = &create<Mime>(*self.m_scene, *self.m_attach);
			self.m_animated->add_item(item);
		}
		return *self.m_animated;
	}

	Flare& flows(Gnode& parent, const Flow& emitter, uint32_t flags)
	{
		UNUSED(flags);
		Gnode& self = parent.suba();
		if(!self.m_particles)
			self.m_particles = &create<Flare>(*self.m_scene, self.m_attach, Sphere(1.f), 1024);
		as<Flow>(*self.m_particles) = emitter;
		self.m_particles->m_node = self.m_attach;
		self.m_particles->m_sprite = &parent.m_scene->m_particle_system->m_block.m_sprites->find_sprite(emitter.m_sprite_name.c_str());
		return *self.m_particles;
	}

	Light& light(Gnode& parent, LightType light_type, bool shadows, Colour colour, float range, float attenuation)
	{
		Gnode& self = parent.suba();
		if(!self.m_light)
		{
			self.m_light = &create<Light>(*self.m_scene, *self.m_attach, light_type, shadows);
		}
		self.m_light->m_type = light_type;
		self.m_light->m_colour = colour;
		self.m_light->m_range = range;
		self.m_light->m_attenuation = attenuation;
		return *self.m_light;
	}

	Light& direct_light_node(Gnode& parent, const quat& rotation)
	{
		Gnode& self = node(parent, {}, vec3(0.f), rotation);
		Light& l = light(self, LightType::Direct, true, Colour{ 0.8f, 0.8f, 0.7f }, 1.f);
		l.m_energy = 0.6f;
		l.m_shadow_flags = CSM_Stabilize;
		l.m_shadow_bias = 0.1f;
#ifdef MUD_PLATFORM_EMSCRIPTEN
		l.m_shadow_num_splits = 2;
#else
		l.m_shadow_num_splits = 4;
#endif
		return l;
	}

	Light& sun_light(Gnode& parent, float azimuth, float elevation)
	{
		return direct_light_node(parent, sun_rotation(azimuth, elevation));
	}

	Light& direct_light_node(Gnode& parent, const vec3& direction)
	{
		return direct_light_node(parent, facing(direction));
	}

	Light& direct_light_node(Gnode& parent)
	{
		return direct_light_node(parent, quat(vec3(-c_pi / 4.f, -c_pi / 4.f, 0.f)));
	}

	void radiance(Gnode& parent, const string& texture, BackgroundMode background)
	{
		parent.m_scene->m_env.m_radiance.m_texture = parent.m_scene->m_gfx.textures().file(texture.c_str());
		parent.m_scene->m_env.m_background.m_mode = background;
	}

	void custom_sky(Gnode& parent, CustomSky renderer)
	{
		parent.m_scene->m_env.m_background.m_custom_function = renderer;
		parent.m_scene->m_env.m_background.m_mode = BackgroundMode::Custom;
	}

	void manual_job(Gnode& parent, PassType pass, ManualJob job)
	{
		parent.m_scene->m_pass_jobs->m_jobs[pass].push_back(job);
	}

	Material& solid_material(GfxSystem& gfx, const string& name, const Colour& colour)
	{
		Program& program = *gfx.programs().file("solid");
		Material& material = gfx.materials().fetch(name);
		material.m_program = &program;
		material.m_solid.m_colour = colour;
		return material;
	}

	Material& pbr_material(GfxSystem& gfx, const string& name, const MaterialPbr& pbr_block)
	{
		Program& program = *gfx.programs().file("pbr/pbr");
		Material& material = gfx.materials().fetch(name);
		material.m_program = &program;
		material.m_pbr = pbr_block;
		return material;
	}

	Material& pbr_material(GfxSystem& gfx, const string& name, const Colour& albedo, float metallic, float roughness)
	{
		return pbr_material(gfx, name, { albedo, metallic, roughness });
	}
}
}
