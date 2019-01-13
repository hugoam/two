#include <infra/Api.h>
#include <type/Api.h>
#include <refl/Api.h>
#include <srlz/Api.h>
#include <math/Api.h>
#include <gltf/Api.h>
#include <emscripten.h>
#include <cstdint>


extern "C" {
	
	// glTF
	glTF* EMSCRIPTEN_KEEPALIVE glTF_glTF_0() {
		return new glTF();
	}
	void EMSCRIPTEN_KEEPALIVE glTF___destroy__(glTF* self) {
		delete self;
	}
	// glTFAccessor
	glTFAccessor* EMSCRIPTEN_KEEPALIVE glTFAccessor_glTFAccessor_0() {
		return new glTFAccessor();
	}
	const char* EMSCRIPTEN_KEEPALIVE glTFAccessor_get_name(glTFAccessor* self) {
		return self->name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE glTFAccessor_set_name(glTFAccessor* self, const char* value) {
		self->name = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFAccessor_get_buffer_view(glTFAccessor* self) {
		return self->buffer_view;
	}
	void EMSCRIPTEN_KEEPALIVE glTFAccessor_set_buffer_view(glTFAccessor* self, int value) {
		self->buffer_view = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFAccessor_get_byte_offset(glTFAccessor* self) {
		return self->byte_offset;
	}
	void EMSCRIPTEN_KEEPALIVE glTFAccessor_set_byte_offset(glTFAccessor* self, int value) {
		self->byte_offset = value;
	}
	glTFComponentType EMSCRIPTEN_KEEPALIVE glTFAccessor_get_component_type(glTFAccessor* self) {
		return self->component_type;
	}
	void EMSCRIPTEN_KEEPALIVE glTFAccessor_set_component_type(glTFAccessor* self, glTFComponentType value) {
		self->component_type = value;
	}
	bool EMSCRIPTEN_KEEPALIVE glTFAccessor_get_normalized(glTFAccessor* self) {
		return self->normalized;
	}
	void EMSCRIPTEN_KEEPALIVE glTFAccessor_set_normalized(glTFAccessor* self, bool value) {
		self->normalized = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFAccessor_get_count(glTFAccessor* self) {
		return self->count;
	}
	void EMSCRIPTEN_KEEPALIVE glTFAccessor_set_count(glTFAccessor* self, int value) {
		self->count = value;
	}
	glTFType EMSCRIPTEN_KEEPALIVE glTFAccessor_get_type(glTFAccessor* self) {
		return self->type;
	}
	void EMSCRIPTEN_KEEPALIVE glTFAccessor_set_type(glTFAccessor* self, glTFType value) {
		self->type = value;
	}
	glTFSparse* EMSCRIPTEN_KEEPALIVE glTFAccessor_get_sparse(glTFAccessor* self) {
		static glTFSparse temp;
		return (temp = self->sparse, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE glTFAccessor_set_sparse(glTFAccessor* self, glTFSparse* value) {
		self->sparse = *value;
	}
	void EMSCRIPTEN_KEEPALIVE glTFAccessor___destroy__(glTFAccessor* self) {
		delete self;
	}
	// glTFAnimation
	glTFAnimation* EMSCRIPTEN_KEEPALIVE glTFAnimation_glTFAnimation_0() {
		return new glTFAnimation();
	}
	const char* EMSCRIPTEN_KEEPALIVE glTFAnimation_get_name(glTFAnimation* self) {
		return self->name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE glTFAnimation_set_name(glTFAnimation* self, const char* value) {
		self->name = value;
	}
	void EMSCRIPTEN_KEEPALIVE glTFAnimation___destroy__(glTFAnimation* self) {
		delete self;
	}
	// glTFAnimationChannel
	glTFAnimationChannel* EMSCRIPTEN_KEEPALIVE glTFAnimationChannel_glTFAnimationChannel_0() {
		return new glTFAnimationChannel();
	}
	int EMSCRIPTEN_KEEPALIVE glTFAnimationChannel_get_sampler(glTFAnimationChannel* self) {
		return self->sampler;
	}
	void EMSCRIPTEN_KEEPALIVE glTFAnimationChannel_set_sampler(glTFAnimationChannel* self, int value) {
		self->sampler = value;
	}
	glTFAnimationTarget* EMSCRIPTEN_KEEPALIVE glTFAnimationChannel_get_target(glTFAnimationChannel* self) {
		static glTFAnimationTarget temp;
		return (temp = self->target, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE glTFAnimationChannel_set_target(glTFAnimationChannel* self, glTFAnimationTarget* value) {
		self->target = *value;
	}
	void EMSCRIPTEN_KEEPALIVE glTFAnimationChannel___destroy__(glTFAnimationChannel* self) {
		delete self;
	}
	// glTFAnimationSampler
	glTFAnimationSampler* EMSCRIPTEN_KEEPALIVE glTFAnimationSampler_glTFAnimationSampler_0() {
		return new glTFAnimationSampler();
	}
	glTFInterpolation EMSCRIPTEN_KEEPALIVE glTFAnimationSampler_get_interpolation(glTFAnimationSampler* self) {
		return self->interpolation;
	}
	void EMSCRIPTEN_KEEPALIVE glTFAnimationSampler_set_interpolation(glTFAnimationSampler* self, glTFInterpolation value) {
		self->interpolation = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFAnimationSampler_get_input(glTFAnimationSampler* self) {
		return self->input;
	}
	void EMSCRIPTEN_KEEPALIVE glTFAnimationSampler_set_input(glTFAnimationSampler* self, int value) {
		self->input = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFAnimationSampler_get_output(glTFAnimationSampler* self) {
		return self->output;
	}
	void EMSCRIPTEN_KEEPALIVE glTFAnimationSampler_set_output(glTFAnimationSampler* self, int value) {
		self->output = value;
	}
	void EMSCRIPTEN_KEEPALIVE glTFAnimationSampler___destroy__(glTFAnimationSampler* self) {
		delete self;
	}
	// glTFAnimationTarget
	glTFAnimationTarget* EMSCRIPTEN_KEEPALIVE glTFAnimationTarget_glTFAnimationTarget_0() {
		return new glTFAnimationTarget();
	}
	int EMSCRIPTEN_KEEPALIVE glTFAnimationTarget_get_node(glTFAnimationTarget* self) {
		return self->node;
	}
	void EMSCRIPTEN_KEEPALIVE glTFAnimationTarget_set_node(glTFAnimationTarget* self, int value) {
		self->node = value;
	}
	const char* EMSCRIPTEN_KEEPALIVE glTFAnimationTarget_get_path(glTFAnimationTarget* self) {
		return self->path.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE glTFAnimationTarget_set_path(glTFAnimationTarget* self, const char* value) {
		self->path = value;
	}
	void EMSCRIPTEN_KEEPALIVE glTFAnimationTarget___destroy__(glTFAnimationTarget* self) {
		delete self;
	}
	// glTFAttributes
	glTFAttributes* EMSCRIPTEN_KEEPALIVE glTFAttributes_glTFAttributes_0() {
		return new glTFAttributes();
	}
	int EMSCRIPTEN_KEEPALIVE glTFAttributes_get_POSITION(glTFAttributes* self) {
		return self->POSITION;
	}
	void EMSCRIPTEN_KEEPALIVE glTFAttributes_set_POSITION(glTFAttributes* self, int value) {
		self->POSITION = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFAttributes_get_NORMAL(glTFAttributes* self) {
		return self->NORMAL;
	}
	void EMSCRIPTEN_KEEPALIVE glTFAttributes_set_NORMAL(glTFAttributes* self, int value) {
		self->NORMAL = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFAttributes_get_TANGENT(glTFAttributes* self) {
		return self->TANGENT;
	}
	void EMSCRIPTEN_KEEPALIVE glTFAttributes_set_TANGENT(glTFAttributes* self, int value) {
		self->TANGENT = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFAttributes_get_TEXCOORD_0(glTFAttributes* self) {
		return self->TEXCOORD_0;
	}
	void EMSCRIPTEN_KEEPALIVE glTFAttributes_set_TEXCOORD_0(glTFAttributes* self, int value) {
		self->TEXCOORD_0 = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFAttributes_get_TEXCOORD_1(glTFAttributes* self) {
		return self->TEXCOORD_1;
	}
	void EMSCRIPTEN_KEEPALIVE glTFAttributes_set_TEXCOORD_1(glTFAttributes* self, int value) {
		self->TEXCOORD_1 = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFAttributes_get_COLOR_0(glTFAttributes* self) {
		return self->COLOR_0;
	}
	void EMSCRIPTEN_KEEPALIVE glTFAttributes_set_COLOR_0(glTFAttributes* self, int value) {
		self->COLOR_0 = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFAttributes_get_JOINTS_0(glTFAttributes* self) {
		return self->JOINTS_0;
	}
	void EMSCRIPTEN_KEEPALIVE glTFAttributes_set_JOINTS_0(glTFAttributes* self, int value) {
		self->JOINTS_0 = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFAttributes_get_WEIGHTS_0(glTFAttributes* self) {
		return self->WEIGHTS_0;
	}
	void EMSCRIPTEN_KEEPALIVE glTFAttributes_set_WEIGHTS_0(glTFAttributes* self, int value) {
		self->WEIGHTS_0 = value;
	}
	void EMSCRIPTEN_KEEPALIVE glTFAttributes___destroy__(glTFAttributes* self) {
		delete self;
	}
	// glTFBuffer
	glTFBuffer* EMSCRIPTEN_KEEPALIVE glTFBuffer_glTFBuffer_0() {
		return new glTFBuffer();
	}
	const char* EMSCRIPTEN_KEEPALIVE glTFBuffer_get_name(glTFBuffer* self) {
		return self->name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE glTFBuffer_set_name(glTFBuffer* self, const char* value) {
		self->name = value;
	}
	const char* EMSCRIPTEN_KEEPALIVE glTFBuffer_get_mime_type(glTFBuffer* self) {
		return self->mime_type.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE glTFBuffer_set_mime_type(glTFBuffer* self, const char* value) {
		self->mime_type = value;
	}
	const char* EMSCRIPTEN_KEEPALIVE glTFBuffer_get_uri(glTFBuffer* self) {
		return self->uri.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE glTFBuffer_set_uri(glTFBuffer* self, const char* value) {
		self->uri = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFBuffer_get_byte_length(glTFBuffer* self) {
		return self->byte_length;
	}
	void EMSCRIPTEN_KEEPALIVE glTFBuffer_set_byte_length(glTFBuffer* self, int value) {
		self->byte_length = value;
	}
	void EMSCRIPTEN_KEEPALIVE glTFBuffer___destroy__(glTFBuffer* self) {
		delete self;
	}
	// glTFBufferView
	glTFBufferView* EMSCRIPTEN_KEEPALIVE glTFBufferView_glTFBufferView_0() {
		return new glTFBufferView();
	}
	const char* EMSCRIPTEN_KEEPALIVE glTFBufferView_get_name(glTFBufferView* self) {
		return self->name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE glTFBufferView_set_name(glTFBufferView* self, const char* value) {
		self->name = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFBufferView_get_buffer(glTFBufferView* self) {
		return self->buffer;
	}
	void EMSCRIPTEN_KEEPALIVE glTFBufferView_set_buffer(glTFBufferView* self, int value) {
		self->buffer = value;
	}
	size_t EMSCRIPTEN_KEEPALIVE glTFBufferView_get_byte_offset(glTFBufferView* self) {
		return self->byte_offset;
	}
	void EMSCRIPTEN_KEEPALIVE glTFBufferView_set_byte_offset(glTFBufferView* self, size_t value) {
		self->byte_offset = value;
	}
	size_t EMSCRIPTEN_KEEPALIVE glTFBufferView_get_byte_length(glTFBufferView* self) {
		return self->byte_length;
	}
	void EMSCRIPTEN_KEEPALIVE glTFBufferView_set_byte_length(glTFBufferView* self, size_t value) {
		self->byte_length = value;
	}
	size_t EMSCRIPTEN_KEEPALIVE glTFBufferView_get_byte_stride(glTFBufferView* self) {
		return self->byte_stride;
	}
	void EMSCRIPTEN_KEEPALIVE glTFBufferView_set_byte_stride(glTFBufferView* self, size_t value) {
		self->byte_stride = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFBufferView_get_target(glTFBufferView* self) {
		return self->target;
	}
	void EMSCRIPTEN_KEEPALIVE glTFBufferView_set_target(glTFBufferView* self, int value) {
		self->target = value;
	}
	void EMSCRIPTEN_KEEPALIVE glTFBufferView___destroy__(glTFBufferView* self) {
		delete self;
	}
	// glTFCamera
	glTFCamera* EMSCRIPTEN_KEEPALIVE glTFCamera_glTFCamera_0() {
		return new glTFCamera();
	}
	const char* EMSCRIPTEN_KEEPALIVE glTFCamera_get_name(glTFCamera* self) {
		return self->name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE glTFCamera_set_name(glTFCamera* self, const char* value) {
		self->name = value;
	}
	const char* EMSCRIPTEN_KEEPALIVE glTFCamera_get_type(glTFCamera* self) {
		return self->type.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE glTFCamera_set_type(glTFCamera* self, const char* value) {
		self->type = value;
	}
	glTFOrthographic* EMSCRIPTEN_KEEPALIVE glTFCamera_get_orthographic(glTFCamera* self) {
		static glTFOrthographic temp;
		return (temp = self->orthographic, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE glTFCamera_set_orthographic(glTFCamera* self, glTFOrthographic* value) {
		self->orthographic = *value;
	}
	glTFPerspective* EMSCRIPTEN_KEEPALIVE glTFCamera_get_perspective(glTFCamera* self) {
		static glTFPerspective temp;
		return (temp = self->perspective, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE glTFCamera_set_perspective(glTFCamera* self, glTFPerspective* value) {
		self->perspective = *value;
	}
	void EMSCRIPTEN_KEEPALIVE glTFCamera___destroy__(glTFCamera* self) {
		delete self;
	}
	// glTFImage
	glTFImage* EMSCRIPTEN_KEEPALIVE glTFImage_glTFImage_0() {
		return new glTFImage();
	}
	const char* EMSCRIPTEN_KEEPALIVE glTFImage_get_name(glTFImage* self) {
		return self->name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE glTFImage_set_name(glTFImage* self, const char* value) {
		self->name = value;
	}
	const char* EMSCRIPTEN_KEEPALIVE glTFImage_get_mime_type(glTFImage* self) {
		return self->mime_type.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE glTFImage_set_mime_type(glTFImage* self, const char* value) {
		self->mime_type = value;
	}
	const char* EMSCRIPTEN_KEEPALIVE glTFImage_get_uri(glTFImage* self) {
		return self->uri.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE glTFImage_set_uri(glTFImage* self, const char* value) {
		self->uri = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFImage_get_buffer_view(glTFImage* self) {
		return self->buffer_view;
	}
	void EMSCRIPTEN_KEEPALIVE glTFImage_set_buffer_view(glTFImage* self, int value) {
		self->buffer_view = value;
	}
	void EMSCRIPTEN_KEEPALIVE glTFImage___destroy__(glTFImage* self) {
		delete self;
	}
	// glTFMaterial
	glTFMaterial* EMSCRIPTEN_KEEPALIVE glTFMaterial_glTFMaterial_0() {
		return new glTFMaterial();
	}
	const char* EMSCRIPTEN_KEEPALIVE glTFMaterial_get_name(glTFMaterial* self) {
		return self->name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE glTFMaterial_set_name(glTFMaterial* self, const char* value) {
		self->name = value;
	}
	glTFTextureInfo* EMSCRIPTEN_KEEPALIVE glTFMaterial_get_normal_texture(glTFMaterial* self) {
		static glTFTextureInfo temp;
		return (temp = self->normal_texture, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE glTFMaterial_set_normal_texture(glTFMaterial* self, glTFTextureInfo* value) {
		self->normal_texture = *value;
	}
	glTFTextureInfo* EMSCRIPTEN_KEEPALIVE glTFMaterial_get_occlusion_texture(glTFMaterial* self) {
		static glTFTextureInfo temp;
		return (temp = self->occlusion_texture, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE glTFMaterial_set_occlusion_texture(glTFMaterial* self, glTFTextureInfo* value) {
		self->occlusion_texture = *value;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE glTFMaterial_get_emissive_factor(glTFMaterial* self) {
		static mud::vec3 temp;
		return (temp = self->emissive_factor, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE glTFMaterial_set_emissive_factor(glTFMaterial* self, mud::vec3* value) {
		self->emissive_factor = *value;
	}
	glTFTextureInfo* EMSCRIPTEN_KEEPALIVE glTFMaterial_get_emissive_texture(glTFMaterial* self) {
		static glTFTextureInfo temp;
		return (temp = self->emissive_texture, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE glTFMaterial_set_emissive_texture(glTFMaterial* self, glTFTextureInfo* value) {
		self->emissive_texture = *value;
	}
	bool EMSCRIPTEN_KEEPALIVE glTFMaterial_get_double_sided(glTFMaterial* self) {
		return self->double_sided;
	}
	void EMSCRIPTEN_KEEPALIVE glTFMaterial_set_double_sided(glTFMaterial* self, bool value) {
		self->double_sided = value;
	}
	glTFAlphaMode EMSCRIPTEN_KEEPALIVE glTFMaterial_get_alpha_mode(glTFMaterial* self) {
		return self->alpha_mode;
	}
	void EMSCRIPTEN_KEEPALIVE glTFMaterial_set_alpha_mode(glTFMaterial* self, glTFAlphaMode value) {
		self->alpha_mode = value;
	}
	glTFMaterialPBR* EMSCRIPTEN_KEEPALIVE glTFMaterial_get_pbr_metallic_roughness(glTFMaterial* self) {
		static glTFMaterialPBR temp;
		return (temp = self->pbr_metallic_roughness, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE glTFMaterial_set_pbr_metallic_roughness(glTFMaterial* self, glTFMaterialPBR* value) {
		self->pbr_metallic_roughness = *value;
	}
	void EMSCRIPTEN_KEEPALIVE glTFMaterial___destroy__(glTFMaterial* self) {
		delete self;
	}
	// glTFMaterialPBR
	glTFMaterialPBR* EMSCRIPTEN_KEEPALIVE glTFMaterialPBR_glTFMaterialPBR_0() {
		return new glTFMaterialPBR();
	}
	mud::vec4* EMSCRIPTEN_KEEPALIVE glTFMaterialPBR_get_base_color_factor(glTFMaterialPBR* self) {
		static mud::vec4 temp;
		return (temp = self->base_color_factor, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE glTFMaterialPBR_set_base_color_factor(glTFMaterialPBR* self, mud::vec4* value) {
		self->base_color_factor = *value;
	}
	glTFTextureInfo* EMSCRIPTEN_KEEPALIVE glTFMaterialPBR_get_base_color_texture(glTFMaterialPBR* self) {
		static glTFTextureInfo temp;
		return (temp = self->base_color_texture, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE glTFMaterialPBR_set_base_color_texture(glTFMaterialPBR* self, glTFTextureInfo* value) {
		self->base_color_texture = *value;
	}
	float EMSCRIPTEN_KEEPALIVE glTFMaterialPBR_get_metallic_factor(glTFMaterialPBR* self) {
		return self->metallic_factor;
	}
	void EMSCRIPTEN_KEEPALIVE glTFMaterialPBR_set_metallic_factor(glTFMaterialPBR* self, float value) {
		self->metallic_factor = value;
	}
	float EMSCRIPTEN_KEEPALIVE glTFMaterialPBR_get_roughness_factor(glTFMaterialPBR* self) {
		return self->roughness_factor;
	}
	void EMSCRIPTEN_KEEPALIVE glTFMaterialPBR_set_roughness_factor(glTFMaterialPBR* self, float value) {
		self->roughness_factor = value;
	}
	glTFTextureInfo* EMSCRIPTEN_KEEPALIVE glTFMaterialPBR_get_metallic_roughness_texture(glTFMaterialPBR* self) {
		static glTFTextureInfo temp;
		return (temp = self->metallic_roughness_texture, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE glTFMaterialPBR_set_metallic_roughness_texture(glTFMaterialPBR* self, glTFTextureInfo* value) {
		self->metallic_roughness_texture = *value;
	}
	void EMSCRIPTEN_KEEPALIVE glTFMaterialPBR___destroy__(glTFMaterialPBR* self) {
		delete self;
	}
	// glTFMesh
	glTFMesh* EMSCRIPTEN_KEEPALIVE glTFMesh_glTFMesh_0() {
		return new glTFMesh();
	}
	const char* EMSCRIPTEN_KEEPALIVE glTFMesh_get_name(glTFMesh* self) {
		return self->name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE glTFMesh_set_name(glTFMesh* self, const char* value) {
		self->name = value;
	}
	void EMSCRIPTEN_KEEPALIVE glTFMesh___destroy__(glTFMesh* self) {
		delete self;
	}
	// glTFMorphTarget
	glTFMorphTarget* EMSCRIPTEN_KEEPALIVE glTFMorphTarget_glTFMorphTarget_0() {
		return new glTFMorphTarget();
	}
	int EMSCRIPTEN_KEEPALIVE glTFMorphTarget_get_POSITION(glTFMorphTarget* self) {
		return self->POSITION;
	}
	void EMSCRIPTEN_KEEPALIVE glTFMorphTarget_set_POSITION(glTFMorphTarget* self, int value) {
		self->POSITION = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFMorphTarget_get_NORMAL(glTFMorphTarget* self) {
		return self->NORMAL;
	}
	void EMSCRIPTEN_KEEPALIVE glTFMorphTarget_set_NORMAL(glTFMorphTarget* self, int value) {
		self->NORMAL = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFMorphTarget_get_TANGENT(glTFMorphTarget* self) {
		return self->TANGENT;
	}
	void EMSCRIPTEN_KEEPALIVE glTFMorphTarget_set_TANGENT(glTFMorphTarget* self, int value) {
		self->TANGENT = value;
	}
	void EMSCRIPTEN_KEEPALIVE glTFMorphTarget___destroy__(glTFMorphTarget* self) {
		delete self;
	}
	// glTFNode
	glTFNode* EMSCRIPTEN_KEEPALIVE glTFNode_glTFNode_0() {
		return new glTFNode();
	}
	const char* EMSCRIPTEN_KEEPALIVE glTFNode_get_name(glTFNode* self) {
		return self->name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE glTFNode_set_name(glTFNode* self, const char* value) {
		self->name = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFNode_get_mesh(glTFNode* self) {
		return self->mesh;
	}
	void EMSCRIPTEN_KEEPALIVE glTFNode_set_mesh(glTFNode* self, int value) {
		self->mesh = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFNode_get_camera(glTFNode* self) {
		return self->camera;
	}
	void EMSCRIPTEN_KEEPALIVE glTFNode_set_camera(glTFNode* self, int value) {
		self->camera = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFNode_get_skin(glTFNode* self) {
		return self->skin;
	}
	void EMSCRIPTEN_KEEPALIVE glTFNode_set_skin(glTFNode* self, int value) {
		self->skin = value;
	}
	mud::mat4* EMSCRIPTEN_KEEPALIVE glTFNode_get_matrix(glTFNode* self) {
		static mud::mat4 temp;
		return (temp = self->matrix, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE glTFNode_set_matrix(glTFNode* self, mud::mat4* value) {
		self->matrix = *value;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE glTFNode_get_translation(glTFNode* self) {
		static mud::vec3 temp;
		return (temp = self->translation, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE glTFNode_set_translation(glTFNode* self, mud::vec3* value) {
		self->translation = *value;
	}
	mud::quat* EMSCRIPTEN_KEEPALIVE glTFNode_get_rotation(glTFNode* self) {
		static mud::quat temp;
		return (temp = self->rotation, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE glTFNode_set_rotation(glTFNode* self, mud::quat* value) {
		self->rotation = *value;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE glTFNode_get_scale(glTFNode* self) {
		static mud::vec3 temp;
		return (temp = self->scale, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE glTFNode_set_scale(glTFNode* self, mud::vec3* value) {
		self->scale = *value;
	}
	void EMSCRIPTEN_KEEPALIVE glTFNode___destroy__(glTFNode* self) {
		delete self;
	}
	// glTFNodeExtras
	glTFNodeExtras* EMSCRIPTEN_KEEPALIVE glTFNodeExtras_glTFNodeExtras_0() {
		return new glTFNodeExtras();
	}
	void EMSCRIPTEN_KEEPALIVE glTFNodeExtras___destroy__(glTFNodeExtras* self) {
		delete self;
	}
	// glTFOrthographic
	glTFOrthographic* EMSCRIPTEN_KEEPALIVE glTFOrthographic_glTFOrthographic_0() {
		return new glTFOrthographic();
	}
	float EMSCRIPTEN_KEEPALIVE glTFOrthographic_get_xmag(glTFOrthographic* self) {
		return self->xmag;
	}
	void EMSCRIPTEN_KEEPALIVE glTFOrthographic_set_xmag(glTFOrthographic* self, float value) {
		self->xmag = value;
	}
	float EMSCRIPTEN_KEEPALIVE glTFOrthographic_get_ymag(glTFOrthographic* self) {
		return self->ymag;
	}
	void EMSCRIPTEN_KEEPALIVE glTFOrthographic_set_ymag(glTFOrthographic* self, float value) {
		self->ymag = value;
	}
	float EMSCRIPTEN_KEEPALIVE glTFOrthographic_get_zfar(glTFOrthographic* self) {
		return self->zfar;
	}
	void EMSCRIPTEN_KEEPALIVE glTFOrthographic_set_zfar(glTFOrthographic* self, float value) {
		self->zfar = value;
	}
	float EMSCRIPTEN_KEEPALIVE glTFOrthographic_get_znear(glTFOrthographic* self) {
		return self->znear;
	}
	void EMSCRIPTEN_KEEPALIVE glTFOrthographic_set_znear(glTFOrthographic* self, float value) {
		self->znear = value;
	}
	void EMSCRIPTEN_KEEPALIVE glTFOrthographic___destroy__(glTFOrthographic* self) {
		delete self;
	}
	// glTFPerspective
	glTFPerspective* EMSCRIPTEN_KEEPALIVE glTFPerspective_glTFPerspective_0() {
		return new glTFPerspective();
	}
	float EMSCRIPTEN_KEEPALIVE glTFPerspective_get_yfov(glTFPerspective* self) {
		return self->yfov;
	}
	void EMSCRIPTEN_KEEPALIVE glTFPerspective_set_yfov(glTFPerspective* self, float value) {
		self->yfov = value;
	}
	float EMSCRIPTEN_KEEPALIVE glTFPerspective_get_zfar(glTFPerspective* self) {
		return self->zfar;
	}
	void EMSCRIPTEN_KEEPALIVE glTFPerspective_set_zfar(glTFPerspective* self, float value) {
		self->zfar = value;
	}
	float EMSCRIPTEN_KEEPALIVE glTFPerspective_get_znear(glTFPerspective* self) {
		return self->znear;
	}
	void EMSCRIPTEN_KEEPALIVE glTFPerspective_set_znear(glTFPerspective* self, float value) {
		self->znear = value;
	}
	float EMSCRIPTEN_KEEPALIVE glTFPerspective_get_aspect_ration(glTFPerspective* self) {
		return self->aspect_ration;
	}
	void EMSCRIPTEN_KEEPALIVE glTFPerspective_set_aspect_ration(glTFPerspective* self, float value) {
		self->aspect_ration = value;
	}
	void EMSCRIPTEN_KEEPALIVE glTFPerspective___destroy__(glTFPerspective* self) {
		delete self;
	}
	// glTFPrimitive
	glTFPrimitive* EMSCRIPTEN_KEEPALIVE glTFPrimitive_glTFPrimitive_0() {
		return new glTFPrimitive();
	}
	glTFAttributes* EMSCRIPTEN_KEEPALIVE glTFPrimitive_get_attributes(glTFPrimitive* self) {
		static glTFAttributes temp;
		return (temp = self->attributes, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE glTFPrimitive_set_attributes(glTFPrimitive* self, glTFAttributes* value) {
		self->attributes = *value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFPrimitive_get_indices(glTFPrimitive* self) {
		return self->indices;
	}
	void EMSCRIPTEN_KEEPALIVE glTFPrimitive_set_indices(glTFPrimitive* self, int value) {
		self->indices = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFPrimitive_get_material(glTFPrimitive* self) {
		return self->material;
	}
	void EMSCRIPTEN_KEEPALIVE glTFPrimitive_set_material(glTFPrimitive* self, int value) {
		self->material = value;
	}
	glTFPrimitiveType EMSCRIPTEN_KEEPALIVE glTFPrimitive_get_mode(glTFPrimitive* self) {
		return self->mode;
	}
	void EMSCRIPTEN_KEEPALIVE glTFPrimitive_set_mode(glTFPrimitive* self, glTFPrimitiveType value) {
		self->mode = value;
	}
	void EMSCRIPTEN_KEEPALIVE glTFPrimitive___destroy__(glTFPrimitive* self) {
		delete self;
	}
	// glTFSampler
	glTFSampler* EMSCRIPTEN_KEEPALIVE glTFSampler_glTFSampler_0() {
		return new glTFSampler();
	}
	int EMSCRIPTEN_KEEPALIVE glTFSampler_get_mag_filter(glTFSampler* self) {
		return self->mag_filter;
	}
	void EMSCRIPTEN_KEEPALIVE glTFSampler_set_mag_filter(glTFSampler* self, int value) {
		self->mag_filter = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFSampler_get_min_filter(glTFSampler* self) {
		return self->min_filter;
	}
	void EMSCRIPTEN_KEEPALIVE glTFSampler_set_min_filter(glTFSampler* self, int value) {
		self->min_filter = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFSampler_get_wrap_s(glTFSampler* self) {
		return self->wrap_s;
	}
	void EMSCRIPTEN_KEEPALIVE glTFSampler_set_wrap_s(glTFSampler* self, int value) {
		self->wrap_s = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFSampler_get_wrap_t(glTFSampler* self) {
		return self->wrap_t;
	}
	void EMSCRIPTEN_KEEPALIVE glTFSampler_set_wrap_t(glTFSampler* self, int value) {
		self->wrap_t = value;
	}
	const char* EMSCRIPTEN_KEEPALIVE glTFSampler_get_name(glTFSampler* self) {
		return self->name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE glTFSampler_set_name(glTFSampler* self, const char* value) {
		self->name = value;
	}
	void EMSCRIPTEN_KEEPALIVE glTFSampler___destroy__(glTFSampler* self) {
		delete self;
	}
	// glTFScene
	glTFScene* EMSCRIPTEN_KEEPALIVE glTFScene_glTFScene_0() {
		return new glTFScene();
	}
	const char* EMSCRIPTEN_KEEPALIVE glTFScene_get_name(glTFScene* self) {
		return self->name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE glTFScene_set_name(glTFScene* self, const char* value) {
		self->name = value;
	}
	void EMSCRIPTEN_KEEPALIVE glTFScene___destroy__(glTFScene* self) {
		delete self;
	}
	// glTFSkin
	glTFSkin* EMSCRIPTEN_KEEPALIVE glTFSkin_glTFSkin_0() {
		return new glTFSkin();
	}
	const char* EMSCRIPTEN_KEEPALIVE glTFSkin_get_name(glTFSkin* self) {
		return self->name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE glTFSkin_set_name(glTFSkin* self, const char* value) {
		self->name = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFSkin_get_skeleton(glTFSkin* self) {
		return self->skeleton;
	}
	void EMSCRIPTEN_KEEPALIVE glTFSkin_set_skeleton(glTFSkin* self, int value) {
		self->skeleton = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFSkin_get_inverse_bind_matrices(glTFSkin* self) {
		return self->inverse_bind_matrices;
	}
	void EMSCRIPTEN_KEEPALIVE glTFSkin_set_inverse_bind_matrices(glTFSkin* self, int value) {
		self->inverse_bind_matrices = value;
	}
	void EMSCRIPTEN_KEEPALIVE glTFSkin___destroy__(glTFSkin* self) {
		delete self;
	}
	// glTFSparse
	glTFSparse* EMSCRIPTEN_KEEPALIVE glTFSparse_glTFSparse_0() {
		return new glTFSparse();
	}
	int EMSCRIPTEN_KEEPALIVE glTFSparse_get_count(glTFSparse* self) {
		return self->count;
	}
	void EMSCRIPTEN_KEEPALIVE glTFSparse_set_count(glTFSparse* self, int value) {
		self->count = value;
	}
	glTFSparseIndices* EMSCRIPTEN_KEEPALIVE glTFSparse_get_indices(glTFSparse* self) {
		static glTFSparseIndices temp;
		return (temp = self->indices, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE glTFSparse_set_indices(glTFSparse* self, glTFSparseIndices* value) {
		self->indices = *value;
	}
	glTFSparseValues* EMSCRIPTEN_KEEPALIVE glTFSparse_get_values(glTFSparse* self) {
		static glTFSparseValues temp;
		return (temp = self->values, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE glTFSparse_set_values(glTFSparse* self, glTFSparseValues* value) {
		self->values = *value;
	}
	void EMSCRIPTEN_KEEPALIVE glTFSparse___destroy__(glTFSparse* self) {
		delete self;
	}
	// glTFSparseIndices
	glTFSparseIndices* EMSCRIPTEN_KEEPALIVE glTFSparseIndices_glTFSparseIndices_0() {
		return new glTFSparseIndices();
	}
	int EMSCRIPTEN_KEEPALIVE glTFSparseIndices_get_buffer_view(glTFSparseIndices* self) {
		return self->buffer_view;
	}
	void EMSCRIPTEN_KEEPALIVE glTFSparseIndices_set_buffer_view(glTFSparseIndices* self, int value) {
		self->buffer_view = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFSparseIndices_get_byte_offset(glTFSparseIndices* self) {
		return self->byte_offset;
	}
	void EMSCRIPTEN_KEEPALIVE glTFSparseIndices_set_byte_offset(glTFSparseIndices* self, int value) {
		self->byte_offset = value;
	}
	glTFComponentType EMSCRIPTEN_KEEPALIVE glTFSparseIndices_get_component_type(glTFSparseIndices* self) {
		return self->component_type;
	}
	void EMSCRIPTEN_KEEPALIVE glTFSparseIndices_set_component_type(glTFSparseIndices* self, glTFComponentType value) {
		self->component_type = value;
	}
	void EMSCRIPTEN_KEEPALIVE glTFSparseIndices___destroy__(glTFSparseIndices* self) {
		delete self;
	}
	// glTFSparseValues
	glTFSparseValues* EMSCRIPTEN_KEEPALIVE glTFSparseValues_glTFSparseValues_0() {
		return new glTFSparseValues();
	}
	int EMSCRIPTEN_KEEPALIVE glTFSparseValues_get_buffer_view(glTFSparseValues* self) {
		return self->buffer_view;
	}
	void EMSCRIPTEN_KEEPALIVE glTFSparseValues_set_buffer_view(glTFSparseValues* self, int value) {
		self->buffer_view = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFSparseValues_get_byte_offset(glTFSparseValues* self) {
		return self->byte_offset;
	}
	void EMSCRIPTEN_KEEPALIVE glTFSparseValues_set_byte_offset(glTFSparseValues* self, int value) {
		self->byte_offset = value;
	}
	void EMSCRIPTEN_KEEPALIVE glTFSparseValues___destroy__(glTFSparseValues* self) {
		delete self;
	}
	// glTFTexture
	glTFTexture* EMSCRIPTEN_KEEPALIVE glTFTexture_glTFTexture_0() {
		return new glTFTexture();
	}
	const char* EMSCRIPTEN_KEEPALIVE glTFTexture_get_name(glTFTexture* self) {
		return self->name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE glTFTexture_set_name(glTFTexture* self, const char* value) {
		self->name = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFTexture_get_sampler(glTFTexture* self) {
		return self->sampler;
	}
	void EMSCRIPTEN_KEEPALIVE glTFTexture_set_sampler(glTFTexture* self, int value) {
		self->sampler = value;
	}
	int EMSCRIPTEN_KEEPALIVE glTFTexture_get_source(glTFTexture* self) {
		return self->source;
	}
	void EMSCRIPTEN_KEEPALIVE glTFTexture_set_source(glTFTexture* self, int value) {
		self->source = value;
	}
	void EMSCRIPTEN_KEEPALIVE glTFTexture___destroy__(glTFTexture* self) {
		delete self;
	}
	// glTFTextureInfo
	glTFTextureInfo* EMSCRIPTEN_KEEPALIVE glTFTextureInfo_glTFTextureInfo_0() {
		return new glTFTextureInfo();
	}
	int EMSCRIPTEN_KEEPALIVE glTFTextureInfo_get_index(glTFTextureInfo* self) {
		return self->index;
	}
	void EMSCRIPTEN_KEEPALIVE glTFTextureInfo_set_index(glTFTextureInfo* self, int value) {
		self->index = value;
	}
	float EMSCRIPTEN_KEEPALIVE glTFTextureInfo_get_scale(glTFTextureInfo* self) {
		return self->scale;
	}
	void EMSCRIPTEN_KEEPALIVE glTFTextureInfo_set_scale(glTFTextureInfo* self, float value) {
		self->scale = value;
	}
	void EMSCRIPTEN_KEEPALIVE glTFTextureInfo___destroy__(glTFTextureInfo* self) {
		delete self;
	}
	// glTFAlphaMode
	glTFAlphaMode EMSCRIPTEN_KEEPALIVE glTFAlphaMode_OPAQUE() {
		return glTFAlphaMode::OPAQUE;
	}
	glTFAlphaMode EMSCRIPTEN_KEEPALIVE glTFAlphaMode_MASK() {
		return glTFAlphaMode::MASK;
	}
	glTFAlphaMode EMSCRIPTEN_KEEPALIVE glTFAlphaMode_BLEND() {
		return glTFAlphaMode::BLEND;
	}
	// glTFComponentType
	glTFComponentType EMSCRIPTEN_KEEPALIVE glTFComponentType_BYTE() {
		return glTFComponentType::BYTE;
	}
	glTFComponentType EMSCRIPTEN_KEEPALIVE glTFComponentType_UNSIGNED_BYTE() {
		return glTFComponentType::UNSIGNED_BYTE;
	}
	glTFComponentType EMSCRIPTEN_KEEPALIVE glTFComponentType_SHORT() {
		return glTFComponentType::SHORT;
	}
	glTFComponentType EMSCRIPTEN_KEEPALIVE glTFComponentType_UNSIGNED_SHORT() {
		return glTFComponentType::UNSIGNED_SHORT;
	}
	glTFComponentType EMSCRIPTEN_KEEPALIVE glTFComponentType_INT() {
		return glTFComponentType::INT;
	}
	glTFComponentType EMSCRIPTEN_KEEPALIVE glTFComponentType_FLOAT() {
		return glTFComponentType::FLOAT;
	}
	// glTFInterpolation
	glTFInterpolation EMSCRIPTEN_KEEPALIVE glTFInterpolation_LINEAR() {
		return glTFInterpolation::LINEAR;
	}
	glTFInterpolation EMSCRIPTEN_KEEPALIVE glTFInterpolation_STEP() {
		return glTFInterpolation::STEP;
	}
	glTFInterpolation EMSCRIPTEN_KEEPALIVE glTFInterpolation_CATMULLROMSPLINE() {
		return glTFInterpolation::CATMULLROMSPLINE;
	}
	glTFInterpolation EMSCRIPTEN_KEEPALIVE glTFInterpolation_CUBIC_SPLINE() {
		return glTFInterpolation::CUBIC_SPLINE;
	}
	// glTFPrimitiveType
	glTFPrimitiveType EMSCRIPTEN_KEEPALIVE glTFPrimitiveType_POINTS() {
		return glTFPrimitiveType::POINTS;
	}
	glTFPrimitiveType EMSCRIPTEN_KEEPALIVE glTFPrimitiveType_LINES() {
		return glTFPrimitiveType::LINES;
	}
	glTFPrimitiveType EMSCRIPTEN_KEEPALIVE glTFPrimitiveType_LINE_LOOP() {
		return glTFPrimitiveType::LINE_LOOP;
	}
	glTFPrimitiveType EMSCRIPTEN_KEEPALIVE glTFPrimitiveType_LINE_STRIP() {
		return glTFPrimitiveType::LINE_STRIP;
	}
	glTFPrimitiveType EMSCRIPTEN_KEEPALIVE glTFPrimitiveType_TRIANGLES() {
		return glTFPrimitiveType::TRIANGLES;
	}
	glTFPrimitiveType EMSCRIPTEN_KEEPALIVE glTFPrimitiveType_TRIANGLE_STRIP() {
		return glTFPrimitiveType::TRIANGLE_STRIP;
	}
	glTFPrimitiveType EMSCRIPTEN_KEEPALIVE glTFPrimitiveType_TRIANGLE_FAN() {
		return glTFPrimitiveType::TRIANGLE_FAN;
	}
	// glTFType
	glTFType EMSCRIPTEN_KEEPALIVE glTFType_SCALAR() {
		return glTFType::SCALAR;
	}
	glTFType EMSCRIPTEN_KEEPALIVE glTFType_VEC2() {
		return glTFType::VEC2;
	}
	glTFType EMSCRIPTEN_KEEPALIVE glTFType_VEC3() {
		return glTFType::VEC3;
	}
	glTFType EMSCRIPTEN_KEEPALIVE glTFType_VEC4() {
		return glTFType::VEC4;
	}
	glTFType EMSCRIPTEN_KEEPALIVE glTFType_MAT2() {
		return glTFType::MAT2;
	}
	glTFType EMSCRIPTEN_KEEPALIVE glTFType_MAT3() {
		return glTFType::MAT3;
	}
	glTFType EMSCRIPTEN_KEEPALIVE glTFType_MAT4() {
		return glTFType::MAT4;
	}
	glTFType EMSCRIPTEN_KEEPALIVE glTFType_INVALID() {
		return glTFType::INVALID;
	}
	
}


