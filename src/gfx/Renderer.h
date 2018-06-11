//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <obj/Cls.h>
#include <infra/Array.h>
#include <infra/NonCopy.h>
#include <obj/Unique.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Shader.h>

#include <cstdint>

#include <bgfx/bgfx.h>

namespace mud
{
#define GFX_TEXTURE_CLAMP BGFX_TEXTURE_U_CLAMP | BGFX_TEXTURE_V_CLAMP
#define GFX_TEXTURE_CLAMP_UVW BGFX_TEXTURE_U_CLAMP | BGFX_TEXTURE_V_CLAMP | BGFX_TEXTURE_W_CLAMP
#define GFX_TEXTURE_POINT BGFX_TEXTURE_MIN_POINT | BGFX_TEXTURE_MAG_POINT

	MUD_GFX_EXPORT bgfx::VertexDecl vertex_decl(size_t vertex_format);

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
	};

	export_ enum class PassType : unsigned int
	{
		Shadowmap,
		Probes,
		Clear,
		Depth,
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
		//ShaderVersion m_shader_config = {};
		RenderPass* m_render_block = nullptr;

		bool m_use_mrt = false;
		uint8_t m_index = 0;
		uint8_t m_sub_pass = 0;
	};

	export_ struct refl_ MUD_GFX_EXPORT RenderFrame
	{
		uint32_t m_frame;
		float m_time;
		float m_delta_time;
		uint8_t m_render_pass;
	};

	struct RenderFilters;

	export_ struct MUD_GFX_EXPORT Render : public NonCopy
	{
		Render(Viewport& viewport, RenderTarget& target, RenderFrame& frame);
		Render(Viewport& viewport, bgfx::FrameBufferHandle& target_fbo, RenderFrame& frame);
		~Render();

		Scene& m_scene;
		RenderTarget* m_target;
		bgfx::FrameBufferHandle m_target_fbo;
		Viewport& m_viewport;
		Camera& m_camera;
		RenderFrame& m_frame;

		unique_ptr<Frustum> m_frustum;

		Environment* m_environment = nullptr;
		RenderFilters* m_filters = nullptr;

		bool m_needs_mrt = false;
		bool m_is_mrt = false;
		bool m_needs_depth_prepass = false;

		//ShadowAtlas* m_shadow_atlas = nullptr;
		//ReflectionAtlas* m_reflection_atlas = nullptr;

		uint8_t m_preprocess_view_index = s_preprocess_pass_id;
		uint8_t m_pass_index = s_render_pass_id;
		uint8_t m_sub_pass_index = 0;

		unique_ptr<Shot> m_shot;

		Pass next_pass(const char* name, bool subpass = false);
		uint8_t next_pass_id() { return m_pass_index++; }

		uint8_t preprocess_pass()
		{
			return m_preprocess_view_index++;
		}

		uint8_t composite_pass()
		{
			return m_pass_index++;
		}

		void set_uniforms();

		static const uint8_t s_render_picking_pass_id = 1;
		static const uint8_t s_blit_picking_pass_id = 2;
		static const uint8_t s_preprocess_pass_id = 10;
		static const uint8_t s_shadow_atlas_pass_id = 50;
		static const uint8_t s_reflection_probe_pass_id = 70;
		static const uint8_t s_render_pass_id = 100;
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

		virtual void init_gfx_block() = 0;

		virtual void begin_gfx_block(Render& render) = 0;
		virtual void submit_gfx_block(Render& render) = 0;

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

		virtual void begin_gfx_pass(Render& render) = 0;
		virtual void submit_gfx_element(Render& render, Pass& render_pass, DrawElement& element) = 0;
	};

	export_ class MUD_GFX_EXPORT RenderPass
	{
	public:
		RenderPass(GfxSystem& gfx_system, const char* name, PassType pass_type);
		virtual ~RenderPass() {}

		virtual void begin_render_pass(Render& render) = 0;
		virtual void submit_render_pass(Render& render) = 0;

		void begin_render_blocks(Render& render) { for(GfxBlock* block : m_gfx_blocks) block->begin_gfx_block(render); }
		void submit_render_blocks(Render& render) { for(GfxBlock* block : m_gfx_blocks) block->submit_gfx_block(render); }

		const char* m_name;
		PassType m_pass_type;
		array<GfxBlock*> m_gfx_blocks;
	};
	
	export_ struct MUD_GFX_EXPORT DrawElement
	{
		DrawElement() {}
		DrawElement(Item& item, const ModelItem& model, const Material& material, const Skin* skin = nullptr);
		Item* m_item = nullptr;
		const ModelItem* m_model = nullptr;
		const Material* m_material = nullptr;
		const Skin* m_skin = nullptr;

		uint64_t m_sort_key = 0;
		ShaderVersion m_shader_version = {};
		uint64_t m_bgfx_state = 0;
	};

	export_ class MUD_GFX_EXPORT DrawPass : public RenderPass
	{
	public:
		DrawPass(GfxSystem& gfx_system, const char* name, PassType pass_type);
		~DrawPass();

		void init_blocks();
		void add_element(DrawElement element);

		virtual void begin_render_pass(Render& render) final;
		virtual void submit_render_pass(Render& render) final;

		void gather_draw_elements(Render& render);
		//void submit_draw_elements(Render& render);

		virtual uint8_t num_draw_passes(Render& render) { UNUSED(render); return 1; }
		virtual void next_draw_pass(Render& render, Pass& render_pass) = 0;
		virtual void queue_draw_element(Render& render, DrawElement& element) = 0;
		virtual void submit_draw_element(Pass& render_pass, DrawElement& element) = 0;

		struct Impl;
		unique_ptr<Impl> m_impl;
	};

	export_ class MUD_GFX_EXPORT Renderer : public NonCopy
	{
	public:
		Renderer(GfxSystem& gfx_system, Pipeline& pipeline);
		~Renderer();

		GfxSystem& m_gfx_system;
		Pipeline& m_pipeline;

		struct Impl;
		unique_ptr<Impl> m_impl;

		void init();

		bool has_block(GfxBlock& gfx_block);
		void add_block(GfxBlock& gfx_block);

		void render(Render& render);

		RenderPass& add_pass(unique_ptr<RenderPass> pass);

		template <class T_Pass, class... T_Args>
		T_Pass& add_pass(T_Args&&... args) { return as<T_Pass>(add_pass(make_unique<T_Pass>(std::forward<T_Args>(args)...))); }
	};
}
