//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <cstdio>
#include <gfx/Cpp20.h>
module two.gfx;

namespace two
{
	template class PooledNode<Gnode>;

	void Gnode::release()
	{
		NodeSound* sound = this->find_state<NodeSound>();
		if(sound && sound->m_sound)
		{
			this->scene().m_orphan_sounds.push_back(sound->m_sound);
			sound->m_sound = nullptr;
			error("sound goes out of graph but wasn't destroyed\n");
		}
	}

	Scene& Gnode::scene() { return static_cast<Scene&>(*m_graph); }
	SoundManager* Gnode::sound_manager() { return this->scene().m_sound_manager; }

	// a node without a transform of its own takes the one of its parent, the first time it's asked: a gfx node never changes parent
	Node3& Gnode::attach()
	{
		Node3*& attach = this->scene().m_attach[m_index];
		if(!attach)
			attach = &this->parent()->attach();
		return *attach;
	}

	void Gnode::set_attach(Node3& node) { this->scene().m_attach[m_index] = &node; }

	void debug_tree(Gnode node, size_t index, size_t depth)
	{
		auto print_depth = [](size_t depth) { for(size_t i = 0; i < depth; ++i) printf("    "); };
		print_depth(depth);
		printf("node %i\n", int(index));
		if(Item* item = node.find_state<Item>())
		{
			print_depth(depth + 1);
			printf("item %s\n", item->m_model->m_name.c_str());
		}
		size_t i = 0;
		for(Gnode child : node.children())
			debug_tree(child, i++, depth + 1);
	}

namespace gfx
{
	void setup_pipeline_minimal(GfxSystem& gfx)
	{
		gfx.init_pipeline(pipeline_minimal);
	}

	Gnode node(Gnode parent, const mat4& transform)
	{
		Gnode self = parent.suba();
		//Gnode self = parent.subi((void*)object.as_uint());
		FoundState<Node3> node = self.find_or_create_state<Node3>();
		if(node.created)
			self.set_attach(node.state);
		node.state.m_transform = transform;
		return self;
	}

	Gnode node(Gnode parent, const vec3& position, const quat& rotation, const vec3& scale)
	{
		return node(parent, bxTRS(scale, rotation, position));
	}

	Gnode node(Gnode parent, const Transform& transform)
	{
		return node(parent, transform.m_position, transform.m_rotation, transform.m_scale);
	}

	Gnode transform(Gnode parent, const vec3& position, const quat& rotation, const vec3& scale)
	{
		return node(parent, parent.attach().m_transform * bxTRS(scale, rotation, position));
	}

	Gnode transform(Gnode parent, const vec3& position, const quat& rotation)
	{
		return node(parent, parent.attach().m_transform * bxTRS(vec3(1.f), rotation, position));
	}

	Item& item(Gnode parent, const Model& model, uint32_t flags, Material* material)
	{
		Gnode self = parent.suba();
		FoundState<Item> item = self.find_or_create_state<Item>(self.attach(), model, flags, material);
		bool update = item.created || (flags & ItemFlag::NoUpdate) == 0;
		item.state.m_model = const_cast<Model*>(&model);
		item.state.m_material = material;
		if(update)
		{
			item.state.update_aabb();
		}
		return item.state;
	}

	Batch& batch(Gnode parent, Item& item, uint16_t stride)
	{
		Gnode self = parent.suba();
		FoundState<Batch> batch = self.find_or_create_state<Batch>(item, stride);
		if(batch.created)
			item.m_batch = &batch.state;
		return batch.state;
	}

	Batch& instances(Gnode parent, Item& item, span<mat4> transforms)
	{
		Gnode self = parent.suba();
		FoundState<Batch> batch = self.find_or_create_state<Batch>(item, uint16_t(sizeof(mat4)));
		if(batch.created)
			item.m_batch = &batch.state;
		batch.state.transforms(transforms);
		batch.state.update_aabb(transforms);
		return batch.state;
	}

	void prefab(Gnode parent, const Prefab& prefab, bool transform, uint32_t flags, Material* material)
	{
		Gnode self = parent.suba();
		
		for(const Prefab::Elem& elem : prefab.m_items)
		{
			const Node3& n = prefab.m_nodes[elem.node];
			mat4 tr = transform ? parent.attach().m_transform * n.m_transform
								: n.m_transform;
			Gnode no = node(self, tr);
			Item& it = item(no, *elem.item.m_model, elem.item.m_flags | flags, material);
			//it = prefab.m_items[i];
			//shape(self, Cube(i.m_aabb.m_center, vec3(0.1f)), Symbol::wire(Colour::Red, true));
			//shape(self, submodel->m_aabb, Symbol::wire(Colour::White));
			UNUSED(it);
		}
	}

