#include <infra/Api.h>
#include <jobs/Api.h>
#include <type/Api.h>
#include <pool/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <ctx/Api.h>
#include <bgfx/Api.h>
#include <emscripten.h>


extern "C" {
	
	// Not using size_t for array indices as the values used by the javascript code are signed.
	void array_bounds_check(const int array_size, const int array_idx) {
		  if (array_idx < 0 || array_idx >= array_size) {
			    EM_ASM({
				      throw 'Array index ' + $0 + ' out of bounds: [0,' + $1 + ')';
				    }, array_idx, array_size);
			  }
	}
	// Animated
	void EMSCRIPTEN_KEEPALIVE Animated_start_2(mud::Animated* self, const char* animation, bool loop) {
		self->start(animation, loop, blend, speed, transient);
	}
	void EMSCRIPTEN_KEEPALIVE Animated_start_3(mud::Animated* self, const char* animation, bool loop, float blend) {
		self->start(animation, loop, blend, speed, transient);
	}
	void EMSCRIPTEN_KEEPALIVE Animated_start_4(mud::Animated* self, const char* animation, bool loop, float blend, float speed) {
		self->start(animation, loop, blend, speed, transient);
	}
	void EMSCRIPTEN_KEEPALIVE Animated_start_5(mud::Animated* self, const char* animation, bool loop, float blend, float speed, bool transient) {
		self->start(animation, loop, blend, speed, transient);
	}
	void EMSCRIPTEN_KEEPALIVE Animated_play_2(mud::Animated* self, const Animation animation, bool loop) {
		self->play(*animation, loop, blend, speed, transient);
	}
	void EMSCRIPTEN_KEEPALIVE Animated_play_3(mud::Animated* self, const Animation animation, bool loop, float blend) {
		self->play(*animation, loop, blend, speed, transient);
	}
	void EMSCRIPTEN_KEEPALIVE Animated_play_4(mud::Animated* self, const Animation animation, bool loop, float blend, float speed) {
		self->play(*animation, loop, blend, speed, transient);
	}
	void EMSCRIPTEN_KEEPALIVE Animated_play_5(mud::Animated* self, const Animation animation, bool loop, float blend, float speed, bool transient) {
		self->play(*animation, loop, blend, speed, transient);
	}
	void EMSCRIPTEN_KEEPALIVE Animated_seek_1(mud::Animated* self, float time) {
		self->seek(time);
	}
	void EMSCRIPTEN_KEEPALIVE Animated_pause_0(mud::Animated* self) {
		self->pause();
	}
	void EMSCRIPTEN_KEEPALIVE Animated_stop_0(mud::Animated* self) {
		self->stop();
	}
	void EMSCRIPTEN_KEEPALIVE Animated_advance_1(mud::Animated* self, float time) {
		self->advance(time);
	}
	void EMSCRIPTEN_KEEPALIVE Animated_next_animation_0(mud::Animated* self) {
		self->next_animation();
	}
	std::string EMSCRIPTEN_KEEPALIVE Animated_playing_0(mud::Animated* self) {
		return self->playing();
	}
	std::vector<mud::AnimationPlay> EMSCRIPTEN_KEEPALIVE Animated_get_playing(mud::Animated* self) {
		return self->m_playing;
	}
	std::vector<mud::Animation*> EMSCRIPTEN_KEEPALIVE Animated_get_queue(mud::Animated* self) {
		return self->m_queue;
	}
	bool EMSCRIPTEN_KEEPALIVE Animated_get_active(mud::Animated* self) {
		return self->m_active;
	}
	float EMSCRIPTEN_KEEPALIVE Animated_get_speed_scale(mud::Animated* self) {
		return self->m_speed_scale;
	}
	float EMSCRIPTEN_KEEPALIVE Animated_get_default_blend_time(mud::Animated* self) {
		return self->m_default_blend_time;
	}
	void EMSCRIPTEN_KEEPALIVE Animated___destroy__(mud::Animated* self) {
		delete self;
	}
	// AnimatedTrack
	mud::AnimatedTrack* EMSCRIPTEN_KEEPALIVE AnimatedTrack_AnimatedTrack_0() {
		return new mud::AnimatedTrack();
	}
	void EMSCRIPTEN_KEEPALIVE AnimatedTrack___destroy__(mud::AnimatedTrack* self) {
		delete self;
	}
	// Animation
	std::string EMSCRIPTEN_KEEPALIVE Animation_get_name(mud::Animation* self) {
		return self->m_name;
	}
	float EMSCRIPTEN_KEEPALIVE Animation_get_length(mud::Animation* self) {
		return self->m_length;
	}
	float EMSCRIPTEN_KEEPALIVE Animation_get_step(mud::Animation* self) {
		return self->m_step;
	}
	void EMSCRIPTEN_KEEPALIVE Animation___destroy__(mud::Animation* self) {
		delete self;
	}
	// AnimationPlay
	mud::AnimationPlay* EMSCRIPTEN_KEEPALIVE AnimationPlay_AnimationPlay_0() {
		return new mud::AnimationPlay();
	}
	const Animation EMSCRIPTEN_KEEPALIVE AnimationPlay_get_animation(mud::AnimationPlay* self) {
		return self->m_animation;
	}
	bool EMSCRIPTEN_KEEPALIVE AnimationPlay_get_loop(mud::AnimationPlay* self) {
		return self->m_loop;
	}
	float EMSCRIPTEN_KEEPALIVE AnimationPlay_get_speed(mud::AnimationPlay* self) {
		return self->m_speed;
	}
	bool EMSCRIPTEN_KEEPALIVE AnimationPlay_get_transient(mud::AnimationPlay* self) {
		return self->m_transient;
	}
	float EMSCRIPTEN_KEEPALIVE AnimationPlay_get_fadeout(mud::AnimationPlay* self) {
		return self->m_fadeout;
	}
	float EMSCRIPTEN_KEEPALIVE AnimationPlay_get_fadeout_left(mud::AnimationPlay* self) {
		return self->m_fadeout_left;
	}
	float EMSCRIPTEN_KEEPALIVE AnimationPlay_get_cursor(mud::AnimationPlay* self) {
		return self->m_cursor;
	}
	bool EMSCRIPTEN_KEEPALIVE AnimationPlay_get_ended(mud::AnimationPlay* self) {
		return self->m_ended;
	}
	void EMSCRIPTEN_KEEPALIVE AnimationPlay___destroy__(mud::AnimationPlay* self) {
		delete self;
	}
	// AnimationTrack
	Animation EMSCRIPTEN_KEEPALIVE AnimationTrack_get_animation(mud::AnimationTrack* self) {
		return self->m_animation;
	}
	size_t EMSCRIPTEN_KEEPALIVE AnimationTrack_get_node(mud::AnimationTrack* self) {
		return self->m_node;
	}
	std::string EMSCRIPTEN_KEEPALIVE AnimationTrack_get_node_name(mud::AnimationTrack* self) {
		return self->m_node_name;
	}
	AnimationTarget EMSCRIPTEN_KEEPALIVE AnimationTrack_get_target(mud::AnimationTrack* self) {
		return self->m_target;
	}
	Type EMSCRIPTEN_KEEPALIVE AnimationTrack_get_value_type(mud::AnimationTrack* self) {
		return self->m_value_type;
	}
	float EMSCRIPTEN_KEEPALIVE AnimationTrack_get_length(mud::AnimationTrack* self) {
		return self->m_length;
	}
	Interpolation EMSCRIPTEN_KEEPALIVE AnimationTrack_get_interpolation(mud::AnimationTrack* self) {
		return self->m_interpolation;
	}
	void EMSCRIPTEN_KEEPALIVE AnimationTrack___destroy__(mud::AnimationTrack* self) {
		delete self;
	}
	// Background
	mud::Background* EMSCRIPTEN_KEEPALIVE Background_Background_0() {
		return new mud::Background();
	}
	BackgroundMode EMSCRIPTEN_KEEPALIVE Background_get_mode(mud::Background* self) {
		return self->m_mode;
	}
	Colour EMSCRIPTEN_KEEPALIVE Background_get_colour(mud::Background* self) {
		return self->m_colour;
	}
	Program EMSCRIPTEN_KEEPALIVE Background_get_custoprogram(mud::Background* self) {
		return self->m_custom_program;
	}
	void EMSCRIPTEN_KEEPALIVE Background___destroy__(mud::Background* self) {
		delete self;
	}
	// BaseMaterialBlock
	mud::BaseMaterialBlock* EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_BaseMaterialBlock_0() {
		return new mud::BaseMaterialBlock();
	}
	BlendMode EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_get_blend_mode(mud::BaseMaterialBlock* self) {
		return self->m_blend_mode;
	}
	CullMode EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_get_cull_mode(mud::BaseMaterialBlock* self) {
		return self->m_cull_mode;
	}
	DepthDraw EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_get_depth_draw_mode(mud::BaseMaterialBlock* self) {
		return self->m_depth_draw_mode;
	}
	DepthTest EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_get_depth_test(mud::BaseMaterialBlock* self) {
		return self->m_depth_test;
	}
	vec2 EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_get_uv0_scale(mud::BaseMaterialBlock* self) {
		return self->m_uv0_scale;
	}
	vec2 EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_get_uv0_offset(mud::BaseMaterialBlock* self) {
		return self->m_uv0_offset;
	}
	vec2 EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_get_uv1_scale(mud::BaseMaterialBlock* self) {
		return self->m_uv1_scale;
	}
	vec2 EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_get_uv1_offset(mud::BaseMaterialBlock* self) {
		return self->m_uv1_offset;
	}
	bool EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_get_is_alpha(mud::BaseMaterialBlock* self) {
		return self->m_is_alpha;
	}
	bool EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_get_screen_filter(mud::BaseMaterialBlock* self) {
		return self->m_screen_filter;
	}
	void EMSCRIPTEN_KEEPALIVE BaseMaterialBlock___destroy__(mud::BaseMaterialBlock* self) {
		delete self;
	}
	// Bone
	mud::Bone* EMSCRIPTEN_KEEPALIVE Bone_Bone_0() {
		return new mud::Bone();
	}
	vec3 EMSCRIPTEN_KEEPALIVE Bone_get_position(mud::Bone* self) {
		return self->m_position;
	}
	quat EMSCRIPTEN_KEEPALIVE Bone_get_rotation(mud::Bone* self) {
		return self->m_rotation;
	}
	vec3 EMSCRIPTEN_KEEPALIVE Bone_get_scale(mud::Bone* self) {
		return self->m_scale;
	}
	void EMSCRIPTEN_KEEPALIVE Bone___destroy__(mud::Bone* self) {
		delete self;
	}
	// Camera
	vec3 EMSCRIPTEN_KEEPALIVE Camera_get_eye(mud::Camera* self) {
		return self->m_eye;
	}
	vec3 EMSCRIPTEN_KEEPALIVE Camera_get_target(mud::Camera* self) {
		return self->m_target;
	}
	mat4 EMSCRIPTEN_KEEPALIVE Camera_get_transform(mud::Camera* self) {
		return self->m_transform;
	}
	mat4 EMSCRIPTEN_KEEPALIVE Camera_get_projection(mud::Camera* self) {
		return self->m_projection;
	}
	float EMSCRIPTEN_KEEPALIVE Camera_get_fov(mud::Camera* self) {
		return self->m_fov;
	}
	float EMSCRIPTEN_KEEPALIVE Camera_get_aspect(mud::Camera* self) {
		return self->m_aspect;
	}
	float EMSCRIPTEN_KEEPALIVE Camera_get_near(mud::Camera* self) {
		return self->m_near;
	}
	float EMSCRIPTEN_KEEPALIVE Camera_get_far(mud::Camera* self) {
		return self->m_far;
	}
	bool EMSCRIPTEN_KEEPALIVE Camera_get_orthographic(mud::Camera* self) {
		return self->m_orthographic;
	}
	float EMSCRIPTEN_KEEPALIVE Camera_get_height(mud::Camera* self) {
		return self->m_height;
	}
	bool EMSCRIPTEN_KEEPALIVE Camera_get_optimize_ends(mud::Camera* self) {
		return self->m_optimize_ends;
	}
	bool EMSCRIPTEN_KEEPALIVE Camera_get_clustered(mud::Camera* self) {
		return self->m_clustered;
	}
	vec4 EMSCRIPTEN_KEEPALIVE Camera_get_lod_offsets(mud::Camera* self) {
		return self->m_lod_offsets;
	}
	void EMSCRIPTEN_KEEPALIVE Camera___destroy__(mud::Camera* self) {
		delete self;
	}
	// DepthParams
	mud::DepthParams* EMSCRIPTEN_KEEPALIVE DepthParams_DepthParams_0() {
		return new mud::DepthParams();
	}
	void EMSCRIPTEN_KEEPALIVE DepthParams___destroy__(mud::DepthParams* self) {
		delete self;
	}
	// Environment
	mud::Environment* EMSCRIPTEN_KEEPALIVE Environment_Environment_0() {
		return new mud::Environment();
	}
	Background EMSCRIPTEN_KEEPALIVE Environment_get_background(mud::Environment* self) {
		return self->m_background;
	}
	Radiance EMSCRIPTEN_KEEPALIVE Environment_get_radiance(mud::Environment* self) {
		return self->m_radiance;
	}
	Sun EMSCRIPTEN_KEEPALIVE Environment_get_sun(mud::Environment* self) {
		return self->m_sun;
	}
	Fog EMSCRIPTEN_KEEPALIVE Environment_get_fog(mud::Environment* self) {
		return self->m_fog;
	}
	void EMSCRIPTEN_KEEPALIVE Environment___destroy__(mud::Environment* self) {
		delete self;
	}
	// Filter
	void EMSCRIPTEN_KEEPALIVE Filter___destroy__(mud::Filter* self) {
		delete self;
	}
	// Fog
	mud::Fog* EMSCRIPTEN_KEEPALIVE Fog_Fog_0() {
		return new mud::Fog();
	}
	bool EMSCRIPTEN_KEEPALIVE Fog_get_enabled(mud::Fog* self) {
		return self->m_enabled;
	}
	float EMSCRIPTEN_KEEPALIVE Fog_get_density(mud::Fog* self) {
		return self->m_density;
	}
	Colour EMSCRIPTEN_KEEPALIVE Fog_get_colour(mud::Fog* self) {
		return self->m_colour;
	}
	bool EMSCRIPTEN_KEEPALIVE Fog_get_depth(mud::Fog* self) {
		return self->m_depth;
	}
	float EMSCRIPTEN_KEEPALIVE Fog_get_depth_begin(mud::Fog* self) {
		return self->m_depth_begin;
	}
	float EMSCRIPTEN_KEEPALIVE Fog_get_depth_curve(mud::Fog* self) {
		return self->m_depth_curve;
	}
	bool EMSCRIPTEN_KEEPALIVE Fog_get_height(mud::Fog* self) {
		return self->m_height;
	}
	float EMSCRIPTEN_KEEPALIVE Fog_get_height_min(mud::Fog* self) {
		return self->m_height_min;
	}
	float EMSCRIPTEN_KEEPALIVE Fog_get_height_max(mud::Fog* self) {
		return self->m_height_max;
	}
	float EMSCRIPTEN_KEEPALIVE Fog_get_height_curve(mud::Fog* self) {
		return self->m_height_curve;
	}
	bool EMSCRIPTEN_KEEPALIVE Fog_get_transmit(mud::Fog* self) {
		return self->m_transmit;
	}
	float EMSCRIPTEN_KEEPALIVE Fog_get_transmit_curve(mud::Fog* self) {
		return self->m_transmit_curve;
	}
	void EMSCRIPTEN_KEEPALIVE Fog___destroy__(mud::Fog* self) {
		delete self;
	}
	// FrameBuffer
	void EMSCRIPTEN_KEEPALIVE FrameBuffer___destroy__(mud::FrameBuffer* self) {
		delete self;
	}
	// FresnelMaterialBlock
	mud::FresnelMaterialBlock* EMSCRIPTEN_KEEPALIVE FresnelMaterialBlock_FresnelMaterialBlock_0() {
		return new mud::FresnelMaterialBlock();
	}
	bool EMSCRIPTEN_KEEPALIVE FresnelMaterialBlock_get_enabled(mud::FresnelMaterialBlock* self) {
		return self->m_enabled;
	}
	float EMSCRIPTEN_KEEPALIVE FresnelMaterialBlock_get_fresnel_scale(mud::FresnelMaterialBlock* self) {
		return self->m_fresnel_scale;
	}
	float EMSCRIPTEN_KEEPALIVE FresnelMaterialBlock_get_fresnel_bias(mud::FresnelMaterialBlock* self) {
		return self->m_fresnel_bias;
	}
	float EMSCRIPTEN_KEEPALIVE FresnelMaterialBlock_get_fresnel_power(mud::FresnelMaterialBlock* self) {
		return self->m_fresnel_power;
	}
	void EMSCRIPTEN_KEEPALIVE FresnelMaterialBlock___destroy__(mud::FresnelMaterialBlock* self) {
		delete self;
	}
	// Frustum
	float EMSCRIPTEN_KEEPALIVE Frustum_get_fov(mud::Frustum* self) {
		return self->m_fov;
	}
	float EMSCRIPTEN_KEEPALIVE Frustum_get_aspect(mud::Frustum* self) {
		return self->m_aspect;
	}
	float EMSCRIPTEN_KEEPALIVE Frustum_get_near(mud::Frustum* self) {
		return self->m_near;
	}
	float EMSCRIPTEN_KEEPALIVE Frustum_get_far(mud::Frustum* self) {
		return self->m_far;
	}
	vec3 EMSCRIPTEN_KEEPALIVE Frustum_get_center(mud::Frustum* self) {
		return self->m_center;
	}
	float EMSCRIPTEN_KEEPALIVE Frustum_get_radius(mud::Frustum* self) {
		return self->m_radius;
	}
	void EMSCRIPTEN_KEEPALIVE Frustum___destroy__(mud::Frustum* self) {
		delete self;
	}
	// FrustumSlice
	mud::FrustumSlice* EMSCRIPTEN_KEEPALIVE FrustumSlice_FrustumSlice_0() {
		return new mud::FrustumSlice();
	}
	void EMSCRIPTEN_KEEPALIVE FrustumSlice___destroy__(mud::FrustumSlice* self) {
		delete self;
	}
	// GfxBlock
	Type EMSCRIPTEN_KEEPALIVE GfxBlock_get_type(mud::GfxBlock* self) {
		return self->m_type;
	}
	uint8_t EMSCRIPTEN_KEEPALIVE GfxBlock_get_index(mud::GfxBlock* self) {
		return self->m_index;
	}
	void EMSCRIPTEN_KEEPALIVE GfxBlock___destroy__(mud::GfxBlock* self) {
		delete self;
	}
	// GfxContext
	void EMSCRIPTEN_KEEPALIVE GfxContext___destroy__(mud::GfxContext* self) {
		delete self;
	}
	// GfxSystem
	void EMSCRIPTEN_KEEPALIVE GfxSystem_add_resource_path_1(mud::GfxSystem* self, const char* path) {
		self->add_resource_path(path);
	}
	Material EMSCRIPTEN_KEEPALIVE GfxSystem_debug_material_0(mud::GfxSystem* self) {
		return self->debug_material();
	}
	Material EMSCRIPTEN_KEEPALIVE GfxSystem_fetch_material_2(mud::GfxSystem* self, const char* name, const char* shader) {
		return self->fetch_material(name, shader, builtin);
	}
	Material EMSCRIPTEN_KEEPALIVE GfxSystem_fetch_material_3(mud::GfxSystem* self, const char* name, const char* shader, bool builtin) {
		return self->fetch_material(name, shader, builtin);
	}
	Material EMSCRIPTEN_KEEPALIVE GfxSystem_fetch_image256_material_1(mud::GfxSystem* self, const Image256 image) {
		return self->fetch_image256_material(*image);
	}
	Model EMSCRIPTEN_KEEPALIVE GfxSystem_fetch_symbol_3(mud::GfxSystem* self, const Symbol symbol, const Shape shape, DrawMode draw_mode) {
		return self->fetch_symbol(*symbol, *shape, draw_mode);
	}
	Material EMSCRIPTEN_KEEPALIVE GfxSystem_fetch_symbol_material_2(mud::GfxSystem* self, const Symbol symbol, DrawMode draw_mode) {
		return self->fetch_symbol_material(*symbol, draw_mode);
	}
	void EMSCRIPTEN_KEEPALIVE GfxSystem___destroy__(mud::GfxSystem* self) {
		delete self;
	}
	// Gnode
	void EMSCRIPTEN_KEEPALIVE Gnode___destroy__(mud::Gnode* self) {
		delete self;
	}
	// ImmediateDraw
	void EMSCRIPTEN_KEEPALIVE ImmediateDraw___destroy__(mud::ImmediateDraw* self) {
		delete self;
	}
	// ImportConfig
	mud::ImportConfig* EMSCRIPTEN_KEEPALIVE ImportConfig_ImportConfig_0() {
		return new mud::ImportConfig();
	}
	ModelFormat EMSCRIPTEN_KEEPALIVE ImportConfig_get_format(mud::ImportConfig* self) {
		return self->m_format;
	}
	vec3 EMSCRIPTEN_KEEPALIVE ImportConfig_get_position(mud::ImportConfig* self) {
		return self->m_position;
	}
	quat EMSCRIPTEN_KEEPALIVE ImportConfig_get_rotation(mud::ImportConfig* self) {
		return self->m_rotation;
	}
	vec3 EMSCRIPTEN_KEEPALIVE ImportConfig_get_scale(mud::ImportConfig* self) {
		return self->m_scale;
	}
	mat4 EMSCRIPTEN_KEEPALIVE ImportConfig_get_transform(mud::ImportConfig* self) {
		return self->m_transform;
	}
	std::vector<std::string> EMSCRIPTEN_KEEPALIVE ImportConfig_get_exclude_elements(mud::ImportConfig* self) {
		return self->m_exclude_elements;
	}
	std::vector<std::string> EMSCRIPTEN_KEEPALIVE ImportConfig_get_exclude_materials(mud::ImportConfig* self) {
		return self->m_exclude_materials;
	}
	std::vector<std::string> EMSCRIPTEN_KEEPALIVE ImportConfig_get_include_elements(mud::ImportConfig* self) {
		return self->m_include_elements;
	}
	std::vector<std::string> EMSCRIPTEN_KEEPALIVE ImportConfig_get_include_materials(mud::ImportConfig* self) {
		return self->m_include_materials;
	}
	std::string EMSCRIPTEN_KEEPALIVE ImportConfig_get_suffix(mud::ImportConfig* self) {
		return self->m_suffix;
	}
	bool EMSCRIPTEN_KEEPALIVE ImportConfig_get_force_reimport(mud::ImportConfig* self) {
		return self->m_force_reimport;
	}
	bool EMSCRIPTEN_KEEPALIVE ImportConfig_get_cache_geometry(mud::ImportConfig* self) {
		return self->m_cache_geometry;
	}
	bool EMSCRIPTEN_KEEPALIVE ImportConfig_get_optimize_geometry(mud::ImportConfig* self) {
		return self->m_optimize_geometry;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE ImportConfig_get_flags(mud::ImportConfig* self) {
		return self->m_flags;
	}
	void EMSCRIPTEN_KEEPALIVE ImportConfig___destroy__(mud::ImportConfig* self) {
		delete self;
	}
	// Item
	Node3 EMSCRIPTEN_KEEPALIVE Item_get_node(mud::Item* self) {
		return self->m_node;
	}
	Model EMSCRIPTEN_KEEPALIVE Item_get_model(mud::Item* self) {
		return self->m_model;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE Item_get_flags(mud::Item* self) {
		return self->m_flags;
	}
	Colour EMSCRIPTEN_KEEPALIVE Item_get_colour(mud::Item* self) {
		return self->m_colour;
	}
	Material EMSCRIPTEN_KEEPALIVE Item_get_material(mud::Item* self) {
		return self->m_material;
	}
	bool EMSCRIPTEN_KEEPALIVE Item_get_visible(mud::Item* self) {
		return self->m_visible;
	}
	ItemShadow EMSCRIPTEN_KEEPALIVE Item_get_shadow(mud::Item* self) {
		return self->m_shadow;
	}
	Rig EMSCRIPTEN_KEEPALIVE Item_get_rig(mud::Item* self) {
		return self->m_rig;
	}
	void EMSCRIPTEN_KEEPALIVE Item___destroy__(mud::Item* self) {
		delete self;
	}
	// Joint
	mud::Joint* EMSCRIPTEN_KEEPALIVE Joint_Joint_0() {
		return new mud::Joint();
	}
	void EMSCRIPTEN_KEEPALIVE Joint___destroy__(mud::Joint* self) {
		delete self;
	}
	// Light
	Node3 EMSCRIPTEN_KEEPALIVE Light_get_node(mud::Light* self) {
		return self->m_node;
	}
	LightType EMSCRIPTEN_KEEPALIVE Light_get_type(mud::Light* self) {
		return self->m_type;
	}
	bool EMSCRIPTEN_KEEPALIVE Light_get_visible(mud::Light* self) {
		return self->m_visible;
	}
	Colour EMSCRIPTEN_KEEPALIVE Light_get_colour(mud::Light* self) {
		return self->m_colour;
	}
	float EMSCRIPTEN_KEEPALIVE Light_get_range(mud::Light* self) {
		return self->m_range;
	}
	float EMSCRIPTEN_KEEPALIVE Light_get_energy(mud::Light* self) {
		return self->m_energy;
	}
	float EMSCRIPTEN_KEEPALIVE Light_get_specular(mud::Light* self) {
		return self->m_specular;
	}
	float EMSCRIPTEN_KEEPALIVE Light_get_attenuation(mud::Light* self) {
		return self->m_attenuation;
	}
	bool EMSCRIPTEN_KEEPALIVE Light_get_shadows(mud::Light* self) {
		return self->m_shadows;
	}
	Colour EMSCRIPTEN_KEEPALIVE Light_get_shadow_colour(mud::Light* self) {
		return self->m_shadow_colour;
	}
	float EMSCRIPTEN_KEEPALIVE Light_get_shadow_range(mud::Light* self) {
		return self->m_shadow_range;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE Light_get_layers(mud::Light* self) {
		return self->m_layers;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE Light_get_last_render(mud::Light* self) {
		return self->m_last_render;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE Light_get_last_update(mud::Light* self) {
		return self->m_last_update;
	}
	float EMSCRIPTEN_KEEPALIVE Light_get_spot_angle(mud::Light* self) {
		return self->m_spot_angle;
	}
	float EMSCRIPTEN_KEEPALIVE Light_get_spot_attenuation(mud::Light* self) {
		return self->m_spot_attenuation;
	}
	ShadowFlags EMSCRIPTEN_KEEPALIVE Light_get_shadow_flags(mud::Light* self) {
		return self->m_shadow_flags;
	}
	uint8_t EMSCRIPTEN_KEEPALIVE Light_get_shadow_nusplits(mud::Light* self) {
		return self->m_shadow_num_splits;
	}
	float EMSCRIPTEN_KEEPALIVE Light_get_shadow_split_distribution(mud::Light* self) {
		return self->m_shadow_split_distribution;
	}
	float EMSCRIPTEN_KEEPALIVE Light_get_shadow_normal_bias(mud::Light* self) {
		return self->m_shadow_normal_bias;
	}
	float EMSCRIPTEN_KEEPALIVE Light_get_shadow_bias(mud::Light* self) {
		return self->m_shadow_bias;
	}
	void EMSCRIPTEN_KEEPALIVE Light___destroy__(mud::Light* self) {
		delete self;
	}
	// Material
	uint16_t EMSCRIPTEN_KEEPALIVE Material_get_index(mud::Material* self) {
		return self->m_index;
	}
	bool EMSCRIPTEN_KEEPALIVE Material_get_builtin(mud::Material* self) {
		return self->m_builtin;
	}
	Program EMSCRIPTEN_KEEPALIVE Material_get_program(mud::Material* self) {
		return self->m_program;
	}
	BaseMaterialBlock EMSCRIPTEN_KEEPALIVE Material_get_base_block(mud::Material* self) {
		return self->m_base_block;
	}
	UnshadedMaterialBlock EMSCRIPTEN_KEEPALIVE Material_get_unshaded_block(mud::Material* self) {
		return self->m_unshaded_block;
	}
	PbrMaterialBlock EMSCRIPTEN_KEEPALIVE Material_get_pbr_block(mud::Material* self) {
		return self->m_pbr_block;
	}
	FresnelMaterialBlock EMSCRIPTEN_KEEPALIVE Material_get_fresnel_block(mud::Material* self) {
		return self->m_fresnel_block;
	}
	void EMSCRIPTEN_KEEPALIVE Material___destroy__(mud::Material* self) {
		delete self;
	}
	// Mesh
	std::string EMSCRIPTEN_KEEPALIVE Mesh_get_name(mud::Mesh* self) {
		return self->m_name;
	}
	uint16_t EMSCRIPTEN_KEEPALIVE Mesh_get_index(mud::Mesh* self) {
		return self->m_index;
	}
	DrawMode EMSCRIPTEN_KEEPALIVE Mesh_get_draw_mode(mud::Mesh* self) {
		return self->m_draw_mode;
	}
	Aabb EMSCRIPTEN_KEEPALIVE Mesh_get_aabb(mud::Mesh* self) {
		return self->m_aabb;
	}
	float EMSCRIPTEN_KEEPALIVE Mesh_get_radius(mud::Mesh* self) {
		return self->m_radius;
	}
	vec3 EMSCRIPTEN_KEEPALIVE Mesh_get_origin(mud::Mesh* self) {
		return self->m_origin;
	}
	bool EMSCRIPTEN_KEEPALIVE Mesh_get_readback(mud::Mesh* self) {
		return self->m_readback;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE Mesh_get_vertex_format(mud::Mesh* self) {
		return self->m_vertex_format;
	}
	bool EMSCRIPTEN_KEEPALIVE Mesh_get_qnormals(mud::Mesh* self) {
		return self->m_qnormals;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE Mesh_get_vertex_count(mud::Mesh* self) {
		return self->m_vertex_count;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE Mesh_get_index_count(mud::Mesh* self) {
		return self->m_index_count;
	}
	bool EMSCRIPTEN_KEEPALIVE Mesh_get_index32(mud::Mesh* self) {
		return self->m_index32;
	}
	Material EMSCRIPTEN_KEEPALIVE Mesh_get_material(mud::Mesh* self) {
		return self->m_material;
	}
	void EMSCRIPTEN_KEEPALIVE Mesh___destroy__(mud::Mesh* self) {
		delete self;
	}
	// Model
	std::string EMSCRIPTEN_KEEPALIVE Model_get_name(mud::Model* self) {
		return self->m_name;
	}
	uint16_t EMSCRIPTEN_KEEPALIVE Model_get_index(mud::Model* self) {
		return self->m_index;
	}
	Aabb EMSCRIPTEN_KEEPALIVE Model_get_aabb(mud::Model* self) {
		return self->m_aabb;
	}
	float EMSCRIPTEN_KEEPALIVE Model_get_radius(mud::Model* self) {
		return self->m_radius;
	}
	vec3 EMSCRIPTEN_KEEPALIVE Model_get_origin(mud::Model* self) {
		return self->m_origin;
	}
	void EMSCRIPTEN_KEEPALIVE Model___destroy__(mud::Model* self) {
		delete self;
	}
	// ModelItem
	mud::ModelItem* EMSCRIPTEN_KEEPALIVE ModelItem_ModelItem_0() {
		return new mud::ModelItem();
	}
	size_t EMSCRIPTEN_KEEPALIVE ModelItem_get_index(mud::ModelItem* self) {
		return self->m_index;
	}
	Mesh EMSCRIPTEN_KEEPALIVE ModelItem_get_mesh(mud::ModelItem* self) {
		return self->m_mesh;
	}
	bool EMSCRIPTEN_KEEPALIVE ModelItem_get_has_transform(mud::ModelItem* self) {
		return self->m_has_transform;
	}
	mat4 EMSCRIPTEN_KEEPALIVE ModelItem_get_transform(mud::ModelItem* self) {
		return self->m_transform;
	}
	int EMSCRIPTEN_KEEPALIVE ModelItem_get_skin(mud::ModelItem* self) {
		return self->m_skin;
	}
	Colour EMSCRIPTEN_KEEPALIVE ModelItem_get_colour(mud::ModelItem* self) {
		return self->m_colour;
	}
	Material EMSCRIPTEN_KEEPALIVE ModelItem_get_material(mud::ModelItem* self) {
		return self->m_material;
	}
	void EMSCRIPTEN_KEEPALIVE ModelItem___destroy__(mud::ModelItem* self) {
		delete self;
	}
	// Node3
	Scene EMSCRIPTEN_KEEPALIVE Node3_get_scene(mud::Node3* self) {
		return self->m_scene;
	}
	uint16_t EMSCRIPTEN_KEEPALIVE Node3_get_index(mud::Node3* self) {
		return self->m_index;
	}
	mat4 EMSCRIPTEN_KEEPALIVE Node3_get_transform(mud::Node3* self) {
		return self->m_transform;
	}
	bool EMSCRIPTEN_KEEPALIVE Node3_get_visible(mud::Node3* self) {
		return self->m_visible;
	}
	void EMSCRIPTEN_KEEPALIVE Node3___destroy__(mud::Node3* self) {
		delete self;
	}
	// ParticleGenerator
	mud::ParticleGenerator* EMSCRIPTEN_KEEPALIVE ParticleGenerator_ParticleGenerator_0() {
		return new mud::ParticleGenerator();
	}
	std::string EMSCRIPTEN_KEEPALIVE ParticleGenerator_get_name(mud::ParticleGenerator* self) {
		return self->m_name;
	}
	float EMSCRIPTEN_KEEPALIVE ParticleGenerator_get_duration(mud::ParticleGenerator* self) {
		return self->m_duration;
	}
	float EMSCRIPTEN_KEEPALIVE ParticleGenerator_get_start_time(mud::ParticleGenerator* self) {
		return self->m_start_time;
	}
	bool EMSCRIPTEN_KEEPALIVE ParticleGenerator_get_loop(mud::ParticleGenerator* self) {
		return self->m_loop;
	}
	ShapeVar EMSCRIPTEN_KEEPALIVE ParticleGenerator_get_shape(mud::ParticleGenerator* self) {
		return self->m_shape;
	}
	EmitterFlow EMSCRIPTEN_KEEPALIVE ParticleGenerator_get_flow(mud::ParticleGenerator* self) {
		return self->m_flow;
	}
	bool EMSCRIPTEN_KEEPALIVE ParticleGenerator_get_billboard(mud::ParticleGenerator* self) {
		return self->m_billboard;
	}
	vec3 EMSCRIPTEN_KEEPALIVE ParticleGenerator_get_direction(mud::ParticleGenerator* self) {
		return self->m_direction;
	}
	quat EMSCRIPTEN_KEEPALIVE ParticleGenerator_get_rotation(mud::ParticleGenerator* self) {
		return self->m_rotation;
	}
	BlendMode EMSCRIPTEN_KEEPALIVE ParticleGenerator_get_blend_mode(mud::ParticleGenerator* self) {
		return self->m_blend_mode;
	}
	std::string EMSCRIPTEN_KEEPALIVE ParticleGenerator_get_sprite_name(mud::ParticleGenerator* self) {
		return self->m_sprite_name;
	}
	void EMSCRIPTEN_KEEPALIVE ParticleGenerator___destroy__(mud::ParticleGenerator* self) {
		delete self;
	}
	// PbrMaterialBlock
	mud::PbrMaterialBlock* EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_PbrMaterialBlock_0() {
		return new mud::PbrMaterialBlock();
	}
	mud::PbrMaterialBlock* EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_PbrMaterialBlock_0() {
		return new mud::PbrMaterialBlock();
	}
	mud::PbrMaterialBlock* EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_PbrMaterialBlock_1(const Colour albedo) {
		return new mud::PbrMaterialBlock(*albedo, metallic, roughness);
	}
	mud::PbrMaterialBlock* EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_PbrMaterialBlock_2(const Colour albedo, float metallic) {
		return new mud::PbrMaterialBlock(*albedo, metallic, roughness);
	}
	mud::PbrMaterialBlock* EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_PbrMaterialBlock_3(const Colour albedo, float metallic, float roughness) {
		return new mud::PbrMaterialBlock(*albedo, metallic, roughness);
	}
	bool EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_get_enabled(mud::PbrMaterialBlock* self) {
		return self->m_enabled;
	}
	float EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_get_specular(mud::PbrMaterialBlock* self) {
		return self->m_specular;
	}
	float EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_get_emissive_energy(mud::PbrMaterialBlock* self) {
		return self->m_emissive_energy;
	}
	float EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_get_ritint(mud::PbrMaterialBlock* self) {
		return self->m_rim_tint;
	}
	float EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_get_clearcoat_gloss(mud::PbrMaterialBlock* self) {
		return self->m_clearcoat_gloss;
	}
	bool EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_get_deep_parallax(mud::PbrMaterialBlock* self) {
		return self->m_deep_parallax;
	}
	PbrDiffuseMode EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_get_diffuse_mode(mud::PbrMaterialBlock* self) {
		return self->m_diffuse_mode;
	}
	PbrSpecularMode EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_get_specular_mode(mud::PbrMaterialBlock* self) {
		return self->m_specular_mode;
	}
	void EMSCRIPTEN_KEEPALIVE PbrMaterialBlock___destroy__(mud::PbrMaterialBlock* self) {
		delete self;
	}
	// Prefab
	std::string EMSCRIPTEN_KEEPALIVE Prefab_get_name(mud::Prefab* self) {
		return self->m_name;
	}
	void EMSCRIPTEN_KEEPALIVE Prefab___destroy__(mud::Prefab* self) {
		delete self;
	}
	// Program
	const char* EMSCRIPTEN_KEEPALIVE Program_get_name(mud::Program* self) {
		return self->name;
	}
	void EMSCRIPTEN_KEEPALIVE Program___destroy__(mud::Program* self) {
		delete self;
	}
	// Radiance
	mud::Radiance* EMSCRIPTEN_KEEPALIVE Radiance_Radiance_0() {
		return new mud::Radiance();
	}
	float EMSCRIPTEN_KEEPALIVE Radiance_get_energy(mud::Radiance* self) {
		return self->m_energy;
	}
	float EMSCRIPTEN_KEEPALIVE Radiance_get_ambient(mud::Radiance* self) {
		return self->m_ambient;
	}
	Colour EMSCRIPTEN_KEEPALIVE Radiance_get_colour(mud::Radiance* self) {
		return self->m_colour;
	}
	Texture EMSCRIPTEN_KEEPALIVE Radiance_get_texture(mud::Radiance* self) {
		return self->m_texture;
	}
	void EMSCRIPTEN_KEEPALIVE Radiance___destroy__(mud::Radiance* self) {
		delete self;
	}
	// RenderFrame
	mud::RenderFrame* EMSCRIPTEN_KEEPALIVE RenderFrame_RenderFrame_0() {
		return new mud::RenderFrame();
	}
	void EMSCRIPTEN_KEEPALIVE RenderFrame___destroy__(mud::RenderFrame* self) {
		delete self;
	}
	// RenderQuad
	mud::RenderQuad* EMSCRIPTEN_KEEPALIVE RenderQuad_RenderQuad_0() {
		return new mud::RenderQuad();
	}
	void EMSCRIPTEN_KEEPALIVE RenderQuad___destroy__(mud::RenderQuad* self) {
		delete self;
	}
	// Rig
	void EMSCRIPTEN_KEEPALIVE Rig___destroy__(mud::Rig* self) {
		delete self;
	}
	// Scene
	Gnode EMSCRIPTEN_KEEPALIVE Scene_begin_0(mud::Scene* self) {
		return self->begin();
	}
	Gnode EMSCRIPTEN_KEEPALIVE Scene_get_graph(mud::Scene* self) {
		return self->m_graph;
	}
	Node3 EMSCRIPTEN_KEEPALIVE Scene_get_root_node(mud::Scene* self) {
		return self->m_root_node;
	}
	Environment EMSCRIPTEN_KEEPALIVE Scene_get_environment(mud::Scene* self) {
		return self->m_environment;
	}
	Ref EMSCRIPTEN_KEEPALIVE Scene_get_user(mud::Scene* self) {
		return self->m_user;
	}
	void EMSCRIPTEN_KEEPALIVE Scene___destroy__(mud::Scene* self) {
		delete self;
	}
	// Shot
	void EMSCRIPTEN_KEEPALIVE Shot___destroy__(mud::Shot* self) {
		delete self;
	}
	// Skeleton
	void EMSCRIPTEN_KEEPALIVE Skeleton___destroy__(mud::Skeleton* self) {
		delete self;
	}
	// Skin
	void EMSCRIPTEN_KEEPALIVE Skin___destroy__(mud::Skin* self) {
		delete self;
	}
	// Sun
	mud::Sun* EMSCRIPTEN_KEEPALIVE Sun_Sun_0() {
		return new mud::Sun();
	}
	float EMSCRIPTEN_KEEPALIVE Sun_get_azimuth(mud::Sun* self) {
		return self->azimuth;
	}
	float EMSCRIPTEN_KEEPALIVE Sun_get_elevation(mud::Sun* self) {
		return self->elevation;
	}
	Colour EMSCRIPTEN_KEEPALIVE Sun_get_colour(mud::Sun* self) {
		return self->m_colour;
	}
	float EMSCRIPTEN_KEEPALIVE Sun_get_intensity(mud::Sun* self) {
		return self->m_intensity;
	}
	void EMSCRIPTEN_KEEPALIVE Sun___destroy__(mud::Sun* self) {
		delete self;
	}
	// SymbolIndex
	void EMSCRIPTEN_KEEPALIVE SymbolIndex___destroy__(mud::SymbolIndex* self) {
		delete self;
	}
	// Texture
	uint16_t EMSCRIPTEN_KEEPALIVE Texture_get_width(mud::Texture* self) {
		return self->m_width;
	}
	uint16_t EMSCRIPTEN_KEEPALIVE Texture_get_height(mud::Texture* self) {
		return self->m_height;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE Texture_get_bits_per_pixel(mud::Texture* self) {
		return self->m_bits_per_pixel;
	}
	void EMSCRIPTEN_KEEPALIVE Texture___destroy__(mud::Texture* self) {
		delete self;
	}
	// UnshadedMaterialBlock
	mud::UnshadedMaterialBlock* EMSCRIPTEN_KEEPALIVE UnshadedMaterialBlock_UnshadedMaterialBlock_0() {
		return new mud::UnshadedMaterialBlock();
	}
	bool EMSCRIPTEN_KEEPALIVE UnshadedMaterialBlock_get_enabled(mud::UnshadedMaterialBlock* self) {
		return self->m_enabled;
	}
	void EMSCRIPTEN_KEEPALIVE UnshadedMaterialBlock___destroy__(mud::UnshadedMaterialBlock* self) {
		delete self;
	}
	// Viewport
	Camera EMSCRIPTEN_KEEPALIVE Viewport_get_camera(mud::Viewport* self) {
		return self->m_camera;
	}
	Scene EMSCRIPTEN_KEEPALIVE Viewport_get_scene(mud::Viewport* self) {
		return self->m_scene;
	}
	uint16_t EMSCRIPTEN_KEEPALIVE Viewport_get_index(mud::Viewport* self) {
		return self->m_index;
	}
	bool EMSCRIPTEN_KEEPALIVE Viewport_get_active(mud::Viewport* self) {
		return self->m_active;
	}
	uvec4 EMSCRIPTEN_KEEPALIVE Viewport_get_rect(mud::Viewport* self) {
		return self->m_rect;
	}
	bool EMSCRIPTEN_KEEPALIVE Viewport_get_scissor(mud::Viewport* self) {
		return self->m_scissor;
	}
	Colour EMSCRIPTEN_KEEPALIVE Viewport_get_clear_colour(mud::Viewport* self) {
		return self->m_clear_colour;
	}
	Shading EMSCRIPTEN_KEEPALIVE Viewport_get_shading(mud::Viewport* self) {
		return self->m_shading;
	}
	Lighting EMSCRIPTEN_KEEPALIVE Viewport_get_lighting(mud::Viewport* self) {
		return self->m_lighting;
	}
	void EMSCRIPTEN_KEEPALIVE Viewport___destroy__(mud::Viewport* self) {
		delete self;
	}
	// BlockCopy
	void EMSCRIPTEN_KEEPALIVE BlockCopy___destroy__(mud::BlockCopy* self) {
		delete self;
	}
	// DrawBlock
	void EMSCRIPTEN_KEEPALIVE DrawBlock___destroy__(mud::DrawBlock* self) {
		delete self;
	}
	// BlockDepth
	void EMSCRIPTEN_KEEPALIVE BlockDepth___destroy__(mud::BlockDepth* self) {
		delete self;
	}
	// BlockFilter
	void EMSCRIPTEN_KEEPALIVE BlockFilter___destroy__(mud::BlockFilter* self) {
		delete self;
	}
	// BlockParticles
	void EMSCRIPTEN_KEEPALIVE BlockParticles___destroy__(mud::BlockParticles* self) {
		delete self;
	}
	// BlockResolve
	void EMSCRIPTEN_KEEPALIVE BlockResolve___destroy__(mud::BlockResolve* self) {
		delete self;
	}
	// BlockSky
	void EMSCRIPTEN_KEEPALIVE BlockSky___destroy__(mud::BlockSky* self) {
		delete self;
	}
	// ClusteredFrustum
	mud::ClusteredFrustum* EMSCRIPTEN_KEEPALIVE ClusteredFrustum_ClusteredFrustum_0() {
		return new mud::ClusteredFrustum();
	}
	void EMSCRIPTEN_KEEPALIVE ClusteredFrustum___destroy__(mud::ClusteredFrustum* self) {
		delete self;
	}
	// Particles
	mud::Particles* EMSCRIPTEN_KEEPALIVE Particles_Particles_0() {
		return new mud::Particles();
	}
	Node3 EMSCRIPTEN_KEEPALIVE Particles_get_node(mud::Particles* self) {
		return self->m_node;
	}
	void EMSCRIPTEN_KEEPALIVE Particles___destroy__(mud::Particles* self) {
		delete self;
	}
	// RenderTarget
	void EMSCRIPTEN_KEEPALIVE RenderTarget___destroy__(mud::RenderTarget* self) {
		delete self;
	}
	
}


// 'AnimationTarget'
AnimationTarget EMSCRIPTEN_KEEPALIVE emscripten_enum_AnimationTarget_Position() {
	return mud::AnimationTarget::Position;
}
AnimationTarget EMSCRIPTEN_KEEPALIVE emscripten_enum_AnimationTarget_Rotation() {
	return mud::AnimationTarget::Rotation;
}
AnimationTarget EMSCRIPTEN_KEEPALIVE emscripten_enum_AnimationTarget_Scale() {
	return mud::AnimationTarget::Scale;
}
// 'BackgroundMode'
BackgroundMode EMSCRIPTEN_KEEPALIVE emscripten_enum_BackgroundMode_None() {
	return mud::BackgroundMode::None;
}
BackgroundMode EMSCRIPTEN_KEEPALIVE emscripten_enum_BackgroundMode_Panorama() {
	return mud::BackgroundMode::Panorama;
}
BackgroundMode EMSCRIPTEN_KEEPALIVE emscripten_enum_BackgroundMode_Radiance() {
	return mud::BackgroundMode::Radiance;
}
BackgroundMode EMSCRIPTEN_KEEPALIVE emscripten_enum_BackgroundMode_Custom() {
	return mud::BackgroundMode::Custom;
}
// 'BlendMode'
BlendMode EMSCRIPTEN_KEEPALIVE emscripten_enum_BlendMode_Mix() {
	return mud::BlendMode::Mix;
}
BlendMode EMSCRIPTEN_KEEPALIVE emscripten_enum_BlendMode_Add() {
	return mud::BlendMode::Add;
}
BlendMode EMSCRIPTEN_KEEPALIVE emscripten_enum_BlendMode_Sub() {
	return mud::BlendMode::Sub;
}
BlendMode EMSCRIPTEN_KEEPALIVE emscripten_enum_BlendMode_Mul() {
	return mud::BlendMode::Mul;
}
BlendMode EMSCRIPTEN_KEEPALIVE emscripten_enum_BlendMode_Normal() {
	return mud::BlendMode::Normal;
}
BlendMode EMSCRIPTEN_KEEPALIVE emscripten_enum_BlendMode_Alpha() {
	return mud::BlendMode::Alpha;
}
// 'CullMode'
CullMode EMSCRIPTEN_KEEPALIVE emscripten_enum_CullMode_None() {
	return mud::CullMode::None;
}
CullMode EMSCRIPTEN_KEEPALIVE emscripten_enum_CullMode_Front() {
	return mud::CullMode::Front;
}
CullMode EMSCRIPTEN_KEEPALIVE emscripten_enum_CullMode_Back() {
	return mud::CullMode::Back;
}
// 'DepthDraw'
DepthDraw EMSCRIPTEN_KEEPALIVE emscripten_enum_DepthDraw_Enabled() {
	return mud::DepthDraw::Enabled;
}
DepthDraw EMSCRIPTEN_KEEPALIVE emscripten_enum_DepthDraw_Disabled() {
	return mud::DepthDraw::Disabled;
}
// 'DepthTest'
DepthTest EMSCRIPTEN_KEEPALIVE emscripten_enum_DepthTest_Enabled() {
	return mud::DepthTest::Enabled;
}
DepthTest EMSCRIPTEN_KEEPALIVE emscripten_enum_DepthTest_Disabled() {
	return mud::DepthTest::Disabled;
}
// 'EmitterFlow'
EmitterFlow EMSCRIPTEN_KEEPALIVE emscripten_enum_EmitterFlow_Outward() {
	return mud::EmitterFlow::Outward;
}
EmitterFlow EMSCRIPTEN_KEEPALIVE emscripten_enum_EmitterFlow_Absolute() {
	return mud::EmitterFlow::Absolute;
}
// 'Interpolation'
Interpolation EMSCRIPTEN_KEEPALIVE emscripten_enum_Interpolation_Nearest() {
	return mud::Interpolation::Nearest;
}
Interpolation EMSCRIPTEN_KEEPALIVE emscripten_enum_Interpolation_Linear() {
	return mud::Interpolation::Linear;
}
Interpolation EMSCRIPTEN_KEEPALIVE emscripten_enum_Interpolation_Cubic() {
	return mud::Interpolation::Cubic;
}
// 'IsometricAngle'
IsometricAngle EMSCRIPTEN_KEEPALIVE emscripten_enum_IsometricAngle_NORTH() {
	return mud::NORTH;
}
IsometricAngle EMSCRIPTEN_KEEPALIVE emscripten_enum_IsometricAngle_SOUTH() {
	return mud::SOUTH;
}
IsometricAngle EMSCRIPTEN_KEEPALIVE emscripten_enum_IsometricAngle_EAST() {
	return mud::EAST;
}
IsometricAngle EMSCRIPTEN_KEEPALIVE emscripten_enum_IsometricAngle_WEST() {
	return mud::WEST;
}
// 'ItemShadow'
ItemShadow EMSCRIPTEN_KEEPALIVE emscripten_enum_ItemShadow_Default() {
	return mud::ItemShadow::Default;
}
ItemShadow EMSCRIPTEN_KEEPALIVE emscripten_enum_ItemShadow_DoubleSided() {
	return mud::ItemShadow::DoubleSided;
}
// 'LightType'
LightType EMSCRIPTEN_KEEPALIVE emscripten_enum_LightType_Direct() {
	return mud::LightType::Direct;
}
LightType EMSCRIPTEN_KEEPALIVE emscripten_enum_LightType_Point() {
	return mud::LightType::Point;
}
LightType EMSCRIPTEN_KEEPALIVE emscripten_enum_LightType_Spot() {
	return mud::LightType::Spot;
}
LightType EMSCRIPTEN_KEEPALIVE emscripten_enum_LightType_Count() {
	return mud::LightType::Count;
}
// 'Lighting'
Lighting EMSCRIPTEN_KEEPALIVE emscripten_enum_Lighting_None() {
	return mud::Lighting::None;
}
Lighting EMSCRIPTEN_KEEPALIVE emscripten_enum_Lighting_Clustered() {
	return mud::Lighting::Clustered;
}
Lighting EMSCRIPTEN_KEEPALIVE emscripten_enum_Lighting_Deferred() {
	return mud::Lighting::Deferred;
}
Lighting EMSCRIPTEN_KEEPALIVE emscripten_enum_Lighting_VoxelGI() {
	return mud::Lighting::VoxelGI;
}
// 'MSAA'
MSAA EMSCRIPTEN_KEEPALIVE emscripten_enum_MSAA_Disabled() {
	return mud::MSAA::Disabled;
}
MSAA EMSCRIPTEN_KEEPALIVE emscripten_enum_MSAA_X2() {
	return mud::MSAA::X2;
}
MSAA EMSCRIPTEN_KEEPALIVE emscripten_enum_MSAA_X4() {
	return mud::MSAA::X4;
}
MSAA EMSCRIPTEN_KEEPALIVE emscripten_enum_MSAA_X8() {
	return mud::MSAA::X8;
}
MSAA EMSCRIPTEN_KEEPALIVE emscripten_enum_MSAA_X16() {
	return mud::MSAA::X16;
}
// 'MaterialFlag'
MaterialFlag EMSCRIPTEN_KEEPALIVE emscripten_enum_MaterialFlag_TriplanarUV1() {
	return mud::MaterialFlag::TriplanarUV1;
}
MaterialFlag EMSCRIPTEN_KEEPALIVE emscripten_enum_MaterialFlag_TriplanarUV2() {
	return mud::MaterialFlag::TriplanarUV2;
}
MaterialFlag EMSCRIPTEN_KEEPALIVE emscripten_enum_MaterialFlag_Count() {
	return mud::MaterialFlag::Count;
}
// 'ModelFormat'
ModelFormat EMSCRIPTEN_KEEPALIVE emscripten_enum_ModelFormat_obj() {
	return mud::ModelFormat::obj;
}
ModelFormat EMSCRIPTEN_KEEPALIVE emscripten_enum_ModelFormat_gltf() {
	return mud::ModelFormat::gltf;
}
ModelFormat EMSCRIPTEN_KEEPALIVE emscripten_enum_ModelFormat_Count() {
	return mud::ModelFormat::Count;
}
// 'Month'
Month EMSCRIPTEN_KEEPALIVE emscripten_enum_Month_January() {
	return mud::Month::January;
}
Month EMSCRIPTEN_KEEPALIVE emscripten_enum_Month_February() {
	return mud::Month::February;
}
Month EMSCRIPTEN_KEEPALIVE emscripten_enum_Month_March() {
	return mud::Month::March;
}
Month EMSCRIPTEN_KEEPALIVE emscripten_enum_Month_April() {
	return mud::Month::April;
}
Month EMSCRIPTEN_KEEPALIVE emscripten_enum_Month_May() {
	return mud::Month::May;
}
Month EMSCRIPTEN_KEEPALIVE emscripten_enum_Month_June() {
	return mud::Month::June;
}
Month EMSCRIPTEN_KEEPALIVE emscripten_enum_Month_July() {
	return mud::Month::July;
}
Month EMSCRIPTEN_KEEPALIVE emscripten_enum_Month_August() {
	return mud::Month::August;
}
Month EMSCRIPTEN_KEEPALIVE emscripten_enum_Month_September() {
	return mud::Month::September;
}
Month EMSCRIPTEN_KEEPALIVE emscripten_enum_Month_October() {
	return mud::Month::October;
}
Month EMSCRIPTEN_KEEPALIVE emscripten_enum_Month_November() {
	return mud::Month::November;
}
Month EMSCRIPTEN_KEEPALIVE emscripten_enum_Month_December() {
	return mud::Month::December;
}
// 'PbrDiffuseMode'
PbrDiffuseMode EMSCRIPTEN_KEEPALIVE emscripten_enum_PbrDiffuseMode_Lambert() {
	return mud::PbrDiffuseMode::Lambert;
}
PbrDiffuseMode EMSCRIPTEN_KEEPALIVE emscripten_enum_PbrDiffuseMode_LambertHalf() {
	return mud::PbrDiffuseMode::LambertHalf;
}
PbrDiffuseMode EMSCRIPTEN_KEEPALIVE emscripten_enum_PbrDiffuseMode_OrenNayar() {
	return mud::PbrDiffuseMode::OrenNayar;
}
PbrDiffuseMode EMSCRIPTEN_KEEPALIVE emscripten_enum_PbrDiffuseMode_Burley() {
	return mud::PbrDiffuseMode::Burley;
}
PbrDiffuseMode EMSCRIPTEN_KEEPALIVE emscripten_enum_PbrDiffuseMode_Toon() {
	return mud::PbrDiffuseMode::Toon;
}
// 'PbrSpecularMode'
PbrSpecularMode EMSCRIPTEN_KEEPALIVE emscripten_enum_PbrSpecularMode_SchlickGGX() {
	return mud::PbrSpecularMode::SchlickGGX;
}
PbrSpecularMode EMSCRIPTEN_KEEPALIVE emscripten_enum_PbrSpecularMode_Blinn() {
	return mud::PbrSpecularMode::Blinn;
}
PbrSpecularMode EMSCRIPTEN_KEEPALIVE emscripten_enum_PbrSpecularMode_Phong() {
	return mud::PbrSpecularMode::Phong;
}
PbrSpecularMode EMSCRIPTEN_KEEPALIVE emscripten_enum_PbrSpecularMode_Toon() {
	return mud::PbrSpecularMode::Toon;
}
PbrSpecularMode EMSCRIPTEN_KEEPALIVE emscripten_enum_PbrSpecularMode_Disabled() {
	return mud::PbrSpecularMode::Disabled;
}
// 'ShaderType'
ShaderType EMSCRIPTEN_KEEPALIVE emscripten_enum_ShaderType_Compute() {
	return mud::ShaderType::Compute;
}
ShaderType EMSCRIPTEN_KEEPALIVE emscripten_enum_ShaderType_Fragment() {
	return mud::ShaderType::Fragment;
}
ShaderType EMSCRIPTEN_KEEPALIVE emscripten_enum_ShaderType_Geometry() {
	return mud::ShaderType::Geometry;
}
ShaderType EMSCRIPTEN_KEEPALIVE emscripten_enum_ShaderType_Vertex() {
	return mud::ShaderType::Vertex;
}
ShaderType EMSCRIPTEN_KEEPALIVE emscripten_enum_ShaderType_Count() {
	return mud::ShaderType::Count;
}
// 'Shading'
Shading EMSCRIPTEN_KEEPALIVE emscripten_enum_Shading_Wireframe() {
	return mud::Shading::Wireframe;
}
Shading EMSCRIPTEN_KEEPALIVE emscripten_enum_Shading_Unshaded() {
	return mud::Shading::Unshaded;
}
Shading EMSCRIPTEN_KEEPALIVE emscripten_enum_Shading_Shaded() {
	return mud::Shading::Shaded;
}
Shading EMSCRIPTEN_KEEPALIVE emscripten_enum_Shading_Volume() {
	return mud::Shading::Volume;
}
Shading EMSCRIPTEN_KEEPALIVE emscripten_enum_Shading_Voxels() {
	return mud::Shading::Voxels;
}
Shading EMSCRIPTEN_KEEPALIVE emscripten_enum_Shading_Lightmap() {
	return mud::Shading::Lightmap;
}
Shading EMSCRIPTEN_KEEPALIVE emscripten_enum_Shading_Clear() {
	return mud::Shading::Clear;
}
Shading EMSCRIPTEN_KEEPALIVE emscripten_enum_Shading_Count() {
	return mud::Shading::Count;
}
// 'ShadowFlags'
ShadowFlags EMSCRIPTEN_KEEPALIVE emscripten_enum_ShadowFlags_CSM_Stabilize() {
	return mud::CSM_Stabilize;
}
ShadowFlags EMSCRIPTEN_KEEPALIVE emscripten_enum_ShadowFlags_CSM_Optimize() {
	return mud::CSM_Optimize;
}
ShadowFlags EMSCRIPTEN_KEEPALIVE emscripten_enum_ShadowFlags_CSM_BlendSplits() {
	return mud::CSM_BlendSplits;
}
// 'TextureChannel'
TextureChannel EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureChannel_Red() {
	return mud::TextureChannel::Red;
}
TextureChannel EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureChannel_Green() {
	return mud::TextureChannel::Green;
}
TextureChannel EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureChannel_Blue() {
	return mud::TextureChannel::Blue;
}
TextureChannel EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureChannel_Alpha() {
	return mud::TextureChannel::Alpha;
}
TextureChannel EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureChannel_All() {
	return mud::TextureChannel::All;
}
// 'TextureHint'
TextureHint EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureHint_Black() {
	return mud::TextureHint::Black;
}
TextureHint EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureHint_White() {
	return mud::TextureHint::White;
}
TextureHint EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureHint_Normal() {
	return mud::TextureHint::Normal;
}
// 'TextureSampler'
TextureSampler EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureSampler_Source0() {
	return mud::TextureSampler::Source0;
}
TextureSampler EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureSampler_Source1() {
	return mud::TextureSampler::Source1;
}
TextureSampler EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureSampler_Source2() {
	return mud::TextureSampler::Source2;
}
TextureSampler EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureSampler_Source3() {
	return mud::TextureSampler::Source3;
}
TextureSampler EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureSampler_SourceDepth() {
	return mud::TextureSampler::SourceDepth;
}
TextureSampler EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureSampler_Color() {
	return mud::TextureSampler::Color;
}
TextureSampler EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureSampler_Albedo() {
	return mud::TextureSampler::Albedo;
}
TextureSampler EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureSampler_Metallic() {
	return mud::TextureSampler::Metallic;
}
TextureSampler EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureSampler_Roughness() {
	return mud::TextureSampler::Roughness;
}
TextureSampler EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureSampler_Emissive() {
	return mud::TextureSampler::Emissive;
}
TextureSampler EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureSampler_Normal() {
	return mud::TextureSampler::Normal;
}
TextureSampler EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureSampler_AO() {
	return mud::TextureSampler::AO;
}
TextureSampler EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureSampler_Depth() {
	return mud::TextureSampler::Depth;
}
TextureSampler EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureSampler_Skeleton() {
	return mud::TextureSampler::Skeleton;
}
TextureSampler EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureSampler_ShadowCSM() {
	return mud::TextureSampler::ShadowCSM;
}
TextureSampler EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureSampler_ShadowAtlas() {
	return mud::TextureSampler::ShadowAtlas;
}
TextureSampler EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureSampler_Radiance() {
	return mud::TextureSampler::Radiance;
}
TextureSampler EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureSampler_ReflectionProbe() {
	return mud::TextureSampler::ReflectionProbe;
}
TextureSampler EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureSampler_GIProbe() {
	return mud::TextureSampler::GIProbe;
}
TextureSampler EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureSampler_Lights() {
	return mud::TextureSampler::Lights;
}
TextureSampler EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureSampler_Clusters() {
	return mud::TextureSampler::Clusters;
}
TextureSampler EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureSampler_LightRecords() {
	return mud::TextureSampler::LightRecords;
}
TextureSampler EMSCRIPTEN_KEEPALIVE emscripten_enum_TextureSampler_Lightmap() {
	return mud::TextureSampler::Lightmap;
}
