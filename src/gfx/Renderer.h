//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <math/Math.h>
#include <type/Cls.h>
#include <infra/Array.h>
#include <infra/NonCopy.h>
#include <type/Unique.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Shader.h>

#include <cstdint>

#include <bgfx/bgfx.h>

namespace mud
{
#define GFX_TEXTURE_CLAMP BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP
#define GFX_TEXTURE_CLAMP_UVW BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP | BGFX_SAMPLER_W_CLAMP
#define GFX_TEXTURE_POINT BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT

	MUD_GFX_EXPORT const bgfx::VertexDecl& vertex_decl(uint32_t vertex_format);

	export_ enum class refl_ TextureSampler : unsigned int
	{
		Source0 = 0,
		Source1 = 1,
		Source2 = 2,
		Source3 = 3,
		SourceDepth = 3,

		Color = 0,
		Albedo = 0,
		Metallic = 1,
		Roughness = 2,
		Emissive = 3,
		Normal = 4,
		AO = 11,
		Depth = 12,

		Skeleton = 5,
		ShadowCSM = 6,
		ShadowAtlas = 7,
		Radiance = 8,
		ReflectionProbe = 9,
		GIProbe = 10,
		Lights = 13,
		Clusters = 14,
		LightRecords = 15,
		Lightmap = 7,  // can't be 16 because max samplers... FIX THIS
	};

