#include <mud/srlz.refl.h>
#include <mud/infra.refl.h>
#include <mud/type.refl.h>
#include <mud/gltf.h>
#include <mud/refl.refl.h>
#include <mud/refl.h>
#include <mud/math.refl.h>
#include <mud/infra.h>
#include <mud/type.h>
#include <mud/gltf.refl.h>


#ifdef MUD_MODULES
module mud.gltf;
#else
#include <cstddef>
#include <stl/new.h>
#endif


using namespace mud;

void glTFAlphaMode__to_string(void* val, string& str) { str = g_enu[type<glTFAlphaMode>().m_id]->name(uint32_t((*static_cast<glTFAlphaMode*>(val)))); }
void glTFAlphaMode__to_value(const string& str, void* val) { (*static_cast<glTFAlphaMode*>(val)) = glTFAlphaMode(g_enu[type<glTFAlphaMode>().m_id]->value(str.c_str())); }
void glTFComponentType__to_string(void* val, string& str) { str = g_enu[type<glTFComponentType>().m_id]->name(uint32_t((*static_cast<glTFComponentType*>(val)))); }
void glTFComponentType__to_value(const string& str, void* val) { (*static_cast<glTFComponentType*>(val)) = glTFComponentType(g_enu[type<glTFComponentType>().m_id]->value(str.c_str())); }
void glTFInterpolation__to_string(void* val, string& str) { str = g_enu[type<glTFInterpolation>().m_id]->name(uint32_t((*static_cast<glTFInterpolation*>(val)))); }
void glTFInterpolation__to_value(const string& str, void* val) { (*static_cast<glTFInterpolation*>(val)) = glTFInterpolation(g_enu[type<glTFInterpolation>().m_id]->value(str.c_str())); }
void glTFPrimitiveType__to_string(void* val, string& str) { str = g_enu[type<glTFPrimitiveType>().m_id]->name(uint32_t((*static_cast<glTFPrimitiveType*>(val)))); }
void glTFPrimitiveType__to_value(const string& str, void* val) { (*static_cast<glTFPrimitiveType*>(val)) = glTFPrimitiveType(g_enu[type<glTFPrimitiveType>().m_id]->value(str.c_str())); }
void glTFType__to_string(void* val, string& str) { str = g_enu[type<glTFType>().m_id]->name(uint32_t((*static_cast<glTFType*>(val)))); }
void glTFType__to_value(const string& str, void* val) { (*static_cast<glTFType*>(val)) = glTFType(g_enu[type<glTFType>().m_id]->value(str.c_str())); }
size_t stl_vector_glTFAccessor__size(void* vec) { return (*static_cast<stl::vector<glTFAccessor>*>(vec)).size(); }
void* stl_vector_glTFAccessor__at(void* vec, size_t i) { return &(*static_cast<stl::vector<glTFAccessor>*>(vec))[i]; }
void stl_vector_glTFAccessor__push(void* vec) { (*static_cast<stl::vector<glTFAccessor>*>(vec)).emplace_back(); }
void stl_vector_glTFAccessor__add(void* vec, void* value) { (*static_cast<stl::vector<glTFAccessor>*>(vec)).push_back(*static_cast<glTFAccessor*>(value)); }
void stl_vector_glTFAccessor__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<glTFAccessor>*>(vec)), *static_cast<glTFAccessor*>(value)); }
size_t stl_vector_glTFAnimation__size(void* vec) { return (*static_cast<stl::vector<glTFAnimation>*>(vec)).size(); }
void* stl_vector_glTFAnimation__at(void* vec, size_t i) { return &(*static_cast<stl::vector<glTFAnimation>*>(vec))[i]; }
void stl_vector_glTFAnimation__push(void* vec) { (*static_cast<stl::vector<glTFAnimation>*>(vec)).emplace_back(); }
void stl_vector_glTFAnimation__add(void* vec, void* value) { (*static_cast<stl::vector<glTFAnimation>*>(vec)).push_back(*static_cast<glTFAnimation*>(value)); }
void stl_vector_glTFAnimation__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<glTFAnimation>*>(vec)), *static_cast<glTFAnimation*>(value)); }
size_t stl_vector_glTFAnimationChannel__size(void* vec) { return (*static_cast<stl::vector<glTFAnimationChannel>*>(vec)).size(); }
void* stl_vector_glTFAnimationChannel__at(void* vec, size_t i) { return &(*static_cast<stl::vector<glTFAnimationChannel>*>(vec))[i]; }
void stl_vector_glTFAnimationChannel__push(void* vec) { (*static_cast<stl::vector<glTFAnimationChannel>*>(vec)).emplace_back(); }
void stl_vector_glTFAnimationChannel__add(void* vec, void* value) { (*static_cast<stl::vector<glTFAnimationChannel>*>(vec)).push_back(*static_cast<glTFAnimationChannel*>(value)); }
void stl_vector_glTFAnimationChannel__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<glTFAnimationChannel>*>(vec)), *static_cast<glTFAnimationChannel*>(value)); }
size_t stl_vector_glTFAnimationSampler__size(void* vec) { return (*static_cast<stl::vector<glTFAnimationSampler>*>(vec)).size(); }
void* stl_vector_glTFAnimationSampler__at(void* vec, size_t i) { return &(*static_cast<stl::vector<glTFAnimationSampler>*>(vec))[i]; }
void stl_vector_glTFAnimationSampler__push(void* vec) { (*static_cast<stl::vector<glTFAnimationSampler>*>(vec)).emplace_back(); }
void stl_vector_glTFAnimationSampler__add(void* vec, void* value) { (*static_cast<stl::vector<glTFAnimationSampler>*>(vec)).push_back(*static_cast<glTFAnimationSampler*>(value)); }
void stl_vector_glTFAnimationSampler__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<glTFAnimationSampler>*>(vec)), *static_cast<glTFAnimationSampler*>(value)); }
size_t stl_vector_glTFBuffer__size(void* vec) { return (*static_cast<stl::vector<glTFBuffer>*>(vec)).size(); }
void* stl_vector_glTFBuffer__at(void* vec, size_t i) { return &(*static_cast<stl::vector<glTFBuffer>*>(vec))[i]; }
void stl_vector_glTFBuffer__push(void* vec) { (*static_cast<stl::vector<glTFBuffer>*>(vec)).emplace_back(); }
void stl_vector_glTFBuffer__add(void* vec, void* value) { (*static_cast<stl::vector<glTFBuffer>*>(vec)).push_back(*static_cast<glTFBuffer*>(value)); }
void stl_vector_glTFBuffer__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<glTFBuffer>*>(vec)), *static_cast<glTFBuffer*>(value)); }
size_t stl_vector_glTFBufferView__size(void* vec) { return (*static_cast<stl::vector<glTFBufferView>*>(vec)).size(); }
void* stl_vector_glTFBufferView__at(void* vec, size_t i) { return &(*static_cast<stl::vector<glTFBufferView>*>(vec))[i]; }
void stl_vector_glTFBufferView__push(void* vec) { (*static_cast<stl::vector<glTFBufferView>*>(vec)).emplace_back(); }
void stl_vector_glTFBufferView__add(void* vec, void* value) { (*static_cast<stl::vector<glTFBufferView>*>(vec)).push_back(*static_cast<glTFBufferView*>(value)); }
void stl_vector_glTFBufferView__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<glTFBufferView>*>(vec)), *static_cast<glTFBufferView*>(value)); }
size_t stl_vector_glTFCamera__size(void* vec) { return (*static_cast<stl::vector<glTFCamera>*>(vec)).size(); }
void* stl_vector_glTFCamera__at(void* vec, size_t i) { return &(*static_cast<stl::vector<glTFCamera>*>(vec))[i]; }
void stl_vector_glTFCamera__push(void* vec) { (*static_cast<stl::vector<glTFCamera>*>(vec)).emplace_back(); }
void stl_vector_glTFCamera__add(void* vec, void* value) { (*static_cast<stl::vector<glTFCamera>*>(vec)).push_back(*static_cast<glTFCamera*>(value)); }
void stl_vector_glTFCamera__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<glTFCamera>*>(vec)), *static_cast<glTFCamera*>(value)); }
size_t stl_vector_glTFImage__size(void* vec) { return (*static_cast<stl::vector<glTFImage>*>(vec)).size(); }
void* stl_vector_glTFImage__at(void* vec, size_t i) { return &(*static_cast<stl::vector<glTFImage>*>(vec))[i]; }
void stl_vector_glTFImage__push(void* vec) { (*static_cast<stl::vector<glTFImage>*>(vec)).emplace_back(); }
void stl_vector_glTFImage__add(void* vec, void* value) { (*static_cast<stl::vector<glTFImage>*>(vec)).push_back(*static_cast<glTFImage*>(value)); }
void stl_vector_glTFImage__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<glTFImage>*>(vec)), *static_cast<glTFImage*>(value)); }
size_t stl_vector_glTFMaterial__size(void* vec) { return (*static_cast<stl::vector<glTFMaterial>*>(vec)).size(); }
void* stl_vector_glTFMaterial__at(void* vec, size_t i) { return &(*static_cast<stl::vector<glTFMaterial>*>(vec))[i]; }
void stl_vector_glTFMaterial__push(void* vec) { (*static_cast<stl::vector<glTFMaterial>*>(vec)).emplace_back(); }
void stl_vector_glTFMaterial__add(void* vec, void* value) { (*static_cast<stl::vector<glTFMaterial>*>(vec)).push_back(*static_cast<glTFMaterial*>(value)); }
void stl_vector_glTFMaterial__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<glTFMaterial>*>(vec)), *static_cast<glTFMaterial*>(value)); }
size_t stl_vector_glTFMesh__size(void* vec) { return (*static_cast<stl::vector<glTFMesh>*>(vec)).size(); }
void* stl_vector_glTFMesh__at(void* vec, size_t i) { return &(*static_cast<stl::vector<glTFMesh>*>(vec))[i]; }
void stl_vector_glTFMesh__push(void* vec) { (*static_cast<stl::vector<glTFMesh>*>(vec)).emplace_back(); }
void stl_vector_glTFMesh__add(void* vec, void* value) { (*static_cast<stl::vector<glTFMesh>*>(vec)).push_back(*static_cast<glTFMesh*>(value)); }
void stl_vector_glTFMesh__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<glTFMesh>*>(vec)), *static_cast<glTFMesh*>(value)); }
size_t stl_vector_glTFMorphTarget__size(void* vec) { return (*static_cast<stl::vector<glTFMorphTarget>*>(vec)).size(); }
void* stl_vector_glTFMorphTarget__at(void* vec, size_t i) { return &(*static_cast<stl::vector<glTFMorphTarget>*>(vec))[i]; }
void stl_vector_glTFMorphTarget__push(void* vec) { (*static_cast<stl::vector<glTFMorphTarget>*>(vec)).emplace_back(); }
void stl_vector_glTFMorphTarget__add(void* vec, void* value) { (*static_cast<stl::vector<glTFMorphTarget>*>(vec)).push_back(*static_cast<glTFMorphTarget*>(value)); }
void stl_vector_glTFMorphTarget__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<glTFMorphTarget>*>(vec)), *static_cast<glTFMorphTarget*>(value)); }
size_t stl_vector_glTFNode__size(void* vec) { return (*static_cast<stl::vector<glTFNode>*>(vec)).size(); }
void* stl_vector_glTFNode__at(void* vec, size_t i) { return &(*static_cast<stl::vector<glTFNode>*>(vec))[i]; }
void stl_vector_glTFNode__push(void* vec) { (*static_cast<stl::vector<glTFNode>*>(vec)).emplace_back(); }
void stl_vector_glTFNode__add(void* vec, void* value) { (*static_cast<stl::vector<glTFNode>*>(vec)).push_back(*static_cast<glTFNode*>(value)); }
void stl_vector_glTFNode__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<glTFNode>*>(vec)), *static_cast<glTFNode*>(value)); }
size_t stl_vector_glTFPrimitive__size(void* vec) { return (*static_cast<stl::vector<glTFPrimitive>*>(vec)).size(); }
void* stl_vector_glTFPrimitive__at(void* vec, size_t i) { return &(*static_cast<stl::vector<glTFPrimitive>*>(vec))[i]; }
void stl_vector_glTFPrimitive__push(void* vec) { (*static_cast<stl::vector<glTFPrimitive>*>(vec)).emplace_back(); }
void stl_vector_glTFPrimitive__add(void* vec, void* value) { (*static_cast<stl::vector<glTFPrimitive>*>(vec)).push_back(*static_cast<glTFPrimitive*>(value)); }
void stl_vector_glTFPrimitive__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<glTFPrimitive>*>(vec)), *static_cast<glTFPrimitive*>(value)); }
size_t stl_vector_glTFSampler__size(void* vec) { return (*static_cast<stl::vector<glTFSampler>*>(vec)).size(); }
void* stl_vector_glTFSampler__at(void* vec, size_t i) { return &(*static_cast<stl::vector<glTFSampler>*>(vec))[i]; }
void stl_vector_glTFSampler__push(void* vec) { (*static_cast<stl::vector<glTFSampler>*>(vec)).emplace_back(); }
void stl_vector_glTFSampler__add(void* vec, void* value) { (*static_cast<stl::vector<glTFSampler>*>(vec)).push_back(*static_cast<glTFSampler*>(value)); }
void stl_vector_glTFSampler__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<glTFSampler>*>(vec)), *static_cast<glTFSampler*>(value)); }
size_t stl_vector_glTFScene__size(void* vec) { return (*static_cast<stl::vector<glTFScene>*>(vec)).size(); }
void* stl_vector_glTFScene__at(void* vec, size_t i) { return &(*static_cast<stl::vector<glTFScene>*>(vec))[i]; }
void stl_vector_glTFScene__push(void* vec) { (*static_cast<stl::vector<glTFScene>*>(vec)).emplace_back(); }
void stl_vector_glTFScene__add(void* vec, void* value) { (*static_cast<stl::vector<glTFScene>*>(vec)).push_back(*static_cast<glTFScene*>(value)); }
void stl_vector_glTFScene__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<glTFScene>*>(vec)), *static_cast<glTFScene*>(value)); }
size_t stl_vector_glTFSkin__size(void* vec) { return (*static_cast<stl::vector<glTFSkin>*>(vec)).size(); }
void* stl_vector_glTFSkin__at(void* vec, size_t i) { return &(*static_cast<stl::vector<glTFSkin>*>(vec))[i]; }
void stl_vector_glTFSkin__push(void* vec) { (*static_cast<stl::vector<glTFSkin>*>(vec)).emplace_back(); }
void stl_vector_glTFSkin__add(void* vec, void* value) { (*static_cast<stl::vector<glTFSkin>*>(vec)).push_back(*static_cast<glTFSkin*>(value)); }
void stl_vector_glTFSkin__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<glTFSkin>*>(vec)), *static_cast<glTFSkin*>(value)); }
size_t stl_vector_glTFTexture__size(void* vec) { return (*static_cast<stl::vector<glTFTexture>*>(vec)).size(); }
void* stl_vector_glTFTexture__at(void* vec, size_t i) { return &(*static_cast<stl::vector<glTFTexture>*>(vec))[i]; }
void stl_vector_glTFTexture__push(void* vec) { (*static_cast<stl::vector<glTFTexture>*>(vec)).emplace_back(); }
void stl_vector_glTFTexture__add(void* vec, void* value) { (*static_cast<stl::vector<glTFTexture>*>(vec)).push_back(*static_cast<glTFTexture*>(value)); }
void stl_vector_glTFTexture__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<glTFTexture>*>(vec)), *static_cast<glTFTexture*>(value)); }
void glTF__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) glTF(  ); }
void glTF__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) glTF((*static_cast<glTF*>(other))); }
void glTFAccessor__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) glTFAccessor(  ); }
void glTFAccessor__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) glTFAccessor((*static_cast<glTFAccessor*>(other))); }
void glTFAnimation__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) glTFAnimation(  ); }
void glTFAnimation__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) glTFAnimation((*static_cast<glTFAnimation*>(other))); }
void glTFAnimationChannel__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) glTFAnimationChannel(  ); }
void glTFAnimationChannel__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) glTFAnimationChannel((*static_cast<glTFAnimationChannel*>(other))); }
void glTFAnimationSampler__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) glTFAnimationSampler(  ); }
void glTFAnimationSampler__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) glTFAnimationSampler((*static_cast<glTFAnimationSampler*>(other))); }
void glTFAnimationTarget__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) glTFAnimationTarget(  ); }
void glTFAnimationTarget__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) glTFAnimationTarget((*static_cast<glTFAnimationTarget*>(other))); }
void glTFAttributes__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) glTFAttributes(  ); }
void glTFAttributes__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) glTFAttributes((*static_cast<glTFAttributes*>(other))); }
void glTFBuffer__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) glTFBuffer(  ); }
void glTFBuffer__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) glTFBuffer((*static_cast<glTFBuffer*>(other))); }
void glTFBufferView__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) glTFBufferView(  ); }
void glTFBufferView__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) glTFBufferView((*static_cast<glTFBufferView*>(other))); }
void glTFCamera__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) glTFCamera(  ); }
void glTFCamera__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) glTFCamera((*static_cast<glTFCamera*>(other))); }
void glTFImage__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) glTFImage(  ); }
void glTFImage__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) glTFImage((*static_cast<glTFImage*>(other))); }
void glTFMaterial__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) glTFMaterial(  ); }
void glTFMaterial__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) glTFMaterial((*static_cast<glTFMaterial*>(other))); }
void glTFMaterialPBR__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) glTFMaterialPBR(  ); }
void glTFMaterialPBR__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) glTFMaterialPBR((*static_cast<glTFMaterialPBR*>(other))); }
void glTFMesh__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) glTFMesh(  ); }
void glTFMesh__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) glTFMesh((*static_cast<glTFMesh*>(other))); }
void glTFMorphTarget__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) glTFMorphTarget(  ); }
void glTFMorphTarget__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) glTFMorphTarget((*static_cast<glTFMorphTarget*>(other))); }
void glTFNode__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) glTFNode(  ); }
void glTFNode__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) glTFNode((*static_cast<glTFNode*>(other))); }
void glTFNodeExtras__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) glTFNodeExtras(  ); }
void glTFNodeExtras__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) glTFNodeExtras((*static_cast<glTFNodeExtras*>(other))); }
void glTFOrthographic__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) glTFOrthographic(  ); }
void glTFOrthographic__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) glTFOrthographic((*static_cast<glTFOrthographic*>(other))); }
void glTFPerspective__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) glTFPerspective(  ); }
void glTFPerspective__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) glTFPerspective((*static_cast<glTFPerspective*>(other))); }
void glTFPrimitive__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) glTFPrimitive(  ); }
void glTFPrimitive__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) glTFPrimitive((*static_cast<glTFPrimitive*>(other))); }
void glTFSampler__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) glTFSampler(  ); }
void glTFSampler__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) glTFSampler((*static_cast<glTFSampler*>(other))); }
void glTFScene__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) glTFScene(  ); }
void glTFScene__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) glTFScene((*static_cast<glTFScene*>(other))); }
void glTFSkin__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) glTFSkin(  ); }
void glTFSkin__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) glTFSkin((*static_cast<glTFSkin*>(other))); }
void glTFSparse__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) glTFSparse(  ); }
void glTFSparse__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) glTFSparse((*static_cast<glTFSparse*>(other))); }
void glTFSparseIndices__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) glTFSparseIndices(  ); }
void glTFSparseIndices__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) glTFSparseIndices((*static_cast<glTFSparseIndices*>(other))); }
void glTFSparseValues__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) glTFSparseValues(  ); }
void glTFSparseValues__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) glTFSparseValues((*static_cast<glTFSparseValues*>(other))); }
void glTFTexture__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) glTFTexture(  ); }
void glTFTexture__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) glTFTexture((*static_cast<glTFTexture*>(other))); }
void glTFTextureInfo__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) glTFTextureInfo(  ); }
void glTFTextureInfo__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) glTFTextureInfo((*static_cast<glTFTextureInfo*>(other))); }

