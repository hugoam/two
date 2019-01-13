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
	void EMSCRIPTEN_KEEPALIVE Animated_advance_1(mud::Animated* self, float time) {
		self->advance(time);
	}
	void EMSCRIPTEN_KEEPALIVE Animated_next_animation_0(mud::Animated* self) {
		self->next_animation();
	}
	void EMSCRIPTEN_KEEPALIVE Animated_pause_0(mud::Animated* self) {
		self->pause();
	}
	void EMSCRIPTEN_KEEPALIVE Animated_play_2(mud::Animated* self, const mud::Animation* animation, bool loop) {
		self->play(*animation, loop);
	}
	void EMSCRIPTEN_KEEPALIVE Animated_play_3(mud::Animated* self, const mud::Animation* animation, bool loop, float blend) {
		self->play(*animation, loop, blend);
	}
	void EMSCRIPTEN_KEEPALIVE Animated_play_4(mud::Animated* self, const mud::Animation* animation, bool loop, float blend, float speed) {
		self->play(*animation, loop, blend, speed);
	}
	void EMSCRIPTEN_KEEPALIVE Animated_play_5(mud::Animated* self, const mud::Animation* animation, bool loop, float blend, float speed, bool transient) {
		self->play(*animation, loop, blend, speed, transient);
	}
	const char* EMSCRIPTEN_KEEPALIVE Animated_playing_0(mud::Animated* self) {
		return self->playing().c_str();
	}
	void EMSCRIPTEN_KEEPALIVE Animated_seek_1(mud::Animated* self, float time) {
		self->seek(time);
	}
	void EMSCRIPTEN_KEEPALIVE Animated_start_2(mud::Animated* self, const char* animation, bool loop) {
		self->start(animation, loop);
	}
	void EMSCRIPTEN_KEEPALIVE Animated_start_3(mud::Animated* self, const char* animation, bool loop, float blend) {
		self->start(animation, loop, blend);
	}
	void EMSCRIPTEN_KEEPALIVE Animated_start_4(mud::Animated* self, const char* animation, bool loop, float blend, float speed) {
		self->start(animation, loop, blend, speed);
	}
	void EMSCRIPTEN_KEEPALIVE Animated_start_5(mud::Animated* self, const char* animation, bool loop, float blend, float speed, bool transient) {
		self->start(animation, loop, blend, speed, transient);
	}
	void EMSCRIPTEN_KEEPALIVE Animated_stop_0(mud::Animated* self) {
		self->stop();
	}
	bool EMSCRIPTEN_KEEPALIVE Animated_get_active(mud::Animated* self) {
		return self->m_active;
	}
	void EMSCRIPTEN_KEEPALIVE Animated_set_active(mud::Animated* self, bool active) {
		self->m_active = active;
	}
	float EMSCRIPTEN_KEEPALIVE Animated_get_speed_scale(mud::Animated* self) {
		return self->m_speed_scale;
	}
	void EMSCRIPTEN_KEEPALIVE Animated_set_speed_scale(mud::Animated* self, float speed_scale) {
		self->m_speed_scale = speed_scale;
	}
	float EMSCRIPTEN_KEEPALIVE Animated_get_default_blend_time(mud::Animated* self) {
		return self->m_default_blend_time;
	}
	void EMSCRIPTEN_KEEPALIVE Animated_set_default_blend_time(mud::Animated* self, float default_blend_time) {
		self->m_default_blend_time = default_blend_time;
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
	const char* EMSCRIPTEN_KEEPALIVE Animation_get_name(mud::Animation* self) {
		return self->m_name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE Animation_set_name(mud::Animation* self, const char* name) {
		self->m_name = name;
	}
	float EMSCRIPTEN_KEEPALIVE Animation_get_length(mud::Animation* self) {
		return self->m_length;
	}
	void EMSCRIPTEN_KEEPALIVE Animation_set_length(mud::Animation* self, float length) {
		self->m_length = length;
	}
	float EMSCRIPTEN_KEEPALIVE Animation_get_step(mud::Animation* self) {
		return self->m_step;
	}
	void EMSCRIPTEN_KEEPALIVE Animation_set_step(mud::Animation* self, float step) {
		self->m_step = step;
	}
	void EMSCRIPTEN_KEEPALIVE Animation___destroy__(mud::Animation* self) {
		delete self;
	}
	// AnimationPlay
	mud::AnimationPlay* EMSCRIPTEN_KEEPALIVE AnimationPlay_AnimationPlay_0() {
		return new mud::AnimationPlay();
	}
	const mud::Animation* EMSCRIPTEN_KEEPALIVE AnimationPlay_get_animation(mud::AnimationPlay* self) {
		return self->m_animation;
	}
	void EMSCRIPTEN_KEEPALIVE AnimationPlay_set_animation(mud::AnimationPlay* self, const mud::Animation* animation) {
		self->m_animation = animation;
	}
	bool EMSCRIPTEN_KEEPALIVE AnimationPlay_get_loop(mud::AnimationPlay* self) {
		return self->m_loop;
	}
	void EMSCRIPTEN_KEEPALIVE AnimationPlay_set_loop(mud::AnimationPlay* self, bool loop) {
		self->m_loop = loop;
	}
	float EMSCRIPTEN_KEEPALIVE AnimationPlay_get_speed(mud::AnimationPlay* self) {
		return self->m_speed;
	}
	void EMSCRIPTEN_KEEPALIVE AnimationPlay_set_speed(mud::AnimationPlay* self, float speed) {
		self->m_speed = speed;
	}
	bool EMSCRIPTEN_KEEPALIVE AnimationPlay_get_transient(mud::AnimationPlay* self) {
		return self->m_transient;
	}
	void EMSCRIPTEN_KEEPALIVE AnimationPlay_set_transient(mud::AnimationPlay* self, bool transient) {
		self->m_transient = transient;
	}
	float EMSCRIPTEN_KEEPALIVE AnimationPlay_get_fadeout(mud::AnimationPlay* self) {
		return self->m_fadeout;
	}
	void EMSCRIPTEN_KEEPALIVE AnimationPlay_set_fadeout(mud::AnimationPlay* self, float fadeout) {
		self->m_fadeout = fadeout;
	}
	float EMSCRIPTEN_KEEPALIVE AnimationPlay_get_fadeout_left(mud::AnimationPlay* self) {
		return self->m_fadeout_left;
	}
	void EMSCRIPTEN_KEEPALIVE AnimationPlay_set_fadeout_left(mud::AnimationPlay* self, float fadeout_left) {
		self->m_fadeout_left = fadeout_left;
	}
	float EMSCRIPTEN_KEEPALIVE AnimationPlay_get_cursor(mud::AnimationPlay* self) {
		return self->m_cursor;
	}
	void EMSCRIPTEN_KEEPALIVE AnimationPlay_set_cursor(mud::AnimationPlay* self, float cursor) {
		self->m_cursor = cursor;
	}
	bool EMSCRIPTEN_KEEPALIVE AnimationPlay_get_ended(mud::AnimationPlay* self) {
		return self->m_ended;
	}
	void EMSCRIPTEN_KEEPALIVE AnimationPlay_set_ended(mud::AnimationPlay* self, bool ended) {
		self->m_ended = ended;
	}
	void EMSCRIPTEN_KEEPALIVE AnimationPlay___destroy__(mud::AnimationPlay* self) {
		delete self;
	}
	// AnimationTrack
	mud::Animation* EMSCRIPTEN_KEEPALIVE AnimationTrack_get_animation(mud::AnimationTrack* self) {
		return self->m_animation;
	}
	void EMSCRIPTEN_KEEPALIVE AnimationTrack_set_animation(mud::AnimationTrack* self, mud::Animation* animation) {
		self->m_animation = animation;
	}
	size_t EMSCRIPTEN_KEEPALIVE AnimationTrack_get_node(mud::AnimationTrack* self) {
		return self->m_node;
	}
	void EMSCRIPTEN_KEEPALIVE AnimationTrack_set_node(mud::AnimationTrack* self, size_t node) {
		self->m_node = node;
	}
	const char* EMSCRIPTEN_KEEPALIVE AnimationTrack_get_node_name(mud::AnimationTrack* self) {
		return self->m_node_name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE AnimationTrack_set_node_name(mud::AnimationTrack* self, const char* node_name) {
		self->m_node_name = node_name;
	}
	mud::AnimationTarget EMSCRIPTEN_KEEPALIVE AnimationTrack_get_target(mud::AnimationTrack* self) {
		return self->m_target;
	}
	void EMSCRIPTEN_KEEPALIVE AnimationTrack_set_target(mud::AnimationTrack* self, mud::AnimationTarget target) {
		self->m_target = target;
	}
	mud::Type* EMSCRIPTEN_KEEPALIVE AnimationTrack_get_value_type(mud::AnimationTrack* self) {
		return self->m_value_type;
	}
	void EMSCRIPTEN_KEEPALIVE AnimationTrack_set_value_type(mud::AnimationTrack* self, mud::Type* value_type) {
		self->m_value_type = value_type;
	}
	float EMSCRIPTEN_KEEPALIVE AnimationTrack_get_length(mud::AnimationTrack* self) {
		return self->m_length;
	}
	void EMSCRIPTEN_KEEPALIVE AnimationTrack_set_length(mud::AnimationTrack* self, float length) {
		self->m_length = length;
	}
	mud::Interpolation EMSCRIPTEN_KEEPALIVE AnimationTrack_get_interpolation(mud::AnimationTrack* self) {
		return self->m_interpolation;
	}
	void EMSCRIPTEN_KEEPALIVE AnimationTrack_set_interpolation(mud::AnimationTrack* self, mud::Interpolation interpolation) {
		self->m_interpolation = interpolation;
	}
	void EMSCRIPTEN_KEEPALIVE AnimationTrack___destroy__(mud::AnimationTrack* self) {
		delete self;
	}
	// Background
	mud::Background* EMSCRIPTEN_KEEPALIVE Background_Background_0() {
		return new mud::Background();
	}
	mud::BackgroundMode EMSCRIPTEN_KEEPALIVE Background_get_mode(mud::Background* self) {
		return self->m_mode;
	}
	void EMSCRIPTEN_KEEPALIVE Background_set_mode(mud::Background* self, mud::BackgroundMode mode) {
		self->m_mode = mode;
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE Background_get_colour(mud::Background* self) {
		static mud::Colour temp;
		return (temp = self->m_colour, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Background_set_colour(mud::Background* self, mud::Colour* colour) {
		self->m_colour = *colour;
	}
	mud::Program* EMSCRIPTEN_KEEPALIVE Background_get_custoprogram(mud::Background* self) {
		return self->m_custom_program;
	}
	void EMSCRIPTEN_KEEPALIVE Background_set_custoprogram(mud::Background* self, mud::Program* custoprogram) {
		self->m_custom_program = custoprogram;
	}
	void EMSCRIPTEN_KEEPALIVE Background___destroy__(mud::Background* self) {
		delete self;
	}
	// BaseMaterialBlock
	mud::BaseMaterialBlock* EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_BaseMaterialBlock_0() {
		return new mud::BaseMaterialBlock();
	}
	mud::BlendMode EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_get_blend_mode(mud::BaseMaterialBlock* self) {
		return self->m_blend_mode;
	}
	void EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_set_blend_mode(mud::BaseMaterialBlock* self, mud::BlendMode blend_mode) {
		self->m_blend_mode = blend_mode;
	}
	mud::CullMode EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_get_cull_mode(mud::BaseMaterialBlock* self) {
		return self->m_cull_mode;
	}
	void EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_set_cull_mode(mud::BaseMaterialBlock* self, mud::CullMode cull_mode) {
		self->m_cull_mode = cull_mode;
	}
	mud::DepthDraw EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_get_depth_draw_mode(mud::BaseMaterialBlock* self) {
		return self->m_depth_draw_mode;
	}
	void EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_set_depth_draw_mode(mud::BaseMaterialBlock* self, mud::DepthDraw depth_draw_mode) {
		self->m_depth_draw_mode = depth_draw_mode;
	}
	mud::DepthTest EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_get_depth_test(mud::BaseMaterialBlock* self) {
		return self->m_depth_test;
	}
	void EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_set_depth_test(mud::BaseMaterialBlock* self, mud::DepthTest depth_test) {
		self->m_depth_test = depth_test;
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_get_uv0_scale(mud::BaseMaterialBlock* self) {
		static mud::vec2 temp;
		return (temp = self->m_uv0_scale, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_set_uv0_scale(mud::BaseMaterialBlock* self, mud::vec2* uv0_scale) {
		self->m_uv0_scale = *uv0_scale;
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_get_uv0_offset(mud::BaseMaterialBlock* self) {
		static mud::vec2 temp;
		return (temp = self->m_uv0_offset, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_set_uv0_offset(mud::BaseMaterialBlock* self, mud::vec2* uv0_offset) {
		self->m_uv0_offset = *uv0_offset;
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_get_uv1_scale(mud::BaseMaterialBlock* self) {
		static mud::vec2 temp;
		return (temp = self->m_uv1_scale, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_set_uv1_scale(mud::BaseMaterialBlock* self, mud::vec2* uv1_scale) {
		self->m_uv1_scale = *uv1_scale;
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_get_uv1_offset(mud::BaseMaterialBlock* self) {
		static mud::vec2 temp;
		return (temp = self->m_uv1_offset, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_set_uv1_offset(mud::BaseMaterialBlock* self, mud::vec2* uv1_offset) {
		self->m_uv1_offset = *uv1_offset;
	}
	bool EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_get_is_alpha(mud::BaseMaterialBlock* self) {
		return self->m_is_alpha;
	}
	void EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_set_is_alpha(mud::BaseMaterialBlock* self, bool is_alpha) {
		self->m_is_alpha = is_alpha;
	}
	bool EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_get_screen_filter(mud::BaseMaterialBlock* self) {
		return self->m_screen_filter;
	}
	void EMSCRIPTEN_KEEPALIVE BaseMaterialBlock_set_screen_filter(mud::BaseMaterialBlock* self, bool screen_filter) {
		self->m_screen_filter = screen_filter;
	}
	void EMSCRIPTEN_KEEPALIVE BaseMaterialBlock___destroy__(mud::BaseMaterialBlock* self) {
		delete self;
	}
	// Bone
	mud::Bone* EMSCRIPTEN_KEEPALIVE Bone_Bone_0() {
		return new mud::Bone();
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE Bone_get_position(mud::Bone* self) {
		static mud::vec3 temp;
		return (temp = self->m_position, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Bone_set_position(mud::Bone* self, mud::vec3* position) {
		self->m_position = *position;
	}
	mud::quat* EMSCRIPTEN_KEEPALIVE Bone_get_rotation(mud::Bone* self) {
		static mud::quat temp;
		return (temp = self->m_rotation, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Bone_set_rotation(mud::Bone* self, mud::quat* rotation) {
		self->m_rotation = *rotation;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE Bone_get_scale(mud::Bone* self) {
		static mud::vec3 temp;
		return (temp = self->m_scale, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Bone_set_scale(mud::Bone* self, mud::vec3* scale) {
		self->m_scale = *scale;
	}
	void EMSCRIPTEN_KEEPALIVE Bone___destroy__(mud::Bone* self) {
		delete self;
	}
	// Camera
	mud::vec3* EMSCRIPTEN_KEEPALIVE Camera_get_eye(mud::Camera* self) {
		static mud::vec3 temp;
		return (temp = self->m_eye, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Camera_set_eye(mud::Camera* self, mud::vec3* eye) {
		self->m_eye = *eye;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE Camera_get_target(mud::Camera* self) {
		static mud::vec3 temp;
		return (temp = self->m_target, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Camera_set_target(mud::Camera* self, mud::vec3* target) {
		self->m_target = *target;
	}
	mud::mat4* EMSCRIPTEN_KEEPALIVE Camera_get_transform(mud::Camera* self) {
		static mud::mat4 temp;
		return (temp = self->m_transform, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Camera_set_transform(mud::Camera* self, mud::mat4* transform) {
		self->m_transform = *transform;
	}
	mud::mat4* EMSCRIPTEN_KEEPALIVE Camera_get_projection(mud::Camera* self) {
		static mud::mat4 temp;
		return (temp = self->m_projection, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Camera_set_projection(mud::Camera* self, mud::mat4* projection) {
		self->m_projection = *projection;
	}
	float EMSCRIPTEN_KEEPALIVE Camera_get_fov(mud::Camera* self) {
		return self->m_fov;
	}
	void EMSCRIPTEN_KEEPALIVE Camera_set_fov(mud::Camera* self, float fov) {
		self->m_fov = fov;
	}
	float EMSCRIPTEN_KEEPALIVE Camera_get_aspect(mud::Camera* self) {
		return self->m_aspect;
	}
	void EMSCRIPTEN_KEEPALIVE Camera_set_aspect(mud::Camera* self, float aspect) {
		self->m_aspect = aspect;
	}
	float EMSCRIPTEN_KEEPALIVE Camera_get_near(mud::Camera* self) {
		return self->m_near;
	}
	void EMSCRIPTEN_KEEPALIVE Camera_set_near(mud::Camera* self, float near) {
		self->m_near = near;
	}
	float EMSCRIPTEN_KEEPALIVE Camera_get_far(mud::Camera* self) {
		return self->m_far;
	}
	void EMSCRIPTEN_KEEPALIVE Camera_set_far(mud::Camera* self, float far) {
		self->m_far = far;
	}
	bool EMSCRIPTEN_KEEPALIVE Camera_get_orthographic(mud::Camera* self) {
		return self->m_orthographic;
	}
	void EMSCRIPTEN_KEEPALIVE Camera_set_orthographic(mud::Camera* self, bool orthographic) {
		self->m_orthographic = orthographic;
	}
	float EMSCRIPTEN_KEEPALIVE Camera_get_height(mud::Camera* self) {
		return self->m_height;
	}
	void EMSCRIPTEN_KEEPALIVE Camera_set_height(mud::Camera* self, float height) {
		self->m_height = height;
	}
	bool EMSCRIPTEN_KEEPALIVE Camera_get_optimize_ends(mud::Camera* self) {
		return self->m_optimize_ends;
	}
	void EMSCRIPTEN_KEEPALIVE Camera_set_optimize_ends(mud::Camera* self, bool optimize_ends) {
		self->m_optimize_ends = optimize_ends;
	}
	bool EMSCRIPTEN_KEEPALIVE Camera_get_clustered(mud::Camera* self) {
		return self->m_clustered;
	}
	void EMSCRIPTEN_KEEPALIVE Camera_set_clustered(mud::Camera* self, bool clustered) {
		self->m_clustered = clustered;
	}
	mud::vec4* EMSCRIPTEN_KEEPALIVE Camera_get_lod_offsets(mud::Camera* self) {
		static mud::vec4 temp;
		return (temp = self->m_lod_offsets, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Camera_set_lod_offsets(mud::Camera* self, mud::vec4* lod_offsets) {
		self->m_lod_offsets = *lod_offsets;
	}
	void EMSCRIPTEN_KEEPALIVE Camera___destroy__(mud::Camera* self) {
		delete self;
	}
	// Culler
	mud::Viewport* EMSCRIPTEN_KEEPALIVE Culler_get_viewport(mud::Culler* self) {
		return self->m_viewport;
	}
	void EMSCRIPTEN_KEEPALIVE Culler_set_viewport(mud::Culler* self, mud::Viewport* viewport) {
		self->m_viewport = viewport;
	}
	void EMSCRIPTEN_KEEPALIVE Culler___destroy__(mud::Culler* self) {
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
	mud::Background* EMSCRIPTEN_KEEPALIVE Environment_get_background(mud::Environment* self) {
		static mud::Background temp;
		return (temp = self->m_background, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Environment_set_background(mud::Environment* self, mud::Background* background) {
		self->m_background = *background;
	}
	mud::Radiance* EMSCRIPTEN_KEEPALIVE Environment_get_radiance(mud::Environment* self) {
		static mud::Radiance temp;
		return (temp = self->m_radiance, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Environment_set_radiance(mud::Environment* self, mud::Radiance* radiance) {
		self->m_radiance = *radiance;
	}
	mud::Sun* EMSCRIPTEN_KEEPALIVE Environment_get_sun(mud::Environment* self) {
		static mud::Sun temp;
		return (temp = self->m_sun, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Environment_set_sun(mud::Environment* self, mud::Sun* sun) {
		self->m_sun = *sun;
	}
	mud::Fog* EMSCRIPTEN_KEEPALIVE Environment_get_fog(mud::Environment* self) {
		static mud::Fog temp;
		return (temp = self->m_fog, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Environment_set_fog(mud::Environment* self, mud::Fog* fog) {
		self->m_fog = *fog;
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
	void EMSCRIPTEN_KEEPALIVE Fog_set_enabled(mud::Fog* self, bool enabled) {
		self->m_enabled = enabled;
	}
	float EMSCRIPTEN_KEEPALIVE Fog_get_density(mud::Fog* self) {
		return self->m_density;
	}
	void EMSCRIPTEN_KEEPALIVE Fog_set_density(mud::Fog* self, float density) {
		self->m_density = density;
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE Fog_get_colour(mud::Fog* self) {
		static mud::Colour temp;
		return (temp = self->m_colour, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Fog_set_colour(mud::Fog* self, mud::Colour* colour) {
		self->m_colour = *colour;
	}
	bool EMSCRIPTEN_KEEPALIVE Fog_get_depth(mud::Fog* self) {
		return self->m_depth;
	}
	void EMSCRIPTEN_KEEPALIVE Fog_set_depth(mud::Fog* self, bool depth) {
		self->m_depth = depth;
	}
	float EMSCRIPTEN_KEEPALIVE Fog_get_depth_begin(mud::Fog* self) {
		return self->m_depth_begin;
	}
	void EMSCRIPTEN_KEEPALIVE Fog_set_depth_begin(mud::Fog* self, float depth_begin) {
		self->m_depth_begin = depth_begin;
	}
	float EMSCRIPTEN_KEEPALIVE Fog_get_depth_curve(mud::Fog* self) {
		return self->m_depth_curve;
	}
	void EMSCRIPTEN_KEEPALIVE Fog_set_depth_curve(mud::Fog* self, float depth_curve) {
		self->m_depth_curve = depth_curve;
	}
	bool EMSCRIPTEN_KEEPALIVE Fog_get_height(mud::Fog* self) {
		return self->m_height;
	}
	void EMSCRIPTEN_KEEPALIVE Fog_set_height(mud::Fog* self, bool height) {
		self->m_height = height;
	}
	float EMSCRIPTEN_KEEPALIVE Fog_get_height_min(mud::Fog* self) {
		return self->m_height_min;
	}
	void EMSCRIPTEN_KEEPALIVE Fog_set_height_min(mud::Fog* self, float height_min) {
		self->m_height_min = height_min;
	}
	float EMSCRIPTEN_KEEPALIVE Fog_get_height_max(mud::Fog* self) {
		return self->m_height_max;
	}
	void EMSCRIPTEN_KEEPALIVE Fog_set_height_max(mud::Fog* self, float height_max) {
		self->m_height_max = height_max;
	}
	float EMSCRIPTEN_KEEPALIVE Fog_get_height_curve(mud::Fog* self) {
		return self->m_height_curve;
	}
	void EMSCRIPTEN_KEEPALIVE Fog_set_height_curve(mud::Fog* self, float height_curve) {
		self->m_height_curve = height_curve;
	}
	bool EMSCRIPTEN_KEEPALIVE Fog_get_transmit(mud::Fog* self) {
		return self->m_transmit;
	}
	void EMSCRIPTEN_KEEPALIVE Fog_set_transmit(mud::Fog* self, bool transmit) {
		self->m_transmit = transmit;
	}
	float EMSCRIPTEN_KEEPALIVE Fog_get_transmit_curve(mud::Fog* self) {
		return self->m_transmit_curve;
	}
	void EMSCRIPTEN_KEEPALIVE Fog_set_transmit_curve(mud::Fog* self, float transmit_curve) {
		self->m_transmit_curve = transmit_curve;
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
	void EMSCRIPTEN_KEEPALIVE FresnelMaterialBlock_set_enabled(mud::FresnelMaterialBlock* self, bool enabled) {
		self->m_enabled = enabled;
	}
	float EMSCRIPTEN_KEEPALIVE FresnelMaterialBlock_get_fresnel_scale(mud::FresnelMaterialBlock* self) {
		return self->m_fresnel_scale;
	}
	void EMSCRIPTEN_KEEPALIVE FresnelMaterialBlock_set_fresnel_scale(mud::FresnelMaterialBlock* self, float fresnel_scale) {
		self->m_fresnel_scale = fresnel_scale;
	}
	float EMSCRIPTEN_KEEPALIVE FresnelMaterialBlock_get_fresnel_bias(mud::FresnelMaterialBlock* self) {
		return self->m_fresnel_bias;
	}
	void EMSCRIPTEN_KEEPALIVE FresnelMaterialBlock_set_fresnel_bias(mud::FresnelMaterialBlock* self, float fresnel_bias) {
		self->m_fresnel_bias = fresnel_bias;
	}
	float EMSCRIPTEN_KEEPALIVE FresnelMaterialBlock_get_fresnel_power(mud::FresnelMaterialBlock* self) {
		return self->m_fresnel_power;
	}
	void EMSCRIPTEN_KEEPALIVE FresnelMaterialBlock_set_fresnel_power(mud::FresnelMaterialBlock* self, float fresnel_power) {
		self->m_fresnel_power = fresnel_power;
	}
	void EMSCRIPTEN_KEEPALIVE FresnelMaterialBlock___destroy__(mud::FresnelMaterialBlock* self) {
		delete self;
	}
	// Frustum
	float EMSCRIPTEN_KEEPALIVE Frustum_get_fov(mud::Frustum* self) {
		return self->m_fov;
	}
	void EMSCRIPTEN_KEEPALIVE Frustum_set_fov(mud::Frustum* self, float fov) {
		self->m_fov = fov;
	}
	float EMSCRIPTEN_KEEPALIVE Frustum_get_aspect(mud::Frustum* self) {
		return self->m_aspect;
	}
	void EMSCRIPTEN_KEEPALIVE Frustum_set_aspect(mud::Frustum* self, float aspect) {
		self->m_aspect = aspect;
	}
	float EMSCRIPTEN_KEEPALIVE Frustum_get_near(mud::Frustum* self) {
		return self->m_near;
	}
	void EMSCRIPTEN_KEEPALIVE Frustum_set_near(mud::Frustum* self, float near) {
		self->m_near = near;
	}
	float EMSCRIPTEN_KEEPALIVE Frustum_get_far(mud::Frustum* self) {
		return self->m_far;
	}
	void EMSCRIPTEN_KEEPALIVE Frustum_set_far(mud::Frustum* self, float far) {
		self->m_far = far;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE Frustum_get_center(mud::Frustum* self) {
		static mud::vec3 temp;
		return (temp = self->m_center, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Frustum_set_center(mud::Frustum* self, mud::vec3* center) {
		self->m_center = *center;
	}
	float EMSCRIPTEN_KEEPALIVE Frustum_get_radius(mud::Frustum* self) {
		return self->m_radius;
	}
	void EMSCRIPTEN_KEEPALIVE Frustum_set_radius(mud::Frustum* self, float radius) {
		self->m_radius = radius;
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
	mud::Type* EMSCRIPTEN_KEEPALIVE GfxBlock_get_type(mud::GfxBlock* self) {
		return &self->m_type;
	}
	uint8_t EMSCRIPTEN_KEEPALIVE GfxBlock_get_index(mud::GfxBlock* self) {
		return self->m_index;
	}
	void EMSCRIPTEN_KEEPALIVE GfxBlock_set_index(mud::GfxBlock* self, uint8_t index) {
		self->m_index = index;
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
	mud::Material* EMSCRIPTEN_KEEPALIVE GfxSystem_debug_material_0(mud::GfxSystem* self) {
		return &self->debug_material();
	}
	mud::Material* EMSCRIPTEN_KEEPALIVE GfxSystem_fetch_image256_material_1(mud::GfxSystem* self, const mud::Image256* image) {
		return &self->fetch_image256_material(*image);
	}
	mud::Material* EMSCRIPTEN_KEEPALIVE GfxSystem_fetch_material_2(mud::GfxSystem* self, const char* name, const char* shader) {
		return &self->fetch_material(name, shader);
	}
	mud::Material* EMSCRIPTEN_KEEPALIVE GfxSystem_fetch_material_3(mud::GfxSystem* self, const char* name, const char* shader, bool builtin) {
		return &self->fetch_material(name, shader, builtin);
	}
	mud::Model* EMSCRIPTEN_KEEPALIVE GfxSystem_fetch_symbol_3(mud::GfxSystem* self, const mud::Symbol* symbol, const mud::Shape* shape, mud::DrawMode draw_mode) {
		return &self->fetch_symbol(*symbol, *shape, draw_mode);
	}
	mud::Material* EMSCRIPTEN_KEEPALIVE GfxSystem_fetch_symbol_material_2(mud::GfxSystem* self, const mud::Symbol* symbol, mud::DrawMode draw_mode) {
		return &self->fetch_symbol_material(*symbol, draw_mode);
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
	mud::ModelFormat EMSCRIPTEN_KEEPALIVE ImportConfig_get_format(mud::ImportConfig* self) {
		return self->m_format;
	}
	void EMSCRIPTEN_KEEPALIVE ImportConfig_set_format(mud::ImportConfig* self, mud::ModelFormat format) {
		self->m_format = format;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE ImportConfig_get_position(mud::ImportConfig* self) {
		static mud::vec3 temp;
		return (temp = self->m_position, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE ImportConfig_set_position(mud::ImportConfig* self, mud::vec3* position) {
		self->m_position = *position;
	}
	mud::quat* EMSCRIPTEN_KEEPALIVE ImportConfig_get_rotation(mud::ImportConfig* self) {
		static mud::quat temp;
		return (temp = self->m_rotation, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE ImportConfig_set_rotation(mud::ImportConfig* self, mud::quat* rotation) {
		self->m_rotation = *rotation;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE ImportConfig_get_scale(mud::ImportConfig* self) {
		static mud::vec3 temp;
		return (temp = self->m_scale, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE ImportConfig_set_scale(mud::ImportConfig* self, mud::vec3* scale) {
		self->m_scale = *scale;
	}
	mud::mat4* EMSCRIPTEN_KEEPALIVE ImportConfig_get_transform(mud::ImportConfig* self) {
		static mud::mat4 temp;
		return (temp = self->m_transform, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE ImportConfig_set_transform(mud::ImportConfig* self, mud::mat4* transform) {
		self->m_transform = *transform;
	}
	const char* EMSCRIPTEN_KEEPALIVE ImportConfig_get_suffix(mud::ImportConfig* self) {
		return self->m_suffix.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE ImportConfig_set_suffix(mud::ImportConfig* self, const char* suffix) {
		self->m_suffix = suffix;
	}
	bool EMSCRIPTEN_KEEPALIVE ImportConfig_get_force_reimport(mud::ImportConfig* self) {
		return self->m_force_reimport;
	}
	void EMSCRIPTEN_KEEPALIVE ImportConfig_set_force_reimport(mud::ImportConfig* self, bool force_reimport) {
		self->m_force_reimport = force_reimport;
	}
	bool EMSCRIPTEN_KEEPALIVE ImportConfig_get_cache_geometry(mud::ImportConfig* self) {
		return self->m_cache_geometry;
	}
	void EMSCRIPTEN_KEEPALIVE ImportConfig_set_cache_geometry(mud::ImportConfig* self, bool cache_geometry) {
		self->m_cache_geometry = cache_geometry;
	}
	bool EMSCRIPTEN_KEEPALIVE ImportConfig_get_optimize_geometry(mud::ImportConfig* self) {
		return self->m_optimize_geometry;
	}
	void EMSCRIPTEN_KEEPALIVE ImportConfig_set_optimize_geometry(mud::ImportConfig* self, bool optimize_geometry) {
		self->m_optimize_geometry = optimize_geometry;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE ImportConfig_get_flags(mud::ImportConfig* self) {
		return self->m_flags;
	}
	void EMSCRIPTEN_KEEPALIVE ImportConfig_set_flags(mud::ImportConfig* self, uint32_t flags) {
		self->m_flags = flags;
	}
	void EMSCRIPTEN_KEEPALIVE ImportConfig___destroy__(mud::ImportConfig* self) {
		delete self;
	}
	// Item
	mud::Node3* EMSCRIPTEN_KEEPALIVE Item_get_node(mud::Item* self) {
		return self->m_node;
	}
	void EMSCRIPTEN_KEEPALIVE Item_set_node(mud::Item* self, mud::Node3* node) {
		self->m_node = node;
	}
	mud::Model* EMSCRIPTEN_KEEPALIVE Item_get_model(mud::Item* self) {
		return self->m_model;
	}
	void EMSCRIPTEN_KEEPALIVE Item_set_model(mud::Item* self, mud::Model* model) {
		self->m_model = model;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE Item_get_flags(mud::Item* self) {
		return self->m_flags;
	}
	void EMSCRIPTEN_KEEPALIVE Item_set_flags(mud::Item* self, uint32_t flags) {
		self->m_flags = flags;
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE Item_get_colour(mud::Item* self) {
		static mud::Colour temp;
		return (temp = self->m_colour, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Item_set_colour(mud::Item* self, mud::Colour* colour) {
		self->m_colour = *colour;
	}
	mud::Material* EMSCRIPTEN_KEEPALIVE Item_get_material(mud::Item* self) {
		return self->m_material;
	}
	void EMSCRIPTEN_KEEPALIVE Item_set_material(mud::Item* self, mud::Material* material) {
		self->m_material = material;
	}
	bool EMSCRIPTEN_KEEPALIVE Item_get_visible(mud::Item* self) {
		return self->m_visible;
	}
	void EMSCRIPTEN_KEEPALIVE Item_set_visible(mud::Item* self, bool visible) {
		self->m_visible = visible;
	}
	mud::ItemShadow EMSCRIPTEN_KEEPALIVE Item_get_shadow(mud::Item* self) {
		return self->m_shadow;
	}
	void EMSCRIPTEN_KEEPALIVE Item_set_shadow(mud::Item* self, mud::ItemShadow shadow) {
		self->m_shadow = shadow;
	}
	mud::Rig* EMSCRIPTEN_KEEPALIVE Item_get_rig(mud::Item* self) {
		return self->m_rig;
	}
	void EMSCRIPTEN_KEEPALIVE Item_set_rig(mud::Item* self, mud::Rig* rig) {
		self->m_rig = rig;
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
	mud::Node3* EMSCRIPTEN_KEEPALIVE Light_get_node(mud::Light* self) {
		return &self->m_node;
	}
	mud::LightType EMSCRIPTEN_KEEPALIVE Light_get_type(mud::Light* self) {
		return self->m_type;
	}
	void EMSCRIPTEN_KEEPALIVE Light_set_type(mud::Light* self, mud::LightType type) {
		self->m_type = type;
	}
	bool EMSCRIPTEN_KEEPALIVE Light_get_visible(mud::Light* self) {
		return self->m_visible;
	}
	void EMSCRIPTEN_KEEPALIVE Light_set_visible(mud::Light* self, bool visible) {
		self->m_visible = visible;
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE Light_get_colour(mud::Light* self) {
		static mud::Colour temp;
		return (temp = self->m_colour, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Light_set_colour(mud::Light* self, mud::Colour* colour) {
		self->m_colour = *colour;
	}
	float EMSCRIPTEN_KEEPALIVE Light_get_range(mud::Light* self) {
		return self->m_range;
	}
	void EMSCRIPTEN_KEEPALIVE Light_set_range(mud::Light* self, float range) {
		self->m_range = range;
	}
	float EMSCRIPTEN_KEEPALIVE Light_get_energy(mud::Light* self) {
		return self->m_energy;
	}
	void EMSCRIPTEN_KEEPALIVE Light_set_energy(mud::Light* self, float energy) {
		self->m_energy = energy;
	}
	float EMSCRIPTEN_KEEPALIVE Light_get_specular(mud::Light* self) {
		return self->m_specular;
	}
	void EMSCRIPTEN_KEEPALIVE Light_set_specular(mud::Light* self, float specular) {
		self->m_specular = specular;
	}
	float EMSCRIPTEN_KEEPALIVE Light_get_attenuation(mud::Light* self) {
		return self->m_attenuation;
	}
	void EMSCRIPTEN_KEEPALIVE Light_set_attenuation(mud::Light* self, float attenuation) {
		self->m_attenuation = attenuation;
	}
	bool EMSCRIPTEN_KEEPALIVE Light_get_shadows(mud::Light* self) {
		return self->m_shadows;
	}
	void EMSCRIPTEN_KEEPALIVE Light_set_shadows(mud::Light* self, bool shadows) {
		self->m_shadows = shadows;
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE Light_get_shadow_colour(mud::Light* self) {
		static mud::Colour temp;
		return (temp = self->m_shadow_colour, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Light_set_shadow_colour(mud::Light* self, mud::Colour* shadow_colour) {
		self->m_shadow_colour = *shadow_colour;
	}
	float EMSCRIPTEN_KEEPALIVE Light_get_shadow_range(mud::Light* self) {
		return self->m_shadow_range;
	}
	void EMSCRIPTEN_KEEPALIVE Light_set_shadow_range(mud::Light* self, float shadow_range) {
		self->m_shadow_range = shadow_range;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE Light_get_layers(mud::Light* self) {
		return self->m_layers;
	}
	void EMSCRIPTEN_KEEPALIVE Light_set_layers(mud::Light* self, uint32_t layers) {
		self->m_layers = layers;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE Light_get_last_render(mud::Light* self) {
		return self->m_last_render;
	}
	void EMSCRIPTEN_KEEPALIVE Light_set_last_render(mud::Light* self, uint32_t last_render) {
		self->m_last_render = last_render;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE Light_get_last_update(mud::Light* self) {
		return self->m_last_update;
	}
	void EMSCRIPTEN_KEEPALIVE Light_set_last_update(mud::Light* self, uint32_t last_update) {
		self->m_last_update = last_update;
	}
	float EMSCRIPTEN_KEEPALIVE Light_get_spot_angle(mud::Light* self) {
		return self->m_spot_angle;
	}
	void EMSCRIPTEN_KEEPALIVE Light_set_spot_angle(mud::Light* self, float spot_angle) {
		self->m_spot_angle = spot_angle;
	}
	float EMSCRIPTEN_KEEPALIVE Light_get_spot_attenuation(mud::Light* self) {
		return self->m_spot_attenuation;
	}
	void EMSCRIPTEN_KEEPALIVE Light_set_spot_attenuation(mud::Light* self, float spot_attenuation) {
		self->m_spot_attenuation = spot_attenuation;
	}
	mud::ShadowFlags EMSCRIPTEN_KEEPALIVE Light_get_shadow_flags(mud::Light* self) {
		return self->m_shadow_flags;
	}
	void EMSCRIPTEN_KEEPALIVE Light_set_shadow_flags(mud::Light* self, mud::ShadowFlags shadow_flags) {
		self->m_shadow_flags = shadow_flags;
	}
	uint8_t EMSCRIPTEN_KEEPALIVE Light_get_shadow_nusplits(mud::Light* self) {
		return self->m_shadow_num_splits;
	}
	void EMSCRIPTEN_KEEPALIVE Light_set_shadow_nusplits(mud::Light* self, uint8_t shadow_nusplits) {
		self->m_shadow_num_splits = shadow_nusplits;
	}
	float EMSCRIPTEN_KEEPALIVE Light_get_shadow_split_distribution(mud::Light* self) {
		return self->m_shadow_split_distribution;
	}
	void EMSCRIPTEN_KEEPALIVE Light_set_shadow_split_distribution(mud::Light* self, float shadow_split_distribution) {
		self->m_shadow_split_distribution = shadow_split_distribution;
	}
	float EMSCRIPTEN_KEEPALIVE Light_get_shadow_normal_bias(mud::Light* self) {
		return self->m_shadow_normal_bias;
	}
	void EMSCRIPTEN_KEEPALIVE Light_set_shadow_normal_bias(mud::Light* self, float shadow_normal_bias) {
		self->m_shadow_normal_bias = shadow_normal_bias;
	}
	float EMSCRIPTEN_KEEPALIVE Light_get_shadow_bias(mud::Light* self) {
		return self->m_shadow_bias;
	}
	void EMSCRIPTEN_KEEPALIVE Light_set_shadow_bias(mud::Light* self, float shadow_bias) {
		self->m_shadow_bias = shadow_bias;
	}
	void EMSCRIPTEN_KEEPALIVE Light___destroy__(mud::Light* self) {
		delete self;
	}
	// Material
	uint16_t EMSCRIPTEN_KEEPALIVE Material_get_index(mud::Material* self) {
		return self->m_index;
	}
	void EMSCRIPTEN_KEEPALIVE Material_set_index(mud::Material* self, uint16_t index) {
		self->m_index = index;
	}
	bool EMSCRIPTEN_KEEPALIVE Material_get_builtin(mud::Material* self) {
		return self->m_builtin;
	}
	void EMSCRIPTEN_KEEPALIVE Material_set_builtin(mud::Material* self, bool builtin) {
		self->m_builtin = builtin;
	}
	mud::Program* EMSCRIPTEN_KEEPALIVE Material_get_program(mud::Material* self) {
		return self->m_program;
	}
	void EMSCRIPTEN_KEEPALIVE Material_set_program(mud::Material* self, mud::Program* program) {
		self->m_program = program;
	}
	mud::BaseMaterialBlock* EMSCRIPTEN_KEEPALIVE Material_get_base_block(mud::Material* self) {
		static mud::BaseMaterialBlock temp;
		return (temp = self->m_base_block, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Material_set_base_block(mud::Material* self, mud::BaseMaterialBlock* base_block) {
		self->m_base_block = *base_block;
	}
	mud::UnshadedMaterialBlock* EMSCRIPTEN_KEEPALIVE Material_get_unshaded_block(mud::Material* self) {
		static mud::UnshadedMaterialBlock temp;
		return (temp = self->m_unshaded_block, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Material_set_unshaded_block(mud::Material* self, mud::UnshadedMaterialBlock* unshaded_block) {
		self->m_unshaded_block = *unshaded_block;
	}
	mud::PbrMaterialBlock* EMSCRIPTEN_KEEPALIVE Material_get_pbr_block(mud::Material* self) {
		static mud::PbrMaterialBlock temp;
		return (temp = self->m_pbr_block, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Material_set_pbr_block(mud::Material* self, mud::PbrMaterialBlock* pbr_block) {
		self->m_pbr_block = *pbr_block;
	}
	mud::FresnelMaterialBlock* EMSCRIPTEN_KEEPALIVE Material_get_fresnel_block(mud::Material* self) {
		static mud::FresnelMaterialBlock temp;
		return (temp = self->m_fresnel_block, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Material_set_fresnel_block(mud::Material* self, mud::FresnelMaterialBlock* fresnel_block) {
		self->m_fresnel_block = *fresnel_block;
	}
	void EMSCRIPTEN_KEEPALIVE Material___destroy__(mud::Material* self) {
		delete self;
	}
	// Mesh
	const char* EMSCRIPTEN_KEEPALIVE Mesh_get_name(mud::Mesh* self) {
		return self->m_name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE Mesh_set_name(mud::Mesh* self, const char* name) {
		self->m_name = name;
	}
	uint16_t EMSCRIPTEN_KEEPALIVE Mesh_get_index(mud::Mesh* self) {
		return self->m_index;
	}
	void EMSCRIPTEN_KEEPALIVE Mesh_set_index(mud::Mesh* self, uint16_t index) {
		self->m_index = index;
	}
	mud::DrawMode EMSCRIPTEN_KEEPALIVE Mesh_get_draw_mode(mud::Mesh* self) {
		return self->m_draw_mode;
	}
	void EMSCRIPTEN_KEEPALIVE Mesh_set_draw_mode(mud::Mesh* self, mud::DrawMode draw_mode) {
		self->m_draw_mode = draw_mode;
	}
	mud::Aabb* EMSCRIPTEN_KEEPALIVE Mesh_get_aabb(mud::Mesh* self) {
		static mud::Aabb temp;
		return (temp = self->m_aabb, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Mesh_set_aabb(mud::Mesh* self, mud::Aabb* aabb) {
		self->m_aabb = *aabb;
	}
	float EMSCRIPTEN_KEEPALIVE Mesh_get_radius(mud::Mesh* self) {
		return self->m_radius;
	}
	void EMSCRIPTEN_KEEPALIVE Mesh_set_radius(mud::Mesh* self, float radius) {
		self->m_radius = radius;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE Mesh_get_origin(mud::Mesh* self) {
		static mud::vec3 temp;
		return (temp = self->m_origin, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Mesh_set_origin(mud::Mesh* self, mud::vec3* origin) {
		self->m_origin = *origin;
	}
	bool EMSCRIPTEN_KEEPALIVE Mesh_get_readback(mud::Mesh* self) {
		return self->m_readback;
	}
	void EMSCRIPTEN_KEEPALIVE Mesh_set_readback(mud::Mesh* self, bool readback) {
		self->m_readback = readback;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE Mesh_get_vertex_format(mud::Mesh* self) {
		return self->m_vertex_format;
	}
	void EMSCRIPTEN_KEEPALIVE Mesh_set_vertex_format(mud::Mesh* self, uint32_t vertex_format) {
		self->m_vertex_format = vertex_format;
	}
	bool EMSCRIPTEN_KEEPALIVE Mesh_get_qnormals(mud::Mesh* self) {
		return self->m_qnormals;
	}
	void EMSCRIPTEN_KEEPALIVE Mesh_set_qnormals(mud::Mesh* self, bool qnormals) {
		self->m_qnormals = qnormals;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE Mesh_get_vertex_count(mud::Mesh* self) {
		return self->m_vertex_count;
	}
	void EMSCRIPTEN_KEEPALIVE Mesh_set_vertex_count(mud::Mesh* self, uint32_t vertex_count) {
		self->m_vertex_count = vertex_count;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE Mesh_get_index_count(mud::Mesh* self) {
		return self->m_index_count;
	}
	void EMSCRIPTEN_KEEPALIVE Mesh_set_index_count(mud::Mesh* self, uint32_t index_count) {
		self->m_index_count = index_count;
	}
	bool EMSCRIPTEN_KEEPALIVE Mesh_get_index32(mud::Mesh* self) {
		return self->m_index32;
	}
	void EMSCRIPTEN_KEEPALIVE Mesh_set_index32(mud::Mesh* self, bool index32) {
		self->m_index32 = index32;
	}
	mud::Material* EMSCRIPTEN_KEEPALIVE Mesh_get_material(mud::Mesh* self) {
		return self->m_material;
	}
	void EMSCRIPTEN_KEEPALIVE Mesh_set_material(mud::Mesh* self, mud::Material* material) {
		self->m_material = material;
	}
	void EMSCRIPTEN_KEEPALIVE Mesh___destroy__(mud::Mesh* self) {
		delete self;
	}
	// Model
	const char* EMSCRIPTEN_KEEPALIVE Model_get_name(mud::Model* self) {
		return self->m_name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE Model_set_name(mud::Model* self, const char* name) {
		self->m_name = name;
	}
	uint16_t EMSCRIPTEN_KEEPALIVE Model_get_index(mud::Model* self) {
		return self->m_index;
	}
	void EMSCRIPTEN_KEEPALIVE Model_set_index(mud::Model* self, uint16_t index) {
		self->m_index = index;
	}
	mud::Aabb* EMSCRIPTEN_KEEPALIVE Model_get_aabb(mud::Model* self) {
		static mud::Aabb temp;
		return (temp = self->m_aabb, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Model_set_aabb(mud::Model* self, mud::Aabb* aabb) {
		self->m_aabb = *aabb;
	}
	float EMSCRIPTEN_KEEPALIVE Model_get_radius(mud::Model* self) {
		return self->m_radius;
	}
	void EMSCRIPTEN_KEEPALIVE Model_set_radius(mud::Model* self, float radius) {
		self->m_radius = radius;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE Model_get_origin(mud::Model* self) {
		static mud::vec3 temp;
		return (temp = self->m_origin, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Model_set_origin(mud::Model* self, mud::vec3* origin) {
		self->m_origin = *origin;
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
	void EMSCRIPTEN_KEEPALIVE ModelItem_set_index(mud::ModelItem* self, size_t index) {
		self->m_index = index;
	}
	mud::Mesh* EMSCRIPTEN_KEEPALIVE ModelItem_get_mesh(mud::ModelItem* self) {
		return self->m_mesh;
	}
	void EMSCRIPTEN_KEEPALIVE ModelItem_set_mesh(mud::ModelItem* self, mud::Mesh* mesh) {
		self->m_mesh = mesh;
	}
	bool EMSCRIPTEN_KEEPALIVE ModelItem_get_has_transform(mud::ModelItem* self) {
		return self->m_has_transform;
	}
	void EMSCRIPTEN_KEEPALIVE ModelItem_set_has_transform(mud::ModelItem* self, bool has_transform) {
		self->m_has_transform = has_transform;
	}
	mud::mat4* EMSCRIPTEN_KEEPALIVE ModelItem_get_transform(mud::ModelItem* self) {
		static mud::mat4 temp;
		return (temp = self->m_transform, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE ModelItem_set_transform(mud::ModelItem* self, mud::mat4* transform) {
		self->m_transform = *transform;
	}
	int EMSCRIPTEN_KEEPALIVE ModelItem_get_skin(mud::ModelItem* self) {
		return self->m_skin;
	}
	void EMSCRIPTEN_KEEPALIVE ModelItem_set_skin(mud::ModelItem* self, int skin) {
		self->m_skin = skin;
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE ModelItem_get_colour(mud::ModelItem* self) {
		static mud::Colour temp;
		return (temp = self->m_colour, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE ModelItem_set_colour(mud::ModelItem* self, mud::Colour* colour) {
		self->m_colour = *colour;
	}
	mud::Material* EMSCRIPTEN_KEEPALIVE ModelItem_get_material(mud::ModelItem* self) {
		return self->m_material;
	}
	void EMSCRIPTEN_KEEPALIVE ModelItem_set_material(mud::ModelItem* self, mud::Material* material) {
		self->m_material = material;
	}
	void EMSCRIPTEN_KEEPALIVE ModelItem___destroy__(mud::ModelItem* self) {
		delete self;
	}
	// Node3
	mud::Scene* EMSCRIPTEN_KEEPALIVE Node3_get_scene(mud::Node3* self) {
		return self->m_scene;
	}
	void EMSCRIPTEN_KEEPALIVE Node3_set_scene(mud::Node3* self, mud::Scene* scene) {
		self->m_scene = scene;
	}
	uint16_t EMSCRIPTEN_KEEPALIVE Node3_get_index(mud::Node3* self) {
		return self->m_index;
	}
	void EMSCRIPTEN_KEEPALIVE Node3_set_index(mud::Node3* self, uint16_t index) {
		self->m_index = index;
	}
	mud::mat4* EMSCRIPTEN_KEEPALIVE Node3_get_transform(mud::Node3* self) {
		static mud::mat4 temp;
		return (temp = self->m_transform, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Node3_set_transform(mud::Node3* self, mud::mat4* transform) {
		self->m_transform = *transform;
	}
	bool EMSCRIPTEN_KEEPALIVE Node3_get_visible(mud::Node3* self) {
		return self->m_visible;
	}
	void EMSCRIPTEN_KEEPALIVE Node3_set_visible(mud::Node3* self, bool visible) {
		self->m_visible = visible;
	}
	void EMSCRIPTEN_KEEPALIVE Node3___destroy__(mud::Node3* self) {
		delete self;
	}
	// ParticleGenerator
	mud::ParticleGenerator* EMSCRIPTEN_KEEPALIVE ParticleGenerator_ParticleGenerator_0() {
		return new mud::ParticleGenerator();
	}
	const char* EMSCRIPTEN_KEEPALIVE ParticleGenerator_get_name(mud::ParticleGenerator* self) {
		return self->m_name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE ParticleGenerator_set_name(mud::ParticleGenerator* self, const char* name) {
		self->m_name = name;
	}
	float EMSCRIPTEN_KEEPALIVE ParticleGenerator_get_duration(mud::ParticleGenerator* self) {
		return self->m_duration;
	}
	void EMSCRIPTEN_KEEPALIVE ParticleGenerator_set_duration(mud::ParticleGenerator* self, float duration) {
		self->m_duration = duration;
	}
	float EMSCRIPTEN_KEEPALIVE ParticleGenerator_get_start_time(mud::ParticleGenerator* self) {
		return self->m_start_time;
	}
	void EMSCRIPTEN_KEEPALIVE ParticleGenerator_set_start_time(mud::ParticleGenerator* self, float start_time) {
		self->m_start_time = start_time;
	}
	bool EMSCRIPTEN_KEEPALIVE ParticleGenerator_get_loop(mud::ParticleGenerator* self) {
		return self->m_loop;
	}
	void EMSCRIPTEN_KEEPALIVE ParticleGenerator_set_loop(mud::ParticleGenerator* self, bool loop) {
		self->m_loop = loop;
	}
	mud::ShapeVar* EMSCRIPTEN_KEEPALIVE ParticleGenerator_get_shape(mud::ParticleGenerator* self) {
		static mud::ShapeVar temp;
		return (temp = self->m_shape, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE ParticleGenerator_set_shape(mud::ParticleGenerator* self, mud::ShapeVar* shape) {
		self->m_shape = *shape;
	}
	mud::EmitterFlow EMSCRIPTEN_KEEPALIVE ParticleGenerator_get_flow(mud::ParticleGenerator* self) {
		return self->m_flow;
	}
	void EMSCRIPTEN_KEEPALIVE ParticleGenerator_set_flow(mud::ParticleGenerator* self, mud::EmitterFlow flow) {
		self->m_flow = flow;
	}
	bool EMSCRIPTEN_KEEPALIVE ParticleGenerator_get_billboard(mud::ParticleGenerator* self) {
		return self->m_billboard;
	}
	void EMSCRIPTEN_KEEPALIVE ParticleGenerator_set_billboard(mud::ParticleGenerator* self, bool billboard) {
		self->m_billboard = billboard;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE ParticleGenerator_get_direction(mud::ParticleGenerator* self) {
		static mud::vec3 temp;
		return (temp = self->m_direction, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE ParticleGenerator_set_direction(mud::ParticleGenerator* self, mud::vec3* direction) {
		self->m_direction = *direction;
	}
	mud::quat* EMSCRIPTEN_KEEPALIVE ParticleGenerator_get_rotation(mud::ParticleGenerator* self) {
		static mud::quat temp;
		return (temp = self->m_rotation, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE ParticleGenerator_set_rotation(mud::ParticleGenerator* self, mud::quat* rotation) {
		self->m_rotation = *rotation;
	}
	mud::BlendMode EMSCRIPTEN_KEEPALIVE ParticleGenerator_get_blend_mode(mud::ParticleGenerator* self) {
		return self->m_blend_mode;
	}
	void EMSCRIPTEN_KEEPALIVE ParticleGenerator_set_blend_mode(mud::ParticleGenerator* self, mud::BlendMode blend_mode) {
		self->m_blend_mode = blend_mode;
	}
	const char* EMSCRIPTEN_KEEPALIVE ParticleGenerator_get_sprite_name(mud::ParticleGenerator* self) {
		return self->m_sprite_name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE ParticleGenerator_set_sprite_name(mud::ParticleGenerator* self, const char* sprite_name) {
		self->m_sprite_name = sprite_name;
	}
	void EMSCRIPTEN_KEEPALIVE ParticleGenerator___destroy__(mud::ParticleGenerator* self) {
		delete self;
	}
	// PbrMaterialBlock
	mud::PbrMaterialBlock* EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_PbrMaterialBlock_0() {
		return new mud::PbrMaterialBlock();
	}
	mud::PbrMaterialBlock* EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_PbrMaterialBlock_1(const mud::Colour* albedo) {
		return new mud::PbrMaterialBlock(*albedo);
	}
	mud::PbrMaterialBlock* EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_PbrMaterialBlock_2(const mud::Colour* albedo, float metallic) {
		return new mud::PbrMaterialBlock(*albedo, metallic);
	}
	mud::PbrMaterialBlock* EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_PbrMaterialBlock_3(const mud::Colour* albedo, float metallic, float roughness) {
		return new mud::PbrMaterialBlock(*albedo, metallic, roughness);
	}
	bool EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_get_enabled(mud::PbrMaterialBlock* self) {
		return self->m_enabled;
	}
	void EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_set_enabled(mud::PbrMaterialBlock* self, bool enabled) {
		self->m_enabled = enabled;
	}
	float EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_get_specular(mud::PbrMaterialBlock* self) {
		return self->m_specular;
	}
	void EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_set_specular(mud::PbrMaterialBlock* self, float specular) {
		self->m_specular = specular;
	}
	float EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_get_emissive_energy(mud::PbrMaterialBlock* self) {
		return self->m_emissive_energy;
	}
	void EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_set_emissive_energy(mud::PbrMaterialBlock* self, float emissive_energy) {
		self->m_emissive_energy = emissive_energy;
	}
	float EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_get_ritint(mud::PbrMaterialBlock* self) {
		return self->m_rim_tint;
	}
	void EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_set_ritint(mud::PbrMaterialBlock* self, float ritint) {
		self->m_rim_tint = ritint;
	}
	float EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_get_clearcoat_gloss(mud::PbrMaterialBlock* self) {
		return self->m_clearcoat_gloss;
	}
	void EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_set_clearcoat_gloss(mud::PbrMaterialBlock* self, float clearcoat_gloss) {
		self->m_clearcoat_gloss = clearcoat_gloss;
	}
	bool EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_get_deep_parallax(mud::PbrMaterialBlock* self) {
		return self->m_deep_parallax;
	}
	void EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_set_deep_parallax(mud::PbrMaterialBlock* self, bool deep_parallax) {
		self->m_deep_parallax = deep_parallax;
	}
	mud::PbrDiffuseMode EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_get_diffuse_mode(mud::PbrMaterialBlock* self) {
		return self->m_diffuse_mode;
	}
	void EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_set_diffuse_mode(mud::PbrMaterialBlock* self, mud::PbrDiffuseMode diffuse_mode) {
		self->m_diffuse_mode = diffuse_mode;
	}
	mud::PbrSpecularMode EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_get_specular_mode(mud::PbrMaterialBlock* self) {
		return self->m_specular_mode;
	}
	void EMSCRIPTEN_KEEPALIVE PbrMaterialBlock_set_specular_mode(mud::PbrMaterialBlock* self, mud::PbrSpecularMode specular_mode) {
		self->m_specular_mode = specular_mode;
	}
	void EMSCRIPTEN_KEEPALIVE PbrMaterialBlock___destroy__(mud::PbrMaterialBlock* self) {
		delete self;
	}
	// Prefab
	const char* EMSCRIPTEN_KEEPALIVE Prefab_get_name(mud::Prefab* self) {
		return self->m_name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE Prefab_set_name(mud::Prefab* self, const char* name) {
		self->m_name = name;
	}
	void EMSCRIPTEN_KEEPALIVE Prefab___destroy__(mud::Prefab* self) {
		delete self;
	}
	// Program
	const char* EMSCRIPTEN_KEEPALIVE Program_get_name(mud::Program* self) {
		return self->name();
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
	void EMSCRIPTEN_KEEPALIVE Radiance_set_energy(mud::Radiance* self, float energy) {
		self->m_energy = energy;
	}
	float EMSCRIPTEN_KEEPALIVE Radiance_get_ambient(mud::Radiance* self) {
		return self->m_ambient;
	}
	void EMSCRIPTEN_KEEPALIVE Radiance_set_ambient(mud::Radiance* self, float ambient) {
		self->m_ambient = ambient;
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE Radiance_get_colour(mud::Radiance* self) {
		static mud::Colour temp;
		return (temp = self->m_colour, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Radiance_set_colour(mud::Radiance* self, mud::Colour* colour) {
		self->m_colour = *colour;
	}
	mud::Texture* EMSCRIPTEN_KEEPALIVE Radiance_get_texture(mud::Radiance* self) {
		return self->m_texture;
	}
	void EMSCRIPTEN_KEEPALIVE Radiance_set_texture(mud::Radiance* self, mud::Texture* texture) {
		self->m_texture = texture;
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
	mud::Gnode* EMSCRIPTEN_KEEPALIVE Scene_begin_0(mud::Scene* self) {
		return &self->begin();
	}
	mud::Gnode* EMSCRIPTEN_KEEPALIVE Scene_get_graph(mud::Scene* self) {
		return &self->m_graph;
	}
	mud::Node3* EMSCRIPTEN_KEEPALIVE Scene_get_root_node(mud::Scene* self) {
		return &self->m_root_node;
	}
	mud::Environment* EMSCRIPTEN_KEEPALIVE Scene_get_environment(mud::Scene* self) {
		static mud::Environment temp;
		return (temp = self->m_environment, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Scene_set_environment(mud::Scene* self, mud::Environment* environment) {
		self->m_environment = *environment;
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
	void EMSCRIPTEN_KEEPALIVE Sun_set_azimuth(mud::Sun* self, float azimuth) {
		self->azimuth = azimuth;
	}
	float EMSCRIPTEN_KEEPALIVE Sun_get_elevation(mud::Sun* self) {
		return self->elevation;
	}
	void EMSCRIPTEN_KEEPALIVE Sun_set_elevation(mud::Sun* self, float elevation) {
		self->elevation = elevation;
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE Sun_get_colour(mud::Sun* self) {
		static mud::Colour temp;
		return (temp = self->m_colour, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Sun_set_colour(mud::Sun* self, mud::Colour* colour) {
		self->m_colour = *colour;
	}
	float EMSCRIPTEN_KEEPALIVE Sun_get_intensity(mud::Sun* self) {
		return self->m_intensity;
	}
	void EMSCRIPTEN_KEEPALIVE Sun_set_intensity(mud::Sun* self, float intensity) {
		self->m_intensity = intensity;
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
	void EMSCRIPTEN_KEEPALIVE Texture_set_width(mud::Texture* self, uint16_t width) {
		self->m_width = width;
	}
	uint16_t EMSCRIPTEN_KEEPALIVE Texture_get_height(mud::Texture* self) {
		return self->m_height;
	}
	void EMSCRIPTEN_KEEPALIVE Texture_set_height(mud::Texture* self, uint16_t height) {
		self->m_height = height;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE Texture_get_bits_per_pixel(mud::Texture* self) {
		return self->m_bits_per_pixel;
	}
	void EMSCRIPTEN_KEEPALIVE Texture_set_bits_per_pixel(mud::Texture* self, uint32_t bits_per_pixel) {
		self->m_bits_per_pixel = bits_per_pixel;
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
	void EMSCRIPTEN_KEEPALIVE UnshadedMaterialBlock_set_enabled(mud::UnshadedMaterialBlock* self, bool enabled) {
		self->m_enabled = enabled;
	}
	void EMSCRIPTEN_KEEPALIVE UnshadedMaterialBlock___destroy__(mud::UnshadedMaterialBlock* self) {
		delete self;
	}
	// Viewport
	mud::Camera* EMSCRIPTEN_KEEPALIVE Viewport_get_camera(mud::Viewport* self) {
		return self->m_camera;
	}
	void EMSCRIPTEN_KEEPALIVE Viewport_set_camera(mud::Viewport* self, mud::Camera* camera) {
		self->m_camera = camera;
	}
	mud::Scene* EMSCRIPTEN_KEEPALIVE Viewport_get_scene(mud::Viewport* self) {
		return self->m_scene;
	}
	void EMSCRIPTEN_KEEPALIVE Viewport_set_scene(mud::Viewport* self, mud::Scene* scene) {
		self->m_scene = scene;
	}
	uint16_t EMSCRIPTEN_KEEPALIVE Viewport_get_index(mud::Viewport* self) {
		return self->m_index;
	}
	void EMSCRIPTEN_KEEPALIVE Viewport_set_index(mud::Viewport* self, uint16_t index) {
		self->m_index = index;
	}
	bool EMSCRIPTEN_KEEPALIVE Viewport_get_active(mud::Viewport* self) {
		return self->m_active;
	}
	void EMSCRIPTEN_KEEPALIVE Viewport_set_active(mud::Viewport* self, bool active) {
		self->m_active = active;
	}
	mud::uvec4* EMSCRIPTEN_KEEPALIVE Viewport_get_rect(mud::Viewport* self) {
		static mud::uvec4 temp;
		return (temp = self->m_rect, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Viewport_set_rect(mud::Viewport* self, mud::uvec4* rect) {
		self->m_rect = *rect;
	}
	bool EMSCRIPTEN_KEEPALIVE Viewport_get_scissor(mud::Viewport* self) {
		return self->m_scissor;
	}
	void EMSCRIPTEN_KEEPALIVE Viewport_set_scissor(mud::Viewport* self, bool scissor) {
		self->m_scissor = scissor;
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE Viewport_get_clear_colour(mud::Viewport* self) {
		static mud::Colour temp;
		return (temp = self->m_clear_colour, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Viewport_set_clear_colour(mud::Viewport* self, mud::Colour* clear_colour) {
		self->m_clear_colour = *clear_colour;
	}
	mud::Shading EMSCRIPTEN_KEEPALIVE Viewport_get_shading(mud::Viewport* self) {
		return self->m_shading;
	}
	void EMSCRIPTEN_KEEPALIVE Viewport_set_shading(mud::Viewport* self, mud::Shading shading) {
		self->m_shading = shading;
	}
	mud::Lighting EMSCRIPTEN_KEEPALIVE Viewport_get_lighting(mud::Viewport* self) {
		return self->m_lighting;
	}
	void EMSCRIPTEN_KEEPALIVE Viewport_set_lighting(mud::Viewport* self, mud::Lighting lighting) {
		self->m_lighting = lighting;
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
	mud::Node3* EMSCRIPTEN_KEEPALIVE Particles_get_node(mud::Particles* self) {
		return self->m_node;
	}
	void EMSCRIPTEN_KEEPALIVE Particles_set_node(mud::Particles* self, mud::Node3* node) {
		self->m_node = node;
	}
	void EMSCRIPTEN_KEEPALIVE Particles___destroy__(mud::Particles* self) {
		delete self;
	}
	// RenderTarget
	void EMSCRIPTEN_KEEPALIVE RenderTarget___destroy__(mud::RenderTarget* self) {
		delete self;
	}
	// AnimationTarget
	mud::AnimationTarget EMSCRIPTEN_KEEPALIVE AnimationTarget_Position() {
		return mud::AnimationTarget::Position;
	}
	mud::AnimationTarget EMSCRIPTEN_KEEPALIVE AnimationTarget_Rotation() {
		return mud::AnimationTarget::Rotation;
	}
	mud::AnimationTarget EMSCRIPTEN_KEEPALIVE AnimationTarget_Scale() {
		return mud::AnimationTarget::Scale;
	}
	// BackgroundMode
	mud::BackgroundMode EMSCRIPTEN_KEEPALIVE BackgroundMode_None() {
		return mud::BackgroundMode::None;
	}
	mud::BackgroundMode EMSCRIPTEN_KEEPALIVE BackgroundMode_Panorama() {
		return mud::BackgroundMode::Panorama;
	}
	mud::BackgroundMode EMSCRIPTEN_KEEPALIVE BackgroundMode_Radiance() {
		return mud::BackgroundMode::Radiance;
	}
	mud::BackgroundMode EMSCRIPTEN_KEEPALIVE BackgroundMode_Custom() {
		return mud::BackgroundMode::Custom;
	}
	// BlendMode
	mud::BlendMode EMSCRIPTEN_KEEPALIVE BlendMode_Mix() {
		return mud::BlendMode::Mix;
	}
	mud::BlendMode EMSCRIPTEN_KEEPALIVE BlendMode_Add() {
		return mud::BlendMode::Add;
	}
	mud::BlendMode EMSCRIPTEN_KEEPALIVE BlendMode_Sub() {
		return mud::BlendMode::Sub;
	}
	mud::BlendMode EMSCRIPTEN_KEEPALIVE BlendMode_Mul() {
		return mud::BlendMode::Mul;
	}
	mud::BlendMode EMSCRIPTEN_KEEPALIVE BlendMode_Normal() {
		return mud::BlendMode::Normal;
	}
	mud::BlendMode EMSCRIPTEN_KEEPALIVE BlendMode_Alpha() {
		return mud::BlendMode::Alpha;
	}
	// CullMode
	mud::CullMode EMSCRIPTEN_KEEPALIVE CullMode_None() {
		return mud::CullMode::None;
	}
	mud::CullMode EMSCRIPTEN_KEEPALIVE CullMode_Front() {
		return mud::CullMode::Front;
	}
	mud::CullMode EMSCRIPTEN_KEEPALIVE CullMode_Back() {
		return mud::CullMode::Back;
	}
	// DepthDraw
	mud::DepthDraw EMSCRIPTEN_KEEPALIVE DepthDraw_Enabled() {
		return mud::DepthDraw::Enabled;
	}
	mud::DepthDraw EMSCRIPTEN_KEEPALIVE DepthDraw_Disabled() {
		return mud::DepthDraw::Disabled;
	}
	// DepthTest
	mud::DepthTest EMSCRIPTEN_KEEPALIVE DepthTest_Enabled() {
		return mud::DepthTest::Enabled;
	}
	mud::DepthTest EMSCRIPTEN_KEEPALIVE DepthTest_Disabled() {
		return mud::DepthTest::Disabled;
	}
	// EmitterFlow
	mud::EmitterFlow EMSCRIPTEN_KEEPALIVE EmitterFlow_Outward() {
		return mud::EmitterFlow::Outward;
	}
	mud::EmitterFlow EMSCRIPTEN_KEEPALIVE EmitterFlow_Absolute() {
		return mud::EmitterFlow::Absolute;
	}
	// Interpolation
	mud::Interpolation EMSCRIPTEN_KEEPALIVE Interpolation_Nearest() {
		return mud::Interpolation::Nearest;
	}
	mud::Interpolation EMSCRIPTEN_KEEPALIVE Interpolation_Linear() {
		return mud::Interpolation::Linear;
	}
	mud::Interpolation EMSCRIPTEN_KEEPALIVE Interpolation_Cubic() {
		return mud::Interpolation::Cubic;
	}
	// IsometricAngle
	mud::IsometricAngle EMSCRIPTEN_KEEPALIVE IsometricAngle_NORTH() {
		return mud::NORTH;
	}
	mud::IsometricAngle EMSCRIPTEN_KEEPALIVE IsometricAngle_SOUTH() {
		return mud::SOUTH;
	}
	mud::IsometricAngle EMSCRIPTEN_KEEPALIVE IsometricAngle_EAST() {
		return mud::EAST;
	}
	mud::IsometricAngle EMSCRIPTEN_KEEPALIVE IsometricAngle_WEST() {
		return mud::WEST;
	}
	// ItemShadow
	mud::ItemShadow EMSCRIPTEN_KEEPALIVE ItemShadow_Default() {
		return mud::ItemShadow::Default;
	}
	mud::ItemShadow EMSCRIPTEN_KEEPALIVE ItemShadow_DoubleSided() {
		return mud::ItemShadow::DoubleSided;
	}
	// LightType
	mud::LightType EMSCRIPTEN_KEEPALIVE LightType_Direct() {
		return mud::LightType::Direct;
	}
	mud::LightType EMSCRIPTEN_KEEPALIVE LightType_Point() {
		return mud::LightType::Point;
	}
	mud::LightType EMSCRIPTEN_KEEPALIVE LightType_Spot() {
		return mud::LightType::Spot;
	}
	mud::LightType EMSCRIPTEN_KEEPALIVE LightType_Count() {
		return mud::LightType::Count;
	}
	// Lighting
	mud::Lighting EMSCRIPTEN_KEEPALIVE Lighting_None() {
		return mud::Lighting::None;
	}
	mud::Lighting EMSCRIPTEN_KEEPALIVE Lighting_Clustered() {
		return mud::Lighting::Clustered;
	}
	mud::Lighting EMSCRIPTEN_KEEPALIVE Lighting_Deferred() {
		return mud::Lighting::Deferred;
	}
	mud::Lighting EMSCRIPTEN_KEEPALIVE Lighting_VoxelGI() {
		return mud::Lighting::VoxelGI;
	}
	// MSAA
	mud::MSAA EMSCRIPTEN_KEEPALIVE MSAA_Disabled() {
		return mud::MSAA::Disabled;
	}
	mud::MSAA EMSCRIPTEN_KEEPALIVE MSAA_X2() {
		return mud::MSAA::X2;
	}
	mud::MSAA EMSCRIPTEN_KEEPALIVE MSAA_X4() {
		return mud::MSAA::X4;
	}
	mud::MSAA EMSCRIPTEN_KEEPALIVE MSAA_X8() {
		return mud::MSAA::X8;
	}
	mud::MSAA EMSCRIPTEN_KEEPALIVE MSAA_X16() {
		return mud::MSAA::X16;
	}
	// MaterialFlag
	mud::MaterialFlag EMSCRIPTEN_KEEPALIVE MaterialFlag_TriplanarUV1() {
		return mud::MaterialFlag::TriplanarUV1;
	}
	mud::MaterialFlag EMSCRIPTEN_KEEPALIVE MaterialFlag_TriplanarUV2() {
		return mud::MaterialFlag::TriplanarUV2;
	}
	mud::MaterialFlag EMSCRIPTEN_KEEPALIVE MaterialFlag_Count() {
		return mud::MaterialFlag::Count;
	}
	// ModelFormat
	mud::ModelFormat EMSCRIPTEN_KEEPALIVE ModelFormat_obj() {
		return mud::ModelFormat::obj;
	}
	mud::ModelFormat EMSCRIPTEN_KEEPALIVE ModelFormat_gltf() {
		return mud::ModelFormat::gltf;
	}
	mud::ModelFormat EMSCRIPTEN_KEEPALIVE ModelFormat_Count() {
		return mud::ModelFormat::Count;
	}
	// Month
	mud::Month EMSCRIPTEN_KEEPALIVE Month_January() {
		return mud::Month::January;
	}
	mud::Month EMSCRIPTEN_KEEPALIVE Month_February() {
		return mud::Month::February;
	}
	mud::Month EMSCRIPTEN_KEEPALIVE Month_March() {
		return mud::Month::March;
	}
	mud::Month EMSCRIPTEN_KEEPALIVE Month_April() {
		return mud::Month::April;
	}
	mud::Month EMSCRIPTEN_KEEPALIVE Month_May() {
		return mud::Month::May;
	}
	mud::Month EMSCRIPTEN_KEEPALIVE Month_June() {
		return mud::Month::June;
	}
	mud::Month EMSCRIPTEN_KEEPALIVE Month_July() {
		return mud::Month::July;
	}
	mud::Month EMSCRIPTEN_KEEPALIVE Month_August() {
		return mud::Month::August;
	}
	mud::Month EMSCRIPTEN_KEEPALIVE Month_September() {
		return mud::Month::September;
	}
	mud::Month EMSCRIPTEN_KEEPALIVE Month_October() {
		return mud::Month::October;
	}
	mud::Month EMSCRIPTEN_KEEPALIVE Month_November() {
		return mud::Month::November;
	}
	mud::Month EMSCRIPTEN_KEEPALIVE Month_December() {
		return mud::Month::December;
	}
	// PbrDiffuseMode
	mud::PbrDiffuseMode EMSCRIPTEN_KEEPALIVE PbrDiffuseMode_Lambert() {
		return mud::PbrDiffuseMode::Lambert;
	}
	mud::PbrDiffuseMode EMSCRIPTEN_KEEPALIVE PbrDiffuseMode_LambertHalf() {
		return mud::PbrDiffuseMode::LambertHalf;
	}
	mud::PbrDiffuseMode EMSCRIPTEN_KEEPALIVE PbrDiffuseMode_OrenNayar() {
		return mud::PbrDiffuseMode::OrenNayar;
	}
	mud::PbrDiffuseMode EMSCRIPTEN_KEEPALIVE PbrDiffuseMode_Burley() {
		return mud::PbrDiffuseMode::Burley;
	}
	mud::PbrDiffuseMode EMSCRIPTEN_KEEPALIVE PbrDiffuseMode_Toon() {
		return mud::PbrDiffuseMode::Toon;
	}
	// PbrSpecularMode
	mud::PbrSpecularMode EMSCRIPTEN_KEEPALIVE PbrSpecularMode_SchlickGGX() {
		return mud::PbrSpecularMode::SchlickGGX;
	}
	mud::PbrSpecularMode EMSCRIPTEN_KEEPALIVE PbrSpecularMode_Blinn() {
		return mud::PbrSpecularMode::Blinn;
	}
	mud::PbrSpecularMode EMSCRIPTEN_KEEPALIVE PbrSpecularMode_Phong() {
		return mud::PbrSpecularMode::Phong;
	}
	mud::PbrSpecularMode EMSCRIPTEN_KEEPALIVE PbrSpecularMode_Toon() {
		return mud::PbrSpecularMode::Toon;
	}
	mud::PbrSpecularMode EMSCRIPTEN_KEEPALIVE PbrSpecularMode_Disabled() {
		return mud::PbrSpecularMode::Disabled;
	}
	// ShaderType
	mud::ShaderType EMSCRIPTEN_KEEPALIVE ShaderType_Compute() {
		return mud::ShaderType::Compute;
	}
	mud::ShaderType EMSCRIPTEN_KEEPALIVE ShaderType_Fragment() {
		return mud::ShaderType::Fragment;
	}
	mud::ShaderType EMSCRIPTEN_KEEPALIVE ShaderType_Geometry() {
		return mud::ShaderType::Geometry;
	}
	mud::ShaderType EMSCRIPTEN_KEEPALIVE ShaderType_Vertex() {
		return mud::ShaderType::Vertex;
	}
	mud::ShaderType EMSCRIPTEN_KEEPALIVE ShaderType_Count() {
		return mud::ShaderType::Count;
	}
	// Shading
	mud::Shading EMSCRIPTEN_KEEPALIVE Shading_Wireframe() {
		return mud::Shading::Wireframe;
	}
	mud::Shading EMSCRIPTEN_KEEPALIVE Shading_Unshaded() {
		return mud::Shading::Unshaded;
	}
	mud::Shading EMSCRIPTEN_KEEPALIVE Shading_Shaded() {
		return mud::Shading::Shaded;
	}
	mud::Shading EMSCRIPTEN_KEEPALIVE Shading_Volume() {
		return mud::Shading::Volume;
	}
	mud::Shading EMSCRIPTEN_KEEPALIVE Shading_Voxels() {
		return mud::Shading::Voxels;
	}
	mud::Shading EMSCRIPTEN_KEEPALIVE Shading_Lightmap() {
		return mud::Shading::Lightmap;
	}
	mud::Shading EMSCRIPTEN_KEEPALIVE Shading_Clear() {
		return mud::Shading::Clear;
	}
	mud::Shading EMSCRIPTEN_KEEPALIVE Shading_Count() {
		return mud::Shading::Count;
	}
	// ShadowFlags
	mud::ShadowFlags EMSCRIPTEN_KEEPALIVE ShadowFlags_CSM_Stabilize() {
		return mud::CSM_Stabilize;
	}
	mud::ShadowFlags EMSCRIPTEN_KEEPALIVE ShadowFlags_CSM_Optimize() {
		return mud::CSM_Optimize;
	}
	mud::ShadowFlags EMSCRIPTEN_KEEPALIVE ShadowFlags_CSM_BlendSplits() {
		return mud::CSM_BlendSplits;
	}
	// TextureChannel
	mud::TextureChannel EMSCRIPTEN_KEEPALIVE TextureChannel_Red() {
		return mud::TextureChannel::Red;
	}
	mud::TextureChannel EMSCRIPTEN_KEEPALIVE TextureChannel_Green() {
		return mud::TextureChannel::Green;
	}
	mud::TextureChannel EMSCRIPTEN_KEEPALIVE TextureChannel_Blue() {
		return mud::TextureChannel::Blue;
	}
	mud::TextureChannel EMSCRIPTEN_KEEPALIVE TextureChannel_Alpha() {
		return mud::TextureChannel::Alpha;
	}
	mud::TextureChannel EMSCRIPTEN_KEEPALIVE TextureChannel_All() {
		return mud::TextureChannel::All;
	}
	// TextureHint
	mud::TextureHint EMSCRIPTEN_KEEPALIVE TextureHint_Black() {
		return mud::TextureHint::Black;
	}
	mud::TextureHint EMSCRIPTEN_KEEPALIVE TextureHint_White() {
		return mud::TextureHint::White;
	}
	mud::TextureHint EMSCRIPTEN_KEEPALIVE TextureHint_Normal() {
		return mud::TextureHint::Normal;
	}
	// TextureSampler
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE TextureSampler_Source0() {
		return mud::TextureSampler::Source0;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE TextureSampler_Source1() {
		return mud::TextureSampler::Source1;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE TextureSampler_Source2() {
		return mud::TextureSampler::Source2;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE TextureSampler_Source3() {
		return mud::TextureSampler::Source3;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE TextureSampler_SourceDepth() {
		return mud::TextureSampler::SourceDepth;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE TextureSampler_Color() {
		return mud::TextureSampler::Color;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE TextureSampler_Albedo() {
		return mud::TextureSampler::Albedo;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE TextureSampler_Metallic() {
		return mud::TextureSampler::Metallic;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE TextureSampler_Roughness() {
		return mud::TextureSampler::Roughness;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE TextureSampler_Emissive() {
		return mud::TextureSampler::Emissive;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE TextureSampler_Normal() {
		return mud::TextureSampler::Normal;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE TextureSampler_AO() {
		return mud::TextureSampler::AO;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE TextureSampler_Depth() {
		return mud::TextureSampler::Depth;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE TextureSampler_Skeleton() {
		return mud::TextureSampler::Skeleton;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE TextureSampler_ShadowCSM() {
		return mud::TextureSampler::ShadowCSM;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE TextureSampler_ShadowAtlas() {
		return mud::TextureSampler::ShadowAtlas;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE TextureSampler_Radiance() {
		return mud::TextureSampler::Radiance;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE TextureSampler_ReflectionProbe() {
		return mud::TextureSampler::ReflectionProbe;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE TextureSampler_GIProbe() {
		return mud::TextureSampler::GIProbe;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE TextureSampler_Lights() {
		return mud::TextureSampler::Lights;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE TextureSampler_Clusters() {
		return mud::TextureSampler::Clusters;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE TextureSampler_LightRecords() {
		return mud::TextureSampler::LightRecords;
	}
	mud::TextureSampler EMSCRIPTEN_KEEPALIVE TextureSampler_Lightmap() {
		return mud::TextureSampler::Lightmap;
	}
	
}