	export_ enum class PassType : unsigned int
	{
		VoxelGI,
		Lightmap,
		Shadowmap,
		Probes,
		Clear,
		Depth,
		Geometry,
		Lights,
		Opaque,
		Background,
		Particles,
		Alpha,
		Unshaded,
		Effects,
		PostProcess,
		Flip,

		Count
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

	export_ struct MUD_GFX_EXPORT Pass
	{
		RenderTarget* m_target = nullptr;
		bgfx::FrameBufferHandle m_fbo = BGFX_INVALID_HANDLE;
		Viewport* m_viewport = nullptr;
		uint64_t m_bgfx_state = 0;
		bgfx::Encoder* m_encoder = nullptr;

		bool m_use_mrt = false;
		uint8_t m_index = 0;
		uint8_t m_sub_pass = 0;
	};

	export_ struct refl_ MUD_GFX_EXPORT RenderFrame
	{
		RenderFrame(uint32_t frame, float time, float delta, uint8_t render_pass) : m_frame(frame), m_time(time), m_delta_time(delta), m_render_pass(render_pass) {}
		uint32_t m_frame;
		float m_time;
		float m_delta_time;
		uint8_t m_render_pass;
		uint32_t m_num_draw_calls = 0;
		uint32_t m_num_vertices = 0;
		uint32_t m_num_triangles = 0;
	};

	struct RenderFilters;

	export_ struct MUD_GFX_EXPORT Render : public NonCopy
	{
		Render(Shading shading, Viewport& viewport, RenderTarget& target, RenderFrame& frame);
		Render(Shading shading, Viewport& viewport, bgfx::FrameBufferHandle& target_fbo, RenderFrame& frame);
		~Render();

		Shading m_shading;
		Scene& m_scene;
		RenderTarget* m_target;
		bgfx::FrameBufferHandle m_target_fbo;
		Viewport& m_viewport;
		Camera& m_camera;
		RenderFrame& m_frame;

		unique_ptr<Frustum> m_frustum;

		Environment* m_environment = nullptr;
		RenderFilters* m_filters = nullptr;

		Lighting m_lighting = Lighting::None;
		bool m_needs_mrt = false;
		bool m_is_mrt = false;
		bool m_needs_depth_prepass = false;

		//ShadowAtlas* m_shadow_atlas = nullptr;
		//ReflectionAtlas* m_reflection_atlas = nullptr;

		uint8_t m_picking_pass_index = s_picking_pass_id;
		uint8_t m_preprocess_pass_index = s_preprocess_pass_id;
		uint8_t m_pass_index = s_render_pass_id;
		uint8_t m_debug_pass_index = s_debug_pass_id;
		uint8_t m_sub_pass_index = 0;

		unique_ptr<Shot> m_shot;

		uint32_t m_num_draw_calls = 0;
		uint32_t m_num_vertices = 0;
		uint32_t m_num_triangles = 0;

		Pass next_pass(const char* name, bool subpass = false);
		uint8_t next_pass_id() { return m_pass_index++; }

		uint8_t picking_pass() { return m_picking_pass_index++; }
		uint8_t preprocess_pass() { return m_preprocess_pass_index++; }
		uint8_t composite_pass() { return m_pass_index++; }
		uint8_t debug_pass() { return m_debug_pass_index++; }

		void set_uniforms(bgfx::Encoder& encoder) const;

		static const uint8_t s_picking_pass_id = 1;
		static const uint8_t s_preprocess_pass_id = 20;
		static const uint8_t s_shadow_atlas_pass_id = 50;
		static const uint8_t s_reflection_probe_pass_id = 70;
		static const uint8_t s_render_pass_id = 100;
		static const uint8_t s_debug_pass_id = 240;
		static const uint8_t s_resolve_pass_id = 254;
		static const uint8_t s_final_draw_pass_id = 254;
		static const uint8_t s_ui_pass_id = 255;
	};

	export_ class refl_ MUD_GFX_EXPORT GfxBlock
	{
	public:
		GfxBlock(GfxSystem& gfx_system, Type& type);
		virtual ~GfxBlock();

		template <class T>
		GfxBlock(GfxSystem& gfx_system, T& self) : GfxBlock(gfx_system, type<T>()) { UNUSED(self); }

		virtual void init_block() = 0;
		virtual void begin_frame(const RenderFrame& frame) { UNUSED(frame); }

		virtual void begin_render(Render& render) = 0;
		virtual void begin_pass(Render& render) = 0;
		virtual void submit_pass(Render& render) { UNUSED(render); }

		GfxSystem& m_gfx_system;
		attr_ Type& m_type;
		attr_ uint8_t m_index;

		unique_ptr<ShaderBlock> m_shader_block;

		bool m_draw_block = false;

		static uint8_t s_block_index;
	};

	export_ class refl_ MUD_GFX_EXPORT DrawBlock : public GfxBlock
	{
	public:
		DrawBlock(GfxSystem& gfx_system, Type& type) : GfxBlock(gfx_system, type) { m_draw_block = true; }

		virtual void begin_draw_pass(Render& render) = 0;

		virtual void options(Render& render, ShaderVersion& shader_version) const = 0;
		virtual void submit(Render& render, const Pass& render_pass) const = 0;
		virtual void submit(Render& render, const DrawElement& element, const Pass& render_pass) const { UNUSED(element); this->submit(render, render_pass); }
	};

	export_ class MUD_GFX_EXPORT RenderPass
	{
	public:
		RenderPass(GfxSystem& gfx_system, const char* name, PassType pass_type);
		virtual ~RenderPass() {}

		virtual void submit_render_pass(Render& render) = 0;

		void blocks_begin_render(Render& render) { for(GfxBlock* block : m_gfx_blocks) block->begin_render(render); }
		void blocks_begin_draw_pass(Render& render) { for(DrawBlock* block : m_draw_blocks) block->begin_draw_pass(render); }
		void blocks_begin_pass(Render& render) { for(GfxBlock* block : m_gfx_blocks) block->begin_pass(render); }

		GfxSystem& m_gfx_system;
		const char* m_name;
		PassType m_pass_type;
		array<GfxBlock*> m_gfx_blocks;
		array<DrawBlock*> m_draw_blocks;
	};
	
	export_ struct MUD_GFX_EXPORT DrawElement
	{
		DrawElement() {}
		DrawElement(Item& item, const Program& program, const ModelItem& model, const Material& material, const Skin* skin = nullptr);
		Item* m_item = nullptr;
		const Program* m_program = nullptr;
		const ModelItem* m_model = nullptr;
		const Material* m_material = nullptr;
		const Skin* m_skin = nullptr;

		uint64_t m_sort_key = 0;
		ShaderVersion m_shader_version = {};
		uint64_t m_bgfx_state = 0;
		bgfx::ProgramHandle m_bgfx_program = BGFX_INVALID_HANDLE;
	};

	export_ struct MUD_GFX_EXPORT DrawCluster
	{
		ShaderVersion m_shader_version = {};
		uint64_t m_bgfx_state = 0;
		array<Light*> m_lights = {};
	};

	export_ class MUD_GFX_EXPORT DrawPass : public RenderPass
	{
	public:
		DrawPass(GfxSystem& gfx_system, const char* name, PassType pass_type);
		~DrawPass();

		void init_blocks();
		void add_element(Render& render, DrawElement element);

		virtual void submit_render_pass(Render& render) final;

		void gather_draw_elements(Render& render);
		void submit_draw_elements(bgfx::Encoder& encoder, Render& render, Pass& render_pass, size_t first, size_t count) const;

		virtual uint8_t num_draw_passes(Render& render) { UNUSED(render); return 1; }
		virtual void next_draw_pass(Render& render, Pass& render_pass) = 0;
		virtual void queue_draw_element(Render& render, DrawElement& element) = 0;

		struct Impl;
		unique_ptr<Impl> m_impl;
	};

	export_ class MUD_GFX_EXPORT Renderer : public NonCopy
	{
	public:
		Renderer(GfxSystem& gfx_system, Pipeline& pipeline, Shading shading);
		~Renderer();

		GfxSystem& m_gfx_system;
		Pipeline& m_pipeline;
		Shading m_shading;

		struct Impl;
		unique_ptr<Impl> m_impl;

		void init();

		bool has_block(GfxBlock& gfx_block);
		void add_block(GfxBlock& gfx_block);

		void render(Render& render);
		void subrender(Render& render, Render& sub);

		RenderPass& add_pass(unique_ptr<RenderPass> pass);

		template <class T_Pass, class... T_Args>
		T_Pass& add_pass(T_Args&&... args) { return as<T_Pass>(add_pass(make_unique<T_Pass>(std::forward<T_Args>(args)...))); }
	};
}
