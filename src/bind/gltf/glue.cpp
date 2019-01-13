#include <infra/Api.h>
#include <type/Api.h>
#include <refl/Api.h>
#include <srlz/Api.h>
#include <math/Api.h>
#include <gltf/Api.h>
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
	// glTF
	glTF* EMSCRIPTEN_KEEPALIVE glTF_glTF_0() {
		return new glTF();
	}
	std::vector<glTFBuffer> EMSCRIPTEN_KEEPALIVE glTF_get_buffers(glTF* self) {
		return self->m_buffers;
	}
	std::vector<glTFBufferView> EMSCRIPTEN_KEEPALIVE glTF_get_buffer_views(glTF* self) {
		return self->m_buffer_views;
	}
	std::vector<glTFAccessor> EMSCRIPTEN_KEEPALIVE glTF_get_accessors(glTF* self) {
		return self->m_accessors;
	}
	std::vector<glTFImage> EMSCRIPTEN_KEEPALIVE glTF_get_images(glTF* self) {
		return self->m_images;
	}
	std::vector<glTFTexture> EMSCRIPTEN_KEEPALIVE glTF_get_textures(glTF* self) {
		return self->m_textures;
	}
	std::vector<glTFMaterial> EMSCRIPTEN_KEEPALIVE glTF_get_materials(glTF* self) {
		return self->m_materials;
	}
	std::vector<glTFMesh> EMSCRIPTEN_KEEPALIVE glTF_get_meshes(glTF* self) {
		return self->m_meshes;
	}
	std::vector<glTFNode> EMSCRIPTEN_KEEPALIVE glTF_get_nodes(glTF* self) {
		return self->m_nodes;
	}
	std::vector<glTFSkin> EMSCRIPTEN_KEEPALIVE glTF_get_skins(glTF* self) {
		return self->m_skins;
	}
	std::vector<glTFAnimation> EMSCRIPTEN_KEEPALIVE glTF_get_animations(glTF* self) {
		return self->m_animations;
	}
	std::vector<glTFCamera> EMSCRIPTEN_KEEPALIVE glTF_get_cameras(glTF* self) {
		return self->m_cameras;
	}
	std::vector<glTFSampler> EMSCRIPTEN_KEEPALIVE glTF_get_samplers(glTF* self) {
		return self->m_samplers;
	}
	std::vector<glTFScene> EMSCRIPTEN_KEEPALIVE glTF_get_scenes(glTF* self) {
		return self->m_scenes;
	}
	void EMSCRIPTEN_KEEPALIVE glTF___destroy__(glTF* self) {
		delete self;
	}
	// glTFAccessor
	glTFAccessor* EMSCRIPTEN_KEEPALIVE glTFAccessor_glTFAccessor_0() {
		return new glTFAccessor();
	}
	std::string EMSCRIPTEN_KEEPALIVE glTFAccessor_get_name(glTFAccessor* self) {
		return self->name;
	}
	int EMSCRIPTEN_KEEPALIVE glTFAccessor_get_buffer_view(glTFAccessor* self) {
		return self->buffer_view;
	}
	int EMSCRIPTEN_KEEPALIVE glTFAccessor_get_byte_offset(glTFAccessor* self) {
		return self->byte_offset;
	}
	glTFComponentType EMSCRIPTEN_KEEPALIVE glTFAccessor_get_component_type(glTFAccessor* self) {
		return self->component_type;
	}
	bool EMSCRIPTEN_KEEPALIVE glTFAccessor_get_normalized(glTFAccessor* self) {
		return self->normalized;
	}
	int EMSCRIPTEN_KEEPALIVE glTFAccessor_get_count(glTFAccessor* self) {
		return self->count;
	}
	glTFType EMSCRIPTEN_KEEPALIVE glTFAccessor_get_type(glTFAccessor* self) {
		return self->type;
	}
	glTFSparse EMSCRIPTEN_KEEPALIVE glTFAccessor_get_sparse(glTFAccessor* self) {
		return self->sparse;
	}
	void EMSCRIPTEN_KEEPALIVE glTFAccessor___destroy__(glTFAccessor* self) {
		delete self;
	}
	// glTFAnimation
	glTFAnimation* EMSCRIPTEN_KEEPALIVE glTFAnimation_glTFAnimation_0() {
		return new glTFAnimation();
	}
	std::string EMSCRIPTEN_KEEPALIVE glTFAnimation_get_name(glTFAnimation* self) {
		return self->name;
	}
	std::vector<glTFAnimationSampler> EMSCRIPTEN_KEEPALIVE glTFAnimation_get_samplers(glTFAnimation* self) {
		return self->samplers;
	}
	std::vector<glTFAnimationChannel> EMSCRIPTEN_KEEPALIVE glTFAnimation_get_channels(glTFAnimation* self) {
		return self->channels;
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
	glTFAnimationTarget EMSCRIPTEN_KEEPALIVE glTFAnimationChannel_get_target(glTFAnimationChannel* self) {
		return self->target;
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
	int EMSCRIPTEN_KEEPALIVE glTFAnimationSampler_get_input(glTFAnimationSampler* self) {
		return self->input;
	}
	int EMSCRIPTEN_KEEPALIVE glTFAnimationSampler_get_output(glTFAnimationSampler* self) {
		return self->output;
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
	std::string EMSCRIPTEN_KEEPALIVE glTFAnimationTarget_get_path(glTFAnimationTarget* self) {
		return self->path;
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
	int EMSCRIPTEN_KEEPALIVE glTFAttributes_get_NORMAL(glTFAttributes* self) {
		return self->NORMAL;
	}
	int EMSCRIPTEN_KEEPALIVE glTFAttributes_get_TANGENT(glTFAttributes* self) {
		return self->TANGENT;
	}
	int EMSCRIPTEN_KEEPALIVE glTFAttributes_get_TEXCOORD_0(glTFAttributes* self) {
		return self->TEXCOORD_0;
	}
	int EMSCRIPTEN_KEEPALIVE glTFAttributes_get_TEXCOORD_1(glTFAttributes* self) {
		return self->TEXCOORD_1;
	}
	int EMSCRIPTEN_KEEPALIVE glTFAttributes_get_COLOR_0(glTFAttributes* self) {
		return self->COLOR_0;
	}
	int EMSCRIPTEN_KEEPALIVE glTFAttributes_get_JOINTS_0(glTFAttributes* self) {
		return self->JOINTS_0;
	}
	int EMSCRIPTEN_KEEPALIVE glTFAttributes_get_WEIGHTS_0(glTFAttributes* self) {
		return self->WEIGHTS_0;
	}
	void EMSCRIPTEN_KEEPALIVE glTFAttributes___destroy__(glTFAttributes* self) {
		delete self;
	}
	// glTFBuffer
	glTFBuffer* EMSCRIPTEN_KEEPALIVE glTFBuffer_glTFBuffer_0() {
		return new glTFBuffer();
	}
	std::string EMSCRIPTEN_KEEPALIVE glTFBuffer_get_name(glTFBuffer* self) {
		return self->name;
	}
	std::string EMSCRIPTEN_KEEPALIVE glTFBuffer_get_mime_type(glTFBuffer* self) {
		return self->mime_type;
	}
	std::string EMSCRIPTEN_KEEPALIVE glTFBuffer_get_uri(glTFBuffer* self) {
		return self->uri;
	}
	int EMSCRIPTEN_KEEPALIVE glTFBuffer_get_byte_length(glTFBuffer* self) {
		return self->byte_length;
	}
	void EMSCRIPTEN_KEEPALIVE glTFBuffer___destroy__(glTFBuffer* self) {
		delete self;
	}
	// glTFBufferView
	glTFBufferView* EMSCRIPTEN_KEEPALIVE glTFBufferView_glTFBufferView_0() {
		return new glTFBufferView();
	}
	std::string EMSCRIPTEN_KEEPALIVE glTFBufferView_get_name(glTFBufferView* self) {
		return self->name;
	}
	int EMSCRIPTEN_KEEPALIVE glTFBufferView_get_buffer(glTFBufferView* self) {
		return self->buffer;
	}
	size_t EMSCRIPTEN_KEEPALIVE glTFBufferView_get_byte_offset(glTFBufferView* self) {
		return self->byte_offset;
	}
	size_t EMSCRIPTEN_KEEPALIVE glTFBufferView_get_byte_length(glTFBufferView* self) {
		return self->byte_length;
	}
	size_t EMSCRIPTEN_KEEPALIVE glTFBufferView_get_byte_stride(glTFBufferView* self) {
		return self->byte_stride;
	}
	int EMSCRIPTEN_KEEPALIVE glTFBufferView_get_target(glTFBufferView* self) {
		return self->target;
	}
	void EMSCRIPTEN_KEEPALIVE glTFBufferView___destroy__(glTFBufferView* self) {
		delete self;
	}
	// glTFCamera
	glTFCamera* EMSCRIPTEN_KEEPALIVE glTFCamera_glTFCamera_0() {
		return new glTFCamera();
	}
	std::string EMSCRIPTEN_KEEPALIVE glTFCamera_get_name(glTFCamera* self) {
		return self->name;
	}
	std::string EMSCRIPTEN_KEEPALIVE glTFCamera_get_type(glTFCamera* self) {
		return self->type;
	}
	glTFOrthographic EMSCRIPTEN_KEEPALIVE glTFCamera_get_orthographic(glTFCamera* self) {
		return self->orthographic;
	}
	glTFPerspective EMSCRIPTEN_KEEPALIVE glTFCamera_get_perspective(glTFCamera* self) {
		return self->perspective;
	}
	void EMSCRIPTEN_KEEPALIVE glTFCamera___destroy__(glTFCamera* self) {
		delete self;
	}
	// glTFImage
	glTFImage* EMSCRIPTEN_KEEPALIVE glTFImage_glTFImage_0() {
		return new glTFImage();
	}
	std::string EMSCRIPTEN_KEEPALIVE glTFImage_get_name(glTFImage* self) {
		return self->name;
	}
	std::string EMSCRIPTEN_KEEPALIVE glTFImage_get_mime_type(glTFImage* self) {
		return self->mime_type;
	}
	std::string EMSCRIPTEN_KEEPALIVE glTFImage_get_uri(glTFImage* self) {
		return self->uri;
	}
	int EMSCRIPTEN_KEEPALIVE glTFImage_get_buffer_view(glTFImage* self) {
		return self->buffer_view;
	}
	void EMSCRIPTEN_KEEPALIVE glTFImage___destroy__(glTFImage* self) {
		delete self;
	}
	// glTFMaterial
	glTFMaterial* EMSCRIPTEN_KEEPALIVE glTFMaterial_glTFMaterial_0() {
		return new glTFMaterial();
	}
	std::string EMSCRIPTEN_KEEPALIVE glTFMaterial_get_name(glTFMaterial* self) {
		return self->name;
	}
	glTFTextureInfo EMSCRIPTEN_KEEPALIVE glTFMaterial_get_normal_texture(glTFMaterial* self) {
		return self->normal_texture;
	}
	glTFTextureInfo EMSCRIPTEN_KEEPALIVE glTFMaterial_get_occlusion_texture(glTFMaterial* self) {
		return self->occlusion_texture;
	}
	vec3 EMSCRIPTEN_KEEPALIVE glTFMaterial_get_emissive_factor(glTFMaterial* self) {
		return self->emissive_factor;
	}
	glTFTextureInfo EMSCRIPTEN_KEEPALIVE glTFMaterial_get_emissive_texture(glTFMaterial* self) {
		return self->emissive_texture;
	}
	bool EMSCRIPTEN_KEEPALIVE glTFMaterial_get_double_sided(glTFMaterial* self) {
		return self->double_sided;
	}
	glTFAlphaMode EMSCRIPTEN_KEEPALIVE glTFMaterial_get_alpha_mode(glTFMaterial* self) {
		return self->alpha_mode;
	}
	glTFMaterialPBR EMSCRIPTEN_KEEPALIVE glTFMaterial_get_pbr_metallic_roughness(glTFMaterial* self) {
		return self->pbr_metallic_roughness;
	}
	void EMSCRIPTEN_KEEPALIVE glTFMaterial___destroy__(glTFMaterial* self) {
		delete self;
	}
	// glTFMaterialPBR
	glTFMaterialPBR* EMSCRIPTEN_KEEPALIVE glTFMaterialPBR_glTFMaterialPBR_0() {
		return new glTFMaterialPBR();
	}
	vec4 EMSCRIPTEN_KEEPALIVE glTFMaterialPBR_get_base_color_factor(glTFMaterialPBR* self) {
		return self->base_color_factor;
	}
	glTFTextureInfo EMSCRIPTEN_KEEPALIVE glTFMaterialPBR_get_base_color_texture(glTFMaterialPBR* self) {
		return self->base_color_texture;
	}
	float EMSCRIPTEN_KEEPALIVE glTFMaterialPBR_get_metallic_factor(glTFMaterialPBR* self) {
		return self->metallic_factor;
	}
	float EMSCRIPTEN_KEEPALIVE glTFMaterialPBR_get_roughness_factor(glTFMaterialPBR* self) {
		return self->roughness_factor;
	}
	glTFTextureInfo EMSCRIPTEN_KEEPALIVE glTFMaterialPBR_get_metallic_roughness_texture(glTFMaterialPBR* self) {
		return self->metallic_roughness_texture;
	}
	void EMSCRIPTEN_KEEPALIVE glTFMaterialPBR___destroy__(glTFMaterialPBR* self) {
		delete self;
	}
	// glTFMesh
	glTFMesh* EMSCRIPTEN_KEEPALIVE glTFMesh_glTFMesh_0() {
		return new glTFMesh();
	}
	std::string EMSCRIPTEN_KEEPALIVE glTFMesh_get_name(glTFMesh* self) {
		return self->name;
	}
	std::vector<glTFPrimitive> EMSCRIPTEN_KEEPALIVE glTFMesh_get_primitives(glTFMesh* self) {
		return self->primitives;
	}
	std::vector<float> EMSCRIPTEN_KEEPALIVE glTFMesh_get_weights(glTFMesh* self) {
		return self->weights;
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
	int EMSCRIPTEN_KEEPALIVE glTFMorphTarget_get_NORMAL(glTFMorphTarget* self) {
		return self->NORMAL;
	}
	int EMSCRIPTEN_KEEPALIVE glTFMorphTarget_get_TANGENT(glTFMorphTarget* self) {
		return self->TANGENT;
	}
	void EMSCRIPTEN_KEEPALIVE glTFMorphTarget___destroy__(glTFMorphTarget* self) {
		delete self;
	}
	// glTFNode
	glTFNode* EMSCRIPTEN_KEEPALIVE glTFNode_glTFNode_0() {
		return new glTFNode();
	}
	std::string EMSCRIPTEN_KEEPALIVE glTFNode_get_name(glTFNode* self) {
		return self->name;
	}
	int EMSCRIPTEN_KEEPALIVE glTFNode_get_mesh(glTFNode* self) {
		return self->mesh;
	}
	int EMSCRIPTEN_KEEPALIVE glTFNode_get_camera(glTFNode* self) {
		return self->camera;
	}
	int EMSCRIPTEN_KEEPALIVE glTFNode_get_skin(glTFNode* self) {
		return self->skin;
	}
	mat4 EMSCRIPTEN_KEEPALIVE glTFNode_get_matrix(glTFNode* self) {
		return self->matrix;
	}
	vec3 EMSCRIPTEN_KEEPALIVE glTFNode_get_translation(glTFNode* self) {
		return self->translation;
	}
	quat EMSCRIPTEN_KEEPALIVE glTFNode_get_rotation(glTFNode* self) {
		return self->rotation;
	}
	vec3 EMSCRIPTEN_KEEPALIVE glTFNode_get_scale(glTFNode* self) {
		return self->scale;
	}
	std::vector<int> EMSCRIPTEN_KEEPALIVE glTFNode_get_children(glTFNode* self) {
		return self->children;
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
	float EMSCRIPTEN_KEEPALIVE glTFOrthographic_get_ymag(glTFOrthographic* self) {
		return self->ymag;
	}
	float EMSCRIPTEN_KEEPALIVE glTFOrthographic_get_zfar(glTFOrthographic* self) {
		return self->zfar;
	}
	float EMSCRIPTEN_KEEPALIVE glTFOrthographic_get_znear(glTFOrthographic* self) {
		return self->znear;
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
	float EMSCRIPTEN_KEEPALIVE glTFPerspective_get_zfar(glTFPerspective* self) {
		return self->zfar;
	}
	float EMSCRIPTEN_KEEPALIVE glTFPerspective_get_znear(glTFPerspective* self) {
		return self->znear;
	}
	float EMSCRIPTEN_KEEPALIVE glTFPerspective_get_aspect_ration(glTFPerspective* self) {
		return self->aspect_ration;
	}
	void EMSCRIPTEN_KEEPALIVE glTFPerspective___destroy__(glTFPerspective* self) {
		delete self;
	}
	// glTFPrimitive
	glTFPrimitive* EMSCRIPTEN_KEEPALIVE glTFPrimitive_glTFPrimitive_0() {
		return new glTFPrimitive();
	}
	glTFAttributes EMSCRIPTEN_KEEPALIVE glTFPrimitive_get_attributes(glTFPrimitive* self) {
		return self->attributes;
	}
	int EMSCRIPTEN_KEEPALIVE glTFPrimitive_get_indices(glTFPrimitive* self) {
		return self->indices;
	}
	int EMSCRIPTEN_KEEPALIVE glTFPrimitive_get_material(glTFPrimitive* self) {
		return self->material;
	}
	glTFPrimitiveType EMSCRIPTEN_KEEPALIVE glTFPrimitive_get_mode(glTFPrimitive* self) {
		return self->mode;
	}
	std::vector<glTFMorphTarget> EMSCRIPTEN_KEEPALIVE glTFPrimitive_get_targets(glTFPrimitive* self) {
		return self->targets;
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
	int EMSCRIPTEN_KEEPALIVE glTFSampler_get_min_filter(glTFSampler* self) {
		return self->min_filter;
	}
	int EMSCRIPTEN_KEEPALIVE glTFSampler_get_wrap_s(glTFSampler* self) {
		return self->wrap_s;
	}
	int EMSCRIPTEN_KEEPALIVE glTFSampler_get_wrap_t(glTFSampler* self) {
		return self->wrap_t;
	}
	std::string EMSCRIPTEN_KEEPALIVE glTFSampler_get_name(glTFSampler* self) {
		return self->name;
	}
	void EMSCRIPTEN_KEEPALIVE glTFSampler___destroy__(glTFSampler* self) {
		delete self;
	}
	// glTFScene
	glTFScene* EMSCRIPTEN_KEEPALIVE glTFScene_glTFScene_0() {
		return new glTFScene();
	}
	std::string EMSCRIPTEN_KEEPALIVE glTFScene_get_name(glTFScene* self) {
		return self->name;
	}
	std::vector<int> EMSCRIPTEN_KEEPALIVE glTFScene_get_nodes(glTFScene* self) {
		return self->nodes;
	}
	void EMSCRIPTEN_KEEPALIVE glTFScene___destroy__(glTFScene* self) {
		delete self;
	}
	// glTFSkin
	glTFSkin* EMSCRIPTEN_KEEPALIVE glTFSkin_glTFSkin_0() {
		return new glTFSkin();
	}
	std::string EMSCRIPTEN_KEEPALIVE glTFSkin_get_name(glTFSkin* self) {
		return self->name;
	}
	int EMSCRIPTEN_KEEPALIVE glTFSkin_get_skeleton(glTFSkin* self) {
		return self->skeleton;
	}
	std::vector<int> EMSCRIPTEN_KEEPALIVE glTFSkin_get_joints(glTFSkin* self) {
		return self->joints;
	}
	int EMSCRIPTEN_KEEPALIVE glTFSkin_get_inverse_bind_matrices(glTFSkin* self) {
		return self->inverse_bind_matrices;
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
	glTFSparseIndices EMSCRIPTEN_KEEPALIVE glTFSparse_get_indices(glTFSparse* self) {
		return self->indices;
	}
	glTFSparseValues EMSCRIPTEN_KEEPALIVE glTFSparse_get_values(glTFSparse* self) {
		return self->values;
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
	int EMSCRIPTEN_KEEPALIVE glTFSparseIndices_get_byte_offset(glTFSparseIndices* self) {
		return self->byte_offset;
	}
	glTFComponentType EMSCRIPTEN_KEEPALIVE glTFSparseIndices_get_component_type(glTFSparseIndices* self) {
		return self->component_type;
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
	int EMSCRIPTEN_KEEPALIVE glTFSparseValues_get_byte_offset(glTFSparseValues* self) {
		return self->byte_offset;
	}
	void EMSCRIPTEN_KEEPALIVE glTFSparseValues___destroy__(glTFSparseValues* self) {
		delete self;
	}
	// glTFTexture
	glTFTexture* EMSCRIPTEN_KEEPALIVE glTFTexture_glTFTexture_0() {
		return new glTFTexture();
	}
	std::string EMSCRIPTEN_KEEPALIVE glTFTexture_get_name(glTFTexture* self) {
		return self->name;
	}
	int EMSCRIPTEN_KEEPALIVE glTFTexture_get_sampler(glTFTexture* self) {
		return self->sampler;
	}
	int EMSCRIPTEN_KEEPALIVE glTFTexture_get_source(glTFTexture* self) {
		return self->source;
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
	float EMSCRIPTEN_KEEPALIVE glTFTextureInfo_get_scale(glTFTextureInfo* self) {
		return self->scale;
	}
	void EMSCRIPTEN_KEEPALIVE glTFTextureInfo___destroy__(glTFTextureInfo* self) {
		delete self;
	}
	// glTFAlphaMode
	glTFAlphaMode EMSCRIPTEN_KEEPALIVE emscripten_enum_glTFAlphaMode_OPAQUE() {
		return glTFAlphaMode::OPAQUE;
	}
	glTFAlphaMode EMSCRIPTEN_KEEPALIVE emscripten_enum_glTFAlphaMode_MASK() {
		return glTFAlphaMode::MASK;
	}
	glTFAlphaMode EMSCRIPTEN_KEEPALIVE emscripten_enum_glTFAlphaMode_BLEND() {
		return glTFAlphaMode::BLEND;
	}
	// glTFComponentType
	glTFComponentType EMSCRIPTEN_KEEPALIVE emscripten_enum_glTFComponentType_BYTE() {
		return glTFComponentType::BYTE;
	}
	glTFComponentType EMSCRIPTEN_KEEPALIVE emscripten_enum_glTFComponentType_UNSIGNED_BYTE() {
		return glTFComponentType::UNSIGNED_BYTE;
	}
	glTFComponentType EMSCRIPTEN_KEEPALIVE emscripten_enum_glTFComponentType_SHORT() {
		return glTFComponentType::SHORT;
	}
	glTFComponentType EMSCRIPTEN_KEEPALIVE emscripten_enum_glTFComponentType_UNSIGNED_SHORT() {
		return glTFComponentType::UNSIGNED_SHORT;
	}
	glTFComponentType EMSCRIPTEN_KEEPALIVE emscripten_enum_glTFComponentType_INT() {
		return glTFComponentType::INT;
	}
	glTFComponentType EMSCRIPTEN_KEEPALIVE emscripten_enum_glTFComponentType_FLOAT() {
		return glTFComponentType::FLOAT;
	}
	// glTFInterpolation
	glTFInterpolation EMSCRIPTEN_KEEPALIVE emscripten_enum_glTFInterpolation_LINEAR() {
		return glTFInterpolation::LINEAR;
	}
	glTFInterpolation EMSCRIPTEN_KEEPALIVE emscripten_enum_glTFInterpolation_STEP() {
		return glTFInterpolation::STEP;
	}
	glTFInterpolation EMSCRIPTEN_KEEPALIVE emscripten_enum_glTFInterpolation_CATMULLROMSPLINE() {
		return glTFInterpolation::CATMULLROMSPLINE;
	}
	glTFInterpolation EMSCRIPTEN_KEEPALIVE emscripten_enum_glTFInterpolation_CUBIC_SPLINE() {
		return glTFInterpolation::CUBIC_SPLINE;
	}
	// glTFPrimitiveType
	glTFPrimitiveType EMSCRIPTEN_KEEPALIVE emscripten_enum_glTFPrimitiveType_POINTS() {
		return glTFPrimitiveType::POINTS;
	}
	glTFPrimitiveType EMSCRIPTEN_KEEPALIVE emscripten_enum_glTFPrimitiveType_LINES() {
		return glTFPrimitiveType::LINES;
	}
	glTFPrimitiveType EMSCRIPTEN_KEEPALIVE emscripten_enum_glTFPrimitiveType_LINE_LOOP() {
		return glTFPrimitiveType::LINE_LOOP;
	}
	glTFPrimitiveType EMSCRIPTEN_KEEPALIVE emscripten_enum_glTFPrimitiveType_LINE_STRIP() {
		return glTFPrimitiveType::LINE_STRIP;
	}
	glTFPrimitiveType EMSCRIPTEN_KEEPALIVE emscripten_enum_glTFPrimitiveType_TRIANGLES() {
		return glTFPrimitiveType::TRIANGLES;
	}
	glTFPrimitiveType EMSCRIPTEN_KEEPALIVE emscripten_enum_glTFPrimitiveType_TRIANGLE_STRIP() {
		return glTFPrimitiveType::TRIANGLE_STRIP;
	}
	glTFPrimitiveType EMSCRIPTEN_KEEPALIVE emscripten_enum_glTFPrimitiveType_TRIANGLE_FAN() {
		return glTFPrimitiveType::TRIANGLE_FAN;
	}
	// glTFType
	glTFType EMSCRIPTEN_KEEPALIVE emscripten_enum_glTFType_SCALAR() {
		return glTFType::SCALAR;
	}
	glTFType EMSCRIPTEN_KEEPALIVE emscripten_enum_glTFType_VEC2() {
		return glTFType::VEC2;
	}
	glTFType EMSCRIPTEN_KEEPALIVE emscripten_enum_glTFType_VEC3() {
		return glTFType::VEC3;
	}
	glTFType EMSCRIPTEN_KEEPALIVE emscripten_enum_glTFType_VEC4() {
		return glTFType::VEC4;
	}
	glTFType EMSCRIPTEN_KEEPALIVE emscripten_enum_glTFType_MAT2() {
		return glTFType::MAT2;
	}
	glTFType EMSCRIPTEN_KEEPALIVE emscripten_enum_glTFType_MAT3() {
		return glTFType::MAT3;
	}
	glTFType EMSCRIPTEN_KEEPALIVE emscripten_enum_glTFType_MAT4() {
		return glTFType::MAT4;
	}
	glTFType EMSCRIPTEN_KEEPALIVE emscripten_enum_glTFType_INVALID() {
		return glTFType::INVALID;
	}
	
}


