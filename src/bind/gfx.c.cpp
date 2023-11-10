#include <infra/Api.h>
#include <type/Api.h>
#include <tree/Api.h>
#include <jobs/Api.h>
#include <pool/Api.h>
#include <ecs/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <ctx/Api.h>
#include <bgfx/Api.h>
#include <gfx/Api.h>

#ifdef TWO_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// Node3
	two::Type* DECL two_Node3__type() {
		return &two::type<two::Node3>();
	}
	two::Node3* DECL two_Node3__construct_0() {
		return new two::Node3();
	}
	two::Node3* DECL two_Node3__construct_1(const two::vec3* position) {
		return new two::Node3(*position);
	}
	two::Node3* DECL two_Node3__construct_2(const two::vec3* position, const two::quat* rotation) {
		return new two::Node3(*position, *rotation);
	}
	two::Node3* DECL two_Node3__construct_3(const two::vec3* position, const two::quat* rotation, const two::vec3* scale) {
		return new two::Node3(*position, *rotation, *scale);
	}
	void DECL two_Node3_apply_1(two::Node3* self, const two::vec3* position) {
		self->apply(*position);
	}
	void DECL two_Node3_apply_2(two::Node3* self, const two::vec3* position, const two::quat* rotation) {
		self->apply(*position, *rotation);
	}
	void DECL two_Node3_apply_3(two::Node3* self, const two::vec3* position, const two::quat* rotation, const two::vec3* scale) {
		self->apply(*position, *rotation, *scale);
	}
	void DECL two_Node3_derive_2(two::Node3* self, const two::Node3* parent, const two::vec3* position) {
		self->derive(*parent, *position);
	}
	void DECL two_Node3_derive_3(two::Node3* self, const two::Node3* parent, const two::vec3* position, const two::quat* rotation) {
		self->derive(*parent, *position, *rotation);
	}
	void DECL two_Node3_derive_4(two::Node3* self, const two::Node3* parent, const two::vec3* position, const two::quat* rotation, const two::vec3* scale) {
		self->derive(*parent, *position, *rotation, *scale);
	}
	two::vec3* DECL two_Node3_position_0(two::Node3* self) {
		static two::vec3 temp;
		return (temp = self->position(), &temp);
	}
	two::vec3* DECL two_Node3_axis_1(two::Node3* self, const two::vec3* dir) {
		static two::vec3 temp;
		return (temp = self->axis(*dir), &temp);
	}
	two::vec3* DECL two_Node3_direction_0(two::Node3* self) {
		static two::vec3 temp;
		return (temp = self->direction(), &temp);
	}
	uint32_t DECL two_Node3__get_parent(two::Node3* self) {
		return self->m_parent;
	}
	void DECL two_Node3__set_parent(two::Node3* self, uint32_t value) {
		self->m_parent = value;
	}
	two::mat4* DECL two_Node3__get_transform(two::Node3* self) {
		return &self->m_transform;
	}
	void DECL two_Node3__set_transform(two::Node3* self, two::mat4* value) {
		self->m_transform = *value;
	}
	void DECL two_Node3__destroy(two::Node3* self) {
		delete self;
	}
	// AnimTrack
	two::Type* DECL two_AnimTrack__type() {
		return &two::type<two::AnimTrack>();
	}
	two::Animation* DECL two_AnimTrack__get_animation(two::AnimTrack* self) {
		return self->m_animation;
	}
	void DECL two_AnimTrack__set_animation(two::AnimTrack* self, two::Animation* value) {
		self->m_animation = value;
	}
	size_t DECL two_AnimTrack__get_node(two::AnimTrack* self) {
		return self->m_node;
	}
	void DECL two_AnimTrack__set_node(two::AnimTrack* self, size_t value) {
		self->m_node = value;
	}
	const char* DECL two_AnimTrack__get_node_name(two::AnimTrack* self) {
		return self->m_node_name.c_str();
	}
	void DECL two_AnimTrack__set_node_name(two::AnimTrack* self, const char* value) {
		self->m_node_name = value;
	}
	two::AnimTarget DECL two_AnimTrack__get_target(two::AnimTrack* self) {
		return self->m_target;
	}
	void DECL two_AnimTrack__set_target(two::AnimTrack* self, two::AnimTarget value) {
		self->m_target = value;
	}
	two::Type* DECL two_AnimTrack__get_value_type(two::AnimTrack* self) {
		return self->m_value_type;
	}
	void DECL two_AnimTrack__set_value_type(two::AnimTrack* self, two::Type* value) {
		self->m_value_type = value;
	}
	float DECL two_AnimTrack__get_length(two::AnimTrack* self) {
		return self->m_length;
	}
	void DECL two_AnimTrack__set_length(two::AnimTrack* self, float value) {
		self->m_length = value;
	}
	two::Interpolation DECL two_AnimTrack__get_interpolation(two::AnimTrack* self) {
		return self->m_interpolation;
	}
	void DECL two_AnimTrack__set_interpolation(two::AnimTrack* self, two::Interpolation value) {
		self->m_interpolation = value;
	}
	void DECL two_AnimTrack__destroy(two::AnimTrack* self) {
		delete self;
	}
	// Animation
	two::Type* DECL two_Animation__type() {
		return &two::type<two::Animation>();
	}
	const char* DECL two_Animation__get_name(two::Animation* self) {
		return self->m_name.c_str();
	}
	void DECL two_Animation__set_name(two::Animation* self, const char* value) {
		self->m_name = value;
	}
	float DECL two_Animation__get_length(two::Animation* self) {
		return self->m_length;
	}
	void DECL two_Animation__set_length(two::Animation* self, float value) {
		self->m_length = value;
	}
	float DECL two_Animation__get_step(two::Animation* self) {
		return self->m_step;
	}
	void DECL two_Animation__set_step(two::Animation* self, float value) {
		self->m_step = value;
	}
	void DECL two_Animation__destroy(two::Animation* self) {
		delete self;
	}
	// Texture
	two::Type* DECL two_Texture__type() {
		return &two::type<two::Texture>();
	}
	two::Texture* DECL two_Texture__construct_0() {
		return new two::Texture();
	}
	two::Texture* DECL two_Texture__construct_1(const char* name) {
		return new two::Texture(name);
	}
	two::Texture* DECL two_Texture__construct_3(const two::uvec2* size, bool mips, two::TextureFormat format) {
		return new two::Texture(*size, mips, format);
	}
	two::Texture* DECL two_Texture__construct_4(const two::uvec2* size, bool mips, two::TextureFormat format, uint64_t flags) {
		return new two::Texture(*size, mips, format, flags);
	}
	two::Texture* DECL two_Texture__construct_5(const two::uvec2* size, bool mips, two::TextureFormat format, uint64_t flags, bool cube) {
		return new two::Texture(*size, mips, format, flags, cube);
	}
	bool DECL two_Texture_valid_0(two::Texture* self) {
		return self->valid();
	}
	void DECL two_Texture_load_2(two::Texture* self, two::GfxSystem* gfx, const char* path) {
		self->load(*gfx, path);
	}
	void DECL two_Texture_load_3(two::Texture* self, two::GfxSystem* gfx, const char* path, bool srgb) {
		self->load(*gfx, path, srgb);
	}
	void DECL two_Texture_load_4(two::Texture* self, two::GfxSystem* gfx, const char* path, bool srgb, bool mips) {
		self->load(*gfx, path, srgb, mips);
	}
	void DECL two_Texture_reload_1(two::Texture* self, two::GfxSystem* gfx) {
		self->reload(*gfx);
	}
	void DECL two_Texture_reload_2(two::Texture* self, two::GfxSystem* gfx, bool srgb) {
		self->reload(*gfx, srgb);
	}
	void DECL two_Texture_reload_3(two::Texture* self, two::GfxSystem* gfx, bool srgb, bool mips) {
		self->reload(*gfx, srgb, mips);
	}
	void DECL two_Texture_load_mem_2(two::Texture* self, two::GfxSystem* gfx, uchar* data, int data_size) {
		self->load_mem(*gfx, { (uint8_t*)data, data_size / (sizeof(uint8_t) / sizeof(uchar)) });
	}
	void DECL two_Texture_load_rgba_2(two::Texture* self, const two::uvec2* size, uint* data, int data_size) {
		self->load_rgba(*size, { (uint32_t*)data, data_size / (sizeof(uint32_t) / sizeof(uint)) });
	}
	void DECL two_Texture_load_rgba_3(two::Texture* self, const two::uvec2* size, uint* data, int data_size, bool ref) {
		self->load_rgba(*size, { (uint32_t*)data, data_size / (sizeof(uint32_t) / sizeof(uint)) }, ref);
	}
	void DECL two_Texture_load_float_2(two::Texture* self, const two::uvec2* size, float* data, int data_size) {
		self->load_float(*size, { (float*)data, data_size / (sizeof(float) / sizeof(float)) });
	}
	void DECL two_Texture_load_float_3(two::Texture* self, const two::uvec2* size, float* data, int data_size, bool ref) {
		self->load_float(*size, { (float*)data, data_size / (sizeof(float) / sizeof(float)) }, ref);
	}
	const char* DECL two_Texture__get_name(two::Texture* self) {
		return self->m_name.c_str();
	}
	void DECL two_Texture__set_name(two::Texture* self, const char* value) {
		self->m_name = value;
	}
	const char* DECL two_Texture__get_location(two::Texture* self) {
		return self->m_location.c_str();
	}
	void DECL two_Texture__set_location(two::Texture* self, const char* value) {
		self->m_location = value;
	}
	two::TextureFormat DECL two_Texture__get_format(two::Texture* self) {
		return self->m_format;
	}
	void DECL two_Texture__set_format(two::Texture* self, two::TextureFormat value) {
		self->m_format = value;
	}
	two::uvec2* DECL two_Texture__get_size(two::Texture* self) {
		return &self->m_size;
	}
	void DECL two_Texture__set_size(two::Texture* self, two::uvec2* value) {
		self->m_size = *value;
	}
	uint16_t DECL two_Texture__get_depth(two::Texture* self) {
		return self->m_depth;
	}
	void DECL two_Texture__set_depth(two::Texture* self, uint16_t value) {
		self->m_depth = value;
	}
	uint32_t DECL two_Texture__get_memsize(two::Texture* self) {
		return self->m_memsize;
	}
	void DECL two_Texture__set_memsize(two::Texture* self, uint32_t value) {
		self->m_memsize = value;
	}
	uint32_t DECL two_Texture__get_bits_per_pixel(two::Texture* self) {
		return self->m_bits_per_pixel;
	}
	void DECL two_Texture__set_bits_per_pixel(two::Texture* self, uint32_t value) {
		self->m_bits_per_pixel = value;
	}
	bool DECL two_Texture__get_is_depth(two::Texture* self) {
		return self->m_is_depth;
	}
	void DECL two_Texture__set_is_depth(two::Texture* self, bool value) {
		self->m_is_depth = value;
	}
	bool DECL two_Texture__get_is_depth_packed(two::Texture* self) {
		return self->m_is_depth_packed;
	}
	void DECL two_Texture__set_is_depth_packed(two::Texture* self, bool value) {
		self->m_is_depth_packed = value;
	}
	bool DECL two_Texture__get_is_array(two::Texture* self) {
		return self->m_is_array;
	}
	void DECL two_Texture__set_is_array(two::Texture* self, bool value) {
		self->m_is_array = value;
	}
	bool DECL two_Texture__get_is_cube(two::Texture* self) {
		return self->m_is_cube;
	}
	void DECL two_Texture__set_is_cube(two::Texture* self, bool value) {
		self->m_is_cube = value;
	}
	bool DECL two_Texture__get_is_fbo(two::Texture* self) {
		return self->m_is_fbo;
	}
	void DECL two_Texture__set_is_fbo(two::Texture* self, bool value) {
		self->m_is_fbo = value;
	}
	bool DECL two_Texture__get_mips(two::Texture* self) {
		return self->m_mips;
	}
	void DECL two_Texture__set_mips(two::Texture* self, bool value) {
		self->m_mips = value;
	}
	void DECL two_Texture__destroy(two::Texture* self) {
		delete self;
	}
	// Skeleton
	two::Type* DECL two_Skeleton__type() {
		return &two::type<two::Skeleton>();
	}
	void DECL two_Skeleton__destroy(two::Skeleton* self) {
		delete self;
	}
	// Joint
	two::Type* DECL two_Joint__type() {
		return &two::type<two::Joint>();
	}
	two::Joint* DECL two_Joint__construct_0() {
		return new two::Joint();
	}
	void DECL two_Joint__destroy(two::Joint* self) {
		delete self;
	}
	// Skin
	two::Type* DECL two_Skin__type() {
		return &two::type<two::Skin>();
	}
	void DECL two_Skin__destroy(two::Skin* self) {
		delete self;
	}
	// Rig
	two::Type* DECL two_Rig__type() {
		return &two::type<two::Rig>();
	}
	void DECL two_Rig__destroy(two::Rig* self) {
		delete self;
	}
	// AnimNode
	two::Type* DECL two_AnimNode__type() {
		return &two::type<two::AnimNode>();
	}
	two::AnimNode* DECL two_AnimNode__construct_0() {
		return new two::AnimNode();
	}
	two::vec3* DECL two_AnimNode__get_position(two::AnimNode* self) {
		return &self->m_position;
	}
	void DECL two_AnimNode__set_position(two::AnimNode* self, two::vec3* value) {
		self->m_position = *value;
	}
	two::quat* DECL two_AnimNode__get_rotation(two::AnimNode* self) {
		return &self->m_rotation;
	}
	void DECL two_AnimNode__set_rotation(two::AnimNode* self, two::quat* value) {
		self->m_rotation = *value;
	}
	two::vec3* DECL two_AnimNode__get_scale(two::AnimNode* self) {
		return &self->m_scale;
	}
	void DECL two_AnimNode__set_scale(two::AnimNode* self, two::vec3* value) {
		self->m_scale = *value;
	}
	two::mat4* DECL two_AnimNode__get_transform(two::AnimNode* self) {
		return &self->m_transform;
	}
	void DECL two_AnimNode__set_transform(two::AnimNode* self, two::mat4* value) {
		self->m_transform = *value;
	}
	void DECL two_AnimNode__destroy(two::AnimNode* self) {
		delete self;
	}
	// AnimPlay
	two::Type* DECL two_AnimPlay__type() {
		return &two::type<two::AnimPlay>();
	}
	two::AnimPlay* DECL two_AnimPlay__construct_0() {
		return new two::AnimPlay();
	}
	const two::Animation* DECL two_AnimPlay__get_animation(two::AnimPlay* self) {
		return self->m_animation;
	}
	void DECL two_AnimPlay__set_animation(two::AnimPlay* self, const two::Animation* value) {
		self->m_animation = value;
	}
	bool DECL two_AnimPlay__get_loop(two::AnimPlay* self) {
		return self->m_loop;
	}
	void DECL two_AnimPlay__set_loop(two::AnimPlay* self, bool value) {
		self->m_loop = value;
	}
	float DECL two_AnimPlay__get_speed(two::AnimPlay* self) {
		return self->m_speed;
	}
	void DECL two_AnimPlay__set_speed(two::AnimPlay* self, float value) {
		self->m_speed = value;
	}
	bool DECL two_AnimPlay__get_transient(two::AnimPlay* self) {
		return self->m_transient;
	}
	void DECL two_AnimPlay__set_transient(two::AnimPlay* self, bool value) {
		self->m_transient = value;
	}
	float DECL two_AnimPlay__get_fadeout(two::AnimPlay* self) {
		return self->m_fadeout;
	}
	void DECL two_AnimPlay__set_fadeout(two::AnimPlay* self, float value) {
		self->m_fadeout = value;
	}
	float DECL two_AnimPlay__get_fadeout_left(two::AnimPlay* self) {
		return self->m_fadeout_left;
	}
	void DECL two_AnimPlay__set_fadeout_left(two::AnimPlay* self, float value) {
		self->m_fadeout_left = value;
	}
	float DECL two_AnimPlay__get_cursor(two::AnimPlay* self) {
		return self->m_cursor;
	}
	void DECL two_AnimPlay__set_cursor(two::AnimPlay* self, float value) {
		self->m_cursor = value;
	}
	bool DECL two_AnimPlay__get_ended(two::AnimPlay* self) {
		return self->m_ended;
	}
	void DECL two_AnimPlay__set_ended(two::AnimPlay* self, bool value) {
		self->m_ended = value;
	}
	void DECL two_AnimPlay__destroy(two::AnimPlay* self) {
		delete self;
	}
	// Mime
	two::Type* DECL two_Mime__type() {
		return &two::type<two::Mime>();
	}
	two::Mime* DECL two_Mime__construct_0() {
		return new two::Mime();
	}
	void DECL two_Mime_start_2(two::Mime* self, const char* animation, bool loop) {
		self->start(animation, loop);
	}
	void DECL two_Mime_start_3(two::Mime* self, const char* animation, bool loop, float blend) {
		self->start(animation, loop, blend);
	}
	void DECL two_Mime_start_4(two::Mime* self, const char* animation, bool loop, float blend, float speed) {
		self->start(animation, loop, blend, speed);
	}
	void DECL two_Mime_start_5(two::Mime* self, const char* animation, bool loop, float blend, float speed, bool transient) {
		self->start(animation, loop, blend, speed, transient);
	}
	void DECL two_Mime_play_2(two::Mime* self, const two::Animation* animation, bool loop) {
		self->play(*animation, loop);
	}
	void DECL two_Mime_play_3(two::Mime* self, const two::Animation* animation, bool loop, float blend) {
		self->play(*animation, loop, blend);
	}
	void DECL two_Mime_play_4(two::Mime* self, const two::Animation* animation, bool loop, float blend, float speed) {
		self->play(*animation, loop, blend, speed);
	}
	void DECL two_Mime_play_5(two::Mime* self, const two::Animation* animation, bool loop, float blend, float speed, bool transient) {
		self->play(*animation, loop, blend, speed, transient);
	}
	void DECL two_Mime_seek_1(two::Mime* self, float time) {
		self->seek(time);
	}
	void DECL two_Mime_pause_0(two::Mime* self) {
		self->pause();
	}
	void DECL two_Mime_stop_0(two::Mime* self) {
		self->stop();
	}
	void DECL two_Mime_advance_1(two::Mime* self, float time) {
		self->advance(time);
	}
	void DECL two_Mime_next_animation_0(two::Mime* self) {
		self->next_animation();
	}
	void DECL two_Mime_add_item_1(two::Mime* self, two::Item* item) {
		self->add_item(*item);
	}
	const char* DECL two_Mime_playing_0(two::Mime* self) {
		return self->playing().c_str();
	}
	bool DECL two_Mime__get_active(two::Mime* self) {
		return self->m_active;
	}
	void DECL two_Mime__set_active(two::Mime* self, bool value) {
		self->m_active = value;
	}
	float DECL two_Mime__get_speed_scale(two::Mime* self) {
		return self->m_speed_scale;
	}
	void DECL two_Mime__set_speed_scale(two::Mime* self, float value) {
		self->m_speed_scale = value;
	}
	float DECL two_Mime__get_default_blend_time(two::Mime* self) {
		return self->m_default_blend_time;
	}
	void DECL two_Mime__set_default_blend_time(two::Mime* self, float value) {
		self->m_default_blend_time = value;
	}
	void DECL two_Mime__destroy(two::Mime* self) {
		delete self;
	}
	// Frustum
	two::Type* DECL two_Frustum__type() {
		return &two::type<two::Frustum>();
	}
	float DECL two_Frustum__get_fov(two::Frustum* self) {
		return self->m_fov;
	}
	void DECL two_Frustum__set_fov(two::Frustum* self, float value) {
		self->m_fov = value;
	}
	float DECL two_Frustum__get_aspect(two::Frustum* self) {
		return self->m_aspect;
	}
	void DECL two_Frustum__set_aspect(two::Frustum* self, float value) {
		self->m_aspect = value;
	}
	float DECL two_Frustum__get_near(two::Frustum* self) {
		return self->m_near;
	}
	void DECL two_Frustum__set_near(two::Frustum* self, float value) {
		self->m_near = value;
	}
	float DECL two_Frustum__get_far(two::Frustum* self) {
		return self->m_far;
	}
	void DECL two_Frustum__set_far(two::Frustum* self, float value) {
		self->m_far = value;
	}
	two::vec3* DECL two_Frustum__get_center(two::Frustum* self) {
		return &self->m_center;
	}
	void DECL two_Frustum__set_center(two::Frustum* self, two::vec3* value) {
		self->m_center = *value;
	}
	float DECL two_Frustum__get_radius(two::Frustum* self) {
		return self->m_radius;
	}
	void DECL two_Frustum__set_radius(two::Frustum* self, float value) {
		self->m_radius = value;
	}
	void DECL two_Frustum__destroy(two::Frustum* self) {
		delete self;
	}
	// FrustumSlice
	two::Type* DECL two_FrustumSlice__type() {
		return &two::type<two::FrustumSlice>();
	}
	two::FrustumSlice* DECL two_FrustumSlice__construct_0() {
		return new two::FrustumSlice();
	}
	void DECL two_FrustumSlice__destroy(two::FrustumSlice* self) {
		delete self;
	}
	// ShaderDefine
	two::Type* DECL two_ShaderDefine__type() {
		return &two::type<two::ShaderDefine>();
	}
	two::ShaderDefine* DECL two_ShaderDefine__construct_0() {
		return new two::ShaderDefine();
	}
	const char* DECL two_ShaderDefine__get_name(two::ShaderDefine* self) {
		return self->m_name.c_str();
	}
	void DECL two_ShaderDefine__set_name(two::ShaderDefine* self, const char* value) {
		self->m_name = value;
	}
	const char* DECL two_ShaderDefine__get_value(two::ShaderDefine* self) {
		return self->m_value.c_str();
	}
	void DECL two_ShaderDefine__set_value(two::ShaderDefine* self, const char* value) {
		self->m_value = value;
	}
	void DECL two_ShaderDefine__destroy(two::ShaderDefine* self) {
		delete self;
	}
	// ShaderBlock
	two::Type* DECL two_ShaderBlock__type() {
		return &two::type<two::ShaderBlock>();
	}
	two::ShaderBlock* DECL two_ShaderBlock__construct_0() {
		return new two::ShaderBlock();
	}
	void DECL two_ShaderBlock_add_option_1(two::ShaderBlock* self, const char* name) {
		self->add_option(name);
	}
	void DECL two_ShaderBlock_add_mode_1(two::ShaderBlock* self, const char* name) {
		self->add_mode(name);
	}
	void DECL two_ShaderBlock_add_define_2(two::ShaderBlock* self, const char* name, const char* value) {
		self->add_define(name, value);
	}
	uint8_t DECL two_ShaderBlock__get_index(two::ShaderBlock* self) {
		return self->m_index;
	}
	void DECL two_ShaderBlock__set_index(two::ShaderBlock* self, uint8_t value) {
		self->m_index = value;
	}
	void DECL two_ShaderBlock__destroy(two::ShaderBlock* self) {
		delete self;
	}
	// ProgramMode
	two::Type* DECL two_ProgramMode__type() {
		return &two::type<two::ProgramMode>();
	}
	two::ProgramMode* DECL two_ProgramMode__construct_0() {
		return new two::ProgramMode();
	}
	const char* DECL two_ProgramMode__get_name(two::ProgramMode* self) {
		return self->name.c_str();
	}
	void DECL two_ProgramMode__set_name(two::ProgramMode* self, const char* value) {
		self->name = value;
	}
	uint32_t DECL two_ProgramMode__get_size(two::ProgramMode* self) {
		return self->size;
	}
	void DECL two_ProgramMode__set_size(two::ProgramMode* self, uint32_t value) {
		self->size = value;
	}
	uint32_t DECL two_ProgramMode__get_shift(two::ProgramMode* self) {
		return self->shift;
	}
	void DECL two_ProgramMode__set_shift(two::ProgramMode* self, uint32_t value) {
		self->shift = value;
	}
	uint32_t DECL two_ProgramMode__get_mask(two::ProgramMode* self) {
		return self->mask;
	}
	void DECL two_ProgramMode__set_mask(two::ProgramMode* self, uint32_t value) {
		self->mask = value;
	}
	void DECL two_ProgramMode__destroy(two::ProgramMode* self) {
		delete self;
	}
	// ProgramBlock
	two::Type* DECL two_ProgramBlock__type() {
		return &two::type<two::ProgramBlock>();
	}
	two::ProgramBlock* DECL two_ProgramBlock__construct_0() {
		return new two::ProgramBlock();
	}
	bool DECL two_ProgramBlock__get_enabled(two::ProgramBlock* self) {
		return self->m_enabled;
	}
	void DECL two_ProgramBlock__set_enabled(two::ProgramBlock* self, bool value) {
		self->m_enabled = value;
	}
	uint8_t DECL two_ProgramBlock__get_option_shift(two::ProgramBlock* self) {
		return self->m_option_shift;
	}
	void DECL two_ProgramBlock__set_option_shift(two::ProgramBlock* self, uint8_t value) {
		self->m_option_shift = value;
	}
	uint8_t DECL two_ProgramBlock__get_mode_shift(two::ProgramBlock* self) {
		return self->m_mode_shift;
	}
	void DECL two_ProgramBlock__set_mode_shift(two::ProgramBlock* self, uint8_t value) {
		self->m_mode_shift = value;
	}
	void DECL two_ProgramBlock__destroy(two::ProgramBlock* self) {
		delete self;
	}
	// Program
	two::Type* DECL two_Program__type() {
		return &two::type<two::Program>();
	}
	void DECL two_Program_set_block_1(two::Program* self, two::MaterialBlock block) {
		self->set_block(block);
	}
	void DECL two_Program_set_block_2(two::Program* self, two::MaterialBlock block, bool enabled) {
		self->set_block(block, enabled);
	}
	void DECL two_Program_set_pass_1(two::Program* self, two::PassType type) {
		self->set_pass(type);
	}
	void DECL two_Program_set_pass_2(two::Program* self, two::PassType type, bool enabled) {
		self->set_pass(type, enabled);
	}
	void DECL two_Program_set_source_2(two::Program* self, two::ShaderType type, const char* source) {
		self->set_source(type, source);
	}
	void DECL two_Program_register_blocks_1(two::Program* self, const two::Program* program) {
		self->register_blocks(*program);
	}
	void DECL two_Program_register_block_1(two::Program* self, const two::ShaderBlock* block) {
		self->register_block(*block);
	}
	const char* DECL two_Program__get_name(two::Program* self) {
		return self->m_name.c_str();
	}
	void DECL two_Program__set_name(two::Program* self, const char* value) {
		self->m_name = value;
	}
	void DECL two_Program__destroy(two::Program* self) {
		delete self;
	}
	// ProgramVersion
	two::Type* DECL two_ProgramVersion__type() {
		return &two::type<two::ProgramVersion>();
	}
	two::ProgramVersion* DECL two_ProgramVersion__construct_0() {
		return new two::ProgramVersion();
	}
	two::ProgramVersion* DECL two_ProgramVersion__construct_1(const two::Program* program) {
		return new two::ProgramVersion(*program);
	}
	void DECL two_ProgramVersion_clear_0(two::ProgramVersion* self) {
		self->clear();
	}
	void DECL two_ProgramVersion_set_option_2(two::ProgramVersion* self, uint8_t block, uint8_t option) {
		self->set_option(block, option);
	}
	void DECL two_ProgramVersion_set_option_3(two::ProgramVersion* self, uint8_t block, uint8_t option, bool active) {
		self->set_option(block, option, active);
	}
	void DECL two_ProgramVersion_set_mode_3(two::ProgramVersion* self, uint8_t block, uint8_t mode, uint8_t value) {
		self->set_mode(block, mode, value);
	}
	uint64_t DECL two_ProgramVersion_hash_0(two::ProgramVersion* self) {
		return self->hash();
	}
	void DECL two_ProgramVersion__destroy(two::ProgramVersion* self) {
		delete self;
	}
	// Shot
	two::Type* DECL two_Shot__type() {
		return &two::type<two::Shot>();
	}
	void DECL two_Shot__destroy(two::Shot* self) {
		delete self;
	}
	// Pass
	two::Type* DECL two_Pass__type() {
		return &two::type<two::Pass>();
	}
	two::Pass* DECL two_Pass__construct_0() {
		return new two::Pass();
	}
	const char* DECL two_Pass__get_name(two::Pass* self) {
		return self->m_name.c_str();
	}
	void DECL two_Pass__set_name(two::Pass* self, const char* value) {
		self->m_name = value;
	}
	two::RenderTarget* DECL two_Pass__get_target(two::Pass* self) {
		return self->m_target;
	}
	void DECL two_Pass__set_target(two::Pass* self, two::RenderTarget* value) {
		self->m_target = value;
	}
	two::FrameBuffer* DECL two_Pass__get_fbo(two::Pass* self) {
		return self->m_fbo;
	}
	void DECL two_Pass__set_fbo(two::Pass* self, two::FrameBuffer* value) {
		self->m_fbo = value;
	}
	two::Viewport* DECL two_Pass__get_viewport(two::Pass* self) {
		return self->m_viewport;
	}
	void DECL two_Pass__set_viewport(two::Pass* self, two::Viewport* value) {
		self->m_viewport = value;
	}
	two::vec4* DECL two_Pass__get_rect(two::Pass* self) {
		return &self->m_rect;
	}
	void DECL two_Pass__set_rect(two::Pass* self, two::vec4* value) {
		self->m_rect = *value;
	}
	uint64_t DECL two_Pass__get_bgfx_state(two::Pass* self) {
		return self->m_bgfx_state;
	}
	void DECL two_Pass__set_bgfx_state(two::Pass* self, uint64_t value) {
		self->m_bgfx_state = value;
	}
	two::PassType DECL two_Pass__get_pass_type(two::Pass* self) {
		return self->m_pass_type;
	}
	void DECL two_Pass__set_pass_type(two::Pass* self, two::PassType value) {
		self->m_pass_type = value;
	}
	bool DECL two_Pass__get_use_mrt(two::Pass* self) {
		return self->m_use_mrt;
	}
	void DECL two_Pass__set_use_mrt(two::Pass* self, bool value) {
		self->m_use_mrt = value;
	}
	uint8_t DECL two_Pass__get_index(two::Pass* self) {
		return self->m_index;
	}
	void DECL two_Pass__set_index(two::Pass* self, uint8_t value) {
		self->m_index = value;
	}
	void DECL two_Pass__destroy(two::Pass* self) {
		delete self;
	}
	// RenderFrame
	two::Type* DECL two_RenderFrame__type() {
		return &two::type<two::RenderFrame>();
	}
	two::RenderFrame* DECL two_RenderFrame__construct_0() {
		return new two::RenderFrame();
	}
	uint32_t DECL two_RenderFrame__get_frame(two::RenderFrame* self) {
		return self->m_frame;
	}
	void DECL two_RenderFrame__set_frame(two::RenderFrame* self, uint32_t value) {
		self->m_frame = value;
	}
	float DECL two_RenderFrame__get_time(two::RenderFrame* self) {
		return self->m_time;
	}
	void DECL two_RenderFrame__set_time(two::RenderFrame* self, float value) {
		self->m_time = value;
	}
	float DECL two_RenderFrame__get_delta_time(two::RenderFrame* self) {
		return self->m_delta_time;
	}
	void DECL two_RenderFrame__set_delta_time(two::RenderFrame* self, float value) {
		self->m_delta_time = value;
	}
	uint8_t DECL two_RenderFrame__get_render_pass(two::RenderFrame* self) {
		return self->m_render_pass;
	}
	void DECL two_RenderFrame__set_render_pass(two::RenderFrame* self, uint8_t value) {
		self->m_render_pass = value;
	}
	uint32_t DECL two_RenderFrame__get_nudraw_calls(two::RenderFrame* self) {
		return self->m_num_draw_calls;
	}
	void DECL two_RenderFrame__set_nudraw_calls(two::RenderFrame* self, uint32_t value) {
		self->m_num_draw_calls = value;
	}
	uint32_t DECL two_RenderFrame__get_nuvertices(two::RenderFrame* self) {
		return self->m_num_vertices;
	}
	void DECL two_RenderFrame__set_nuvertices(two::RenderFrame* self, uint32_t value) {
		self->m_num_vertices = value;
	}
	uint32_t DECL two_RenderFrame__get_nutriangles(two::RenderFrame* self) {
		return self->m_num_triangles;
	}
	void DECL two_RenderFrame__set_nutriangles(two::RenderFrame* self, uint32_t value) {
		self->m_num_triangles = value;
	}
	void DECL two_RenderFrame__destroy(two::RenderFrame* self) {
		delete self;
	}
	// Render
	two::Type* DECL two_Render__type() {
		return &two::type<two::Render>();
	}
	two::Render* DECL two_Render__construct_0() {
		return new two::Render();
	}
	two::Render* DECL two_Render__construct_4(two::Shading shading, two::Viewport* viewport, two::RenderTarget* target, two::RenderFrame* frame) {
		return new two::Render(shading, *viewport, *target, *frame);
	}
	two::Render* DECL two_Render__construct_5(two::Shading shading, two::Viewport* viewport, two::RenderTarget* target, two::FrameBuffer* target_fbo, two::RenderFrame* frame) {
		return new two::Render(shading, *viewport, *target, *target_fbo, *frame);
	}
	void DECL two_Render_subrender_1(two::Render* self, const two::Render* render) {
		self->subrender(*render);
	}
	two::Pass* DECL two_Render_next_pass_2(two::Render* self, const char* name, two::PassType type) {
		static two::Pass temp;
		return (temp = self->next_pass(name, type), &temp);
	}
	two::Pass* DECL two_Render_next_pass_3(two::Render* self, const char* name, two::PassType type, uint8_t index) {
		static two::Pass temp;
		return (temp = self->next_pass(name, type, index), &temp);
	}
	two::Pass* DECL two_Render_composite_pass_3(two::Render* self, const char* name, two::FrameBuffer* fbo, const two::vec4* rect) {
		static two::Pass temp;
		return (temp = self->composite_pass(name, *fbo, *rect), &temp);
	}
	two::Shading DECL two_Render__get_shading(two::Render* self) {
		return self->m_shading;
	}
	void DECL two_Render__set_shading(two::Render* self, two::Shading value) {
		self->m_shading = value;
	}
	two::Scene* DECL two_Render__get_scene(two::Render* self) {
		return self->m_scene;
	}
	void DECL two_Render__set_scene(two::Render* self, two::Scene* value) {
		self->m_scene = value;
	}
	two::RenderTarget* DECL two_Render__get_target(two::Render* self) {
		return self->m_target;
	}
	void DECL two_Render__set_target(two::Render* self, two::RenderTarget* value) {
		self->m_target = value;
	}
	two::FrameBuffer* DECL two_Render__get_fbo(two::Render* self) {
		return self->m_fbo;
	}
	void DECL two_Render__set_fbo(two::Render* self, two::FrameBuffer* value) {
		self->m_fbo = value;
	}
	two::Viewport* DECL two_Render__get_viewport(two::Render* self) {
		return self->m_viewport;
	}
	void DECL two_Render__set_viewport(two::Render* self, two::Viewport* value) {
		self->m_viewport = value;
	}
	two::vec4* DECL two_Render__get_rect(two::Render* self) {
		return &self->m_rect;
	}
	void DECL two_Render__set_rect(two::Render* self, two::vec4* value) {
		self->m_rect = *value;
	}
	two::Camera* DECL two_Render__get_camera(two::Render* self) {
		return self->m_camera;
	}
	void DECL two_Render__set_camera(two::Render* self, two::Camera* value) {
		self->m_camera = value;
	}
	two::RenderFrame* DECL two_Render__get_frame(two::Render* self) {
		return self->m_frame;
	}
	void DECL two_Render__set_frame(two::Render* self, two::RenderFrame* value) {
		self->m_frame = value;
	}
	two::Frustum* DECL two_Render__get_frustum(two::Render* self) {
		return &self->m_frustum;
	}
	two::Zone* DECL two_Render__get_env(two::Render* self) {
		return self->m_env;
	}
	void DECL two_Render__set_env(two::Render* self, two::Zone* value) {
		self->m_env = value;
	}
	two::Lighting DECL two_Render__get_lighting(two::Render* self) {
		return self->m_lighting;
	}
	void DECL two_Render__set_lighting(two::Render* self, two::Lighting value) {
		self->m_lighting = value;
	}
	bool DECL two_Render__get_vflip(two::Render* self) {
		return self->m_vflip;
	}
	void DECL two_Render__set_vflip(two::Render* self, bool value) {
		self->m_vflip = value;
	}
	bool DECL two_Render__get_needs_mrt(two::Render* self) {
		return self->m_needs_mrt;
	}
	void DECL two_Render__set_needs_mrt(two::Render* self, bool value) {
		self->m_needs_mrt = value;
	}
	bool DECL two_Render__get_is_mrt(two::Render* self) {
		return self->m_is_mrt;
	}
	void DECL two_Render__set_is_mrt(two::Render* self, bool value) {
		self->m_is_mrt = value;
	}
	uint8_t DECL two_Render__get_pass_index(two::Render* self) {
		return self->m_pass_index;
	}
	void DECL two_Render__set_pass_index(two::Render* self, uint8_t value) {
		self->m_pass_index = value;
	}
	void DECL two_Render__destroy(two::Render* self) {
		delete self;
	}
	// GfxBlock
	two::Type* DECL two_GfxBlock__type() {
		return &two::type<two::GfxBlock>();
	}
	two::Type* DECL two_GfxBlock__get_type(two::GfxBlock* self) {
		return &self->m_type;
	}
	void DECL two_GfxBlock__destroy(two::GfxBlock* self) {
		delete self;
	}
	// DrawBlock
	two::Type* DECL two_DrawBlock__type() {
		return &two::type<two::DrawBlock>();
	}
	void DECL two_DrawBlock__destroy(two::DrawBlock* self) {
		delete self;
	}
	// Renderer
	two::Type* DECL two_Renderer__type() {
		return &two::type<two::Renderer>();
	}
	void DECL two_Renderer_gather_1(two::Renderer* self, two::Render* render) {
		self->gather(*render);
	}
	void DECL two_Renderer_begin_1(two::Renderer* self, two::Render* render) {
		self->begin(*render);
	}
	void DECL two_Renderer_end_1(two::Renderer* self, two::Render* render) {
		self->end(*render);
	}
	void DECL two_Renderer__destroy(two::Renderer* self) {
		delete self;
	}
	// GfxWindow
	two::Type* DECL two_GfxWindow__type() {
		return &two::type<two::GfxWindow>();
	}
	void DECL two_GfxWindow__destroy(two::GfxWindow* self) {
		delete self;
	}
	// GfxSystem
	two::Type* DECL two_GfxSystem__type() {
		return &two::type<two::GfxSystem>();
	}
	two::GfxSystem* DECL two_GfxSystem__construct_1(const char* resource_path) {
		return new two::GfxSystem(resource_path);
	}
	two::RenderTarget* DECL two_GfxSystem_main_target_0(two::GfxSystem* self) {
		return &self->main_target();
	}
	void DECL two_GfxSystem_default_pipeline_0(two::GfxSystem* self) {
		self->default_pipeline();
	}
	void DECL two_GfxSystem_add_resource_path_1(two::GfxSystem* self, const char* path) {
		self->add_resource_path(path);
	}
	void DECL two_GfxSystem_add_resource_path_2(two::GfxSystem* self, const char* path, bool relative) {
		self->add_resource_path(path, relative);
	}
	two::Material* DECL two_GfxSystem_debug_material_0(two::GfxSystem* self) {
		return &self->debug_material();
	}
	two::Model* DECL two_GfxSystem_create_model_1(two::GfxSystem* self, const char* name) {
		return &self->create_model(name);
	}
	two::Model* DECL two_GfxSystem_create_model_geo_2(two::GfxSystem* self, const char* name, const two::MeshPacker* geometry) {
		return &self->create_model_geo(name, *geometry);
	}
	two::Model* DECL two_GfxSystem_create_model_geo_3(two::GfxSystem* self, const char* name, const two::MeshPacker* geometry, bool readback) {
		return &self->create_model_geo(name, *geometry, readback);
	}
	two::Model* DECL two_GfxSystem_create_model_geo_4(two::GfxSystem* self, const char* name, const two::MeshPacker* geometry, bool readback, bool optimize) {
		return &self->create_model_geo(name, *geometry, readback, optimize);
	}
	two::Model* DECL two_GfxSystem_create_model_gpu_2(two::GfxSystem* self, const char* name, const two::GpuMesh* gpu_mesh) {
		return &self->create_model_gpu(name, *gpu_mesh);
	}
	two::Model* DECL two_GfxSystem_create_model_gpu_3(two::GfxSystem* self, const char* name, const two::GpuMesh* gpu_mesh, bool readback) {
		return &self->create_model_gpu(name, *gpu_mesh, readback);
	}
	two::Model* DECL two_GfxSystem_create_model_gpu_4(two::GfxSystem* self, const char* name, const two::GpuMesh* gpu_mesh, bool readback, bool optimize) {
		return &self->create_model_gpu(name, *gpu_mesh, readback, optimize);
	}
	two::Material* DECL two_GfxSystem_fetch_material_2(two::GfxSystem* self, const char* name, const char* shader) {
		return &self->fetch_material(name, shader);
	}
	two::Material* DECL two_GfxSystem_fetch_material_3(two::GfxSystem* self, const char* name, const char* shader, bool builtin) {
		return &self->fetch_material(name, shader, builtin);
	}
	two::Material* DECL two_GfxSystem_fetch_image256_material_1(two::GfxSystem* self, const two::Image256* image) {
		return &self->fetch_image256_material(*image);
	}
	two::Model* DECL two_GfxSystem_shape_1(two::GfxSystem* self, const two::Shape* shape) {
		return &self->shape(*shape);
	}
	two::Model* DECL two_GfxSystem_shape_2(two::GfxSystem* self, const two::Shape* shape, const two::Symbol* symbol) {
		return &self->shape(*shape, *symbol);
	}
	two::Model* DECL two_GfxSystem_shape_3(two::GfxSystem* self, const two::Shape* shape, const two::Symbol* symbol, two::DrawMode draw_mode) {
		return &self->shape(*shape, *symbol, draw_mode);
	}
	two::Material* DECL two_GfxSystem_symbol_material_1(two::GfxSystem* self, const two::Symbol* symbol) {
		return &self->symbol_material(*symbol);
	}
	two::Material* DECL two_GfxSystem_symbol_material_2(two::GfxSystem* self, const two::Symbol* symbol, two::DrawMode draw_mode) {
		return &self->symbol_material(*symbol, draw_mode);
	}
	two::Renderer* DECL two_GfxSystem__get_renderer(two::GfxSystem* self) {
		return &self->m_renderer;
	}
	two::BlockCopy* DECL two_GfxSystem__get_copy(two::GfxSystem* self) {
		return self->m_copy;
	}
	void DECL two_GfxSystem__set_copy(two::GfxSystem* self, two::BlockCopy* value) {
		self->m_copy = value;
	}
	two::BlockFilter* DECL two_GfxSystem__get_filter(two::GfxSystem* self) {
		return self->m_filter;
	}
	void DECL two_GfxSystem__set_filter(two::GfxSystem* self, two::BlockFilter* value) {
		self->m_filter = value;
	}
	bool DECL two_GfxSystem__get_flip_y(two::GfxSystem* self) {
		return self->m_flip_y;
	}
	void DECL two_GfxSystem__set_flip_y(two::GfxSystem* self, bool value) {
		self->m_flip_y = value;
	}
	two::RenderFrame* DECL two_GfxSystem__get_render_frame(two::GfxSystem* self) {
		return &self->m_render_frame;
	}
	void DECL two_GfxSystem__set_render_frame(two::GfxSystem* self, two::RenderFrame* value) {
		self->m_render_frame = *value;
	}
	two::AssetStore<two::Texture>* DECL two_GfxSystem__get_textures(two::GfxSystem* self) {
		return &self->textures();
	}
	two::AssetStore<two::Program>* DECL two_GfxSystem__get_programs(two::GfxSystem* self) {
		return &self->programs();
	}
	two::AssetStore<two::Material>* DECL two_GfxSystem__get_materials(two::GfxSystem* self) {
		return &self->materials();
	}
	two::AssetStore<two::Model>* DECL two_GfxSystem__get_models(two::GfxSystem* self) {
		return &self->models();
	}
	two::AssetStore<two::Flow>* DECL two_GfxSystem__get_flows(two::GfxSystem* self) {
		return &self->flows();
	}
	two::AssetStore<two::Prefab>* DECL two_GfxSystem__get_prefabs(two::GfxSystem* self) {
		return &self->prefabs();
	}
	void DECL two_GfxSystem__destroy(two::GfxSystem* self) {
		delete self;
	}
	// MaterialParam<two::Colour>
	two::Type* DECL two_MaterialParam_two_Colour__type() {
		return &two::type<two::MaterialParam<two::Colour>>();
	}
	two::MaterialParam<two::Colour>* DECL two_MaterialParam_two_Colour__construct_0() {
		return new two::MaterialParam<two::Colour>();
	}
	two::Colour* DECL two_MaterialParam_two_Colour__get_value(two::MaterialParam<two::Colour>* self) {
		return &self->m_value;
	}
	void DECL two_MaterialParam_two_Colour__set_value(two::MaterialParam<two::Colour>* self, two::Colour* value) {
		self->m_value = *value;
	}
	two::Texture* DECL two_MaterialParam_two_Colour__get_texture(two::MaterialParam<two::Colour>* self) {
		return self->m_texture;
	}
	void DECL two_MaterialParam_two_Colour__set_texture(two::MaterialParam<two::Colour>* self, two::Texture* value) {
		self->m_texture = value;
	}
	two::TextureChannel DECL two_MaterialParam_two_Colour__get_channel(two::MaterialParam<two::Colour>* self) {
		return self->m_channel;
	}
	void DECL two_MaterialParam_two_Colour__set_channel(two::MaterialParam<two::Colour>* self, two::TextureChannel value) {
		self->m_channel = value;
	}
	void DECL two_MaterialParam_two_Colour__destroy(two::MaterialParam<two::Colour>* self) {
		delete self;
	}
	// MaterialParam<float>
	two::Type* DECL two_MaterialParam_float__type() {
		return &two::type<two::MaterialParam<float>>();
	}
	two::MaterialParam<float>* DECL two_MaterialParam_float__construct_0() {
		return new two::MaterialParam<float>();
	}
	float DECL two_MaterialParam_float__get_value(two::MaterialParam<float>* self) {
		return self->m_value;
	}
	void DECL two_MaterialParam_float__set_value(two::MaterialParam<float>* self, float value) {
		self->m_value = value;
	}
	two::Texture* DECL two_MaterialParam_float__get_texture(two::MaterialParam<float>* self) {
		return self->m_texture;
	}
	void DECL two_MaterialParam_float__set_texture(two::MaterialParam<float>* self, two::Texture* value) {
		self->m_texture = value;
	}
	two::TextureChannel DECL two_MaterialParam_float__get_channel(two::MaterialParam<float>* self) {
		return self->m_channel;
	}
	void DECL two_MaterialParam_float__set_channel(two::MaterialParam<float>* self, two::TextureChannel value) {
		self->m_channel = value;
	}
	void DECL two_MaterialParam_float__destroy(two::MaterialParam<float>* self) {
		delete self;
	}
	// MaterialParam<two::vec4>
	two::Type* DECL two_MaterialParam_two_vec4__type() {
		return &two::type<two::MaterialParam<two::vec4>>();
	}
	two::MaterialParam<two::vec4>* DECL two_MaterialParam_two_vec4__construct_0() {
		return new two::MaterialParam<two::vec4>();
	}
	two::vec4* DECL two_MaterialParam_two_vec4__get_value(two::MaterialParam<two::vec4>* self) {
		return &self->m_value;
	}
	void DECL two_MaterialParam_two_vec4__set_value(two::MaterialParam<two::vec4>* self, two::vec4* value) {
		self->m_value = *value;
	}
	two::Texture* DECL two_MaterialParam_two_vec4__get_texture(two::MaterialParam<two::vec4>* self) {
		return self->m_texture;
	}
	void DECL two_MaterialParam_two_vec4__set_texture(two::MaterialParam<two::vec4>* self, two::Texture* value) {
		self->m_texture = value;
	}
	two::TextureChannel DECL two_MaterialParam_two_vec4__get_channel(two::MaterialParam<two::vec4>* self) {
		return self->m_channel;
	}
	void DECL two_MaterialParam_two_vec4__set_channel(two::MaterialParam<two::vec4>* self, two::TextureChannel value) {
		self->m_channel = value;
	}
	void DECL two_MaterialParam_two_vec4__destroy(two::MaterialParam<two::vec4>* self) {
		delete self;
	}
	// MaterialBase
	two::Type* DECL two_MaterialBase__type() {
		return &two::type<two::MaterialBase>();
	}
	two::MaterialBase* DECL two_MaterialBase__construct_0() {
		return new two::MaterialBase();
	}
	two::BlendMode DECL two_MaterialBase__get_blend_mode(two::MaterialBase* self) {
		return self->m_blend_mode;
	}
	void DECL two_MaterialBase__set_blend_mode(two::MaterialBase* self, two::BlendMode value) {
		self->m_blend_mode = value;
	}
	two::CullMode DECL two_MaterialBase__get_cull_mode(two::MaterialBase* self) {
		return self->m_cull_mode;
	}
	void DECL two_MaterialBase__set_cull_mode(two::MaterialBase* self, two::CullMode value) {
		self->m_cull_mode = value;
	}
	two::DepthDraw DECL two_MaterialBase__get_depth_draw(two::MaterialBase* self) {
		return self->m_depth_draw;
	}
	void DECL two_MaterialBase__set_depth_draw(two::MaterialBase* self, two::DepthDraw value) {
		self->m_depth_draw = value;
	}
	two::DepthTest DECL two_MaterialBase__get_depth_test(two::MaterialBase* self) {
		return self->m_depth_test;
	}
	void DECL two_MaterialBase__set_depth_test(two::MaterialBase* self, two::DepthTest value) {
		self->m_depth_test = value;
	}
	two::vec2* DECL two_MaterialBase__get_uv0_scale(two::MaterialBase* self) {
		return &self->m_uv0_scale;
	}
	void DECL two_MaterialBase__set_uv0_scale(two::MaterialBase* self, two::vec2* value) {
		self->m_uv0_scale = *value;
	}
	two::vec2* DECL two_MaterialBase__get_uv0_offset(two::MaterialBase* self) {
		return &self->m_uv0_offset;
	}
	void DECL two_MaterialBase__set_uv0_offset(two::MaterialBase* self, two::vec2* value) {
		self->m_uv0_offset = *value;
	}
	two::vec2* DECL two_MaterialBase__get_uv1_scale(two::MaterialBase* self) {
		return &self->m_uv1_scale;
	}
	void DECL two_MaterialBase__set_uv1_scale(two::MaterialBase* self, two::vec2* value) {
		self->m_uv1_scale = *value;
	}
	two::vec2* DECL two_MaterialBase__get_uv1_offset(two::MaterialBase* self) {
		return &self->m_uv1_offset;
	}
	void DECL two_MaterialBase__set_uv1_offset(two::MaterialBase* self, two::vec2* value) {
		self->m_uv1_offset = *value;
	}
	two::ShaderColor DECL two_MaterialBase__get_shader_color(two::MaterialBase* self) {
		return self->m_shader_color;
	}
	void DECL two_MaterialBase__set_shader_color(two::MaterialBase* self, two::ShaderColor value) {
		self->m_shader_color = value;
	}
	bool DECL two_MaterialBase__get_flat_shaded(two::MaterialBase* self) {
		return self->m_flat_shaded;
	}
	void DECL two_MaterialBase__set_flat_shaded(two::MaterialBase* self, bool value) {
		self->m_flat_shaded = value;
	}
	bool DECL two_MaterialBase__get_screen_filter(two::MaterialBase* self) {
		return self->m_screen_filter;
	}
	void DECL two_MaterialBase__set_screen_filter(two::MaterialBase* self, bool value) {
		self->m_screen_filter = value;
	}
	float DECL two_MaterialBase__get_anisotropy(two::MaterialBase* self) {
		return self->m_anisotropy;
	}
	void DECL two_MaterialBase__set_anisotropy(two::MaterialBase* self, float value) {
		self->m_anisotropy = value;
	}
	void DECL two_MaterialBase__destroy(two::MaterialBase* self) {
		delete self;
	}
	// MaterialUser
	two::Type* DECL two_MaterialUser__type() {
		return &two::type<two::MaterialUser>();
	}
	two::MaterialUser* DECL two_MaterialUser__construct_0() {
		return new two::MaterialUser();
	}
	two::Texture* DECL two_MaterialUser__get_tex0(two::MaterialUser* self) {
		return self->m_tex0;
	}
	void DECL two_MaterialUser__set_tex0(two::MaterialUser* self, two::Texture* value) {
		self->m_tex0 = value;
	}
	two::Texture* DECL two_MaterialUser__get_tex1(two::MaterialUser* self) {
		return self->m_tex1;
	}
	void DECL two_MaterialUser__set_tex1(two::MaterialUser* self, two::Texture* value) {
		self->m_tex1 = value;
	}
	two::Texture* DECL two_MaterialUser__get_tex2(two::MaterialUser* self) {
		return self->m_tex2;
	}
	void DECL two_MaterialUser__set_tex2(two::MaterialUser* self, two::Texture* value) {
		self->m_tex2 = value;
	}
	two::Texture* DECL two_MaterialUser__get_tex3(two::MaterialUser* self) {
		return self->m_tex3;
	}
	void DECL two_MaterialUser__set_tex3(two::MaterialUser* self, two::Texture* value) {
		self->m_tex3 = value;
	}
	two::Texture* DECL two_MaterialUser__get_tex4(two::MaterialUser* self) {
		return self->m_tex4;
	}
	void DECL two_MaterialUser__set_tex4(two::MaterialUser* self, two::Texture* value) {
		self->m_tex4 = value;
	}
	two::Texture* DECL two_MaterialUser__get_tex5(two::MaterialUser* self) {
		return self->m_tex5;
	}
	void DECL two_MaterialUser__set_tex5(two::MaterialUser* self, two::Texture* value) {
		self->m_tex5 = value;
	}
	two::vec4* DECL two_MaterialUser__get_attr0(two::MaterialUser* self) {
		return &self->m_attr0;
	}
	void DECL two_MaterialUser__set_attr0(two::MaterialUser* self, two::vec4* value) {
		self->m_attr0 = *value;
	}
	two::vec4* DECL two_MaterialUser__get_attr1(two::MaterialUser* self) {
		return &self->m_attr1;
	}
	void DECL two_MaterialUser__set_attr1(two::MaterialUser* self, two::vec4* value) {
		self->m_attr1 = *value;
	}
	two::vec4* DECL two_MaterialUser__get_attr2(two::MaterialUser* self) {
		return &self->m_attr2;
	}
	void DECL two_MaterialUser__set_attr2(two::MaterialUser* self, two::vec4* value) {
		self->m_attr2 = *value;
	}
	two::vec4* DECL two_MaterialUser__get_attr3(two::MaterialUser* self) {
		return &self->m_attr3;
	}
	void DECL two_MaterialUser__set_attr3(two::MaterialUser* self, two::vec4* value) {
		self->m_attr3 = *value;
	}
	two::vec4* DECL two_MaterialUser__get_attr4(two::MaterialUser* self) {
		return &self->m_attr4;
	}
	void DECL two_MaterialUser__set_attr4(two::MaterialUser* self, two::vec4* value) {
		self->m_attr4 = *value;
	}
	two::vec4* DECL two_MaterialUser__get_attr5(two::MaterialUser* self) {
		return &self->m_attr5;
	}
	void DECL two_MaterialUser__set_attr5(two::MaterialUser* self, two::vec4* value) {
		self->m_attr5 = *value;
	}
	void DECL two_MaterialUser__destroy(two::MaterialUser* self) {
		delete self;
	}
	// MaterialAlpha
	two::Type* DECL two_MaterialAlpha__type() {
		return &two::type<two::MaterialAlpha>();
	}
	two::MaterialAlpha* DECL two_MaterialAlpha__construct_0() {
		return new two::MaterialAlpha();
	}
	two::MaterialParam<float>* DECL two_MaterialAlpha__get_alpha(two::MaterialAlpha* self) {
		return &self->m_alpha;
	}
	void DECL two_MaterialAlpha__set_alpha(two::MaterialAlpha* self, two::MaterialParam<float>* value) {
		self->m_alpha = *value;
	}
	float DECL two_MaterialAlpha__get_alpha_scissor(two::MaterialAlpha* self) {
		return self->m_alpha_scissor;
	}
	void DECL two_MaterialAlpha__set_alpha_scissor(two::MaterialAlpha* self, float value) {
		self->m_alpha_scissor = value;
	}
	bool DECL two_MaterialAlpha__get_alpha_test(two::MaterialAlpha* self) {
		return self->m_alpha_test;
	}
	void DECL two_MaterialAlpha__set_alpha_test(two::MaterialAlpha* self, bool value) {
		self->m_alpha_test = value;
	}
	bool DECL two_MaterialAlpha__get_is_alpha(two::MaterialAlpha* self) {
		return self->m_is_alpha;
	}
	void DECL two_MaterialAlpha__set_is_alpha(two::MaterialAlpha* self, bool value) {
		self->m_is_alpha = value;
	}
	void DECL two_MaterialAlpha__destroy(two::MaterialAlpha* self) {
		delete self;
	}
	// MaterialSolid
	two::Type* DECL two_MaterialSolid__type() {
		return &two::type<two::MaterialSolid>();
	}
	two::MaterialSolid* DECL two_MaterialSolid__construct_0() {
		return new two::MaterialSolid();
	}
	two::MaterialParam<two::Colour>* DECL two_MaterialSolid__get_colour(two::MaterialSolid* self) {
		return &self->m_colour;
	}
	void DECL two_MaterialSolid__set_colour(two::MaterialSolid* self, two::MaterialParam<two::Colour>* value) {
		self->m_colour = *value;
	}
	void DECL two_MaterialSolid__destroy(two::MaterialSolid* self) {
		delete self;
	}
	// MaterialPoint
	two::Type* DECL two_MaterialPoint__type() {
		return &two::type<two::MaterialPoint>();
	}
	two::MaterialPoint* DECL two_MaterialPoint__construct_0() {
		return new two::MaterialPoint();
	}
	float DECL two_MaterialPoint__get_point_size(two::MaterialPoint* self) {
		return self->m_point_size;
	}
	void DECL two_MaterialPoint__set_point_size(two::MaterialPoint* self, float value) {
		self->m_point_size = value;
	}
	bool DECL two_MaterialPoint__get_project(two::MaterialPoint* self) {
		return self->m_project;
	}
	void DECL two_MaterialPoint__set_project(two::MaterialPoint* self, bool value) {
		self->m_project = value;
	}
	void DECL two_MaterialPoint__destroy(two::MaterialPoint* self) {
		delete self;
	}
	// MaterialLine
	two::Type* DECL two_MaterialLine__type() {
		return &two::type<two::MaterialLine>();
	}
	two::MaterialLine* DECL two_MaterialLine__construct_0() {
		return new two::MaterialLine();
	}
	float DECL two_MaterialLine__get_line_width(two::MaterialLine* self) {
		return self->m_line_width;
	}
	void DECL two_MaterialLine__set_line_width(two::MaterialLine* self, float value) {
		self->m_line_width = value;
	}
	bool DECL two_MaterialLine__get_dashed(two::MaterialLine* self) {
		return self->m_dashed;
	}
	void DECL two_MaterialLine__set_dashed(two::MaterialLine* self, bool value) {
		self->m_dashed = value;
	}
	float DECL two_MaterialLine__get_dash_scale(two::MaterialLine* self) {
		return self->m_dash_scale;
	}
	void DECL two_MaterialLine__set_dash_scale(two::MaterialLine* self, float value) {
		self->m_dash_scale = value;
	}
	float DECL two_MaterialLine__get_dash_size(two::MaterialLine* self) {
		return self->m_dash_size;
	}
	void DECL two_MaterialLine__set_dash_size(two::MaterialLine* self, float value) {
		self->m_dash_size = value;
	}
	float DECL two_MaterialLine__get_dash_gap(two::MaterialLine* self) {
		return self->m_dash_gap;
	}
	void DECL two_MaterialLine__set_dash_gap(two::MaterialLine* self, float value) {
		self->m_dash_gap = value;
	}
	void DECL two_MaterialLine__destroy(two::MaterialLine* self) {
		delete self;
	}
	// MaterialFresnel
	two::Type* DECL two_MaterialFresnel__type() {
		return &two::type<two::MaterialFresnel>();
	}
	two::MaterialFresnel* DECL two_MaterialFresnel__construct_0() {
		return new two::MaterialFresnel();
	}
	two::MaterialParam<two::Colour>* DECL two_MaterialFresnel__get_value(two::MaterialFresnel* self) {
		return &self->m_value;
	}
	void DECL two_MaterialFresnel__set_value(two::MaterialFresnel* self, two::MaterialParam<two::Colour>* value) {
		self->m_value = *value;
	}
	float DECL two_MaterialFresnel__get_fresnel_scale(two::MaterialFresnel* self) {
		return self->m_fresnel_scale;
	}
	void DECL two_MaterialFresnel__set_fresnel_scale(two::MaterialFresnel* self, float value) {
		self->m_fresnel_scale = value;
	}
	float DECL two_MaterialFresnel__get_fresnel_bias(two::MaterialFresnel* self) {
		return self->m_fresnel_bias;
	}
	void DECL two_MaterialFresnel__set_fresnel_bias(two::MaterialFresnel* self, float value) {
		self->m_fresnel_bias = value;
	}
	float DECL two_MaterialFresnel__get_fresnel_power(two::MaterialFresnel* self) {
		return self->m_fresnel_power;
	}
	void DECL two_MaterialFresnel__set_fresnel_power(two::MaterialFresnel* self, float value) {
		self->m_fresnel_power = value;
	}
	void DECL two_MaterialFresnel__destroy(two::MaterialFresnel* self) {
		delete self;
	}
	// MaterialLit
	two::Type* DECL two_MaterialLit__type() {
		return &two::type<two::MaterialLit>();
	}
	two::MaterialLit* DECL two_MaterialLit__construct_0() {
		return new two::MaterialLit();
	}
	two::MaterialParam<two::Colour>* DECL two_MaterialLit__get_emissive(two::MaterialLit* self) {
		return &self->m_emissive;
	}
	void DECL two_MaterialLit__set_emissive(two::MaterialLit* self, two::MaterialParam<two::Colour>* value) {
		self->m_emissive = *value;
	}
	float DECL two_MaterialLit__get_emissive_energy(two::MaterialLit* self) {
		return self->m_emissive_energy;
	}
	void DECL two_MaterialLit__set_emissive_energy(two::MaterialLit* self, float value) {
		self->m_emissive_energy = value;
	}
	two::MaterialParam<float>* DECL two_MaterialLit__get_normal(two::MaterialLit* self) {
		return &self->m_normal;
	}
	void DECL two_MaterialLit__set_normal(two::MaterialLit* self, two::MaterialParam<float>* value) {
		self->m_normal = *value;
	}
	two::MaterialParam<float>* DECL two_MaterialLit__get_bump(two::MaterialLit* self) {
		return &self->m_bump;
	}
	void DECL two_MaterialLit__set_bump(two::MaterialLit* self, two::MaterialParam<float>* value) {
		self->m_bump = *value;
	}
	two::MaterialParam<float>* DECL two_MaterialLit__get_displace(two::MaterialLit* self) {
		return &self->m_displace;
	}
	void DECL two_MaterialLit__set_displace(two::MaterialLit* self, two::MaterialParam<float>* value) {
		self->m_displace = *value;
	}
	float DECL two_MaterialLit__get_displace_bias(two::MaterialLit* self) {
		return self->m_displace_bias;
	}
	void DECL two_MaterialLit__set_displace_bias(two::MaterialLit* self, float value) {
		self->m_displace_bias = value;
	}
	two::MaterialParam<float>* DECL two_MaterialLit__get_occlusion(two::MaterialLit* self) {
		return &self->m_occlusion;
	}
	void DECL two_MaterialLit__set_occlusion(two::MaterialLit* self, two::MaterialParam<float>* value) {
		self->m_occlusion = *value;
	}
	two::MaterialParam<float>* DECL two_MaterialLit__get_lightmap(two::MaterialLit* self) {
		return &self->m_lightmap;
	}
	void DECL two_MaterialLit__set_lightmap(two::MaterialLit* self, two::MaterialParam<float>* value) {
		self->m_lightmap = *value;
	}
	bool DECL two_MaterialLit__get_no_envmap(two::MaterialLit* self) {
		return self->m_no_envmap;
	}
	void DECL two_MaterialLit__set_no_envmap(two::MaterialLit* self, bool value) {
		self->m_no_envmap = value;
	}
	void DECL two_MaterialLit__destroy(two::MaterialLit* self) {
		delete self;
	}
	// MaterialPbr
	two::Type* DECL two_MaterialPbr__type() {
		return &two::type<two::MaterialPbr>();
	}
	two::MaterialPbr* DECL two_MaterialPbr__construct_0() {
		return new two::MaterialPbr();
	}
	two::MaterialPbr* DECL two_MaterialPbr__construct_1(const two::Colour* albedo) {
		return new two::MaterialPbr(*albedo);
	}
	two::MaterialPbr* DECL two_MaterialPbr__construct_2(const two::Colour* albedo, float metallic) {
		return new two::MaterialPbr(*albedo, metallic);
	}
	two::MaterialPbr* DECL two_MaterialPbr__construct_3(const two::Colour* albedo, float metallic, float roughness) {
		return new two::MaterialPbr(*albedo, metallic, roughness);
	}
	two::MaterialParam<two::Colour>* DECL two_MaterialPbr__get_albedo(two::MaterialPbr* self) {
		return &self->m_albedo;
	}
	void DECL two_MaterialPbr__set_albedo(two::MaterialPbr* self, two::MaterialParam<two::Colour>* value) {
		self->m_albedo = *value;
	}
	float DECL two_MaterialPbr__get_specular(two::MaterialPbr* self) {
		return self->m_specular;
	}
	void DECL two_MaterialPbr__set_specular(two::MaterialPbr* self, float value) {
		self->m_specular = value;
	}
	two::MaterialParam<float>* DECL two_MaterialPbr__get_metallic(two::MaterialPbr* self) {
		return &self->m_metallic;
	}
	void DECL two_MaterialPbr__set_metallic(two::MaterialPbr* self, two::MaterialParam<float>* value) {
		self->m_metallic = *value;
	}
	two::MaterialParam<float>* DECL two_MaterialPbr__get_roughness(two::MaterialPbr* self) {
		return &self->m_roughness;
	}
	void DECL two_MaterialPbr__set_roughness(two::MaterialPbr* self, two::MaterialParam<float>* value) {
		self->m_roughness = *value;
	}
	two::MaterialParam<float>* DECL two_MaterialPbr__get_rim(two::MaterialPbr* self) {
		return &self->m_rim;
	}
	void DECL two_MaterialPbr__set_rim(two::MaterialPbr* self, two::MaterialParam<float>* value) {
		self->m_rim = *value;
	}
	float DECL two_MaterialPbr__get_ritint(two::MaterialPbr* self) {
		return self->m_rim_tint;
	}
	void DECL two_MaterialPbr__set_ritint(two::MaterialPbr* self, float value) {
		self->m_rim_tint = value;
	}
	two::MaterialParam<float>* DECL two_MaterialPbr__get_clearcoat(two::MaterialPbr* self) {
		return &self->m_clearcoat;
	}
	void DECL two_MaterialPbr__set_clearcoat(two::MaterialPbr* self, two::MaterialParam<float>* value) {
		self->m_clearcoat = *value;
	}
	float DECL two_MaterialPbr__get_clearcoat_gloss(two::MaterialPbr* self) {
		return self->m_clearcoat_gloss;
	}
	void DECL two_MaterialPbr__set_clearcoat_gloss(two::MaterialPbr* self, float value) {
		self->m_clearcoat_gloss = value;
	}
	two::MaterialParam<float>* DECL two_MaterialPbr__get_anisotropy(two::MaterialPbr* self) {
		return &self->m_anisotropy;
	}
	void DECL two_MaterialPbr__set_anisotropy(two::MaterialPbr* self, two::MaterialParam<float>* value) {
		self->m_anisotropy = *value;
	}
	two::MaterialParam<float>* DECL two_MaterialPbr__get_subsurface(two::MaterialPbr* self) {
		return &self->m_subsurface;
	}
	void DECL two_MaterialPbr__set_subsurface(two::MaterialPbr* self, two::MaterialParam<float>* value) {
		self->m_subsurface = *value;
	}
	two::MaterialParam<float>* DECL two_MaterialPbr__get_refraction(two::MaterialPbr* self) {
		return &self->m_refraction;
	}
	void DECL two_MaterialPbr__set_refraction(two::MaterialPbr* self, two::MaterialParam<float>* value) {
		self->m_refraction = *value;
	}
	two::MaterialParam<float>* DECL two_MaterialPbr__get_depth(two::MaterialPbr* self) {
		return &self->m_depth;
	}
	void DECL two_MaterialPbr__set_depth(two::MaterialPbr* self, two::MaterialParam<float>* value) {
		self->m_depth = *value;
	}
	two::MaterialParam<two::Colour>* DECL two_MaterialPbr__get_transmission(two::MaterialPbr* self) {
		return &self->m_transmission;
	}
	void DECL two_MaterialPbr__set_transmission(two::MaterialPbr* self, two::MaterialParam<two::Colour>* value) {
		self->m_transmission = *value;
	}
	bool DECL two_MaterialPbr__get_deep_parallax(two::MaterialPbr* self) {
		return self->m_deep_parallax;
	}
	void DECL two_MaterialPbr__set_deep_parallax(two::MaterialPbr* self, bool value) {
		self->m_deep_parallax = value;
	}
	two::PbrDiffuseMode DECL two_MaterialPbr__get_diffuse_mode(two::MaterialPbr* self) {
		return self->m_diffuse_mode;
	}
	void DECL two_MaterialPbr__set_diffuse_mode(two::MaterialPbr* self, two::PbrDiffuseMode value) {
		self->m_diffuse_mode = value;
	}
	two::PbrSpecularMode DECL two_MaterialPbr__get_specular_mode(two::MaterialPbr* self) {
		return self->m_specular_mode;
	}
	void DECL two_MaterialPbr__set_specular_mode(two::MaterialPbr* self, two::PbrSpecularMode value) {
		self->m_specular_mode = value;
	}
	void DECL two_MaterialPbr__destroy(two::MaterialPbr* self) {
		delete self;
	}
	// MaterialPhong
	two::Type* DECL two_MaterialPhong__type() {
		return &two::type<two::MaterialPhong>();
	}
	two::MaterialPhong* DECL two_MaterialPhong__construct_0() {
		return new two::MaterialPhong();
	}
	two::MaterialParam<two::Colour>* DECL two_MaterialPhong__get_diffuse(two::MaterialPhong* self) {
		return &self->m_diffuse;
	}
	void DECL two_MaterialPhong__set_diffuse(two::MaterialPhong* self, two::MaterialParam<two::Colour>* value) {
		self->m_diffuse = *value;
	}
	two::MaterialParam<two::Colour>* DECL two_MaterialPhong__get_specular(two::MaterialPhong* self) {
		return &self->m_specular;
	}
	void DECL two_MaterialPhong__set_specular(two::MaterialPhong* self, two::MaterialParam<two::Colour>* value) {
		self->m_specular = *value;
	}
	two::MaterialParam<float>* DECL two_MaterialPhong__get_shininess(two::MaterialPhong* self) {
		return &self->m_shininess;
	}
	void DECL two_MaterialPhong__set_shininess(two::MaterialPhong* self, two::MaterialParam<float>* value) {
		self->m_shininess = *value;
	}
	two::MaterialParam<float>* DECL two_MaterialPhong__get_reflectivity(two::MaterialPhong* self) {
		return &self->m_reflectivity;
	}
	void DECL two_MaterialPhong__set_reflectivity(two::MaterialPhong* self, two::MaterialParam<float>* value) {
		self->m_reflectivity = *value;
	}
	two::MaterialParam<float>* DECL two_MaterialPhong__get_refraction(two::MaterialPhong* self) {
		return &self->m_refraction;
	}
	void DECL two_MaterialPhong__set_refraction(two::MaterialPhong* self, two::MaterialParam<float>* value) {
		self->m_refraction = *value;
	}
	two::PhongEnvBlendMode DECL two_MaterialPhong__get_env_blend(two::MaterialPhong* self) {
		return self->m_env_blend;
	}
	void DECL two_MaterialPhong__set_env_blend(two::MaterialPhong* self, two::PhongEnvBlendMode value) {
		self->m_env_blend = value;
	}
	bool DECL two_MaterialPhong__get_toon(two::MaterialPhong* self) {
		return self->m_toon;
	}
	void DECL two_MaterialPhong__set_toon(two::MaterialPhong* self, bool value) {
		self->m_toon = value;
	}
	void DECL two_MaterialPhong__destroy(two::MaterialPhong* self) {
		delete self;
	}
	// BlockMaterial
	two::Type* DECL two_BlockMaterial__type() {
		return &two::type<two::BlockMaterial>();
	}
	void DECL two_BlockMaterial__destroy(two::BlockMaterial* self) {
		delete self;
	}
	// Material
	two::Type* DECL two_Material__type() {
		return &two::type<two::Material>();
	}
	uint16_t DECL two_Material__get_index(two::Material* self) {
		return self->m_index;
	}
	void DECL two_Material__set_index(two::Material* self, uint16_t value) {
		self->m_index = value;
	}
	const char* DECL two_Material__get_name(two::Material* self) {
		return self->m_name.c_str();
	}
	void DECL two_Material__set_name(two::Material* self, const char* value) {
		self->m_name = value;
	}
	bool DECL two_Material__get_builtin(two::Material* self) {
		return self->m_builtin;
	}
	void DECL two_Material__set_builtin(two::Material* self, bool value) {
		self->m_builtin = value;
	}
	two::Program* DECL two_Material__get_program(two::Material* self) {
		return self->m_program;
	}
	void DECL two_Material__set_program(two::Material* self, two::Program* value) {
		self->m_program = value;
	}
	two::MaterialBase* DECL two_Material__get_base(two::Material* self) {
		return &self->m_base;
	}
	void DECL two_Material__set_base(two::Material* self, two::MaterialBase* value) {
		self->m_base = *value;
	}
	two::MaterialAlpha* DECL two_Material__get_alpha(two::Material* self) {
		return &self->m_alpha;
	}
	void DECL two_Material__set_alpha(two::Material* self, two::MaterialAlpha* value) {
		self->m_alpha = *value;
	}
	two::MaterialSolid* DECL two_Material__get_solid(two::Material* self) {
		return &self->m_solid;
	}
	void DECL two_Material__set_solid(two::Material* self, two::MaterialSolid* value) {
		self->m_solid = *value;
	}
	two::MaterialPoint* DECL two_Material__get_point(two::Material* self) {
		return &self->m_point;
	}
	void DECL two_Material__set_point(two::Material* self, two::MaterialPoint* value) {
		self->m_point = *value;
	}
	two::MaterialLine* DECL two_Material__get_line(two::Material* self) {
		return &self->m_line;
	}
	void DECL two_Material__set_line(two::Material* self, two::MaterialLine* value) {
		self->m_line = *value;
	}
	two::MaterialLit* DECL two_Material__get_lit(two::Material* self) {
		return &self->m_lit;
	}
	void DECL two_Material__set_lit(two::Material* self, two::MaterialLit* value) {
		self->m_lit = *value;
	}
	two::MaterialPbr* DECL two_Material__get_pbr(two::Material* self) {
		return &self->m_pbr;
	}
	void DECL two_Material__set_pbr(two::Material* self, two::MaterialPbr* value) {
		self->m_pbr = *value;
	}
	two::MaterialPhong* DECL two_Material__get_phong(two::Material* self) {
		return &self->m_phong;
	}
	void DECL two_Material__set_phong(two::Material* self, two::MaterialPhong* value) {
		self->m_phong = *value;
	}
	two::MaterialFresnel* DECL two_Material__get_fresnel(two::Material* self) {
		return &self->m_fresnel;
	}
	void DECL two_Material__set_fresnel(two::Material* self, two::MaterialFresnel* value) {
		self->m_fresnel = *value;
	}
	two::MaterialUser* DECL two_Material__get_user(two::Material* self) {
		return &self->m_user;
	}
	void DECL two_Material__set_user(two::Material* self, two::MaterialUser* value) {
		self->m_user = *value;
	}
	void DECL two_Material__destroy(two::Material* self) {
		delete self;
	}
	// ModelElem
	two::Type* DECL two_ModelElem__type() {
		return &two::type<two::ModelElem>();
	}
	two::ModelElem* DECL two_ModelElem__construct_0() {
		return new two::ModelElem();
	}
	size_t DECL two_ModelElem__get_index(two::ModelElem* self) {
		return self->m_index;
	}
	void DECL two_ModelElem__set_index(two::ModelElem* self, size_t value) {
		self->m_index = value;
	}
	two::Mesh* DECL two_ModelElem__get_mesh(two::ModelElem* self) {
		return self->m_mesh;
	}
	void DECL two_ModelElem__set_mesh(two::ModelElem* self, two::Mesh* value) {
		self->m_mesh = value;
	}
	bool DECL two_ModelElem__get_has_transform(two::ModelElem* self) {
		return self->m_has_transform;
	}
	void DECL two_ModelElem__set_has_transform(two::ModelElem* self, bool value) {
		self->m_has_transform = value;
	}
	two::mat4* DECL two_ModelElem__get_transform(two::ModelElem* self) {
		return &self->m_transform;
	}
	void DECL two_ModelElem__set_transform(two::ModelElem* self, two::mat4* value) {
		self->m_transform = *value;
	}
	int DECL two_ModelElem__get_skin(two::ModelElem* self) {
		return self->m_skin;
	}
	void DECL two_ModelElem__set_skin(two::ModelElem* self, int value) {
		self->m_skin = value;
	}
	two::Colour* DECL two_ModelElem__get_colour(two::ModelElem* self) {
		return &self->m_colour;
	}
	void DECL two_ModelElem__set_colour(two::ModelElem* self, two::Colour* value) {
		self->m_colour = *value;
	}
	two::Material* DECL two_ModelElem__get_material(two::ModelElem* self) {
		return self->m_material;
	}
	void DECL two_ModelElem__set_material(two::ModelElem* self, two::Material* value) {
		self->m_material = value;
	}
	void DECL two_ModelElem__destroy(two::ModelElem* self) {
		delete self;
	}
	// Model
	two::Type* DECL two_Model__type() {
		return &two::type<two::Model>();
	}
	two::Mesh* DECL two_Model_get_mesh_1(two::Model* self, size_t index) {
		return &self->get_mesh(index);
	}
	two::Mesh* DECL two_Model_add_mesh_1(two::Model* self, const char* name) {
		return &self->add_mesh(name);
	}
	two::Mesh* DECL two_Model_add_mesh_2(two::Model* self, const char* name, bool readback) {
		return &self->add_mesh(name, readback);
	}
	two::Rig* DECL two_Model_add_rig_1(two::Model* self, const char* name) {
		return &self->add_rig(name);
	}
	two::ModelElem* DECL two_Model_add_item_2(two::Model* self, two::Mesh* mesh, const two::mat4* transform) {
		return &self->add_item(*mesh, *transform);
	}
	two::ModelElem* DECL two_Model_add_item_3(two::Model* self, two::Mesh* mesh, const two::mat4* transform, int skin) {
		return &self->add_item(*mesh, *transform, skin);
	}
	two::ModelElem* DECL two_Model_add_item_4(two::Model* self, two::Mesh* mesh, const two::mat4* transform, int skin, const two::Colour* colour) {
		return &self->add_item(*mesh, *transform, skin, *colour);
	}
	two::ModelElem* DECL two_Model_add_item_5(two::Model* self, two::Mesh* mesh, const two::mat4* transform, int skin, const two::Colour* colour, two::Material* material) {
		return &self->add_item(*mesh, *transform, skin, *colour, material);
	}
	void DECL two_Model_prepare_0(two::Model* self) {
		self->prepare();
	}
	const char* DECL two_Model__get_name(two::Model* self) {
		return self->m_name.c_str();
	}
	void DECL two_Model__set_name(two::Model* self, const char* value) {
		self->m_name = value;
	}
	uint16_t DECL two_Model__get_index(two::Model* self) {
		return self->m_index;
	}
	void DECL two_Model__set_index(two::Model* self, uint16_t value) {
		self->m_index = value;
	}
	two::Aabb* DECL two_Model__get_aabb(two::Model* self) {
		return &self->m_aabb;
	}
	void DECL two_Model__set_aabb(two::Model* self, two::Aabb* value) {
		self->m_aabb = *value;
	}
	float DECL two_Model__get_radius(two::Model* self) {
		return self->m_radius;
	}
	void DECL two_Model__set_radius(two::Model* self, float value) {
		self->m_radius = value;
	}
	two::vec3* DECL two_Model__get_origin(two::Model* self) {
		return &self->m_origin;
	}
	void DECL two_Model__set_origin(two::Model* self, two::vec3* value) {
		self->m_origin = *value;
	}
	void DECL two_Model__destroy(two::Model* self) {
		delete self;
	}
	// Flow
	two::Type* DECL two_Flow__type() {
		return &two::type<two::Flow>();
	}
	two::Flow* DECL two_Flow__construct_0() {
		return new two::Flow();
	}
	const char* DECL two_Flow__get_name(two::Flow* self) {
		return self->m_name.c_str();
	}
	void DECL two_Flow__set_name(two::Flow* self, const char* value) {
		self->m_name = value;
	}
	float DECL two_Flow__get_duration(two::Flow* self) {
		return self->m_duration;
	}
	void DECL two_Flow__set_duration(two::Flow* self, float value) {
		self->m_duration = value;
	}
	float DECL two_Flow__get_start_time(two::Flow* self) {
		return self->m_start_time;
	}
	void DECL two_Flow__set_start_time(two::Flow* self, float value) {
		self->m_start_time = value;
	}
	bool DECL two_Flow__get_loop(two::Flow* self) {
		return self->m_loop;
	}
	void DECL two_Flow__set_loop(two::Flow* self, bool value) {
		self->m_loop = value;
	}
	two::ShapeVar* DECL two_Flow__get_shape(two::Flow* self) {
		return &self->m_shape;
	}
	two::EmitterFlow DECL two_Flow__get_flow(two::Flow* self) {
		return self->m_flow;
	}
	void DECL two_Flow__set_flow(two::Flow* self, two::EmitterFlow value) {
		self->m_flow = value;
	}
	bool DECL two_Flow__get_billboard(two::Flow* self) {
		return self->m_billboard;
	}
	void DECL two_Flow__set_billboard(two::Flow* self, bool value) {
		self->m_billboard = value;
	}
	two::vec3* DECL two_Flow__get_direction(two::Flow* self) {
		return &self->m_direction;
	}
	void DECL two_Flow__set_direction(two::Flow* self, two::vec3* value) {
		self->m_direction = *value;
	}
	two::quat* DECL two_Flow__get_rotation(two::Flow* self) {
		return &self->m_rotation;
	}
	void DECL two_Flow__set_rotation(two::Flow* self, two::quat* value) {
		self->m_rotation = *value;
	}
	two::BlendMode DECL two_Flow__get_blend_mode(two::Flow* self) {
		return self->m_blend_mode;
	}
	void DECL two_Flow__set_blend_mode(two::Flow* self, two::BlendMode value) {
		self->m_blend_mode = value;
	}
	two::ValueTrack<float>* DECL two_Flow__get_volume(two::Flow* self) {
		return &self->m_volume;
	}
	void DECL two_Flow__set_volume(two::Flow* self, two::ValueTrack<float>* value) {
		self->m_volume = *value;
	}
	two::ValueTrack<uint32_t>* DECL two_Flow__get_rate(two::Flow* self) {
		return &self->m_rate;
	}
	void DECL two_Flow__set_rate(two::Flow* self, two::ValueTrack<uint32_t>* value) {
		self->m_rate = *value;
	}
	two::ValueTrack<float>* DECL two_Flow__get_lifetime(two::Flow* self) {
		return &self->m_lifetime;
	}
	void DECL two_Flow__set_lifetime(two::Flow* self, two::ValueTrack<float>* value) {
		self->m_lifetime = *value;
	}
	two::ValueTrack<float>* DECL two_Flow__get_gravity(two::Flow* self) {
		return &self->m_gravity;
	}
	void DECL two_Flow__set_gravity(two::Flow* self, two::ValueTrack<float>* value) {
		self->m_gravity = *value;
	}
	two::ValueTrack<float>* DECL two_Flow__get_speed(two::Flow* self) {
		return &self->m_speed;
	}
	void DECL two_Flow__set_speed(two::Flow* self, two::ValueTrack<float>* value) {
		self->m_speed = *value;
	}
	two::ValueTrack<float>* DECL two_Flow__get_angle(two::Flow* self) {
		return &self->m_angle;
	}
	void DECL two_Flow__set_angle(two::Flow* self, two::ValueTrack<float>* value) {
		self->m_angle = *value;
	}
	two::ValueTrack<float>* DECL two_Flow__get_blend(two::Flow* self) {
		return &self->m_blend;
	}
	void DECL two_Flow__set_blend(two::Flow* self, two::ValueTrack<float>* value) {
		self->m_blend = *value;
	}
	two::ValueTrack<two::Colour>* DECL two_Flow__get_colour(two::Flow* self) {
		return &self->m_colour;
	}
	void DECL two_Flow__set_colour(two::Flow* self, two::ValueTrack<two::Colour>* value) {
		self->m_colour = *value;
	}
	two::ValueTrack<float>* DECL two_Flow__get_scale(two::Flow* self) {
		return &self->m_scale;
	}
	void DECL two_Flow__set_scale(two::Flow* self, two::ValueTrack<float>* value) {
		self->m_scale = *value;
	}
	two::ValueTrack<float>* DECL two_Flow__get_sprite_frame(two::Flow* self) {
		return &self->m_sprite_frame;
	}
	void DECL two_Flow__set_sprite_frame(two::Flow* self, two::ValueTrack<float>* value) {
		self->m_sprite_frame = *value;
	}
	const char* DECL two_Flow__get_sprite_name(two::Flow* self) {
		return self->m_sprite_name.c_str();
	}
	void DECL two_Flow__set_sprite_name(two::Flow* self, const char* value) {
		self->m_sprite_name = value;
	}
	void DECL two_Flow__destroy(two::Flow* self) {
		delete self;
	}
	// Flare
	two::Type* DECL two_Flare__type() {
		return &two::type<two::Flare>();
	}
	two::Flare* DECL two_Flare__construct_0() {
		return new two::Flare();
	}
	two::Node3* DECL two_Flare__get_node(two::Flare* self) {
		return self->m_node;
	}
	void DECL two_Flare__set_node(two::Flare* self, two::Node3* value) {
		self->m_node = value;
	}
	void DECL two_Flare__destroy(two::Flare* self) {
		delete self;
	}
	// BlockParticles
	two::Type* DECL two_BlockParticles__type() {
		return &two::type<two::BlockParticles>();
	}
	void DECL two_BlockParticles__destroy(two::BlockParticles* self) {
		delete self;
	}
	// Batch
	two::Type* DECL two_Batch__type() {
		return &two::type<two::Batch>();
	}
	two::Batch* DECL two_Batch__construct_0() {
		return new two::Batch();
	}
	two::Batch* DECL two_Batch__construct_2(two::Item* item, uint16_t stride) {
		return new two::Batch(*item, stride);
	}
	void DECL two_Batch_update_aabb_1(two::Batch* self, float* instances, int instances_size) {
		self->update_aabb({ (two::mat4*)instances, instances_size / (sizeof(two::mat4) / sizeof(float)) });
	}
	void DECL two_Batch_transforms_1(two::Batch* self, float* instances, int instances_size) {
		self->transforms({ (two::mat4*)instances, instances_size / (sizeof(two::mat4) / sizeof(float)) });
	}
	float* DECL two_Batch_begin_1(two::Batch* self, uint32_t count) {
		return (float*)self->begin(count).data();
	}
	void DECL two_Batch_commit_1(two::Batch* self, float* data, int data_size) {
		self->commit({ (float*)data, data_size / (sizeof(float) / sizeof(float)) });
	}
	void DECL two_Batch_cache_1(two::Batch* self, float* data, int data_size) {
		self->cache({ (float*)data, data_size / (sizeof(float) / sizeof(float)) });
	}
	void DECL two_Batch_transform_1(two::Batch* self, const two::mat4* m) {
		self->transform(*m);
	}
	two::Item* DECL two_Batch__get_item(two::Batch* self) {
		return self->m_item;
	}
	void DECL two_Batch__set_item(two::Batch* self, two::Item* value) {
		self->m_item = value;
	}
	uint16_t DECL two_Batch__get_stride(two::Batch* self) {
		return self->m_stride;
	}
	void DECL two_Batch__set_stride(two::Batch* self, uint16_t value) {
		self->m_stride = value;
	}
	void DECL two_Batch__destroy(two::Batch* self) {
		delete self;
	}
	// Item
	two::Type* DECL two_Item__type() {
		return &two::type<two::Item>();
	}
	two::Item* DECL two_Item__construct_0() {
		return new two::Item();
	}
	two::Item* DECL two_Item__construct_2(two::Node3* node, const two::Model* model) {
		return new two::Item(*node, *model);
	}
	two::Item* DECL two_Item__construct_3(two::Node3* node, const two::Model* model, uint32_t flags) {
		return new two::Item(*node, *model, flags);
	}
	two::Item* DECL two_Item__construct_4(two::Node3* node, const two::Model* model, uint32_t flags, two::Material* material) {
		return new two::Item(*node, *model, flags, material);
	}
	void DECL two_Item_update_aabb_0(two::Item* self) {
		self->update_aabb();
	}
	two::Node3* DECL two_Item__get_node(two::Item* self) {
		return self->m_node;
	}
	void DECL two_Item__set_node(two::Item* self, two::Node3* value) {
		self->m_node = value;
	}
	two::Model* DECL two_Item__get_model(two::Item* self) {
		return self->m_model;
	}
	void DECL two_Item__set_model(two::Item* self, two::Model* value) {
		self->m_model = value;
	}
	uint32_t DECL two_Item__get_flags(two::Item* self) {
		return self->m_flags;
	}
	void DECL two_Item__set_flags(two::Item* self, uint32_t value) {
		self->m_flags = value;
	}
	two::Colour* DECL two_Item__get_colour(two::Item* self) {
		return &self->m_colour;
	}
	void DECL two_Item__set_colour(two::Item* self, two::Colour* value) {
		self->m_colour = *value;
	}
	two::Material* DECL two_Item__get_material(two::Item* self) {
		return self->m_material;
	}
	void DECL two_Item__set_material(two::Item* self, two::Material* value) {
		self->m_material = value;
	}
	bool DECL two_Item__get_visible(two::Item* self) {
		return self->m_visible;
	}
	void DECL two_Item__set_visible(two::Item* self, bool value) {
		self->m_visible = value;
	}
	two::ItemShadow DECL two_Item__get_shadow(two::Item* self) {
		return self->m_shadow;
	}
	void DECL two_Item__set_shadow(two::Item* self, two::ItemShadow value) {
		self->m_shadow = value;
	}
	two::Rig* DECL two_Item__get_rig(two::Item* self) {
		return self->m_rig;
	}
	void DECL two_Item__set_rig(two::Item* self, two::Rig* value) {
		self->m_rig = value;
	}
	two::Aabb* DECL two_Item__get_aabb(two::Item* self) {
		return &self->m_aabb;
	}
	void DECL two_Item__set_aabb(two::Item* self, two::Aabb* value) {
		self->m_aabb = *value;
	}
	two::Batch* DECL two_Item__get_batch(two::Item* self) {
		return self->m_batch;
	}
	void DECL two_Item__set_batch(two::Item* self, two::Batch* value) {
		self->m_batch = value;
	}
	void DECL two_Item__destroy(two::Item* self) {
		delete self;
	}
	// ImportConfig
	two::Type* DECL two_ImportConfig__type() {
		return &two::type<two::ImportConfig>();
	}
	two::ImportConfig* DECL two_ImportConfig__construct_0() {
		return new two::ImportConfig();
	}
	two::ModelFormat DECL two_ImportConfig__get_format(two::ImportConfig* self) {
		return self->m_format;
	}
	void DECL two_ImportConfig__set_format(two::ImportConfig* self, two::ModelFormat value) {
		self->m_format = value;
	}
	two::vec3* DECL two_ImportConfig__get_position(two::ImportConfig* self) {
		return &self->m_position;
	}
	void DECL two_ImportConfig__set_position(two::ImportConfig* self, two::vec3* value) {
		self->m_position = *value;
	}
	two::quat* DECL two_ImportConfig__get_rotation(two::ImportConfig* self) {
		return &self->m_rotation;
	}
	void DECL two_ImportConfig__set_rotation(two::ImportConfig* self, two::quat* value) {
		self->m_rotation = *value;
	}
	two::vec3* DECL two_ImportConfig__get_scale(two::ImportConfig* self) {
		return &self->m_scale;
	}
	void DECL two_ImportConfig__set_scale(two::ImportConfig* self, two::vec3* value) {
		self->m_scale = *value;
	}
	two::mat4* DECL two_ImportConfig__get_transform(two::ImportConfig* self) {
		return &self->m_transform;
	}
	void DECL two_ImportConfig__set_transform(two::ImportConfig* self, two::mat4* value) {
		self->m_transform = *value;
	}
	const char* DECL two_ImportConfig__get_suffix(two::ImportConfig* self) {
		return self->m_suffix.c_str();
	}
	void DECL two_ImportConfig__set_suffix(two::ImportConfig* self, const char* value) {
		self->m_suffix = value;
	}
	bool DECL two_ImportConfig__get_force_reimport(two::ImportConfig* self) {
		return self->m_force_reimport;
	}
	void DECL two_ImportConfig__set_force_reimport(two::ImportConfig* self, bool value) {
		self->m_force_reimport = value;
	}
	bool DECL two_ImportConfig__get_cache_geometry(two::ImportConfig* self) {
		return self->m_cache_geometry;
	}
	void DECL two_ImportConfig__set_cache_geometry(two::ImportConfig* self, bool value) {
		self->m_cache_geometry = value;
	}
	bool DECL two_ImportConfig__get_optimize_geometry(two::ImportConfig* self) {
		return self->m_optimize_geometry;
	}
	void DECL two_ImportConfig__set_optimize_geometry(two::ImportConfig* self, bool value) {
		self->m_optimize_geometry = value;
	}
	bool DECL two_ImportConfig__get_need_normals(two::ImportConfig* self) {
		return self->m_need_normals;
	}
	void DECL two_ImportConfig__set_need_normals(two::ImportConfig* self, bool value) {
		self->m_need_normals = value;
	}
	bool DECL two_ImportConfig__get_need_uvs(two::ImportConfig* self) {
		return self->m_need_uvs;
	}
	void DECL two_ImportConfig__set_need_uvs(two::ImportConfig* self, bool value) {
		self->m_need_uvs = value;
	}
	bool DECL two_ImportConfig__get_no_transforms(two::ImportConfig* self) {
		return self->m_no_transforms;
	}
	void DECL two_ImportConfig__set_no_transforms(two::ImportConfig* self, bool value) {
		self->m_no_transforms = value;
	}
	uint32_t DECL two_ImportConfig__get_flags(two::ImportConfig* self) {
		return self->m_flags;
	}
	void DECL two_ImportConfig__set_flags(two::ImportConfig* self, uint32_t value) {
		self->m_flags = value;
	}
	void DECL two_ImportConfig__destroy(two::ImportConfig* self) {
		delete self;
	}
	// Import
	two::Type* DECL two_Import__type() {
		return &two::type<two::Import>();
	}
	const char* DECL two_Import__get_name(two::Import* self) {
		return self->m_name.c_str();
	}
	void DECL two_Import__set_name(two::Import* self, const char* value) {
		self->m_name = value;
	}
	const char* DECL two_Import__get_file(two::Import* self) {
		return self->m_file.c_str();
	}
	void DECL two_Import__set_file(two::Import* self, const char* value) {
		self->m_file = value;
	}
	const char* DECL two_Import__get_path(two::Import* self) {
		return self->m_path.c_str();
	}
	void DECL two_Import__set_path(two::Import* self, const char* value) {
		self->m_path = value;
	}
	two::ImportConfig* DECL two_Import__get_config(two::Import* self) {
		return &self->m_config;
	}
	void DECL two_Import__set_config(two::Import* self, two::ImportConfig* value) {
		self->m_config = *value;
	}
	void DECL two_Import__destroy(two::Import* self) {
		delete self;
	}
	// Prefab
	two::Type* DECL two_Prefab__type() {
		return &two::type<two::Prefab>();
	}
	void DECL two_Prefab_add_1(two::Prefab* self, two::Scene* scene) {
		self->add(*scene);
	}
	void DECL two_Prefab_add_2(two::Prefab* self, two::Scene* scene, two::Mime* mime) {
		self->add(*scene, mime);
	}
	const char* DECL two_Prefab__get_name(two::Prefab* self) {
		return self->m_name.c_str();
	}
	void DECL two_Prefab__set_name(two::Prefab* self, const char* value) {
		self->m_name = value;
	}
	void DECL two_Prefab__destroy(two::Prefab* self) {
		delete self;
	}
	// AssetStore<two::Texture>
	two::Type* DECL two_AssetStore_two_Texture__type() {
		return &two::type<two::AssetStore<two::Texture>>();
	}
	two::Texture* DECL two_AssetStore_two_Texture_get_1(two::AssetStore<two::Texture>* self, const char* name) {
		return self->get(name);
	}
	two::Texture* DECL two_AssetStore_two_Texture_create_1(two::AssetStore<two::Texture>* self, const char* name) {
		return &self->create(name);
	}
	two::Texture* DECL two_AssetStore_two_Texture_fetch_1(two::AssetStore<two::Texture>* self, const char* name) {
		return &self->fetch(name);
	}
	two::Texture* DECL two_AssetStore_two_Texture_file_1(two::AssetStore<two::Texture>* self, const char* name) {
		return self->file(name);
	}
	two::Texture* DECL two_AssetStore_two_Texture_file_at_2(two::AssetStore<two::Texture>* self, const char* path, const char* name) {
		return &self->file_at(path, name);
	}
	two::Texture* DECL two_AssetStore_two_Texture_load_2(two::AssetStore<two::Texture>* self, const char* path, const char* name) {
		return self->load(path, name);
	}
	void DECL two_AssetStore_two_Texture_destroy_1(two::AssetStore<two::Texture>* self, const char* name) {
		self->destroy(name);
	}
	void DECL two_AssetStore_two_Texture_clear_0(two::AssetStore<two::Texture>* self) {
		self->clear();
	}
	void DECL two_AssetStore_two_Texture__destroy(two::AssetStore<two::Texture>* self) {
		delete self;
	}
	// AssetStore<two::Program>
	two::Type* DECL two_AssetStore_two_Program__type() {
		return &two::type<two::AssetStore<two::Program>>();
	}
	two::Program* DECL two_AssetStore_two_Program_get_1(two::AssetStore<two::Program>* self, const char* name) {
		return self->get(name);
	}
	two::Program* DECL two_AssetStore_two_Program_create_1(two::AssetStore<two::Program>* self, const char* name) {
		return &self->create(name);
	}
	two::Program* DECL two_AssetStore_two_Program_fetch_1(two::AssetStore<two::Program>* self, const char* name) {
		return &self->fetch(name);
	}
	two::Program* DECL two_AssetStore_two_Program_file_1(two::AssetStore<two::Program>* self, const char* name) {
		return self->file(name);
	}
	two::Program* DECL two_AssetStore_two_Program_file_at_2(two::AssetStore<two::Program>* self, const char* path, const char* name) {
		return &self->file_at(path, name);
	}
	two::Program* DECL two_AssetStore_two_Program_load_2(two::AssetStore<two::Program>* self, const char* path, const char* name) {
		return self->load(path, name);
	}
	void DECL two_AssetStore_two_Program_destroy_1(two::AssetStore<two::Program>* self, const char* name) {
		self->destroy(name);
	}
	void DECL two_AssetStore_two_Program_clear_0(two::AssetStore<two::Program>* self) {
		self->clear();
	}
	void DECL two_AssetStore_two_Program__destroy(two::AssetStore<two::Program>* self) {
		delete self;
	}
	// AssetStore<two::Material>
	two::Type* DECL two_AssetStore_two_Material__type() {
		return &two::type<two::AssetStore<two::Material>>();
	}
	two::Material* DECL two_AssetStore_two_Material_get_1(two::AssetStore<two::Material>* self, const char* name) {
		return self->get(name);
	}
	two::Material* DECL two_AssetStore_two_Material_create_1(two::AssetStore<two::Material>* self, const char* name) {
		return &self->create(name);
	}
	two::Material* DECL two_AssetStore_two_Material_fetch_1(two::AssetStore<two::Material>* self, const char* name) {
		return &self->fetch(name);
	}
	two::Material* DECL two_AssetStore_two_Material_file_1(two::AssetStore<two::Material>* self, const char* name) {
		return self->file(name);
	}
	two::Material* DECL two_AssetStore_two_Material_file_at_2(two::AssetStore<two::Material>* self, const char* path, const char* name) {
		return &self->file_at(path, name);
	}
	two::Material* DECL two_AssetStore_two_Material_load_2(two::AssetStore<two::Material>* self, const char* path, const char* name) {
		return self->load(path, name);
	}
	void DECL two_AssetStore_two_Material_destroy_1(two::AssetStore<two::Material>* self, const char* name) {
		self->destroy(name);
	}
	void DECL two_AssetStore_two_Material_clear_0(two::AssetStore<two::Material>* self) {
		self->clear();
	}
	void DECL two_AssetStore_two_Material__destroy(two::AssetStore<two::Material>* self) {
		delete self;
	}
	// AssetStore<two::Model>
	two::Type* DECL two_AssetStore_two_Model__type() {
		return &two::type<two::AssetStore<two::Model>>();
	}
	two::Model* DECL two_AssetStore_two_Model_get_1(two::AssetStore<two::Model>* self, const char* name) {
		return self->get(name);
	}
	two::Model* DECL two_AssetStore_two_Model_create_1(two::AssetStore<two::Model>* self, const char* name) {
		return &self->create(name);
	}
	two::Model* DECL two_AssetStore_two_Model_fetch_1(two::AssetStore<two::Model>* self, const char* name) {
		return &self->fetch(name);
	}
	two::Model* DECL two_AssetStore_two_Model_file_1(two::AssetStore<two::Model>* self, const char* name) {
		return self->file(name);
	}
	two::Model* DECL two_AssetStore_two_Model_file_at_2(two::AssetStore<two::Model>* self, const char* path, const char* name) {
		return &self->file_at(path, name);
	}
	two::Model* DECL two_AssetStore_two_Model_load_2(two::AssetStore<two::Model>* self, const char* path, const char* name) {
		return self->load(path, name);
	}
	void DECL two_AssetStore_two_Model_destroy_1(two::AssetStore<two::Model>* self, const char* name) {
		self->destroy(name);
	}
	void DECL two_AssetStore_two_Model_clear_0(two::AssetStore<two::Model>* self) {
		self->clear();
	}
	void DECL two_AssetStore_two_Model__destroy(two::AssetStore<two::Model>* self) {
		delete self;
	}
	// AssetStore<two::Flow>
	two::Type* DECL two_AssetStore_two_Flow__type() {
		return &two::type<two::AssetStore<two::Flow>>();
	}
	two::Flow* DECL two_AssetStore_two_Flow_get_1(two::AssetStore<two::Flow>* self, const char* name) {
		return self->get(name);
	}
	two::Flow* DECL two_AssetStore_two_Flow_create_1(two::AssetStore<two::Flow>* self, const char* name) {
		return &self->create(name);
	}
	two::Flow* DECL two_AssetStore_two_Flow_fetch_1(two::AssetStore<two::Flow>* self, const char* name) {
		return &self->fetch(name);
	}
	two::Flow* DECL two_AssetStore_two_Flow_file_1(two::AssetStore<two::Flow>* self, const char* name) {
		return self->file(name);
	}
	two::Flow* DECL two_AssetStore_two_Flow_file_at_2(two::AssetStore<two::Flow>* self, const char* path, const char* name) {
		return &self->file_at(path, name);
	}
	two::Flow* DECL two_AssetStore_two_Flow_load_2(two::AssetStore<two::Flow>* self, const char* path, const char* name) {
		return self->load(path, name);
	}
	void DECL two_AssetStore_two_Flow_destroy_1(two::AssetStore<two::Flow>* self, const char* name) {
		self->destroy(name);
	}
	void DECL two_AssetStore_two_Flow_clear_0(two::AssetStore<two::Flow>* self) {
		self->clear();
	}
	void DECL two_AssetStore_two_Flow__destroy(two::AssetStore<two::Flow>* self) {
		delete self;
	}
	// AssetStore<two::Prefab>
	two::Type* DECL two_AssetStore_two_Prefab__type() {
		return &two::type<two::AssetStore<two::Prefab>>();
	}
	two::Prefab* DECL two_AssetStore_two_Prefab_get_1(two::AssetStore<two::Prefab>* self, const char* name) {
		return self->get(name);
	}
	two::Prefab* DECL two_AssetStore_two_Prefab_create_1(two::AssetStore<two::Prefab>* self, const char* name) {
		return &self->create(name);
	}
	two::Prefab* DECL two_AssetStore_two_Prefab_fetch_1(two::AssetStore<two::Prefab>* self, const char* name) {
		return &self->fetch(name);
	}
	two::Prefab* DECL two_AssetStore_two_Prefab_file_1(two::AssetStore<two::Prefab>* self, const char* name) {
		return self->file(name);
	}
	two::Prefab* DECL two_AssetStore_two_Prefab_file_at_2(two::AssetStore<two::Prefab>* self, const char* path, const char* name) {
		return &self->file_at(path, name);
	}
	two::Prefab* DECL two_AssetStore_two_Prefab_load_2(two::AssetStore<two::Prefab>* self, const char* path, const char* name) {
		return self->load(path, name);
	}
	void DECL two_AssetStore_two_Prefab_destroy_1(two::AssetStore<two::Prefab>* self, const char* name) {
		self->destroy(name);
	}
	void DECL two_AssetStore_two_Prefab_clear_0(two::AssetStore<two::Prefab>* self) {
		self->clear();
	}
	void DECL two_AssetStore_two_Prefab__destroy(two::AssetStore<two::Prefab>* self) {
		delete self;
	}
	// Camera
	two::Type* DECL two_Camera__type() {
		return &two::type<two::Camera>();
	}
	void DECL two_Camera_set_look_at_2(two::Camera* self, const two::vec3* eye, const two::vec3* target) {
		self->set_look_at(*eye, *target);
	}
	void DECL two_Camera_set_isometric_2(two::Camera* self, two::IsometricAngle angle, const two::vec3* position) {
		self->set_isometric(angle, *position);
	}
	two::Ray* DECL two_Camera_ray_1(two::Camera* self, const two::vec2* offset) {
		static two::Ray temp;
		return (temp = self->ray(*offset), &temp);
	}
	two::vec3* DECL two_Camera_transform_1(two::Camera* self, const two::vec3* point) {
		static two::vec3 temp;
		return (temp = self->transform(*point), &temp);
	}
	two::vec3* DECL two_Camera_project_1(two::Camera* self, const two::vec3* point) {
		static two::vec3 temp;
		return (temp = self->project(*point), &temp);
	}
	two::vec3* DECL two_Camera__get_eye(two::Camera* self) {
		return &self->m_eye;
	}
	void DECL two_Camera__set_eye(two::Camera* self, two::vec3* value) {
		self->m_eye = *value;
	}
	two::vec3* DECL two_Camera__get_target(two::Camera* self) {
		return &self->m_target;
	}
	void DECL two_Camera__set_target(two::Camera* self, two::vec3* value) {
		self->m_target = *value;
	}
	two::vec3* DECL two_Camera__get_up(two::Camera* self) {
		return &self->m_up;
	}
	void DECL two_Camera__set_up(two::Camera* self, two::vec3* value) {
		self->m_up = *value;
	}
	two::mat4* DECL two_Camera__get_view(two::Camera* self) {
		return &self->m_view;
	}
	void DECL two_Camera__set_view(two::Camera* self, two::mat4* value) {
		self->m_view = *value;
	}
	two::mat4* DECL two_Camera__get_proj(two::Camera* self) {
		return &self->m_proj;
	}
	void DECL two_Camera__set_proj(two::Camera* self, two::mat4* value) {
		self->m_proj = *value;
	}
	float DECL two_Camera__get_fov(two::Camera* self) {
		return self->m_fov;
	}
	void DECL two_Camera__set_fov(two::Camera* self, float value) {
		self->m_fov = value;
	}
	float DECL two_Camera__get_aspect(two::Camera* self) {
		return self->m_aspect;
	}
	void DECL two_Camera__set_aspect(two::Camera* self, float value) {
		self->m_aspect = value;
	}
	float DECL two_Camera__get_near(two::Camera* self) {
		return self->m_near;
	}
	void DECL two_Camera__set_near(two::Camera* self, float value) {
		self->m_near = value;
	}
	float DECL two_Camera__get_far(two::Camera* self) {
		return self->m_far;
	}
	void DECL two_Camera__set_far(two::Camera* self, float value) {
		self->m_far = value;
	}
	bool DECL two_Camera__get_orthographic(two::Camera* self) {
		return self->m_orthographic;
	}
	void DECL two_Camera__set_orthographic(two::Camera* self, bool value) {
		self->m_orthographic = value;
	}
	float DECL two_Camera__get_height(two::Camera* self) {
		return self->m_height;
	}
	void DECL two_Camera__set_height(two::Camera* self, float value) {
		self->m_height = value;
	}
	bool DECL two_Camera__get_no_update(two::Camera* self) {
		return self->m_no_update;
	}
	void DECL two_Camera__set_no_update(two::Camera* self, bool value) {
		self->m_no_update = value;
	}
	bool DECL two_Camera__get_optimize_ends(two::Camera* self) {
		return self->m_optimize_ends;
	}
	void DECL two_Camera__set_optimize_ends(two::Camera* self, bool value) {
		self->m_optimize_ends = value;
	}
	two::vec4* DECL two_Camera__get_lod_offsets(two::Camera* self) {
		return &self->m_lod_offsets;
	}
	void DECL two_Camera__set_lod_offsets(two::Camera* self, two::vec4* value) {
		self->m_lod_offsets = *value;
	}
	void DECL two_Camera__destroy(two::Camera* self) {
		delete self;
	}
	// MirrorCamera
	two::Type* DECL two_MirrorCamera__type() {
		return &two::type<two::MirrorCamera>();
	}
	two::MirrorCamera* DECL two_MirrorCamera__construct_0() {
		return new two::MirrorCamera();
	}
	bool DECL two_MirrorCamera__get_visible(two::MirrorCamera* self) {
		return self->m_visible;
	}
	void DECL two_MirrorCamera__set_visible(two::MirrorCamera* self, bool value) {
		self->m_visible = value;
	}
	two::Camera* DECL two_MirrorCamera__get_camera(two::MirrorCamera* self) {
		return &self->m_camera;
	}
	two::mat4* DECL two_MirrorCamera__get_mirror(two::MirrorCamera* self) {
		return &self->m_mirror;
	}
	void DECL two_MirrorCamera__set_mirror(two::MirrorCamera* self, two::mat4* value) {
		self->m_mirror = *value;
	}
	void DECL two_MirrorCamera__destroy(two::MirrorCamera* self) {
		delete self;
	}
	// DepthParams
	two::Type* DECL two_DepthParams__type() {
		return &two::type<two::DepthParams>();
	}
	two::DepthParams* DECL two_DepthParams__construct_0() {
		return new two::DepthParams();
	}
	float DECL two_DepthParams__get_depth_bias(two::DepthParams* self) {
		return self->m_depth_bias;
	}
	void DECL two_DepthParams__set_depth_bias(two::DepthParams* self, float value) {
		self->m_depth_bias = value;
	}
	float DECL two_DepthParams__get_depth_normal_bias(two::DepthParams* self) {
		return self->m_depth_normal_bias;
	}
	void DECL two_DepthParams__set_depth_normal_bias(two::DepthParams* self, float value) {
		self->m_depth_normal_bias = value;
	}
	float DECL two_DepthParams__get_depth_z_far(two::DepthParams* self) {
		return self->m_depth_z_far;
	}
	void DECL two_DepthParams__set_depth_z_far(two::DepthParams* self, float value) {
		self->m_depth_z_far = value;
	}
	void DECL two_DepthParams__destroy(two::DepthParams* self) {
		delete self;
	}
	// DistanceParams
	two::Type* DECL two_DistanceParams__type() {
		return &two::type<two::DistanceParams>();
	}
	two::DistanceParams* DECL two_DistanceParams__construct_0() {
		return new two::DistanceParams();
	}
	two::vec3* DECL two_DistanceParams__get_eye(two::DistanceParams* self) {
		return &self->m_eye;
	}
	void DECL two_DistanceParams__set_eye(two::DistanceParams* self, two::vec3* value) {
		self->m_eye = *value;
	}
	float DECL two_DistanceParams__get_near(two::DistanceParams* self) {
		return self->m_near;
	}
	void DECL two_DistanceParams__set_near(two::DistanceParams* self, float value) {
		self->m_near = value;
	}
	float DECL two_DistanceParams__get_far(two::DistanceParams* self) {
		return self->m_far;
	}
	void DECL two_DistanceParams__set_far(two::DistanceParams* self, float value) {
		self->m_far = value;
	}
	void DECL two_DistanceParams__destroy(two::DistanceParams* self) {
		delete self;
	}
	// BlockDepth
	two::Type* DECL two_BlockDepth__type() {
		return &two::type<two::BlockDepth>();
	}
	void DECL two_BlockDepth__destroy(two::BlockDepth* self) {
		delete self;
	}
	// GpuMesh
	two::Type* DECL two_GpuMesh__type() {
		return &two::type<two::GpuMesh>();
	}
	two::GpuMesh* DECL two_GpuMesh__construct_0() {
		return new two::GpuMesh();
	}
	void DECL two_GpuMesh__destroy(two::GpuMesh* self) {
		delete self;
	}
	// Mesh
	two::Type* DECL two_Mesh__type() {
		return &two::type<two::Mesh>();
	}
	void DECL two_Mesh_clear_0(two::Mesh* self) {
		self->clear();
	}
	void DECL two_Mesh_write_1(two::Mesh* self, const two::MeshPacker* packer) {
		self->write(*packer);
	}
	void DECL two_Mesh_write_2(two::Mesh* self, const two::MeshPacker* packer, bool optimize) {
		self->write(*packer, optimize);
	}
	void DECL two_Mesh_write_3(two::Mesh* self, const two::MeshPacker* packer, bool optimize, bool dynamic) {
		self->write(*packer, optimize, dynamic);
	}
	void DECL two_Mesh_xwrite_2(two::Mesh* self, const two::MeshPacker* packer, const two::mat4* transform) {
		self->xwrite(*packer, *transform);
	}
	void DECL two_Mesh_xwrite_3(two::Mesh* self, const two::MeshPacker* packer, const two::mat4* transform, bool optimize) {
		self->xwrite(*packer, *transform, optimize);
	}
	void DECL two_Mesh_xwrite_4(two::Mesh* self, const two::MeshPacker* packer, const two::mat4* transform, bool optimize, bool dynamic) {
		self->xwrite(*packer, *transform, optimize, dynamic);
	}
	void DECL two_Mesh_morph_1(two::Mesh* self, const two::MeshPacker* packer) {
		self->morph(*packer);
	}
	void DECL two_Mesh_upload_1(two::Mesh* self, const two::GpuMesh* gpu_mesh) {
		self->upload(*gpu_mesh);
	}
	void DECL two_Mesh_upload_2(two::Mesh* self, const two::GpuMesh* gpu_mesh, bool optimize) {
		self->upload(*gpu_mesh, optimize);
	}
	void DECL two_Mesh_cache_1(two::Mesh* self, const two::GpuMesh* gpu_mesh) {
		self->cache(*gpu_mesh);
	}
	two::MeshAdapter* DECL two_Mesh_direct_2(two::Mesh* self, uint32_t vertex_format, uint32_t vertex_count) {
		return &self->direct(vertex_format, vertex_count);
	}
	two::MeshAdapter* DECL two_Mesh_direct_3(two::Mesh* self, uint32_t vertex_format, uint32_t vertex_count, uint32_t index_count) {
		return &self->direct(vertex_format, vertex_count, index_count);
	}
	const char* DECL two_Mesh__get_name(two::Mesh* self) {
		return self->m_name.c_str();
	}
	void DECL two_Mesh__set_name(two::Mesh* self, const char* value) {
		self->m_name = value;
	}
	uint16_t DECL two_Mesh__get_index(two::Mesh* self) {
		return self->m_index;
	}
	void DECL two_Mesh__set_index(two::Mesh* self, uint16_t value) {
		self->m_index = value;
	}
	two::PrimitiveType DECL two_Mesh__get_primitive(two::Mesh* self) {
		return self->m_primitive;
	}
	void DECL two_Mesh__set_primitive(two::Mesh* self, two::PrimitiveType value) {
		self->m_primitive = value;
	}
	two::Aabb* DECL two_Mesh__get_aabb(two::Mesh* self) {
		return &self->m_aabb;
	}
	void DECL two_Mesh__set_aabb(two::Mesh* self, two::Aabb* value) {
		self->m_aabb = *value;
	}
	float DECL two_Mesh__get_radius(two::Mesh* self) {
		return self->m_radius;
	}
	void DECL two_Mesh__set_radius(two::Mesh* self, float value) {
		self->m_radius = value;
	}
	two::vec3* DECL two_Mesh__get_origin(two::Mesh* self) {
		return &self->m_origin;
	}
	void DECL two_Mesh__set_origin(two::Mesh* self, two::vec3* value) {
		self->m_origin = *value;
	}
	bool DECL two_Mesh__get_readback(two::Mesh* self) {
		return self->m_readback;
	}
	void DECL two_Mesh__set_readback(two::Mesh* self, bool value) {
		self->m_readback = value;
	}
	uint32_t DECL two_Mesh__get_vertex_format(two::Mesh* self) {
		return self->m_vertex_format;
	}
	void DECL two_Mesh__set_vertex_format(two::Mesh* self, uint32_t value) {
		self->m_vertex_format = value;
	}
	bool DECL two_Mesh__get_qnormals(two::Mesh* self) {
		return self->m_qnormals;
	}
	void DECL two_Mesh__set_qnormals(two::Mesh* self, bool value) {
		self->m_qnormals = value;
	}
	uint32_t DECL two_Mesh__get_vertex_count(two::Mesh* self) {
		return self->m_vertex_count;
	}
	void DECL two_Mesh__set_vertex_count(two::Mesh* self, uint32_t value) {
		self->m_vertex_count = value;
	}
	uint32_t DECL two_Mesh__get_index_count(two::Mesh* self) {
		return self->m_index_count;
	}
	void DECL two_Mesh__set_index_count(two::Mesh* self, uint32_t value) {
		self->m_index_count = value;
	}
	bool DECL two_Mesh__get_index32(two::Mesh* self) {
		return self->m_index32;
	}
	void DECL two_Mesh__set_index32(two::Mesh* self, bool value) {
		self->m_index32 = value;
	}
	two::Material* DECL two_Mesh__get_material(two::Mesh* self) {
		return self->m_material;
	}
	void DECL two_Mesh__set_material(two::Mesh* self, two::Material* value) {
		self->m_material = value;
	}
	bool DECL two_Mesh__get_is_dynamic(two::Mesh* self) {
		return self->m_is_dynamic;
	}
	void DECL two_Mesh__set_is_dynamic(two::Mesh* self, bool value) {
		self->m_is_dynamic = value;
	}
	bool DECL two_Mesh__get_is_direct(two::Mesh* self) {
		return self->m_is_direct;
	}
	void DECL two_Mesh__set_is_direct(two::Mesh* self, bool value) {
		self->m_is_direct = value;
	}
	two::MeshAdapter* DECL two_Mesh__get_cache(two::Mesh* self) {
		return &self->m_cache;
	}
	void DECL two_Mesh__set_cache(two::Mesh* self, two::MeshAdapter* value) {
		self->m_cache = *value;
	}
	void DECL two_Mesh__destroy(two::Mesh* self) {
		delete self;
	}
	// Direct
	two::Type* DECL two_Direct__type() {
		return &two::type<two::Direct>();
	}
	two::Direct* DECL two_Direct__construct_0() {
		return new two::Direct();
	}
	two::Direct* DECL two_Direct__construct_1(two::Item* item) {
		return new two::Direct(*item);
	}
	two::Item* DECL two_Direct__get_item(two::Direct* self) {
		return self->m_item;
	}
	void DECL two_Direct__set_item(two::Direct* self, two::Item* value) {
		self->m_item = value;
	}
	void DECL two_Direct__destroy(two::Direct* self) {
		delete self;
	}
	// ImmediateDraw
	two::Type* DECL two_ImmediateDraw__type() {
		return &two::type<two::ImmediateDraw>();
	}
	void DECL two_ImmediateDraw__destroy(two::ImmediateDraw* self) {
		delete self;
	}
	// SymbolIndex
	two::Type* DECL two_SymbolIndex__type() {
		return &two::type<two::SymbolIndex>();
	}
	void DECL two_SymbolIndex__destroy(two::SymbolIndex* self) {
		delete self;
	}
	// Lines
	two::Type* DECL two_Lines__type() {
		return &two::type<two::Lines>();
	}
	two::Lines* DECL two_Lines__construct_0() {
		return new two::Lines();
	}
	two::Lines* DECL two_Lines__construct_2(const two::Curve3* curve, size_t subdiv) {
		return new two::Lines(*curve, subdiv);
	}
	void DECL two_Lines_add_2(two::Lines* self, const two::vec3* start, const two::vec3* end) {
		self->add(*start, *end);
	}
	void DECL two_Lines_add_3(two::Lines* self, const two::vec3* start, const two::vec3* end, const two::Colour* start_colour) {
		self->add(*start, *end, *start_colour);
	}
	void DECL two_Lines_add_4(two::Lines* self, const two::vec3* start, const two::vec3* end, const two::Colour* start_colour, const two::Colour* end_colour) {
		self->add(*start, *end, *start_colour, *end_colour);
	}
	void DECL two_Lines_start_1(two::Lines* self, const two::vec3* position) {
		self->start(*position);
	}
	void DECL two_Lines_start_2(two::Lines* self, const two::vec3* position, const two::Colour* colour) {
		self->start(*position, *colour);
	}
	void DECL two_Lines_next_1(two::Lines* self, const two::vec3* position) {
		self->next(*position);
	}
	void DECL two_Lines_next_2(two::Lines* self, const two::vec3* position, const two::Colour* colour) {
		self->next(*position, *colour);
	}
	void DECL two_Lines_setup_0(two::Lines* self) {
		self->setup();
	}
	void DECL two_Lines_write_1(two::Lines* self, two::Mesh* mesh) {
		self->write(*mesh);
	}
	void DECL two_Lines_commit_1(two::Lines* self, two::Batch* batch) {
		self->commit(*batch);
	}
	void DECL two_Lines__destroy(two::Lines* self) {
		delete self;
	}
	// BlockFilter
	two::Type* DECL two_BlockFilter__type() {
		return &two::type<two::BlockFilter>();
	}
	void DECL two_BlockFilter_submit_4(two::BlockFilter* self, const two::Pass* pass, two::FrameBuffer* fbo, const two::ProgramVersion* program, const two::RenderQuad* quad) {
		self->submit(*pass, *fbo, *program, *quad);
	}
	void DECL two_BlockFilter_submit_5(two::BlockFilter* self, const two::Pass* pass, two::FrameBuffer* fbo, const two::ProgramVersion* program, const two::RenderQuad* quad, uint64_t flags) {
		self->submit(*pass, *fbo, *program, *quad, flags);
	}
	void DECL two_BlockFilter_submit_6(two::BlockFilter* self, const two::Pass* pass, two::FrameBuffer* fbo, const two::ProgramVersion* program, const two::RenderQuad* quad, uint64_t flags, bool render) {
		self->submit(*pass, *fbo, *program, *quad, flags, render);
	}
	void DECL two_BlockFilter_quad_3(two::BlockFilter* self, const two::Pass* pass, two::FrameBuffer* fbo, const two::ProgramVersion* program) {
		self->quad(*pass, *fbo, *program);
	}
	void DECL two_BlockFilter_quad_4(two::BlockFilter* self, const two::Pass* pass, two::FrameBuffer* fbo, const two::ProgramVersion* program, uint64_t flags) {
		self->quad(*pass, *fbo, *program, flags);
	}
	void DECL two_BlockFilter_quad_5(two::BlockFilter* self, const two::Pass* pass, two::FrameBuffer* fbo, const two::ProgramVersion* program, uint64_t flags, bool render) {
		self->quad(*pass, *fbo, *program, flags, render);
	}
	void DECL two_BlockFilter_multiply_1(two::BlockFilter* self, float mul) {
		self->multiply(mul);
	}
	void DECL two_BlockFilter_source0p_2(two::BlockFilter* self, const two::Texture* texture, two::ProgramVersion* program) {
		self->source0p(*texture, *program);
	}
	void DECL two_BlockFilter_source0p_3(two::BlockFilter* self, const two::Texture* texture, two::ProgramVersion* program, int level) {
		self->source0p(*texture, *program, level);
	}
	void DECL two_BlockFilter_source0p_4(two::BlockFilter* self, const two::Texture* texture, two::ProgramVersion* program, int level, uint32_t flags) {
		self->source0p(*texture, *program, level, flags);
	}
	void DECL two_BlockFilter_source0_1(two::BlockFilter* self, const two::Texture* texture) {
		self->source0(*texture);
	}
	void DECL two_BlockFilter_source0_2(two::BlockFilter* self, const two::Texture* texture, uint32_t flags) {
		self->source0(*texture, flags);
	}
	void DECL two_BlockFilter_source1_1(two::BlockFilter* self, const two::Texture* texture) {
		self->source1(*texture);
	}
	void DECL two_BlockFilter_source1_2(two::BlockFilter* self, const two::Texture* texture, uint32_t flags) {
		self->source1(*texture, flags);
	}
	void DECL two_BlockFilter_source2_1(two::BlockFilter* self, const two::Texture* texture) {
		self->source2(*texture);
	}
	void DECL two_BlockFilter_source2_2(two::BlockFilter* self, const two::Texture* texture, uint32_t flags) {
		self->source2(*texture, flags);
	}
	void DECL two_BlockFilter_source3_1(two::BlockFilter* self, const two::Texture* texture) {
		self->source3(*texture);
	}
	void DECL two_BlockFilter_source3_2(two::BlockFilter* self, const two::Texture* texture, uint32_t flags) {
		self->source3(*texture, flags);
	}
	void DECL two_BlockFilter_sourcedepth_1(two::BlockFilter* self, const two::Texture* texture) {
		self->sourcedepth(*texture);
	}
	void DECL two_BlockFilter_sourcedepth_2(two::BlockFilter* self, const two::Texture* texture, uint32_t flags) {
		self->sourcedepth(*texture, flags);
	}
	void DECL two_BlockFilter_uniform_3(two::BlockFilter* self, const two::Pass* pass, const char* name, const two::vec4* value) {
		self->uniform(*pass, name, *value);
	}
	void DECL two_BlockFilter_uniforms_3(two::BlockFilter* self, const two::Pass* pass, const char* name, float* values, int values_size) {
		self->uniforms(*pass, name, { (float*)values, values_size / (sizeof(float) / sizeof(float)) });
	}
	void DECL two_BlockFilter__destroy(two::BlockFilter* self) {
		delete self;
	}
	// BlockCopy
	two::Type* DECL two_BlockCopy__type() {
		return &two::type<two::BlockCopy>();
	}
	void DECL two_BlockCopy_submit_4(two::BlockCopy* self, const two::Pass* pass, two::FrameBuffer* fbo, const two::Texture* texture, const two::RenderQuad* quad) {
		self->submit(*pass, *fbo, *texture, *quad);
	}
	void DECL two_BlockCopy_submit_5(two::BlockCopy* self, const two::Pass* pass, two::FrameBuffer* fbo, const two::Texture* texture, const two::RenderQuad* quad, uint64_t flags) {
		self->submit(*pass, *fbo, *texture, *quad, flags);
	}
	void DECL two_BlockCopy_submit_6(two::BlockCopy* self, const two::Pass* pass, two::FrameBuffer* fbo, const two::Texture* texture, const two::RenderQuad* quad, uint64_t flags, bool render) {
		self->submit(*pass, *fbo, *texture, *quad, flags, render);
	}
	void DECL two_BlockCopy_quad_3(two::BlockCopy* self, const two::Pass* pass, two::FrameBuffer* fbo, const two::Texture* texture) {
		self->quad(*pass, *fbo, *texture);
	}
	void DECL two_BlockCopy_quad_4(two::BlockCopy* self, const two::Pass* pass, two::FrameBuffer* fbo, const two::Texture* texture, uint64_t flags) {
		self->quad(*pass, *fbo, *texture, flags);
	}
	void DECL two_BlockCopy_quad_5(two::BlockCopy* self, const two::Pass* pass, two::FrameBuffer* fbo, const two::Texture* texture, uint64_t flags, bool render) {
		self->quad(*pass, *fbo, *texture, flags, render);
	}
	void DECL two_BlockCopy_debug_show_texture_3(two::BlockCopy* self, two::Render* render, const two::Texture* texture, const two::vec4* rect) {
		self->debug_show_texture(*render, *texture, *rect);
	}
	void DECL two_BlockCopy_debug_show_texture_4(two::BlockCopy* self, two::Render* render, const two::Texture* texture, const two::vec4* rect, int level) {
		self->debug_show_texture(*render, *texture, *rect, level);
	}
	void DECL two_BlockCopy_debug_show_texturep_3(two::BlockCopy* self, two::Render* render, const two::Texture* texture, const two::vec4* rect) {
		self->debug_show_texturep(*render, texture, *rect);
	}
	void DECL two_BlockCopy_debug_show_texturep_4(two::BlockCopy* self, two::Render* render, const two::Texture* texture, const two::vec4* rect, int level) {
		self->debug_show_texturep(*render, texture, *rect, level);
	}
	void DECL two_BlockCopy__destroy(two::BlockCopy* self) {
		delete self;
	}
	// ClusteredFrustum
	two::Type* DECL two_ClusteredFrustum__type() {
		return &two::type<two::ClusteredFrustum>();
	}
	two::ClusteredFrustum* DECL two_ClusteredFrustum__construct_0() {
		return new two::ClusteredFrustum();
	}
	void DECL two_ClusteredFrustum__destroy(two::ClusteredFrustum* self) {
		delete self;
	}
	// Light
	two::Type* DECL two_Light__type() {
		return &two::type<two::Light>();
	}
	two::Light* DECL two_Light__construct_1(two::Node3* node) {
		return new two::Light(*node);
	}
	two::Light* DECL two_Light__construct_2(two::Node3* node, two::LightType type) {
		return new two::Light(*node, type);
	}
	two::Light* DECL two_Light__construct_3(two::Node3* node, two::LightType type, bool shadows) {
		return new two::Light(*node, type, shadows);
	}
	two::Light* DECL two_Light__construct_4(two::Node3* node, two::LightType type, bool shadows, two::Colour* colour) {
		return new two::Light(*node, type, shadows, *colour);
	}
	two::Light* DECL two_Light__construct_5(two::Node3* node, two::LightType type, bool shadows, two::Colour* colour, float energy) {
		return new two::Light(*node, type, shadows, *colour, energy);
	}
	two::Light* DECL two_Light__construct_6(two::Node3* node, two::LightType type, bool shadows, two::Colour* colour, float energy, float range) {
		return new two::Light(*node, type, shadows, *colour, energy, range);
	}
	two::Node3* DECL two_Light__get_node(two::Light* self) {
		return self->m_node;
	}
	void DECL two_Light__set_node(two::Light* self, two::Node3* value) {
		self->m_node = value;
	}
	two::LightType DECL two_Light__get_type(two::Light* self) {
		return self->m_type;
	}
	void DECL two_Light__set_type(two::Light* self, two::LightType value) {
		self->m_type = value;
	}
	bool DECL two_Light__get_visible(two::Light* self) {
		return self->m_visible;
	}
	void DECL two_Light__set_visible(two::Light* self, bool value) {
		self->m_visible = value;
	}
	two::Colour* DECL two_Light__get_colour(two::Light* self) {
		return &self->m_colour;
	}
	void DECL two_Light__set_colour(two::Light* self, two::Colour* value) {
		self->m_colour = *value;
	}
	float DECL two_Light__get_range(two::Light* self) {
		return self->m_range;
	}
	void DECL two_Light__set_range(two::Light* self, float value) {
		self->m_range = value;
	}
	float DECL two_Light__get_energy(two::Light* self) {
		return self->m_energy;
	}
	void DECL two_Light__set_energy(two::Light* self, float value) {
		self->m_energy = value;
	}
	float DECL two_Light__get_specular(two::Light* self) {
		return self->m_specular;
	}
	void DECL two_Light__set_specular(two::Light* self, float value) {
		self->m_specular = value;
	}
	float DECL two_Light__get_attenuation(two::Light* self) {
		return self->m_attenuation;
	}
	void DECL two_Light__set_attenuation(two::Light* self, float value) {
		self->m_attenuation = value;
	}
	bool DECL two_Light__get_shadows(two::Light* self) {
		return self->m_shadows;
	}
	void DECL two_Light__set_shadows(two::Light* self, bool value) {
		self->m_shadows = value;
	}
	float DECL two_Light__get_shadow_range(two::Light* self) {
		return self->m_shadow_range;
	}
	void DECL two_Light__set_shadow_range(two::Light* self, float value) {
		self->m_shadow_range = value;
	}
	uint32_t DECL two_Light__get_layers(two::Light* self) {
		return self->m_layers;
	}
	void DECL two_Light__set_layers(two::Light* self, uint32_t value) {
		self->m_layers = value;
	}
	uint32_t DECL two_Light__get_last_render(two::Light* self) {
		return self->m_last_render;
	}
	void DECL two_Light__set_last_render(two::Light* self, uint32_t value) {
		self->m_last_render = value;
	}
	uint32_t DECL two_Light__get_last_update(two::Light* self) {
		return self->m_last_update;
	}
	void DECL two_Light__set_last_update(two::Light* self, uint32_t value) {
		self->m_last_update = value;
	}
	float DECL two_Light__get_spot_angle(two::Light* self) {
		return self->m_spot_angle;
	}
	void DECL two_Light__set_spot_angle(two::Light* self, float value) {
		self->m_spot_angle = value;
	}
	float DECL two_Light__get_spot_attenuation(two::Light* self) {
		return self->m_spot_attenuation;
	}
	void DECL two_Light__set_spot_attenuation(two::Light* self, float value) {
		self->m_spot_attenuation = value;
	}
	two::ShadowFlags DECL two_Light__get_shadow_flags(two::Light* self) {
		return self->m_shadow_flags;
	}
	void DECL two_Light__set_shadow_flags(two::Light* self, two::ShadowFlags value) {
		self->m_shadow_flags = value;
	}
	uint8_t DECL two_Light__get_shadow_nusplits(two::Light* self) {
		return self->m_shadow_num_splits;
	}
	void DECL two_Light__set_shadow_nusplits(two::Light* self, uint8_t value) {
		self->m_shadow_num_splits = value;
	}
	float DECL two_Light__get_shadow_split_distribution(two::Light* self) {
		return self->m_shadow_split_distribution;
	}
	void DECL two_Light__set_shadow_split_distribution(two::Light* self, float value) {
		self->m_shadow_split_distribution = value;
	}
	float DECL two_Light__get_shadow_normal_bias(two::Light* self) {
		return self->m_shadow_normal_bias;
	}
	void DECL two_Light__set_shadow_normal_bias(two::Light* self, float value) {
		self->m_shadow_normal_bias = value;
	}
	float DECL two_Light__get_shadow_bias(two::Light* self) {
		return self->m_shadow_bias;
	}
	void DECL two_Light__set_shadow_bias(two::Light* self, float value) {
		self->m_shadow_bias = value;
	}
	void DECL two_Light__destroy(two::Light* self) {
		delete self;
	}
	// Gnode
	two::Type* DECL two_Gnode__type() {
		return &two::type<two::Gnode>();
	}
	void DECL two_Gnode__destroy(two::Gnode* self) {
		delete self;
	}
	// TPool<two::Node3>
	two::Type* DECL two_TPool_two_Node3__type() {
		return &two::type<two::TPool<two::Node3>>();
	}
	two::Node3* DECL two_TPool_two_Node3_add_1(two::TPool<two::Node3>* self, const two::Node3* value) {
		return &self->add(*value);
	}
	two::Node3* DECL two_TPool_two_Node3_talloc_0(two::TPool<two::Node3>* self) {
		return self->talloc();
	}
	void DECL two_TPool_two_Node3_tdestroy_1(two::TPool<two::Node3>* self, two::Node3* object) {
		self->tdestroy(*object);
	}
	void DECL two_TPool_two_Node3_tfree_1(two::TPool<two::Node3>* self, two::Node3* object) {
		self->tfree(*object);
	}
	void DECL two_TPool_two_Node3__destroy(two::TPool<two::Node3>* self) {
		delete self;
	}
	// TPool<two::Item>
	two::Type* DECL two_TPool_two_Item__type() {
		return &two::type<two::TPool<two::Item>>();
	}
	two::Item* DECL two_TPool_two_Item_add_1(two::TPool<two::Item>* self, const two::Item* value) {
		return &self->add(*value);
	}
	two::Item* DECL two_TPool_two_Item_talloc_0(two::TPool<two::Item>* self) {
		return self->talloc();
	}
	void DECL two_TPool_two_Item_tdestroy_1(two::TPool<two::Item>* self, two::Item* object) {
		self->tdestroy(*object);
	}
	void DECL two_TPool_two_Item_tfree_1(two::TPool<two::Item>* self, two::Item* object) {
		self->tfree(*object);
	}
	void DECL two_TPool_two_Item__destroy(two::TPool<two::Item>* self) {
		delete self;
	}
	// TPool<two::Batch>
	two::Type* DECL two_TPool_two_Batch__type() {
		return &two::type<two::TPool<two::Batch>>();
	}
	two::Batch* DECL two_TPool_two_Batch_add_1(two::TPool<two::Batch>* self, const two::Batch* value) {
		return &self->add(*value);
	}
	two::Batch* DECL two_TPool_two_Batch_talloc_0(two::TPool<two::Batch>* self) {
		return self->talloc();
	}
	void DECL two_TPool_two_Batch_tdestroy_1(two::TPool<two::Batch>* self, two::Batch* object) {
		self->tdestroy(*object);
	}
	void DECL two_TPool_two_Batch_tfree_1(two::TPool<two::Batch>* self, two::Batch* object) {
		self->tfree(*object);
	}
	void DECL two_TPool_two_Batch__destroy(two::TPool<two::Batch>* self) {
		delete self;
	}
	// TPool<two::Direct>
	two::Type* DECL two_TPool_two_Direct__type() {
		return &two::type<two::TPool<two::Direct>>();
	}
	two::Direct* DECL two_TPool_two_Direct_add_1(two::TPool<two::Direct>* self, const two::Direct* value) {
		return &self->add(*value);
	}
	two::Direct* DECL two_TPool_two_Direct_talloc_0(two::TPool<two::Direct>* self) {
		return self->talloc();
	}
	void DECL two_TPool_two_Direct_tdestroy_1(two::TPool<two::Direct>* self, two::Direct* object) {
		self->tdestroy(*object);
	}
	void DECL two_TPool_two_Direct_tfree_1(two::TPool<two::Direct>* self, two::Direct* object) {
		self->tfree(*object);
	}
	void DECL two_TPool_two_Direct__destroy(two::TPool<two::Direct>* self) {
		delete self;
	}
	// TPool<two::Mime>
	two::Type* DECL two_TPool_two_Mime__type() {
		return &two::type<two::TPool<two::Mime>>();
	}
	two::Mime* DECL two_TPool_two_Mime_add_1(two::TPool<two::Mime>* self, const two::Mime* value) {
		return &self->add(*value);
	}
	two::Mime* DECL two_TPool_two_Mime_talloc_0(two::TPool<two::Mime>* self) {
		return self->talloc();
	}
	void DECL two_TPool_two_Mime_tdestroy_1(two::TPool<two::Mime>* self, two::Mime* object) {
		self->tdestroy(*object);
	}
	void DECL two_TPool_two_Mime_tfree_1(two::TPool<two::Mime>* self, two::Mime* object) {
		self->tfree(*object);
	}
	void DECL two_TPool_two_Mime__destroy(two::TPool<two::Mime>* self) {
		delete self;
	}
	// TPool<two::Light>
	two::Type* DECL two_TPool_two_Light__type() {
		return &two::type<two::TPool<two::Light>>();
	}
	two::Light* DECL two_TPool_two_Light_add_1(two::TPool<two::Light>* self, const two::Light* value) {
		return &self->add(*value);
	}
	two::Light* DECL two_TPool_two_Light_talloc_0(two::TPool<two::Light>* self) {
		return self->talloc();
	}
	void DECL two_TPool_two_Light_tdestroy_1(two::TPool<two::Light>* self, two::Light* object) {
		self->tdestroy(*object);
	}
	void DECL two_TPool_two_Light_tfree_1(two::TPool<two::Light>* self, two::Light* object) {
		self->tfree(*object);
	}
	void DECL two_TPool_two_Light__destroy(two::TPool<two::Light>* self) {
		delete self;
	}
	// TPool<two::Flare>
	two::Type* DECL two_TPool_two_Flare__type() {
		return &two::type<two::TPool<two::Flare>>();
	}
	two::Flare* DECL two_TPool_two_Flare_add_1(two::TPool<two::Flare>* self, const two::Flare* value) {
		return &self->add(*value);
	}
	two::Flare* DECL two_TPool_two_Flare_talloc_0(two::TPool<two::Flare>* self) {
		return self->talloc();
	}
	void DECL two_TPool_two_Flare_tdestroy_1(two::TPool<two::Flare>* self, two::Flare* object) {
		self->tdestroy(*object);
	}
	void DECL two_TPool_two_Flare_tfree_1(two::TPool<two::Flare>* self, two::Flare* object) {
		self->tfree(*object);
	}
	void DECL two_TPool_two_Flare__destroy(two::TPool<two::Flare>* self) {
		delete self;
	}
	// Culler
	two::Type* DECL two_Culler__type() {
		return &two::type<two::Culler>();
	}
	two::Viewport* DECL two_Culler__get_viewport(two::Culler* self) {
		return self->m_viewport;
	}
	void DECL two_Culler__set_viewport(two::Culler* self, two::Viewport* value) {
		self->m_viewport = value;
	}
	void DECL two_Culler__destroy(two::Culler* self) {
		delete self;
	}
	// Viewport
	two::Type* DECL two_Viewport__type() {
		return &two::type<two::Viewport>();
	}
	two::Viewport* DECL two_Viewport__construct_0() {
		return new two::Viewport();
	}
	two::Viewport* DECL two_Viewport__construct_2(two::Camera* camera, two::Scene* scene) {
		return new two::Viewport(*camera, *scene);
	}
	two::Viewport* DECL two_Viewport__construct_3(two::Camera* camera, two::Scene* scene, const two::vec4* rect) {
		return new two::Viewport(*camera, *scene, *rect);
	}
	two::Viewport* DECL two_Viewport__construct_4(two::Camera* camera, two::Scene* scene, const two::vec4* rect, bool scissor) {
		return new two::Viewport(*camera, *scene, *rect, scissor);
	}
	void DECL two_Viewport_cull_1(two::Viewport* self, two::Render* render) {
		self->cull(*render);
	}
	void DECL two_Viewport_render_1(two::Viewport* self, two::Render* render) {
		self->render(*render);
	}
	void DECL two_Viewport_set_clustered_1(two::Viewport* self, two::GfxSystem* gfx) {
		self->set_clustered(*gfx);
	}
	two::Camera* DECL two_Viewport__get_camera(two::Viewport* self) {
		return self->m_camera;
	}
	void DECL two_Viewport__set_camera(two::Viewport* self, two::Camera* value) {
		self->m_camera = value;
	}
	two::Scene* DECL two_Viewport__get_scene(two::Viewport* self) {
		return self->m_scene;
	}
	void DECL two_Viewport__set_scene(two::Viewport* self, two::Scene* value) {
		self->m_scene = value;
	}
	uint16_t DECL two_Viewport__get_index(two::Viewport* self) {
		return self->m_index;
	}
	void DECL two_Viewport__set_index(two::Viewport* self, uint16_t value) {
		self->m_index = value;
	}
	bool DECL two_Viewport__get_autorender(two::Viewport* self) {
		return self->m_autorender;
	}
	void DECL two_Viewport__set_autorender(two::Viewport* self, bool value) {
		self->m_autorender = value;
	}
	bool DECL two_Viewport__get_autoflip(two::Viewport* self) {
		return self->m_autoflip;
	}
	void DECL two_Viewport__set_autoflip(two::Viewport* self, bool value) {
		self->m_autoflip = value;
	}
	two::vec4* DECL two_Viewport__get_rect(two::Viewport* self) {
		return &self->m_rect;
	}
	void DECL two_Viewport__set_rect(two::Viewport* self, two::vec4* value) {
		self->m_rect = *value;
	}
	bool DECL two_Viewport__get_scissor(two::Viewport* self) {
		return self->m_scissor;
	}
	void DECL two_Viewport__set_scissor(two::Viewport* self, bool value) {
		self->m_scissor = value;
	}
	two::Colour* DECL two_Viewport__get_clear_colour(two::Viewport* self) {
		return &self->m_clear_colour;
	}
	void DECL two_Viewport__set_clear_colour(two::Viewport* self, two::Colour* value) {
		self->m_clear_colour = *value;
	}
	two::Shading DECL two_Viewport__get_shading(two::Viewport* self) {
		return self->m_shading;
	}
	void DECL two_Viewport__set_shading(two::Viewport* self, two::Shading value) {
		self->m_shading = value;
	}
	two::Lighting DECL two_Viewport__get_lighting(two::Viewport* self) {
		return self->m_lighting;
	}
	void DECL two_Viewport__set_lighting(two::Viewport* self, two::Lighting value) {
		self->m_lighting = value;
	}
	bool DECL two_Viewport__get_clustered(two::Viewport* self) {
		return self->m_clustered;
	}
	void DECL two_Viewport__set_clustered(two::Viewport* self, bool value) {
		self->m_clustered = value;
	}
	bool DECL two_Viewport__get_to_gamma(two::Viewport* self) {
		return self->m_to_gamma;
	}
	void DECL two_Viewport__set_to_gamma(two::Viewport* self, bool value) {
		self->m_to_gamma = value;
	}
	void DECL two_Viewport__destroy(two::Viewport* self) {
		delete self;
	}
	// RenderQuad
	two::Type* DECL two_RenderQuad__type() {
		return &two::type<two::RenderQuad>();
	}
	two::RenderQuad* DECL two_RenderQuad__construct_0() {
		return new two::RenderQuad();
	}
	two::RenderQuad* DECL two_RenderQuad__construct_1(const two::vec4* rect) {
		return new two::RenderQuad(*rect);
	}
	two::RenderQuad* DECL two_RenderQuad__construct_2(const two::vec4* crop, const two::vec4* dest) {
		return new two::RenderQuad(*crop, *dest);
	}
	two::RenderQuad* DECL two_RenderQuad__construct_3(const two::vec4* crop, const two::vec4* dest, bool fbo_flip) {
		return new two::RenderQuad(*crop, *dest, fbo_flip);
	}
	two::RenderQuad* DECL two_RenderQuad__construct_4(const two::vec4* crop, const two::vec4* dest, bool fbo_flip, bool relative) {
		return new two::RenderQuad(*crop, *dest, fbo_flip, relative);
	}
	two::vec4* DECL two_RenderQuad__get_source(two::RenderQuad* self) {
		return &self->m_source;
	}
	void DECL two_RenderQuad__set_source(two::RenderQuad* self, two::vec4* value) {
		self->m_source = *value;
	}
	two::vec4* DECL two_RenderQuad__get_dest(two::RenderQuad* self) {
		return &self->m_dest;
	}
	void DECL two_RenderQuad__set_dest(two::RenderQuad* self, two::vec4* value) {
		self->m_dest = *value;
	}
	bool DECL two_RenderQuad__get_fbo_flip(two::RenderQuad* self) {
		return self->m_fbo_flip;
	}
	void DECL two_RenderQuad__set_fbo_flip(two::RenderQuad* self, bool value) {
		self->m_fbo_flip = value;
	}
	bool DECL two_RenderQuad__get_relative(two::RenderQuad* self) {
		return self->m_relative;
	}
	void DECL two_RenderQuad__set_relative(two::RenderQuad* self, bool value) {
		self->m_relative = value;
	}
	void DECL two_RenderQuad__destroy(two::RenderQuad* self) {
		delete self;
	}
	// FrameBuffer
	two::Type* DECL two_FrameBuffer__type() {
		return &two::type<two::FrameBuffer>();
	}
	two::FrameBuffer* DECL two_FrameBuffer__construct_0() {
		return new two::FrameBuffer();
	}
	two::FrameBuffer* DECL two_FrameBuffer__construct_2(const two::uvec2* size, two::TextureFormat format) {
		return new two::FrameBuffer(*size, format);
	}
	two::FrameBuffer* DECL two_FrameBuffer__construct_3(const two::uvec2* size, two::TextureFormat format, uint64_t flags) {
		return new two::FrameBuffer(*size, format, flags);
	}
	bool DECL two_FrameBuffer_valid_0(two::FrameBuffer* self) {
		return self->valid();
	}
	two::uvec2* DECL two_FrameBuffer__get_size(two::FrameBuffer* self) {
		return &self->m_size;
	}
	void DECL two_FrameBuffer__set_size(two::FrameBuffer* self, two::uvec2* value) {
		self->m_size = *value;
	}
	two::Texture* DECL two_FrameBuffer__get_tex(two::FrameBuffer* self) {
		return &self->m_tex;
	}
	void DECL two_FrameBuffer__destroy(two::FrameBuffer* self) {
		delete self;
	}
	// SwapBuffer
	two::Type* DECL two_SwapBuffer__type() {
		return &two::type<two::SwapBuffer>();
	}
	two::SwapBuffer* DECL two_SwapBuffer__construct_0() {
		return new two::SwapBuffer();
	}
	void DECL two_SwapBuffer_create_2(two::SwapBuffer* self, const two::uvec2* size, two::TextureFormat color_format) {
		self->create(*size, color_format);
	}
	two::FrameBuffer* DECL two_SwapBuffer_swap_0(two::SwapBuffer* self) {
		return &self->swap();
	}
	two::FrameBuffer* DECL two_SwapBuffer_current_0(two::SwapBuffer* self) {
		return &self->current();
	}
	two::Texture* DECL two_SwapBuffer_last_0(two::SwapBuffer* self) {
		return &self->last();
	}
	two::FrameBuffer* DECL two_SwapBuffer__get_one(two::SwapBuffer* self) {
		return &self->m_one;
	}
	two::FrameBuffer* DECL two_SwapBuffer__get_two(two::SwapBuffer* self) {
		return &self->m_two;
	}
	void DECL two_SwapBuffer__destroy(two::SwapBuffer* self) {
		delete self;
	}
	// Cascade
	two::Type* DECL two_Cascade__type() {
		return &two::type<two::Cascade>();
	}
	two::Cascade* DECL two_Cascade__construct_0() {
		return new two::Cascade();
	}
	void DECL two_Cascade_create_2(two::Cascade* self, const two::uvec2* size, two::TextureFormat color_format) {
		self->create(*size, color_format);
	}
	two::FrameBuffer* DECL two_Cascade_level_1(two::Cascade* self, uint8_t index) {
		return &self->level(index);
	}
	two::Texture* DECL two_Cascade__get_texture(two::Cascade* self) {
		return &self->m_texture;
	}
	size_t DECL two_Cascade__get_numips(two::Cascade* self) {
		return self->m_num_mips;
	}
	void DECL two_Cascade__set_numips(two::Cascade* self, size_t value) {
		self->m_num_mips = value;
	}
	void DECL two_Cascade__destroy(two::Cascade* self) {
		delete self;
	}
	// SwapCascade
	two::Type* DECL two_SwapCascade__type() {
		return &two::type<two::SwapCascade>();
	}
	two::SwapCascade* DECL two_SwapCascade__construct_0() {
		return new two::SwapCascade();
	}
	void DECL two_SwapCascade_create_2(two::SwapCascade* self, const two::uvec2* size, two::TextureFormat color_format) {
		self->create(*size, color_format);
	}
	two::Cascade* DECL two_SwapCascade_swap_0(two::SwapCascade* self) {
		return &self->swap();
	}
	two::Cascade* DECL two_SwapCascade_last_0(two::SwapCascade* self) {
		return &self->last();
	}
	two::Cascade* DECL two_SwapCascade__get_one(two::SwapCascade* self) {
		return &self->m_one;
	}
	two::Cascade* DECL two_SwapCascade__get_two(two::SwapCascade* self) {
		return &self->m_two;
	}
	void DECL two_SwapCascade__destroy(two::SwapCascade* self) {
		delete self;
	}
	// RenderTarget
	two::Type* DECL two_RenderTarget__type() {
		return &two::type<two::RenderTarget>();
	}
	two::FrameBuffer* DECL two_RenderTarget__get_backbuffer(two::RenderTarget* self) {
		return &self->m_backbuffer;
	}
	two::MSAA DECL two_RenderTarget__get_msaa(two::RenderTarget* self) {
		return self->m_msaa;
	}
	void DECL two_RenderTarget__set_msaa(two::RenderTarget* self, two::MSAA value) {
		self->m_msaa = value;
	}
	bool DECL two_RenderTarget__get_mrt(two::RenderTarget* self) {
		return self->m_mrt;
	}
	void DECL two_RenderTarget__set_mrt(two::RenderTarget* self, bool value) {
		self->m_mrt = value;
	}
	two::Texture* DECL two_RenderTarget__get_depth(two::RenderTarget* self) {
		return &self->m_depth;
	}
	two::Texture* DECL two_RenderTarget__get_diffuse(two::RenderTarget* self) {
		return &self->m_diffuse;
	}
	two::Texture* DECL two_RenderTarget__get_specular(two::RenderTarget* self) {
		return &self->m_specular;
	}
	two::Texture* DECL two_RenderTarget__get_normal_rough(two::RenderTarget* self) {
		return &self->m_normal_rough;
	}
	two::Texture* DECL two_RenderTarget__get_sss(two::RenderTarget* self) {
		return &self->m_sss;
	}
	two::SwapBuffer* DECL two_RenderTarget__get_ping_pong(two::RenderTarget* self) {
		return &self->m_ping_pong;
	}
	two::SwapBuffer* DECL two_RenderTarget__get_post(two::RenderTarget* self) {
		return &self->m_post;
	}
	two::Cascade* DECL two_RenderTarget__get_cascade(two::RenderTarget* self) {
		return &self->m_cascade;
	}
	two::SwapCascade* DECL two_RenderTarget__get_swap_cascade(two::RenderTarget* self) {
		return &self->m_swap_cascade;
	}
	bool DECL two_RenderTarget__get_deferred(two::RenderTarget* self) {
		return self->m_deferred;
	}
	void DECL two_RenderTarget__set_deferred(two::RenderTarget* self, bool value) {
		self->m_deferred = value;
	}
	void DECL two_RenderTarget__destroy(two::RenderTarget* self) {
		delete self;
	}
	// Sun
	two::Type* DECL two_Sun__type() {
		return &two::type<two::Sun>();
	}
	two::Sun* DECL two_Sun__construct_0() {
		return new two::Sun();
	}
	float DECL two_Sun__get_azimuth(two::Sun* self) {
		return self->azimuth;
	}
	void DECL two_Sun__set_azimuth(two::Sun* self, float value) {
		self->azimuth = value;
	}
	float DECL two_Sun__get_elevation(two::Sun* self) {
		return self->elevation;
	}
	void DECL two_Sun__set_elevation(two::Sun* self, float value) {
		self->elevation = value;
	}
	two::Colour* DECL two_Sun__get_colour(two::Sun* self) {
		return &self->m_colour;
	}
	void DECL two_Sun__set_colour(two::Sun* self, two::Colour* value) {
		self->m_colour = *value;
	}
	float DECL two_Sun__get_intensity(two::Sun* self) {
		return self->m_intensity;
	}
	void DECL two_Sun__set_intensity(two::Sun* self, float value) {
		self->m_intensity = value;
	}
	void DECL two_Sun__destroy(two::Sun* self) {
		delete self;
	}
	// Radiance
	two::Type* DECL two_Radiance__type() {
		return &two::type<two::Radiance>();
	}
	two::Radiance* DECL two_Radiance__construct_0() {
		return new two::Radiance();
	}
	two::Colour* DECL two_Radiance__get_colour(two::Radiance* self) {
		return &self->m_colour;
	}
	void DECL two_Radiance__set_colour(two::Radiance* self, two::Colour* value) {
		self->m_colour = *value;
	}
	float DECL two_Radiance__get_energy(two::Radiance* self) {
		return self->m_energy;
	}
	void DECL two_Radiance__set_energy(two::Radiance* self, float value) {
		self->m_energy = value;
	}
	two::Colour* DECL two_Radiance__get_ambient(two::Radiance* self) {
		return &self->m_ambient;
	}
	void DECL two_Radiance__set_ambient(two::Radiance* self, two::Colour* value) {
		self->m_ambient = *value;
	}
	two::Texture* DECL two_Radiance__get_texture(two::Radiance* self) {
		return self->m_texture;
	}
	void DECL two_Radiance__set_texture(two::Radiance* self, two::Texture* value) {
		self->m_texture = value;
	}
	two::Texture* DECL two_Radiance__get_filtered(two::Radiance* self) {
		return self->m_filtered;
	}
	void DECL two_Radiance__set_filtered(two::Radiance* self, two::Texture* value) {
		self->m_filtered = value;
	}
	bool DECL two_Radiance__get_filter(two::Radiance* self) {
		return self->m_filter;
	}
	void DECL two_Radiance__set_filter(two::Radiance* self, bool value) {
		self->m_filter = value;
	}
	void DECL two_Radiance__destroy(two::Radiance* self) {
		delete self;
	}
	// Background
	two::Type* DECL two_Background__type() {
		return &two::type<two::Background>();
	}
	two::Background* DECL two_Background__construct_0() {
		return new two::Background();
	}
	two::BackgroundMode DECL two_Background__get_mode(two::Background* self) {
		return self->m_mode;
	}
	void DECL two_Background__set_mode(two::Background* self, two::BackgroundMode value) {
		self->m_mode = value;
	}
	two::Colour* DECL two_Background__get_colour(two::Background* self) {
		return &self->m_colour;
	}
	void DECL two_Background__set_colour(two::Background* self, two::Colour* value) {
		self->m_colour = *value;
	}
	two::Program* DECL two_Background__get_custoprogram(two::Background* self) {
		return self->m_custom_program;
	}
	void DECL two_Background__set_custoprogram(two::Background* self, two::Program* value) {
		self->m_custom_program = value;
	}
	two::Texture* DECL two_Background__get_texture(two::Background* self) {
		return self->m_texture;
	}
	void DECL two_Background__set_texture(two::Background* self, two::Texture* value) {
		self->m_texture = value;
	}
	void DECL two_Background__destroy(two::Background* self) {
		delete self;
	}
	// Skylight
	two::Type* DECL two_Skylight__type() {
		return &two::type<two::Skylight>();
	}
	two::Skylight* DECL two_Skylight__construct_0() {
		return new two::Skylight();
	}
	bool DECL two_Skylight__get_enabled(two::Skylight* self) {
		return self->m_enabled;
	}
	void DECL two_Skylight__set_enabled(two::Skylight* self, bool value) {
		self->m_enabled = value;
	}
	float DECL two_Skylight__get_intensity(two::Skylight* self) {
		return self->m_intensity;
	}
	void DECL two_Skylight__set_intensity(two::Skylight* self, float value) {
		self->m_intensity = value;
	}
	two::vec3* DECL two_Skylight__get_position(two::Skylight* self) {
		return &self->m_position;
	}
	void DECL two_Skylight__set_position(two::Skylight* self, two::vec3* value) {
		self->m_position = *value;
	}
	two::vec3* DECL two_Skylight__get_direction(two::Skylight* self) {
		return &self->m_direction;
	}
	void DECL two_Skylight__set_direction(two::Skylight* self, two::vec3* value) {
		self->m_direction = *value;
	}
	two::Colour* DECL two_Skylight__get_color(two::Skylight* self) {
		return &self->m_color;
	}
	void DECL two_Skylight__set_color(two::Skylight* self, two::Colour* value) {
		self->m_color = *value;
	}
	two::Colour* DECL two_Skylight__get_ground(two::Skylight* self) {
		return &self->m_ground;
	}
	void DECL two_Skylight__set_ground(two::Skylight* self, two::Colour* value) {
		self->m_ground = *value;
	}
	void DECL two_Skylight__destroy(two::Skylight* self) {
		delete self;
	}
	// Fog
	two::Type* DECL two_Fog__type() {
		return &two::type<two::Fog>();
	}
	two::Fog* DECL two_Fog__construct_0() {
		return new two::Fog();
	}
	bool DECL two_Fog__get_enabled(two::Fog* self) {
		return self->m_enabled;
	}
	void DECL two_Fog__set_enabled(two::Fog* self, bool value) {
		self->m_enabled = value;
	}
	float DECL two_Fog__get_density(two::Fog* self) {
		return self->m_density;
	}
	void DECL two_Fog__set_density(two::Fog* self, float value) {
		self->m_density = value;
	}
	two::Colour* DECL two_Fog__get_colour(two::Fog* self) {
		return &self->m_colour;
	}
	void DECL two_Fog__set_colour(two::Fog* self, two::Colour* value) {
		self->m_colour = *value;
	}
	bool DECL two_Fog__get_depth(two::Fog* self) {
		return self->m_depth;
	}
	void DECL two_Fog__set_depth(two::Fog* self, bool value) {
		self->m_depth = value;
	}
	float DECL two_Fog__get_depth_begin(two::Fog* self) {
		return self->m_depth_begin;
	}
	void DECL two_Fog__set_depth_begin(two::Fog* self, float value) {
		self->m_depth_begin = value;
	}
	float DECL two_Fog__get_depth_end(two::Fog* self) {
		return self->m_depth_end;
	}
	void DECL two_Fog__set_depth_end(two::Fog* self, float value) {
		self->m_depth_end = value;
	}
	float DECL two_Fog__get_depth_curve(two::Fog* self) {
		return self->m_depth_curve;
	}
	void DECL two_Fog__set_depth_curve(two::Fog* self, float value) {
		self->m_depth_curve = value;
	}
	bool DECL two_Fog__get_height(two::Fog* self) {
		return self->m_height;
	}
	void DECL two_Fog__set_height(two::Fog* self, bool value) {
		self->m_height = value;
	}
	float DECL two_Fog__get_height_min(two::Fog* self) {
		return self->m_height_min;
	}
	void DECL two_Fog__set_height_min(two::Fog* self, float value) {
		self->m_height_min = value;
	}
	float DECL two_Fog__get_height_max(two::Fog* self) {
		return self->m_height_max;
	}
	void DECL two_Fog__set_height_max(two::Fog* self, float value) {
		self->m_height_max = value;
	}
	float DECL two_Fog__get_height_curve(two::Fog* self) {
		return self->m_height_curve;
	}
	void DECL two_Fog__set_height_curve(two::Fog* self, float value) {
		self->m_height_curve = value;
	}
	bool DECL two_Fog__get_transmit(two::Fog* self) {
		return self->m_transmit;
	}
	void DECL two_Fog__set_transmit(two::Fog* self, bool value) {
		self->m_transmit = value;
	}
	float DECL two_Fog__get_transmit_curve(two::Fog* self) {
		return self->m_transmit_curve;
	}
	void DECL two_Fog__set_transmit_curve(two::Fog* self, float value) {
		self->m_transmit_curve = value;
	}
	void DECL two_Fog__destroy(two::Fog* self) {
		delete self;
	}
	// Zone
	two::Type* DECL two_Zone__type() {
		return &two::type<two::Zone>();
	}
	two::Zone* DECL two_Zone__construct_0() {
		return new two::Zone();
	}
	two::Background* DECL two_Zone__get_background(two::Zone* self) {
		return &self->m_background;
	}
	void DECL two_Zone__set_background(two::Zone* self, two::Background* value) {
		self->m_background = *value;
	}
	two::Radiance* DECL two_Zone__get_radiance(two::Zone* self) {
		return &self->m_radiance;
	}
	void DECL two_Zone__set_radiance(two::Zone* self, two::Radiance* value) {
		self->m_radiance = *value;
	}
	two::Sun* DECL two_Zone__get_sun(two::Zone* self) {
		return &self->m_sun;
	}
	void DECL two_Zone__set_sun(two::Zone* self, two::Sun* value) {
		self->m_sun = *value;
	}
	two::Skylight* DECL two_Zone__get_skylight(two::Zone* self) {
		return &self->m_skylight;
	}
	void DECL two_Zone__set_skylight(two::Zone* self, two::Skylight* value) {
		self->m_skylight = *value;
	}
	two::Fog* DECL two_Zone__get_fog(two::Zone* self) {
		return &self->m_fog;
	}
	void DECL two_Zone__set_fog(two::Zone* self, two::Fog* value) {
		self->m_fog = *value;
	}
	void DECL two_Zone__destroy(two::Zone* self) {
		delete self;
	}
	// Scene
	two::Type* DECL two_Scene__type() {
		return &two::type<two::Scene>();
	}
	two::Scene* DECL two_Scene__construct_1(two::GfxSystem* gfx) {
		return new two::Scene(*gfx);
	}
	two::Gnode* DECL two_Scene_begin_0(two::Scene* self) {
		return &self->begin();
	}
	void DECL two_Scene_update_0(two::Scene* self) {
		self->update();
	}
	two::TPool<two::Node3>* DECL two_Scene_nodes_0(two::Scene* self) {
		return &two::gfx::nodes(*self);
	}
	two::TPool<two::Item>* DECL two_Scene_items_0(two::Scene* self) {
		return &two::gfx::items(*self);
	}
	two::TPool<two::Batch>* DECL two_Scene_batches_0(two::Scene* self) {
		return &two::gfx::batches(*self);
	}
	two::TPool<two::Direct>* DECL two_Scene_directs_0(two::Scene* self) {
		return &two::gfx::directs(*self);
	}
	two::TPool<two::Mime>* DECL two_Scene_mimes_0(two::Scene* self) {
		return &two::gfx::mimes(*self);
	}
	two::TPool<two::Light>* DECL two_Scene_lights_0(two::Scene* self) {
		return &two::gfx::lights(*self);
	}
	two::TPool<two::Flare>* DECL two_Scene_flares_0(two::Scene* self) {
		return &two::gfx::flares(*self);
	}
	uint32_t DECL two_Scene__get_index(two::Scene* self) {
		return self->m_index;
	}
	void DECL two_Scene__set_index(two::Scene* self, uint32_t value) {
		self->m_index = value;
	}
	two::Gnode* DECL two_Scene__get_graph(two::Scene* self) {
		return &self->m_graph;
	}
	two::Node3* DECL two_Scene__get_root_node(two::Scene* self) {
		return &self->m_root_node;
	}
	two::Zone* DECL two_Scene__get_env(two::Scene* self) {
		return &self->m_env;
	}
	void DECL two_Scene__set_env(two::Scene* self, two::Zone* value) {
		self->m_env = *value;
	}
	two::Ref* DECL two_Scene__get_user(two::Scene* self) {
		return &self->m_user;
	}
	void DECL two_Scene__set_user(two::Scene* self, two::Ref* value) {
		self->m_user = *value;
	}
	void DECL two_Scene__destroy(two::Scene* self) {
		delete self;
	}
	// BlockSky
	two::Type* DECL two_BlockSky__type() {
		return &two::type<two::BlockSky>();
	}
	void DECL two_BlockSky__destroy(two::BlockSky* self) {
		delete self;
	}
	two::mat4* DECL two_bxidentity_0() {
		static two::mat4 temp;
		return (temp = two::bxidentity(), &temp);
	}
	two::mat4* DECL two_bxinverse_1(const two::mat4* mat) {
		static two::mat4 temp;
		return (temp = two::bxinverse(*mat), &temp);
	}
	two::mat4* DECL two_bxSRT_3(const two::vec3* scale, const two::vec3* rot, const two::vec3* trans) {
		static two::mat4 temp;
		return (temp = two::bxSRT(*scale, *rot, *trans), &temp);
	}
	two::mat4* DECL two_bxscale_1(const two::vec3* scale) {
		static two::mat4 temp;
		return (temp = two::bxscale(*scale), &temp);
	}
	two::mat4* DECL two_bxrotation_1(const two::quat* rot) {
		static two::mat4 temp;
		return (temp = two::bxrotation(*rot), &temp);
	}
	two::mat4* DECL two_bxtranslation_1(const two::vec3* vec) {
		static two::mat4 temp;
		return (temp = two::bxtranslation(*vec), &temp);
	}
	two::mat4* DECL two_bxmul_2(const two::mat4* lhs, const two::mat4* rhs) {
		static two::mat4 temp;
		return (temp = two::bxmul(*lhs, *rhs), &temp);
	}
	two::vec3* DECL two_bxmulh_2(const two::mat4* mat, const two::vec3* vec) {
		static two::vec3 temp;
		return (temp = two::bxmulh(*mat, *vec), &temp);
	}
	two::mat4* DECL two_bxlookat_2(const two::vec3* eye, const two::vec3* at) {
		static two::mat4 temp;
		return (temp = two::bxlookat(*eye, *at), &temp);
	}
	two::mat4* DECL two_bxlookat_3(const two::vec3* eye, const two::vec3* at, const two::vec3* up) {
		static two::mat4 temp;
		return (temp = two::bxlookat(*eye, *at, *up), &temp);
	}
	void DECL two_bxlookat_4(two::mat4* result, const two::vec3* eye, const two::vec3* at, const two::vec3* up) {
		two::bxlookat(*result, *eye, *at, *up);
	}
	two::mat4* DECL two_bxproj_5(float fov, float aspect, float near, float far, bool oglNdc) {
		static two::mat4 temp;
		return (temp = two::bxproj(fov, aspect, near, far, oglNdc), &temp);
	}
	two::mat4* DECL two_bxortho_5(const two::vec4* rect, float near, float far, float offset, bool oglNdc) {
		static two::mat4 temp;
		return (temp = two::bxortho(*rect, near, far, offset, oglNdc), &temp);
	}
	two::mat4* DECL two_bxortho_8(float left, float right, float bottom, float top, float near, float far, float offset, bool oglNdc) {
		static two::mat4 temp;
		return (temp = two::bxortho(left, right, bottom, top, near, far, offset, oglNdc), &temp);
	}
	two::mat4* DECL two_bxTRS_3(const two::vec3* scale, const two::quat* rot, const two::vec3* trans) {
		static two::mat4 temp;
		return (temp = two::bxTRS(*scale, *rot, *trans), &temp);
	}
	two::MirrorCamera* DECL two_mirror_camera_2(const two::Camera* sourcecam, two::Node3* node) {
		static two::MirrorCamera temp;
		return (temp = two::mirror_camera(*sourcecam, *node), &temp);
	}
	two::MirrorCamera* DECL two_mirror_camera_3(const two::Camera* sourcecam, two::Node3* node, float clipBias) {
		static two::MirrorCamera temp;
		return (temp = two::mirror_camera(*sourcecam, *node, clipBias), &temp);
	}
	void DECL two_gfx_setup_pipeline_minimal_1(two::GfxSystem* gfx) {
		two::gfx::setup_pipeline_minimal(*gfx);
	}
	two::Gnode* DECL two_gfx_node_1(two::Gnode* parent) {
		return &two::gfx::node(*parent);
	}
	two::Gnode* DECL two_gfx_node_2(two::Gnode* parent, const two::vec3* position) {
		return &two::gfx::node(*parent, *position);
	}
	two::Gnode* DECL two_gfx_node_3(two::Gnode* parent, const two::vec3* position, const two::quat* rotation) {
		return &two::gfx::node(*parent, *position, *rotation);
	}
	two::Gnode* DECL two_gfx_node_4(two::Gnode* parent, const two::vec3* position, const two::quat* rotation, const two::vec3* scale) {
		return &two::gfx::node(*parent, *position, *rotation, *scale);
	}
	two::Item* DECL two_gfx_shape_3(two::Gnode* parent, const two::Shape* shape, const two::Symbol* symbol) {
		return &two::gfx::shape(*parent, *shape, *symbol);
	}
	two::Item* DECL two_gfx_shape_4(two::Gnode* parent, const two::Shape* shape, const two::Symbol* symbol, uint32_t flags) {
		return &two::gfx::shape(*parent, *shape, *symbol, flags);
	}
	two::Item* DECL two_gfx_shape_5(two::Gnode* parent, const two::Shape* shape, const two::Symbol* symbol, uint32_t flags, two::Material* material) {
		return &two::gfx::shape(*parent, *shape, *symbol, flags, material);
	}
	void DECL two_gfx_draw_3(two::Gnode* parent, const two::Shape* shape, const two::Symbol* symbol) {
		two::gfx::draw(*parent, *shape, *symbol);
	}
	void DECL two_gfx_draw_4(two::Gnode* parent, const two::Shape* shape, const two::Symbol* symbol, uint32_t flags) {
		two::gfx::draw(*parent, *shape, *symbol, flags);
	}
	two::Item* DECL two_gfx_sprite_3(two::Gnode* parent, const two::Image256* image, const two::vec2* size) {
		return &two::gfx::sprite(*parent, *image, *size);
	}
	two::Item* DECL two_gfx_sprite_4(two::Gnode* parent, const two::Image256* image, const two::vec2* size, uint32_t flags) {
		return &two::gfx::sprite(*parent, *image, *size, flags);
	}
	two::Item* DECL two_gfx_sprite_5(two::Gnode* parent, const two::Image256* image, const two::vec2* size, uint32_t flags, two::Material* material) {
		return &two::gfx::sprite(*parent, *image, *size, flags, material);
	}
	two::Item* DECL two_gfx_item_2(two::Gnode* parent, const two::Model* model) {
		return &two::gfx::item(*parent, *model);
	}
	two::Item* DECL two_gfx_item_3(two::Gnode* parent, const two::Model* model, uint32_t flags) {
		return &two::gfx::item(*parent, *model, flags);
	}
	two::Item* DECL two_gfx_item_4(two::Gnode* parent, const two::Model* model, uint32_t flags, two::Material* material) {
		return &two::gfx::item(*parent, *model, flags, material);
	}
	two::Batch* DECL two_gfx_batch_3(two::Gnode* parent, two::Item* item, uint16_t stride) {
		return &two::gfx::batch(*parent, *item, stride);
	}
	two::Batch* DECL two_gfx_instances_2(two::Gnode* parent, two::Item* item) {
		return &two::gfx::instances(*parent, *item);
	}
	two::Batch* DECL two_gfx_instances_3(two::Gnode* parent, two::Item* item, float* transforms, int transforms_size) {
		return &two::gfx::instances(*parent, *item, { (two::mat4*)transforms, transforms_size / (sizeof(two::mat4) / sizeof(float)) });
	}
	void DECL two_gfx_prefab_2(two::Gnode* parent, const two::Prefab* prefab) {
		two::gfx::prefab(*parent, *prefab);
	}
	void DECL two_gfx_prefab_3(two::Gnode* parent, const two::Prefab* prefab, bool transform) {
		two::gfx::prefab(*parent, *prefab, transform);
	}
	void DECL two_gfx_prefab_4(two::Gnode* parent, const two::Prefab* prefab, bool transform, uint32_t flags) {
		two::gfx::prefab(*parent, *prefab, transform, flags);
	}
	void DECL two_gfx_prefab_5(two::Gnode* parent, const two::Prefab* prefab, bool transform, uint32_t flags, two::Material* material) {
		two::gfx::prefab(*parent, *prefab, transform, flags, material);
	}
	two::Item* DECL two_gfx_model_2(two::Gnode* parent, const char* name) {
		return two::gfx::model(*parent, name);
	}
	two::Item* DECL two_gfx_model_3(two::Gnode* parent, const char* name, uint32_t flags) {
		return two::gfx::model(*parent, name, flags);
	}
	two::Item* DECL two_gfx_model_4(two::Gnode* parent, const char* name, uint32_t flags, two::Material* material) {
		return two::gfx::model(*parent, name, flags, material);
	}
	two::Mime* DECL two_gfx_animated_2(two::Gnode* parent, two::Item* item) {
		return &two::gfx::animated(*parent, *item);
	}
	two::Flare* DECL two_gfx_flows_2(two::Gnode* parent, const two::Flow* emitter) {
		return &two::gfx::flows(*parent, *emitter);
	}
	two::Flare* DECL two_gfx_flows_3(two::Gnode* parent, const two::Flow* emitter, uint32_t flags) {
		return &two::gfx::flows(*parent, *emitter, flags);
	}
	two::Light* DECL two_gfx_light_4(two::Gnode* parent, two::LightType type, bool shadows, two::Colour* colour) {
		return &two::gfx::light(*parent, type, shadows, *colour);
	}
	two::Light* DECL two_gfx_light_5(two::Gnode* parent, two::LightType type, bool shadows, two::Colour* colour, float range) {
		return &two::gfx::light(*parent, type, shadows, *colour, range);
	}
	two::Light* DECL two_gfx_light_6(two::Gnode* parent, two::LightType type, bool shadows, two::Colour* colour, float range, float attenuation) {
		return &two::gfx::light(*parent, type, shadows, *colour, range, attenuation);
	}
	two::Light* DECL two_gfx_sun_light_3(two::Gnode* parent, float azimuth, float elevation) {
		return &two::gfx::sun_light(*parent, azimuth, elevation);
	}
	void DECL two_gfx_radiance_3(two::Gnode* parent, const char* texture, two::BackgroundMode background) {
		two::gfx::radiance(*parent, texture, background);
	}
	two::Light* DECL two_gfx_direct_light_node_2(two::Gnode* parent, const two::vec3* direction) {
		return &two::gfx::direct_light_node(*parent, *direction);
	}
	two::Material* DECL two_gfx_solid_material_3(two::GfxSystem* gfx, const char* name, const two::Colour* colour) {
		return &two::gfx::solid_material(*gfx, name, *colour);
	}
	two::Material* DECL two_gfx_pbr_material_3(two::GfxSystem* gfx, const char* name, const two::Colour* albedo) {
		return &two::gfx::pbr_material(*gfx, name, *albedo);
	}
	two::Material* DECL two_gfx_pbr_material_4(two::GfxSystem* gfx, const char* name, const two::Colour* albedo, float metallic) {
		return &two::gfx::pbr_material(*gfx, name, *albedo, metallic);
	}
	two::Material* DECL two_gfx_pbr_material_5(two::GfxSystem* gfx, const char* name, const two::Colour* albedo, float metallic, float roughness) {
		return &two::gfx::pbr_material(*gfx, name, *albedo, metallic, roughness);
	}
	two::Model* DECL two_gfx_model_suzanne_1(two::GfxSystem* gfx) {
		return &two::gfx::model_suzanne(*gfx);
	}
	void DECL two_pass_clear_fbo_4(two::GfxSystem* gfx, two::Render* render, two::FrameBuffer* fbo, const two::Colour* colour) {
		two::pass_clear_fbo(*gfx, *render, *fbo, *colour);
	}
	void DECL two_pass_clear_fbo_5(two::GfxSystem* gfx, two::Render* render, two::FrameBuffer* fbo, const two::Colour* colour, float depth) {
		two::pass_clear_fbo(*gfx, *render, *fbo, *colour, depth);
	}
	void DECL two_pass_clear_2(two::GfxSystem* gfx, two::Render* render) {
		two::pass_clear(*gfx, *render);
	}
	void DECL two_pass_gclear_2(two::GfxSystem* gfx, two::Render* render) {
		two::pass_gclear(*gfx, *render);
	}
	void DECL two_pass_depth_2(two::GfxSystem* gfx, two::Render* render) {
		two::pass_depth(*gfx, *render);
	}
	void DECL two_pass_background_2(two::GfxSystem* gfx, two::Render* render) {
		two::pass_background(*gfx, *render);
	}
	void DECL two_pass_solid_2(two::GfxSystem* gfx, two::Render* render) {
		two::pass_solid(*gfx, *render);
	}
	void DECL two_pass_flip_2(two::GfxSystem* gfx, two::Render* render) {
		two::pass_flip(*gfx, *render);
	}
	void DECL two_render_minimal_2(two::GfxSystem* gfx, two::Render* render) {
		two::render_minimal(*gfx, *render);
	}
	void DECL two_render_solid_2(two::GfxSystem* gfx, two::Render* render) {
		two::render_solid(*gfx, *render);
	}
	void DECL two_render_clear_2(two::GfxSystem* gfx, two::Render* render) {
		two::render_clear(*gfx, *render);
	}
	// AnimTarget
	two::AnimTarget DECL two_AnimTarget_Position() {
		return two::AnimTarget::Position;
	}
	two::AnimTarget DECL two_AnimTarget_Rotation() {
		return two::AnimTarget::Rotation;
	}
	two::AnimTarget DECL two_AnimTarget_Scale() {
		return two::AnimTarget::Scale;
	}
	two::AnimTarget DECL two_AnimTarget_Weights() {
		return two::AnimTarget::Weights;
	}
	two::AnimTarget DECL two_AnimTarget_Count() {
		return two::AnimTarget::Count;
	}
	// Interpolation
	two::Interpolation DECL two_Interpolation_Nearest() {
		return two::Interpolation::Nearest;
	}
	two::Interpolation DECL two_Interpolation_Linear() {
		return two::Interpolation::Linear;
	}
	two::Interpolation DECL two_Interpolation_Cubic() {
		return two::Interpolation::Cubic;
	}
	// TextureHint
	two::TextureHint DECL two_TextureHint_Black() {
		return two::TextureHint::Black;
	}
	two::TextureHint DECL two_TextureHint_White() {
		return two::TextureHint::White;
	}
	two::TextureHint DECL two_TextureHint_Normal() {
		return two::TextureHint::Normal;
	}
	// TextureFormat
	two::TextureFormat DECL two_TextureFormat_None() {
		return two::TextureFormat::None;
	}
	two::TextureFormat DECL two_TextureFormat_R8() {
		return two::TextureFormat::R8;
	}
	two::TextureFormat DECL two_TextureFormat_R16F() {
		return two::TextureFormat::R16F;
	}
	two::TextureFormat DECL two_TextureFormat_R32U() {
		return two::TextureFormat::R32U;
	}
	two::TextureFormat DECL two_TextureFormat_R32F() {
		return two::TextureFormat::R32F;
	}
	two::TextureFormat DECL two_TextureFormat_RG8() {
		return two::TextureFormat::RG8;
	}
	two::TextureFormat DECL two_TextureFormat_RG16F() {
		return two::TextureFormat::RG16F;
	}
	two::TextureFormat DECL two_TextureFormat_RG32F() {
		return two::TextureFormat::RG32F;
	}
	two::TextureFormat DECL two_TextureFormat_RGB8() {
		return two::TextureFormat::RGB8;
	}
	two::TextureFormat DECL two_TextureFormat_BGRA8() {
		return two::TextureFormat::BGRA8;
	}
	two::TextureFormat DECL two_TextureFormat_RGBA8() {
		return two::TextureFormat::RGBA8;
	}
	two::TextureFormat DECL two_TextureFormat_RGB10A2() {
		return two::TextureFormat::RGB10A2;
	}
	two::TextureFormat DECL two_TextureFormat_RGBA16F() {
		return two::TextureFormat::RGBA16F;
	}
	two::TextureFormat DECL two_TextureFormat_RGBA32F() {
		return two::TextureFormat::RGBA32F;
	}
	two::TextureFormat DECL two_TextureFormat_D16() {
		return two::TextureFormat::D16;
	}
	two::TextureFormat DECL two_TextureFormat_D24() {
		return two::TextureFormat::D24;
	}
	two::TextureFormat DECL two_TextureFormat_D24S8() {
		return two::TextureFormat::D24S8;
	}
	two::TextureFormat DECL two_TextureFormat_D32() {
		return two::TextureFormat::D32;
	}
	two::TextureFormat DECL two_TextureFormat_D32F() {
		return two::TextureFormat::D32F;
	}
	two::TextureFormat DECL two_TextureFormat_Count() {
		return two::TextureFormat::Count;
	}
	// ShaderType
	two::ShaderType DECL two_ShaderType_Compute() {
		return two::ShaderType::Compute;
	}
	two::ShaderType DECL two_ShaderType_Fragment() {
		return two::ShaderType::Fragment;
	}
	two::ShaderType DECL two_ShaderType_Geometry() {
		return two::ShaderType::Geometry;
	}
	two::ShaderType DECL two_ShaderType_Vertex() {
		return two::ShaderType::Vertex;
	}
	two::ShaderType DECL two_ShaderType_Count() {
		return two::ShaderType::Count;
	}
	// PassType
	two::PassType DECL two_PassType_VoxelGI() {
		return two::PassType::VoxelGI;
	}
	two::PassType DECL two_PassType_Lightmap() {
		return two::PassType::Lightmap;
	}
	two::PassType DECL two_PassType_Shadowmap() {
		return two::PassType::Shadowmap;
	}
	two::PassType DECL two_PassType_Probes() {
		return two::PassType::Probes;
	}
	two::PassType DECL two_PassType_Clear() {
		return two::PassType::Clear;
	}
	two::PassType DECL two_PassType_Depth() {
		return two::PassType::Depth;
	}
	two::PassType DECL two_PassType_Normals() {
		return two::PassType::Normals;
	}
	two::PassType DECL two_PassType_Shadow() {
		return two::PassType::Shadow;
	}
	two::PassType DECL two_PassType_Geometry() {
		return two::PassType::Geometry;
	}
	two::PassType DECL two_PassType_Lights() {
		return two::PassType::Lights;
	}
	two::PassType DECL two_PassType_Opaque() {
		return two::PassType::Opaque;
	}
	two::PassType DECL two_PassType_Background() {
		return two::PassType::Background;
	}
	two::PassType DECL two_PassType_Particles() {
		return two::PassType::Particles;
	}
	two::PassType DECL two_PassType_Alpha() {
		return two::PassType::Alpha;
	}
	two::PassType DECL two_PassType_Solid() {
		return two::PassType::Solid;
	}
	two::PassType DECL two_PassType_Effects() {
		return two::PassType::Effects;
	}
	two::PassType DECL two_PassType_PostProcess() {
		return two::PassType::PostProcess;
	}
	two::PassType DECL two_PassType_Flip() {
		return two::PassType::Flip;
	}
	two::PassType DECL two_PassType_Count() {
		return two::PassType::Count;
	}
	// MaterialBlock
	two::MaterialBlock DECL two_MaterialBlock_Base() {
		return two::MaterialBlock::Base;
	}
	two::MaterialBlock DECL two_MaterialBlock_Alpha() {
		return two::MaterialBlock::Alpha;
	}
	two::MaterialBlock DECL two_MaterialBlock_Solid() {
		return two::MaterialBlock::Solid;
	}
	two::MaterialBlock DECL two_MaterialBlock_Point() {
		return two::MaterialBlock::Point;
	}
	two::MaterialBlock DECL two_MaterialBlock_Line() {
		return two::MaterialBlock::Line;
	}
	two::MaterialBlock DECL two_MaterialBlock_Lit() {
		return two::MaterialBlock::Lit;
	}
	two::MaterialBlock DECL two_MaterialBlock_Pbr() {
		return two::MaterialBlock::Pbr;
	}
	two::MaterialBlock DECL two_MaterialBlock_Phong() {
		return two::MaterialBlock::Phong;
	}
	two::MaterialBlock DECL two_MaterialBlock_Fresnel() {
		return two::MaterialBlock::Fresnel;
	}
	two::MaterialBlock DECL two_MaterialBlock_User() {
		return two::MaterialBlock::User;
	}
	two::MaterialBlock DECL two_MaterialBlock_Count() {
		return two::MaterialBlock::Count;
	}
	// TextureSampler
	two::TextureSampler DECL two_TextureSampler_Source0() {
		return two::TextureSampler::Source0;
	}
	two::TextureSampler DECL two_TextureSampler_Source1() {
		return two::TextureSampler::Source1;
	}
	two::TextureSampler DECL two_TextureSampler_Source2() {
		return two::TextureSampler::Source2;
	}
	two::TextureSampler DECL two_TextureSampler_Source3() {
		return two::TextureSampler::Source3;
	}
	two::TextureSampler DECL two_TextureSampler_SourceDepth() {
		return two::TextureSampler::SourceDepth;
	}
	two::TextureSampler DECL two_TextureSampler_Color() {
		return two::TextureSampler::Color;
	}
	two::TextureSampler DECL two_TextureSampler_Albedo() {
		return two::TextureSampler::Albedo;
	}
	two::TextureSampler DECL two_TextureSampler_Diffuse() {
		return two::TextureSampler::Diffuse;
	}
	two::TextureSampler DECL two_TextureSampler_Alpha() {
		return two::TextureSampler::Alpha;
	}
	two::TextureSampler DECL two_TextureSampler_Metallic() {
		return two::TextureSampler::Metallic;
	}
	two::TextureSampler DECL two_TextureSampler_Specular() {
		return two::TextureSampler::Specular;
	}
	two::TextureSampler DECL two_TextureSampler_Roughness() {
		return two::TextureSampler::Roughness;
	}
	two::TextureSampler DECL two_TextureSampler_Shininess() {
		return two::TextureSampler::Shininess;
	}
	two::TextureSampler DECL two_TextureSampler_Emissive() {
		return two::TextureSampler::Emissive;
	}
	two::TextureSampler DECL two_TextureSampler_Normal() {
		return two::TextureSampler::Normal;
	}
	two::TextureSampler DECL two_TextureSampler_AO() {
		return two::TextureSampler::AO;
	}
	two::TextureSampler DECL two_TextureSampler_Displace() {
		return two::TextureSampler::Displace;
	}
	two::TextureSampler DECL two_TextureSampler_Depth() {
		return two::TextureSampler::Depth;
	}
	two::TextureSampler DECL two_TextureSampler_User0() {
		return two::TextureSampler::User0;
	}
	two::TextureSampler DECL two_TextureSampler_User1() {
		return two::TextureSampler::User1;
	}
	two::TextureSampler DECL two_TextureSampler_User2() {
		return two::TextureSampler::User2;
	}
	two::TextureSampler DECL two_TextureSampler_User3() {
		return two::TextureSampler::User3;
	}
	two::TextureSampler DECL two_TextureSampler_User4() {
		return two::TextureSampler::User4;
	}
	two::TextureSampler DECL two_TextureSampler_User5() {
		return two::TextureSampler::User5;
	}
	two::TextureSampler DECL two_TextureSampler_Radiance() {
		return two::TextureSampler::Radiance;
	}
	two::TextureSampler DECL two_TextureSampler_Shadow() {
		return two::TextureSampler::Shadow;
	}
	two::TextureSampler DECL two_TextureSampler_Lightmap() {
		return two::TextureSampler::Lightmap;
	}
	two::TextureSampler DECL two_TextureSampler_ReflectionProbe() {
		return two::TextureSampler::ReflectionProbe;
	}
	two::TextureSampler DECL two_TextureSampler_GIProbe() {
		return two::TextureSampler::GIProbe;
	}
	two::TextureSampler DECL two_TextureSampler_Skeleton() {
		return two::TextureSampler::Skeleton;
	}
	two::TextureSampler DECL two_TextureSampler_Zones() {
		return two::TextureSampler::Zones;
	}
	two::TextureSampler DECL two_TextureSampler_Materials() {
		return two::TextureSampler::Materials;
	}
	two::TextureSampler DECL two_TextureSampler_Lights() {
		return two::TextureSampler::Lights;
	}
	two::TextureSampler DECL two_TextureSampler_Clusters() {
		return two::TextureSampler::Clusters;
	}
	two::TextureSampler DECL two_TextureSampler_LightRecords() {
		return two::TextureSampler::LightRecords;
	}
	// Lighting
	two::Lighting DECL two_Lighting_None() {
		return two::Lighting::None;
	}
	two::Lighting DECL two_Lighting_Clustered() {
		return two::Lighting::Clustered;
	}
	two::Lighting DECL two_Lighting_Deferred() {
		return two::Lighting::Deferred;
	}
	two::Lighting DECL two_Lighting_VoxelGI() {
		return two::Lighting::VoxelGI;
	}
	// BlendMode
	two::BlendMode DECL two_BlendMode_None() {
		return two::BlendMode::None;
	}
	two::BlendMode DECL two_BlendMode_Mix() {
		return two::BlendMode::Mix;
	}
	two::BlendMode DECL two_BlendMode_Add() {
		return two::BlendMode::Add;
	}
	two::BlendMode DECL two_BlendMode_Sub() {
		return two::BlendMode::Sub;
	}
	two::BlendMode DECL two_BlendMode_Mul() {
		return two::BlendMode::Mul;
	}
	two::BlendMode DECL two_BlendMode_Normal() {
		return two::BlendMode::Normal;
	}
	two::BlendMode DECL two_BlendMode_Alpha() {
		return two::BlendMode::Alpha;
	}
	// CullMode
	two::CullMode DECL two_CullMode_None() {
		return two::CullMode::None;
	}
	two::CullMode DECL two_CullMode_Front() {
		return two::CullMode::Front;
	}
	two::CullMode DECL two_CullMode_Back() {
		return two::CullMode::Back;
	}
	two::CullMode DECL two_CullMode_Count() {
		return two::CullMode::Count;
	}
	// DepthDraw
	two::DepthDraw DECL two_DepthDraw_Enabled() {
		return two::DepthDraw::Enabled;
	}
	two::DepthDraw DECL two_DepthDraw_Disabled() {
		return two::DepthDraw::Disabled;
	}
	// DepthTest
	two::DepthTest DECL two_DepthTest_Enabled() {
		return two::DepthTest::Enabled;
	}
	two::DepthTest DECL two_DepthTest_Disabled() {
		return two::DepthTest::Disabled;
	}
	// MaterialFlag
	two::MaterialFlag DECL two_MaterialFlag_TriplanarUV1() {
		return two::MaterialFlag::TriplanarUV1;
	}
	two::MaterialFlag DECL two_MaterialFlag_TriplanarUV2() {
		return two::MaterialFlag::TriplanarUV2;
	}
	two::MaterialFlag DECL two_MaterialFlag_Count() {
		return two::MaterialFlag::Count;
	}
	// ShaderColor
	two::ShaderColor DECL two_ShaderColor_Shader() {
		return two::ShaderColor::Shader;
	}
	two::ShaderColor DECL two_ShaderColor_Vertex() {
		return two::ShaderColor::Vertex;
	}
	two::ShaderColor DECL two_ShaderColor_Face() {
		return two::ShaderColor::Face;
	}
	// TextureChannel
	two::TextureChannel DECL two_TextureChannel_Red() {
		return two::TextureChannel::Red;
	}
	two::TextureChannel DECL two_TextureChannel_Green() {
		return two::TextureChannel::Green;
	}
	two::TextureChannel DECL two_TextureChannel_Blue() {
		return two::TextureChannel::Blue;
	}
	two::TextureChannel DECL two_TextureChannel_Alpha() {
		return two::TextureChannel::Alpha;
	}
	two::TextureChannel DECL two_TextureChannel_All() {
		return two::TextureChannel::All;
	}
	// PbrDiffuseMode
	two::PbrDiffuseMode DECL two_PbrDiffuseMode_Lambert() {
		return two::PbrDiffuseMode::Lambert;
	}
	two::PbrDiffuseMode DECL two_PbrDiffuseMode_LambertHalf() {
		return two::PbrDiffuseMode::LambertHalf;
	}
	two::PbrDiffuseMode DECL two_PbrDiffuseMode_OrenNayar() {
		return two::PbrDiffuseMode::OrenNayar;
	}
	two::PbrDiffuseMode DECL two_PbrDiffuseMode_Burley() {
		return two::PbrDiffuseMode::Burley;
	}
	two::PbrDiffuseMode DECL two_PbrDiffuseMode_Toon() {
		return two::PbrDiffuseMode::Toon;
	}
	// PbrSpecularMode
	two::PbrSpecularMode DECL two_PbrSpecularMode_SchlickGGX() {
		return two::PbrSpecularMode::SchlickGGX;
	}
	two::PbrSpecularMode DECL two_PbrSpecularMode_Blinn() {
		return two::PbrSpecularMode::Blinn;
	}
	two::PbrSpecularMode DECL two_PbrSpecularMode_Phong() {
		return two::PbrSpecularMode::Phong;
	}
	two::PbrSpecularMode DECL two_PbrSpecularMode_Toon() {
		return two::PbrSpecularMode::Toon;
	}
	two::PbrSpecularMode DECL two_PbrSpecularMode_Disabled() {
		return two::PbrSpecularMode::Disabled;
	}
	// PhongEnvBlendMode
	two::PhongEnvBlendMode DECL two_PhongEnvBlendMode_Mul() {
		return two::PhongEnvBlendMode::Mul;
	}
	two::PhongEnvBlendMode DECL two_PhongEnvBlendMode_Mix() {
		return two::PhongEnvBlendMode::Mix;
	}
	two::PhongEnvBlendMode DECL two_PhongEnvBlendMode_Add() {
		return two::PhongEnvBlendMode::Add;
	}
	// EmitterFlow
	two::EmitterFlow DECL two_EmitterFlow_Outward() {
		return two::EmitterFlow::Outward;
	}
	two::EmitterFlow DECL two_EmitterFlow_Absolute() {
		return two::EmitterFlow::Absolute;
	}
	// ItemShadow
	two::ItemShadow DECL two_ItemShadow_Default() {
		return two::ItemShadow::Default;
	}
	two::ItemShadow DECL two_ItemShadow_DoubleSided() {
		return two::ItemShadow::DoubleSided;
	}
	// ModelFormat
	two::ModelFormat DECL two_ModelFormat_obj() {
		return two::ModelFormat::obj;
	}
	two::ModelFormat DECL two_ModelFormat_ply() {
		return two::ModelFormat::ply;
	}
	two::ModelFormat DECL two_ModelFormat_gltf() {
		return two::ModelFormat::gltf;
	}
	two::ModelFormat DECL two_ModelFormat_Count() {
		return two::ModelFormat::Count;
	}
	// IsometricAngle
	two::IsometricAngle DECL two_IsometricAngle_NORTH() {
		return two::NORTH;
	}
	two::IsometricAngle DECL two_IsometricAngle_SOUTH() {
		return two::SOUTH;
	}
	two::IsometricAngle DECL two_IsometricAngle_EAST() {
		return two::EAST;
	}
	two::IsometricAngle DECL two_IsometricAngle_WEST() {
		return two::WEST;
	}
	// DepthMethod
	two::DepthMethod DECL two_DepthMethod_Depth() {
		return two::DepthMethod::Depth;
	}
	two::DepthMethod DECL two_DepthMethod_DepthPacked() {
		return two::DepthMethod::DepthPacked;
	}
	two::DepthMethod DECL two_DepthMethod_Distance() {
		return two::DepthMethod::Distance;
	}
	two::DepthMethod DECL two_DepthMethod_Count() {
		return two::DepthMethod::Count;
	}
	// LightType
	two::LightType DECL two_LightType_Direct() {
		return two::LightType::Direct;
	}
	two::LightType DECL two_LightType_Point() {
		return two::LightType::Point;
	}
	two::LightType DECL two_LightType_Spot() {
		return two::LightType::Spot;
	}
	two::LightType DECL two_LightType_Count() {
		return two::LightType::Count;
	}
	// ShadowFlags
	two::ShadowFlags DECL two_ShadowFlags_CSM_Stabilize() {
		return two::CSM_Stabilize;
	}
	two::ShadowFlags DECL two_ShadowFlags_CSM_Optimize() {
		return two::CSM_Optimize;
	}
	two::ShadowFlags DECL two_ShadowFlags_CSM_BlendSplits() {
		return two::CSM_BlendSplits;
	}
	// MSAA
	two::MSAA DECL two_MSAA_Disabled() {
		return two::MSAA::Disabled;
	}
	two::MSAA DECL two_MSAA_X2() {
		return two::MSAA::X2;
	}
	two::MSAA DECL two_MSAA_X4() {
		return two::MSAA::X4;
	}
	two::MSAA DECL two_MSAA_X8() {
		return two::MSAA::X8;
	}
	two::MSAA DECL two_MSAA_X16() {
		return two::MSAA::X16;
	}
	two::MSAA DECL two_MSAA_Count() {
		return two::MSAA::Count;
	}
	// Shading
	two::Shading DECL two_Shading_Wireframe() {
		return two::Shading::Wireframe;
	}
	two::Shading DECL two_Shading_Solid() {
		return two::Shading::Solid;
	}
	two::Shading DECL two_Shading_Shaded() {
		return two::Shading::Shaded;
	}
	two::Shading DECL two_Shading_Volume() {
		return two::Shading::Volume;
	}
	two::Shading DECL two_Shading_Voxels() {
		return two::Shading::Voxels;
	}
	two::Shading DECL two_Shading_Lightmap() {
		return two::Shading::Lightmap;
	}
	two::Shading DECL two_Shading_Clear() {
		return two::Shading::Clear;
	}
	two::Shading DECL two_Shading_Count() {
		return two::Shading::Count;
	}
	// BackgroundMode
	two::BackgroundMode DECL two_BackgroundMode_None() {
		return two::BackgroundMode::None;
	}
	two::BackgroundMode DECL two_BackgroundMode_Panorama() {
		return two::BackgroundMode::Panorama;
	}
	two::BackgroundMode DECL two_BackgroundMode_Radiance() {
		return two::BackgroundMode::Radiance;
	}
	two::BackgroundMode DECL two_BackgroundMode_Custom() {
		return two::BackgroundMode::Custom;
	}
	// Month
	two::Month DECL two_Month_January() {
		return two::Month::January;
	}
	two::Month DECL two_Month_February() {
		return two::Month::February;
	}
	two::Month DECL two_Month_March() {
		return two::Month::March;
	}
	two::Month DECL two_Month_April() {
		return two::Month::April;
	}
	two::Month DECL two_Month_May() {
		return two::Month::May;
	}
	two::Month DECL two_Month_June() {
		return two::Month::June;
	}
	two::Month DECL two_Month_July() {
		return two::Month::July;
	}
	two::Month DECL two_Month_August() {
		return two::Month::August;
	}
	two::Month DECL two_Month_September() {
		return two::Month::September;
	}
	two::Month DECL two_Month_October() {
		return two::Month::October;
	}
	two::Month DECL two_Month_November() {
		return two::Month::November;
	}
	two::Month DECL two_Month_December() {
		return two::Month::December;
	}
	
}


