#include <infra/Api.h>
#include <jobs/Api.h>
#include <type/Api.h>
#include <pool/Api.h>
#include <ecs/Api.h>
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
	
	// AnimatedTrack
	mud::Type* DECL mud_AnimatedTrack__type() {
		return &mud::type<mud::AnimatedTrack>();
	}
	mud::AnimatedTrack* DECL mud_AnimatedTrack__construct_0() {
		return new mud::AnimatedTrack();
	}
	void DECL mud_AnimatedTrack__destroy(mud::AnimatedTrack* self) {
		delete self;
	}
	// Animation
	mud::Type* DECL mud_Animation__type() {
		return &mud::type<mud::Animation>();
	}
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
	mud::Type* DECL mud_AnimationPlay__type() {
		return &mud::type<mud::AnimationPlay>();
	}
	mud::AnimationPlay* DECL mud_AnimationPlay__construct_0() {
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
	mud::Type* DECL mud_AnimationTrack__type() {
		return &mud::type<mud::AnimationTrack>();
	}
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
	// AssetStore<mud::Flow>
	mud::Type* DECL mud_AssetStore_mud_Flow__type() {
		return &mud::type<mud::AssetStore<mud::Flow>>();
	}
	mud::Flow* DECL mud_AssetStore_mud_Flow_get_1(mud::AssetStore<mud::Flow>* self, const char* name) {
		return self->get(name);
	}
	mud::Flow* DECL mud_AssetStore_mud_Flow_create_1(mud::AssetStore<mud::Flow>* self, const char* name) {
		return &self->create(name);
	}
	mud::Flow* DECL mud_AssetStore_mud_Flow_fetch_1(mud::AssetStore<mud::Flow>* self, const char* name) {
		return &self->fetch(name);
	}
	mud::Flow* DECL mud_AssetStore_mud_Flow_file_1(mud::AssetStore<mud::Flow>* self, const char* name) {
		return self->file(name);
	}
	mud::Flow* DECL mud_AssetStore_mud_Flow_file_at_2(mud::AssetStore<mud::Flow>* self, const char* path, const char* name) {
		return &self->file_at(path, name);
	}
	void DECL mud_AssetStore_mud_Flow_destroy_1(mud::AssetStore<mud::Flow>* self, const char* name) {
		self->destroy(name);
	}
	void DECL mud_AssetStore_mud_Flow__destroy(mud::AssetStore<mud::Flow>* self) {
		delete self;
	}
	// AssetStore<mud::Material>
	mud::Type* DECL mud_AssetStore_mud_Material__type() {
		return &mud::type<mud::AssetStore<mud::Material>>();
	}
	mud::Material* DECL mud_AssetStore_mud_Material_get_1(mud::AssetStore<mud::Material>* self, const char* name) {
		return self->get(name);
	}
	mud::Material* DECL mud_AssetStore_mud_Material_create_1(mud::AssetStore<mud::Material>* self, const char* name) {
		return &self->create(name);
	}
	mud::Material* DECL mud_AssetStore_mud_Material_fetch_1(mud::AssetStore<mud::Material>* self, const char* name) {
		return &self->fetch(name);
	}
	mud::Material* DECL mud_AssetStore_mud_Material_file_1(mud::AssetStore<mud::Material>* self, const char* name) {
		return self->file(name);
	}
	mud::Material* DECL mud_AssetStore_mud_Material_file_at_2(mud::AssetStore<mud::Material>* self, const char* path, const char* name) {
		return &self->file_at(path, name);
	}
	void DECL mud_AssetStore_mud_Material_destroy_1(mud::AssetStore<mud::Material>* self, const char* name) {
		self->destroy(name);
	}
	void DECL mud_AssetStore_mud_Material__destroy(mud::AssetStore<mud::Material>* self) {
		delete self;
	}
	// AssetStore<mud::Model>
	mud::Type* DECL mud_AssetStore_mud_Model__type() {
		return &mud::type<mud::AssetStore<mud::Model>>();
	}
	mud::Model* DECL mud_AssetStore_mud_Model_get_1(mud::AssetStore<mud::Model>* self, const char* name) {
		return self->get(name);
	}
	mud::Model* DECL mud_AssetStore_mud_Model_create_1(mud::AssetStore<mud::Model>* self, const char* name) {
		return &self->create(name);
	}
	mud::Model* DECL mud_AssetStore_mud_Model_fetch_1(mud::AssetStore<mud::Model>* self, const char* name) {
		return &self->fetch(name);
	}
	mud::Model* DECL mud_AssetStore_mud_Model_file_1(mud::AssetStore<mud::Model>* self, const char* name) {
		return self->file(name);
	}
	mud::Model* DECL mud_AssetStore_mud_Model_file_at_2(mud::AssetStore<mud::Model>* self, const char* path, const char* name) {
		return &self->file_at(path, name);
	}
	void DECL mud_AssetStore_mud_Model_destroy_1(mud::AssetStore<mud::Model>* self, const char* name) {
		self->destroy(name);
	}
	void DECL mud_AssetStore_mud_Model__destroy(mud::AssetStore<mud::Model>* self) {
		delete self;
	}
	// AssetStore<mud::Prefab>
	mud::Type* DECL mud_AssetStore_mud_Prefab__type() {
		return &mud::type<mud::AssetStore<mud::Prefab>>();
	}
	mud::Prefab* DECL mud_AssetStore_mud_Prefab_get_1(mud::AssetStore<mud::Prefab>* self, const char* name) {
		return self->get(name);
	}
	mud::Prefab* DECL mud_AssetStore_mud_Prefab_create_1(mud::AssetStore<mud::Prefab>* self, const char* name) {
		return &self->create(name);
	}
	mud::Prefab* DECL mud_AssetStore_mud_Prefab_fetch_1(mud::AssetStore<mud::Prefab>* self, const char* name) {
		return &self->fetch(name);
	}
	mud::Prefab* DECL mud_AssetStore_mud_Prefab_file_1(mud::AssetStore<mud::Prefab>* self, const char* name) {
		return self->file(name);
	}
	mud::Prefab* DECL mud_AssetStore_mud_Prefab_file_at_2(mud::AssetStore<mud::Prefab>* self, const char* path, const char* name) {
		return &self->file_at(path, name);
	}
	void DECL mud_AssetStore_mud_Prefab_destroy_1(mud::AssetStore<mud::Prefab>* self, const char* name) {
		self->destroy(name);
	}
	void DECL mud_AssetStore_mud_Prefab__destroy(mud::AssetStore<mud::Prefab>* self) {
		delete self;
	}
	// AssetStore<mud::Program>
	mud::Type* DECL mud_AssetStore_mud_Program__type() {
		return &mud::type<mud::AssetStore<mud::Program>>();
	}
	mud::Program* DECL mud_AssetStore_mud_Program_get_1(mud::AssetStore<mud::Program>* self, const char* name) {
		return self->get(name);
	}
	mud::Program* DECL mud_AssetStore_mud_Program_create_1(mud::AssetStore<mud::Program>* self, const char* name) {
		return &self->create(name);
	}
	mud::Program* DECL mud_AssetStore_mud_Program_fetch_1(mud::AssetStore<mud::Program>* self, const char* name) {
		return &self->fetch(name);
	}
	mud::Program* DECL mud_AssetStore_mud_Program_file_1(mud::AssetStore<mud::Program>* self, const char* name) {
		return self->file(name);
	}
	mud::Program* DECL mud_AssetStore_mud_Program_file_at_2(mud::AssetStore<mud::Program>* self, const char* path, const char* name) {
		return &self->file_at(path, name);
	}
	void DECL mud_AssetStore_mud_Program_destroy_1(mud::AssetStore<mud::Program>* self, const char* name) {
		self->destroy(name);
	}
	void DECL mud_AssetStore_mud_Program__destroy(mud::AssetStore<mud::Program>* self) {
		delete self;
	}
	// AssetStore<mud::Texture>
	mud::Type* DECL mud_AssetStore_mud_Texture__type() {
		return &mud::type<mud::AssetStore<mud::Texture>>();
	}
	mud::Texture* DECL mud_AssetStore_mud_Texture_get_1(mud::AssetStore<mud::Texture>* self, const char* name) {
		return self->get(name);
	}
	mud::Texture* DECL mud_AssetStore_mud_Texture_create_1(mud::AssetStore<mud::Texture>* self, const char* name) {
		return &self->create(name);
	}
	mud::Texture* DECL mud_AssetStore_mud_Texture_fetch_1(mud::AssetStore<mud::Texture>* self, const char* name) {
		return &self->fetch(name);
	}
	mud::Texture* DECL mud_AssetStore_mud_Texture_file_1(mud::AssetStore<mud::Texture>* self, const char* name) {
		return self->file(name);
	}
	mud::Texture* DECL mud_AssetStore_mud_Texture_file_at_2(mud::AssetStore<mud::Texture>* self, const char* path, const char* name) {
		return &self->file_at(path, name);
	}
	void DECL mud_AssetStore_mud_Texture_destroy_1(mud::AssetStore<mud::Texture>* self, const char* name) {
		self->destroy(name);
	}
	void DECL mud_AssetStore_mud_Texture__destroy(mud::AssetStore<mud::Texture>* self) {
		delete self;
	}
	// Background
	mud::Type* DECL mud_Background__type() {
		return &mud::type<mud::Background>();
	}
	mud::Background* DECL mud_Background__construct_0() {
		return new mud::Background();
	}
	mud::BackgroundMode DECL mud_Background__get_mode(mud::Background* self) {
		return self->m_mode;
	}
	void DECL mud_Background__set_mode(mud::Background* self, mud::BackgroundMode value) {
		self->m_mode = value;
	}
	mud::Colour* DECL mud_Background__get_colour(mud::Background* self) {
		return &self->m_colour;
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
	// Batch
	mud::Type* DECL mud_Batch__type() {
		return &mud::type<mud::Batch>();
	}
	mud::Batch* DECL mud_Batch__construct_0() {
		return new mud::Batch();
	}
	mud::Batch* DECL mud_Batch__construct_1(mud::Item* item) {
		return new mud::Batch(*item);
	}
	void DECL mud_Batch_update_aabb_1(mud::Batch* self, float* instances, int instances_size) {
		self->update_aabb({ (mud::mat4*)instances, instances_size / (sizeof(mud::mat4) / sizeof(float)) });
	}
	void DECL mud_Batch_transforms_1(mud::Batch* self, float* instances, int instances_size) {
		self->transforms({ (mud::mat4*)instances, instances_size / (sizeof(mud::mat4) / sizeof(float)) });
	}
	float* DECL mud_Batch_begin_2(mud::Batch* self, uint32_t count, uint16_t stride) {
		return (float*)self->begin(count, stride).data();
	}
	void DECL mud_Batch_commit_3(mud::Batch* self, uint32_t count, uint16_t stride, float* data, int data_size) {
		self->commit(count, stride, { (float*)data, data_size / (sizeof(float) / sizeof(float)) });
	}
	mud::Item* DECL mud_Batch__get_item(mud::Batch* self) {
		return self->m_item;
	}
	void DECL mud_Batch__set_item(mud::Batch* self, mud::Item* value) {
		self->m_item = value;
	}
	void DECL mud_Batch__destroy(mud::Batch* self) {
		delete self;
	}
	// Bone
	mud::Type* DECL mud_Bone__type() {
		return &mud::type<mud::Bone>();
	}
	mud::Bone* DECL mud_Bone__construct_0() {
		return new mud::Bone();
	}
	mud::vec3* DECL mud_Bone__get_position(mud::Bone* self) {
		return &self->m_position;
	}
	void DECL mud_Bone__set_position(mud::Bone* self, mud::vec3* value) {
		self->m_position = *value;
	}
	mud::quat* DECL mud_Bone__get_rotation(mud::Bone* self) {
		return &self->m_rotation;
	}
	void DECL mud_Bone__set_rotation(mud::Bone* self, mud::quat* value) {
		self->m_rotation = *value;
	}
	mud::vec3* DECL mud_Bone__get_scale(mud::Bone* self) {
		return &self->m_scale;
	}
	void DECL mud_Bone__set_scale(mud::Bone* self, mud::vec3* value) {
		self->m_scale = *value;
	}
	void DECL mud_Bone__destroy(mud::Bone* self) {
		delete self;
	}
	// Camera
	mud::Type* DECL mud_Camera__type() {
		return &mud::type<mud::Camera>();
	}
	void DECL mud_Camera_set_clustered_2(mud::Camera* self, mud::GfxSystem* gfx, mud::Viewport* viewport) {
		self->set_clustered(*gfx, *viewport);
	}
	void DECL mud_Camera_set_look_at_2(mud::Camera* self, const mud::vec3* eye, const mud::vec3* target) {
		self->set_look_at(*eye, *target);
	}
	void DECL mud_Camera_set_isometric_2(mud::Camera* self, mud::IsometricAngle angle, const mud::vec3* position) {
		self->set_isometric(angle, *position);
	}
	mud::vec3* DECL mud_Camera__get_eye(mud::Camera* self) {
		return &self->m_eye;
	}
	void DECL mud_Camera__set_eye(mud::Camera* self, mud::vec3* value) {
		self->m_eye = *value;
	}
	mud::vec3* DECL mud_Camera__get_target(mud::Camera* self) {
		return &self->m_target;
	}
	void DECL mud_Camera__set_target(mud::Camera* self, mud::vec3* value) {
		self->m_target = *value;
	}
	mud::vec3* DECL mud_Camera__get_up(mud::Camera* self) {
		return &self->m_up;
	}
	void DECL mud_Camera__set_up(mud::Camera* self, mud::vec3* value) {
		self->m_up = *value;
	}
	mud::mat4* DECL mud_Camera__get_transform(mud::Camera* self) {
		return &self->m_transform;
	}
	void DECL mud_Camera__set_transform(mud::Camera* self, mud::mat4* value) {
		self->m_transform = *value;
	}
	mud::mat4* DECL mud_Camera__get_projection(mud::Camera* self) {
		return &self->m_projection;
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
		return &self->m_lod_offsets;
	}
	void DECL mud_Camera__set_lod_offsets(mud::Camera* self, mud::vec4* value) {
		self->m_lod_offsets = *value;
	}
	void DECL mud_Camera__destroy(mud::Camera* self) {
		delete self;
	}
	// Culler
	mud::Type* DECL mud_Culler__type() {
		return &mud::type<mud::Culler>();
	}
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
	mud::Type* DECL mud_DepthParams__type() {
		return &mud::type<mud::DepthParams>();
	}
	mud::DepthParams* DECL mud_DepthParams__construct_0() {
		return new mud::DepthParams();
	}
	float DECL mud_DepthParams__get_depth_bias(mud::DepthParams* self) {
		return self->m_depth_bias;
	}
	void DECL mud_DepthParams__set_depth_bias(mud::DepthParams* self, float value) {
		self->m_depth_bias = value;
	}
	float DECL mud_DepthParams__get_depth_normal_bias(mud::DepthParams* self) {
		return self->m_depth_normal_bias;
	}
	void DECL mud_DepthParams__set_depth_normal_bias(mud::DepthParams* self, float value) {
		self->m_depth_normal_bias = value;
	}
	float DECL mud_DepthParams__get_depth_z_far(mud::DepthParams* self) {
		return self->m_depth_z_far;
	}
	void DECL mud_DepthParams__set_depth_z_far(mud::DepthParams* self, float value) {
		self->m_depth_z_far = value;
	}
	void DECL mud_DepthParams__destroy(mud::DepthParams* self) {
		delete self;
	}
	// Direct
	mud::Type* DECL mud_Direct__type() {
		return &mud::type<mud::Direct>();
	}
	mud::Direct* DECL mud_Direct__construct_0() {
		return new mud::Direct();
	}
	mud::Direct* DECL mud_Direct__construct_2(mud::Node3* node, mud::Material* material) {
		return new mud::Direct(*node, *material);
	}
	mud::Node3* DECL mud_Direct__get_node(mud::Direct* self) {
		return self->m_node;
	}
	void DECL mud_Direct__set_node(mud::Direct* self, mud::Node3* value) {
		self->m_node = value;
	}
	mud::Material* DECL mud_Direct__get_material(mud::Direct* self) {
		return self->m_material;
	}
	void DECL mud_Direct__set_material(mud::Direct* self, mud::Material* value) {
		self->m_material = value;
	}
	void DECL mud_Direct__destroy(mud::Direct* self) {
		delete self;
	}
	// DistanceParams
	mud::Type* DECL mud_DistanceParams__type() {
		return &mud::type<mud::DistanceParams>();
	}
	mud::DistanceParams* DECL mud_DistanceParams__construct_0() {
		return new mud::DistanceParams();
	}
	mud::vec3* DECL mud_DistanceParams__get_eye(mud::DistanceParams* self) {
		return &self->m_eye;
	}
	void DECL mud_DistanceParams__set_eye(mud::DistanceParams* self, mud::vec3* value) {
		self->m_eye = *value;
	}
	float DECL mud_DistanceParams__get_near(mud::DistanceParams* self) {
		return self->m_near;
	}
	void DECL mud_DistanceParams__set_near(mud::DistanceParams* self, float value) {
		self->m_near = value;
	}
	float DECL mud_DistanceParams__get_far(mud::DistanceParams* self) {
		return self->m_far;
	}
	void DECL mud_DistanceParams__set_far(mud::DistanceParams* self, float value) {
		self->m_far = value;
	}
	void DECL mud_DistanceParams__destroy(mud::DistanceParams* self) {
		delete self;
	}
	// Filter
	mud::Type* DECL mud_Filter__type() {
		return &mud::type<mud::Filter>();
	}
	void DECL mud_Filter__destroy(mud::Filter* self) {
		delete self;
	}
	// Flow
	mud::Type* DECL mud_Flow__type() {
		return &mud::type<mud::Flow>();
	}
	mud::Flow* DECL mud_Flow__construct_0() {
		return new mud::Flow();
	}
	const char* DECL mud_Flow__get_name(mud::Flow* self) {
		return self->m_name.c_str();
	}
	void DECL mud_Flow__set_name(mud::Flow* self, const char* value) {
		self->m_name = value;
	}
	float DECL mud_Flow__get_duration(mud::Flow* self) {
		return self->m_duration;
	}
	void DECL mud_Flow__set_duration(mud::Flow* self, float value) {
		self->m_duration = value;
	}
	float DECL mud_Flow__get_start_time(mud::Flow* self) {
		return self->m_start_time;
	}
	void DECL mud_Flow__set_start_time(mud::Flow* self, float value) {
		self->m_start_time = value;
	}
	bool DECL mud_Flow__get_loop(mud::Flow* self) {
		return self->m_loop;
	}
	void DECL mud_Flow__set_loop(mud::Flow* self, bool value) {
		self->m_loop = value;
	}
	mud::ShapeVar* DECL mud_Flow__get_shape(mud::Flow* self) {
		return &self->m_shape;
	}
	mud::EmitterFlow DECL mud_Flow__get_flow(mud::Flow* self) {
		return self->m_flow;
	}
	void DECL mud_Flow__set_flow(mud::Flow* self, mud::EmitterFlow value) {
		self->m_flow = value;
	}
	bool DECL mud_Flow__get_billboard(mud::Flow* self) {
		return self->m_billboard;
	}
	void DECL mud_Flow__set_billboard(mud::Flow* self, bool value) {
		self->m_billboard = value;
	}
	mud::vec3* DECL mud_Flow__get_direction(mud::Flow* self) {
		return &self->m_direction;
	}
	void DECL mud_Flow__set_direction(mud::Flow* self, mud::vec3* value) {
		self->m_direction = *value;
	}
	mud::quat* DECL mud_Flow__get_rotation(mud::Flow* self) {
		return &self->m_rotation;
	}
	void DECL mud_Flow__set_rotation(mud::Flow* self, mud::quat* value) {
		self->m_rotation = *value;
	}
	mud::BlendMode DECL mud_Flow__get_blend_mode(mud::Flow* self) {
		return self->m_blend_mode;
	}
	void DECL mud_Flow__set_blend_mode(mud::Flow* self, mud::BlendMode value) {
		self->m_blend_mode = value;
	}
	mud::ValueTrack<float>* DECL mud_Flow__get_volume(mud::Flow* self) {
		return &self->m_volume;
	}
	void DECL mud_Flow__set_volume(mud::Flow* self, mud::ValueTrack<float>* value) {
		self->m_volume = *value;
	}
	mud::ValueTrack<uint32_t>* DECL mud_Flow__get_rate(mud::Flow* self) {
		return &self->m_rate;
	}
	void DECL mud_Flow__set_rate(mud::Flow* self, mud::ValueTrack<uint32_t>* value) {
		self->m_rate = *value;
	}
	mud::ValueTrack<float>* DECL mud_Flow__get_lifetime(mud::Flow* self) {
		return &self->m_lifetime;
	}
	void DECL mud_Flow__set_lifetime(mud::Flow* self, mud::ValueTrack<float>* value) {
		self->m_lifetime = *value;
	}
	mud::ValueTrack<float>* DECL mud_Flow__get_gravity(mud::Flow* self) {
		return &self->m_gravity;
	}
	void DECL mud_Flow__set_gravity(mud::Flow* self, mud::ValueTrack<float>* value) {
		self->m_gravity = *value;
	}
	mud::ValueTrack<float>* DECL mud_Flow__get_speed(mud::Flow* self) {
		return &self->m_speed;
	}
	void DECL mud_Flow__set_speed(mud::Flow* self, mud::ValueTrack<float>* value) {
		self->m_speed = *value;
	}
	mud::ValueTrack<float>* DECL mud_Flow__get_angle(mud::Flow* self) {
		return &self->m_angle;
	}
	void DECL mud_Flow__set_angle(mud::Flow* self, mud::ValueTrack<float>* value) {
		self->m_angle = *value;
	}
	mud::ValueTrack<float>* DECL mud_Flow__get_blend(mud::Flow* self) {
		return &self->m_blend;
	}
	void DECL mud_Flow__set_blend(mud::Flow* self, mud::ValueTrack<float>* value) {
		self->m_blend = *value;
	}
	mud::ValueTrack<mud::Colour>* DECL mud_Flow__get_colour(mud::Flow* self) {
		return &self->m_colour;
	}
	void DECL mud_Flow__set_colour(mud::Flow* self, mud::ValueTrack<mud::Colour>* value) {
		self->m_colour = *value;
	}
	mud::ValueTrack<float>* DECL mud_Flow__get_scale(mud::Flow* self) {
		return &self->m_scale;
	}
	void DECL mud_Flow__set_scale(mud::Flow* self, mud::ValueTrack<float>* value) {
		self->m_scale = *value;
	}
	mud::ValueTrack<float>* DECL mud_Flow__get_sprite_frame(mud::Flow* self) {
		return &self->m_sprite_frame;
	}
	void DECL mud_Flow__set_sprite_frame(mud::Flow* self, mud::ValueTrack<float>* value) {
		self->m_sprite_frame = *value;
	}
	const char* DECL mud_Flow__get_sprite_name(mud::Flow* self) {
		return self->m_sprite_name.c_str();
	}
	void DECL mud_Flow__set_sprite_name(mud::Flow* self, const char* value) {
		self->m_sprite_name = value;
	}
	void DECL mud_Flow__destroy(mud::Flow* self) {
		delete self;
	}
	// Fog
	mud::Type* DECL mud_Fog__type() {
		return &mud::type<mud::Fog>();
	}
	mud::Fog* DECL mud_Fog__construct_0() {
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
		return &self->m_colour;
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
	mud::Type* DECL mud_FrameBuffer__type() {
		return &mud::type<mud::FrameBuffer>();
	}
	void DECL mud_FrameBuffer__destroy(mud::FrameBuffer* self) {
		delete self;
	}
	// Frustum
	mud::Type* DECL mud_Frustum__type() {
		return &mud::type<mud::Frustum>();
	}
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
		return &self->m_center;
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
	mud::Type* DECL mud_FrustumSlice__type() {
		return &mud::type<mud::FrustumSlice>();
	}
	mud::FrustumSlice* DECL mud_FrustumSlice__construct_0() {
		return new mud::FrustumSlice();
	}
	void DECL mud_FrustumSlice__destroy(mud::FrustumSlice* self) {
		delete self;
	}
	// GfxBlock
	mud::Type* DECL mud_GfxBlock__type() {
		return &mud::type<mud::GfxBlock>();
	}
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
	mud::Type* DECL mud_GfxContext__type() {
		return &mud::type<mud::GfxContext>();
	}
	void DECL mud_GfxContext__destroy(mud::GfxContext* self) {
		delete self;
	}
	// Gnode
	mud::Type* DECL mud_Gnode__type() {
		return &mud::type<mud::Gnode>();
	}
	void DECL mud_Gnode__destroy(mud::Gnode* self) {
		delete self;
	}
	// GpuMesh
	mud::Type* DECL mud_GpuMesh__type() {
		return &mud::type<mud::GpuMesh>();
	}
	mud::GpuMesh* DECL mud_GpuMesh__construct_0() {
		return new mud::GpuMesh();
	}
	void DECL mud_GpuMesh__destroy(mud::GpuMesh* self) {
		delete self;
	}
	// ImmediateDraw
	mud::Type* DECL mud_ImmediateDraw__type() {
		return &mud::type<mud::ImmediateDraw>();
	}
	void DECL mud_ImmediateDraw__destroy(mud::ImmediateDraw* self) {
		delete self;
	}
	// Import
	mud::Type* DECL mud_Import__type() {
		return &mud::type<mud::Import>();
	}
	const char* DECL mud_Import__get_name(mud::Import* self) {
		return self->m_name.c_str();
	}
	void DECL mud_Import__set_name(mud::Import* self, const char* value) {
		self->m_name = value;
	}
	const char* DECL mud_Import__get_file(mud::Import* self) {
		return self->m_file.c_str();
	}
	void DECL mud_Import__set_file(mud::Import* self, const char* value) {
		self->m_file = value;
	}
	const char* DECL mud_Import__get_path(mud::Import* self) {
		return self->m_path.c_str();
	}
	void DECL mud_Import__set_path(mud::Import* self, const char* value) {
		self->m_path = value;
	}
	mud::ImportConfig* DECL mud_Import__get_config(mud::Import* self) {
		return &self->m_config;
	}
	void DECL mud_Import__set_config(mud::Import* self, mud::ImportConfig* value) {
		self->m_config = *value;
	}
	void DECL mud_Import__destroy(mud::Import* self) {
		delete self;
	}
	// ImportConfig
	mud::Type* DECL mud_ImportConfig__type() {
		return &mud::type<mud::ImportConfig>();
	}
	mud::ImportConfig* DECL mud_ImportConfig__construct_0() {
		return new mud::ImportConfig();
	}
	mud::ModelFormat DECL mud_ImportConfig__get_format(mud::ImportConfig* self) {
		return self->m_format;
	}
	void DECL mud_ImportConfig__set_format(mud::ImportConfig* self, mud::ModelFormat value) {
		self->m_format = value;
	}
	mud::vec3* DECL mud_ImportConfig__get_position(mud::ImportConfig* self) {
		return &self->m_position;
	}
	void DECL mud_ImportConfig__set_position(mud::ImportConfig* self, mud::vec3* value) {
		self->m_position = *value;
	}
	mud::quat* DECL mud_ImportConfig__get_rotation(mud::ImportConfig* self) {
		return &self->m_rotation;
	}
	void DECL mud_ImportConfig__set_rotation(mud::ImportConfig* self, mud::quat* value) {
		self->m_rotation = *value;
	}
	mud::vec3* DECL mud_ImportConfig__get_scale(mud::ImportConfig* self) {
		return &self->m_scale;
	}
	void DECL mud_ImportConfig__set_scale(mud::ImportConfig* self, mud::vec3* value) {
		self->m_scale = *value;
	}
	mud::mat4* DECL mud_ImportConfig__get_transform(mud::ImportConfig* self) {
		return &self->m_transform;
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
	mud::Type* DECL mud_Item__type() {
		return &mud::type<mud::Item>();
	}
	mud::Item* DECL mud_Item__construct_0() {
		return new mud::Item();
	}
	mud::Item* DECL mud_Item__construct_2(mud::Node3* node, const mud::Model* model) {
		return new mud::Item(*node, *model);
	}
	mud::Item* DECL mud_Item__construct_3(mud::Node3* node, const mud::Model* model, uint32_t flags) {
		return new mud::Item(*node, *model, flags);
	}
	mud::Item* DECL mud_Item__construct_4(mud::Node3* node, const mud::Model* model, uint32_t flags, mud::Material* material) {
		return new mud::Item(*node, *model, flags, material);
	}
	void DECL mud_Item_update_aabb_0(mud::Item* self) {
		self->update_aabb();
	}
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
		return &self->m_colour;
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
	mud::Aabb* DECL mud_Item__get_aabb(mud::Item* self) {
		return &self->m_aabb;
	}
	void DECL mud_Item__set_aabb(mud::Item* self, mud::Aabb* value) {
		self->m_aabb = *value;
	}
	mud::Batch* DECL mud_Item__get_batch(mud::Item* self) {
		return self->m_batch;
	}
	void DECL mud_Item__set_batch(mud::Item* self, mud::Batch* value) {
		self->m_batch = value;
	}
	void DECL mud_Item__destroy(mud::Item* self) {
		delete self;
	}
	// Joint
	mud::Type* DECL mud_Joint__type() {
		return &mud::type<mud::Joint>();
	}
	mud::Joint* DECL mud_Joint__construct_0() {
		return new mud::Joint();
	}
	void DECL mud_Joint__destroy(mud::Joint* self) {
		delete self;
	}
	// Light
	mud::Type* DECL mud_Light__type() {
		return &mud::type<mud::Light>();
	}
	mud::Light* DECL mud_Light__construct_1(mud::Node3* node) {
		return new mud::Light(*node);
	}
	mud::Light* DECL mud_Light__construct_2(mud::Node3* node, mud::LightType type) {
		return new mud::Light(*node, type);
	}
	mud::Light* DECL mud_Light__construct_3(mud::Node3* node, mud::LightType type, bool shadows) {
		return new mud::Light(*node, type, shadows);
	}
	mud::Light* DECL mud_Light__construct_4(mud::Node3* node, mud::LightType type, bool shadows, mud::Colour* colour) {
		return new mud::Light(*node, type, shadows, *colour);
	}
	mud::Light* DECL mud_Light__construct_5(mud::Node3* node, mud::LightType type, bool shadows, mud::Colour* colour, float energy) {
		return new mud::Light(*node, type, shadows, *colour, energy);
	}
	mud::Light* DECL mud_Light__construct_6(mud::Node3* node, mud::LightType type, bool shadows, mud::Colour* colour, float energy, float range) {
		return new mud::Light(*node, type, shadows, *colour, energy, range);
	}
	mud::Node3* DECL mud_Light__get_node(mud::Light* self) {
		return self->m_node;
	}
	void DECL mud_Light__set_node(mud::Light* self, mud::Node3* value) {
		self->m_node = value;
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
		return &self->m_colour;
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
	// Lines
	mud::Type* DECL mud_Lines__type() {
		return &mud::type<mud::Lines>();
	}
	mud::Lines* DECL mud_Lines__construct_1(mud::GfxSystem* gfx) {
		return new mud::Lines(*gfx);
	}
	void DECL mud_Lines_add_4(mud::Lines* self, const mud::vec3* start, const mud::vec3* end, mud::Colour* start_colour, mud::Colour* end_colour) {
		self->add(*start, *end, *start_colour, *end_colour);
	}
	void DECL mud_Lines_setup_0(mud::Lines* self) {
		self->setup();
	}
	void DECL mud_Lines_commit_1(mud::Lines* self, mud::Batch* batch) {
		self->commit(*batch);
	}
	mud::Model* DECL mud_Lines__get_model(mud::Lines* self) {
		return self->m_model;
	}
	void DECL mud_Lines__set_model(mud::Lines* self, mud::Model* value) {
		self->m_model = value;
	}
	void DECL mud_Lines__destroy(mud::Lines* self) {
		delete self;
	}
	// Material
	mud::Type* DECL mud_Material__type() {
		return &mud::type<mud::Material>();
	}
	uint16_t DECL mud_Material__get_index(mud::Material* self) {
		return self->m_index;
	}
	void DECL mud_Material__set_index(mud::Material* self, uint16_t value) {
		self->m_index = value;
	}
	const char* DECL mud_Material__get_name(mud::Material* self) {
		return self->m_name.c_str();
	}
	void DECL mud_Material__set_name(mud::Material* self, const char* value) {
		self->m_name = value;
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
	mud::MaterialBase* DECL mud_Material__get_base(mud::Material* self) {
		return &self->m_base;
	}
	void DECL mud_Material__set_base(mud::Material* self, mud::MaterialBase* value) {
		self->m_base = *value;
	}
	mud::MaterialAlpha* DECL mud_Material__get_alpha(mud::Material* self) {
		return &self->m_alpha;
	}
	void DECL mud_Material__set_alpha(mud::Material* self, mud::MaterialAlpha* value) {
		self->m_alpha = *value;
	}
	mud::MaterialSolid* DECL mud_Material__get_solid(mud::Material* self) {
		return &self->m_solid;
	}
	void DECL mud_Material__set_solid(mud::Material* self, mud::MaterialSolid* value) {
		self->m_solid = *value;
	}
	mud::MaterialPoint* DECL mud_Material__get_point(mud::Material* self) {
		return &self->m_point;
	}
	void DECL mud_Material__set_point(mud::Material* self, mud::MaterialPoint* value) {
		self->m_point = *value;
	}
	mud::MaterialLine* DECL mud_Material__get_line(mud::Material* self) {
		return &self->m_line;
	}
	void DECL mud_Material__set_line(mud::Material* self, mud::MaterialLine* value) {
		self->m_line = *value;
	}
	mud::MaterialPbr* DECL mud_Material__get_pbr(mud::Material* self) {
		return &self->m_pbr;
	}
	void DECL mud_Material__set_pbr(mud::Material* self, mud::MaterialPbr* value) {
		self->m_pbr = *value;
	}
	mud::MaterialFresnel* DECL mud_Material__get_fresnel(mud::Material* self) {
		return &self->m_fresnel;
	}
	void DECL mud_Material__set_fresnel(mud::Material* self, mud::MaterialFresnel* value) {
		self->m_fresnel = *value;
	}
	mud::MaterialUser* DECL mud_Material__get_user(mud::Material* self) {
		return &self->m_user;
	}
	void DECL mud_Material__set_user(mud::Material* self, mud::MaterialUser* value) {
		self->m_user = *value;
	}
	void DECL mud_Material__destroy(mud::Material* self) {
		delete self;
	}
	// MaterialAlpha
	mud::Type* DECL mud_MaterialAlpha__type() {
		return &mud::type<mud::MaterialAlpha>();
	}
	mud::MaterialAlpha* DECL mud_MaterialAlpha__construct_0() {
		return new mud::MaterialAlpha();
	}
	mud::MaterialParam<float>* DECL mud_MaterialAlpha__get_alpha(mud::MaterialAlpha* self) {
		return &self->m_alpha;
	}
	void DECL mud_MaterialAlpha__set_alpha(mud::MaterialAlpha* self, mud::MaterialParam<float>* value) {
		self->m_alpha = *value;
	}
	float DECL mud_MaterialAlpha__get_alpha_scissor(mud::MaterialAlpha* self) {
		return self->m_alpha_scissor;
	}
	void DECL mud_MaterialAlpha__set_alpha_scissor(mud::MaterialAlpha* self, float value) {
		self->m_alpha_scissor = value;
	}
	bool DECL mud_MaterialAlpha__get_alpha_test(mud::MaterialAlpha* self) {
		return self->m_alpha_test;
	}
	void DECL mud_MaterialAlpha__set_alpha_test(mud::MaterialAlpha* self, bool value) {
		self->m_alpha_test = value;
	}
	bool DECL mud_MaterialAlpha__get_is_alpha(mud::MaterialAlpha* self) {
		return self->m_is_alpha;
	}
	void DECL mud_MaterialAlpha__set_is_alpha(mud::MaterialAlpha* self, bool value) {
		self->m_is_alpha = value;
	}
	void DECL mud_MaterialAlpha__destroy(mud::MaterialAlpha* self) {
		delete self;
	}
	// MaterialBase
	mud::Type* DECL mud_MaterialBase__type() {
		return &mud::type<mud::MaterialBase>();
	}
	mud::MaterialBase* DECL mud_MaterialBase__construct_0() {
		return new mud::MaterialBase();
	}
	mud::BlendMode DECL mud_MaterialBase__get_blend_mode(mud::MaterialBase* self) {
		return self->m_blend_mode;
	}
	void DECL mud_MaterialBase__set_blend_mode(mud::MaterialBase* self, mud::BlendMode value) {
		self->m_blend_mode = value;
	}
	mud::CullMode DECL mud_MaterialBase__get_cull_mode(mud::MaterialBase* self) {
		return self->m_cull_mode;
	}
	void DECL mud_MaterialBase__set_cull_mode(mud::MaterialBase* self, mud::CullMode value) {
		self->m_cull_mode = value;
	}
	mud::DepthDraw DECL mud_MaterialBase__get_depth_draw(mud::MaterialBase* self) {
		return self->m_depth_draw;
	}
	void DECL mud_MaterialBase__set_depth_draw(mud::MaterialBase* self, mud::DepthDraw value) {
		self->m_depth_draw = value;
	}
	mud::DepthTest DECL mud_MaterialBase__get_depth_test(mud::MaterialBase* self) {
		return self->m_depth_test;
	}
	void DECL mud_MaterialBase__set_depth_test(mud::MaterialBase* self, mud::DepthTest value) {
		self->m_depth_test = value;
	}
	mud::vec2* DECL mud_MaterialBase__get_uv0_scale(mud::MaterialBase* self) {
		return &self->m_uv0_scale;
	}
	void DECL mud_MaterialBase__set_uv0_scale(mud::MaterialBase* self, mud::vec2* value) {
		self->m_uv0_scale = *value;
	}
	mud::vec2* DECL mud_MaterialBase__get_uv0_offset(mud::MaterialBase* self) {
		return &self->m_uv0_offset;
	}
	void DECL mud_MaterialBase__set_uv0_offset(mud::MaterialBase* self, mud::vec2* value) {
		self->m_uv0_offset = *value;
	}
	mud::vec2* DECL mud_MaterialBase__get_uv1_scale(mud::MaterialBase* self) {
		return &self->m_uv1_scale;
	}
	void DECL mud_MaterialBase__set_uv1_scale(mud::MaterialBase* self, mud::vec2* value) {
		self->m_uv1_scale = *value;
	}
	mud::vec2* DECL mud_MaterialBase__get_uv1_offset(mud::MaterialBase* self) {
		return &self->m_uv1_offset;
	}
	void DECL mud_MaterialBase__set_uv1_offset(mud::MaterialBase* self, mud::vec2* value) {
		self->m_uv1_offset = *value;
	}
	mud::ShaderColor DECL mud_MaterialBase__get_shader_color(mud::MaterialBase* self) {
		return self->m_shader_color;
	}
	void DECL mud_MaterialBase__set_shader_color(mud::MaterialBase* self, mud::ShaderColor value) {
		self->m_shader_color = value;
	}
	bool DECL mud_MaterialBase__get_screen_filter(mud::MaterialBase* self) {
		return self->m_screen_filter;
	}
	void DECL mud_MaterialBase__set_screen_filter(mud::MaterialBase* self, bool value) {
		self->m_screen_filter = value;
	}
	float DECL mud_MaterialBase__get_anisotropy(mud::MaterialBase* self) {
		return self->m_anisotropy;
	}
	void DECL mud_MaterialBase__set_anisotropy(mud::MaterialBase* self, float value) {
		self->m_anisotropy = value;
	}
	void DECL mud_MaterialBase__destroy(mud::MaterialBase* self) {
		delete self;
	}
	// MaterialFresnel
	mud::Type* DECL mud_MaterialFresnel__type() {
		return &mud::type<mud::MaterialFresnel>();
	}
	mud::MaterialFresnel* DECL mud_MaterialFresnel__construct_0() {
		return new mud::MaterialFresnel();
	}
	mud::MaterialParam<mud::Colour>* DECL mud_MaterialFresnel__get_value(mud::MaterialFresnel* self) {
		return &self->m_value;
	}
	void DECL mud_MaterialFresnel__set_value(mud::MaterialFresnel* self, mud::MaterialParam<mud::Colour>* value) {
		self->m_value = *value;
	}
	float DECL mud_MaterialFresnel__get_fresnel_scale(mud::MaterialFresnel* self) {
		return self->m_fresnel_scale;
	}
	void DECL mud_MaterialFresnel__set_fresnel_scale(mud::MaterialFresnel* self, float value) {
		self->m_fresnel_scale = value;
	}
	float DECL mud_MaterialFresnel__get_fresnel_bias(mud::MaterialFresnel* self) {
		return self->m_fresnel_bias;
	}
	void DECL mud_MaterialFresnel__set_fresnel_bias(mud::MaterialFresnel* self, float value) {
		self->m_fresnel_bias = value;
	}
	float DECL mud_MaterialFresnel__get_fresnel_power(mud::MaterialFresnel* self) {
		return self->m_fresnel_power;
	}
	void DECL mud_MaterialFresnel__set_fresnel_power(mud::MaterialFresnel* self, float value) {
		self->m_fresnel_power = value;
	}
	void DECL mud_MaterialFresnel__destroy(mud::MaterialFresnel* self) {
		delete self;
	}
	// MaterialLine
	mud::Type* DECL mud_MaterialLine__type() {
		return &mud::type<mud::MaterialLine>();
	}
	mud::MaterialLine* DECL mud_MaterialLine__construct_0() {
		return new mud::MaterialLine();
	}
	float DECL mud_MaterialLine__get_line_width(mud::MaterialLine* self) {
		return self->m_line_width;
	}
	void DECL mud_MaterialLine__set_line_width(mud::MaterialLine* self, float value) {
		self->m_line_width = value;
	}
	bool DECL mud_MaterialLine__get_dashed(mud::MaterialLine* self) {
		return self->m_dashed;
	}
	void DECL mud_MaterialLine__set_dashed(mud::MaterialLine* self, bool value) {
		self->m_dashed = value;
	}
	float DECL mud_MaterialLine__get_dash_scale(mud::MaterialLine* self) {
		return self->m_dash_scale;
	}
	void DECL mud_MaterialLine__set_dash_scale(mud::MaterialLine* self, float value) {
		self->m_dash_scale = value;
	}
	float DECL mud_MaterialLine__get_dash_size(mud::MaterialLine* self) {
		return self->m_dash_size;
	}
	void DECL mud_MaterialLine__set_dash_size(mud::MaterialLine* self, float value) {
		self->m_dash_size = value;
	}
	float DECL mud_MaterialLine__get_dash_gap(mud::MaterialLine* self) {
		return self->m_dash_gap;
	}
	void DECL mud_MaterialLine__set_dash_gap(mud::MaterialLine* self, float value) {
		self->m_dash_gap = value;
	}
	void DECL mud_MaterialLine__destroy(mud::MaterialLine* self) {
		delete self;
	}
	// MaterialParam<float>
	mud::Type* DECL mud_MaterialParam_float__type() {
		return &mud::type<mud::MaterialParam<float>>();
	}
	mud::MaterialParam<float>* DECL mud_MaterialParam_float__construct_0() {
		return new mud::MaterialParam<float>();
	}
	float DECL mud_MaterialParam_float__get_value(mud::MaterialParam<float>* self) {
		return self->m_value;
	}
	void DECL mud_MaterialParam_float__set_value(mud::MaterialParam<float>* self, float value) {
		self->m_value = value;
	}
	mud::Texture* DECL mud_MaterialParam_float__get_texture(mud::MaterialParam<float>* self) {
		return self->m_texture;
	}
	void DECL mud_MaterialParam_float__set_texture(mud::MaterialParam<float>* self, mud::Texture* value) {
		self->m_texture = value;
	}
	mud::TextureChannel DECL mud_MaterialParam_float__get_channel(mud::MaterialParam<float>* self) {
		return self->m_channel;
	}
	void DECL mud_MaterialParam_float__set_channel(mud::MaterialParam<float>* self, mud::TextureChannel value) {
		self->m_channel = value;
	}
	void DECL mud_MaterialParam_float__destroy(mud::MaterialParam<float>* self) {
		delete self;
	}
	// MaterialParam<mud::Colour>
	mud::Type* DECL mud_MaterialParam_mud_Colour__type() {
		return &mud::type<mud::MaterialParam<mud::Colour>>();
	}
	mud::MaterialParam<mud::Colour>* DECL mud_MaterialParam_mud_Colour__construct_0() {
		return new mud::MaterialParam<mud::Colour>();
	}
	mud::Colour* DECL mud_MaterialParam_mud_Colour__get_value(mud::MaterialParam<mud::Colour>* self) {
		return &self->m_value;
	}
	void DECL mud_MaterialParam_mud_Colour__set_value(mud::MaterialParam<mud::Colour>* self, mud::Colour* value) {
		self->m_value = *value;
	}
	mud::Texture* DECL mud_MaterialParam_mud_Colour__get_texture(mud::MaterialParam<mud::Colour>* self) {
		return self->m_texture;
	}
	void DECL mud_MaterialParam_mud_Colour__set_texture(mud::MaterialParam<mud::Colour>* self, mud::Texture* value) {
		self->m_texture = value;
	}
	mud::TextureChannel DECL mud_MaterialParam_mud_Colour__get_channel(mud::MaterialParam<mud::Colour>* self) {
		return self->m_channel;
	}
	void DECL mud_MaterialParam_mud_Colour__set_channel(mud::MaterialParam<mud::Colour>* self, mud::TextureChannel value) {
		self->m_channel = value;
	}
	void DECL mud_MaterialParam_mud_Colour__destroy(mud::MaterialParam<mud::Colour>* self) {
		delete self;
	}
	// MaterialParam<mud::vec4>
	mud::Type* DECL mud_MaterialParam_mud_vec4__type() {
		return &mud::type<mud::MaterialParam<mud::vec4>>();
	}
	mud::MaterialParam<mud::vec4>* DECL mud_MaterialParam_mud_vec4__construct_0() {
		return new mud::MaterialParam<mud::vec4>();
	}
	mud::vec4* DECL mud_MaterialParam_mud_vec4__get_value(mud::MaterialParam<mud::vec4>* self) {
		return &self->m_value;
	}
	void DECL mud_MaterialParam_mud_vec4__set_value(mud::MaterialParam<mud::vec4>* self, mud::vec4* value) {
		self->m_value = *value;
	}
	mud::Texture* DECL mud_MaterialParam_mud_vec4__get_texture(mud::MaterialParam<mud::vec4>* self) {
		return self->m_texture;
	}
	void DECL mud_MaterialParam_mud_vec4__set_texture(mud::MaterialParam<mud::vec4>* self, mud::Texture* value) {
		self->m_texture = value;
	}
	mud::TextureChannel DECL mud_MaterialParam_mud_vec4__get_channel(mud::MaterialParam<mud::vec4>* self) {
		return self->m_channel;
	}
	void DECL mud_MaterialParam_mud_vec4__set_channel(mud::MaterialParam<mud::vec4>* self, mud::TextureChannel value) {
		self->m_channel = value;
	}
	void DECL mud_MaterialParam_mud_vec4__destroy(mud::MaterialParam<mud::vec4>* self) {
		delete self;
	}
	// MaterialPbr
	mud::Type* DECL mud_MaterialPbr__type() {
		return &mud::type<mud::MaterialPbr>();
	}
	mud::MaterialPbr* DECL mud_MaterialPbr__construct_0() {
		return new mud::MaterialPbr();
	}
	mud::MaterialPbr* DECL mud_MaterialPbr__construct_1(const mud::Colour* albedo) {
		return new mud::MaterialPbr(*albedo);
	}
	mud::MaterialPbr* DECL mud_MaterialPbr__construct_2(const mud::Colour* albedo, float metallic) {
		return new mud::MaterialPbr(*albedo, metallic);
	}
	mud::MaterialPbr* DECL mud_MaterialPbr__construct_3(const mud::Colour* albedo, float metallic, float roughness) {
		return new mud::MaterialPbr(*albedo, metallic, roughness);
	}
	mud::MaterialParam<mud::Colour>* DECL mud_MaterialPbr__get_albedo(mud::MaterialPbr* self) {
		return &self->m_albedo;
	}
	void DECL mud_MaterialPbr__set_albedo(mud::MaterialPbr* self, mud::MaterialParam<mud::Colour>* value) {
		self->m_albedo = *value;
	}
	float DECL mud_MaterialPbr__get_specular(mud::MaterialPbr* self) {
		return self->m_specular;
	}
	void DECL mud_MaterialPbr__set_specular(mud::MaterialPbr* self, float value) {
		self->m_specular = value;
	}
	mud::MaterialParam<float>* DECL mud_MaterialPbr__get_metallic(mud::MaterialPbr* self) {
		return &self->m_metallic;
	}
	void DECL mud_MaterialPbr__set_metallic(mud::MaterialPbr* self, mud::MaterialParam<float>* value) {
		self->m_metallic = *value;
	}
	mud::MaterialParam<float>* DECL mud_MaterialPbr__get_roughness(mud::MaterialPbr* self) {
		return &self->m_roughness;
	}
	void DECL mud_MaterialPbr__set_roughness(mud::MaterialPbr* self, mud::MaterialParam<float>* value) {
		self->m_roughness = *value;
	}
	mud::MaterialParam<float>* DECL mud_MaterialPbr__get_normal(mud::MaterialPbr* self) {
		return &self->m_normal;
	}
	void DECL mud_MaterialPbr__set_normal(mud::MaterialPbr* self, mud::MaterialParam<float>* value) {
		self->m_normal = *value;
	}
	mud::MaterialParam<mud::Colour>* DECL mud_MaterialPbr__get_emissive(mud::MaterialPbr* self) {
		return &self->m_emissive;
	}
	void DECL mud_MaterialPbr__set_emissive(mud::MaterialPbr* self, mud::MaterialParam<mud::Colour>* value) {
		self->m_emissive = *value;
	}
	float DECL mud_MaterialPbr__get_emissive_energy(mud::MaterialPbr* self) {
		return self->m_emissive_energy;
	}
	void DECL mud_MaterialPbr__set_emissive_energy(mud::MaterialPbr* self, float value) {
		self->m_emissive_energy = value;
	}
	mud::MaterialParam<float>* DECL mud_MaterialPbr__get_rim(mud::MaterialPbr* self) {
		return &self->m_rim;
	}
	void DECL mud_MaterialPbr__set_rim(mud::MaterialPbr* self, mud::MaterialParam<float>* value) {
		self->m_rim = *value;
	}
	float DECL mud_MaterialPbr__get_ritint(mud::MaterialPbr* self) {
		return self->m_rim_tint;
	}
	void DECL mud_MaterialPbr__set_ritint(mud::MaterialPbr* self, float value) {
		self->m_rim_tint = value;
	}
	mud::MaterialParam<float>* DECL mud_MaterialPbr__get_clearcoat(mud::MaterialPbr* self) {
		return &self->m_clearcoat;
	}
	void DECL mud_MaterialPbr__set_clearcoat(mud::MaterialPbr* self, mud::MaterialParam<float>* value) {
		self->m_clearcoat = *value;
	}
	float DECL mud_MaterialPbr__get_clearcoat_gloss(mud::MaterialPbr* self) {
		return self->m_clearcoat_gloss;
	}
	void DECL mud_MaterialPbr__set_clearcoat_gloss(mud::MaterialPbr* self, float value) {
		self->m_clearcoat_gloss = value;
	}
	mud::MaterialParam<float>* DECL mud_MaterialPbr__get_anisotropy(mud::MaterialPbr* self) {
		return &self->m_anisotropy;
	}
	void DECL mud_MaterialPbr__set_anisotropy(mud::MaterialPbr* self, mud::MaterialParam<float>* value) {
		self->m_anisotropy = *value;
	}
	mud::MaterialParam<float>* DECL mud_MaterialPbr__get_subsurface(mud::MaterialPbr* self) {
		return &self->m_subsurface;
	}
	void DECL mud_MaterialPbr__set_subsurface(mud::MaterialPbr* self, mud::MaterialParam<float>* value) {
		self->m_subsurface = *value;
	}
	mud::MaterialParam<float>* DECL mud_MaterialPbr__get_refraction(mud::MaterialPbr* self) {
		return &self->m_refraction;
	}
	void DECL mud_MaterialPbr__set_refraction(mud::MaterialPbr* self, mud::MaterialParam<float>* value) {
		self->m_refraction = *value;
	}
	mud::MaterialParam<float>* DECL mud_MaterialPbr__get_depth(mud::MaterialPbr* self) {
		return &self->m_depth;
	}
	void DECL mud_MaterialPbr__set_depth(mud::MaterialPbr* self, mud::MaterialParam<float>* value) {
		self->m_depth = *value;
	}
	mud::MaterialParam<float>* DECL mud_MaterialPbr__get_ambient_occlusion(mud::MaterialPbr* self) {
		return &self->m_ambient_occlusion;
	}
	void DECL mud_MaterialPbr__set_ambient_occlusion(mud::MaterialPbr* self, mud::MaterialParam<float>* value) {
		self->m_ambient_occlusion = *value;
	}
	mud::MaterialParam<mud::Colour>* DECL mud_MaterialPbr__get_transmission(mud::MaterialPbr* self) {
		return &self->m_transmission;
	}
	void DECL mud_MaterialPbr__set_transmission(mud::MaterialPbr* self, mud::MaterialParam<mud::Colour>* value) {
		self->m_transmission = *value;
	}
	bool DECL mud_MaterialPbr__get_deep_parallax(mud::MaterialPbr* self) {
		return self->m_deep_parallax;
	}
	void DECL mud_MaterialPbr__set_deep_parallax(mud::MaterialPbr* self, bool value) {
		self->m_deep_parallax = value;
	}
	bool DECL mud_MaterialPbr__get_scene_environment(mud::MaterialPbr* self) {
		return self->m_scene_environment;
	}
	void DECL mud_MaterialPbr__set_scene_environment(mud::MaterialPbr* self, bool value) {
		self->m_scene_environment = value;
	}
	mud::PbrDiffuseMode DECL mud_MaterialPbr__get_diffuse_mode(mud::MaterialPbr* self) {
		return self->m_diffuse_mode;
	}
	void DECL mud_MaterialPbr__set_diffuse_mode(mud::MaterialPbr* self, mud::PbrDiffuseMode value) {
		self->m_diffuse_mode = value;
	}
	mud::PbrSpecularMode DECL mud_MaterialPbr__get_specular_mode(mud::MaterialPbr* self) {
		return self->m_specular_mode;
	}
	void DECL mud_MaterialPbr__set_specular_mode(mud::MaterialPbr* self, mud::PbrSpecularMode value) {
		self->m_specular_mode = value;
	}
	void DECL mud_MaterialPbr__destroy(mud::MaterialPbr* self) {
		delete self;
	}
	// MaterialPoint
	mud::Type* DECL mud_MaterialPoint__type() {
		return &mud::type<mud::MaterialPoint>();
	}
	mud::MaterialPoint* DECL mud_MaterialPoint__construct_0() {
		return new mud::MaterialPoint();
	}
	float DECL mud_MaterialPoint__get_point_size(mud::MaterialPoint* self) {
		return self->m_point_size;
	}
	void DECL mud_MaterialPoint__set_point_size(mud::MaterialPoint* self, float value) {
		self->m_point_size = value;
	}
	bool DECL mud_MaterialPoint__get_project(mud::MaterialPoint* self) {
		return self->m_project;
	}
	void DECL mud_MaterialPoint__set_project(mud::MaterialPoint* self, bool value) {
		self->m_project = value;
	}
	void DECL mud_MaterialPoint__destroy(mud::MaterialPoint* self) {
		delete self;
	}
	// MaterialSolid
	mud::Type* DECL mud_MaterialSolid__type() {
		return &mud::type<mud::MaterialSolid>();
	}
	mud::MaterialSolid* DECL mud_MaterialSolid__construct_0() {
		return new mud::MaterialSolid();
	}
	mud::MaterialParam<mud::Colour>* DECL mud_MaterialSolid__get_colour(mud::MaterialSolid* self) {
		return &self->m_colour;
	}
	void DECL mud_MaterialSolid__set_colour(mud::MaterialSolid* self, mud::MaterialParam<mud::Colour>* value) {
		self->m_colour = *value;
	}
	void DECL mud_MaterialSolid__destroy(mud::MaterialSolid* self) {
		delete self;
	}
	// MaterialUser
	mud::Type* DECL mud_MaterialUser__type() {
		return &mud::type<mud::MaterialUser>();
	}
	mud::MaterialUser* DECL mud_MaterialUser__construct_0() {
		return new mud::MaterialUser();
	}
	mud::MaterialParam<mud::vec4>* DECL mud_MaterialUser__get_attr0(mud::MaterialUser* self) {
		return &self->m_attr0;
	}
	void DECL mud_MaterialUser__set_attr0(mud::MaterialUser* self, mud::MaterialParam<mud::vec4>* value) {
		self->m_attr0 = *value;
	}
	mud::MaterialParam<mud::vec4>* DECL mud_MaterialUser__get_attr1(mud::MaterialUser* self) {
		return &self->m_attr1;
	}
	void DECL mud_MaterialUser__set_attr1(mud::MaterialUser* self, mud::MaterialParam<mud::vec4>* value) {
		self->m_attr1 = *value;
	}
	mud::MaterialParam<mud::vec4>* DECL mud_MaterialUser__get_attr2(mud::MaterialUser* self) {
		return &self->m_attr2;
	}
	void DECL mud_MaterialUser__set_attr2(mud::MaterialUser* self, mud::MaterialParam<mud::vec4>* value) {
		self->m_attr2 = *value;
	}
	mud::MaterialParam<mud::vec4>* DECL mud_MaterialUser__get_attr3(mud::MaterialUser* self) {
		return &self->m_attr3;
	}
	void DECL mud_MaterialUser__set_attr3(mud::MaterialUser* self, mud::MaterialParam<mud::vec4>* value) {
		self->m_attr3 = *value;
	}
	void DECL mud_MaterialUser__destroy(mud::MaterialUser* self) {
		delete self;
	}
	// Mesh
	mud::Type* DECL mud_Mesh__type() {
		return &mud::type<mud::Mesh>();
	}
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
	mud::PrimitiveType DECL mud_Mesh__get_primitive(mud::Mesh* self) {
		return self->m_primitive;
	}
	void DECL mud_Mesh__set_primitive(mud::Mesh* self, mud::PrimitiveType value) {
		self->m_primitive = value;
	}
	mud::Aabb* DECL mud_Mesh__get_aabb(mud::Mesh* self) {
		return &self->m_aabb;
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
		return &self->m_origin;
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
	bool DECL mud_Mesh__get_is_dynamic(mud::Mesh* self) {
		return self->m_is_dynamic;
	}
	void DECL mud_Mesh__set_is_dynamic(mud::Mesh* self, bool value) {
		self->m_is_dynamic = value;
	}
	bool DECL mud_Mesh__get_is_direct(mud::Mesh* self) {
		return self->m_is_direct;
	}
	void DECL mud_Mesh__set_is_direct(mud::Mesh* self, bool value) {
		self->m_is_direct = value;
	}
	void DECL mud_Mesh__destroy(mud::Mesh* self) {
		delete self;
	}
	// Mime
	mud::Type* DECL mud_Mime__type() {
		return &mud::type<mud::Mime>();
	}
	void DECL mud_Mime_start_2(mud::Mime* self, const char* animation, bool loop) {
		self->start(animation, loop);
	}
	void DECL mud_Mime_start_3(mud::Mime* self, const char* animation, bool loop, float blend) {
		self->start(animation, loop, blend);
	}
	void DECL mud_Mime_start_4(mud::Mime* self, const char* animation, bool loop, float blend, float speed) {
		self->start(animation, loop, blend, speed);
	}
	void DECL mud_Mime_start_5(mud::Mime* self, const char* animation, bool loop, float blend, float speed, bool transient) {
		self->start(animation, loop, blend, speed, transient);
	}
	void DECL mud_Mime_play_2(mud::Mime* self, const mud::Animation* animation, bool loop) {
		self->play(*animation, loop);
	}
	void DECL mud_Mime_play_3(mud::Mime* self, const mud::Animation* animation, bool loop, float blend) {
		self->play(*animation, loop, blend);
	}
	void DECL mud_Mime_play_4(mud::Mime* self, const mud::Animation* animation, bool loop, float blend, float speed) {
		self->play(*animation, loop, blend, speed);
	}
	void DECL mud_Mime_play_5(mud::Mime* self, const mud::Animation* animation, bool loop, float blend, float speed, bool transient) {
		self->play(*animation, loop, blend, speed, transient);
	}
	void DECL mud_Mime_seek_1(mud::Mime* self, float time) {
		self->seek(time);
	}
	void DECL mud_Mime_pause_0(mud::Mime* self) {
		self->pause();
	}
	void DECL mud_Mime_stop_0(mud::Mime* self) {
		self->stop();
	}
	void DECL mud_Mime_advance_1(mud::Mime* self, float time) {
		self->advance(time);
	}
	void DECL mud_Mime_next_animation_0(mud::Mime* self) {
		self->next_animation();
	}
	const char* DECL mud_Mime_playing_0(mud::Mime* self) {
		return self->playing().c_str();
	}
	bool DECL mud_Mime__get_active(mud::Mime* self) {
		return self->m_active;
	}
	void DECL mud_Mime__set_active(mud::Mime* self, bool value) {
		self->m_active = value;
	}
	float DECL mud_Mime__get_speed_scale(mud::Mime* self) {
		return self->m_speed_scale;
	}
	void DECL mud_Mime__set_speed_scale(mud::Mime* self, float value) {
		self->m_speed_scale = value;
	}
	float DECL mud_Mime__get_default_blend_time(mud::Mime* self) {
		return self->m_default_blend_time;
	}
	void DECL mud_Mime__set_default_blend_time(mud::Mime* self, float value) {
		self->m_default_blend_time = value;
	}
	void DECL mud_Mime__destroy(mud::Mime* self) {
		delete self;
	}
	// Model
	mud::Type* DECL mud_Model__type() {
		return &mud::type<mud::Model>();
	}
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
		return &self->m_aabb;
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
		return &self->m_origin;
	}
	void DECL mud_Model__set_origin(mud::Model* self, mud::vec3* value) {
		self->m_origin = *value;
	}
	void DECL mud_Model__destroy(mud::Model* self) {
		delete self;
	}
	// ModelItem
	mud::Type* DECL mud_ModelItem__type() {
		return &mud::type<mud::ModelItem>();
	}
	mud::ModelItem* DECL mud_ModelItem__construct_0() {
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
		return &self->m_transform;
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
		return &self->m_colour;
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
	mud::Type* DECL mud_Node3__type() {
		return &mud::type<mud::Node3>();
	}
	mud::Node3* DECL mud_Node3__construct_0() {
		return new mud::Node3();
	}
	mud::Node3* DECL mud_Node3__construct_1(const mud::mat4* transform) {
		return new mud::Node3(*transform);
	}
	mud::Node3* DECL mud_Node3__construct_2(const mud::vec3* position, const mud::quat* rotation) {
		return new mud::Node3(*position, *rotation);
	}
	mud::Node3* DECL mud_Node3__construct_3(const mud::vec3* position, const mud::quat* rotation, const mud::vec3* scale) {
		return new mud::Node3(*position, *rotation, *scale);
	}
	void DECL mud_Node3_apply_1(mud::Node3* self, const mud::vec3* position) {
		self->apply(*position);
	}
	void DECL mud_Node3_apply_2(mud::Node3* self, const mud::vec3* position, const mud::quat* rotation) {
		self->apply(*position, *rotation);
	}
	void DECL mud_Node3_apply_3(mud::Node3* self, const mud::vec3* position, const mud::quat* rotation, const mud::vec3* scale) {
		self->apply(*position, *rotation, *scale);
	}
	void DECL mud_Node3_derive_2(mud::Node3* self, const mud::Node3* parent, const mud::vec3* position) {
		self->derive(*parent, *position);
	}
	void DECL mud_Node3_derive_3(mud::Node3* self, const mud::Node3* parent, const mud::vec3* position, const mud::quat* rotation) {
		self->derive(*parent, *position, *rotation);
	}
	void DECL mud_Node3_derive_4(mud::Node3* self, const mud::Node3* parent, const mud::vec3* position, const mud::quat* rotation, const mud::vec3* scale) {
		self->derive(*parent, *position, *rotation, *scale);
	}
	mud::vec3* DECL mud_Node3_position_0(mud::Node3* self) {
		static mud::vec3 temp;
		return (temp = self->position(), &temp);
	}
	mud::vec3* DECL mud_Node3_axis_1(mud::Node3* self, const mud::vec3* dir) {
		static mud::vec3 temp;
		return (temp = self->axis(*dir), &temp);
	}
	mud::vec3* DECL mud_Node3_direction_0(mud::Node3* self) {
		static mud::vec3 temp;
		return (temp = self->direction(), &temp);
	}
	uint16_t DECL mud_Node3__get_index(mud::Node3* self) {
		return self->m_index;
	}
	void DECL mud_Node3__set_index(mud::Node3* self, uint16_t value) {
		self->m_index = value;
	}
	mud::mat4* DECL mud_Node3__get_transform(mud::Node3* self) {
		return &self->m_transform;
	}
	void DECL mud_Node3__set_transform(mud::Node3* self, mud::mat4* value) {
		self->m_transform = *value;
	}
	void DECL mud_Node3__destroy(mud::Node3* self) {
		delete self;
	}
	// Prefab
	mud::Type* DECL mud_Prefab__type() {
		return &mud::type<mud::Prefab>();
	}
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
	mud::Type* DECL mud_Program__type() {
		return &mud::type<mud::Program>();
	}
	void DECL mud_Program_set_block_1(mud::Program* self, mud::MaterialBlock block) {
		self->set_block(block);
	}
	void DECL mud_Program_set_block_2(mud::Program* self, mud::MaterialBlock block, bool enabled) {
		self->set_block(block, enabled);
	}
	void DECL mud_Program_set_source_2(mud::Program* self, mud::ShaderType type, const char* source) {
		self->set_source(type, source);
	}
	const char* DECL mud_Program__get_name(mud::Program* self) {
		return self->m_name.c_str();
	}
	void DECL mud_Program__set_name(mud::Program* self, const char* value) {
		self->m_name = value;
	}
	void DECL mud_Program__destroy(mud::Program* self) {
		delete self;
	}
	// Radiance
	mud::Type* DECL mud_Radiance__type() {
		return &mud::type<mud::Radiance>();
	}
	mud::Radiance* DECL mud_Radiance__construct_0() {
		return new mud::Radiance();
	}
	mud::Colour* DECL mud_Radiance__get_colour(mud::Radiance* self) {
		return &self->m_colour;
	}
	void DECL mud_Radiance__set_colour(mud::Radiance* self, mud::Colour* value) {
		self->m_colour = *value;
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
	mud::Type* DECL mud_RenderFrame__type() {
		return &mud::type<mud::RenderFrame>();
	}
	mud::RenderFrame* DECL mud_RenderFrame__construct_0() {
		return new mud::RenderFrame();
	}
	void DECL mud_RenderFrame__destroy(mud::RenderFrame* self) {
		delete self;
	}
	// RenderQuad
	mud::Type* DECL mud_RenderQuad__type() {
		return &mud::type<mud::RenderQuad>();
	}
	mud::RenderQuad* DECL mud_RenderQuad__construct_0() {
		return new mud::RenderQuad();
	}
	void DECL mud_RenderQuad__destroy(mud::RenderQuad* self) {
		delete self;
	}
	// Rig
	mud::Type* DECL mud_Rig__type() {
		return &mud::type<mud::Rig>();
	}
	void DECL mud_Rig__destroy(mud::Rig* self) {
		delete self;
	}
	// Scene
	mud::Type* DECL mud_Scene__type() {
		return &mud::type<mud::Scene>();
	}
	mud::Scene* DECL mud_Scene__construct_1(mud::GfxSystem* gfx) {
		return new mud::Scene(*gfx);
	}
	mud::Gnode* DECL mud_Scene_begin_0(mud::Scene* self) {
		return &self->begin();
	}
	mud::TPool<mud::Node3>* DECL mud_Scene_nodes_0(mud::Scene* self) {
		return &mud::gfx::nodes(*self);
	}
	mud::TPool<mud::Item>* DECL mud_Scene_items_0(mud::Scene* self) {
		return &mud::gfx::items(*self);
	}
	mud::TPool<mud::Batch>* DECL mud_Scene_batches_0(mud::Scene* self) {
		return &mud::gfx::batches(*self);
	}
	mud::TPool<mud::Direct>* DECL mud_Scene_directs_0(mud::Scene* self) {
		return &mud::gfx::directs(*self);
	}
	mud::TPool<mud::Mime>* DECL mud_Scene_mimes_0(mud::Scene* self) {
		return &mud::gfx::mimes(*self);
	}
	mud::TPool<mud::Light>* DECL mud_Scene_lights_0(mud::Scene* self) {
		return &mud::gfx::lights(*self);
	}
	mud::TPool<mud::Flare>* DECL mud_Scene_flares_0(mud::Scene* self) {
		return &mud::gfx::flares(*self);
	}
	mud::Gnode* DECL mud_Scene__get_graph(mud::Scene* self) {
		return &self->m_graph;
	}
	mud::Node3* DECL mud_Scene__get_root_node(mud::Scene* self) {
		return &self->m_root_node;
	}
	mud::Zone* DECL mud_Scene__get_env(mud::Scene* self) {
		return &self->m_env;
	}
	void DECL mud_Scene__set_env(mud::Scene* self, mud::Zone* value) {
		self->m_env = *value;
	}
	mud::Ref* DECL mud_Scene__get_user(mud::Scene* self) {
		return &self->m_user;
	}
	void DECL mud_Scene__set_user(mud::Scene* self, mud::Ref* value) {
		self->m_user = *value;
	}
	void DECL mud_Scene__destroy(mud::Scene* self) {
		delete self;
	}
	// Shot
	mud::Type* DECL mud_Shot__type() {
		return &mud::type<mud::Shot>();
	}
	void DECL mud_Shot__destroy(mud::Shot* self) {
		delete self;
	}
	// Skeleton
	mud::Type* DECL mud_Skeleton__type() {
		return &mud::type<mud::Skeleton>();
	}
	void DECL mud_Skeleton__destroy(mud::Skeleton* self) {
		delete self;
	}
	// Skin
	mud::Type* DECL mud_Skin__type() {
		return &mud::type<mud::Skin>();
	}
	void DECL mud_Skin__destroy(mud::Skin* self) {
		delete self;
	}
	// Sun
	mud::Type* DECL mud_Sun__type() {
		return &mud::type<mud::Sun>();
	}
	mud::Sun* DECL mud_Sun__construct_0() {
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
		return &self->m_colour;
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
	mud::Type* DECL mud_SymbolIndex__type() {
		return &mud::type<mud::SymbolIndex>();
	}
	void DECL mud_SymbolIndex__destroy(mud::SymbolIndex* self) {
		delete self;
	}
	// TPool<mud::Batch>
	mud::Type* DECL mud_TPool_mud_Batch__type() {
		return &mud::type<mud::TPool<mud::Batch>>();
	}
	mud::Batch* DECL mud_TPool_mud_Batch_add_1(mud::TPool<mud::Batch>* self, const mud::Batch* value) {
		return &self->add(*value);
	}
	mud::Batch* DECL mud_TPool_mud_Batch_talloc_0(mud::TPool<mud::Batch>* self) {
		return self->talloc();
	}
	void DECL mud_TPool_mud_Batch_tdestroy_1(mud::TPool<mud::Batch>* self, mud::Batch* object) {
		self->tdestroy(*object);
	}
	void DECL mud_TPool_mud_Batch_tfree_1(mud::TPool<mud::Batch>* self, mud::Batch* object) {
		self->tfree(*object);
	}
	void DECL mud_TPool_mud_Batch__destroy(mud::TPool<mud::Batch>* self) {
		delete self;
	}
	// TPool<mud::Direct>
	mud::Type* DECL mud_TPool_mud_Direct__type() {
		return &mud::type<mud::TPool<mud::Direct>>();
	}
	mud::Direct* DECL mud_TPool_mud_Direct_add_1(mud::TPool<mud::Direct>* self, const mud::Direct* value) {
		return &self->add(*value);
	}
	mud::Direct* DECL mud_TPool_mud_Direct_talloc_0(mud::TPool<mud::Direct>* self) {
		return self->talloc();
	}
	void DECL mud_TPool_mud_Direct_tdestroy_1(mud::TPool<mud::Direct>* self, mud::Direct* object) {
		self->tdestroy(*object);
	}
	void DECL mud_TPool_mud_Direct_tfree_1(mud::TPool<mud::Direct>* self, mud::Direct* object) {
		self->tfree(*object);
	}
	void DECL mud_TPool_mud_Direct__destroy(mud::TPool<mud::Direct>* self) {
		delete self;
	}
	// TPool<mud::Flare>
	mud::Type* DECL mud_TPool_mud_Flare__type() {
		return &mud::type<mud::TPool<mud::Flare>>();
	}
	mud::Flare* DECL mud_TPool_mud_Flare_add_1(mud::TPool<mud::Flare>* self, const mud::Flare* value) {
		return &self->add(*value);
	}
	mud::Flare* DECL mud_TPool_mud_Flare_talloc_0(mud::TPool<mud::Flare>* self) {
		return self->talloc();
	}
	void DECL mud_TPool_mud_Flare_tdestroy_1(mud::TPool<mud::Flare>* self, mud::Flare* object) {
		self->tdestroy(*object);
	}
	void DECL mud_TPool_mud_Flare_tfree_1(mud::TPool<mud::Flare>* self, mud::Flare* object) {
		self->tfree(*object);
	}
	void DECL mud_TPool_mud_Flare__destroy(mud::TPool<mud::Flare>* self) {
		delete self;
	}
	// TPool<mud::Item>
	mud::Type* DECL mud_TPool_mud_Item__type() {
		return &mud::type<mud::TPool<mud::Item>>();
	}
	mud::Item* DECL mud_TPool_mud_Item_add_1(mud::TPool<mud::Item>* self, const mud::Item* value) {
		return &self->add(*value);
	}
	mud::Item* DECL mud_TPool_mud_Item_talloc_0(mud::TPool<mud::Item>* self) {
		return self->talloc();
	}
	void DECL mud_TPool_mud_Item_tdestroy_1(mud::TPool<mud::Item>* self, mud::Item* object) {
		self->tdestroy(*object);
	}
	void DECL mud_TPool_mud_Item_tfree_1(mud::TPool<mud::Item>* self, mud::Item* object) {
		self->tfree(*object);
	}
	void DECL mud_TPool_mud_Item__destroy(mud::TPool<mud::Item>* self) {
		delete self;
	}
	// TPool<mud::Light>
	mud::Type* DECL mud_TPool_mud_Light__type() {
		return &mud::type<mud::TPool<mud::Light>>();
	}
	mud::Light* DECL mud_TPool_mud_Light_add_1(mud::TPool<mud::Light>* self, const mud::Light* value) {
		return &self->add(*value);
	}
	mud::Light* DECL mud_TPool_mud_Light_talloc_0(mud::TPool<mud::Light>* self) {
		return self->talloc();
	}
	void DECL mud_TPool_mud_Light_tdestroy_1(mud::TPool<mud::Light>* self, mud::Light* object) {
		self->tdestroy(*object);
	}
	void DECL mud_TPool_mud_Light_tfree_1(mud::TPool<mud::Light>* self, mud::Light* object) {
		self->tfree(*object);
	}
	void DECL mud_TPool_mud_Light__destroy(mud::TPool<mud::Light>* self) {
		delete self;
	}
	// TPool<mud::Mime>
	mud::Type* DECL mud_TPool_mud_Mime__type() {
		return &mud::type<mud::TPool<mud::Mime>>();
	}
	mud::Mime* DECL mud_TPool_mud_Mime_add_1(mud::TPool<mud::Mime>* self, const mud::Mime* value) {
		return &self->add(*value);
	}
	mud::Mime* DECL mud_TPool_mud_Mime_talloc_0(mud::TPool<mud::Mime>* self) {
		return self->talloc();
	}
	void DECL mud_TPool_mud_Mime_tdestroy_1(mud::TPool<mud::Mime>* self, mud::Mime* object) {
		self->tdestroy(*object);
	}
	void DECL mud_TPool_mud_Mime_tfree_1(mud::TPool<mud::Mime>* self, mud::Mime* object) {
		self->tfree(*object);
	}
	void DECL mud_TPool_mud_Mime__destroy(mud::TPool<mud::Mime>* self) {
		delete self;
	}
	// TPool<mud::Node3>
	mud::Type* DECL mud_TPool_mud_Node3__type() {
		return &mud::type<mud::TPool<mud::Node3>>();
	}
	mud::Node3* DECL mud_TPool_mud_Node3_add_1(mud::TPool<mud::Node3>* self, const mud::Node3* value) {
		return &self->add(*value);
	}
	mud::Node3* DECL mud_TPool_mud_Node3_talloc_0(mud::TPool<mud::Node3>* self) {
		return self->talloc();
	}
	void DECL mud_TPool_mud_Node3_tdestroy_1(mud::TPool<mud::Node3>* self, mud::Node3* object) {
		self->tdestroy(*object);
	}
	void DECL mud_TPool_mud_Node3_tfree_1(mud::TPool<mud::Node3>* self, mud::Node3* object) {
		self->tfree(*object);
	}
	void DECL mud_TPool_mud_Node3__destroy(mud::TPool<mud::Node3>* self) {
		delete self;
	}
	// Texture
	mud::Type* DECL mud_Texture__type() {
		return &mud::type<mud::Texture>();
	}
	const char* DECL mud_Texture__get_name(mud::Texture* self) {
		return self->m_name.c_str();
	}
	void DECL mud_Texture__set_name(mud::Texture* self, const char* value) {
		self->m_name = value;
	}
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
	// Viewport
	mud::Type* DECL mud_Viewport__type() {
		return &mud::type<mud::Viewport>();
	}
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
		return &self->m_rect;
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
		return &self->m_clear_colour;
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
	// Zone
	mud::Type* DECL mud_Zone__type() {
		return &mud::type<mud::Zone>();
	}
	mud::Zone* DECL mud_Zone__construct_0() {
		return new mud::Zone();
	}
	mud::Background* DECL mud_Zone__get_background(mud::Zone* self) {
		return &self->m_background;
	}
	void DECL mud_Zone__set_background(mud::Zone* self, mud::Background* value) {
		self->m_background = *value;
	}
	mud::Radiance* DECL mud_Zone__get_radiance(mud::Zone* self) {
		return &self->m_radiance;
	}
	void DECL mud_Zone__set_radiance(mud::Zone* self, mud::Radiance* value) {
		self->m_radiance = *value;
	}
	mud::Sun* DECL mud_Zone__get_sun(mud::Zone* self) {
		return &self->m_sun;
	}
	void DECL mud_Zone__set_sun(mud::Zone* self, mud::Sun* value) {
		self->m_sun = *value;
	}
	mud::Fog* DECL mud_Zone__get_fog(mud::Zone* self) {
		return &self->m_fog;
	}
	void DECL mud_Zone__set_fog(mud::Zone* self, mud::Fog* value) {
		self->m_fog = *value;
	}
	void DECL mud_Zone__destroy(mud::Zone* self) {
		delete self;
	}
	// BlockCopy
	mud::Type* DECL mud_BlockCopy__type() {
		return &mud::type<mud::BlockCopy>();
	}
	void DECL mud_BlockCopy__destroy(mud::BlockCopy* self) {
		delete self;
	}
	// BlockDepth
	mud::Type* DECL mud_BlockDepth__type() {
		return &mud::type<mud::BlockDepth>();
	}
	void DECL mud_BlockDepth__destroy(mud::BlockDepth* self) {
		delete self;
	}
	// BlockFilter
	mud::Type* DECL mud_BlockFilter__type() {
		return &mud::type<mud::BlockFilter>();
	}
	void DECL mud_BlockFilter__destroy(mud::BlockFilter* self) {
		delete self;
	}
	// BlockMaterial
	mud::Type* DECL mud_BlockMaterial__type() {
		return &mud::type<mud::BlockMaterial>();
	}
	void DECL mud_BlockMaterial__destroy(mud::BlockMaterial* self) {
		delete self;
	}
	// BlockParticles
	mud::Type* DECL mud_BlockParticles__type() {
		return &mud::type<mud::BlockParticles>();
	}
	void DECL mud_BlockParticles__destroy(mud::BlockParticles* self) {
		delete self;
	}
	// BlockResolve
	mud::Type* DECL mud_BlockResolve__type() {
		return &mud::type<mud::BlockResolve>();
	}
	void DECL mud_BlockResolve__destroy(mud::BlockResolve* self) {
		delete self;
	}
	// BlockSky
	mud::Type* DECL mud_BlockSky__type() {
		return &mud::type<mud::BlockSky>();
	}
	void DECL mud_BlockSky__destroy(mud::BlockSky* self) {
		delete self;
	}
	// ClusteredFrustum
	mud::Type* DECL mud_ClusteredFrustum__type() {
		return &mud::type<mud::ClusteredFrustum>();
	}
	mud::ClusteredFrustum* DECL mud_ClusteredFrustum__construct_0() {
		return new mud::ClusteredFrustum();
	}
	void DECL mud_ClusteredFrustum__destroy(mud::ClusteredFrustum* self) {
		delete self;
	}
	// DrawBlock
	mud::Type* DECL mud_DrawBlock__type() {
		return &mud::type<mud::DrawBlock>();
	}
	void DECL mud_DrawBlock__destroy(mud::DrawBlock* self) {
		delete self;
	}
	// Flare
	mud::Type* DECL mud_Flare__type() {
		return &mud::type<mud::Flare>();
	}
	mud::Flare* DECL mud_Flare__construct_0() {
		return new mud::Flare();
	}
	mud::Node3* DECL mud_Flare__get_node(mud::Flare* self) {
		return self->m_node;
	}
	void DECL mud_Flare__set_node(mud::Flare* self, mud::Node3* value) {
		self->m_node = value;
	}
	void DECL mud_Flare__destroy(mud::Flare* self) {
		delete self;
	}
	// GfxSystem
	mud::Type* DECL mud_GfxSystem__type() {
		return &mud::type<mud::GfxSystem>();
	}
	mud::GfxSystem* DECL mud_GfxSystem__construct_1(const char* resource_path) {
		return new mud::GfxSystem(resource_path);
	}
	void DECL mud_GfxSystem_default_pipeline_0(mud::GfxSystem* self) {
		self->default_pipeline();
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
	mud::Model* DECL mud_GfxSystem_create_model_1(mud::GfxSystem* self, const char* name) {
		return &self->create_model(name);
	}
	mud::Model* DECL mud_GfxSystem_create_model_geo_2(mud::GfxSystem* self, const char* name, const mud::MeshPacker* geometry) {
		return &self->create_model_geo(name, *geometry);
	}
	mud::Model* DECL mud_GfxSystem_create_model_geo_3(mud::GfxSystem* self, const char* name, const mud::MeshPacker* geometry, bool readback) {
		return &self->create_model_geo(name, *geometry, readback);
	}
	mud::Model* DECL mud_GfxSystem_create_model_geo_4(mud::GfxSystem* self, const char* name, const mud::MeshPacker* geometry, bool readback, bool optimize) {
		return &self->create_model_geo(name, *geometry, readback, optimize);
	}
	mud::Model* DECL mud_GfxSystem_create_model_gpu_2(mud::GfxSystem* self, const char* name, const mud::GpuMesh* gpu_mesh) {
		return &self->create_model_gpu(name, *gpu_mesh);
	}
	mud::Model* DECL mud_GfxSystem_create_model_gpu_3(mud::GfxSystem* self, const char* name, const mud::GpuMesh* gpu_mesh, bool readback) {
		return &self->create_model_gpu(name, *gpu_mesh, readback);
	}
	mud::Model* DECL mud_GfxSystem_create_model_gpu_4(mud::GfxSystem* self, const char* name, const mud::GpuMesh* gpu_mesh, bool readback, bool optimize) {
		return &self->create_model_gpu(name, *gpu_mesh, readback, optimize);
	}
	mud::Material* DECL mud_GfxSystem_fetch_material_2(mud::GfxSystem* self, const char* name, const char* shader) {
		return &self->fetch_material(name, shader);
	}
	mud::Material* DECL mud_GfxSystem_fetch_material_3(mud::GfxSystem* self, const char* name, const char* shader, bool builtin) {
		return &self->fetch_material(name, shader, builtin);
	}
	mud::Material* DECL mud_GfxSystem_fetch_image256_material_1(mud::GfxSystem* self, const mud::Image256* image) {
		return &self->fetch_image256_material(*image);
	}
	mud::Model* DECL mud_GfxSystem_shape_1(mud::GfxSystem* self, const mud::Shape* shape) {
		return &self->shape(*shape);
	}
	mud::Model* DECL mud_GfxSystem_shape_2(mud::GfxSystem* self, const mud::Shape* shape, const mud::Symbol* symbol) {
		return &self->shape(*shape, *symbol);
	}
	mud::Model* DECL mud_GfxSystem_shape_3(mud::GfxSystem* self, const mud::Shape* shape, const mud::Symbol* symbol, mud::DrawMode draw_mode) {
		return &self->shape(*shape, *symbol, draw_mode);
	}
	mud::Material* DECL mud_GfxSystem_symbol_material_1(mud::GfxSystem* self, const mud::Symbol* symbol) {
		return &self->symbol_material(*symbol);
	}
	mud::Material* DECL mud_GfxSystem_symbol_material_2(mud::GfxSystem* self, const mud::Symbol* symbol, mud::DrawMode draw_mode) {
		return &self->symbol_material(*symbol, draw_mode);
	}
	mud::AssetStore<mud::Texture>* DECL mud_GfxSystem__get_textures(mud::GfxSystem* self) {
		return &self->textures();
	}
	mud::AssetStore<mud::Program>* DECL mud_GfxSystem__get_programs(mud::GfxSystem* self) {
		return &self->programs();
	}
	mud::AssetStore<mud::Material>* DECL mud_GfxSystem__get_materials(mud::GfxSystem* self) {
		return &self->materials();
	}
	mud::AssetStore<mud::Model>* DECL mud_GfxSystem__get_models(mud::GfxSystem* self) {
		return &self->models();
	}
	mud::AssetStore<mud::Flow>* DECL mud_GfxSystem__get_flows(mud::GfxSystem* self) {
		return &self->flows();
	}
	mud::AssetStore<mud::Prefab>* DECL mud_GfxSystem__get_prefabs(mud::GfxSystem* self) {
		return &self->prefabs();
	}
	void DECL mud_GfxSystem__destroy(mud::GfxSystem* self) {
		delete self;
	}
	// RenderTarget
	mud::Type* DECL mud_RenderTarget__type() {
		return &mud::type<mud::RenderTarget>();
	}
	void DECL mud_RenderTarget__destroy(mud::RenderTarget* self) {
		delete self;
	}
	mud::mat4* DECL mud_bxidentity_0() {
		static mud::mat4 temp;
		return (temp = mud::bxidentity(), &temp);
	}
	mud::mat4* DECL mud_bxinverse_1(const mud::mat4* mat) {
		static mud::mat4 temp;
		return (temp = mud::bxinverse(*mat), &temp);
	}
	mud::mat4* DECL mud_bxSRT_3(const mud::vec3* scale, const mud::vec3* rot, const mud::vec3* trans) {
		static mud::mat4 temp;
		return (temp = mud::bxSRT(*scale, *rot, *trans), &temp);
	}
	mud::mat4* DECL mud_bxscale_1(const mud::vec3* scale) {
		static mud::mat4 temp;
		return (temp = mud::bxscale(*scale), &temp);
	}
	mud::mat4* DECL mud_bxrotation_1(const mud::quat* rot) {
		static mud::mat4 temp;
		return (temp = mud::bxrotation(*rot), &temp);
	}
	mud::mat4* DECL mud_bxtranslation_1(const mud::vec3* vec) {
		static mud::mat4 temp;
		return (temp = mud::bxtranslation(*vec), &temp);
	}
	mud::mat4* DECL mud_bxmul_2(const mud::mat4* lhs, const mud::mat4* rhs) {
		static mud::mat4 temp;
		return (temp = mud::bxmul(*lhs, *rhs), &temp);
	}
	mud::vec3* DECL mud_bxmulh_2(const mud::mat4* mat, const mud::vec3* vec) {
		static mud::vec3 temp;
		return (temp = mud::bxmulh(*mat, *vec), &temp);
	}
	mud::mat4* DECL mud_bxlookat_2(const mud::vec3* eye, const mud::vec3* at) {
		static mud::mat4 temp;
		return (temp = mud::bxlookat(*eye, *at), &temp);
	}
	mud::mat4* DECL mud_bxlookat_3(const mud::vec3* eye, const mud::vec3* at, const mud::vec3* up) {
		static mud::mat4 temp;
		return (temp = mud::bxlookat(*eye, *at, *up), &temp);
	}
	void DECL mud_bxlookat_4(mud::mat4* result, const mud::vec3* eye, const mud::vec3* at, const mud::vec3* up) {
		mud::bxlookat(*result, *eye, *at, *up);
	}
	mud::mat4* DECL mud_bxproj_5(float fov, float aspect, float near, float far, bool oglNdc) {
		static mud::mat4 temp;
		return (temp = mud::bxproj(fov, aspect, near, far, oglNdc), &temp);
	}
	mud::mat4* DECL mud_bxortho_5(const mud::vec4* rect, float near, float far, float offset, bool oglNdc) {
		static mud::mat4 temp;
		return (temp = mud::bxortho(*rect, near, far, offset, oglNdc), &temp);
	}
	mud::mat4* DECL mud_bxortho_8(float left, float right, float bottom, float top, float near, float far, float offset, bool oglNdc) {
		static mud::mat4 temp;
		return (temp = mud::bxortho(left, right, bottom, top, near, far, offset, oglNdc), &temp);
	}
	mud::mat4* DECL mud_bxTRS_3(const mud::vec3* scale, const mud::quat* rot, const mud::vec3* trans) {
		static mud::mat4 temp;
		return (temp = mud::bxTRS(*scale, *rot, *trans), &temp);
	}
	void DECL mud_load_texture_rgba_4(mud::Texture* texture, uint16_t width, uint16_t height, uint* data, int data_size) {
		mud::load_texture_rgba(*texture, width, height, { (uint32_t*)data, data_size / (sizeof(uint32_t) / sizeof(uint)) });
	}
	void DECL mud_gfx_setup_pipeline_minimal_1(mud::GfxSystem* gfx) {
		mud::gfx::setup_pipeline_minimal(*gfx);
	}
	mud::Gnode* DECL mud_gfx_node_1(mud::Gnode* parent) {
		return &mud::gfx::node(*parent);
	}
	mud::Gnode* DECL mud_gfx_node_2(mud::Gnode* parent, void* object, mud::Type* object_type) {
		return &mud::gfx::node(*parent, { object, *object_type });
	}
	mud::Gnode* DECL mud_gfx_node_3(mud::Gnode* parent, void* object, mud::Type* object_type, const mud::vec3* position) {
		return &mud::gfx::node(*parent, { object, *object_type }, *position);
	}
	mud::Gnode* DECL mud_gfx_node_4(mud::Gnode* parent, void* object, mud::Type* object_type, const mud::vec3* position, const mud::quat* rotation) {
		return &mud::gfx::node(*parent, { object, *object_type }, *position, *rotation);
	}
	mud::Gnode* DECL mud_gfx_node_5(mud::Gnode* parent, void* object, mud::Type* object_type, const mud::vec3* position, const mud::quat* rotation, const mud::vec3* scale) {
		return &mud::gfx::node(*parent, { object, *object_type }, *position, *rotation, *scale);
	}
	mud::Item* DECL mud_gfx_shape_3(mud::Gnode* parent, const mud::Shape* shape, const mud::Symbol* symbol) {
		return &mud::gfx::shape(*parent, *shape, *symbol);
	}
	mud::Item* DECL mud_gfx_shape_4(mud::Gnode* parent, const mud::Shape* shape, const mud::Symbol* symbol, uint32_t flags) {
		return &mud::gfx::shape(*parent, *shape, *symbol, flags);
	}
	mud::Item* DECL mud_gfx_shape_5(mud::Gnode* parent, const mud::Shape* shape, const mud::Symbol* symbol, uint32_t flags, mud::Material* material) {
		return &mud::gfx::shape(*parent, *shape, *symbol, flags, material);
	}
	void DECL mud_gfx_draw_3(mud::Gnode* parent, const mud::Shape* shape, const mud::Symbol* symbol) {
		mud::gfx::draw(*parent, *shape, *symbol);
	}
	void DECL mud_gfx_draw_4(mud::Gnode* parent, const mud::Shape* shape, const mud::Symbol* symbol, uint32_t flags) {
		mud::gfx::draw(*parent, *shape, *symbol, flags);
	}
	mud::Item* DECL mud_gfx_sprite_3(mud::Gnode* parent, const mud::Image256* image, const mud::vec2* size) {
		return &mud::gfx::sprite(*parent, *image, *size);
	}
	mud::Item* DECL mud_gfx_sprite_4(mud::Gnode* parent, const mud::Image256* image, const mud::vec2* size, uint32_t flags) {
		return &mud::gfx::sprite(*parent, *image, *size, flags);
	}
	mud::Item* DECL mud_gfx_sprite_5(mud::Gnode* parent, const mud::Image256* image, const mud::vec2* size, uint32_t flags, mud::Material* material) {
		return &mud::gfx::sprite(*parent, *image, *size, flags, material);
	}
	mud::Item* DECL mud_gfx_item_2(mud::Gnode* parent, const mud::Model* model) {
		return &mud::gfx::item(*parent, *model);
	}
	mud::Item* DECL mud_gfx_item_3(mud::Gnode* parent, const mud::Model* model, uint32_t flags) {
		return &mud::gfx::item(*parent, *model, flags);
	}
	mud::Item* DECL mud_gfx_item_4(mud::Gnode* parent, const mud::Model* model, uint32_t flags, mud::Material* material) {
		return &mud::gfx::item(*parent, *model, flags, material);
	}
	mud::Batch* DECL mud_gfx_batch_2(mud::Gnode* parent, mud::Item* item) {
		return &mud::gfx::batch(*parent, *item);
	}
	mud::Batch* DECL mud_gfx_instances_2(mud::Gnode* parent, mud::Item* item) {
		return &mud::gfx::instances(*parent, *item);
	}
	mud::Batch* DECL mud_gfx_instances_3(mud::Gnode* parent, mud::Item* item, float* transforms, int transforms_size) {
		return &mud::gfx::instances(*parent, *item, { (mud::mat4*)transforms, transforms_size / (sizeof(mud::mat4) / sizeof(float)) });
	}
	void DECL mud_gfx_prefab_2(mud::Gnode* parent, const mud::Prefab* prefab) {
		mud::gfx::prefab(*parent, *prefab);
	}
	void DECL mud_gfx_prefab_3(mud::Gnode* parent, const mud::Prefab* prefab, bool transform) {
		mud::gfx::prefab(*parent, *prefab, transform);
	}
	void DECL mud_gfx_prefab_4(mud::Gnode* parent, const mud::Prefab* prefab, bool transform, uint32_t flags) {
		mud::gfx::prefab(*parent, *prefab, transform, flags);
	}
	void DECL mud_gfx_prefab_5(mud::Gnode* parent, const mud::Prefab* prefab, bool transform, uint32_t flags, mud::Material* material) {
		mud::gfx::prefab(*parent, *prefab, transform, flags, material);
	}
	mud::Item* DECL mud_gfx_model_2(mud::Gnode* parent, const char* name) {
		return mud::gfx::model(*parent, name);
	}
	mud::Item* DECL mud_gfx_model_3(mud::Gnode* parent, const char* name, uint32_t flags) {
		return mud::gfx::model(*parent, name, flags);
	}
	mud::Item* DECL mud_gfx_model_4(mud::Gnode* parent, const char* name, uint32_t flags, mud::Material* material) {
		return mud::gfx::model(*parent, name, flags, material);
	}
	mud::Mime* DECL mud_gfx_animated_2(mud::Gnode* parent, mud::Item* item) {
		return &mud::gfx::animated(*parent, *item);
	}
	mud::Flare* DECL mud_gfx_flows_2(mud::Gnode* parent, const mud::Flow* emitter) {
		return &mud::gfx::flows(*parent, *emitter);
	}
	mud::Flare* DECL mud_gfx_flows_3(mud::Gnode* parent, const mud::Flow* emitter, uint32_t flags) {
		return &mud::gfx::flows(*parent, *emitter, flags);
	}
	mud::Light* DECL mud_gfx_light_4(mud::Gnode* parent, mud::LightType type, bool shadows, mud::Colour* colour) {
		return &mud::gfx::light(*parent, type, shadows, *colour);
	}
	mud::Light* DECL mud_gfx_light_5(mud::Gnode* parent, mud::LightType type, bool shadows, mud::Colour* colour, float range) {
		return &mud::gfx::light(*parent, type, shadows, *colour, range);
	}
	mud::Light* DECL mud_gfx_light_6(mud::Gnode* parent, mud::LightType type, bool shadows, mud::Colour* colour, float range, float attenuation) {
		return &mud::gfx::light(*parent, type, shadows, *colour, range, attenuation);
	}
	mud::Light* DECL mud_gfx_sun_light_3(mud::Gnode* parent, float azimuth, float elevation) {
		return &mud::gfx::sun_light(*parent, azimuth, elevation);
	}
	void DECL mud_gfx_radiance_3(mud::Gnode* parent, const char* texture, mud::BackgroundMode background) {
		mud::gfx::radiance(*parent, texture, background);
	}
	mud::Light* DECL mud_gfx_direct_light_node_2(mud::Gnode* parent, const mud::vec3* direction) {
		return &mud::gfx::direct_light_node(*parent, *direction);
	}
	mud::Material* DECL mud_gfx_solid_material_3(mud::GfxSystem* gfx, const char* name, const mud::Colour* colour) {
		return &mud::gfx::solid_material(*gfx, name, *colour);
	}
	mud::Material* DECL mud_gfx_pbr_material_3(mud::GfxSystem* gfx, const char* name, const mud::Colour* albedo) {
		return &mud::gfx::pbr_material(*gfx, name, *albedo);
	}
	mud::Material* DECL mud_gfx_pbr_material_4(mud::GfxSystem* gfx, const char* name, const mud::Colour* albedo, float metallic) {
		return &mud::gfx::pbr_material(*gfx, name, *albedo, metallic);
	}
	mud::Material* DECL mud_gfx_pbr_material_5(mud::GfxSystem* gfx, const char* name, const mud::Colour* albedo, float metallic, float roughness) {
		return &mud::gfx::pbr_material(*gfx, name, *albedo, metallic, roughness);
	}
	mud::Model* DECL mud_gfx_model_suzanne_1(mud::GfxSystem* gfx) {
		return &mud::gfx::model_suzanne(*gfx);
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
	mud::AnimationTarget DECL mud_AnimationTarget_Count() {
		return mud::AnimationTarget::Count;
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
	mud::BlendMode DECL mud_BlendMode_None() {
		return mud::BlendMode::None;
	}
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
	mud::CullMode DECL mud_CullMode_Count() {
		return mud::CullMode::Count;
	}
	// DepthDraw
	mud::DepthDraw DECL mud_DepthDraw_Enabled() {
		return mud::DepthDraw::Enabled;
	}
	mud::DepthDraw DECL mud_DepthDraw_Disabled() {
		return mud::DepthDraw::Disabled;
	}
	// DepthMethod
	mud::DepthMethod DECL mud_DepthMethod_Depth() {
		return mud::DepthMethod::Depth;
	}
	mud::DepthMethod DECL mud_DepthMethod_DepthPacked() {
		return mud::DepthMethod::DepthPacked;
	}
	mud::DepthMethod DECL mud_DepthMethod_Distance() {
		return mud::DepthMethod::Distance;
	}
	mud::DepthMethod DECL mud_DepthMethod_Count() {
		return mud::DepthMethod::Count;
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
	mud::MSAA DECL mud_MSAA_Count() {
		return mud::MSAA::Count;
	}
	// MaterialBlock
	mud::MaterialBlock DECL mud_MaterialBlock_Base() {
		return mud::MaterialBlock::Base;
	}
	mud::MaterialBlock DECL mud_MaterialBlock_Alpha() {
		return mud::MaterialBlock::Alpha;
	}
	mud::MaterialBlock DECL mud_MaterialBlock_Solid() {
		return mud::MaterialBlock::Solid;
	}
	mud::MaterialBlock DECL mud_MaterialBlock_Point() {
		return mud::MaterialBlock::Point;
	}
	mud::MaterialBlock DECL mud_MaterialBlock_Line() {
		return mud::MaterialBlock::Line;
	}
	mud::MaterialBlock DECL mud_MaterialBlock_Pbr() {
		return mud::MaterialBlock::Pbr;
	}
	mud::MaterialBlock DECL mud_MaterialBlock_Fresnel() {
		return mud::MaterialBlock::Fresnel;
	}
	mud::MaterialBlock DECL mud_MaterialBlock_User() {
		return mud::MaterialBlock::User;
	}
	mud::MaterialBlock DECL mud_MaterialBlock_Count() {
		return mud::MaterialBlock::Count;
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
	// ShaderColor
	mud::ShaderColor DECL mud_ShaderColor_Shader() {
		return mud::ShaderColor::Shader;
	}
	mud::ShaderColor DECL mud_ShaderColor_Vertex() {
		return mud::ShaderColor::Vertex;
	}
	mud::ShaderColor DECL mud_ShaderColor_Face() {
		return mud::ShaderColor::Face;
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
	mud::Shading DECL mud_Shading_Solid() {
		return mud::Shading::Solid;
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
	mud::TextureSampler DECL mud_TextureSampler_Alpha() {
		return mud::TextureSampler::Alpha;
	}
	mud::TextureSampler DECL mud_TextureSampler_Metallic() {
		return mud::TextureSampler::Metallic;
	}
	mud::TextureSampler DECL mud_TextureSampler_User0() {
		return mud::TextureSampler::User0;
	}
	mud::TextureSampler DECL mud_TextureSampler_Roughness() {
		return mud::TextureSampler::Roughness;
	}
	mud::TextureSampler DECL mud_TextureSampler_User1() {
		return mud::TextureSampler::User1;
	}
	mud::TextureSampler DECL mud_TextureSampler_Emissive() {
		return mud::TextureSampler::Emissive;
	}
	mud::TextureSampler DECL mud_TextureSampler_User2() {
		return mud::TextureSampler::User2;
	}
	mud::TextureSampler DECL mud_TextureSampler_Normal() {
		return mud::TextureSampler::Normal;
	}
	mud::TextureSampler DECL mud_TextureSampler_User3() {
		return mud::TextureSampler::User3;
	}
	mud::TextureSampler DECL mud_TextureSampler_AO() {
		return mud::TextureSampler::AO;
	}
	mud::TextureSampler DECL mud_TextureSampler_User4() {
		return mud::TextureSampler::User4;
	}
	mud::TextureSampler DECL mud_TextureSampler_Depth() {
		return mud::TextureSampler::Depth;
	}
	mud::TextureSampler DECL mud_TextureSampler_User5() {
		return mud::TextureSampler::User5;
	}
	mud::TextureSampler DECL mud_TextureSampler_Radiance() {
		return mud::TextureSampler::Radiance;
	}
	mud::TextureSampler DECL mud_TextureSampler_ShadowAtlas() {
		return mud::TextureSampler::ShadowAtlas;
	}
	mud::TextureSampler DECL mud_TextureSampler_ShadowCSM() {
		return mud::TextureSampler::ShadowCSM;
	}
	mud::TextureSampler DECL mud_TextureSampler_Lightmap() {
		return mud::TextureSampler::Lightmap;
	}
	mud::TextureSampler DECL mud_TextureSampler_ReflectionProbe() {
		return mud::TextureSampler::ReflectionProbe;
	}
	mud::TextureSampler DECL mud_TextureSampler_GIProbe() {
		return mud::TextureSampler::GIProbe;
	}
	mud::TextureSampler DECL mud_TextureSampler_Skeleton() {
		return mud::TextureSampler::Skeleton;
	}
	mud::TextureSampler DECL mud_TextureSampler_Zones() {
		return mud::TextureSampler::Zones;
	}
	mud::TextureSampler DECL mud_TextureSampler_Materials() {
		return mud::TextureSampler::Materials;
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
	
}


