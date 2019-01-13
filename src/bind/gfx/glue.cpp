#include <infra/Api.h>
#include <jobs/Api.h>
#include <type/Api.h>
#include <pool/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <ctx/Api.h>
#include <bgfx/Api.h>
#include <gfx/Api.h>
#include <emscripten.h>
#include <cstdint>


extern "C" {
	
	// Animated
	void EMSCRIPTEN_KEEPALIVE mud_Animated_advance_1(mud::Animated* self, float time) {
		self->advance(time);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Animated_next_animation_0(mud::Animated* self) {
		self->next_animation();
	}
	void EMSCRIPTEN_KEEPALIVE mud_Animated_pause_0(mud::Animated* self) {
		self->pause();
	}
	void EMSCRIPTEN_KEEPALIVE mud_Animated_play_2(mud::Animated* self, const mud::Animation* animation, bool loop) {
		self->play(*animation, loop);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Animated_play_3(mud::Animated* self, const mud::Animation* animation, bool loop, float blend) {
		self->play(*animation, loop, blend);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Animated_play_4(mud::Animated* self, const mud::Animation* animation, bool loop, float blend, float speed) {
		self->play(*animation, loop, blend, speed);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Animated_play_5(mud::Animated* self, const mud::Animation* animation, bool loop, float blend, float speed, bool transient) {
		self->play(*animation, loop, blend, speed, transient);
	}
	const char* EMSCRIPTEN_KEEPALIVE mud_Animated_playing_0(mud::Animated* self) {
		return self->playing().c_str();
	}
	void EMSCRIPTEN_KEEPALIVE mud_Animated_seek_1(mud::Animated* self, float time) {
		self->seek(time);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Animated_start_2(mud::Animated* self, const char* animation, bool loop) {
		self->start(animation, loop);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Animated_start_3(mud::Animated* self, const char* animation, bool loop, float blend) {
		self->start(animation, loop, blend);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Animated_start_4(mud::Animated* self, const char* animation, bool loop, float blend, float speed) {
		self->start(animation, loop, blend, speed);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Animated_start_5(mud::Animated* self, const char* animation, bool loop, float blend, float speed, bool transient) {
		self->start(animation, loop, blend, speed, transient);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Animated_stop_0(mud::Animated* self) {
		self->stop();
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Animated_get_active(mud::Animated* self) {
		return self->m_active;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Animated_set_active(mud::Animated* self, bool value) {
		self->m_active = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Animated_get_speed_scale(mud::Animated* self) {
		return self->m_speed_scale;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Animated_set_speed_scale(mud::Animated* self, float value) {
		self->m_speed_scale = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Animated_get_default_blend_time(mud::Animated* self) {
		return self->m_default_blend_time;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Animated_set_default_blend_time(mud::Animated* self, float value) {
		self->m_default_blend_time = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Animated___destroy__(mud::Animated* self) {
		delete self;
	}
	// AnimatedTrack
	mud::AnimatedTrack* EMSCRIPTEN_KEEPALIVE mud_AnimatedTrack_AnimatedTrack_0() {
		return new mud::AnimatedTrack();
	}
	void EMSCRIPTEN_KEEPALIVE mud_AnimatedTrack___destroy__(mud::AnimatedTrack* self) {
		delete self;
	}
	// Animation
	const char* EMSCRIPTEN_KEEPALIVE mud_Animation_get_name(mud::Animation* self) {
		return self->m_name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE mud_Animation_set_name(mud::Animation* self, const char* value) {
		self->m_name = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Animation_get_length(mud::Animation* self) {
		return self->m_length;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Animation_set_length(mud::Animation* self, float value) {
		self->m_length = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Animation_get_step(mud::Animation* self) {
		return self->m_step;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Animation_set_step(mud::Animation* self, float value) {
		self->m_step = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Animation___destroy__(mud::Animation* self) {
		delete self;
	}
	// AnimationPlay
	mud::AnimationPlay* EMSCRIPTEN_KEEPALIVE mud_AnimationPlay_AnimationPlay_0() {
		return new mud::AnimationPlay();
	}
	const mud::Animation* EMSCRIPTEN_KEEPALIVE mud_AnimationPlay_get_animation(mud::AnimationPlay* self) {
		return self->m_animation;
	}
	void EMSCRIPTEN_KEEPALIVE mud_AnimationPlay_set_animation(mud::AnimationPlay* self, const mud::Animation* value) {
		self->m_animation = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_AnimationPlay_get_loop(mud::AnimationPlay* self) {
		return self->m_loop;
	}
	void EMSCRIPTEN_KEEPALIVE mud_AnimationPlay_set_loop(mud::AnimationPlay* self, bool value) {
		self->m_loop = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_AnimationPlay_get_speed(mud::AnimationPlay* self) {
		return self->m_speed;
	}
	void EMSCRIPTEN_KEEPALIVE mud_AnimationPlay_set_speed(mud::AnimationPlay* self, float value) {
		self->m_speed = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_AnimationPlay_get_transient(mud::AnimationPlay* self) {
		return self->m_transient;
	}
	void EMSCRIPTEN_KEEPALIVE mud_AnimationPlay_set_transient(mud::AnimationPlay* self, bool value) {
		self->m_transient = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_AnimationPlay_get_fadeout(mud::AnimationPlay* self) {
		return self->m_fadeout;
	}
	void EMSCRIPTEN_KEEPALIVE mud_AnimationPlay_set_fadeout(mud::AnimationPlay* self, float value) {
		self->m_fadeout = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_AnimationPlay_get_fadeout_left(mud::AnimationPlay* self) {
		return self->m_fadeout_left;
	}
	void EMSCRIPTEN_KEEPALIVE mud_AnimationPlay_set_fadeout_left(mud::AnimationPlay* self, float value) {
		self->m_fadeout_left = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_AnimationPlay_get_cursor(mud::AnimationPlay* self) {
		return self->m_cursor;
	}
	void EMSCRIPTEN_KEEPALIVE mud_AnimationPlay_set_cursor(mud::AnimationPlay* self, float value) {
		self->m_cursor = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_AnimationPlay_get_ended(mud::AnimationPlay* self) {
		return self->m_ended;
	}
	void EMSCRIPTEN_KEEPALIVE mud_AnimationPlay_set_ended(mud::AnimationPlay* self, bool value) {
		self->m_ended = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_AnimationPlay___destroy__(mud::AnimationPlay* self) {
		delete self;
	}
	// AnimationTrack
	mud::Animation* EMSCRIPTEN_KEEPALIVE mud_AnimationTrack_get_animation(mud::AnimationTrack* self) {
		return self->m_animation;
	}
	void EMSCRIPTEN_KEEPALIVE mud_AnimationTrack_set_animation(mud::AnimationTrack* self, mud::Animation* value) {
		self->m_animation = value;
	}
	size_t EMSCRIPTEN_KEEPALIVE mud_AnimationTrack_get_node(mud::AnimationTrack* self) {
		return self->m_node;
	}
	void EMSCRIPTEN_KEEPALIVE mud_AnimationTrack_set_node(mud::AnimationTrack* self, size_t value) {
		self->m_node = value;
	}
	const char* EMSCRIPTEN_KEEPALIVE mud_AnimationTrack_get_node_name(mud::AnimationTrack* self) {
		return self->m_node_name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE mud_AnimationTrack_set_node_name(mud::AnimationTrack* self, const char* value) {
		self->m_node_name = value;
	}
	mud::AnimationTarget EMSCRIPTEN_KEEPALIVE mud_AnimationTrack_get_target(mud::AnimationTrack* self) {
		return self->m_target;
	}
	void EMSCRIPTEN_KEEPALIVE mud_AnimationTrack_set_target(mud::AnimationTrack* self, mud::AnimationTarget value) {
		self->m_target = value;
	}
	mud::Type* EMSCRIPTEN_KEEPALIVE mud_AnimationTrack_get_value_type(mud::AnimationTrack* self) {
		return self->m_value_type;
	}
	void EMSCRIPTEN_KEEPALIVE mud_AnimationTrack_set_value_type(mud::AnimationTrack* self, mud::Type* value) {
		self->m_value_type = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_AnimationTrack_get_length(mud::AnimationTrack* self) {
		return self->m_length;
	}
	void EMSCRIPTEN_KEEPALIVE mud_AnimationTrack_set_length(mud::AnimationTrack* self, float value) {
		self->m_length = value;
	}
	mud::Interpolation EMSCRIPTEN_KEEPALIVE mud_AnimationTrack_get_interpolation(mud::AnimationTrack* self) {
		return self->m_interpolation;
	}
	void EMSCRIPTEN_KEEPALIVE mud_AnimationTrack_set_interpolation(mud::AnimationTrack* self, mud::Interpolation value) {
		self->m_interpolation = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_AnimationTrack___destroy__(mud::AnimationTrack* self) {
		delete self;
	}
	// Background
	mud::Background* EMSCRIPTEN_KEEPALIVE mud_Background_Background_0() {
		return new mud::Background();
	}
	mud::BackgroundMode EMSCRIPTEN_KEEPALIVE mud_Background_get_mode(mud::Background* self) {
		return self->m_mode;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Background_set_mode(mud::Background* self, mud::BackgroundMode value) {
		self->m_mode = value;
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE mud_Background_get_colour(mud::Background* self) {
		static mud::Colour temp;
		return (temp = self->m_colour, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Background_set_colour(mud::Background* self, mud::Colour* value) {
		self->m_colour = *value;
	}
	mud::Program* EMSCRIPTEN_KEEPALIVE mud_Background_get_custoprogram(mud::Background* self) {
		return self->m_custom_program;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Background_set_custoprogram(mud::Background* self, mud::Program* value) {
		self->m_custom_program = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Background___destroy__(mud::Background* self) {
		delete self;
	}
	// BaseMaterialBlock
	mud::BaseMaterialBlock* EMSCRIPTEN_KEEPALIVE mud_BaseMaterialBlock_BaseMaterialBlock_0() {
		return new mud::BaseMaterialBlock();
	}
	mud::BlendMode EMSCRIPTEN_KEEPALIVE mud_BaseMaterialBlock_get_blend_mode(mud::BaseMaterialBlock* self) {
		return self->m_blend_mode;
	}
	void EMSCRIPTEN_KEEPALIVE mud_BaseMaterialBlock_set_blend_mode(mud::BaseMaterialBlock* self, mud::BlendMode value) {
		self->m_blend_mode = value;
	}
	mud::CullMode EMSCRIPTEN_KEEPALIVE mud_BaseMaterialBlock_get_cull_mode(mud::BaseMaterialBlock* self) {
		return self->m_cull_mode;
	}
	void EMSCRIPTEN_KEEPALIVE mud_BaseMaterialBlock_set_cull_mode(mud::BaseMaterialBlock* self, mud::CullMode value) {
		self->m_cull_mode = value;
	}
	mud::DepthDraw EMSCRIPTEN_KEEPALIVE mud_BaseMaterialBlock_get_depth_draw_mode(mud::BaseMaterialBlock* self) {
		return self->m_depth_draw_mode;
	}
	void EMSCRIPTEN_KEEPALIVE mud_BaseMaterialBlock_set_depth_draw_mode(mud::BaseMaterialBlock* self, mud::DepthDraw value) {
		self->m_depth_draw_mode = value;
	}
	mud::DepthTest EMSCRIPTEN_KEEPALIVE mud_BaseMaterialBlock_get_depth_test(mud::BaseMaterialBlock* self) {
		return self->m_depth_test;
	}
	void EMSCRIPTEN_KEEPALIVE mud_BaseMaterialBlock_set_depth_test(mud::BaseMaterialBlock* self, mud::DepthTest value) {
		self->m_depth_test = value;
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE mud_BaseMaterialBlock_get_uv0_scale(mud::BaseMaterialBlock* self) {
		static mud::vec2 temp;
		return (temp = self->m_uv0_scale, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_BaseMaterialBlock_set_uv0_scale(mud::BaseMaterialBlock* self, mud::vec2* value) {
		self->m_uv0_scale = *value;
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE mud_BaseMaterialBlock_get_uv0_offset(mud::BaseMaterialBlock* self) {
		static mud::vec2 temp;
		return (temp = self->m_uv0_offset, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_BaseMaterialBlock_set_uv0_offset(mud::BaseMaterialBlock* self, mud::vec2* value) {
		self->m_uv0_offset = *value;
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE mud_BaseMaterialBlock_get_uv1_scale(mud::BaseMaterialBlock* self) {
		static mud::vec2 temp;
		return (temp = self->m_uv1_scale, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_BaseMaterialBlock_set_uv1_scale(mud::BaseMaterialBlock* self, mud::vec2* value) {
		self->m_uv1_scale = *value;
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE mud_BaseMaterialBlock_get_uv1_offset(mud::BaseMaterialBlock* self) {
		static mud::vec2 temp;
		return (temp = self->m_uv1_offset, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_BaseMaterialBlock_set_uv1_offset(mud::BaseMaterialBlock* self, mud::vec2* value) {
		self->m_uv1_offset = *value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_BaseMaterialBlock_get_is_alpha(mud::BaseMaterialBlock* self) {
		return self->m_is_alpha;
	}
	void EMSCRIPTEN_KEEPALIVE mud_BaseMaterialBlock_set_is_alpha(mud::BaseMaterialBlock* self, bool value) {
		self->m_is_alpha = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_BaseMaterialBlock_get_screen_filter(mud::BaseMaterialBlock* self) {
		return self->m_screen_filter;
	}
	void EMSCRIPTEN_KEEPALIVE mud_BaseMaterialBlock_set_screen_filter(mud::BaseMaterialBlock* self, bool value) {
		self->m_screen_filter = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_BaseMaterialBlock___destroy__(mud::BaseMaterialBlock* self) {
		delete self;
	}
	// Bone
	mud::Bone* EMSCRIPTEN_KEEPALIVE mud_Bone_Bone_0() {
		return new mud::Bone();
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE mud_Bone_get_position(mud::Bone* self) {
		static mud::vec3 temp;
		return (temp = self->m_position, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Bone_set_position(mud::Bone* self, mud::vec3* value) {
		self->m_position = *value;
	}
	mud::quat* EMSCRIPTEN_KEEPALIVE mud_Bone_get_rotation(mud::Bone* self) {
		static mud::quat temp;
		return (temp = self->m_rotation, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Bone_set_rotation(mud::Bone* self, mud::quat* value) {
		self->m_rotation = *value;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE mud_Bone_get_scale(mud::Bone* self) {
		static mud::vec3 temp;
		return (temp = self->m_scale, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Bone_set_scale(mud::Bone* self, mud::vec3* value) {
		self->m_scale = *value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Bone___destroy__(mud::Bone* self) {
		delete self;
	}
	// Camera
	mud::vec3* EMSCRIPTEN_KEEPALIVE mud_Camera_get_eye(mud::Camera* self) {
		static mud::vec3 temp;
		return (temp = self->m_eye, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Camera_set_eye(mud::Camera* self, mud::vec3* value) {
		self->m_eye = *value;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE mud_Camera_get_target(mud::Camera* self) {
		static mud::vec3 temp;
		return (temp = self->m_target, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Camera_set_target(mud::Camera* self, mud::vec3* value) {
		self->m_target = *value;
	}
	mud::mat4* EMSCRIPTEN_KEEPALIVE mud_Camera_get_transform(mud::Camera* self) {
		static mud::mat4 temp;
		return (temp = self->m_transform, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Camera_set_transform(mud::Camera* self, mud::mat4* value) {
		self->m_transform = *value;
	}
	mud::mat4* EMSCRIPTEN_KEEPALIVE mud_Camera_get_projection(mud::Camera* self) {
		static mud::mat4 temp;
		return (temp = self->m_projection, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Camera_set_projection(mud::Camera* self, mud::mat4* value) {
		self->m_projection = *value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Camera_get_fov(mud::Camera* self) {
		return self->m_fov;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Camera_set_fov(mud::Camera* self, float value) {
		self->m_fov = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Camera_get_aspect(mud::Camera* self) {
		return self->m_aspect;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Camera_set_aspect(mud::Camera* self, float value) {
		self->m_aspect = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Camera_get_near(mud::Camera* self) {
		return self->m_near;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Camera_set_near(mud::Camera* self, float value) {
		self->m_near = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Camera_get_far(mud::Camera* self) {
		return self->m_far;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Camera_set_far(mud::Camera* self, float value) {
		self->m_far = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Camera_get_orthographic(mud::Camera* self) {
		return self->m_orthographic;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Camera_set_orthographic(mud::Camera* self, bool value) {
		self->m_orthographic = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Camera_get_height(mud::Camera* self) {
		return self->m_height;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Camera_set_height(mud::Camera* self, float value) {
		self->m_height = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Camera_get_optimize_ends(mud::Camera* self) {
		return self->m_optimize_ends;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Camera_set_optimize_ends(mud::Camera* self, bool value) {
		self->m_optimize_ends = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Camera_get_clustered(mud::Camera* self) {
		return self->m_clustered;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Camera_set_clustered(mud::Camera* self, bool value) {
		self->m_clustered = value;
	}
	mud::vec4* EMSCRIPTEN_KEEPALIVE mud_Camera_get_lod_offsets(mud::Camera* self) {
		static mud::vec4 temp;
		return (temp = self->m_lod_offsets, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Camera_set_lod_offsets(mud::Camera* self, mud::vec4* value) {
		self->m_lod_offsets = *value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Camera___destroy__(mud::Camera* self) {
		delete self;
	}
	// Culler
	mud::Viewport* EMSCRIPTEN_KEEPALIVE mud_Culler_get_viewport(mud::Culler* self) {
		return self->m_viewport;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Culler_set_viewport(mud::Culler* self, mud::Viewport* value) {
		self->m_viewport = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Culler___destroy__(mud::Culler* self) {
		delete self;
	}
	// DepthParams
	mud::DepthParams* EMSCRIPTEN_KEEPALIVE mud_DepthParams_DepthParams_0() {
		return new mud::DepthParams();
	}
	void EMSCRIPTEN_KEEPALIVE mud_DepthParams___destroy__(mud::DepthParams* self) {
		delete self;
	}
	// Environment
	mud::Environment* EMSCRIPTEN_KEEPALIVE mud_Environment_Environment_0() {
		return new mud::Environment();
	}
	mud::Background* EMSCRIPTEN_KEEPALIVE mud_Environment_get_background(mud::Environment* self) {
		static mud::Background temp;
		return (temp = self->m_background, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Environment_set_background(mud::Environment* self, mud::Background* value) {
		self->m_background = *value;
	}
	mud::Radiance* EMSCRIPTEN_KEEPALIVE mud_Environment_get_radiance(mud::Environment* self) {
		static mud::Radiance temp;
		return (temp = self->m_radiance, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Environment_set_radiance(mud::Environment* self, mud::Radiance* value) {
		self->m_radiance = *value;
	}
	mud::Sun* EMSCRIPTEN_KEEPALIVE mud_Environment_get_sun(mud::Environment* self) {
		static mud::Sun temp;
		return (temp = self->m_sun, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Environment_set_sun(mud::Environment* self, mud::Sun* value) {
		self->m_sun = *value;
	}
	mud::Fog* EMSCRIPTEN_KEEPALIVE mud_Environment_get_fog(mud::Environment* self) {
		static mud::Fog temp;
		return (temp = self->m_fog, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Environment_set_fog(mud::Environment* self, mud::Fog* value) {
		self->m_fog = *value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Environment___destroy__(mud::Environment* self) {
		delete self;
	}
	// Filter
	void EMSCRIPTEN_KEEPALIVE mud_Filter___destroy__(mud::Filter* self) {
		delete self;
	}
	// Fog
	mud::Fog* EMSCRIPTEN_KEEPALIVE mud_Fog_Fog_0() {
		return new mud::Fog();
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Fog_get_enabled(mud::Fog* self) {
		return self->m_enabled;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Fog_set_enabled(mud::Fog* self, bool value) {
		self->m_enabled = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Fog_get_density(mud::Fog* self) {
		return self->m_density;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Fog_set_density(mud::Fog* self, float value) {
		self->m_density = value;
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE mud_Fog_get_colour(mud::Fog* self) {
		static mud::Colour temp;
		return (temp = self->m_colour, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Fog_set_colour(mud::Fog* self, mud::Colour* value) {
		self->m_colour = *value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Fog_get_depth(mud::Fog* self) {
		return self->m_depth;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Fog_set_depth(mud::Fog* self, bool value) {
		self->m_depth = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Fog_get_depth_begin(mud::Fog* self) {
		return self->m_depth_begin;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Fog_set_depth_begin(mud::Fog* self, float value) {
		self->m_depth_begin = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Fog_get_depth_curve(mud::Fog* self) {
		return self->m_depth_curve;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Fog_set_depth_curve(mud::Fog* self, float value) {
		self->m_depth_curve = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Fog_get_height(mud::Fog* self) {
		return self->m_height;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Fog_set_height(mud::Fog* self, bool value) {
		self->m_height = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Fog_get_height_min(mud::Fog* self) {
		return self->m_height_min;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Fog_set_height_min(mud::Fog* self, float value) {
		self->m_height_min = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Fog_get_height_max(mud::Fog* self) {
		return self->m_height_max;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Fog_set_height_max(mud::Fog* self, float value) {
		self->m_height_max = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Fog_get_height_curve(mud::Fog* self) {
		return self->m_height_curve;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Fog_set_height_curve(mud::Fog* self, float value) {
		self->m_height_curve = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Fog_get_transmit(mud::Fog* self) {
		return self->m_transmit;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Fog_set_transmit(mud::Fog* self, bool value) {
		self->m_transmit = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Fog_get_transmit_curve(mud::Fog* self) {
		return self->m_transmit_curve;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Fog_set_transmit_curve(mud::Fog* self, float value) {
		self->m_transmit_curve = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Fog___destroy__(mud::Fog* self) {
		delete self;
	}
	// FrameBuffer
	void EMSCRIPTEN_KEEPALIVE mud_FrameBuffer___destroy__(mud::FrameBuffer* self) {
		delete self;
	}
	// FresnelMaterialBlock
	mud::FresnelMaterialBlock* EMSCRIPTEN_KEEPALIVE mud_FresnelMaterialBlock_FresnelMaterialBlock_0() {
		return new mud::FresnelMaterialBlock();
	}
	bool EMSCRIPTEN_KEEPALIVE mud_FresnelMaterialBlock_get_enabled(mud::FresnelMaterialBlock* self) {
		return self->m_enabled;
	}
	void EMSCRIPTEN_KEEPALIVE mud_FresnelMaterialBlock_set_enabled(mud::FresnelMaterialBlock* self, bool value) {
		self->m_enabled = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_FresnelMaterialBlock_get_fresnel_scale(mud::FresnelMaterialBlock* self) {
		return self->m_fresnel_scale;
	}
	void EMSCRIPTEN_KEEPALIVE mud_FresnelMaterialBlock_set_fresnel_scale(mud::FresnelMaterialBlock* self, float value) {
		self->m_fresnel_scale = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_FresnelMaterialBlock_get_fresnel_bias(mud::FresnelMaterialBlock* self) {
		return self->m_fresnel_bias;
	}
	void EMSCRIPTEN_KEEPALIVE mud_FresnelMaterialBlock_set_fresnel_bias(mud::FresnelMaterialBlock* self, float value) {
		self->m_fresnel_bias = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_FresnelMaterialBlock_get_fresnel_power(mud::FresnelMaterialBlock* self) {
		return self->m_fresnel_power;
	}
	void EMSCRIPTEN_KEEPALIVE mud_FresnelMaterialBlock_set_fresnel_power(mud::FresnelMaterialBlock* self, float value) {
		self->m_fresnel_power = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_FresnelMaterialBlock___destroy__(mud::FresnelMaterialBlock* self) {
		delete self;
	}
	// Frustum
	float EMSCRIPTEN_KEEPALIVE mud_Frustum_get_fov(mud::Frustum* self) {
		return self->m_fov;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Frustum_set_fov(mud::Frustum* self, float value) {
		self->m_fov = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Frustum_get_aspect(mud::Frustum* self) {
		return self->m_aspect;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Frustum_set_aspect(mud::Frustum* self, float value) {
		self->m_aspect = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Frustum_get_near(mud::Frustum* self) {
		return self->m_near;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Frustum_set_near(mud::Frustum* self, float value) {
		self->m_near = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Frustum_get_far(mud::Frustum* self) {
		return self->m_far;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Frustum_set_far(mud::Frustum* self, float value) {
		self->m_far = value;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE mud_Frustum_get_center(mud::Frustum* self) {
		static mud::vec3 temp;
		return (temp = self->m_center, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Frustum_set_center(mud::Frustum* self, mud::vec3* value) {
		self->m_center = *value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Frustum_get_radius(mud::Frustum* self) {
		return self->m_radius;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Frustum_set_radius(mud::Frustum* self, float value) {
		self->m_radius = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Frustum___destroy__(mud::Frustum* self) {
		delete self;
	}
	// FrustumSlice
	mud::FrustumSlice* EMSCRIPTEN_KEEPALIVE mud_FrustumSlice_FrustumSlice_0() {
		return new mud::FrustumSlice();
	}
	void EMSCRIPTEN_KEEPALIVE mud_FrustumSlice___destroy__(mud::FrustumSlice* self) {
		delete self;
	}
	// GfxBlock
	mud::Type* EMSCRIPTEN_KEEPALIVE mud_GfxBlock_get_type(mud::GfxBlock* self) {
		return &self->m_type;
	}
	uint8_t EMSCRIPTEN_KEEPALIVE mud_GfxBlock_get_index(mud::GfxBlock* self) {
		return self->m_index;
	}
	void EMSCRIPTEN_KEEPALIVE mud_GfxBlock_set_index(mud::GfxBlock* self, uint8_t value) {
		self->m_index = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_GfxBlock___destroy__(mud::GfxBlock* self) {
		delete self;
	}
	// GfxContext
	void EMSCRIPTEN_KEEPALIVE mud_GfxContext___destroy__(mud::GfxContext* self) {
		delete self;
	}
	// GfxSystem
	void EMSCRIPTEN_KEEPALIVE mud_GfxSystem_add_resource_path_1(mud::GfxSystem* self, const char* path) {
		self->add_resource_path(path);
	}
	mud::Material* EMSCRIPTEN_KEEPALIVE mud_GfxSystem_debug_material_0(mud::GfxSystem* self) {
		return &self->debug_material();
	}
	mud::Material* EMSCRIPTEN_KEEPALIVE mud_GfxSystem_fetch_image256_material_1(mud::GfxSystem* self, const mud::Image256* image) {
		return &self->fetch_image256_material(*image);
	}
	mud::Material* EMSCRIPTEN_KEEPALIVE mud_GfxSystem_fetch_material_2(mud::GfxSystem* self, const char* name, const char* shader) {
		return &self->fetch_material(name, shader);
	}
	mud::Material* EMSCRIPTEN_KEEPALIVE mud_GfxSystem_fetch_material_3(mud::GfxSystem* self, const char* name, const char* shader, bool builtin) {
		return &self->fetch_material(name, shader, builtin);
	}
	mud::Model* EMSCRIPTEN_KEEPALIVE mud_GfxSystem_fetch_symbol_3(mud::GfxSystem* self, const mud::Symbol* symbol, const mud::Shape* shape, mud::DrawMode draw_mode) {
		return &self->fetch_symbol(*symbol, *shape, draw_mode);
	}
	mud::Material* EMSCRIPTEN_KEEPALIVE mud_GfxSystem_fetch_symbol_material_2(mud::GfxSystem* self, const mud::Symbol* symbol, mud::DrawMode draw_mode) {
		return &self->fetch_symbol_material(*symbol, draw_mode);
	}
	void EMSCRIPTEN_KEEPALIVE mud_GfxSystem___destroy__(mud::GfxSystem* self) {
		delete self;
	}
	// Gnode
	void EMSCRIPTEN_KEEPALIVE mud_Gnode___destroy__(mud::Gnode* self) {
		delete self;
	}
	// ImmediateDraw
	void EMSCRIPTEN_KEEPALIVE mud_ImmediateDraw___destroy__(mud::ImmediateDraw* self) {
		delete self;
	}
	// ImportConfig
	mud::ImportConfig* EMSCRIPTEN_KEEPALIVE mud_ImportConfig_ImportConfig_0() {
		return new mud::ImportConfig();
	}
	mud::ModelFormat EMSCRIPTEN_KEEPALIVE mud_ImportConfig_get_format(mud::ImportConfig* self) {
		return self->m_format;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ImportConfig_set_format(mud::ImportConfig* self, mud::ModelFormat value) {
		self->m_format = value;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE mud_ImportConfig_get_position(mud::ImportConfig* self) {
		static mud::vec3 temp;
		return (temp = self->m_position, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_ImportConfig_set_position(mud::ImportConfig* self, mud::vec3* value) {
		self->m_position = *value;
	}
	mud::quat* EMSCRIPTEN_KEEPALIVE mud_ImportConfig_get_rotation(mud::ImportConfig* self) {
		static mud::quat temp;
		return (temp = self->m_rotation, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_ImportConfig_set_rotation(mud::ImportConfig* self, mud::quat* value) {
		self->m_rotation = *value;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE mud_ImportConfig_get_scale(mud::ImportConfig* self) {
		static mud::vec3 temp;
		return (temp = self->m_scale, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_ImportConfig_set_scale(mud::ImportConfig* self, mud::vec3* value) {
		self->m_scale = *value;
	}
	mud::mat4* EMSCRIPTEN_KEEPALIVE mud_ImportConfig_get_transform(mud::ImportConfig* self) {
		static mud::mat4 temp;
		return (temp = self->m_transform, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_ImportConfig_set_transform(mud::ImportConfig* self, mud::mat4* value) {
		self->m_transform = *value;
	}
	const char* EMSCRIPTEN_KEEPALIVE mud_ImportConfig_get_suffix(mud::ImportConfig* self) {
		return self->m_suffix.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE mud_ImportConfig_set_suffix(mud::ImportConfig* self, const char* value) {
		self->m_suffix = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_ImportConfig_get_force_reimport(mud::ImportConfig* self) {
		return self->m_force_reimport;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ImportConfig_set_force_reimport(mud::ImportConfig* self, bool value) {
		self->m_force_reimport = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_ImportConfig_get_cache_geometry(mud::ImportConfig* self) {
		return self->m_cache_geometry;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ImportConfig_set_cache_geometry(mud::ImportConfig* self, bool value) {
		self->m_cache_geometry = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_ImportConfig_get_optimize_geometry(mud::ImportConfig* self) {
		return self->m_optimize_geometry;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ImportConfig_set_optimize_geometry(mud::ImportConfig* self, bool value) {
		self->m_optimize_geometry = value;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE mud_ImportConfig_get_flags(mud::ImportConfig* self) {
		return self->m_flags;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ImportConfig_set_flags(mud::ImportConfig* self, uint32_t value) {
		self->m_flags = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ImportConfig___destroy__(mud::ImportConfig* self) {
		delete self;
	}
	// Item
	mud::Node3* EMSCRIPTEN_KEEPALIVE mud_Item_get_node(mud::Item* self) {
		return self->m_node;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Item_set_node(mud::Item* self, mud::Node3* value) {
		self->m_node = value;
	}
	mud::Model* EMSCRIPTEN_KEEPALIVE mud_Item_get_model(mud::Item* self) {
		return self->m_model;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Item_set_model(mud::Item* self, mud::Model* value) {
		self->m_model = value;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE mud_Item_get_flags(mud::Item* self) {
		return self->m_flags;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Item_set_flags(mud::Item* self, uint32_t value) {
		self->m_flags = value;
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE mud_Item_get_colour(mud::Item* self) {
		static mud::Colour temp;
		return (temp = self->m_colour, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Item_set_colour(mud::Item* self, mud::Colour* value) {
		self->m_colour = *value;
	}
	mud::Material* EMSCRIPTEN_KEEPALIVE mud_Item_get_material(mud::Item* self) {
		return self->m_material;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Item_set_material(mud::Item* self, mud::Material* value) {
		self->m_material = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Item_get_visible(mud::Item* self) {
		return self->m_visible;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Item_set_visible(mud::Item* self, bool value) {
		self->m_visible = value;
	}
	mud::ItemShadow EMSCRIPTEN_KEEPALIVE mud_Item_get_shadow(mud::Item* self) {
		return self->m_shadow;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Item_set_shadow(mud::Item* self, mud::ItemShadow value) {
		self->m_shadow = value;
	}
	mud::Rig* EMSCRIPTEN_KEEPALIVE mud_Item_get_rig(mud::Item* self) {
		return self->m_rig;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Item_set_rig(mud::Item* self, mud::Rig* value) {
		self->m_rig = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Item___destroy__(mud::Item* self) {
		delete self;
	}
	// Joint
	mud::Joint* EMSCRIPTEN_KEEPALIVE mud_Joint_Joint_0() {
		return new mud::Joint();
	}
	void EMSCRIPTEN_KEEPALIVE mud_Joint___destroy__(mud::Joint* self) {
		delete self;
	}
	// Light
	mud::Node3* EMSCRIPTEN_KEEPALIVE mud_Light_get_node(mud::Light* self) {
		return &self->m_node;
	}
	mud::LightType EMSCRIPTEN_KEEPALIVE mud_Light_get_type(mud::Light* self) {
		return self->m_type;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Light_set_type(mud::Light* self, mud::LightType value) {
		self->m_type = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Light_get_visible(mud::Light* self) {
		return self->m_visible;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Light_set_visible(mud::Light* self, bool value) {
		self->m_visible = value;
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE mud_Light_get_colour(mud::Light* self) {
		static mud::Colour temp;
		return (temp = self->m_colour, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Light_set_colour(mud::Light* self, mud::Colour* value) {
		self->m_colour = *value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Light_get_range(mud::Light* self) {
		return self->m_range;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Light_set_range(mud::Light* self, float value) {
		self->m_range = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Light_get_energy(mud::Light* self) {
		return self->m_energy;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Light_set_energy(mud::Light* self, float value) {
		self->m_energy = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Light_get_specular(mud::Light* self) {
		return self->m_specular;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Light_set_specular(mud::Light* self, float value) {
		self->m_specular = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Light_get_attenuation(mud::Light* self) {
		return self->m_attenuation;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Light_set_attenuation(mud::Light* self, float value) {
		self->m_attenuation = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Light_get_shadows(mud::Light* self) {
		return self->m_shadows;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Light_set_shadows(mud::Light* self, bool value) {
		self->m_shadows = value;
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE mud_Light_get_shadow_colour(mud::Light* self) {
		static mud::Colour temp;
		return (temp = self->m_shadow_colour, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Light_set_shadow_colour(mud::Light* self, mud::Colour* value) {
		self->m_shadow_colour = *value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Light_get_shadow_range(mud::Light* self) {
		return self->m_shadow_range;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Light_set_shadow_range(mud::Light* self, float value) {
		self->m_shadow_range = value;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE mud_Light_get_layers(mud::Light* self) {
		return self->m_layers;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Light_set_layers(mud::Light* self, uint32_t value) {
		self->m_layers = value;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE mud_Light_get_last_render(mud::Light* self) {
		return self->m_last_render;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Light_set_last_render(mud::Light* self, uint32_t value) {
		self->m_last_render = value;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE mud_Light_get_last_update(mud::Light* self) {
		return self->m_last_update;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Light_set_last_update(mud::Light* self, uint32_t value) {
		self->m_last_update = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Light_get_spot_angle(mud::Light* self) {
		return self->m_spot_angle;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Light_set_spot_angle(mud::Light* self, float value) {
		self->m_spot_angle = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Light_get_spot_attenuation(mud::Light* self) {
		return self->m_spot_attenuation;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Light_set_spot_attenuation(mud::Light* self, float value) {
		self->m_spot_attenuation = value;
	}
	mud::ShadowFlags EMSCRIPTEN_KEEPALIVE mud_Light_get_shadow_flags(mud::Light* self) {
		return self->m_shadow_flags;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Light_set_shadow_flags(mud::Light* self, mud::ShadowFlags value) {
		self->m_shadow_flags = value;
	}
	uint8_t EMSCRIPTEN_KEEPALIVE mud_Light_get_shadow_nusplits(mud::Light* self) {
		return self->m_shadow_num_splits;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Light_set_shadow_nusplits(mud::Light* self, uint8_t value) {
		self->m_shadow_num_splits = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Light_get_shadow_split_distribution(mud::Light* self) {
		return self->m_shadow_split_distribution;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Light_set_shadow_split_distribution(mud::Light* self, float value) {
		self->m_shadow_split_distribution = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Light_get_shadow_normal_bias(mud::Light* self) {
		return self->m_shadow_normal_bias;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Light_set_shadow_normal_bias(mud::Light* self, float value) {
		self->m_shadow_normal_bias = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Light_get_shadow_bias(mud::Light* self) {
		return self->m_shadow_bias;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Light_set_shadow_bias(mud::Light* self, float value) {
		self->m_shadow_bias = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Light___destroy__(mud::Light* self) {
		delete self;
	}
	// Material
	uint16_t EMSCRIPTEN_KEEPALIVE mud_Material_get_index(mud::Material* self) {
		return self->m_index;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Material_set_index(mud::Material* self, uint16_t value) {
		self->m_index = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Material_get_builtin(mud::Material* self) {
		return self->m_builtin;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Material_set_builtin(mud::Material* self, bool value) {
		self->m_builtin = value;
	}
	mud::Program* EMSCRIPTEN_KEEPALIVE mud_Material_get_program(mud::Material* self) {
		return self->m_program;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Material_set_program(mud::Material* self, mud::Program* value) {
		self->m_program = value;
	}
	mud::BaseMaterialBlock* EMSCRIPTEN_KEEPALIVE mud_Material_get_base_block(mud::Material* self) {
		static mud::BaseMaterialBlock temp;
		return (temp = self->m_base_block, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Material_set_base_block(mud::Material* self, mud::BaseMaterialBlock* value) {
		self->m_base_block = *value;
	}
	mud::UnshadedMaterialBlock* EMSCRIPTEN_KEEPALIVE mud_Material_get_unshaded_block(mud::Material* self) {
		static mud::UnshadedMaterialBlock temp;
		return (temp = self->m_unshaded_block, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Material_set_unshaded_block(mud::Material* self, mud::UnshadedMaterialBlock* value) {
		self->m_unshaded_block = *value;
	}
	mud::PbrMaterialBlock* EMSCRIPTEN_KEEPALIVE mud_Material_get_pbr_block(mud::Material* self) {
		static mud::PbrMaterialBlock temp;
		return (temp = self->m_pbr_block, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Material_set_pbr_block(mud::Material* self, mud::PbrMaterialBlock* value) {
		self->m_pbr_block = *value;
	}
	mud::FresnelMaterialBlock* EMSCRIPTEN_KEEPALIVE mud_Material_get_fresnel_block(mud::Material* self) {
		static mud::FresnelMaterialBlock temp;
		return (temp = self->m_fresnel_block, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Material_set_fresnel_block(mud::Material* self, mud::FresnelMaterialBlock* value) {
		self->m_fresnel_block = *value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Material___destroy__(mud::Material* self) {
		delete self;
	}
	// Mesh
	const char* EMSCRIPTEN_KEEPALIVE mud_Mesh_get_name(mud::Mesh* self) {
		return self->m_name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE mud_Mesh_set_name(mud::Mesh* self, const char* value) {
		self->m_name = value;
	}
	uint16_t EMSCRIPTEN_KEEPALIVE mud_Mesh_get_index(mud::Mesh* self) {
		return self->m_index;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Mesh_set_index(mud::Mesh* self, uint16_t value) {
		self->m_index = value;
	}
	mud::DrawMode EMSCRIPTEN_KEEPALIVE mud_Mesh_get_draw_mode(mud::Mesh* self) {
		return self->m_draw_mode;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Mesh_set_draw_mode(mud::Mesh* self, mud::DrawMode value) {
		self->m_draw_mode = value;
	}
	mud::Aabb* EMSCRIPTEN_KEEPALIVE mud_Mesh_get_aabb(mud::Mesh* self) {
		static mud::Aabb temp;
		return (temp = self->m_aabb, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Mesh_set_aabb(mud::Mesh* self, mud::Aabb* value) {
		self->m_aabb = *value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Mesh_get_radius(mud::Mesh* self) {
		return self->m_radius;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Mesh_set_radius(mud::Mesh* self, float value) {
		self->m_radius = value;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE mud_Mesh_get_origin(mud::Mesh* self) {
		static mud::vec3 temp;
		return (temp = self->m_origin, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Mesh_set_origin(mud::Mesh* self, mud::vec3* value) {
		self->m_origin = *value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Mesh_get_readback(mud::Mesh* self) {
		return self->m_readback;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Mesh_set_readback(mud::Mesh* self, bool value) {
		self->m_readback = value;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE mud_Mesh_get_vertex_format(mud::Mesh* self) {
		return self->m_vertex_format;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Mesh_set_vertex_format(mud::Mesh* self, uint32_t value) {
		self->m_vertex_format = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Mesh_get_qnormals(mud::Mesh* self) {
		return self->m_qnormals;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Mesh_set_qnormals(mud::Mesh* self, bool value) {
		self->m_qnormals = value;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE mud_Mesh_get_vertex_count(mud::Mesh* self) {
		return self->m_vertex_count;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Mesh_set_vertex_count(mud::Mesh* self, uint32_t value) {
		self->m_vertex_count = value;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE mud_Mesh_get_index_count(mud::Mesh* self) {
		return self->m_index_count;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Mesh_set_index_count(mud::Mesh* self, uint32_t value) {
		self->m_index_count = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Mesh_get_index32(mud::Mesh* self) {
		return self->m_index32;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Mesh_set_index32(mud::Mesh* self, bool value) {
		self->m_index32 = value;
	}
	mud::Material* EMSCRIPTEN_KEEPALIVE mud_Mesh_get_material(mud::Mesh* self) {
		return self->m_material;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Mesh_set_material(mud::Mesh* self, mud::Material* value) {
		self->m_material = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Mesh___destroy__(mud::Mesh* self) {
		delete self;
	}
	// Model
	const char* EMSCRIPTEN_KEEPALIVE mud_Model_get_name(mud::Model* self) {
		return self->m_name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE mud_Model_set_name(mud::Model* self, const char* value) {
		self->m_name = value;
	}
	uint16_t EMSCRIPTEN_KEEPALIVE mud_Model_get_index(mud::Model* self) {
		return self->m_index;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Model_set_index(mud::Model* self, uint16_t value) {
		self->m_index = value;
	}
	mud::Aabb* EMSCRIPTEN_KEEPALIVE mud_Model_get_aabb(mud::Model* self) {
		static mud::Aabb temp;
		return (temp = self->m_aabb, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Model_set_aabb(mud::Model* self, mud::Aabb* value) {
		self->m_aabb = *value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Model_get_radius(mud::Model* self) {
		return self->m_radius;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Model_set_radius(mud::Model* self, float value) {
		self->m_radius = value;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE mud_Model_get_origin(mud::Model* self) {
		static mud::vec3 temp;
		return (temp = self->m_origin, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Model_set_origin(mud::Model* self, mud::vec3* value) {
		self->m_origin = *value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Model___destroy__(mud::Model* self) {
		delete self;
	}
	// ModelItem
	mud::ModelItem* EMSCRIPTEN_KEEPALIVE mud_ModelItem_ModelItem_0() {
		return new mud::ModelItem();
	}
	size_t EMSCRIPTEN_KEEPALIVE mud_ModelItem_get_index(mud::ModelItem* self) {
		return self->m_index;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ModelItem_set_index(mud::ModelItem* self, size_t value) {
		self->m_index = value;
	}
	mud::Mesh* EMSCRIPTEN_KEEPALIVE mud_ModelItem_get_mesh(mud::ModelItem* self) {
		return self->m_mesh;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ModelItem_set_mesh(mud::ModelItem* self, mud::Mesh* value) {
		self->m_mesh = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_ModelItem_get_has_transform(mud::ModelItem* self) {
		return self->m_has_transform;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ModelItem_set_has_transform(mud::ModelItem* self, bool value) {
		self->m_has_transform = value;
	}
	mud::mat4* EMSCRIPTEN_KEEPALIVE mud_ModelItem_get_transform(mud::ModelItem* self) {
		static mud::mat4 temp;
		return (temp = self->m_transform, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_ModelItem_set_transform(mud::ModelItem* self, mud::mat4* value) {
		self->m_transform = *value;
	}
	int EMSCRIPTEN_KEEPALIVE mud_ModelItem_get_skin(mud::ModelItem* self) {
		return self->m_skin;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ModelItem_set_skin(mud::ModelItem* self, int value) {
		self->m_skin = value;
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE mud_ModelItem_get_colour(mud::ModelItem* self) {
		static mud::Colour temp;
		return (temp = self->m_colour, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_ModelItem_set_colour(mud::ModelItem* self, mud::Colour* value) {
		self->m_colour = *value;
	}
	mud::Material* EMSCRIPTEN_KEEPALIVE mud_ModelItem_get_material(mud::ModelItem* self) {
		return self->m_material;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ModelItem_set_material(mud::ModelItem* self, mud::Material* value) {
		self->m_material = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ModelItem___destroy__(mud::ModelItem* self) {
		delete self;
	}
	// Node3
	mud::Scene* EMSCRIPTEN_KEEPALIVE mud_Node3_get_scene(mud::Node3* self) {
		return self->m_scene;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Node3_set_scene(mud::Node3* self, mud::Scene* value) {
		self->m_scene = value;
	}
	uint16_t EMSCRIPTEN_KEEPALIVE mud_Node3_get_index(mud::Node3* self) {
		return self->m_index;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Node3_set_index(mud::Node3* self, uint16_t value) {
		self->m_index = value;
	}
	mud::mat4* EMSCRIPTEN_KEEPALIVE mud_Node3_get_transform(mud::Node3* self) {
		static mud::mat4 temp;
		return (temp = self->m_transform, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Node3_set_transform(mud::Node3* self, mud::mat4* value) {
		self->m_transform = *value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Node3_get_visible(mud::Node3* self) {
		return self->m_visible;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Node3_set_visible(mud::Node3* self, bool value) {
		self->m_visible = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Node3___destroy__(mud::Node3* self) {
		delete self;
	}
	// ParticleGenerator
	mud::ParticleGenerator* EMSCRIPTEN_KEEPALIVE mud_ParticleGenerator_ParticleGenerator_0() {
		return new mud::ParticleGenerator();
	}
	const char* EMSCRIPTEN_KEEPALIVE mud_ParticleGenerator_get_name(mud::ParticleGenerator* self) {
		return self->m_name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE mud_ParticleGenerator_set_name(mud::ParticleGenerator* self, const char* value) {
		self->m_name = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_ParticleGenerator_get_duration(mud::ParticleGenerator* self) {
		return self->m_duration;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ParticleGenerator_set_duration(mud::ParticleGenerator* self, float value) {
		self->m_duration = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_ParticleGenerator_get_start_time(mud::ParticleGenerator* self) {
		return self->m_start_time;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ParticleGenerator_set_start_time(mud::ParticleGenerator* self, float value) {
		self->m_start_time = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_ParticleGenerator_get_loop(mud::ParticleGenerator* self) {
		return self->m_loop;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ParticleGenerator_set_loop(mud::ParticleGenerator* self, bool value) {
		self->m_loop = value;
	}
	mud::ShapeVar* EMSCRIPTEN_KEEPALIVE mud_ParticleGenerator_get_shape(mud::ParticleGenerator* self) {
		static mud::ShapeVar temp;
		return (temp = self->m_shape, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_ParticleGenerator_set_shape(mud::ParticleGenerator* self, mud::ShapeVar* value) {
		self->m_shape = *value;
	}
	mud::EmitterFlow EMSCRIPTEN_KEEPALIVE mud_ParticleGenerator_get_flow(mud::ParticleGenerator* self) {
		return self->m_flow;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ParticleGenerator_set_flow(mud::ParticleGenerator* self, mud::EmitterFlow value) {
		self->m_flow = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_ParticleGenerator_get_billboard(mud::ParticleGenerator* self) {
		return self->m_billboard;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ParticleGenerator_set_billboard(mud::ParticleGenerator* self, bool value) {
		self->m_billboard = value;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE mud_ParticleGenerator_get_direction(mud::ParticleGenerator* self) {
		static mud::vec3 temp;
		return (temp = self->m_direction, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_ParticleGenerator_set_direction(mud::ParticleGenerator* self, mud::vec3* value) {
		self->m_direction = *value;
	}
	mud::quat* EMSCRIPTEN_KEEPALIVE mud_ParticleGenerator_get_rotation(mud::ParticleGenerator* self) {
		static mud::quat temp;
		return (temp = self->m_rotation, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_ParticleGenerator_set_rotation(mud::ParticleGenerator* self, mud::quat* value) {
		self->m_rotation = *value;
	}
	mud::BlendMode EMSCRIPTEN_KEEPALIVE mud_ParticleGenerator_get_blend_mode(mud::ParticleGenerator* self) {
		return self->m_blend_mode;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ParticleGenerator_set_blend_mode(mud::ParticleGenerator* self, mud::BlendMode value) {
		self->m_blend_mode = value;
	}
	const char* EMSCRIPTEN_KEEPALIVE mud_ParticleGenerator_get_sprite_name(mud::ParticleGenerator* self) {
		return self->m_sprite_name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE mud_ParticleGenerator_set_sprite_name(mud::ParticleGenerator* self, const char* value) {
		self->m_sprite_name = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ParticleGenerator___destroy__(mud::ParticleGenerator* self) {
		delete self;
	}
	// PbrMaterialBlock
	mud::PbrMaterialBlock* EMSCRIPTEN_KEEPALIVE mud_PbrMaterialBlock_PbrMaterialBlock_0() {
		return new mud::PbrMaterialBlock();
	}
	mud::PbrMaterialBlock* EMSCRIPTEN_KEEPALIVE mud_PbrMaterialBlock_PbrMaterialBlock_1(const mud::Colour* albedo) {
		return new mud::PbrMaterialBlock(*albedo);
	}
	mud::PbrMaterialBlock* EMSCRIPTEN_KEEPALIVE mud_PbrMaterialBlock_PbrMaterialBlock_2(const mud::Colour* albedo, float metallic) {
		return new mud::PbrMaterialBlock(*albedo, metallic);
	}
	mud::PbrMaterialBlock* EMSCRIPTEN_KEEPALIVE mud_PbrMaterialBlock_PbrMaterialBlock_3(const mud::Colour* albedo, float metallic, float roughness) {
		return new mud::PbrMaterialBlock(*albedo, metallic, roughness);
	}
	bool EMSCRIPTEN_KEEPALIVE mud_PbrMaterialBlock_get_enabled(mud::PbrMaterialBlock* self) {
		return self->m_enabled;
	}
	void EMSCRIPTEN_KEEPALIVE mud_PbrMaterialBlock_set_enabled(mud::PbrMaterialBlock* self, bool value) {
		self->m_enabled = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_PbrMaterialBlock_get_specular(mud::PbrMaterialBlock* self) {
		return self->m_specular;
	}
	void EMSCRIPTEN_KEEPALIVE mud_PbrMaterialBlock_set_specular(mud::PbrMaterialBlock* self, float value) {
		self->m_specular = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_PbrMaterialBlock_get_emissive_energy(mud::PbrMaterialBlock* self) {
		return self->m_emissive_energy;
	}
	void EMSCRIPTEN_KEEPALIVE mud_PbrMaterialBlock_set_emissive_energy(mud::PbrMaterialBlock* self, float value) {
		self->m_emissive_energy = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_PbrMaterialBlock_get_ritint(mud::PbrMaterialBlock* self) {
		return self->m_rim_tint;
	}
	void EMSCRIPTEN_KEEPALIVE mud_PbrMaterialBlock_set_ritint(mud::PbrMaterialBlock* self, float value) {
		self->m_rim_tint = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_PbrMaterialBlock_get_clearcoat_gloss(mud::PbrMaterialBlock* self) {
		return self->m_clearcoat_gloss;
	}
	void EMSCRIPTEN_KEEPALIVE mud_PbrMaterialBlock_set_clearcoat_gloss(mud::PbrMaterialBlock* self, float value) {
		self->m_clearcoat_gloss = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_PbrMaterialBlock_get_deep_parallax(mud::PbrMaterialBlock* self) {
		return self->m_deep_parallax;
	}
	void EMSCRIPTEN_KEEPALIVE mud_PbrMaterialBlock_set_deep_parallax(mud::PbrMaterialBlock* self, bool value) {
		self->m_deep_parallax = value;
	}
	mud::PbrDiffuseMode EMSCRIPTEN_KEEPALIVE mud_PbrMaterialBlock_get_diffuse_mode(mud::PbrMaterialBlock* self) {
		return self->m_diffuse_mode;
	}
	void EMSCRIPTEN_KEEPALIVE mud_PbrMaterialBlock_set_diffuse_mode(mud::PbrMaterialBlock* self, mud::PbrDiffuseMode value) {
		self->m_diffuse_mode = value;
	}
	mud::PbrSpecularMode EMSCRIPTEN_KEEPALIVE mud_PbrMaterialBlock_get_specular_mode(mud::PbrMaterialBlock* self) {
		return self->m_specular_mode;
	}
	void EMSCRIPTEN_KEEPALIVE mud_PbrMaterialBlock_set_specular_mode(mud::PbrMaterialBlock* self, mud::PbrSpecularMode value) {
		self->m_specular_mode = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_PbrMaterialBlock___destroy__(mud::PbrMaterialBlock* self) {
		delete self;
	}
	// Prefab
	const char* EMSCRIPTEN_KEEPALIVE mud_Prefab_get_name(mud::Prefab* self) {
		return self->m_name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE mud_Prefab_set_name(mud::Prefab* self, const char* value) {
		self->m_name = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Prefab___destroy__(mud::Prefab* self) {
		delete self;
	}
	// Program
	const char* EMSCRIPTEN_KEEPALIVE mud_Program_get_name(mud::Program* self) {
		return self->name();
	}
	void EMSCRIPTEN_KEEPALIVE mud_Program___destroy__(mud::Program* self) {
		delete self;
	}
	// Radiance
	mud::Radiance* EMSCRIPTEN_KEEPALIVE mud_Radiance_Radiance_0() {
		return new mud::Radiance();
	}
	float EMSCRIPTEN_KEEPALIVE mud_Radiance_get_energy(mud::Radiance* self) {
		return self->m_energy;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Radiance_set_energy(mud::Radiance* self, float value) {
		self->m_energy = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Radiance_get_ambient(mud::Radiance* self) {
		return self->m_ambient;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Radiance_set_ambient(mud::Radiance* self, float value) {
		self->m_ambient = value;
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE mud_Radiance_get_colour(mud::Radiance* self) {
		static mud::Colour temp;
		return (temp = self->m_colour, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Radiance_set_colour(mud::Radiance* self, mud::Colour* value) {
		self->m_colour = *value;
	}
	mud::Texture* EMSCRIPTEN_KEEPALIVE mud_Radiance_get_texture(mud::Radiance* self) {
		return self->m_texture;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Radiance_set_texture(mud::Radiance* self, mud::Texture* value) {
		self->m_texture = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Radiance___destroy__(mud::Radiance* self) {
		delete self;
	}
	// RenderFrame
	mud::RenderFrame* EMSCRIPTEN_KEEPALIVE mud_RenderFrame_RenderFrame_0() {
		return new mud::RenderFrame();
	}
	void EMSCRIPTEN_KEEPALIVE mud_RenderFrame___destroy__(mud::RenderFrame* self) {
		delete self;
	}
	// RenderQuad
	mud::RenderQuad* EMSCRIPTEN_KEEPALIVE mud_RenderQuad_RenderQuad_0() {
		return new mud::RenderQuad();
	}
	void EMSCRIPTEN_KEEPALIVE mud_RenderQuad___destroy__(mud::RenderQuad* self) {
		delete self;
	}
	// Rig
	void EMSCRIPTEN_KEEPALIVE mud_Rig___destroy__(mud::Rig* self) {
		delete self;
	}
	// Scene
	mud::Gnode* EMSCRIPTEN_KEEPALIVE mud_Scene_begin_0(mud::Scene* self) {
		return &self->begin();
	}
	mud::Gnode* EMSCRIPTEN_KEEPALIVE mud_Scene_get_graph(mud::Scene* self) {
		return &self->m_graph;
	}
	mud::Node3* EMSCRIPTEN_KEEPALIVE mud_Scene_get_root_node(mud::Scene* self) {
		return &self->m_root_node;
	}
	mud::Environment* EMSCRIPTEN_KEEPALIVE mud_Scene_get_environment(mud::Scene* self) {
		static mud::Environment temp;
		return (temp = self->m_environment, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Scene_set_environment(mud::Scene* self, mud::Environment* value) {
		self->m_environment = *value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Scene___destroy__(mud::Scene* self) {
		delete self;
	}
	// Shot
	void EMSCRIPTEN_KEEPALIVE mud_Shot___destroy__(mud::Shot* self) {
		delete self;
	}
	// Skeleton
	void EMSCRIPTEN_KEEPALIVE mud_Skeleton___destroy__(mud::Skeleton* self) {
		delete self;
	}
	// Skin
	void EMSCRIPTEN_KEEPALIVE mud_Skin___destroy__(mud::Skin* self) {
		delete self;
	}
	// Sun
	mud::Sun* EMSCRIPTEN_KEEPALIVE mud_Sun_Sun_0() {
		return new mud::Sun();
	}
	float EMSCRIPTEN_KEEPALIVE mud_Sun_get_azimuth(mud::Sun* self) {
		return self->azimuth;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Sun_set_azimuth(mud::Sun* self, float value) {
		self->azimuth = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Sun_get_elevation(mud::Sun* self) {
		return self->elevation;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Sun_set_elevation(mud::Sun* self, float value) {
		self->elevation = value;
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE mud_Sun_get_colour(mud::Sun* self) {
		static mud::Colour temp;
		return (temp = self->m_colour, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Sun_set_colour(mud::Sun* self, mud::Colour* value) {
		self->m_colour = *value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Sun_get_intensity(mud::Sun* self) {
		return self->m_intensity;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Sun_set_intensity(mud::Sun* self, float value) {
		self->m_intensity = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Sun___destroy__(mud::Sun* self) {
		delete self;
	}
	// SymbolIndex
	void EMSCRIPTEN_KEEPALIVE mud_SymbolIndex___destroy__(mud::SymbolIndex* self) {
		delete self;
	}
	// Texture
	uint16_t EMSCRIPTEN_KEEPALIVE mud_Texture_get_width(mud::Texture* self) {
		return self->m_width;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Texture_set_width(mud::Texture* self, uint16_t value) {
		self->m_width = value;
	}
	uint16_t EMSCRIPTEN_KEEPALIVE mud_Texture_get_height(mud::Texture* self) {
		return self->m_height;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Texture_set_height(mud::Texture* self, uint16_t value) {
		self->m_height = value;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE mud_Texture_get_bits_per_pixel(mud::Texture* self) {
		return self->m_bits_per_pixel;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Texture_set_bits_per_pixel(mud::Texture* self, uint32_t value) {
		self->m_bits_per_pixel = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Texture___destroy__(mud::Texture* self) {
		delete self;
	}
	// UnshadedMaterialBlock
	mud::UnshadedMaterialBlock* EMSCRIPTEN_KEEPALIVE mud_UnshadedMaterialBlock_UnshadedMaterialBlock_0() {
		return new mud::UnshadedMaterialBlock();
	}
	bool EMSCRIPTEN_KEEPALIVE mud_UnshadedMaterialBlock_get_enabled(mud::UnshadedMaterialBlock* self) {
		return self->m_enabled;
	}
	void EMSCRIPTEN_KEEPALIVE mud_UnshadedMaterialBlock_set_enabled(mud::UnshadedMaterialBlock* self, bool value) {
		self->m_enabled = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_UnshadedMaterialBlock___destroy__(mud::UnshadedMaterialBlock* self) {
		delete self;
	}
	// Viewport
	mud::Camera* EMSCRIPTEN_KEEPALIVE mud_Viewport_get_camera(mud::Viewport* self) {
		return self->m_camera;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Viewport_set_camera(mud::Viewport* self, mud::Camera* value) {
		self->m_camera = value;
	}
	mud::Scene* EMSCRIPTEN_KEEPALIVE mud_Viewport_get_scene(mud::Viewport* self) {
		return self->m_scene;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Viewport_set_scene(mud::Viewport* self, mud::Scene* value) {
		self->m_scene = value;
	}
	uint16_t EMSCRIPTEN_KEEPALIVE mud_Viewport_get_index(mud::Viewport* self) {
		return self->m_index;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Viewport_set_index(mud::Viewport* self, uint16_t value) {
		self->m_index = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Viewport_get_active(mud::Viewport* self) {
		return self->m_active;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Viewport_set_active(mud::Viewport* self, bool value) {
		self->m_active = value;
	}
	mud::uvec4* EMSCRIPTEN_KEEPALIVE mud_Viewport_get_rect(mud::Viewport* self) {
		static mud::uvec4 temp;
		return (temp = self->m_rect, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Viewport_set_rect(mud::Viewport* self, mud::uvec4* value) {
		self->m_rect = *value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Viewport_get_scissor(mud::Viewport* self) {
		return self->m_scissor;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Viewport_set_scissor(mud::Viewport* self, bool value) {
		self->m_scissor = value;
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE mud_Viewport_get_clear_colour(mud::Viewport* self) {
		static mud::Colour temp;
		return (temp = self->m_clear_colour, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Viewport_set_clear_colour(mud::Viewport* self, mud::Colour* value) {
		self->m_clear_colour = *value;
	}
	mud::Shading EMSCRIPTEN_KEEPALIVE mud_Viewport_get_shading(mud::Viewport* self) {
		return self->m_shading;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Viewport_set_shading(mud::Viewport* self, mud::Shading value) {
		self->m_shading = value;
	}
	mud::Lighting EMSCRIPTEN_KEEPALIVE mud_Viewport_get_lighting(mud::Viewport* self) {
		return self->m_lighting;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Viewport_set_lighting(mud::Viewport* self, mud::Lighting value) {
		self->m_lighting = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Viewport___destroy__(mud::Viewport* self) {
		delete self;
	}
	// BlockCopy
	void EMSCRIPTEN_KEEPALIVE mud_BlockCopy___destroy__(mud::BlockCopy* self) {
		delete self;
	}
	// DrawBlock
	void EMSCRIPTEN_KEEPALIVE mud_DrawBlock___destroy__(mud::DrawBlock* self) {
		delete self;
	}
	// BlockDepth
	void EMSCRIPTEN_KEEPALIVE mud_BlockDepth___destroy__(mud::BlockDepth* self) {
		delete self;
	}
	// BlockFilter
	void EMSCRIPTEN_KEEPALIVE mud_BlockFilter___destroy__(mud::BlockFilter* self) {
		delete self;
	}
	// BlockParticles
	void EMSCRIPTEN_KEEPALIVE mud_BlockParticles___destroy__(mud::BlockParticles* self) {
		delete self;
	}
	// BlockResolve
	void EMSCRIPTEN_KEEPALIVE mud_BlockResolve___destroy__(mud::BlockResolve* self) {
		delete self;
	}
	// BlockSky
	void EMSCRIPTEN_KEEPALIVE mud_BlockSky___destroy__(mud::BlockSky* self) {
		delete self;
	}
	// ClusteredFrustum
	mud::ClusteredFrustum* EMSCRIPTEN_KEEPALIVE mud_ClusteredFrustum_ClusteredFrustum_0() {
		return new mud::ClusteredFrustum();
	}
	void EMSCRIPTEN_KEEPALIVE mud_ClusteredFrustum___destroy__(mud::ClusteredFrustum* self) {
		delete self;
	}
	// Particles
	mud::Particles* EMSCRIPTEN_KEEPALIVE mud_Particles_Particles_0() {
		return new mud::Particles();
	}
	mud::Node3* EMSCRIPTEN_KEEPALIVE mud_Particles_get_node(mud::Particles* self) {
		return self->m_node;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Particles_set_node(mud::Particles* self, mud::Node3* value) {
		self->m_node = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Particles___destroy__(mud::Particles* self) {
		delete self;
	}
	// RenderTarget
	void EMSCRIPTEN_KEEPALIVE mud_RenderTarget___destroy__(mud::RenderTarget* self) {
		delete self;
	}
	// AnimationTarget
	mud::AnimationTarget EMSCRIPTEN_KEEPALIVE mud_AnimationTarget_Position() {
		return mud::AnimationTarget::Position;
	}
	mud::AnimationTarget EMSCRIPTEN_KEEPALIVE mud_AnimationTarget_Rotation() {
		return mud::AnimationTarget::Rotation;
	}
	mud::AnimationTarget EMSCRIPTEN_KEEPALIVE mud_AnimationTarget_Scale() {
		return mud::AnimationTarget::Scale;
	}
	// BackgroundMode
	mud::BackgroundMode EMSCRIPTEN_KEEPALIVE mud_BackgroundMode_None() {
		return mud::BackgroundMode::None;
	}
	mud::BackgroundMode EMSCRIPTEN_KEEPALIVE mud_BackgroundMode_Panorama() {
		return mud::BackgroundMode::Panorama;
	}
	mud::BackgroundMode EMSCRIPTEN_KEEPALIVE mud_BackgroundMode_Radiance() {
		return mud::BackgroundMode::Radiance;
	}
	mud::BackgroundMode EMSCRIPTEN_KEEPALIVE mud_BackgroundMode_Custom() {
		return mud::BackgroundMode::Custom;
	}
	// BlendMode
	mud::BlendMode EMSCRIPTEN_KEEPALIVE mud_BlendMode_Mix() {
		return mud::BlendMode::Mix;
	}
	mud::BlendMode EMSCRIPTEN_KEEPALIVE mud_BlendMode_Add() {
		return mud::BlendMode::Add;
	}
	mud::BlendMode EMSCRIPTEN_KEEPALIVE mud_BlendMode_Sub() {
		return mud::BlendMode::Sub;
	}
	mud::BlendMode EMSCRIPTEN_KEEPALIVE mud_BlendMode_Mul() {
		return mud::BlendMode::Mul;
	}
	mud::BlendMode EMSCRIPTEN_KEEPALIVE mud_BlendMode_Normal() {
		return mud::BlendMode::Normal;
	}
	mud::BlendMode EMSCRIPTEN_KEEPALIVE mud_BlendMode_Alpha() {
		return mud::BlendMode::Alpha;
	}
	// CullMode
	mud::CullMode EMSCRIPTEN_KEEPALIVE mud_CullMode_None() {
		return mud::CullMode::None;
	}
	mud::CullMode EMSCRIPTEN_KEEPALIVE mud_CullMode_Front() {
		return mud::CullMode::Front;
	}
	mud::CullMode EMSCRIPTEN_KEEPALIVE mud_CullMode_Back() {
		return mud::CullMode::Back;
	}
	// DepthDraw
	mud::DepthDraw EMSCRIPTEN_KEEPALIVE mud_DepthDraw_Enabled() {
		return mud::DepthDraw::Enabled;
	}
	mud::DepthDraw EMSCRIPTEN_KEEPALIVE mud_DepthDraw_Disabled() {
		return mud::DepthDraw::Disabled;
	}
	// DepthTest
	mud::DepthTest EMSCRIPTEN_KEEPALIVE mud_DepthTest_Enabled() {
		return mud::DepthTest::Enabled;
	}
	mud::DepthTest EMSCRIPTEN_KEEPALIVE mud_DepthTest_Disabled() {
		return mud::DepthTest::Disabled;
	}
	// EmitterFlow
	mud::EmitterFlow EMSCRIPTEN_KEEPALIVE mud_EmitterFlow_Outward() {
		return mud::EmitterFlow::Outward;
	}
	mud::EmitterFlow EMSCRIPTEN_KEEPALIVE mud_EmitterFlow_Absolute() {
		return mud::EmitterFlow::Absolute;
	}
	// Interpolation
	mud::Interpolation EMSCRIPTEN_KEEPALIVE mud_Interpolation_Nearest() {
		return mud::Interpolation::Nearest;
	}
	mud::Interpolation EMSCRIPTEN_KEEPALIVE mud_Interpolation_Linear() {
		return mud::Interpolation::Linear;
	}
	mud::Interpolation EMSCRIPTEN_KEEPALIVE mud_Interpolation_Cubic() {
		return mud::Interpolation::Cubic;
	}
	// IsometricAngle
	mud::IsometricAngle EMSCRIPTEN_KEEPALIVE mud_IsometricAngle_NORTH() {
		return mud::NORTH;
	}
	mud::IsometricAngle EMSCRIPTEN_KEEPALIVE mud_IsometricAngle_SOUTH() {
		return mud::SOUTH;
	}
	mud::IsometricAngle EMSCRIPTEN_KEEPALIVE mud_IsometricAngle_EAST() {
		return mud::EAST;
	}
	mud::IsometricAngle EMSCRIPTEN_KEEPALIVE mud_IsometricAngle_WEST() {
		return mud::WEST;
	}
	// ItemShadow
	mud::ItemShadow EMSCRIPTEN_KEEPALIVE mud_ItemShadow_Default() {
		return mud::ItemShadow::Default;
	}
	mud::ItemShadow EMSCRIPTEN_KEEPALIVE mud_ItemShadow_DoubleSided() {
		return mud::ItemShadow::DoubleSided;
	}
	// LightType
	mud::LightType EMSCRIPTEN_KEEPALIVE mud_LightType_Direct() {
		return mud::LightType::Direct;
	}
	mud::LightType EMSCRIPTEN_KEEPALIVE mud_LightType_Point() {
		return mud::LightType::Point;
	}
	mud::LightType EMSCRIPTEN_KEEPALIVE mud_LightType_Spot() {
		return mud::LightType::Spot;
	}
	mud::LightType EMSCRIPTEN_KEEPALIVE mud_LightType_Count() {
		return mud::LightType::Count;
	}
	// Lighting
	mud::Lighting EMSCRIPTEN_KEEPALIVE mud_Lighting_None() {
		return mud::Lighting::None;
	}
	mud::Lighting EMSCRIPTEN_KEEPALIVE mud_Lighting_Clustered() {
		return mud::Lighting::Clustered;
	}
	mud::Lighting EMSCRIPTEN_KEEPALIVE mud_Lighting_Deferred() {
		return mud::Lighting::Deferred;
	}
	mud::Lighting EMSCRIPTEN_KEEPALIVE mud_Lighting_VoxelGI() {
		return mud::Lighting::VoxelGI;
	}
	// MSAA
	mud::MSAA EMSCRIPTEN_KEEPALIVE mud_MSAA_Disabled() {
		return mud::MSAA::Disabled;
	}
	mud::MSAA EMSCRIPTEN_KEEPALIVE mud_MSAA_X2() {
		return mud::MSAA::X2;
	}
	mud::MSAA EMSCRIPTEN_KEEPALIVE mud_MSAA_X4() {
		return mud::MSAA::X4;
	}
	mud::MSAA EMSCRIPTEN_KEEPALIVE mud_MSAA_X8() {
		return mud::MSAA::X8;
	}
	mud::MSAA EMSCRIPTEN_KEEPALIVE mud_MSAA_X16() {
		return mud::MSAA::X16;
	}
	// MaterialFlag
	mud::MaterialFlag EMSCRIPTEN_KEEPALIVE mud_MaterialFlag_TriplanarUV1() {
		return mud::MaterialFlag::TriplanarUV1;
	}
	mud::MaterialFlag EMSCRIPTEN_KEEPALIVE mud_MaterialFlag_TriplanarUV2() {
		return mud::MaterialFlag::TriplanarUV2;
	}
	mud::MaterialFlag EMSCRIPTEN_KEEPALIVE mud_MaterialFlag_Count() {
		return mud::MaterialFlag::Count;
	}
	// ModelFormat
	mud::ModelFormat EMSCRIPTEN_KEEPALIVE mud_ModelFormat_obj() {
		return mud::ModelFormat::obj;
	}
	mud::ModelFormat EMSCRIPTEN_KEEPALIVE mud_ModelFormat_gltf() {
		return mud::ModelFormat::gltf;
	}
	mud::ModelFormat EMSCRIPTEN_KEEPALIVE mud_ModelFormat_Count() {
		return mud::ModelFormat::Count;
	}
	// Month
	mud::Month EMSCRIPTEN_KEEPALIVE mud_Month_January() {
		return mud::Month::January;
	}
	mud::Month EMSCRIPTEN_KEEPALIVE mud_Month_February() {
		return mud::Month::February;
	}
	mud::Month EMSCRIPTEN_KEEPALIVE mud_Month_March() {
		return mud::Month::March;
	}
	mud::Month EMSCRIPTEN_KEEPALIVE mud_Month_April() {
		return mud::Month::April;
	}
	mud::Month EMSCRIPTEN_KEEPALIVE mud_Month_May() {
		return mud::Month::May;
	}
	mud::Month EMSCRIPTEN_KEEPALIVE mud_Month_June() {
		return mud::Month::June;
	}
	mud::Month EMSCRIPTEN_KEEPALIVE mud_Month_July() {
		return mud::Month::July;
	}
	mud::Month EMSCRIPTEN_KEEPALIVE mud_Month_August() {
		return mud::Month::August;
	}
	mud::Month EMSCRIPTEN_KEEPALIVE mud_Month_September() {
		return mud::Month::September;
	}
	mud::Month EMSCRIPTEN_KEEPALIVE mud_Month_October() {
		return mud::Month::October;
	}
	mud::Month EMSCRIPTEN_KEEPALIVE mud_Month_November() {
		return mud::Month::November;
	}
	mud::Month EMSCRIPTEN_KEEPALIVE mud_Month_December() {
		return mud::Month::December;
	}
	// PbrDiffuseMode
	mud::PbrDiffuseMode EMSCRIPTEN_KEEPALIVE mud_PbrDiffuseMode_Lambert() {
		return mud::PbrDiffuseMode::Lambert;
	}
	mud::PbrDiffuseMode EMSCRIPTEN_KEEPALIVE mud_PbrDiffuseMode_LambertHalf() {
		return mud::PbrDiffuseMode::LambertHalf;
	}
	mud::PbrDiffuseMode EMSCRIPTEN_KEEPALIVE mud_PbrDiffuseMode_OrenNayar() {
		return mud::PbrDiffuseMode::OrenNayar;
	}
	mud::PbrDiffuseMode EMSCRIPTEN_KEEPALIVE mud_PbrDiffuseMode_Burley() {
		return mud::PbrDiffuseMode::Burley;
	}
	mud::PbrDiffuseMode EMSCRIPTEN_KEEPALIVE mud_PbrDiffuseMode_Toon() {
		return mud::PbrDiffuseMode::Toon;
	}
	// PbrSpecularMode
	mud::PbrSpecularMode EMSCRIPTEN_KEEPALIVE mud_PbrSpecularMode_SchlickGGX() {
		return mud::PbrSpecularMode::SchlickGGX;
	}
	mud::PbrSpecularMode EMSCRIPTEN_KEEPALIVE mud_PbrSpecularMode_Blinn() {
		return mud::PbrSpecularMode::Blinn;
	}
	mud::PbrSpecularMode EMSCRIPTEN_KEEPALIVE mud_PbrSpecularMode_Phong() {
		return mud::PbrSpecularMode::Phong;
	}
	mud::PbrSpecularMode EMSCRIPTEN_KEEPALIVE mud_PbrSpecularMode_Toon() {
		return mud::PbrSpecularMode::Toon;
	}
	mud::PbrSpecularMode EMSCRIPTEN_KEEPALIVE mud_PbrSpecularMode_Disabled() {
		return mud::PbrSpecularMode::Disabled;
	}
	// ShaderType
	mud::ShaderType EMSCRIPTEN_KEEPALIVE mud_ShaderType_Compute() {
		return mud::ShaderType::Compute;
	}
	mud::ShaderType EMSCRIPTEN_KEEPALIVE mud_ShaderType_Fragment() {
		return mud::ShaderType::Fragment;
	}
	mud::ShaderType EMSCRIPTEN_KEEPALIVE mud_ShaderType_Geometry() {
		return mud::ShaderType::Geometry;
	}
	mud::ShaderType EMSCRIPTEN_KEEPALIVE mud_ShaderType_Vertex() {
		return mud::ShaderType::Vertex;
	}
	mud::ShaderType EMSCRIPTEN_KEEPALIVE mud_ShaderType_Count() {
		return mud::ShaderType::Count;
	}
	// Shading
	mud::Shading EMSCRIPTEN_KEEPALIVE mud_Shading_Wireframe() {
		return mud::Shading::Wireframe;
	}
	mud::Shading EMSCRIPTEN_KEEPALIVE mud_Shading_Unshaded() {
		return mud::Shading::Unshaded;
	}
	mud::Shading EMSCRIPTEN_KEEPALIVE mud_Shading_Shaded() {
		return mud::Shading::Shaded;
	}
	mud::Shading EMSCRIPTEN_KEEPALIVE mud_Shading_Volume() {
		return mud::Shading::Volume;
	}
	mud::Shading EMSCRIPTEN_KEEPALIVE mud_Shading_Voxels() {
		return mud::Shading::Voxels;
	}
	mud::Shading EMSCRIPTEN_KEEPALIVE mud_Shading_Lightmap() {
		return mud::Shading::Lightmap;
	}
	mud::Shading EMSCRIPTEN_KEEPALIVE mud_Shading_Clear() {
		return mud::Shading::Clear;
	}
	mud::Shading EMSCRIPTEN_KEEPALIVE mud_Shading_Count() {
		return mud::Shading::Count;
	}
	// ShadowFlags
	mud::ShadowFlags EMSCRIPTEN_KEEPALIVE mud_ShadowFlags_CSM_Stabilize() {
		return mud::CSM_Stabilize;
	}
	mud::ShadowFlags EMSCRIPTEN_KEEPALIVE mud_ShadowFlags_CSM_Optimize() {
		return mud::CSM_Optimize;
	}
	mud::ShadowFlags EMSCRIPTEN_KEEPALIVE mud_ShadowFlags_CSM_BlendSplits() {
		return mud::CSM_BlendSplits;
	}
	// TextureChannel
	mud::TextureChannel EMSCRIPTEN_KEEPALIVE mud_TextureChannel_Red() {
		return mud::TextureChannel::Red;
	}
	mud::TextureChannel EMSCRIPTEN_KEEPALIVE mud_TextureChannel_Green() {
		return mud::TextureChannel::Green;
	}
	mud::TextureChannel EMSCRIPTEN_KEEPALIVE mud_TextureChannel_Blue() {
		return mud::TextureChannel::Blue;
	}
	mud::TextureChannel EMSCRIPTEN_KEEPALIVE mud_TextureChannel_Alpha() {
		return mud::TextureChannel::Alpha;
	}
	mud::TextureChannel EMSCRIPTEN_KEEPALIVE mud_TextureChannel_All() {
		return mud::TextureChannel::All;
	}
	// TextureHint
	mud::TextureHint EMSCRIPTEN_KEEPALIVE mud_TextureHint_Black() {
		return mud::TextureHint::Black;
	}
	mud::TextureHint EMSCRIPTEN_KEEPALIVE mud_TextureHint_White() {
		return mud::TextureHint::White;
	}
	mud::TextureHint EMSCRIPTEN_KEEPALIVE mud_TextureHint_Normal() {
		return mud::TextureHint::Normal;
	}
	// TextureSampler
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE mud_TextureSampler_Source0() {
		return mud::TextureSampler::Source0;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE mud_TextureSampler_Source1() {
		return mud::TextureSampler::Source1;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE mud_TextureSampler_Source2() {
		return mud::TextureSampler::Source2;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE mud_TextureSampler_Source3() {
		return mud::TextureSampler::Source3;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE mud_TextureSampler_SourceDepth() {
		return mud::TextureSampler::SourceDepth;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE mud_TextureSampler_Color() {
		return mud::TextureSampler::Color;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE mud_TextureSampler_Albedo() {
		return mud::TextureSampler::Albedo;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE mud_TextureSampler_Metallic() {
		return mud::TextureSampler::Metallic;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE mud_TextureSampler_Roughness() {
		return mud::TextureSampler::Roughness;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE mud_TextureSampler_Emissive() {
		return mud::TextureSampler::Emissive;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE mud_TextureSampler_Normal() {
		return mud::TextureSampler::Normal;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE mud_TextureSampler_AO() {
		return mud::TextureSampler::AO;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE mud_TextureSampler_Depth() {
		return mud::TextureSampler::Depth;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE mud_TextureSampler_Skeleton() {
		return mud::TextureSampler::Skeleton;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE mud_TextureSampler_ShadowCSM() {
		return mud::TextureSampler::ShadowCSM;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE mud_TextureSampler_ShadowAtlas() {
		return mud::TextureSampler::ShadowAtlas;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE mud_TextureSampler_Radiance() {
		return mud::TextureSampler::Radiance;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE mud_TextureSampler_ReflectionProbe() {
		return mud::TextureSampler::ReflectionProbe;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE mud_TextureSampler_GIProbe() {
		return mud::TextureSampler::GIProbe;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE mud_TextureSampler_Lights() {
		return mud::TextureSampler::Lights;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE mud_TextureSampler_Clusters() {
		return mud::TextureSampler::Clusters;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE mud_TextureSampler_LightRecords() {
		return mud::TextureSampler::LightRecords;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE mud_TextureSampler_Lightmap() {
		return mud::TextureSampler::Lightmap;
	}
	
}


