#include <infra/Api.h>
#include <type/Api.h>
#include <refl/Api.h>
#include <srlz/Api.h>
#include <math/Api.h>
#include <gltf/Api.h>

#ifdef MUD_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// glTF
	mud::Type* DECL glTF__type() {
		return &mud::type<glTF>();
	}
	glTF* DECL glTF__construct_0() {
		return new glTF();
	}
	void DECL glTF__destroy(glTF* self) {
		delete self;
	}
	// glTFAccessor
	mud::Type* DECL glTFAccessor__type() {
		return &mud::type<glTFAccessor>();
	}
	glTFAccessor* DECL glTFAccessor__construct_0() {
		return new glTFAccessor();
	}
	const char* DECL glTFAccessor__get_name(glTFAccessor* self) {
		return self->name.c_str();
	}
	void DECL glTFAccessor__set_name(glTFAccessor* self, const char* value) {
		self->name = value;
	}
	int DECL glTFAccessor__get_buffer_view(glTFAccessor* self) {
		return self->buffer_view;
	}
	void DECL glTFAccessor__set_buffer_view(glTFAccessor* self, int value) {
		self->buffer_view = value;
	}
	int DECL glTFAccessor__get_byte_offset(glTFAccessor* self) {
		return self->byte_offset;
	}
	void DECL glTFAccessor__set_byte_offset(glTFAccessor* self, int value) {
		self->byte_offset = value;
	}
	glTFComponentType DECL glTFAccessor__get_component_type(glTFAccessor* self) {
		return self->component_type;
	}
	void DECL glTFAccessor__set_component_type(glTFAccessor* self, glTFComponentType value) {
		self->component_type = value;
	}
	bool DECL glTFAccessor__get_normalized(glTFAccessor* self) {
		return self->normalized;
	}
	void DECL glTFAccessor__set_normalized(glTFAccessor* self, bool value) {
		self->normalized = value;
	}
	int DECL glTFAccessor__get_count(glTFAccessor* self) {
		return self->count;
	}
	void DECL glTFAccessor__set_count(glTFAccessor* self, int value) {
		self->count = value;
	}
	glTFType DECL glTFAccessor__get_type(glTFAccessor* self) {
		return self->type;
	}
	void DECL glTFAccessor__set_type(glTFAccessor* self, glTFType value) {
		self->type = value;
	}
	glTFSparse* DECL glTFAccessor__get_sparse(glTFAccessor* self) {
		return &self->sparse;
	}
	void DECL glTFAccessor__set_sparse(glTFAccessor* self, glTFSparse* value) {
		self->sparse = *value;
	}
	void DECL glTFAccessor__destroy(glTFAccessor* self) {
		delete self;
	}
	// glTFAnimation
	mud::Type* DECL glTFAnimation__type() {
		return &mud::type<glTFAnimation>();
	}
	glTFAnimation* DECL glTFAnimation__construct_0() {
		return new glTFAnimation();
	}
	const char* DECL glTFAnimation__get_name(glTFAnimation* self) {
		return self->name.c_str();
	}
	void DECL glTFAnimation__set_name(glTFAnimation* self, const char* value) {
		self->name = value;
	}
	void DECL glTFAnimation__destroy(glTFAnimation* self) {
		delete self;
	}
	// glTFAnimationChannel
	mud::Type* DECL glTFAnimationChannel__type() {
		return &mud::type<glTFAnimationChannel>();
	}
	glTFAnimationChannel* DECL glTFAnimationChannel__construct_0() {
		return new glTFAnimationChannel();
	}
	int DECL glTFAnimationChannel__get_sampler(glTFAnimationChannel* self) {
		return self->sampler;
	}
	void DECL glTFAnimationChannel__set_sampler(glTFAnimationChannel* self, int value) {
		self->sampler = value;
	}
	glTFAnimationTarget* DECL glTFAnimationChannel__get_target(glTFAnimationChannel* self) {
		return &self->target;
	}
	void DECL glTFAnimationChannel__set_target(glTFAnimationChannel* self, glTFAnimationTarget* value) {
		self->target = *value;
	}
	void DECL glTFAnimationChannel__destroy(glTFAnimationChannel* self) {
		delete self;
	}
	// glTFAnimationSampler
	mud::Type* DECL glTFAnimationSampler__type() {
		return &mud::type<glTFAnimationSampler>();
	}
	glTFAnimationSampler* DECL glTFAnimationSampler__construct_0() {
		return new glTFAnimationSampler();
	}
	glTFInterpolation DECL glTFAnimationSampler__get_interpolation(glTFAnimationSampler* self) {
		return self->interpolation;
	}
	void DECL glTFAnimationSampler__set_interpolation(glTFAnimationSampler* self, glTFInterpolation value) {
		self->interpolation = value;
	}
	int DECL glTFAnimationSampler__get_input(glTFAnimationSampler* self) {
		return self->input;
	}
	void DECL glTFAnimationSampler__set_input(glTFAnimationSampler* self, int value) {
		self->input = value;
	}
	int DECL glTFAnimationSampler__get_output(glTFAnimationSampler* self) {
		return self->output;
	}
	void DECL glTFAnimationSampler__set_output(glTFAnimationSampler* self, int value) {
		self->output = value;
	}
	void DECL glTFAnimationSampler__destroy(glTFAnimationSampler* self) {
		delete self;
	}
	// glTFAnimationTarget
	mud::Type* DECL glTFAnimationTarget__type() {
		return &mud::type<glTFAnimationTarget>();
	}
	glTFAnimationTarget* DECL glTFAnimationTarget__construct_0() {
		return new glTFAnimationTarget();
	}
	int DECL glTFAnimationTarget__get_node(glTFAnimationTarget* self) {
		return self->node;
	}
	void DECL glTFAnimationTarget__set_node(glTFAnimationTarget* self, int value) {
		self->node = value;
	}
	const char* DECL glTFAnimationTarget__get_path(glTFAnimationTarget* self) {
		return self->path.c_str();
	}
	void DECL glTFAnimationTarget__set_path(glTFAnimationTarget* self, const char* value) {
		self->path = value;
	}
	void DECL glTFAnimationTarget__destroy(glTFAnimationTarget* self) {
		delete self;
	}
	// glTFAttributes
	mud::Type* DECL glTFAttributes__type() {
		return &mud::type<glTFAttributes>();
	}
	glTFAttributes* DECL glTFAttributes__construct_0() {
		return new glTFAttributes();
	}
	int DECL glTFAttributes__get_POSITION(glTFAttributes* self) {
		return self->POSITION;
	}
	void DECL glTFAttributes__set_POSITION(glTFAttributes* self, int value) {
		self->POSITION = value;
	}
	int DECL glTFAttributes__get_NORMAL(glTFAttributes* self) {
		return self->NORMAL;
	}
	void DECL glTFAttributes__set_NORMAL(glTFAttributes* self, int value) {
		self->NORMAL = value;
	}
	int DECL glTFAttributes__get_TANGENT(glTFAttributes* self) {
		return self->TANGENT;
	}
	void DECL glTFAttributes__set_TANGENT(glTFAttributes* self, int value) {
		self->TANGENT = value;
	}
	int DECL glTFAttributes__get_TEXCOORD_0(glTFAttributes* self) {
		return self->TEXCOORD_0;
	}
	void DECL glTFAttributes__set_TEXCOORD_0(glTFAttributes* self, int value) {
		self->TEXCOORD_0 = value;
	}
	int DECL glTFAttributes__get_TEXCOORD_1(glTFAttributes* self) {
		return self->TEXCOORD_1;
	}
	void DECL glTFAttributes__set_TEXCOORD_1(glTFAttributes* self, int value) {
		self->TEXCOORD_1 = value;
	}
	int DECL glTFAttributes__get_COLOR_0(glTFAttributes* self) {
		return self->COLOR_0;
	}
	void DECL glTFAttributes__set_COLOR_0(glTFAttributes* self, int value) {
		self->COLOR_0 = value;
	}
	int DECL glTFAttributes__get_JOINTS_0(glTFAttributes* self) {
		return self->JOINTS_0;
	}
	void DECL glTFAttributes__set_JOINTS_0(glTFAttributes* self, int value) {
		self->JOINTS_0 = value;
	}
	int DECL glTFAttributes__get_WEIGHTS_0(glTFAttributes* self) {
		return self->WEIGHTS_0;
	}
	void DECL glTFAttributes__set_WEIGHTS_0(glTFAttributes* self, int value) {
		self->WEIGHTS_0 = value;
	}
	void DECL glTFAttributes__destroy(glTFAttributes* self) {
		delete self;
	}
	// glTFBuffer
	mud::Type* DECL glTFBuffer__type() {
		return &mud::type<glTFBuffer>();
	}
	glTFBuffer* DECL glTFBuffer__construct_0() {
		return new glTFBuffer();
	}
	const char* DECL glTFBuffer__get_name(glTFBuffer* self) {
		return self->name.c_str();
	}
	void DECL glTFBuffer__set_name(glTFBuffer* self, const char* value) {
		self->name = value;
	}
	const char* DECL glTFBuffer__get_mime_type(glTFBuffer* self) {
		return self->mime_type.c_str();
	}
	void DECL glTFBuffer__set_mime_type(glTFBuffer* self, const char* value) {
		self->mime_type = value;
	}
	const char* DECL glTFBuffer__get_uri(glTFBuffer* self) {
		return self->uri.c_str();
	}
	void DECL glTFBuffer__set_uri(glTFBuffer* self, const char* value) {
		self->uri = value;
	}
	size_t DECL glTFBuffer__get_byte_length(glTFBuffer* self) {
		return self->byte_length;
	}
	void DECL glTFBuffer__set_byte_length(glTFBuffer* self, size_t value) {
		self->byte_length = value;
	}
	void DECL glTFBuffer__destroy(glTFBuffer* self) {
		delete self;
	}
	// glTFBufferView
	mud::Type* DECL glTFBufferView__type() {
		return &mud::type<glTFBufferView>();
	}
	glTFBufferView* DECL glTFBufferView__construct_0() {
		return new glTFBufferView();
	}
	const char* DECL glTFBufferView__get_name(glTFBufferView* self) {
		return self->name.c_str();
	}
	void DECL glTFBufferView__set_name(glTFBufferView* self, const char* value) {
		self->name = value;
	}
	int DECL glTFBufferView__get_buffer(glTFBufferView* self) {
		return self->buffer;
	}
	void DECL glTFBufferView__set_buffer(glTFBufferView* self, int value) {
		self->buffer = value;
	}
	size_t DECL glTFBufferView__get_byte_offset(glTFBufferView* self) {
		return self->byte_offset;
	}
	void DECL glTFBufferView__set_byte_offset(glTFBufferView* self, size_t value) {
		self->byte_offset = value;
	}
	size_t DECL glTFBufferView__get_byte_length(glTFBufferView* self) {
		return self->byte_length;
	}
	void DECL glTFBufferView__set_byte_length(glTFBufferView* self, size_t value) {
		self->byte_length = value;
	}
	size_t DECL glTFBufferView__get_byte_stride(glTFBufferView* self) {
		return self->byte_stride;
	}
	void DECL glTFBufferView__set_byte_stride(glTFBufferView* self, size_t value) {
		self->byte_stride = value;
	}
	int DECL glTFBufferView__get_target(glTFBufferView* self) {
		return self->target;
	}
	void DECL glTFBufferView__set_target(glTFBufferView* self, int value) {
		self->target = value;
	}
	void DECL glTFBufferView__destroy(glTFBufferView* self) {
		delete self;
	}
	// glTFCamera
	mud::Type* DECL glTFCamera__type() {
		return &mud::type<glTFCamera>();
	}
	glTFCamera* DECL glTFCamera__construct_0() {
		return new glTFCamera();
	}
	const char* DECL glTFCamera__get_name(glTFCamera* self) {
		return self->name.c_str();
	}
	void DECL glTFCamera__set_name(glTFCamera* self, const char* value) {
		self->name = value;
	}
	const char* DECL glTFCamera__get_type(glTFCamera* self) {
		return self->type.c_str();
	}
	void DECL glTFCamera__set_type(glTFCamera* self, const char* value) {
		self->type = value;
	}
	glTFOrthographic* DECL glTFCamera__get_orthographic(glTFCamera* self) {
		return &self->orthographic;
	}
	void DECL glTFCamera__set_orthographic(glTFCamera* self, glTFOrthographic* value) {
		self->orthographic = *value;
	}
	glTFPerspective* DECL glTFCamera__get_perspective(glTFCamera* self) {
		return &self->perspective;
	}
	void DECL glTFCamera__set_perspective(glTFCamera* self, glTFPerspective* value) {
		self->perspective = *value;
	}
	void DECL glTFCamera__destroy(glTFCamera* self) {
		delete self;
	}
	// glTFImage
	mud::Type* DECL glTFImage__type() {
		return &mud::type<glTFImage>();
	}
	glTFImage* DECL glTFImage__construct_0() {
		return new glTFImage();
	}
	const char* DECL glTFImage__get_name(glTFImage* self) {
		return self->name.c_str();
	}
	void DECL glTFImage__set_name(glTFImage* self, const char* value) {
		self->name = value;
	}
	const char* DECL glTFImage__get_mime_type(glTFImage* self) {
		return self->mime_type.c_str();
	}
	void DECL glTFImage__set_mime_type(glTFImage* self, const char* value) {
		self->mime_type = value;
	}
	const char* DECL glTFImage__get_uri(glTFImage* self) {
		return self->uri.c_str();
	}
	void DECL glTFImage__set_uri(glTFImage* self, const char* value) {
		self->uri = value;
	}
	int DECL glTFImage__get_buffer_view(glTFImage* self) {
		return self->buffer_view;
	}
	void DECL glTFImage__set_buffer_view(glTFImage* self, int value) {
		self->buffer_view = value;
	}
	void DECL glTFImage__destroy(glTFImage* self) {
		delete self;
	}
	// glTFMaterial
	mud::Type* DECL glTFMaterial__type() {
		return &mud::type<glTFMaterial>();
	}
	glTFMaterial* DECL glTFMaterial__construct_0() {
		return new glTFMaterial();
	}
	const char* DECL glTFMaterial__get_name(glTFMaterial* self) {
		return self->name.c_str();
	}
	void DECL glTFMaterial__set_name(glTFMaterial* self, const char* value) {
		self->name = value;
	}
	glTFTextureInfo* DECL glTFMaterial__get_normal_texture(glTFMaterial* self) {
		return &self->normal_texture;
	}
	void DECL glTFMaterial__set_normal_texture(glTFMaterial* self, glTFTextureInfo* value) {
		self->normal_texture = *value;
	}
	glTFTextureInfo* DECL glTFMaterial__get_occlusion_texture(glTFMaterial* self) {
		return &self->occlusion_texture;
	}
	void DECL glTFMaterial__set_occlusion_texture(glTFMaterial* self, glTFTextureInfo* value) {
		self->occlusion_texture = *value;
	}
	mud::vec3* DECL glTFMaterial__get_emissive_factor(glTFMaterial* self) {
		return &self->emissive_factor;
	}
	void DECL glTFMaterial__set_emissive_factor(glTFMaterial* self, mud::vec3* value) {
		self->emissive_factor = *value;
	}
	glTFTextureInfo* DECL glTFMaterial__get_emissive_texture(glTFMaterial* self) {
		return &self->emissive_texture;
	}
	void DECL glTFMaterial__set_emissive_texture(glTFMaterial* self, glTFTextureInfo* value) {
		self->emissive_texture = *value;
	}
	bool DECL glTFMaterial__get_double_sided(glTFMaterial* self) {
		return self->double_sided;
	}
	void DECL glTFMaterial__set_double_sided(glTFMaterial* self, bool value) {
		self->double_sided = value;
	}
	glTFAlphaMode DECL glTFMaterial__get_alpha_mode(glTFMaterial* self) {
		return self->alpha_mode;
	}
	void DECL glTFMaterial__set_alpha_mode(glTFMaterial* self, glTFAlphaMode value) {
		self->alpha_mode = value;
	}
	glTFMaterialPBR* DECL glTFMaterial__get_pbr_metallic_roughness(glTFMaterial* self) {
		return &self->pbr_metallic_roughness;
	}
	void DECL glTFMaterial__set_pbr_metallic_roughness(glTFMaterial* self, glTFMaterialPBR* value) {
		self->pbr_metallic_roughness = *value;
	}
	void DECL glTFMaterial__destroy(glTFMaterial* self) {
		delete self;
	}
	// glTFMaterialPBR
	mud::Type* DECL glTFMaterialPBR__type() {
		return &mud::type<glTFMaterialPBR>();
	}
	glTFMaterialPBR* DECL glTFMaterialPBR__construct_0() {
		return new glTFMaterialPBR();
	}
	mud::vec4* DECL glTFMaterialPBR__get_base_color_factor(glTFMaterialPBR* self) {
		return &self->base_color_factor;
	}
	void DECL glTFMaterialPBR__set_base_color_factor(glTFMaterialPBR* self, mud::vec4* value) {
		self->base_color_factor = *value;
	}
	glTFTextureInfo* DECL glTFMaterialPBR__get_base_color_texture(glTFMaterialPBR* self) {
		return &self->base_color_texture;
	}
	void DECL glTFMaterialPBR__set_base_color_texture(glTFMaterialPBR* self, glTFTextureInfo* value) {
		self->base_color_texture = *value;
	}
	float DECL glTFMaterialPBR__get_metallic_factor(glTFMaterialPBR* self) {
		return self->metallic_factor;
	}
	void DECL glTFMaterialPBR__set_metallic_factor(glTFMaterialPBR* self, float value) {
		self->metallic_factor = value;
	}
	float DECL glTFMaterialPBR__get_roughness_factor(glTFMaterialPBR* self) {
		return self->roughness_factor;
	}
	void DECL glTFMaterialPBR__set_roughness_factor(glTFMaterialPBR* self, float value) {
		self->roughness_factor = value;
	}
	glTFTextureInfo* DECL glTFMaterialPBR__get_metallic_roughness_texture(glTFMaterialPBR* self) {
		return &self->metallic_roughness_texture;
	}
	void DECL glTFMaterialPBR__set_metallic_roughness_texture(glTFMaterialPBR* self, glTFTextureInfo* value) {
		self->metallic_roughness_texture = *value;
	}
	void DECL glTFMaterialPBR__destroy(glTFMaterialPBR* self) {
		delete self;
	}
	// glTFMesh
	mud::Type* DECL glTFMesh__type() {
		return &mud::type<glTFMesh>();
	}
	glTFMesh* DECL glTFMesh__construct_0() {
		return new glTFMesh();
	}
	const char* DECL glTFMesh__get_name(glTFMesh* self) {
		return self->name.c_str();
	}
	void DECL glTFMesh__set_name(glTFMesh* self, const char* value) {
		self->name = value;
	}
	void DECL glTFMesh__destroy(glTFMesh* self) {
		delete self;
	}
	// glTFMorphTarget
	mud::Type* DECL glTFMorphTarget__type() {
		return &mud::type<glTFMorphTarget>();
	}
	glTFMorphTarget* DECL glTFMorphTarget__construct_0() {
		return new glTFMorphTarget();
	}
	int DECL glTFMorphTarget__get_POSITION(glTFMorphTarget* self) {
		return self->POSITION;
	}
	void DECL glTFMorphTarget__set_POSITION(glTFMorphTarget* self, int value) {
		self->POSITION = value;
	}
	int DECL glTFMorphTarget__get_NORMAL(glTFMorphTarget* self) {
		return self->NORMAL;
	}
	void DECL glTFMorphTarget__set_NORMAL(glTFMorphTarget* self, int value) {
		self->NORMAL = value;
	}
	int DECL glTFMorphTarget__get_TANGENT(glTFMorphTarget* self) {
		return self->TANGENT;
	}
	void DECL glTFMorphTarget__set_TANGENT(glTFMorphTarget* self, int value) {
		self->TANGENT = value;
	}
	void DECL glTFMorphTarget__destroy(glTFMorphTarget* self) {
		delete self;
	}
	// glTFNode
	mud::Type* DECL glTFNode__type() {
		return &mud::type<glTFNode>();
	}
	glTFNode* DECL glTFNode__construct_0() {
		return new glTFNode();
	}
	const char* DECL glTFNode__get_name(glTFNode* self) {
		return self->name.c_str();
	}
	void DECL glTFNode__set_name(glTFNode* self, const char* value) {
		self->name = value;
	}
	int DECL glTFNode__get_mesh(glTFNode* self) {
		return self->mesh;
	}
	void DECL glTFNode__set_mesh(glTFNode* self, int value) {
		self->mesh = value;
	}
	int DECL glTFNode__get_camera(glTFNode* self) {
		return self->camera;
	}
	void DECL glTFNode__set_camera(glTFNode* self, int value) {
		self->camera = value;
	}
	int DECL glTFNode__get_skin(glTFNode* self) {
		return self->skin;
	}
	void DECL glTFNode__set_skin(glTFNode* self, int value) {
		self->skin = value;
	}
	mud::mat4* DECL glTFNode__get_matrix(glTFNode* self) {
		return &self->matrix;
	}
	void DECL glTFNode__set_matrix(glTFNode* self, mud::mat4* value) {
		self->matrix = *value;
	}
	mud::vec3* DECL glTFNode__get_translation(glTFNode* self) {
		return &self->translation;
	}
	void DECL glTFNode__set_translation(glTFNode* self, mud::vec3* value) {
		self->translation = *value;
	}
	mud::quat* DECL glTFNode__get_rotation(glTFNode* self) {
		return &self->rotation;
	}
	void DECL glTFNode__set_rotation(glTFNode* self, mud::quat* value) {
		self->rotation = *value;
	}
	mud::vec3* DECL glTFNode__get_scale(glTFNode* self) {
		return &self->scale;
	}
	void DECL glTFNode__set_scale(glTFNode* self, mud::vec3* value) {
		self->scale = *value;
	}
	void DECL glTFNode__destroy(glTFNode* self) {
		delete self;
	}
	// glTFNodeExtras
	mud::Type* DECL glTFNodeExtras__type() {
		return &mud::type<glTFNodeExtras>();
	}
	glTFNodeExtras* DECL glTFNodeExtras__construct_0() {
		return new glTFNodeExtras();
	}
	void DECL glTFNodeExtras__destroy(glTFNodeExtras* self) {
		delete self;
	}
	// glTFOrthographic
	mud::Type* DECL glTFOrthographic__type() {
		return &mud::type<glTFOrthographic>();
	}
	glTFOrthographic* DECL glTFOrthographic__construct_0() {
		return new glTFOrthographic();
	}
	float DECL glTFOrthographic__get_xmag(glTFOrthographic* self) {
		return self->xmag;
	}
	void DECL glTFOrthographic__set_xmag(glTFOrthographic* self, float value) {
		self->xmag = value;
	}
	float DECL glTFOrthographic__get_ymag(glTFOrthographic* self) {
		return self->ymag;
	}
	void DECL glTFOrthographic__set_ymag(glTFOrthographic* self, float value) {
		self->ymag = value;
	}
	float DECL glTFOrthographic__get_zfar(glTFOrthographic* self) {
		return self->zfar;
	}
	void DECL glTFOrthographic__set_zfar(glTFOrthographic* self, float value) {
		self->zfar = value;
	}
	float DECL glTFOrthographic__get_znear(glTFOrthographic* self) {
		return self->znear;
	}
	void DECL glTFOrthographic__set_znear(glTFOrthographic* self, float value) {
		self->znear = value;
	}
	void DECL glTFOrthographic__destroy(glTFOrthographic* self) {
		delete self;
	}
	// glTFPerspective
	mud::Type* DECL glTFPerspective__type() {
		return &mud::type<glTFPerspective>();
	}
	glTFPerspective* DECL glTFPerspective__construct_0() {
		return new glTFPerspective();
	}
	float DECL glTFPerspective__get_yfov(glTFPerspective* self) {
		return self->yfov;
	}
	void DECL glTFPerspective__set_yfov(glTFPerspective* self, float value) {
		self->yfov = value;
	}
	float DECL glTFPerspective__get_zfar(glTFPerspective* self) {
		return self->zfar;
	}
	void DECL glTFPerspective__set_zfar(glTFPerspective* self, float value) {
		self->zfar = value;
	}
	float DECL glTFPerspective__get_znear(glTFPerspective* self) {
		return self->znear;
	}
	void DECL glTFPerspective__set_znear(glTFPerspective* self, float value) {
		self->znear = value;
	}
	float DECL glTFPerspective__get_aspect_ratio(glTFPerspective* self) {
		return self->aspect_ratio;
	}
	void DECL glTFPerspective__set_aspect_ratio(glTFPerspective* self, float value) {
		self->aspect_ratio = value;
	}
	void DECL glTFPerspective__destroy(glTFPerspective* self) {
		delete self;
	}
	// glTFPrimitive
	mud::Type* DECL glTFPrimitive__type() {
		return &mud::type<glTFPrimitive>();
	}
	glTFPrimitive* DECL glTFPrimitive__construct_0() {
		return new glTFPrimitive();
	}
	glTFAttributes* DECL glTFPrimitive__get_attributes(glTFPrimitive* self) {
		return &self->attributes;
	}
	void DECL glTFPrimitive__set_attributes(glTFPrimitive* self, glTFAttributes* value) {
		self->attributes = *value;
	}
	int DECL glTFPrimitive__get_indices(glTFPrimitive* self) {
		return self->indices;
	}
	void DECL glTFPrimitive__set_indices(glTFPrimitive* self, int value) {
		self->indices = value;
	}
	int DECL glTFPrimitive__get_material(glTFPrimitive* self) {
		return self->material;
	}
	void DECL glTFPrimitive__set_material(glTFPrimitive* self, int value) {
		self->material = value;
	}
	glTFPrimitiveType DECL glTFPrimitive__get_mode(glTFPrimitive* self) {
		return self->mode;
	}
	void DECL glTFPrimitive__set_mode(glTFPrimitive* self, glTFPrimitiveType value) {
		self->mode = value;
	}
	void DECL glTFPrimitive__destroy(glTFPrimitive* self) {
		delete self;
	}
	// glTFSampler
	mud::Type* DECL glTFSampler__type() {
		return &mud::type<glTFSampler>();
	}
	glTFSampler* DECL glTFSampler__construct_0() {
		return new glTFSampler();
	}
	int DECL glTFSampler__get_mag_filter(glTFSampler* self) {
		return self->mag_filter;
	}
	void DECL glTFSampler__set_mag_filter(glTFSampler* self, int value) {
		self->mag_filter = value;
	}
	int DECL glTFSampler__get_min_filter(glTFSampler* self) {
		return self->min_filter;
	}
	void DECL glTFSampler__set_min_filter(glTFSampler* self, int value) {
		self->min_filter = value;
	}
	int DECL glTFSampler__get_wrap_s(glTFSampler* self) {
		return self->wrap_s;
	}
	void DECL glTFSampler__set_wrap_s(glTFSampler* self, int value) {
		self->wrap_s = value;
	}
	int DECL glTFSampler__get_wrap_t(glTFSampler* self) {
		return self->wrap_t;
	}
	void DECL glTFSampler__set_wrap_t(glTFSampler* self, int value) {
		self->wrap_t = value;
	}
	const char* DECL glTFSampler__get_name(glTFSampler* self) {
		return self->name.c_str();
	}
	void DECL glTFSampler__set_name(glTFSampler* self, const char* value) {
		self->name = value;
	}
	void DECL glTFSampler__destroy(glTFSampler* self) {
		delete self;
	}
	// glTFScene
	mud::Type* DECL glTFScene__type() {
		return &mud::type<glTFScene>();
	}
	glTFScene* DECL glTFScene__construct_0() {
		return new glTFScene();
	}
	const char* DECL glTFScene__get_name(glTFScene* self) {
		return self->name.c_str();
	}
	void DECL glTFScene__set_name(glTFScene* self, const char* value) {
		self->name = value;
	}
	void DECL glTFScene__destroy(glTFScene* self) {
		delete self;
	}
	// glTFSkin
	mud::Type* DECL glTFSkin__type() {
		return &mud::type<glTFSkin>();
	}
	glTFSkin* DECL glTFSkin__construct_0() {
		return new glTFSkin();
	}
	const char* DECL glTFSkin__get_name(glTFSkin* self) {
		return self->name.c_str();
	}
	void DECL glTFSkin__set_name(glTFSkin* self, const char* value) {
		self->name = value;
	}
	int DECL glTFSkin__get_skeleton(glTFSkin* self) {
		return self->skeleton;
	}
	void DECL glTFSkin__set_skeleton(glTFSkin* self, int value) {
		self->skeleton = value;
	}
	int DECL glTFSkin__get_inverse_bind_matrices(glTFSkin* self) {
		return self->inverse_bind_matrices;
	}
	void DECL glTFSkin__set_inverse_bind_matrices(glTFSkin* self, int value) {
		self->inverse_bind_matrices = value;
	}
	void DECL glTFSkin__destroy(glTFSkin* self) {
		delete self;
	}
	// glTFSparse
	mud::Type* DECL glTFSparse__type() {
		return &mud::type<glTFSparse>();
	}
	glTFSparse* DECL glTFSparse__construct_0() {
		return new glTFSparse();
	}
	int DECL glTFSparse__get_count(glTFSparse* self) {
		return self->count;
	}
	void DECL glTFSparse__set_count(glTFSparse* self, int value) {
		self->count = value;
	}
	glTFSparseIndices* DECL glTFSparse__get_indices(glTFSparse* self) {
		return &self->indices;
	}
	void DECL glTFSparse__set_indices(glTFSparse* self, glTFSparseIndices* value) {
		self->indices = *value;
	}
	glTFSparseValues* DECL glTFSparse__get_values(glTFSparse* self) {
		return &self->values;
	}
	void DECL glTFSparse__set_values(glTFSparse* self, glTFSparseValues* value) {
		self->values = *value;
	}
	void DECL glTFSparse__destroy(glTFSparse* self) {
		delete self;
	}
	// glTFSparseIndices
	mud::Type* DECL glTFSparseIndices__type() {
		return &mud::type<glTFSparseIndices>();
	}
	glTFSparseIndices* DECL glTFSparseIndices__construct_0() {
		return new glTFSparseIndices();
	}
	int DECL glTFSparseIndices__get_buffer_view(glTFSparseIndices* self) {
		return self->buffer_view;
	}
	void DECL glTFSparseIndices__set_buffer_view(glTFSparseIndices* self, int value) {
		self->buffer_view = value;
	}
	int DECL glTFSparseIndices__get_byte_offset(glTFSparseIndices* self) {
		return self->byte_offset;
	}
	void DECL glTFSparseIndices__set_byte_offset(glTFSparseIndices* self, int value) {
		self->byte_offset = value;
	}
	glTFComponentType DECL glTFSparseIndices__get_component_type(glTFSparseIndices* self) {
		return self->component_type;
	}
	void DECL glTFSparseIndices__set_component_type(glTFSparseIndices* self, glTFComponentType value) {
		self->component_type = value;
	}
	void DECL glTFSparseIndices__destroy(glTFSparseIndices* self) {
		delete self;
	}
	// glTFSparseValues
	mud::Type* DECL glTFSparseValues__type() {
		return &mud::type<glTFSparseValues>();
	}
	glTFSparseValues* DECL glTFSparseValues__construct_0() {
		return new glTFSparseValues();
	}
	int DECL glTFSparseValues__get_buffer_view(glTFSparseValues* self) {
		return self->buffer_view;
	}
	void DECL glTFSparseValues__set_buffer_view(glTFSparseValues* self, int value) {
		self->buffer_view = value;
	}
	int DECL glTFSparseValues__get_byte_offset(glTFSparseValues* self) {
		return self->byte_offset;
	}
	void DECL glTFSparseValues__set_byte_offset(glTFSparseValues* self, int value) {
		self->byte_offset = value;
	}
	void DECL glTFSparseValues__destroy(glTFSparseValues* self) {
		delete self;
	}
	// glTFTexture
	mud::Type* DECL glTFTexture__type() {
		return &mud::type<glTFTexture>();
	}
	glTFTexture* DECL glTFTexture__construct_0() {
		return new glTFTexture();
	}
	const char* DECL glTFTexture__get_name(glTFTexture* self) {
		return self->name.c_str();
	}
	void DECL glTFTexture__set_name(glTFTexture* self, const char* value) {
		self->name = value;
	}
	int DECL glTFTexture__get_sampler(glTFTexture* self) {
		return self->sampler;
	}
	void DECL glTFTexture__set_sampler(glTFTexture* self, int value) {
		self->sampler = value;
	}
	int DECL glTFTexture__get_source(glTFTexture* self) {
		return self->source;
	}
	void DECL glTFTexture__set_source(glTFTexture* self, int value) {
		self->source = value;
	}
	void DECL glTFTexture__destroy(glTFTexture* self) {
		delete self;
	}
	// glTFTextureInfo
	mud::Type* DECL glTFTextureInfo__type() {
		return &mud::type<glTFTextureInfo>();
	}
	glTFTextureInfo* DECL glTFTextureInfo__construct_0() {
		return new glTFTextureInfo();
	}
	int DECL glTFTextureInfo__get_index(glTFTextureInfo* self) {
		return self->index;
	}
	void DECL glTFTextureInfo__set_index(glTFTextureInfo* self, int value) {
		self->index = value;
	}
	float DECL glTFTextureInfo__get_scale(glTFTextureInfo* self) {
		return self->scale;
	}
	void DECL glTFTextureInfo__set_scale(glTFTextureInfo* self, float value) {
		self->scale = value;
	}
	void DECL glTFTextureInfo__destroy(glTFTextureInfo* self) {
		delete self;
	}
	// glTFAlphaMode
	glTFAlphaMode DECL glTFAlphaMode_Opacity() {
		return glTFAlphaMode::Opacity;
	}
	glTFAlphaMode DECL glTFAlphaMode_MASK() {
		return glTFAlphaMode::MASK;
	}
	glTFAlphaMode DECL glTFAlphaMode_BLEND() {
		return glTFAlphaMode::BLEND;
	}
	// glTFComponentType
	glTFComponentType DECL glTFComponentType_BYTE() {
		return glTFComponentType::BYTE;
	}
	glTFComponentType DECL glTFComponentType_UNSIGNED_BYTE() {
		return glTFComponentType::UNSIGNED_BYTE;
	}
	glTFComponentType DECL glTFComponentType_SHORT() {
		return glTFComponentType::SHORT;
	}
	glTFComponentType DECL glTFComponentType_UNSIGNED_SHORT() {
		return glTFComponentType::UNSIGNED_SHORT;
	}
	glTFComponentType DECL glTFComponentType_INT() {
		return glTFComponentType::INT;
	}
	glTFComponentType DECL glTFComponentType_FLOAT() {
		return glTFComponentType::FLOAT;
	}
	// glTFInterpolation
	glTFInterpolation DECL glTFInterpolation_LINEAR() {
		return glTFInterpolation::LINEAR;
	}
	glTFInterpolation DECL glTFInterpolation_STEP() {
		return glTFInterpolation::STEP;
	}
	glTFInterpolation DECL glTFInterpolation_CATMULLROMSPLINE() {
		return glTFInterpolation::CATMULLROMSPLINE;
	}
	glTFInterpolation DECL glTFInterpolation_CUBIC_SPLINE() {
		return glTFInterpolation::CUBIC_SPLINE;
	}
	// glTFPrimitiveType
	glTFPrimitiveType DECL glTFPrimitiveType_POINTS() {
		return glTFPrimitiveType::POINTS;
	}
	glTFPrimitiveType DECL glTFPrimitiveType_LINES() {
		return glTFPrimitiveType::LINES;
	}
	glTFPrimitiveType DECL glTFPrimitiveType_LINE_LOOP() {
		return glTFPrimitiveType::LINE_LOOP;
	}
	glTFPrimitiveType DECL glTFPrimitiveType_LINE_STRIP() {
		return glTFPrimitiveType::LINE_STRIP;
	}
	glTFPrimitiveType DECL glTFPrimitiveType_TRIANGLES() {
		return glTFPrimitiveType::TRIANGLES;
	}
	glTFPrimitiveType DECL glTFPrimitiveType_TRIANGLE_STRIP() {
		return glTFPrimitiveType::TRIANGLE_STRIP;
	}
	glTFPrimitiveType DECL glTFPrimitiveType_TRIANGLE_FAN() {
		return glTFPrimitiveType::TRIANGLE_FAN;
	}
	// glTFType
	glTFType DECL glTFType_SCALAR() {
		return glTFType::SCALAR;
	}
	glTFType DECL glTFType_VEC2() {
		return glTFType::VEC2;
	}
	glTFType DECL glTFType_VEC3() {
		return glTFType::VEC3;
	}
	glTFType DECL glTFType_VEC4() {
		return glTFType::VEC4;
	}
	glTFType DECL glTFType_MAT2() {
		return glTFType::MAT2;
	}
	glTFType DECL glTFType_MAT3() {
		return glTFType::MAT3;
	}
	glTFType DECL glTFType_MAT4() {
		return glTFType::MAT4;
	}
	glTFType DECL glTFType_INVALID() {
		return glTFType::INVALID;
	}
	
}