namespace mud
{
	void mud_gltf_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<glTFAlphaMode>();
		static Meta meta = { t, &namspc({}), "glTFAlphaMode", sizeof(glTFAlphaMode), TypeClass::Enum };
		static cstring ids[] = { "OPAQUE", "MASK", "BLEND" };
		static uint32_t values[] = { 0, 1, 2 };
		static glTFAlphaMode vars[] = { glTFAlphaMode::OPAQUE, glTFAlphaMode::MASK, glTFAlphaMode::BLEND};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { glTFAlphaMode__to_string,
		                           glTFAlphaMode__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<glTFComponentType>();
		static Meta meta = { t, &namspc({}), "glTFComponentType", sizeof(glTFComponentType), TypeClass::Enum };
		static cstring ids[] = { "BYTE", "UNSIGNED_BYTE", "SHORT", "UNSIGNED_SHORT", "INT", "FLOAT" };
		static uint32_t values[] = { 5120, 5121, 5122, 5123, 5125, 5126 };
		static glTFComponentType vars[] = { glTFComponentType::BYTE, glTFComponentType::UNSIGNED_BYTE, glTFComponentType::SHORT, glTFComponentType::UNSIGNED_SHORT, glTFComponentType::INT, glTFComponentType::FLOAT};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { glTFComponentType__to_string,
		                           glTFComponentType__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<glTFInterpolation>();
		static Meta meta = { t, &namspc({}), "glTFInterpolation", sizeof(glTFInterpolation), TypeClass::Enum };
		static cstring ids[] = { "LINEAR", "STEP", "CATMULLROMSPLINE", "CUBIC_SPLINE" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static glTFInterpolation vars[] = { glTFInterpolation::LINEAR, glTFInterpolation::STEP, glTFInterpolation::CATMULLROMSPLINE, glTFInterpolation::CUBIC_SPLINE};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { glTFInterpolation__to_string,
		                           glTFInterpolation__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<glTFPrimitiveType>();
		static Meta meta = { t, &namspc({}), "glTFPrimitiveType", sizeof(glTFPrimitiveType), TypeClass::Enum };
		static cstring ids[] = { "POINTS", "LINES", "LINE_LOOP", "LINE_STRIP", "TRIANGLES", "TRIANGLE_STRIP", "TRIANGLE_FAN" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6 };
		static glTFPrimitiveType vars[] = { glTFPrimitiveType::POINTS, glTFPrimitiveType::LINES, glTFPrimitiveType::LINE_LOOP, glTFPrimitiveType::LINE_STRIP, glTFPrimitiveType::TRIANGLES, glTFPrimitiveType::TRIANGLE_STRIP, glTFPrimitiveType::TRIANGLE_FAN};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { glTFPrimitiveType__to_string,
		                           glTFPrimitiveType__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<glTFType>();
		static Meta meta = { t, &namspc({}), "glTFType", sizeof(glTFType), TypeClass::Enum };
		static cstring ids[] = { "SCALAR", "VEC2", "VEC3", "VEC4", "MAT2", "MAT3", "MAT4", "INVALID" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
		static glTFType vars[] = { glTFType::SCALAR, glTFType::VEC2, glTFType::VEC3, glTFType::VEC4, glTFType::MAT2, glTFType::MAT3, glTFType::MAT4, glTFType::INVALID};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { glTFType__to_string,
		                           glTFType__to_value };
		g_convert[t.m_id] = &convert;
	}
	
	// Sequences
	{
		Type& t = type<stl::vector<glTFAccessor>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<glTFAccessor>", sizeof(stl::vector<glTFAccessor>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<glTFAccessor>(),
		                             stl_vector_glTFAccessor__size,
		                             stl_vector_glTFAccessor__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_glTFAccessor__push,
		                             stl_vector_glTFAccessor__add,
		                             stl_vector_glTFAccessor__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<glTFAnimation>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<glTFAnimation>", sizeof(stl::vector<glTFAnimation>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<glTFAnimation>(),
		                             stl_vector_glTFAnimation__size,
		                             stl_vector_glTFAnimation__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_glTFAnimation__push,
		                             stl_vector_glTFAnimation__add,
		                             stl_vector_glTFAnimation__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<glTFAnimationChannel>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<glTFAnimationChannel>", sizeof(stl::vector<glTFAnimationChannel>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<glTFAnimationChannel>(),
		                             stl_vector_glTFAnimationChannel__size,
		                             stl_vector_glTFAnimationChannel__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_glTFAnimationChannel__push,
		                             stl_vector_glTFAnimationChannel__add,
		                             stl_vector_glTFAnimationChannel__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<glTFAnimationSampler>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<glTFAnimationSampler>", sizeof(stl::vector<glTFAnimationSampler>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<glTFAnimationSampler>(),
		                             stl_vector_glTFAnimationSampler__size,
		                             stl_vector_glTFAnimationSampler__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_glTFAnimationSampler__push,
		                             stl_vector_glTFAnimationSampler__add,
		                             stl_vector_glTFAnimationSampler__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<glTFBuffer>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<glTFBuffer>", sizeof(stl::vector<glTFBuffer>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<glTFBuffer>(),
		                             stl_vector_glTFBuffer__size,
		                             stl_vector_glTFBuffer__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_glTFBuffer__push,
		                             stl_vector_glTFBuffer__add,
		                             stl_vector_glTFBuffer__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<glTFBufferView>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<glTFBufferView>", sizeof(stl::vector<glTFBufferView>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<glTFBufferView>(),
		                             stl_vector_glTFBufferView__size,
		                             stl_vector_glTFBufferView__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_glTFBufferView__push,
		                             stl_vector_glTFBufferView__add,
		                             stl_vector_glTFBufferView__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<glTFCamera>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<glTFCamera>", sizeof(stl::vector<glTFCamera>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<glTFCamera>(),
		                             stl_vector_glTFCamera__size,
		                             stl_vector_glTFCamera__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_glTFCamera__push,
		                             stl_vector_glTFCamera__add,
		                             stl_vector_glTFCamera__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<glTFImage>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<glTFImage>", sizeof(stl::vector<glTFImage>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<glTFImage>(),
		                             stl_vector_glTFImage__size,
		                             stl_vector_glTFImage__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_glTFImage__push,
		                             stl_vector_glTFImage__add,
		                             stl_vector_glTFImage__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<glTFMaterial>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<glTFMaterial>", sizeof(stl::vector<glTFMaterial>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<glTFMaterial>(),
		                             stl_vector_glTFMaterial__size,
		                             stl_vector_glTFMaterial__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_glTFMaterial__push,
		                             stl_vector_glTFMaterial__add,
		                             stl_vector_glTFMaterial__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<glTFMesh>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<glTFMesh>", sizeof(stl::vector<glTFMesh>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<glTFMesh>(),
		                             stl_vector_glTFMesh__size,
		                             stl_vector_glTFMesh__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_glTFMesh__push,
		                             stl_vector_glTFMesh__add,
		                             stl_vector_glTFMesh__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<glTFMorphTarget>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<glTFMorphTarget>", sizeof(stl::vector<glTFMorphTarget>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<glTFMorphTarget>(),
		                             stl_vector_glTFMorphTarget__size,
		                             stl_vector_glTFMorphTarget__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_glTFMorphTarget__push,
		                             stl_vector_glTFMorphTarget__add,
		                             stl_vector_glTFMorphTarget__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<glTFNode>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<glTFNode>", sizeof(stl::vector<glTFNode>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<glTFNode>(),
		                             stl_vector_glTFNode__size,
		                             stl_vector_glTFNode__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_glTFNode__push,
		                             stl_vector_glTFNode__add,
		                             stl_vector_glTFNode__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<glTFPrimitive>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<glTFPrimitive>", sizeof(stl::vector<glTFPrimitive>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<glTFPrimitive>(),
		                             stl_vector_glTFPrimitive__size,
		                             stl_vector_glTFPrimitive__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_glTFPrimitive__push,
		                             stl_vector_glTFPrimitive__add,
		                             stl_vector_glTFPrimitive__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<glTFSampler>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<glTFSampler>", sizeof(stl::vector<glTFSampler>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<glTFSampler>(),
		                             stl_vector_glTFSampler__size,
		                             stl_vector_glTFSampler__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_glTFSampler__push,
		                             stl_vector_glTFSampler__add,
		                             stl_vector_glTFSampler__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<glTFScene>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<glTFScene>", sizeof(stl::vector<glTFScene>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<glTFScene>(),
		                             stl_vector_glTFScene__size,
		                             stl_vector_glTFScene__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_glTFScene__push,
		                             stl_vector_glTFScene__add,
		                             stl_vector_glTFScene__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<glTFSkin>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<glTFSkin>", sizeof(stl::vector<glTFSkin>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<glTFSkin>(),
		                             stl_vector_glTFSkin__size,
		                             stl_vector_glTFSkin__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_glTFSkin__push,
		                             stl_vector_glTFSkin__add,
		                             stl_vector_glTFSkin__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<glTFTexture>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<glTFTexture>", sizeof(stl::vector<glTFTexture>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<glTFTexture>(),
		                             stl_vector_glTFTexture__size,
		                             stl_vector_glTFTexture__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_glTFTexture__push,
		                             stl_vector_glTFTexture__add,
		                             stl_vector_glTFTexture__remove };
		g_sequence[t.m_id] = &sequence;
	}
	
	// glTF
	{
		Type& t = type<glTF>();
		static Meta meta = { t, &namspc({}), "glTF", sizeof(glTF), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, glTF__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, glTF__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(glTF, m_buffers), type<stl::vector<glTFBuffer>>(), "buffers", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(glTF, m_buffer_views), type<stl::vector<glTFBufferView>>(), "buffer_views", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(glTF, m_accessors), type<stl::vector<glTFAccessor>>(), "accessors", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(glTF, m_images), type<stl::vector<glTFImage>>(), "images", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(glTF, m_textures), type<stl::vector<glTFTexture>>(), "textures", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(glTF, m_materials), type<stl::vector<glTFMaterial>>(), "materials", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(glTF, m_meshes), type<stl::vector<glTFMesh>>(), "meshes", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(glTF, m_nodes), type<stl::vector<glTFNode>>(), "nodes", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(glTF, m_skins), type<stl::vector<glTFSkin>>(), "skins", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(glTF, m_animations), type<stl::vector<glTFAnimation>>(), "animations", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(glTF, m_cameras), type<stl::vector<glTFCamera>>(), "cameras", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(glTF, m_samplers), type<stl::vector<glTFSampler>>(), "samplers", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(glTF, m_scenes), type<stl::vector<glTFScene>>(), "scenes", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// glTFAccessor
	{
		Type& t = type<glTFAccessor>();
		static Meta meta = { t, &namspc({}), "glTFAccessor", sizeof(glTFAccessor), TypeClass::Struct };
		// bases
		// defaults
		static int buffer_view_default = -1;
		static int byte_offset_default = 0;
		static bool normalized_default = false;
		static glTFType type_default = glTFType::INVALID;
		// constructors
		static Constructor constructors[] = {
			{ t, glTFAccessor__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, glTFAccessor__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(glTFAccessor, name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFAccessor, buffer_view), type<int>(), "buffer_view", &buffer_view_default, Member::Value, nullptr },
			{ t, offsetof(glTFAccessor, byte_offset), type<int>(), "byte_offset", &byte_offset_default, Member::Value, nullptr },
			{ t, offsetof(glTFAccessor, component_type), type<glTFComponentType>(), "component_type", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFAccessor, normalized), type<bool>(), "normalized", &normalized_default, Member::Value, nullptr },
			{ t, offsetof(glTFAccessor, count), type<int>(), "count", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFAccessor, type), type<glTFType>(), "type", &type_default, Member::Value, nullptr },
			{ t, offsetof(glTFAccessor, sparse), type<glTFSparse>(), "sparse", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// glTFAnimation
	{
		Type& t = type<glTFAnimation>();
		static Meta meta = { t, &namspc({}), "glTFAnimation", sizeof(glTFAnimation), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, glTFAnimation__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, glTFAnimation__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(glTFAnimation, name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFAnimation, samplers), type<stl::vector<glTFAnimationSampler>>(), "samplers", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(glTFAnimation, channels), type<stl::vector<glTFAnimationChannel>>(), "channels", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// glTFAnimationChannel
	{
		Type& t = type<glTFAnimationChannel>();
		static Meta meta = { t, &namspc({}), "glTFAnimationChannel", sizeof(glTFAnimationChannel), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, glTFAnimationChannel__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, glTFAnimationChannel__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(glTFAnimationChannel, sampler), type<int>(), "sampler", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFAnimationChannel, target), type<glTFAnimationTarget>(), "target", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// glTFAnimationSampler
	{
		Type& t = type<glTFAnimationSampler>();
		static Meta meta = { t, &namspc({}), "glTFAnimationSampler", sizeof(glTFAnimationSampler), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, glTFAnimationSampler__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, glTFAnimationSampler__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(glTFAnimationSampler, interpolation), type<glTFInterpolation>(), "interpolation", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFAnimationSampler, input), type<int>(), "input", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFAnimationSampler, output), type<int>(), "output", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// glTFAnimationTarget
	{
		Type& t = type<glTFAnimationTarget>();
		static Meta meta = { t, &namspc({}), "glTFAnimationTarget", sizeof(glTFAnimationTarget), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, glTFAnimationTarget__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, glTFAnimationTarget__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(glTFAnimationTarget, node), type<int>(), "node", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFAnimationTarget, path), type<stl::string>(), "path", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// glTFAttributes
	{
		Type& t = type<glTFAttributes>();
		static Meta meta = { t, &namspc({}), "glTFAttributes", sizeof(glTFAttributes), TypeClass::Struct };
		// bases
		// defaults
		static int POSITION_default = -1;
		static int NORMAL_default = -1;
		static int TANGENT_default = -1;
		static int TEXCOORD_0_default = -1;
		static int TEXCOORD_1_default = -1;
		static int COLOR_0_default = -1;
		static int JOINTS_0_default = -1;
		static int WEIGHTS_0_default = -1;
		// constructors
		static Constructor constructors[] = {
			{ t, glTFAttributes__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, glTFAttributes__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(glTFAttributes, POSITION), type<int>(), "POSITION", &POSITION_default, Member::Value, nullptr },
			{ t, offsetof(glTFAttributes, NORMAL), type<int>(), "NORMAL", &NORMAL_default, Member::Value, nullptr },
			{ t, offsetof(glTFAttributes, TANGENT), type<int>(), "TANGENT", &TANGENT_default, Member::Value, nullptr },
			{ t, offsetof(glTFAttributes, TEXCOORD_0), type<int>(), "TEXCOORD_0", &TEXCOORD_0_default, Member::Value, nullptr },
			{ t, offsetof(glTFAttributes, TEXCOORD_1), type<int>(), "TEXCOORD_1", &TEXCOORD_1_default, Member::Value, nullptr },
			{ t, offsetof(glTFAttributes, COLOR_0), type<int>(), "COLOR_0", &COLOR_0_default, Member::Value, nullptr },
			{ t, offsetof(glTFAttributes, JOINTS_0), type<int>(), "JOINTS_0", &JOINTS_0_default, Member::Value, nullptr },
			{ t, offsetof(glTFAttributes, WEIGHTS_0), type<int>(), "WEIGHTS_0", &WEIGHTS_0_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// glTFBuffer
	{
		Type& t = type<glTFBuffer>();
		static Meta meta = { t, &namspc({}), "glTFBuffer", sizeof(glTFBuffer), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, glTFBuffer__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, glTFBuffer__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(glTFBuffer, name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFBuffer, mime_type), type<stl::string>(), "mime_type", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFBuffer, uri), type<stl::string>(), "uri", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFBuffer, byte_length), type<size_t>(), "byte_length", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// glTFBufferView
	{
		Type& t = type<glTFBufferView>();
		static Meta meta = { t, &namspc({}), "glTFBufferView", sizeof(glTFBufferView), TypeClass::Struct };
		// bases
		// defaults
		static int buffer_default = 0;
		static size_t byte_offset_default = 0;
		static size_t byte_length_default = 0;
		static size_t byte_stride_default = 0;
		static int target_default = 0;
		// constructors
		static Constructor constructors[] = {
			{ t, glTFBufferView__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, glTFBufferView__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(glTFBufferView, name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFBufferView, buffer), type<int>(), "buffer", &buffer_default, Member::Value, nullptr },
			{ t, offsetof(glTFBufferView, byte_offset), type<size_t>(), "byte_offset", &byte_offset_default, Member::Value, nullptr },
			{ t, offsetof(glTFBufferView, byte_length), type<size_t>(), "byte_length", &byte_length_default, Member::Value, nullptr },
			{ t, offsetof(glTFBufferView, byte_stride), type<size_t>(), "byte_stride", &byte_stride_default, Member::Value, nullptr },
			{ t, offsetof(glTFBufferView, target), type<int>(), "target", &target_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// glTFCamera
	{
		Type& t = type<glTFCamera>();
		static Meta meta = { t, &namspc({}), "glTFCamera", sizeof(glTFCamera), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, glTFCamera__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, glTFCamera__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(glTFCamera, name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFCamera, type), type<stl::string>(), "type", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFCamera, orthographic), type<glTFOrthographic>(), "orthographic", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFCamera, perspective), type<glTFPerspective>(), "perspective", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// glTFImage
	{
		Type& t = type<glTFImage>();
		static Meta meta = { t, &namspc({}), "glTFImage", sizeof(glTFImage), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, glTFImage__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, glTFImage__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(glTFImage, name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFImage, mime_type), type<stl::string>(), "mime_type", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFImage, uri), type<stl::string>(), "uri", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFImage, buffer_view), type<int>(), "buffer_view", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// glTFMaterial
	{
		Type& t = type<glTFMaterial>();
		static Meta meta = { t, &namspc({}), "glTFMaterial", sizeof(glTFMaterial), TypeClass::Struct };
		// bases
		// defaults
		static mud::vec3 emissive_factor_default = to_vec3(mud::Colour::Black);
		static bool double_sided_default = false;
		static glTFAlphaMode alpha_mode_default = glTFAlphaMode::OPAQUE;
		// constructors
		static Constructor constructors[] = {
			{ t, glTFMaterial__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, glTFMaterial__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(glTFMaterial, name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFMaterial, normal_texture), type<glTFTextureInfo>(), "normal_texture", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFMaterial, occlusion_texture), type<glTFTextureInfo>(), "occlusion_texture", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFMaterial, emissive_factor), type<mud::vec3>(), "emissive_factor", &emissive_factor_default, Member::Value, nullptr },
			{ t, offsetof(glTFMaterial, emissive_texture), type<glTFTextureInfo>(), "emissive_texture", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFMaterial, double_sided), type<bool>(), "double_sided", &double_sided_default, Member::Value, nullptr },
			{ t, offsetof(glTFMaterial, alpha_mode), type<glTFAlphaMode>(), "alpha_mode", &alpha_mode_default, Member::Value, nullptr },
			{ t, offsetof(glTFMaterial, pbr_metallic_roughness), type<glTFMaterialPBR>(), "pbr_metallic_roughness", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// glTFMaterialPBR
	{
		Type& t = type<glTFMaterialPBR>();
		static Meta meta = { t, &namspc({}), "glTFMaterialPBR", sizeof(glTFMaterialPBR), TypeClass::Struct };
		// bases
		// defaults
		static float metallic_factor_default = 1.f;
		static float roughness_factor_default = 1.f;
		// constructors
		static Constructor constructors[] = {
			{ t, glTFMaterialPBR__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, glTFMaterialPBR__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(glTFMaterialPBR, base_color_factor), type<mud::vec4>(), "base_color_factor", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFMaterialPBR, base_color_texture), type<glTFTextureInfo>(), "base_color_texture", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFMaterialPBR, metallic_factor), type<float>(), "metallic_factor", &metallic_factor_default, Member::Value, nullptr },
			{ t, offsetof(glTFMaterialPBR, roughness_factor), type<float>(), "roughness_factor", &roughness_factor_default, Member::Value, nullptr },
			{ t, offsetof(glTFMaterialPBR, metallic_roughness_texture), type<glTFTextureInfo>(), "metallic_roughness_texture", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// glTFMesh
	{
		Type& t = type<glTFMesh>();
		static Meta meta = { t, &namspc({}), "glTFMesh", sizeof(glTFMesh), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, glTFMesh__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, glTFMesh__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(glTFMesh, name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFMesh, primitives), type<stl::vector<glTFPrimitive>>(), "primitives", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(glTFMesh, weights), type<stl::vector<float>>(), "weights", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// glTFMorphTarget
	{
		Type& t = type<glTFMorphTarget>();
		static Meta meta = { t, &namspc({}), "glTFMorphTarget", sizeof(glTFMorphTarget), TypeClass::Struct };
		// bases
		// defaults
		static int POSITION_default = -1;
		static int NORMAL_default = -1;
		static int TANGENT_default = -1;
		// constructors
		static Constructor constructors[] = {
			{ t, glTFMorphTarget__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, glTFMorphTarget__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(glTFMorphTarget, POSITION), type<int>(), "POSITION", &POSITION_default, Member::Value, nullptr },
			{ t, offsetof(glTFMorphTarget, NORMAL), type<int>(), "NORMAL", &NORMAL_default, Member::Value, nullptr },
			{ t, offsetof(glTFMorphTarget, TANGENT), type<int>(), "TANGENT", &TANGENT_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// glTFNode
	{
		Type& t = type<glTFNode>();
		static Meta meta = { t, &namspc({}), "glTFNode", sizeof(glTFNode), TypeClass::Struct };
		// bases
		// defaults
		static int mesh_default = -1;
		static int camera_default = -1;
		static int skin_default = -1;
		static mud::mat4 matrix_default = {};
		static mud::quat rotation_default = mud::ZeroQuat;
		// constructors
		static Constructor constructors[] = {
			{ t, glTFNode__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, glTFNode__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(glTFNode, name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFNode, mesh), type<int>(), "mesh", &mesh_default, Member::Value, nullptr },
			{ t, offsetof(glTFNode, camera), type<int>(), "camera", &camera_default, Member::Value, nullptr },
			{ t, offsetof(glTFNode, skin), type<int>(), "skin", &skin_default, Member::Value, nullptr },
			{ t, offsetof(glTFNode, matrix), type<mud::mat4>(), "matrix", &matrix_default, Member::Value, nullptr },
			{ t, offsetof(glTFNode, translation), type<mud::vec3>(), "translation", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFNode, rotation), type<mud::quat>(), "rotation", &rotation_default, Member::Value, nullptr },
			{ t, offsetof(glTFNode, scale), type<mud::vec3>(), "scale", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFNode, children), type<stl::vector<int>>(), "children", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// glTFNodeExtras
	{
		Type& t = type<glTFNodeExtras>();
		static Meta meta = { t, &namspc({}), "glTFNodeExtras", sizeof(glTFNodeExtras), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, glTFNodeExtras__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, glTFNodeExtras__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// glTFOrthographic
	{
		Type& t = type<glTFOrthographic>();
		static Meta meta = { t, &namspc({}), "glTFOrthographic", sizeof(glTFOrthographic), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, glTFOrthographic__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, glTFOrthographic__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(glTFOrthographic, xmag), type<float>(), "xmag", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFOrthographic, ymag), type<float>(), "ymag", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFOrthographic, zfar), type<float>(), "zfar", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFOrthographic, znear), type<float>(), "znear", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// glTFPerspective
	{
		Type& t = type<glTFPerspective>();
		static Meta meta = { t, &namspc({}), "glTFPerspective", sizeof(glTFPerspective), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, glTFPerspective__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, glTFPerspective__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(glTFPerspective, yfov), type<float>(), "yfov", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFPerspective, zfar), type<float>(), "zfar", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFPerspective, znear), type<float>(), "znear", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFPerspective, aspect_ratio), type<float>(), "aspect_ratio", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// glTFPrimitive
	{
		Type& t = type<glTFPrimitive>();
		static Meta meta = { t, &namspc({}), "glTFPrimitive", sizeof(glTFPrimitive), TypeClass::Struct };
		// bases
		// defaults
		static int indices_default = -1;
		static int material_default = -1;
		static glTFPrimitiveType mode_default = glTFPrimitiveType::TRIANGLES;
		// constructors
		static Constructor constructors[] = {
			{ t, glTFPrimitive__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, glTFPrimitive__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(glTFPrimitive, attributes), type<glTFAttributes>(), "attributes", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFPrimitive, indices), type<int>(), "indices", &indices_default, Member::Value, nullptr },
			{ t, offsetof(glTFPrimitive, material), type<int>(), "material", &material_default, Member::Value, nullptr },
			{ t, offsetof(glTFPrimitive, mode), type<glTFPrimitiveType>(), "mode", &mode_default, Member::Value, nullptr },
			{ t, offsetof(glTFPrimitive, targets), type<stl::vector<glTFMorphTarget>>(), "targets", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// glTFSampler
	{
		Type& t = type<glTFSampler>();
		static Meta meta = { t, &namspc({}), "glTFSampler", sizeof(glTFSampler), TypeClass::Struct };
		// bases
		// defaults
		static int wrap_s_default = 10497;
		static int wrap_t_default = 10497;
		// constructors
		static Constructor constructors[] = {
			{ t, glTFSampler__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, glTFSampler__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(glTFSampler, mag_filter), type<int>(), "mag_filter", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFSampler, min_filter), type<int>(), "min_filter", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFSampler, wrap_s), type<int>(), "wrap_s", &wrap_s_default, Member::Value, nullptr },
			{ t, offsetof(glTFSampler, wrap_t), type<int>(), "wrap_t", &wrap_t_default, Member::Value, nullptr },
			{ t, offsetof(glTFSampler, name), type<stl::string>(), "name", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// glTFScene
	{
		Type& t = type<glTFScene>();
		static Meta meta = { t, &namspc({}), "glTFScene", sizeof(glTFScene), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, glTFScene__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, glTFScene__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(glTFScene, name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFScene, nodes), type<stl::vector<int>>(), "nodes", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// glTFSkin
	{
		Type& t = type<glTFSkin>();
		static Meta meta = { t, &namspc({}), "glTFSkin", sizeof(glTFSkin), TypeClass::Struct };
		// bases
		// defaults
		static int skeleton_default = -1;
		// constructors
		static Constructor constructors[] = {
			{ t, glTFSkin__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, glTFSkin__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(glTFSkin, name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFSkin, skeleton), type<int>(), "skeleton", &skeleton_default, Member::Value, nullptr },
			{ t, offsetof(glTFSkin, joints), type<stl::vector<int>>(), "joints", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(glTFSkin, inverse_bind_matrices), type<int>(), "inverse_bind_matrices", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// glTFSparse
	{
		Type& t = type<glTFSparse>();
		static Meta meta = { t, &namspc({}), "glTFSparse", sizeof(glTFSparse), TypeClass::Struct };
		// bases
		// defaults
		static int count_default = 0;
		// constructors
		static Constructor constructors[] = {
			{ t, glTFSparse__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, glTFSparse__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(glTFSparse, count), type<int>(), "count", &count_default, Member::Value, nullptr },
			{ t, offsetof(glTFSparse, indices), type<glTFSparseIndices>(), "indices", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFSparse, values), type<glTFSparseValues>(), "values", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// glTFSparseIndices
	{
		Type& t = type<glTFSparseIndices>();
		static Meta meta = { t, &namspc({}), "glTFSparseIndices", sizeof(glTFSparseIndices), TypeClass::Struct };
		// bases
		// defaults
		static int byte_offset_default = 0;
		// constructors
		static Constructor constructors[] = {
			{ t, glTFSparseIndices__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, glTFSparseIndices__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(glTFSparseIndices, buffer_view), type<int>(), "buffer_view", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFSparseIndices, byte_offset), type<int>(), "byte_offset", &byte_offset_default, Member::Value, nullptr },
			{ t, offsetof(glTFSparseIndices, component_type), type<glTFComponentType>(), "component_type", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// glTFSparseValues
	{
		Type& t = type<glTFSparseValues>();
		static Meta meta = { t, &namspc({}), "glTFSparseValues", sizeof(glTFSparseValues), TypeClass::Struct };
		// bases
		// defaults
		static int byte_offset_default = 0;
		// constructors
		static Constructor constructors[] = {
			{ t, glTFSparseValues__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, glTFSparseValues__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(glTFSparseValues, buffer_view), type<int>(), "buffer_view", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFSparseValues, byte_offset), type<int>(), "byte_offset", &byte_offset_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// glTFTexture
	{
		Type& t = type<glTFTexture>();
		static Meta meta = { t, &namspc({}), "glTFTexture", sizeof(glTFTexture), TypeClass::Struct };
		// bases
		// defaults
		static int sampler_default = -1;
		static int source_default = -1;
		// constructors
		static Constructor constructors[] = {
			{ t, glTFTexture__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, glTFTexture__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(glTFTexture, name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(glTFTexture, sampler), type<int>(), "sampler", &sampler_default, Member::Value, nullptr },
			{ t, offsetof(glTFTexture, source), type<int>(), "source", &source_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// glTFTextureInfo
	{
		Type& t = type<glTFTextureInfo>();
		static Meta meta = { t, &namspc({}), "glTFTextureInfo", sizeof(glTFTextureInfo), TypeClass::Struct };
		// bases
		// defaults
		static int index_default = -1;
		static float scale_default = 1.f;
		// constructors
		static Constructor constructors[] = {
			{ t, glTFTextureInfo__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, glTFTextureInfo__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(glTFTextureInfo, index), type<int>(), "index", &index_default, Member::Value, nullptr },
			{ t, offsetof(glTFTextureInfo, scale), type<float>(), "scale", &scale_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	
	
		m.m_types.push_back(&type<glTF>());
		m.m_types.push_back(&type<glTFAccessor>());
		m.m_types.push_back(&type<glTFAlphaMode>());
		m.m_types.push_back(&type<glTFAnimation>());
		m.m_types.push_back(&type<glTFAnimationChannel>());
		m.m_types.push_back(&type<glTFAnimationSampler>());
		m.m_types.push_back(&type<glTFAnimationTarget>());
		m.m_types.push_back(&type<glTFAttributes>());
		m.m_types.push_back(&type<glTFBuffer>());
		m.m_types.push_back(&type<glTFBufferView>());
		m.m_types.push_back(&type<glTFCamera>());
		m.m_types.push_back(&type<glTFComponentType>());
		m.m_types.push_back(&type<glTFImage>());
		m.m_types.push_back(&type<glTFInterpolation>());
		m.m_types.push_back(&type<glTFMaterial>());
		m.m_types.push_back(&type<glTFMaterialPBR>());
		m.m_types.push_back(&type<glTFMesh>());
		m.m_types.push_back(&type<glTFMorphTarget>());
		m.m_types.push_back(&type<glTFNode>());
		m.m_types.push_back(&type<glTFNodeExtras>());
		m.m_types.push_back(&type<glTFOrthographic>());
		m.m_types.push_back(&type<glTFPerspective>());
		m.m_types.push_back(&type<glTFPrimitive>());
		m.m_types.push_back(&type<glTFPrimitiveType>());
		m.m_types.push_back(&type<glTFSampler>());
		m.m_types.push_back(&type<glTFScene>());
		m.m_types.push_back(&type<glTFSkin>());
		m.m_types.push_back(&type<glTFSparse>());
		m.m_types.push_back(&type<glTFSparseIndices>());
		m.m_types.push_back(&type<glTFSparseValues>());
		m.m_types.push_back(&type<glTFTexture>());
		m.m_types.push_back(&type<glTFTextureInfo>());
		m.m_types.push_back(&type<glTFType>());
		m.m_types.push_back(&type<stl::vector<glTFAccessor>>());
		m.m_types.push_back(&type<stl::vector<glTFAnimation>>());
		m.m_types.push_back(&type<stl::vector<glTFAnimationChannel>>());
		m.m_types.push_back(&type<stl::vector<glTFAnimationSampler>>());
		m.m_types.push_back(&type<stl::vector<glTFBuffer>>());
		m.m_types.push_back(&type<stl::vector<glTFBufferView>>());
		m.m_types.push_back(&type<stl::vector<glTFCamera>>());
		m.m_types.push_back(&type<stl::vector<glTFImage>>());
		m.m_types.push_back(&type<stl::vector<glTFMaterial>>());
		m.m_types.push_back(&type<stl::vector<glTFMesh>>());
		m.m_types.push_back(&type<stl::vector<glTFMorphTarget>>());
		m.m_types.push_back(&type<stl::vector<glTFNode>>());
		m.m_types.push_back(&type<stl::vector<glTFPrimitive>>());
		m.m_types.push_back(&type<stl::vector<glTFSampler>>());
		m.m_types.push_back(&type<stl::vector<glTFScene>>());
		m.m_types.push_back(&type<stl::vector<glTFSkin>>());
		m.m_types.push_back(&type<stl::vector<glTFTexture>>());
	}
}

namespace mud
{
	mud_gltf::mud_gltf()
		: Module("mud::gltf", { &mud_infra::m(), &mud_type::m(), &mud_refl::m(), &mud_srlz::m(), &mud_math::m() })
	{
		// setup reflection meta data
		mud_gltf_meta(*this);
	}
}

#ifdef MUD_GLTF_MODULE
extern "C"
Module& getModule()
{
	return mud_gltf::m();
}
#endif
