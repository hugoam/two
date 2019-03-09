//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/memory.h>
#include <stl/span.h>
#include <stl/vector.h>
#include <math/Vec.h>
#include <ecs/Entity.h>
#include <type/Cls.h>
#include <type/Unique.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Shader.h>

#include <stdint.h>

#include <bgfx/bgfx.h>

#define ZONES_BUFFER 0
#define MATERIALS_BUFFER 0
#define LIGHTS_BUFFER 0

#define ZONES_LIGHTS_BUFFER 0

namespace mud
{
#define GFX_TEXTURE_CLAMP BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP
#define GFX_TEXTURE_CLAMP_UVW BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP | BGFX_SAMPLER_W_CLAMP
#define GFX_TEXTURE_POINT BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT

	MUD_GFX_EXPORT const bgfx::VertexDecl& vertex_decl(uint32_t vertex_format);

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
		Alpha = 1,
		Metallic = 2,
		User0 = 2,
		Roughness = 3,
		User1 = 3,
		Emissive = 4,
		User2 = 4,
		Normal = 5,
		User3 = 5,
		AO = 6,
		User4 = 6,
		Depth = 7,
		User5 = 7,

		// Scene
		Radiance = 10,
		ShadowAtlas = 11,
		ShadowCSM = 12,
		Lightmap = 13,
		ReflectionProbe = 14,
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

	export_ enum class PassType : unsigned int
	{
		VoxelGI,
		Lightmap,
		Shadowmap,
		Probes,
		Clear,
		Depth,
		Shadow,
		Geometry,
		Lights,
		Opaque,
		Background,
		Particles,
		Alpha,
		Solid,
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

	struct GpuTexture
	{
		bgfx::TextureHandle texture;
		uint16_t width = 1024;
		uint8_t stride = 4;
	};

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
	export_ struct MUD_GFX_EXPORT Pass
	{
		RenderTarget* m_target = nullptr;
		bgfx::FrameBufferHandle m_fbo = BGFX_INVALID_HANDLE;
		Viewport* m_viewport = nullptr;
		uvec4 m_rect = {};
		uint64_t m_bgfx_state = 0;
		bgfx::Encoder* m_encoder = nullptr;
		PassType m_pass_type;

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
		uint32_t m_num_draw_calls = 0;
		uint32_t m_num_vertices = 0;
		uint32_t m_num_triangles = 0;
	};

	export_ struct MUD_GFX_EXPORT Render
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

		unique<Frustum> m_frustum;

		Zone* m_env = nullptr;
		Entt m_filters;

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

		unique<Shot> m_shot;

		uint32_t m_num_draw_calls = 0;
		uint32_t m_num_vertices = 0;
		uint32_t m_num_triangles = 0;

		Pass next_pass(cstring name, PassType type, bool subpass = false);
		Pass composite_pass(cstring name, bgfx::FrameBufferHandle fbo, const uvec4& rect);

		uint8_t picking_pass() { return m_picking_pass_index++; }
		uint8_t preprocess_pass() { return m_preprocess_pass_index++; }
		uint8_t composite_pass() { return m_pass_index++; }
		uint8_t debug_pass() { return m_debug_pass_index++; }

		void set_uniforms(const Pass& render_pass) const;

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
		GfxBlock(GfxSystem& gfx, Type& type);
		virtual ~GfxBlock();

		template <class T>
		GfxBlock(GfxSystem& gfx, T& self) : GfxBlock(gfx, type<T>()) { UNUSED(self); }

		virtual void init_block() = 0;
		virtual void begin_frame(const RenderFrame& frame) { UNUSED(frame); }

		virtual void begin_render(Render& render) = 0;
		virtual void submit_pass(Render& render) { UNUSED(render); }

		GfxSystem& m_gfx;
		attr_ Type& m_type;
		attr_ uint8_t m_index;

		unique<ShaderBlock> m_shader_block;

		bool m_draw_block = false;

		static uint8_t s_block_index;
	};

	export_ class refl_ MUD_GFX_EXPORT DrawBlock : public GfxBlock
	{
	public:
		DrawBlock(GfxSystem& gfx, Type& type) : GfxBlock(gfx, type) { m_draw_block = true; }

		virtual void options(Render& render, ShaderVersion& shader_version) const = 0;
		virtual void submit(Render& render, const Pass& render_pass) const = 0;
		virtual void submit(Render& render, const DrawElement& element, const Pass& render_pass) const = 0;
	};

	export_ struct MUD_GFX_EXPORT DrawElement
	{
		DrawElement() {}
		DrawElement(Item& item, const Program& program, const ModelItem& model, const Material& material, const Skin* skin, uint64_t sort_key);
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
		span<Light*> m_lights = {};
	};

	using RenderFunc = void(*)(GfxSystem&, Render&);

	export_ class MUD_GFX_EXPORT Renderer
	{
	public:
		Renderer(GfxSystem& gfx);
		~Renderer();

		GfxSystem& m_gfx;

		struct Impl;
		unique<Impl> m_impl;

		void init();

		void render(Render& render, RenderFunc renderer);
		void subrender(Render& render, Render& sub, RenderFunc renderer);

		void gather(Render& render);
		void begin(Render& render);
		void end(Render& render);

		using Enqueue = void(*)(GfxSystem&, Render&, Pass&, DrawElement);
		using Submit = void(*)(GfxSystem&, Render&, Pass&, const DrawElement&);

		void begin_render_pass(Render& render, PassType pass_type);
		void submit_render_pass(Render& render, Pass& render_pass, Submit submit);

		void shader_options(Render& render, Pass& pass, ShaderVersion& version) const;
		void add_element(Render& render, Pass& pass, DrawElement element);
		void clear_draw_elements(Render& render, Pass& pass);
		void gather_draw_elements(Render& render, Pass& pass);
		void submit_draw_elements(bgfx::Encoder& encoder, Render& render, Pass& pass, Submit submit, size_t first, size_t count) const;
		DrawElement draw_element(Item& item, const ModelItem& model_item) const;

		void submit(bgfx::Encoder& encoder, Render& render, Pass& pass, Submit submit, const DrawElement& element) const;

		void pass(Render& render, Pass& pass, Enqueue enqueue, Submit submit = nullptr);

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
