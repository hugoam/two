#include <infra/Api.h>
#include <jobs/Api.h>
#include <type/Api.h>
#include <pool/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <ctx/Api.h>
#include <bgfx/Api.h>
#include <gfx/Api.h>

#ifdef MUD_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// Animated
	void DECL mud_Animated_advance_1(mud::Animated* self, float time) {
		self->advance(time);
	}
	void DECL mud_Animated_next_animation_0(mud::Animated* self) {
		self->next_animation();
	}
	void DECL mud_Animated_pause_0(mud::Animated* self) {
		self->pause();
	}
	void DECL mud_Animated_play_2(mud::Animated* self, const mud::Animation* animation, bool loop) {
		self->play(*animation, loop);
	}
	void DECL mud_Animated_play_3(mud::Animated* self, const mud::Animation* animation, bool loop, float blend) {
		self->play(*animation, loop, blend);
	}
	void DECL mud_Animated_play_4(mud::Animated* self, const mud::Animation* animation, bool loop, float blend, float speed) {
		self->play(*animation, loop, blend, speed);
	}
	void DECL mud_Animated_play_5(mud::Animated* self, const mud::Animation* animation, bool loop, float blend, float speed, bool transient) {
		self->play(*animation, loop, blend, speed, transient);
	}
	const char* DECL mud_Animated_playing_0(mud::Animated* self) {
		return self->playing().c_str();
	}
	void DECL mud_Animated_seek_1(mud::Animated* self, float time) {
		self->seek(time);
	}
	void DECL mud_Animated_start_2(mud::Animated* self, const char* animation, bool loop) {
		self->start(animation, loop);
	}
	void DECL mud_Animated_start_3(mud::Animated* self, const char* animation, bool loop, float blend) {
		self->start(animation, loop, blend);
	}
	void DECL mud_Animated_start_4(mud::Animated* self, const char* animation, bool loop, float blend, float speed) {
		self->start(animation, loop, blend, speed);
	}
	void DECL mud_Animated_start_5(mud::Animated* self, const char* animation, bool loop, float blend, float speed, bool transient) {
		self->start(animation, loop, blend, speed, transient);
	}
	void DECL mud_Animated_stop_0(mud::Animated* self) {
		self->stop();
	}
	bool DECL mud_Animated__get_active(mud::Animated* self) {
		return self->m_active;
	}
	void DECL mud_Animated__set_active(mud::Animated* self, bool value) {
		self->m_active = value;
	}
	float DECL mud_Animated__get_speed_scale(mud::Animated* self) {
		return self->m_speed_scale;
	}
	void DECL mud_Animated__set_speed_scale(mud::Animated* self, float value) {
		self->m_speed_scale = value;
	}
	float DECL mud_Animated__get_default_blend_time(mud::Animated* self) {
		return self->m_default_blend_time;
	}
	void DECL mud_Animated__set_default_blend_time(mud::Animated* self, float value) {
		self->m_default_blend_time = value;
	}
	void DECL mud_Animated__destroy(mud::Animated* self) {
		delete self;
	}
	// AnimatedTrack
	mud::AnimatedTrack* DECL mud_AnimatedTrack_AnimatedTrack_0() {
		return new mud::AnimatedTrack();
	}
	void DECL mud_AnimatedTrack__destroy(mud::AnimatedTrack* self) {
		delete self;
	}
	// Animation
	const char* DECL mud_Animation__get_name(mud::Animation* self) {
		return self->m_name.c_str();
	}
	void DECL mud_Animation__set_name(mud::Animation* self, const char* value) {
		self->m_name = value;
	}
	float DECL mud_Animation__get_length(mud::Animation* self) {
		return self->m_length;
	}
	void DECL mud_Animation__set_length(mud::Animation* self, float value) {
		self->m_length = value;
	}
	float DECL mud_Animation__get_step(mud::Animation* self) {
		return self->m_step;
	}
	void DECL mud_Animation__set_step(mud::Animation* self, float value) {
		self->m_step = value;
	}
	void DECL mud_Animation__destroy(mud::Animation* self) {
		delete self;
	}
	// AnimationPlay
	mud::AnimationPlay* DECL mud_AnimationPlay_AnimationPlay_0() {
		return new mud::AnimationPlay();
	}
	const mud::Animation* DECL mud_AnimationPlay__get_animation(mud::AnimationPlay* self) {
		return self->m_animation;
	}
	void DECL mud_AnimationPlay__set_animation(mud::AnimationPlay* self, const mud::Animation* value) {
		self->m_animation = value;
	}
	bool DECL mud_AnimationPlay__get_loop(mud::AnimationPlay* self) {
		return self->m_loop;
	}
	void DECL mud_AnimationPlay__set_loop(mud::AnimationPlay* self, bool value) {
		self->m_loop = value;
	}
	float DECL mud_AnimationPlay__get_speed(mud::AnimationPlay* self) {
		return self->m_speed;
	}
	void DECL mud_AnimationPlay__set_speed(mud::AnimationPlay* self, float value) {
		self->m_speed = value;
	}
	bool DECL mud_AnimationPlay__get_transient(mud::AnimationPlay* self) {
		return self->m_transient;
	}
	void DECL mud_AnimationPlay__set_transient(mud::AnimationPlay* self, bool value) {
		self->m_transient = value;
	}
	float DECL mud_AnimationPlay__get_fadeout(mud::AnimationPlay* self) {
		return self->m_fadeout;
	}
	void DECL mud_AnimationPlay__set_fadeout(mud::AnimationPlay* self, float value) {
		self->m_fadeout = value;
	}
	float DECL mud_AnimationPlay__get_fadeout_left(mud::AnimationPlay* self) {
		return self->m_fadeout_left;
	}
	void DECL mud_AnimationPlay__set_fadeout_left(mud::AnimationPlay* self, float value) {
		self->m_fadeout_left = value;
	}
	float DECL mud_AnimationPlay__get_cursor(mud::AnimationPlay* self) {
		return self->m_cursor;
	}
	void DECL mud_AnimationPlay__set_cursor(mud::AnimationPlay* self, float value) {
		self->m_cursor = value;
	}
	bool DECL mud_AnimationPlay__get_ended(mud::AnimationPlay* self) {
		return self->m_ended;
	}
	void DECL mud_AnimationPlay__set_ended(mud::AnimationPlay* self, bool value) {
		self->m_ended = value;
	}
	void DECL mud_AnimationPlay__destroy(mud::AnimationPlay* self) {
		delete self;
	}
	// AnimationTrack
	mud::Animation* DECL mud_AnimationTrack__get_animation(mud::AnimationTrack* self) {
		return self->m_animation;
	}
	void DECL mud_AnimationTrack__set_animation(mud::AnimationTrack* self, mud::Animation* value) {
		self->m_animation = value;
	}
	size_t DECL mud_AnimationTrack__get_node(mud::AnimationTrack* self) {
		return self->m_node;
	}
	void DECL mud_AnimationTrack__set_node(mud::AnimationTrack* self, size_t value) {
		self->m_node = value;
	}
	const char* DECL mud_AnimationTrack__get_node_name(mud::AnimationTrack* self) {
		return self->m_node_name.c_str();
	}
	void DECL mud_AnimationTrack__set_node_name(mud::AnimationTrack* self, const char* value) {
		self->m_node_name = value;
	}
	mud::AnimationTarget DECL mud_AnimationTrack__get_target(mud::AnimationTrack* self) {
		return self->m_target;
	}
	void DECL mud_AnimationTrack__set_target(mud::AnimationTrack* self, mud::AnimationTarget value) {
		self->m_target = value;
	}
	mud::Type* DECL mud_AnimationTrack__get_value_type(mud::AnimationTrack* self) {
		return self->m_value_type;
	}
	void DECL mud_AnimationTrack__set_value_type(mud::AnimationTrack* self, mud::Type* value) {
		self->m_value_type = value;
	}
	float DECL mud_AnimationTrack__get_length(mud::AnimationTrack* self) {
		return self->m_length;
	}
	void DECL mud_AnimationTrack__set_length(mud::AnimationTrack* self, float value) {
		self->m_length = value;
	}
	mud::Interpolation DECL mud_AnimationTrack__get_interpolation(mud::AnimationTrack* self) {
		return self->m_interpolation;
	}
	void DECL mud_AnimationTrack__set_interpolation(mud::AnimationTrack* self, mud::Interpolation value) {
		self->m_interpolation = value;
	}
	void DECL mud_AnimationTrack__destroy(mud::AnimationTrack* self) {
		delete self;
	}
	// Background
	mud::Background* DECL mud_Background_Background_0() {
		return new mud::Background();
	}
	mud::BackgroundMode DECL mud_Background__get_mode(mud::Background* self) {
		return self->m_mode;
	}
	void DECL mud_Background__set_mode(mud::Background* self, mud::BackgroundMode value) {
		self->m_mode = value;
	}
	mud::Colour* DECL mud_Background__get_colour(mud::Background* self) {
		static mud::Colour temp;
		return (temp = self->m_colour, &temp);
	}
	void DECL mud_Background__set_colour(mud::Background* self, mud::Colour* value) {
		self->m_colour = *value;
	}
	mud::Program* DECL mud_Background__get_custoprogram(mud::Background* self) {
		return self->m_custom_program;
	}
	void DECL mud_Background__set_custoprogram(mud::Background* self, mud::Program* value) {
		self->m_custom_program = value;
	}
	void DECL mud_Background__destroy(mud::Background* self) {
		delete self;
	}
	// BaseMaterialBlock
	mud::BaseMaterialBlock* DECL mud_BaseMaterialBlock_BaseMaterialBlock_0() {
		return new mud::BaseMaterialBlock();
	}
	mud::BlendMode DECL mud_BaseMaterialBlock__get_blend_mode(mud::BaseMaterialBlock* self) {
		return self->m_blend_mode;
	}
	void DECL mud_BaseMaterialBlock__set_blend_mode(mud::BaseMaterialBlock* self, mud::BlendMode value) {
		self->m_blend_mode = value;
	}
	mud::CullMode DECL mud_BaseMaterialBlock__get_cull_mode(mud::BaseMaterialBlock* self) {
		return self->m_cull_mode;
	}
	void DECL mud_BaseMaterialBlock__set_cull_mode(mud::BaseMaterialBlock* self, mud::CullMode value) {
		self->m_cull_mode = value;
	}
	mud::DepthDraw DECL mud_BaseMaterialBlock__get_depth_draw_mode(mud::BaseMaterialBlock* self) {
		return self->m_depth_draw_mode;
	}
	void DECL mud_BaseMaterialBlock__set_depth_draw_mode(mud::BaseMaterialBlock* self, mud::DepthDraw value) {
		self->m_depth_draw_mode = value;
	}
	mud::DepthTest DECL mud_BaseMaterialBlock__get_depth_test(mud::BaseMaterialBlock* self) {
		return self->m_depth_test;
	}
	void DECL mud_BaseMaterialBlock__set_depth_test(mud::BaseMaterialBlock* self, mud::DepthTest value) {
		self->m_depth_test = value;
	}
	mud::vec2* DECL mud_BaseMaterialBlock__get_uv0_scale(mud::BaseMaterialBlock* self) {
		static mud::vec2 temp;
		return (temp = self->m_uv0_scale, &temp);
	}
	void DECL mud_BaseMaterialBlock__set_uv0_scale(mud::BaseMaterialBlock* self, mud::vec2* value) {
		self->m_uv0_scale = *value;
	}
	mud::vec2* DECL mud_BaseMaterialBlock__get_uv0_offset(mud::BaseMaterialBlock* self) {
		static mud::vec2 temp;
		return (temp = self->m_uv0_offset, &temp);
	}
	void DECL mud_BaseMaterialBlock__set_uv0_offset(mud::BaseMaterialBlock* self, mud::vec2* value) {
		self->m_uv0_offset = *value;
	}
	mud::vec2* DECL mud_BaseMaterialBlock__get_uv1_scale(mud::BaseMaterialBlock* self) {
		static mud::vec2 temp;
		return (temp = self->m_uv1_scale, &temp);
	}
	void DECL mud_BaseMaterialBlock__set_uv1_scale(mud::BaseMaterialBlock* self, mud::vec2* value) {
		self->m_uv1_scale = *value;
	}
	mud::vec2* DECL mud_BaseMaterialBlock__get_uv1_offset(mud::BaseMaterialBlock* self) {
		static mud::vec2 temp;
		return (temp = self->m_uv1_offset, &temp);
	}
	void DECL mud_BaseMaterialBlock__set_uv1_offset(mud::BaseMaterialBlock* self, mud::vec2* value) {
		self->m_uv1_offset = *value;
	}
	bool DECL mud_BaseMaterialBlock__get_is_alpha(mud::BaseMaterialBlock* self) {
		return self->m_is_alpha;
	}
	void DECL mud_BaseMaterialBlock__set_is_alpha(mud::BaseMaterialBlock* self, bool value) {
		self->m_is_alpha = value;
	}
	bool DECL mud_BaseMaterialBlock__get_screen_filter(mud::BaseMaterialBlock* self) {
		return self->m_screen_filter;
	}
	void DECL mud_BaseMaterialBlock__set_screen_filter(mud::BaseMaterialBlock* self, bool value) {
		self->m_screen_filter = value;
	}
	void DECL mud_BaseMaterialBlock__destroy(mud::BaseMaterialBlock* self) {
		delete self;
	}
	// Bone
	mud::Bone* DECL mud_Bone_Bone_0() {
		return new mud::Bone();
	}
	mud::vec3* DECL mud_Bone__get_position(mud::Bone* self) {
		static mud::vec3 temp;
		return (temp = self->m_position, &temp);
	}
	void DECL mud_Bone__set_position(mud::Bone* self, mud::vec3* value) {
		self->m_position = *value;
	}
	mud::quat* DECL mud_Bone__get_rotation(mud::Bone* self) {
		static mud::quat temp;
		return (temp = self->m_rotation, &temp);
	}
	void DECL mud_Bone__set_rotation(mud::Bone* self, mud::quat* value) {
		self->m_rotation = *value;
	}
	mud::vec3* DECL mud_Bone__get_scale(mud::Bone* self) {
		static mud::vec3 temp;
		return (temp = self->m_scale, &temp);
	}
	void DECL mud_Bone__set_scale(mud::Bone* self, mud::vec3* value) {
		self->m_scale = *value;
	}
	void DECL mud_Bone__destroy(mud::Bone* self) {
		delete self;
	}
	// Camera
	mud::vec3* DECL mud_Camera__get_eye(mud::Camera* self) {
		static mud::vec3 temp;
		return (temp = self->m_eye, &temp);
	}
	void DECL mud_Camera__set_eye(mud::Camera* self, mud::vec3* value) {
		self->m_eye = *value;
	}
	mud::vec3* DECL mud_Camera__get_target(mud::Camera* self) {
		static mud::vec3 temp;
		return (temp = self->m_target, &temp);
	}
	void DECL mud_Camera__set_target(mud::Camera* self, mud::vec3* value) {
		self->m_target = *value;
	}
	mud::mat4* DECL mud_Camera__get_transform(mud::Camera* self) {
		static mud::mat4 temp;
		return (temp = self->m_transform, &temp);
	}
	void DECL mud_Camera__set_transform(mud::Camera* self, mud::mat4* value) {
		self->m_transform = *value;
	}
	mud::mat4* DECL mud_Camera__get_projection(mud::Camera* self) {
		static mud::mat4 temp;
		return (temp = self->m_projection, &temp);
	}
	void DECL mud_Camera__set_projection(mud::Camera* self, mud::mat4* value) {
		self->m_projection = *value;
	}
	float DECL mud_Camera__get_fov(mud::Camera* self) {
		return self->m_fov;
	}
	void DECL mud_Camera__set_fov(mud::Camera* self, float value) {
		self->m_fov = value;
	}
	float DECL mud_Camera__get_aspect(mud::Camera* self) {
		return self->m_aspect;
	}
	void DECL mud_Camera__set_aspect(mud::Camera* self, float value) {
		self->m_aspect = value;
	}
	float DECL mud_Camera__get_near(mud::Camera* self) {
		return self->m_near;
	}
	void DECL mud_Camera__set_near(mud::Camera* self, float value) {
		self->m_near = value;
	}
	float DECL mud_Camera__get_far(mud::Camera* self) {
		return self->m_far;
	}
	void DECL mud_Camera__set_far(mud::Camera* self, float value) {
		self->m_far = value;
	}
	bool DECL mud_Camera__get_orthographic(mud::Camera* self) {
		return self->m_orthographic;
	}
	void DECL mud_Camera__set_orthographic(mud::Camera* self, bool value) {
		self->m_orthographic = value;
	}
	float DECL mud_Camera__get_height(mud::Camera* self) {
		return self->m_height;
	}
	void DECL mud_Camera__set_height(mud::Camera* self, float value) {
		self->m_height = value;
	}
	bool DECL mud_Camera__get_optimize_ends(mud::Camera* self) {
		return self->m_optimize_ends;
	}
	void DECL mud_Camera__set_optimize_ends(mud::Camera* self, bool value) {
		self->m_optimize_ends = value;
	}
	bool DECL mud_Camera__get_clustered(mud::Camera* self) {
		return self->m_clustered;
	}
	void DECL mud_Camera__set_clustered(mud::Camera* self, bool value) {
		self->m_clustered = value;
	}
	mud::vec4* DECL mud_Camera__get_lod_offsets(mud::Camera* self) {
		static mud::vec4 temp;
		return (temp = self->m_lod_offsets, &temp);
	}
	void DECL mud_Camera__set_lod_offsets(mud::Camera* self, mud::vec4* value) {
		self->m_lod_offsets = *value;
	}
	void DECL mud_Camera__destroy(mud::Camera* self) {
		delete self;
	}
	// Culler
	mud::Viewport* DECL mud_Culler__get_viewport(mud::Culler* self) {
		return self->m_viewport;
	}
	void DECL mud_Culler__set_viewport(mud::Culler* self, mud::Viewport* value) {
		self->m_viewport = value;
	}
	void DECL mud_Culler__destroy(mud::Culler* self) {
		delete self;
	}
	// DepthParams
	mud::DepthParams* DECL mud_DepthParams_DepthParams_0() {
		return new mud::DepthParams();
	}
	void DECL mud_DepthParams__destroy(mud::DepthParams* self) {
		delete self;
	}
	// Environment
	mud::Environment* DECL mud_Environment_Environment_0() {
		return new mud::Environment();
	}
	mud::Background* DECL mud_Environment__get_background(mud::Environment* self) {
		static mud::Background temp;
		return (temp = self->m_background, &temp);
	}
	void DECL mud_Environment__set_background(mud::Environment* self, mud::Background* value) {
		self->m_background = *value;
	}
	mud::Radiance* DECL mud_Environment__get_radiance(mud::Environment* self) {
		static mud::Radiance temp;
		return (temp = self->m_radiance, &temp);
	}
	void DECL mud_Environment__set_radiance(mud::Environment* self, mud::Radiance* value) {
		self->m_radiance = *value;
	}
	mud::Sun* DECL mud_Environment__get_sun(mud::Environment* self) {
		static mud::Sun temp;
		return (temp = self->m_sun, &temp);
	}
	void DECL mud_Environment__set_sun(mud::Environment* self, mud::Sun* value) {
		self->m_sun = *value;
	}
	mud::Fog* DECL mud_Environment__get_fog(mud::Environment* self) {
		static mud::Fog temp;
		return (temp = self->m_fog, &temp);
	}
	void DECL mud_Environment__set_fog(mud::Environment* self, mud::Fog* value) {
		self->m_fog = *value;
	}
	void DECL mud_Environment__destroy(mud::Environment* self) {
		delete self;
	}
	// Filter
	void DECL mud_Filter__destroy(mud::Filter* self) {
		delete self;
	}
	// Fog
	mud::Fog* DECL mud_Fog_Fog_0() {
		return new mud::Fog();
	}
	bool DECL mud_Fog__get_enabled(mud::Fog* self) {
		return self->m_enabled;
	}
	void DECL mud_Fog__set_enabled(mud::Fog* self, bool value) {
		self->m_enabled = value;
	}
	float DECL mud_Fog__get_density(mud::Fog* self) {
		return self->m_density;
	}
	void DECL mud_Fog__set_density(mud::Fog* self, float value) {
		self->m_density = value;
	}
	mud::Colour* DECL mud_Fog__get_colour(mud::Fog* self) {
		static mud::Colour temp;
		return (temp = self->m_colour, &temp);
	}
	void DECL mud_Fog__set_colour(mud::Fog* self, mud::Colour* value) {
		self->m_colour = *value;
	}
	bool DECL mud_Fog__get_depth(mud::Fog* self) {
		return self->m_depth;
	}
	void DECL mud_Fog__set_depth(mud::Fog* self, bool value) {
		self->m_depth = value;
	}
	float DECL mud_Fog__get_depth_begin(mud::Fog* self) {
		return self->m_depth_begin;
	}
	void DECL mud_Fog__set_depth_begin(mud::Fog* self, float value) {
		self->m_depth_begin = value;
	}
	float DECL mud_Fog__get_depth_curve(mud::Fog* self) {
		return self->m_depth_curve;
	}
	void DECL mud_Fog__set_depth_curve(mud::Fog* self, float value) {
		self->m_depth_curve = value;
	}
	bool DECL mud_Fog__get_height(mud::Fog* self) {
		return self->m_height;
	}
	void DECL mud_Fog__set_height(mud::Fog* self, bool value) {
		self->m_height = value;
	}
	float DECL mud_Fog__get_height_min(mud::Fog* self) {
		return self->m_height_min;
	}
	void DECL mud_Fog__set_height_min(mud::Fog* self, float value) {
		self->m_height_min = value;
	}
	float DECL mud_Fog__get_height_max(mud::Fog* self) {
		return self->m_height_max;
	}
	void DECL mud_Fog__set_height_max(mud::Fog* self, float value) {
		self->m_height_max = value;
	}
	float DECL mud_Fog__get_height_curve(mud::Fog* self) {
		return self->m_height_curve;
	}
	void DECL mud_Fog__set_height_curve(mud::Fog* self, float value) {
		self->m_height_curve = value;
	}
	bool DECL mud_Fog__get_transmit(mud::Fog* self) {
		return self->m_transmit;
	}
	void DECL mud_Fog__set_transmit(mud::Fog* self, bool value) {
		self->m_transmit = value;
	}
	float DECL mud_Fog__get_transmit_curve(mud::Fog* self) {
		return self->m_transmit_curve;
	}
	void DECL mud_Fog__set_transmit_curve(mud::Fog* self, float value) {
		self->m_transmit_curve = value;
	}
	void DECL mud_Fog__destroy(mud::Fog* self) {
		delete self;
	}
	// FrameBuffer
	void DECL mud_FrameBuffer__destroy(mud::FrameBuffer* self) {
		delete self;
	}
	// FresnelMaterialBlock
	mud::FresnelMaterialBlock* DECL mud_FresnelMaterialBlock_FresnelMaterialBlock_0() {
		return new mud::FresnelMaterialBlock();
	}
	bool DECL mud_FresnelMaterialBlock__get_enabled(mud::FresnelMaterialBlock* self) {
		return self->m_enabled;
	}
	void DECL mud_FresnelMaterialBlock__set_enabled(mud::FresnelMaterialBlock* self, bool value) {
		self->m_enabled = value;
	}
	float DECL mud_FresnelMaterialBlock__get_fresnel_scale(mud::FresnelMaterialBlock* self) {
		return self->m_fresnel_scale;
	}
	void DECL mud_FresnelMaterialBlock__set_fresnel_scale(mud::FresnelMaterialBlock* self, float value) {
		self->m_fresnel_scale = value;
	}
	float DECL mud_FresnelMaterialBlock__get_fresnel_bias(mud::FresnelMaterialBlock* self) {
		return self->m_fresnel_bias;
	}
	void DECL mud_FresnelMaterialBlock__set_fresnel_bias(mud::FresnelMaterialBlock* self, float value) {
		self->m_fresnel_bias = value;
	}
	float DECL mud_FresnelMaterialBlock__get_fresnel_power(mud::FresnelMaterialBlock* self) {
		return self->m_fresnel_power;
	}
	void DECL mud_FresnelMaterialBlock__set_fresnel_power(mud::FresnelMaterialBlock* self, float value) {
		self->m_fresnel_power = value;
	}
	void DECL mud_FresnelMaterialBlock__destroy(mud::FresnelMaterialBlock* self) {
		delete self;
	}
	// Frustum
	float DECL mud_Frustum__get_fov(mud::Frustum* self) {
		return self->m_fov;
	}
	void DECL mud_Frustum__set_fov(mud::Frustum* self, float value) {
		self->m_fov = value;
	}
	float DECL mud_Frustum__get_aspect(mud::Frustum* self) {
		return self->m_aspect;
	}
	void DECL mud_Frustum__set_aspect(mud::Frustum* self, float value) {
		self->m_aspect = value;
	}
	float DECL mud_Frustum__get_near(mud::Frustum* self) {
		return self->m_near;
	}
	void DECL mud_Frustum__set_near(mud::Frustum* self, float value) {
		self->m_near = value;
	}
	float DECL mud_Frustum__get_far(mud::Frustum* self) {
		return self->m_far;
	}
	void DECL mud_Frustum__set_far(mud::Frustum* self, float value) {
		self->m_far = value;
	}
	mud::vec3* DECL mud_Frustum__get_center(mud::Frustum* self) {
		static mud::vec3 temp;
		return (temp = self->m_center, &temp);
	}
	void DECL mud_Frustum__set_center(mud::Frustum* self, mud::vec3* value) {
		self->m_center = *value;
	}
	float DECL mud_Frustum__get_radius(mud::Frustum* self) {
		return self->m_radius;
	}
	void DECL mud_Frustum__set_radius(mud::Frustum* self, float value) {
		self->m_radius = value;
	}
	void DECL mud_Frustum__destroy(mud::Frustum* self) {
		delete self;
	}
	// FrustumSlice
	mud::FrustumSlice* DECL mud_FrustumSlice_FrustumSlice_0() {
		return new mud::FrustumSlice();
	}
	void DECL mud_FrustumSlice__destroy(mud::FrustumSlice* self) {
		delete self;
	}
	// GfxBlock
	mud::Type* DECL mud_GfxBlock__get_type(mud::GfxBlock* self) {
		return &self->m_type;
	}
	uint8_t DECL mud_GfxBlock__get_index(mud::GfxBlock* self) {
		return self->m_index;
	}
	void DECL mud_GfxBlock__set_index(mud::GfxBlock* self, uint8_t value) {
		self->m_index = value;
	}
	void DECL mud_GfxBlock__destroy(mud::GfxBlock* self) {
		delete self;
	}
	// GfxContext
	void DECL mud_GfxContext__destroy(mud::GfxContext* self) {
		delete self;
	}
	// GfxSystem
	mud::GfxSystem* DECL mud_GfxSystem_GfxSystem_1(const char* resource_path) {
		return new mud::GfxSystem(resource_path);
	}
	void DECL mud_GfxSystem_add_resource_path_1(mud::GfxSystem* self, const char* path) {
		self->add_resource_path(path);
	}
	void DECL mud_GfxSystem_add_resource_path_2(mud::GfxSystem* self, const char* path, bool relative) {
		self->add_resource_path(path, relative);
	}
	mud::Material* DECL mud_GfxSystem_debug_material_0(mud::GfxSystem* self) {
		return &self->debug_material();
	}
	mud::Material* DECL mud_GfxSystem_fetch_image256_material_1(mud::GfxSystem* self, const mud::Image256* image) {
		return &self->fetch_image256_material(*image);
	}
	mud::Material* DECL mud_GfxSystem_fetch_material_2(mud::GfxSystem* self, const char* name, const char* shader) {
		return &self->fetch_material(name, shader);
	}
	mud::Material* DECL mud_GfxSystem_fetch_material_3(mud::GfxSystem* self, const char* name, const char* shader, bool builtin) {
		return &self->fetch_material(name, shader, builtin);
	}
	mud::Model* DECL mud_GfxSystem_fetch_symbol_3(mud::GfxSystem* self, const mud::Symbol* symbol, const mud::Shape* shape, mud::DrawMode draw_mode) {
		return &self->fetch_symbol(*symbol, *shape, draw_mode);
	}
	mud::Material* DECL mud_GfxSystem_fetch_symbol_material_2(mud::GfxSystem* self, const mud::Symbol* symbol, mud::DrawMode draw_mode) {
		return &self->fetch_symbol_material(*symbol, draw_mode);
	}
	void DECL mud_GfxSystem__destroy(mud::GfxSystem* self) {
		delete self;
	}
	// Gnode
	void DECL mud_Gnode__destroy(mud::Gnode* self) {
		delete self;
	}
	// ImmediateDraw
	void DECL mud_ImmediateDraw__destroy(mud::ImmediateDraw* self) {
		delete self;
	}
	// ImportConfig
	mud::ImportConfig* DECL mud_ImportConfig_ImportConfig_0() {
		return new mud::ImportConfig();
	}
	mud::ModelFormat DECL mud_ImportConfig__get_format(mud::ImportConfig* self) {
		return self->m_format;
	}
	void DECL mud_ImportConfig__set_format(mud::ImportConfig* self, mud::ModelFormat value) {
		self->m_format = value;
	}
	mud::vec3* DECL mud_ImportConfig__get_position(mud::ImportConfig* self) {
		static mud::vec3 temp;
		return (temp = self->m_position, &temp);
	}
	void DECL mud_ImportConfig__set_position(mud::ImportConfig* self, mud::vec3* value) {
		self->m_position = *value;
	}
	mud::quat* DECL mud_ImportConfig__get_rotation(mud::ImportConfig* self) {
		static mud::quat temp;
		return (temp = self->m_rotation, &temp);
	}
	void DECL mud_ImportConfig__set_rotation(mud::ImportConfig* self, mud::quat* value) {
		self->m_rotation = *value;
	}
	mud::vec3* DECL mud_ImportConfig__get_scale(mud::ImportConfig* self) {
		static mud::vec3 temp;
		return (temp = self->m_scale, &temp);
	}
	void DECL mud_ImportConfig__set_scale(mud::ImportConfig* self, mud::vec3* value) {
		self->m_scale = *value;
	}
	mud::mat4* DECL mud_ImportConfig__get_transform(mud::ImportConfig* self) {
		static mud::mat4 temp;
		return (temp = self->m_transform, &temp);
	}
	void DECL mud_ImportConfig__set_transform(mud::ImportConfig* self, mud::mat4* value) {
		self->m_transform = *value;
	}
	const char* DECL mud_ImportConfig__get_suffix(mud::ImportConfig* self) {
		return self->m_suffix.c_str();
	}
	void DECL mud_ImportConfig__set_suffix(mud::ImportConfig* self, const char* value) {
		self->m_suffix = value;
	}
	bool DECL mud_ImportConfig__get_force_reimport(mud::ImportConfig* self) {
		return self->m_force_reimport;
	}
	void DECL mud_ImportConfig__set_force_reimport(mud::ImportConfig* self, bool value) {
		self->m_force_reimport = value;
	}
	bool DECL mud_ImportConfig__get_cache_geometry(mud::ImportConfig* self) {
		return self->m_cache_geometry;
	}
	void DECL mud_ImportConfig__set_cache_geometry(mud::ImportConfig* self, bool value) {
		self->m_cache_geometry = value;
	}
	bool DECL mud_ImportConfig__get_optimize_geometry(mud::ImportConfig* self) {
		return self->m_optimize_geometry;
	}
	void DECL mud_ImportConfig__set_optimize_geometry(mud::ImportConfig* self, bool value) {
		self->m_optimize_geometry = value;
	}
	uint32_t DECL mud_ImportConfig__get_flags(mud::ImportConfig* self) {
		return self->m_flags;
	}
	void DECL mud_ImportConfig__set_flags(mud::ImportConfig* self, uint32_t value) {
		self->m_flags = value;
	}
	void DECL mud_ImportConfig__destroy(mud::ImportConfig* self) {
		delete self;
	}
	// Item
	mud::Node3* DECL mud_Item__get_node(mud::Item* self) {
		return self->m_node;
	}
	void DECL mud_Item__set_node(mud::Item* self, mud::Node3* value) {
		self->m_node = value;
	}
	mud::Model* DECL mud_Item__get_model(mud::Item* self) {
		return self->m_model;
	}
	void DECL mud_Item__set_model(mud::Item* self, mud::Model* value) {
		self->m_model = value;
	}
	uint32_t DECL mud_Item__get_flags(mud::Item* self) {
		return self->m_flags;
	}
	void DECL mud_Item__set_flags(mud::Item* self, uint32_t value) {
		self->m_flags = value;
	}
	mud::Colour* DECL mud_Item__get_colour(mud::Item* self) {
		static mud::Colour temp;
		return (temp = self->m_colour, &temp);
	}
	void DECL mud_Item__set_colour(mud::Item* self, mud::Colour* value) {
		self->m_colour = *value;
	}
	mud::Material* DECL mud_Item__get_material(mud::Item* self) {
		return self->m_material;
	}
	void DECL mud_Item__set_material(mud::Item* self, mud::Material* value) {
		self->m_material = value;
	}
	bool DECL mud_Item__get_visible(mud::Item* self) {
		return self->m_visible;
	}
	void DECL mud_Item__set_visible(mud::Item* self, bool value) {
		self->m_visible = value;
	}
	mud::ItemShadow DECL mud_Item__get_shadow(mud::Item* self) {
		return self->m_shadow;
	}
	void DECL mud_Item__set_shadow(mud::Item* self, mud::ItemShadow value) {
		self->m_shadow = value;
	}
	mud::Rig* DECL mud_Item__get_rig(mud::Item* self) {
		return self->m_rig;
	}
	void DECL mud_Item__set_rig(mud::Item* self, mud::Rig* value) {
		self->m_rig = value;
	}
	void DECL mud_Item__destroy(mud::Item* self) {
		delete self;
	}
	// Joint
	mud::Joint* DECL mud_Joint_Joint_0() {
		return new mud::Joint();
	}
	void DECL mud_Joint__destroy(mud::Joint* self) {
		delete self;
	}
	// Light
	mud::Node3* DECL mud_Light__get_node(mud::Light* self) {
		return &self->m_node;
	}
	mud::LightType DECL mud_Light__get_type(mud::Light* self) {
		return self->m_type;
	}
	void DECL mud_Light__set_type(mud::Light* self, mud::LightType value) {
		self->m_type = value;
	}
	bool DECL mud_Light__get_visible(mud::Light* self) {
		return self->m_visible;
	}
	void DECL mud_Light__set_visible(mud::Light* self, bool value) {
		self->m_visible = value;
	}
	mud::Colour* DECL mud_Light__get_colour(mud::Light* self) {
		static mud::Colour temp;
		return (temp = self->m_colour, &temp);
	}
	void DECL mud_Light__set_colour(mud::Light* self, mud::Colour* value) {
		self->m_colour = *value;
	}
	float DECL mud_Light__get_range(mud::Light* self) {
		return self->m_range;
	}
	void DECL mud_Light__set_range(mud::Light* self, float value) {
		self->m_range = value;
	}
	float DECL mud_Light__get_energy(mud::Light* self) {
		return self->m_energy;
	}
	void DECL mud_Light__set_energy(mud::Light* self, float value) {
		self->m_energy = value;
	}
	float DECL mud_Light__get_specular(mud::Light* self) {
		return self->m_specular;
	}
	void DECL mud_Light__set_specular(mud::Light* self, float value) {
		self->m_specular = value;
	}
	float DECL mud_Light__get_attenuation(mud::Light* self) {
		return self->m_attenuation;
	}
	void DECL mud_Light__set_attenuation(mud::Light* self, float value) {
		self->m_attenuation = value;
	}
	bool DECL mud_Light__get_shadows(mud::Light* self) {
		return self->m_shadows;
	}
	void DECL mud_Light__set_shadows(mud::Light* self, bool value) {
		self->m_shadows = value;
	}
	mud::Colour* DECL mud_Light__get_shadow_colour(mud::Light* self) {
		static mud::Colour temp;
		return (temp = self->m_shadow_colour, &temp);
	}
	void DECL mud_Light__set_shadow_colour(mud::Light* self, mud::Colour* value) {
		self->m_shadow_colour = *value;
	}
	float DECL mud_Light__get_shadow_range(mud::Light* self) {
		return self->m_shadow_range;
	}
	void DECL mud_Light__set_shadow_range(mud::Light* self, float value) {
		self->m_shadow_range = value;
	}
	uint32_t DECL mud_Light__get_layers(mud::Light* self) {
		return self->m_layers;
	}
	void DECL mud_Light__set_layers(mud::Light* self, uint32_t value) {
		self->m_layers = value;
	}
	uint32_t DECL mud_Light__get_last_render(mud::Light* self) {
		return self->m_last_render;
	}
	void DECL mud_Light__set_last_render(mud::Light* self, uint32_t value) {
		self->m_last_render = value;
	}
	uint32_t DECL mud_Light__get_last_update(mud::Light* self) {
		return self->m_last_update;
	}
	void DECL mud_Light__set_last_update(mud::Light* self, uint32_t value) {
		self->m_last_update = value;
	}
	float DECL mud_Light__get_spot_angle(mud::Light* self) {
		return self->m_spot_angle;
	}
	void DECL mud_Light__set_spot_angle(mud::Light* self, float value) {
		self->m_spot_angle = value;
	}
	float DECL mud_Light__get_spot_attenuation(mud::Light* self) {
		return self->m_spot_attenuation;
	}
	void DECL mud_Light__set_spot_attenuation(mud::Light* self, float value) {
		self->m_spot_attenuation = value;
	}
	mud::ShadowFlags DECL mud_Light__get_shadow_flags(mud::Light* self) {
		return self->m_shadow_flags;
	}
	void DECL mud_Light__set_shadow_flags(mud::Light* self, mud::ShadowFlags value) {
		self->m_shadow_flags = value;
	}
	uint8_t DECL mud_Light__get_shadow_nusplits(mud::Light* self) {
		return self->m_shadow_num_splits;
	}
	void DECL mud_Light__set_shadow_nusplits(mud::Light* self, uint8_t value) {
		self->m_shadow_num_splits = value;
	}
	float DECL mud_Light__get_shadow_split_distribution(mud::Light* self) {
		return self->m_shadow_split_distribution;
	}
	void DECL mud_Light__set_shadow_split_distribution(mud::Light* self, float value) {
		self->m_shadow_split_distribution = value;
	}
	float DECL mud_Light__get_shadow_normal_bias(mud::Light* self) {
		return self->m_shadow_normal_bias;
	}
	void DECL mud_Light__set_shadow_normal_bias(mud::Light* self, float value) {
		self->m_shadow_normal_bias = value;
	}
	float DECL mud_Light__get_shadow_bias(mud::Light* self) {
		return self->m_shadow_bias;
	}
	void DECL mud_Light__set_shadow_bias(mud::Light* self, float value) {
		self->m_shadow_bias = value;
	}
	void DECL mud_Light__destroy(mud::Light* self) {
		delete self;
	}
	// Material
	uint16_t DECL mud_Material__get_index(mud::Material* self) {
		return self->m_index;
	}
	void DECL mud_Material__set_index(mud::Material* self, uint16_t value) {
		self->m_index = value;
	}
	bool DECL mud_Material__get_builtin(mud::Material* self) {
		return self->m_builtin;
	}
	void DECL mud_Material__set_builtin(mud::Material* self, bool value) {
		self->m_builtin = value;
	}
	mud::Program* DECL mud_Material__get_program(mud::Material* self) {
		return self->m_program;
	}
	void DECL mud_Material__set_program(mud::Material* self, mud::Program* value) {
		self->m_program = value;
	}
	mud::BaseMaterialBlock* DECL mud_Material__get_base_block(mud::Material* self) {
		static mud::BaseMaterialBlock temp;
		return (temp = self->m_base_block, &temp);
	}
	void DECL mud_Material__set_base_block(mud::Material* self, mud::BaseMaterialBlock* value) {
		self->m_base_block = *value;
	}
	mud::UnshadedMaterialBlock* DECL mud_Material__get_unshaded_block(mud::Material* self) {
		static mud::UnshadedMaterialBlock temp;
		return (temp = self->m_unshaded_block, &temp);
	}
	void DECL mud_Material__set_unshaded_block(mud::Material* self, mud::UnshadedMaterialBlock* value) {
		self->m_unshaded_block = *value;
	}
	mud::PbrMaterialBlock* DECL mud_Material__get_pbr_block(mud::Material* self) {
		static mud::PbrMaterialBlock temp;
		return (temp = self->m_pbr_block, &temp);
	}
	void DECL mud_Material__set_pbr_block(mud::Material* self, mud::PbrMaterialBlock* value) {
		self->m_pbr_block = *value;
	}
	mud::FresnelMaterialBlock* DECL mud_Material__get_fresnel_block(mud::Material* self) {
		static mud::FresnelMaterialBlock temp;
		return (temp = self->m_fresnel_block, &temp);
	}
	void DECL mud_Material__set_fresnel_block(mud::Material* self, mud::FresnelMaterialBlock* value) {
		self->m_fresnel_block = *value;
	}
	void DECL mud_Material__destroy(mud::Material* self) {
		delete self;
	}
	// Mesh
	const char* DECL mud_Mesh__get_name(mud::Mesh* self) {
		return self->m_name.c_str();
	}
	void DECL mud_Mesh__set_name(mud::Mesh* self, const char* value) {
		self->m_name = value;
	}
	uint16_t DECL mud_Mesh__get_index(mud::Mesh* self) {
		return self->m_index;
	}
	void DECL mud_Mesh__set_index(mud::Mesh* self, uint16_t value) {
		self->m_index = value;
	}
	mud::DrawMode DECL mud_Mesh__get_draw_mode(mud::Mesh* self) {
		return self->m_draw_mode;
	}
	void DECL mud_Mesh__set_draw_mode(mud::Mesh* self, mud::DrawMode value) {
		self->m_draw_mode = value;
	}
	mud::Aabb* DECL mud_Mesh__get_aabb(mud::Mesh* self) {
		static mud::Aabb temp;
		return (temp = self->m_aabb, &temp);
	}
	void DECL mud_Mesh__set_aabb(mud::Mesh* self, mud::Aabb* value) {
		self->m_aabb = *value;
	}
	float DECL mud_Mesh__get_radius(mud::Mesh* self) {
		return self->m_radius;
	}
	void DECL mud_Mesh__set_radius(mud::Mesh* self, float value) {
		self->m_radius = value;
	}
	mud::vec3* DECL mud_Mesh__get_origin(mud::Mesh* self) {
		static mud::vec3 temp;
		return (temp = self->m_origin, &temp);
	}
	void DECL mud_Mesh__set_origin(mud::Mesh* self, mud::vec3* value) {
		self->m_origin = *value;
	}
	bool DECL mud_Mesh__get_readback(mud::Mesh* self) {
		return self->m_readback;
	}
	void DECL mud_Mesh__set_readback(mud::Mesh* self, bool value) {
		self->m_readback = value;
	}
	uint32_t DECL mud_Mesh__get_vertex_format(mud::Mesh* self) {
		return self->m_vertex_format;
	}
	void DECL mud_Mesh__set_vertex_format(mud::Mesh* self, uint32_t value) {
		self->m_vertex_format = value;
	}
	bool DECL mud_Mesh__get_qnormals(mud::Mesh* self) {
		return self->m_qnormals;
	}
	void DECL mud_Mesh__set_qnormals(mud::Mesh* self, bool value) {
		self->m_qnormals = value;
	}
	uint32_t DECL mud_Mesh__get_vertex_count(mud::Mesh* self) {
		return self->m_vertex_count;
	}
	void DECL mud_Mesh__set_vertex_count(mud::Mesh* self, uint32_t value) {
		self->m_vertex_count = value;
	}
	uint32_t DECL mud_Mesh__get_index_count(mud::Mesh* self) {
		return self->m_index_count;
	}
	void DECL mud_Mesh__set_index_count(mud::Mesh* self, uint32_t value) {
		self->m_index_count = value;
	}
	bool DECL mud_Mesh__get_index32(mud::Mesh* self) {
		return self->m_index32;
	}
	void DECL mud_Mesh__set_index32(mud::Mesh* self, bool value) {
		self->m_index32 = value;
	}
	mud::Material* DECL mud_Mesh__get_material(mud::Mesh* self) {
		return self->m_material;
	}
	void DECL mud_Mesh__set_material(mud::Mesh* self, mud::Material* value) {
		self->m_material = value;
	}
	void DECL mud_Mesh__destroy(mud::Mesh* self) {
		delete self;
	}
	// Model
	const char* DECL mud_Model__get_name(mud::Model* self) {
		return self->m_name.c_str();
	}
	void DECL mud_Model__set_name(mud::Model* self, const char* value) {
		self->m_name = value;
	}
	uint16_t DECL mud_Model__get_index(mud::Model* self) {
		return self->m_index;
	}
	void DECL mud_Model__set_index(mud::Model* self, uint16_t value) {
		self->m_index = value;
	}
	mud::Aabb* DECL mud_Model__get_aabb(mud::Model* self) {
		static mud::Aabb temp;
		return (temp = self->m_aabb, &temp);
	}
	void DECL mud_Model__set_aabb(mud::Model* self, mud::Aabb* value) {
		self->m_aabb = *value;
	}
	float DECL mud_Model__get_radius(mud::Model* self) {
		return self->m_radius;
	}
	void DECL mud_Model__set_radius(mud::Model* self, float value) {
		self->m_radius = value;
	}
	mud::vec3* DECL mud_Model__get_origin(mud::Model* self) {
		static mud::vec3 temp;
		return (temp = self->m_origin, &temp);
	}
	void DECL mud_Model__set_origin(mud::Model* self, mud::vec3* value) {
		self->m_origin = *value;
	}
	void DECL mud_Model__destroy(mud::Model* self) {
		delete self;
	}
	// ModelItem
	mud::ModelItem* DECL mud_ModelItem_ModelItem_0() {
		return new mud::ModelItem();
	}
	size_t DECL mud_ModelItem__get_index(mud::ModelItem* self) {
		return self->m_index;
	}
	void DECL mud_ModelItem__set_index(mud::ModelItem* self, size_t value) {
		self->m_index = value;
	}
	mud::Mesh* DECL mud_ModelItem__get_mesh(mud::ModelItem* self) {
		return self->m_mesh;
	}
	void DECL mud_ModelItem__set_mesh(mud::ModelItem* self, mud::Mesh* value) {
		self->m_mesh = value;
	}
	bool DECL mud_ModelItem__get_has_transform(mud::ModelItem* self) {
		return self->m_has_transform;
	}
	void DECL mud_ModelItem__set_has_transform(mud::ModelItem* self, bool value) {
		self->m_has_transform = value;
	}
	mud::mat4* DECL mud_ModelItem__get_transform(mud::ModelItem* self) {
		static mud::mat4 temp;
		return (temp = self->m_transform, &temp);
	}
	void DECL mud_ModelItem__set_transform(mud::ModelItem* self, mud::mat4* value) {
		self->m_transform = *value;
	}
	int DECL mud_ModelItem__get_skin(mud::ModelItem* self) {
		return self->m_skin;
	}
	void DECL mud_ModelItem__set_skin(mud::ModelItem* self, int value) {
		self->m_skin = value;
	}
	mud::Colour* DECL mud_ModelItem__get_colour(mud::ModelItem* self) {
		static mud::Colour temp;
		return (temp = self->m_colour, &temp);
	}
	void DECL mud_ModelItem__set_colour(mud::ModelItem* self, mud::Colour* value) {
		self->m_colour = *value;
	}
	mud::Material* DECL mud_ModelItem__get_material(mud::ModelItem* self) {
		return self->m_material;
	}
	void DECL mud_ModelItem__set_material(mud::ModelItem* self, mud::Material* value) {
		self->m_material = value;
	}
	void DECL mud_ModelItem__destroy(mud::ModelItem* self) {
		delete self;
	}
	// Node3
	mud::Scene* DECL mud_Node3__get_scene(mud::Node3* self) {
		return self->m_scene;
	}
	void DECL mud_Node3__set_scene(mud::Node3* self, mud::Scene* value) {
		self->m_scene = value;
	}
	uint16_t DECL mud_Node3__get_index(mud::Node3* self) {
		return self->m_index;
	}
	void DECL mud_Node3__set_index(mud::Node3* self, uint16_t value) {
		self->m_index = value;
	}
	mud::mat4* DECL mud_Node3__get_transform(mud::Node3* self) {
		static mud::mat4 temp;
		return (temp = self->m_transform, &temp);
	}
	void DECL mud_Node3__set_transform(mud::Node3* self, mud::mat4* value) {
		self->m_transform = *value;
	}
	bool DECL mud_Node3__get_visible(mud::Node3* self) {
		return self->m_visible;
	}
	void DECL mud_Node3__set_visible(mud::Node3* self, bool value) {
		self->m_visible = value;
	}
	void DECL mud_Node3__destroy(mud::Node3* self) {
		delete self;
	}
	// ParticleGenerator
	mud::ParticleGenerator* DECL mud_ParticleGenerator_ParticleGenerator_0() {
		return new mud::ParticleGenerator();
	}
	const char* DECL mud_ParticleGenerator__get_name(mud::ParticleGenerator* self) {
		return self->m_name.c_str();
	}
	void DECL mud_ParticleGenerator__set_name(mud::ParticleGenerator* self, const char* value) {
		self->m_name = value;
	}
	float DECL mud_ParticleGenerator__get_duration(mud::ParticleGenerator* self) {
		return self->m_duration;
	}
	void DECL mud_ParticleGenerator__set_duration(mud::ParticleGenerator* self, float value) {
		self->m_duration = value;
	}
	float DECL mud_ParticleGenerator__get_start_time(mud::ParticleGenerator* self) {
		return self->m_start_time;
	}
	void DECL mud_ParticleGenerator__set_start_time(mud::ParticleGenerator* self, float value) {
		self->m_start_time = value;
	}
	bool DECL mud_ParticleGenerator__get_loop(mud::ParticleGenerator* self) {
		return self->m_loop;
	}
	void DECL mud_ParticleGenerator__set_loop(mud::ParticleGenerator* self, bool value) {
		self->m_loop = value;
	}
	mud::ShapeVar* DECL mud_ParticleGenerator__get_shape(mud::ParticleGenerator* self) {
		static mud::ShapeVar temp;
		return (temp = self->m_shape, &temp);
	}
	void DECL mud_ParticleGenerator__set_shape(mud::ParticleGenerator* self, mud::ShapeVar* value) {
		self->m_shape = *value;
	}
	mud::EmitterFlow DECL mud_ParticleGenerator__get_flow(mud::ParticleGenerator* self) {
		return self->m_flow;
	}
	void DECL mud_ParticleGenerator__set_flow(mud::ParticleGenerator* self, mud::EmitterFlow value) {
		self->m_flow = value;
	}
	bool DECL mud_ParticleGenerator__get_billboard(mud::ParticleGenerator* self) {
		return self->m_billboard;
	}
	void DECL mud_ParticleGenerator__set_billboard(mud::ParticleGenerator* self, bool value) {
		self->m_billboard = value;
	}
	mud::vec3* DECL mud_ParticleGenerator__get_direction(mud::ParticleGenerator* self) {
		static mud::vec3 temp;
		return (temp = self->m_direction, &temp);
	}
	void DECL mud_ParticleGenerator__set_direction(mud::ParticleGenerator* self, mud::vec3* value) {
		self->m_direction = *value;
	}
	mud::quat* DECL mud_ParticleGenerator__get_rotation(mud::ParticleGenerator* self) {
		static mud::quat temp;
		return (temp = self->m_rotation, &temp);
	}
	void DECL mud_ParticleGenerator__set_rotation(mud::ParticleGenerator* self, mud::quat* value) {
		self->m_rotation = *value;
	}
	mud::BlendMode DECL mud_ParticleGenerator__get_blend_mode(mud::ParticleGenerator* self) {
		return self->m_blend_mode;
	}
	void DECL mud_ParticleGenerator__set_blend_mode(mud::ParticleGenerator* self, mud::BlendMode value) {
		self->m_blend_mode = value;
	}
	const char* DECL mud_ParticleGenerator__get_sprite_name(mud::ParticleGenerator* self) {
		return self->m_sprite_name.c_str();
	}
	void DECL mud_ParticleGenerator__set_sprite_name(mud::ParticleGenerator* self, const char* value) {
		self->m_sprite_name = value;
	}
	void DECL mud_ParticleGenerator__destroy(mud::ParticleGenerator* self) {
		delete self;
	}
	// PbrMaterialBlock
	mud::PbrMaterialBlock* DECL mud_PbrMaterialBlock_PbrMaterialBlock_0() {
		return new mud::PbrMaterialBlock();
	}
	mud::PbrMaterialBlock* DECL mud_PbrMaterialBlock_PbrMaterialBlock_1(const mud::Colour* albedo) {
		return new mud::PbrMaterialBlock(*albedo);
	}
	mud::PbrMaterialBlock* DECL mud_PbrMaterialBlock_PbrMaterialBlock_2(const mud::Colour* albedo, float metallic) {
		return new mud::PbrMaterialBlock(*albedo, metallic);
	}
	mud::PbrMaterialBlock* DECL mud_PbrMaterialBlock_PbrMaterialBlock_3(const mud::Colour* albedo, float metallic, float roughness) {
		return new mud::PbrMaterialBlock(*albedo, metallic, roughness);
	}
	bool DECL mud_PbrMaterialBlock__get_enabled(mud::PbrMaterialBlock* self) {
		return self->m_enabled;
	}
	void DECL mud_PbrMaterialBlock__set_enabled(mud::PbrMaterialBlock* self, bool value) {
		self->m_enabled = value;
	}
	float DECL mud_PbrMaterialBlock__get_specular(mud::PbrMaterialBlock* self) {
		return self->m_specular;
	}
	void DECL mud_PbrMaterialBlock__set_specular(mud::PbrMaterialBlock* self, float value) {
		self->m_specular = value;
	}
	float DECL mud_PbrMaterialBlock__get_emissive_energy(mud::PbrMaterialBlock* self) {
		return self->m_emissive_energy;
	}
	void DECL mud_PbrMaterialBlock__set_emissive_energy(mud::PbrMaterialBlock* self, float value) {
		self->m_emissive_energy = value;
	}
	float DECL mud_PbrMaterialBlock__get_ritint(mud::PbrMaterialBlock* self) {
		return self->m_rim_tint;
	}
	void DECL mud_PbrMaterialBlock__set_ritint(mud::PbrMaterialBlock* self, float value) {
		self->m_rim_tint = value;
	}
	float DECL mud_PbrMaterialBlock__get_clearcoat_gloss(mud::PbrMaterialBlock* self) {
		return self->m_clearcoat_gloss;
	}
	void DECL mud_PbrMaterialBlock__set_clearcoat_gloss(mud::PbrMaterialBlock* self, float value) {
		self->m_clearcoat_gloss = value;
	}
	bool DECL mud_PbrMaterialBlock__get_deep_parallax(mud::PbrMaterialBlock* self) {
		return self->m_deep_parallax;
	}
	void DECL mud_PbrMaterialBlock__set_deep_parallax(mud::PbrMaterialBlock* self, bool value) {
		self->m_deep_parallax = value;
	}
	mud::PbrDiffuseMode DECL mud_PbrMaterialBlock__get_diffuse_mode(mud::PbrMaterialBlock* self) {
		return self->m_diffuse_mode;
	}
	void DECL mud_PbrMaterialBlock__set_diffuse_mode(mud::PbrMaterialBlock* self, mud::PbrDiffuseMode value) {
		self->m_diffuse_mode = value;
	}
	mud::PbrSpecularMode DECL mud_PbrMaterialBlock__get_specular_mode(mud::PbrMaterialBlock* self) {
		return self->m_specular_mode;
	}
	void DECL mud_PbrMaterialBlock__set_specular_mode(mud::PbrMaterialBlock* self, mud::PbrSpecularMode value) {
		self->m_specular_mode = value;
	}
	void DECL mud_PbrMaterialBlock__destroy(mud::PbrMaterialBlock* self) {
		delete self;
	}
	// Prefab
	const char* DECL mud_Prefab__get_name(mud::Prefab* self) {
		return self->m_name.c_str();
	}
	void DECL mud_Prefab__set_name(mud::Prefab* self, const char* value) {
		self->m_name = value;
	}
	void DECL mud_Prefab__destroy(mud::Prefab* self) {
		delete self;
	}
	// Program
	const char* DECL mud_Program__get_name(mud::Program* self) {
		return self->name();
	}
	void DECL mud_Program__destroy(mud::Program* self) {
		delete self;
	}
	// Radiance
	mud::Radiance* DECL mud_Radiance_Radiance_0() {
		return new mud::Radiance();
	}
	float DECL mud_Radiance__get_energy(mud::Radiance* self) {
		return self->m_energy;
	}
	void DECL mud_Radiance__set_energy(mud::Radiance* self, float value) {
		self->m_energy = value;
	}
	float DECL mud_Radiance__get_ambient(mud::Radiance* self) {
		return self->m_ambient;
	}
	void DECL mud_Radiance__set_ambient(mud::Radiance* self, float value) {
		self->m_ambient = value;
	}
	mud::Colour* DECL mud_Radiance__get_colour(mud::Radiance* self) {
		static mud::Colour temp;
		return (temp = self->m_colour, &temp);
	}
	void DECL mud_Radiance__set_colour(mud::Radiance* self, mud::Colour* value) {
		self->m_colour = *value;
	}
	mud::Texture* DECL mud_Radiance__get_texture(mud::Radiance* self) {
		return self->m_texture;
	}
	void DECL mud_Radiance__set_texture(mud::Radiance* self, mud::Texture* value) {
		self->m_texture = value;
	}
	void DECL mud_Radiance__destroy(mud::Radiance* self) {
		delete self;
	}
	// RenderFrame
	mud::RenderFrame* DECL mud_RenderFrame_RenderFrame_0() {
		return new mud::RenderFrame();
	}
	void DECL mud_RenderFrame__destroy(mud::RenderFrame* self) {
		delete self;
	}
	// RenderQuad
	mud::RenderQuad* DECL mud_RenderQuad_RenderQuad_0() {
		return new mud::RenderQuad();
	}
	void DECL mud_RenderQuad__destroy(mud::RenderQuad* self) {
		delete self;
	}
	// Rig
	void DECL mud_Rig__destroy(mud::Rig* self) {
		delete self;
	}
	// Scene
	mud::Gnode* DECL mud_Scene_begin_0(mud::Scene* self) {
		return &self->begin();
	}
	mud::Gnode* DECL mud_Scene__get_graph(mud::Scene* self) {
		return &self->m_graph;
	}
	mud::Node3* DECL mud_Scene__get_root_node(mud::Scene* self) {
		return &self->m_root_node;
	}
	mud::Environment* DECL mud_Scene__get_environment(mud::Scene* self) {
		static mud::Environment temp;
		return (temp = self->m_environment, &temp);
	}
	void DECL mud_Scene__set_environment(mud::Scene* self, mud::Environment* value) {
		self->m_environment = *value;
	}
	void DECL mud_Scene__destroy(mud::Scene* self) {
		delete self;
	}
	// Shot
	void DECL mud_Shot__destroy(mud::Shot* self) {
		delete self;
	}
	// Skeleton
	void DECL mud_Skeleton__destroy(mud::Skeleton* self) {
		delete self;
	}
	// Skin
	void DECL mud_Skin__destroy(mud::Skin* self) {
		delete self;
	}
	// Sun
	mud::Sun* DECL mud_Sun_Sun_0() {
		return new mud::Sun();
	}
	float DECL mud_Sun__get_azimuth(mud::Sun* self) {
		return self->azimuth;
	}
	void DECL mud_Sun__set_azimuth(mud::Sun* self, float value) {
		self->azimuth = value;
	}
	float DECL mud_Sun__get_elevation(mud::Sun* self) {
		return self->elevation;
	}
	void DECL mud_Sun__set_elevation(mud::Sun* self, float value) {
		self->elevation = value;
	}
	mud::Colour* DECL mud_Sun__get_colour(mud::Sun* self) {
		static mud::Colour temp;
		return (temp = self->m_colour, &temp);
	}
	void DECL mud_Sun__set_colour(mud::Sun* self, mud::Colour* value) {
		self->m_colour = *value;
	}
	float DECL mud_Sun__get_intensity(mud::Sun* self) {
		return self->m_intensity;
	}
	void DECL mud_Sun__set_intensity(mud::Sun* self, float value) {
		self->m_intensity = value;
	}
	void DECL mud_Sun__destroy(mud::Sun* self) {
		delete self;
	}
	// SymbolIndex
	void DECL mud_SymbolIndex__destroy(mud::SymbolIndex* self) {
		delete self;
	}
	// Texture
	uint16_t DECL mud_Texture__get_width(mud::Texture* self) {
		return self->m_width;
	}
	void DECL mud_Texture__set_width(mud::Texture* self, uint16_t value) {
		self->m_width = value;
	}
	uint16_t DECL mud_Texture__get_height(mud::Texture* self) {
		return self->m_height;
	}
	void DECL mud_Texture__set_height(mud::Texture* self, uint16_t value) {
		self->m_height = value;
	}
	uint32_t DECL mud_Texture__get_bits_per_pixel(mud::Texture* self) {
		return self->m_bits_per_pixel;
	}
	void DECL mud_Texture__set_bits_per_pixel(mud::Texture* self, uint32_t value) {
		self->m_bits_per_pixel = value;
	}
	void DECL mud_Texture__destroy(mud::Texture* self) {
		delete self;
	}
	// UnshadedMaterialBlock
	mud::UnshadedMaterialBlock* DECL mud_UnshadedMaterialBlock_UnshadedMaterialBlock_0() {
		return new mud::UnshadedMaterialBlock();
	}
	bool DECL mud_UnshadedMaterialBlock__get_enabled(mud::UnshadedMaterialBlock* self) {
		return self->m_enabled;
	}
	void DECL mud_UnshadedMaterialBlock__set_enabled(mud::UnshadedMaterialBlock* self, bool value) {
		self->m_enabled = value;
	}
	void DECL mud_UnshadedMaterialBlock__destroy(mud::UnshadedMaterialBlock* self) {
		delete self;
	}
	// Viewport
	mud::Camera* DECL mud_Viewport__get_camera(mud::Viewport* self) {
		return self->m_camera;
	}
	void DECL mud_Viewport__set_camera(mud::Viewport* self, mud::Camera* value) {
		self->m_camera = value;
	}
	mud::Scene* DECL mud_Viewport__get_scene(mud::Viewport* self) {
		return self->m_scene;
	}
	void DECL mud_Viewport__set_scene(mud::Viewport* self, mud::Scene* value) {
		self->m_scene = value;
	}
	uint16_t DECL mud_Viewport__get_index(mud::Viewport* self) {
		return self->m_index;
	}
	void DECL mud_Viewport__set_index(mud::Viewport* self, uint16_t value) {
		self->m_index = value;
	}
	bool DECL mud_Viewport__get_active(mud::Viewport* self) {
		return self->m_active;
	}
	void DECL mud_Viewport__set_active(mud::Viewport* self, bool value) {
		self->m_active = value;
	}
	mud::uvec4* DECL mud_Viewport__get_rect(mud::Viewport* self) {
		static mud::uvec4 temp;
		return (temp = self->m_rect, &temp);
	}
	void DECL mud_Viewport__set_rect(mud::Viewport* self, mud::uvec4* value) {
		self->m_rect = *value;
	}
	bool DECL mud_Viewport__get_scissor(mud::Viewport* self) {
		return self->m_scissor;
	}
	void DECL mud_Viewport__set_scissor(mud::Viewport* self, bool value) {
		self->m_scissor = value;
	}
	mud::Colour* DECL mud_Viewport__get_clear_colour(mud::Viewport* self) {
		static mud::Colour temp;
		return (temp = self->m_clear_colour, &temp);
	}
	void DECL mud_Viewport__set_clear_colour(mud::Viewport* self, mud::Colour* value) {
		self->m_clear_colour = *value;
	}
	mud::Shading DECL mud_Viewport__get_shading(mud::Viewport* self) {
		return self->m_shading;
	}
	void DECL mud_Viewport__set_shading(mud::Viewport* self, mud::Shading value) {
		self->m_shading = value;
	}
	mud::Lighting DECL mud_Viewport__get_lighting(mud::Viewport* self) {
		return self->m_lighting;
	}
	void DECL mud_Viewport__set_lighting(mud::Viewport* self, mud::Lighting value) {
		self->m_lighting = value;
	}
	void DECL mud_Viewport__destroy(mud::Viewport* self) {
		delete self;
	}
	// BlockCopy
	void DECL mud_BlockCopy__destroy(mud::BlockCopy* self) {
		delete self;
	}
	// DrawBlock
	void DECL mud_DrawBlock__destroy(mud::DrawBlock* self) {
		delete self;
	}
	// BlockDepth
	void DECL mud_BlockDepth__destroy(mud::BlockDepth* self) {
		delete self;
	}
	// BlockFilter
	void DECL mud_BlockFilter__destroy(mud::BlockFilter* self) {
		delete self;
	}
	// BlockParticles
	void DECL mud_BlockParticles__destroy(mud::BlockParticles* self) {
		delete self;
	}
	// BlockResolve
	void DECL mud_BlockResolve__destroy(mud::BlockResolve* self) {
		delete self;
	}
	// BlockSky
	void DECL mud_BlockSky__destroy(mud::BlockSky* self) {
		delete self;
	}
	// ClusteredFrustum
	mud::ClusteredFrustum* DECL mud_ClusteredFrustum_ClusteredFrustum_0() {
		return new mud::ClusteredFrustum();
	}
	void DECL mud_ClusteredFrustum__destroy(mud::ClusteredFrustum* self) {
		delete self;
	}
	// Particles
	mud::Particles* DECL mud_Particles_Particles_0() {
		return new mud::Particles();
	}
	mud::Node3* DECL mud_Particles__get_node(mud::Particles* self) {
		return self->m_node;
	}
	void DECL mud_Particles__set_node(mud::Particles* self, mud::Node3* value) {
		self->m_node = value;
	}
	void DECL mud_Particles__destroy(mud::Particles* self) {
		delete self;
	}
	// RenderTarget
	void DECL mud_RenderTarget__destroy(mud::RenderTarget* self) {
		delete self;
	}
	// AnimationTarget
	mud::AnimationTarget DECL mud_AnimationTarget_Position() {
		return mud::AnimationTarget::Position;
	}
	mud::AnimationTarget DECL mud_AnimationTarget_Rotation() {
		return mud::AnimationTarget::Rotation;
	}
	mud::AnimationTarget DECL mud_AnimationTarget_Scale() {
		return mud::AnimationTarget::Scale;
	}
	// BackgroundMode
	mud::BackgroundMode DECL mud_BackgroundMode_None() {
		return mud::BackgroundMode::None;
	}
	mud::BackgroundMode DECL mud_BackgroundMode_Panorama() {
		return mud::BackgroundMode::Panorama;
	}
	mud::BackgroundMode DECL mud_BackgroundMode_Radiance() {
		return mud::BackgroundMode::Radiance;
	}
	mud::BackgroundMode DECL mud_BackgroundMode_Custom() {
		return mud::BackgroundMode::Custom;
	}
	// BlendMode
	mud::BlendMode DECL mud_BlendMode_Mix() {
		return mud::BlendMode::Mix;
	}
	mud::BlendMode DECL mud_BlendMode_Add() {
		return mud::BlendMode::Add;
	}
	mud::BlendMode DECL mud_BlendMode_Sub() {
		return mud::BlendMode::Sub;
	}
	mud::BlendMode DECL mud_BlendMode_Mul() {
		return mud::BlendMode::Mul;
	}
	mud::BlendMode DECL mud_BlendMode_Normal() {
		return mud::BlendMode::Normal;
	}
	mud::BlendMode DECL mud_BlendMode_Alpha() {
		return mud::BlendMode::Alpha;
	}
	// CullMode
	mud::CullMode DECL mud_CullMode_None() {
		return mud::CullMode::None;
	}
	mud::CullMode DECL mud_CullMode_Front() {
		return mud::CullMode::Front;
	}
	mud::CullMode DECL mud_CullMode_Back() {
		return mud::CullMode::Back;
	}
	// DepthDraw
	mud::DepthDraw DECL mud_DepthDraw_Enabled() {
		return mud::DepthDraw::Enabled;
	}
	mud::DepthDraw DECL mud_DepthDraw_Disabled() {
		return mud::DepthDraw::Disabled;
	}
	// DepthTest
	mud::DepthTest DECL mud_DepthTest_Enabled() {
		return mud::DepthTest::Enabled;
	}
	mud::DepthTest DECL mud_DepthTest_Disabled() {
		return mud::DepthTest::Disabled;
	}
	// EmitterFlow
	mud::EmitterFlow DECL mud_EmitterFlow_Outward() {
		return mud::EmitterFlow::Outward;
	}
	mud::EmitterFlow DECL mud_EmitterFlow_Absolute() {
		return mud::EmitterFlow::Absolute;
	}
	// Interpolation
	mud::Interpolation DECL mud_Interpolation_Nearest() {
		return mud::Interpolation::Nearest;
	}
	mud::Interpolation DECL mud_Interpolation_Linear() {
		return mud::Interpolation::Linear;
	}
	mud::Interpolation DECL mud_Interpolation_Cubic() {
		return mud::Interpolation::Cubic;
	}
	// IsometricAngle
	mud::IsometricAngle DECL mud_IsometricAngle_NORTH() {
		return mud::NORTH;
	}
	mud::IsometricAngle DECL mud_IsometricAngle_SOUTH() {
		return mud::SOUTH;
	}
	mud::IsometricAngle DECL mud_IsometricAngle_EAST() {
		return mud::EAST;
	}
	mud::IsometricAngle DECL mud_IsometricAngle_WEST() {
		return mud::WEST;
	}
	// ItemShadow
	mud::ItemShadow DECL mud_ItemShadow_Default() {
		return mud::ItemShadow::Default;
	}
	mud::ItemShadow DECL mud_ItemShadow_DoubleSided() {
		return mud::ItemShadow::DoubleSided;
	}
	// LightType
	mud::LightType DECL mud_LightType_Direct() {
		return mud::LightType::Direct;
	}
	mud::LightType DECL mud_LightType_Point() {
		return mud::LightType::Point;
	}
	mud::LightType DECL mud_LightType_Spot() {
		return mud::LightType::Spot;
	}
	mud::LightType DECL mud_LightType_Count() {
		return mud::LightType::Count;
	}
	// Lighting
	mud::Lighting DECL mud_Lighting_None() {
		return mud::Lighting::None;
	}
	mud::Lighting DECL mud_Lighting_Clustered() {
		return mud::Lighting::Clustered;
	}
	mud::Lighting DECL mud_Lighting_Deferred() {
		return mud::Lighting::Deferred;
	}
	mud::Lighting DECL mud_Lighting_VoxelGI() {
		return mud::Lighting::VoxelGI;
	}
	// MSAA
	mud::MSAA DECL mud_MSAA_Disabled() {
		return mud::MSAA::Disabled;
	}
	mud::MSAA DECL mud_MSAA_X2() {
		return mud::MSAA::X2;
	}
	mud::MSAA DECL mud_MSAA_X4() {
		return mud::MSAA::X4;
	}
	mud::MSAA DECL mud_MSAA_X8() {
		return mud::MSAA::X8;
	}
	mud::MSAA DECL mud_MSAA_X16() {
		return mud::MSAA::X16;
	}
	// MaterialFlag
	mud::MaterialFlag DECL mud_MaterialFlag_TriplanarUV1() {
		return mud::MaterialFlag::TriplanarUV1;
	}
	mud::MaterialFlag DECL mud_MaterialFlag_TriplanarUV2() {
		return mud::MaterialFlag::TriplanarUV2;
	}
	mud::MaterialFlag DECL mud_MaterialFlag_Count() {
		return mud::MaterialFlag::Count;
	}
	// ModelFormat
	mud::ModelFormat DECL mud_ModelFormat_obj() {
		return mud::ModelFormat::obj;
	}
	mud::ModelFormat DECL mud_ModelFormat_gltf() {
		return mud::ModelFormat::gltf;
	}
	mud::ModelFormat DECL mud_ModelFormat_Count() {
		return mud::ModelFormat::Count;
	}
	// Month
	mud::Month DECL mud_Month_January() {
		return mud::Month::January;
	}
	mud::Month DECL mud_Month_February() {
		return mud::Month::February;
	}
	mud::Month DECL mud_Month_March() {
		return mud::Month::March;
	}
	mud::Month DECL mud_Month_April() {
		return mud::Month::April;
	}
	mud::Month DECL mud_Month_May() {
		return mud::Month::May;
	}
	mud::Month DECL mud_Month_June() {
		return mud::Month::June;
	}
	mud::Month DECL mud_Month_July() {
		return mud::Month::July;
	}
	mud::Month DECL mud_Month_August() {
		return mud::Month::August;
	}
	mud::Month DECL mud_Month_September() {
		return mud::Month::September;
	}
	mud::Month DECL mud_Month_October() {
		return mud::Month::October;
	}
	mud::Month DECL mud_Month_November() {
		return mud::Month::November;
	}
	mud::Month DECL mud_Month_December() {
		return mud::Month::December;
	}
	// PbrDiffuseMode
	mud::PbrDiffuseMode DECL mud_PbrDiffuseMode_Lambert() {
		return mud::PbrDiffuseMode::Lambert;
	}
	mud::PbrDiffuseMode DECL mud_PbrDiffuseMode_LambertHalf() {
		return mud::PbrDiffuseMode::LambertHalf;
	}
	mud::PbrDiffuseMode DECL mud_PbrDiffuseMode_OrenNayar() {
		return mud::PbrDiffuseMode::OrenNayar;
	}
	mud::PbrDiffuseMode DECL mud_PbrDiffuseMode_Burley() {
		return mud::PbrDiffuseMode::Burley;
	}
	mud::PbrDiffuseMode DECL mud_PbrDiffuseMode_Toon() {
		return mud::PbrDiffuseMode::Toon;
	}
	// PbrSpecularMode
	mud::PbrSpecularMode DECL mud_PbrSpecularMode_SchlickGGX() {
		return mud::PbrSpecularMode::SchlickGGX;
	}
	mud::PbrSpecularMode DECL mud_PbrSpecularMode_Blinn() {
		return mud::PbrSpecularMode::Blinn;
	}
	mud::PbrSpecularMode DECL mud_PbrSpecularMode_Phong() {
		return mud::PbrSpecularMode::Phong;
	}
	mud::PbrSpecularMode DECL mud_PbrSpecularMode_Toon() {
		return mud::PbrSpecularMode::Toon;
	}
	mud::PbrSpecularMode DECL mud_PbrSpecularMode_Disabled() {
		return mud::PbrSpecularMode::Disabled;
	}
	// ShaderType
	mud::ShaderType DECL mud_ShaderType_Compute() {
		return mud::ShaderType::Compute;
	}
	mud::ShaderType DECL mud_ShaderType_Fragment() {
		return mud::ShaderType::Fragment;
	}
	mud::ShaderType DECL mud_ShaderType_Geometry() {
		return mud::ShaderType::Geometry;
	}
	mud::ShaderType DECL mud_ShaderType_Vertex() {
		return mud::ShaderType::Vertex;
	}
	mud::ShaderType DECL mud_ShaderType_Count() {
		return mud::ShaderType::Count;
	}
	// Shading
	mud::Shading DECL mud_Shading_Wireframe() {
		return mud::Shading::Wireframe;
	}
	mud::Shading DECL mud_Shading_Unshaded() {
		return mud::Shading::Unshaded;
	}
	mud::Shading DECL mud_Shading_Shaded() {
		return mud::Shading::Shaded;
	}
	mud::Shading DECL mud_Shading_Volume() {
		return mud::Shading::Volume;
	}
	mud::Shading DECL mud_Shading_Voxels() {
		return mud::Shading::Voxels;
	}
	mud::Shading DECL mud_Shading_Lightmap() {
		return mud::Shading::Lightmap;
	}
	mud::Shading DECL mud_Shading_Clear() {
		return mud::Shading::Clear;
	}
	mud::Shading DECL mud_Shading_Count() {
		return mud::Shading::Count;
	}
	// ShadowFlags
	mud::ShadowFlags DECL mud_ShadowFlags_CSM_Stabilize() {
		return mud::CSM_Stabilize;
	}
	mud::ShadowFlags DECL mud_ShadowFlags_CSM_Optimize() {
		return mud::CSM_Optimize;
	}
	mud::ShadowFlags DECL mud_ShadowFlags_CSM_BlendSplits() {
		return mud::CSM_BlendSplits;
	}
	// TextureChannel
	mud::TextureChannel DECL mud_TextureChannel_Red() {
		return mud::TextureChannel::Red;
	}
	mud::TextureChannel DECL mud_TextureChannel_Green() {
		return mud::TextureChannel::Green;
	}
	mud::TextureChannel DECL mud_TextureChannel_Blue() {
		return mud::TextureChannel::Blue;
	}
	mud::TextureChannel DECL mud_TextureChannel_Alpha() {
		return mud::TextureChannel::Alpha;
	}
	mud::TextureChannel DECL mud_TextureChannel_All() {
		return mud::TextureChannel::All;
	}
	// TextureHint
	mud::TextureHint DECL mud_TextureHint_Black() {
		return mud::TextureHint::Black;
	}
	mud::TextureHint DECL mud_TextureHint_White() {
		return mud::TextureHint::White;
	}
	mud::TextureHint DECL mud_TextureHint_Normal() {
		return mud::TextureHint::Normal;
	}
	// TextureSampler
	mud::TextureSampler DECL mud_TextureSampler_Source0() {
		return mud::TextureSampler::Source0;
	}
	mud::TextureSampler DECL mud_TextureSampler_Source1() {
		return mud::TextureSampler::Source1;
	}
	mud::TextureSampler DECL mud_TextureSampler_Source2() {
		return mud::TextureSampler::Source2;
	}
	mud::TextureSampler DECL mud_TextureSampler_Source3() {
		return mud::TextureSampler::Source3;
	}
	mud::TextureSampler DECL mud_TextureSampler_SourceDepth() {
		return mud::TextureSampler::SourceDepth;
	}
	mud::TextureSampler DECL mud_TextureSampler_Color() {
		return mud::TextureSampler::Color;
	}
	mud::TextureSampler DECL mud_TextureSampler_Albedo() {
		return mud::TextureSampler::Albedo;
	}
	mud::TextureSampler DECL mud_TextureSampler_Metallic() {
		return mud::TextureSampler::Metallic;
	}
	mud::TextureSampler DECL mud_TextureSampler_Roughness() {
		return mud::TextureSampler::Roughness;
	}
	mud::TextureSampler DECL mud_TextureSampler_Emissive() {
		return mud::TextureSampler::Emissive;
	}
	mud::TextureSampler DECL mud_TextureSampler_Normal() {
		return mud::TextureSampler::Normal;
	}
	mud::TextureSampler DECL mud_TextureSampler_AO() {
		return mud::TextureSampler::AO;
	}
	mud::TextureSampler DECL mud_TextureSampler_Depth() {
		return mud::TextureSampler::Depth;
	}
	mud::TextureSampler DECL mud_TextureSampler_Skeleton() {
		return mud::TextureSampler::Skeleton;
	}
	mud::TextureSampler DECL mud_TextureSampler_ShadowCSM() {
		return mud::TextureSampler::ShadowCSM;
	}
	mud::TextureSampler DECL mud_TextureSampler_ShadowAtlas() {
		return mud::TextureSampler::ShadowAtlas;
	}
	mud::TextureSampler DECL mud_TextureSampler_Radiance() {
		return mud::TextureSampler::Radiance;
	}
	mud::TextureSampler DECL mud_TextureSampler_ReflectionProbe() {
		return mud::TextureSampler::ReflectionProbe;
	}
	mud::TextureSampler DECL mud_TextureSampler_GIProbe() {
		return mud::TextureSampler::GIProbe;
	}
	mud::TextureSampler DECL mud_TextureSampler_Lights() {
		return mud::TextureSampler::Lights;
	}
	mud::TextureSampler DECL mud_TextureSampler_Clusters() {
		return mud::TextureSampler::Clusters;
	}
	mud::TextureSampler DECL mud_TextureSampler_LightRecords() {
		return mud::TextureSampler::LightRecords;
	}
	mud::TextureSampler DECL mud_TextureSampler_Lightmap() {
		return mud::TextureSampler::Lightmap;
	}
	
}


