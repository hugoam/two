//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <stl/memory.h>
#include <stl/span.h>
#include <stl/vector.h>
#include <math/Vec.h>
#include <ecs/Entity.h>
#include <type/Cls.h>
#include <type/Unique.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Frustum.h>
#include <gfx/Shader.h>
#include <gfx/Shot.h>

#include <stdint.h>

#include <bgfx/bgfx.h>

#define ZONES_BUFFER 0
#define MATERIALS_BUFFER 0
#define LIGHTS_BUFFER 0

#define ZONES_LIGHTS_BUFFER 0

namespace two
{
#define TEXTURE_CLAMP  BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP
#define TEXTURE_CLAMP3 BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP | BGFX_SAMPLER_W_CLAMP
#define TEXTURE_POINT  BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT

#ifdef TWO_PLATFORM_EMSCRIPTEN
// webgl doesn't usually support sampling depth textures with filtering on
#define TEXTURE_DEPTH TEXTURE_POINT
#else
#define TEXTURE_DEPTH 0
#endif

	TWO_GFX_EXPORT const bgfx::VertexDecl& vertex_decl(uint32_t vertex_format);

	export_ enum class refl_ TextureSampler : unsigned int
	{
		// Screen
		Source0 = 0,
		Source1 = 1,
		Source2 = 2,
		Source3 = 3,
		SourceDepth = 3,

		// Material
		Color = 0,
		Albedo = 0,
		Diffuse = 0,
		Alpha = 1,
		Metallic = 2,
		Specular = 2,
		Roughness = 3,
		Shininess = 3,
		Emissive = 4,
		Normal = 5,
		AO = 6,
		Displace = 7,
		Depth = 7,

		// User
		// probably the least likely to collide with a user defined material
		User0 = 12,
		User1 = 13,
		User2 = 14,
		User3 = 15,
		User4 = 6,
		User5 = 7,

		// Scene
		Radiance = 10,
		Shadow = 11,
		Lightmap = 12,
		ReflectionProbe = 13,
		GIProbe = 14,

		// Model
		Skeleton = 15,

		// Buffers
		Zones = 0,
		Materials = 8,
		Lights = 9,

		Clusters = 13,	   // collides with Lightmap
		LightRecords = 14, // collides with GIProbe
	};

	export_ enum class refl_ Lighting : unsigned int
	{
		None = 0,
		Clustered = (1 << 0),
		Deferred = (1 << 1),
		VoxelGI = (1 << 2),
	};

	inline Lighting lighting(Lighting clustered = Lighting::None, Lighting deferred = Lighting::None, Lighting gi = Lighting::None)
	{
		return Lighting(uint(clustered) | uint(deferred) | uint(gi));
	}

	inline bool check_lighting(Lighting lighting, Lighting option)
	{
		return (uint(lighting) & uint(option)) != 0;
	}

	enum class GpuStorage
	{
		Uniform,
		Buffer,
		Texture,
	};

	template <class T>
	struct GpuState {};

	/*
	initial idea (reality is quite far from that)
	blocks
		- a block is a unit of renderer work
		- it contains all the information needed to be executed : target, bgfx view, viewport, clear, items, material, render state parameters, uniforms, textures, etc...
		- blocks can be nested : ex in main render pass block there are subblocks for each material
		- they can be complementary : inside a pbr render pass block the pbr material block fills in the missing pbr information
		- the sum of uniform blocks must be equivalent to the uniforms expected by the shader(blocks)
	blocks are functional components
	passes are the unit of renderer work
	both are orthogonal
	*/
	export_ struct refl_ TWO_GFX_EXPORT Pass
	{
		attr_ string m_name;
		attr_ RenderTarget* m_target = nullptr;
		attr_ FrameBuffer* m_fbo = nullptr;
		attr_ Viewport* m_viewport = nullptr;
		attr_ vec4 m_rect = vec4(0.f);
		attr_ uint64_t m_bgfx_state = 0;
		bgfx::Encoder* m_encoder = nullptr;
		attr_ PassType m_pass_type;

		attr_ bool m_use_mrt = false;
		attr_ uint8_t m_index = 0;
	};

	export_ struct refl_ TWO_GFX_EXPORT RenderFrame
	{
		attr_ uint32_t m_frame;
		attr_ float m_time;
		attr_ float m_delta_time;
		attr_ uint8_t m_render_pass;

		attr_ uint32_t m_num_draw_calls = 0;
		attr_ uint32_t m_num_vertices = 0;
		attr_ uint32_t m_num_triangles = 0;
	};

	using RenderFunc = void(*)(GfxSystem&, Render&);

	export_ struct refl_ TWO_GFX_EXPORT Render
	{
		constr_ Render() {}
		constr_ Render(Shading shading, Viewport& viewport, RenderTarget& target, RenderFrame& frame);
		constr_ Render(Shading shading, Viewport& viewport, RenderTarget& target, FrameBuffer& target_fbo, RenderFrame& frame);
		~Render();

		attr_ Shading m_shading;
		attr_ Scene* m_scene;
		attr_ RenderTarget* m_target;
		attr_ FrameBuffer* m_fbo;
		attr_ Viewport* m_viewport;
		attr_ vec4 m_rect;
		attr_ Camera* m_camera;
		attr_ RenderFrame* m_frame;

		RenderFunc m_renderer;

		attr_ Frustum m_frustum;

		attr_ Zone* m_env = nullptr;
		Entt m_filters;

		attr_ Lighting m_lighting = Lighting::None;
		attr_ bool m_vflip = false;
		attr_ bool m_needs_mrt = false;
		attr_ bool m_is_mrt = false;

		//ShadowAtlas* m_shadow_atlas = nullptr;
		//ReflectionAtlas* m_reflection_atlas = nullptr;

		attr_ uint8_t m_pass_index = s_render_pass_id;

		uint8_t m_picking_pass_index = s_picking_pass_id;
		uint8_t m_debug_pass_index = s_debug_pass_id;

		Shot m_shot;

		uint32_t m_num_draw_calls = 0;
		uint32_t m_num_vertices = 0;
		uint32_t m_num_triangles = 0;

		meth_ void subrender(const Render& render);

		meth_ Pass next_pass(cstring name, PassType type);
		meth_ Pass composite_pass(cstring name, FrameBuffer& fbo, const vec4& rect);
		Pass composite_pass(cstring name);

		uint8_t picking_pass() { return m_picking_pass_index++; }
		uint8_t debug_pass() { return m_debug_pass_index++; }

		void set_uniforms(const Pass& pass) const;

		static const uint8_t s_picking_pass_id = 1;
		static const uint8_t s_render_pass_id = 100;
		static const uint8_t s_debug_pass_id = 245;
	};