	Item& shape_item(Gnode parent, Model& model, const Symbol& symbol, uint32_t flags, Material* material, DrawMode draw_mode)
	{
		Item& self = item(parent, model, flags, material);
		self.m_material = material ? material : &parent.scene().m_gfx.symbol_material(symbol, draw_mode);
		return self;
	}

	Item& shape(Gnode parent, const Shape& shape, const Symbol& symbol, uint32_t flags, Material* material)
	{
		Item* item = nullptr;
		static Symbol white = { Colour::White, Colour::White };
		if(symbol.fill())
			item = &shape_item(parent, parent.scene().m_gfx.shape(shape, white, PLAIN), symbol, flags, material, PLAIN);
		if(symbol.outline())
			item = &shape_item(parent, parent.scene().m_gfx.shape(shape, white, OUTLINE), symbol, flags, material, OUTLINE);
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

	void draw(Gnode parent, const Shape& shape, const Symbol& symbol, uint32_t flags)
	{
		draw(parent.scene(), parent.attach().m_transform, shape, symbol, flags);
	}

	Item& sprite(Gnode parent, const Image256& image, const vec2& size, uint32_t flags, Material* material)
	{
		return shape(parent, Quad(size), { image }, flags, material);
	}

	Item* model(Gnode parent, const string& name, uint32_t flags, Material* material)
	{
		Model* model = parent.scene().m_gfx.models().file(name.c_str());
		if(model)
			return &item(parent, *model, flags, material);
		return nullptr;
	}

	Mime& animated(Gnode parent, Item& item)
	{
		Gnode self = parent.suba();
		FoundState<Mime> animated = self.find_or_create_state<Mime>();
		if(animated.created)
			animated.state.add_item(item);
		return animated.state;
	}

	Flare& flows(Gnode parent, const Flow& emitter, uint32_t flags)
	{
		UNUSED(flags);
		Gnode self = parent.suba();
		Flare& particles = self.state<Flare>(&self.attach(), Sphere(1.f), 1024);
		as<Flow>(particles) = emitter;
		particles.m_node = &self.attach();
		particles.m_sprite = &parent.scene().m_particle_system->m_block.m_sprites->find_sprite(emitter.m_sprite_name.c_str());
		return particles;
	}

	Light& light(Gnode parent, LightType light_type, bool shadows, Colour colour, float range, float attenuation)
	{
		Gnode self = parent.suba();
		Light& light = self.state<Light>(self.attach(), light_type, shadows);
		light.m_type = light_type;
		light.m_colour = colour;
		light.m_range = range;
		light.m_attenuation = attenuation;
		return light;
	}

	Light& direct_light_node(Gnode parent, const quat& rotation)
	{
		Gnode self = node(parent, vec3(0.f), rotation);
		Light& l = light(self, LightType::Direct, true, Colour(0.8f, 0.8f, 0.7f), 1.f);
		l.m_energy = 0.6f;
		return l;
	}

	Light& sun_light(Gnode parent, float azimuth, float elevation)
	{
		return direct_light_node(parent, sun_rotation(azimuth, elevation));
	}

	Light& direct_light_node(Gnode parent, const vec3& direction)
	{
		return direct_light_node(parent, facing(direction));
	}

	Light& direct_light_node(Gnode parent)
	{
		return direct_light_node(parent, quat(vec3(-c_pi4, -c_pi4, 0.f)));
	}

	void radiance(Scene& scene, const string& file, BackgroundMode background)
	{
		scene.m_env.m_radiance.m_texture = scene.m_gfx.textures().file(file.c_str());
		scene.m_env.m_background.m_mode = background;
	}

	void radiance(Gnode parent, const string& file, BackgroundMode background)
	{
		Texture& texture = *parent.scene().m_gfx.textures().file(file.c_str());
		Zone& env = parent.scene().m_env;
		env.m_radiance.m_texture = &texture;
		env.m_radiance.m_energy = 0.3f;
		if(background == BackgroundMode::Panorama)
			env.m_background.m_texture = &texture;
		env.m_background.m_mode = background;
	}

	void custom_sky(Gnode parent, CustomSky renderer)
	{
		parent.scene().m_env.m_background.m_custom_function = renderer;
		parent.scene().m_env.m_background.m_mode = BackgroundMode::Custom;
	}

	void manual_job(Gnode parent, PassType pass, ManualJob job)
	{
		parent.scene().m_pass_jobs->m_jobs[pass].push_back(job);
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