	export_ class refl_ TWO_GFX_EXPORT GfxBlock : public ShaderBlock
	{
	public:
		GfxBlock(GfxSystem& gfx, Type& type);
		virtual ~GfxBlock();

		template <class T>
		GfxBlock(GfxSystem& gfx, T& self) : GfxBlock(gfx, type<T>()) { UNUSED(self); }

		virtual void init_block() = 0;
		virtual void begin_frame(const RenderFrame& frame) { UNUSED(frame); }

		virtual void begin_render(Render& render) { UNUSED(render); }
		virtual void submit_pass(Render& render) { UNUSED(render); }

		GfxSystem& m_gfx;
		attr_ Type& m_type;

		bool m_draw_block = false;
	};

	export_ class refl_ TWO_GFX_EXPORT DrawBlock : public GfxBlock
	{
	public:
		DrawBlock(GfxSystem& gfx, Type& type) : GfxBlock(gfx, type) { m_draw_block = true; }

		virtual void options(Render& render, const DrawElement& element, ProgramVersion& program) const { UNUSED(render); UNUSED(element); UNUSED(program); }
		virtual void submit(Render& render, const Pass& pass) const = 0;
		virtual void submit(Render& render, const DrawElement& element, const Pass& pass) const = 0;
	};

	export_ struct TWO_GFX_EXPORT DrawElement
	{
		DrawElement() {}
		DrawElement(Item& item, const Program& program, const ModelElem& model, const Material& material, const Skin* skin, uint64_t sort_key);

		Item* m_item = nullptr;
		const ModelElem* m_elem = nullptr;
		const Material* m_material = nullptr;
		const Skin* m_skin = nullptr;

		uint64_t m_sort_key = 0;
		ProgramVersion m_program = {};
		uint64_t m_bgfx_state = 0;
		bgfx::ProgramHandle m_bgfx_program = BGFX_INVALID_HANDLE;

		void set_program(const Program& program);
	};

	export_ struct TWO_GFX_EXPORT DrawCluster
	{
		ProgramVersion m_shader_version = {};
		uint64_t m_bgfx_state = 0;
		span<Light*> m_lights = {};
	};

	export_ class refl_ TWO_GFX_EXPORT Renderer
	{
	public:
		Renderer(GfxSystem& gfx);
		~Renderer();

		GfxSystem& m_gfx;

		struct Impl;
		unique<Impl> m_impl;

		void init();

		void submit(Render& render, RenderFunc renderer);
		void render(Render& render, RenderFunc renderer);
		void subrender(Render& render, Render& sub, RenderFunc renderer);

		meth_ void gather(Render& render);
		meth_ void begin(Render& render);
		meth_ void end(Render& render);

		using Enqueue = bool(*)(GfxSystem&, Render&, Pass&, DrawElement&);
		using Submit = void(*)(GfxSystem&, Render&, Pass&, const DrawElement&);

		void begin_render_pass(Render& render, PassType pass_type);
		void submit_render_pass(Render& render, Pass& pass, Submit submit);

		void shader_options(Render& render, Pass& pass, ProgramVersion& version) const;
		void element_options(Render& render, Pass& pass, DrawElement& element);
		void add_element(Render& render, Pass& pass, DrawElement element);
		void clear_draw_elements(Render& render, Pass& pass);
		void gather_draw_elements(Render& render, Pass& pass);
		void submit_draw_elements(bgfx::Encoder& encoder, Render& render, Pass& pass, Submit submit, size_t first, size_t count) const;
		DrawElement draw_element(Item& item, const ModelElem& elem) const;

		void submit(bgfx::Encoder& encoder, Render& render, Pass& pass, Submit submit, const DrawElement& element) const;

		void pass(Render& render, Pass& pass, Enqueue enqueue, Submit submit = nullptr, bool sorted = false);
		void sorted_pass(Render& render, Pass& pass, Enqueue enqueue, Submit submit = nullptr);
		void direct_pass(Render& render, Pass& pass, Enqueue enqueue, Submit submit = nullptr);

		using GatherFunc = void(*)(Scene&, Render&);
		GatherFunc m_gather_func;

		template <class T_Block>
		T_Block* block() { for(auto& block : m_gfx_blocks) if(&(block->m_type) == &type<T_Block>()) return &as<T_Block>(*block); return nullptr; }

		template <class T_Block, class... Args>
		T_Block& add_block(Args&&... args) { m_gfx_blocks.push_back(make_unique<T_Block>(static_cast<Args&&>(args)...)); return as<T_Block>(*m_gfx_blocks.back()); }

		vector<unique<GfxBlock>> m_gfx_blocks;

		table<PassType, vector<GfxBlock*>> m_pass_blocks;
	};
}
