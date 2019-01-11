#include <gltf/Api.h>
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(mud_gltf)
{
    
    // Enums
    enum_<glTFAlphaMode>("glTFAlphaMode")
        .value("OPAQUE", glTFAlphaMode::OPAQUE)
        .value("MASK", glTFAlphaMode::MASK)
        .value("BLEND", glTFAlphaMode::BLEND)
        ;
    enum_<glTFComponentType>("glTFComponentType")
        .value("BYTE", glTFComponentType::BYTE)
        .value("UNSIGNED_BYTE", glTFComponentType::UNSIGNED_BYTE)
        .value("SHORT", glTFComponentType::SHORT)
        .value("UNSIGNED_SHORT", glTFComponentType::UNSIGNED_SHORT)
        .value("INT", glTFComponentType::INT)
        .value("FLOAT", glTFComponentType::FLOAT)
        ;
    enum_<glTFInterpolation>("glTFInterpolation")
        .value("LINEAR", glTFInterpolation::LINEAR)
        .value("STEP", glTFInterpolation::STEP)
        .value("CATMULLROMSPLINE", glTFInterpolation::CATMULLROMSPLINE)
        .value("CUBIC_SPLINE", glTFInterpolation::CUBIC_SPLINE)
        ;
    enum_<glTFPrimitiveType>("glTFPrimitiveType")
        .value("POINTS", glTFPrimitiveType::POINTS)
        .value("LINES", glTFPrimitiveType::LINES)
        .value("LINE_LOOP", glTFPrimitiveType::LINE_LOOP)
        .value("LINE_STRIP", glTFPrimitiveType::LINE_STRIP)
        .value("TRIANGLES", glTFPrimitiveType::TRIANGLES)
        .value("TRIANGLE_STRIP", glTFPrimitiveType::TRIANGLE_STRIP)
        .value("TRIANGLE_FAN", glTFPrimitiveType::TRIANGLE_FAN)
        ;
    enum_<glTFType>("glTFType")
        .value("SCALAR", glTFType::SCALAR)
        .value("VEC2", glTFType::VEC2)
        .value("VEC3", glTFType::VEC3)
        .value("VEC4", glTFType::VEC4)
        .value("MAT2", glTFType::MAT2)
        .value("MAT3", glTFType::MAT3)
        .value("MAT4", glTFType::MAT4)
        .value("INVALID", glTFType::INVALID)
        ;
    
    // Sequences
    
    // Arrays
    
    // Structs
    value_object<glTF>("glTF")
        .field("buffers", &glTF::buffers)
        .field("buffer_views", &glTF::buffer_views)
        .field("accessors", &glTF::accessors)
        .field("images", &glTF::images)
        .field("textures", &glTF::textures)
        .field("materials", &glTF::materials)
        .field("meshes", &glTF::meshes)
        .field("nodes", &glTF::nodes)
        .field("skins", &glTF::skins)
        .field("animations", &glTF::animations)
        .field("cameras", &glTF::cameras)
        .field("samplers", &glTF::samplers)
        .field("scenes", &glTF::scenes)
        ;
    value_object<glTFAccessor>("glTFAccessor")
        .field("name", &glTFAccessor::name)
        .field("buffer_view", &glTFAccessor::buffer_view)
        .field("byte_offset", &glTFAccessor::byte_offset)
        .field("component_type", &glTFAccessor::component_type)
        .field("normalized", &glTFAccessor::normalized)
        .field("count", &glTFAccessor::count)
        .field("type", &glTFAccessor::type)
        .field("sparse", &glTFAccessor::sparse)
        ;
    value_object<glTFAnimation>("glTFAnimation")
        .field("name", &glTFAnimation::name)
        .field("samplers", &glTFAnimation::samplers)
        .field("channels", &glTFAnimation::channels)
        ;
    value_object<glTFAnimationChannel>("glTFAnimationChannel")
        .field("sampler", &glTFAnimationChannel::sampler)
        .field("target", &glTFAnimationChannel::target)
        ;
    value_object<glTFAnimationSampler>("glTFAnimationSampler")
        .field("interpolation", &glTFAnimationSampler::interpolation)
        .field("input", &glTFAnimationSampler::input)
        .field("output", &glTFAnimationSampler::output)
        ;
    value_object<glTFAnimationTarget>("glTFAnimationTarget")
        .field("node", &glTFAnimationTarget::node)
        .field("path", &glTFAnimationTarget::path)
        ;
    value_object<glTFAttributes>("glTFAttributes")
        .field("POSITION", &glTFAttributes::POSITION)
        .field("NORMAL", &glTFAttributes::NORMAL)
        .field("TANGENT", &glTFAttributes::TANGENT)
        .field("TEXCOORD_0", &glTFAttributes::TEXCOORD_0)
        .field("TEXCOORD_1", &glTFAttributes::TEXCOORD_1)
        .field("COLOR_0", &glTFAttributes::COLOR_0)
        .field("JOINTS_0", &glTFAttributes::JOINTS_0)
        .field("WEIGHTS_0", &glTFAttributes::WEIGHTS_0)
        ;
    value_object<glTFBuffer>("glTFBuffer")
        .field("name", &glTFBuffer::name)
        .field("mime_type", &glTFBuffer::mime_type)
        .field("uri", &glTFBuffer::uri)
        .field("byte_length", &glTFBuffer::byte_length)
        ;
    value_object<glTFBufferView>("glTFBufferView")
        .field("name", &glTFBufferView::name)
        .field("buffer", &glTFBufferView::buffer)
        .field("byte_offset", &glTFBufferView::byte_offset)
        .field("byte_length", &glTFBufferView::byte_length)
        .field("byte_stride", &glTFBufferView::byte_stride)
        .field("target", &glTFBufferView::target)
        ;
    value_object<glTFCamera>("glTFCamera")
        .field("name", &glTFCamera::name)
        .field("type", &glTFCamera::type)
        .field("orthographic", &glTFCamera::orthographic)
        .field("perspective", &glTFCamera::perspective)
        ;
    value_object<glTFImage>("glTFImage")
        .field("name", &glTFImage::name)
        .field("mime_type", &glTFImage::mime_type)
        .field("uri", &glTFImage::uri)
        .field("buffer_view", &glTFImage::buffer_view)
        ;
    value_object<glTFMaterial>("glTFMaterial")
        .field("name", &glTFMaterial::name)
        .field("normal_texture", &glTFMaterial::normal_texture)
        .field("occlusion_texture", &glTFMaterial::occlusion_texture)
        .field("emissive_factor", &glTFMaterial::emissive_factor)
        .field("emissive_texture", &glTFMaterial::emissive_texture)
        .field("double_sided", &glTFMaterial::double_sided)
        .field("alpha_mode", &glTFMaterial::alpha_mode)
        .field("pbr_metallic_roughness", &glTFMaterial::pbr_metallic_roughness)
        ;
    value_object<glTFMaterialPBR>("glTFMaterialPBR")
        .field("base_color_factor", &glTFMaterialPBR::base_color_factor)
        .field("base_color_texture", &glTFMaterialPBR::base_color_texture)
        .field("metallic_factor", &glTFMaterialPBR::metallic_factor)
        .field("roughness_factor", &glTFMaterialPBR::roughness_factor)
        .field("metallic_roughness_texture", &glTFMaterialPBR::metallic_roughness_texture)
        ;
    value_object<glTFMesh>("glTFMesh")
        .field("name", &glTFMesh::name)
        .field("primitives", &glTFMesh::primitives)
        .field("weights", &glTFMesh::weights)
        ;
    value_object<glTFMorphTarget>("glTFMorphTarget")
        .field("POSITION", &glTFMorphTarget::POSITION)
        .field("NORMAL", &glTFMorphTarget::NORMAL)
        .field("TANGENT", &glTFMorphTarget::TANGENT)
        ;
    value_object<glTFNode>("glTFNode")
        .field("name", &glTFNode::name)
        .field("mesh", &glTFNode::mesh)
        .field("camera", &glTFNode::camera)
        .field("skin", &glTFNode::skin)
        .field("matrix", &glTFNode::matrix)
        .field("translation", &glTFNode::translation)
        .field("rotation", &glTFNode::rotation)
        .field("scale", &glTFNode::scale)
        .field("children", &glTFNode::children)
        ;
    value_object<glTFNodeExtras>("glTFNodeExtras")
        ;
    value_object<glTFOrthographic>("glTFOrthographic")
        .field("xmag", &glTFOrthographic::xmag)
        .field("ymag", &glTFOrthographic::ymag)
        .field("zfar", &glTFOrthographic::zfar)
        .field("znear", &glTFOrthographic::znear)
        ;
    value_object<glTFPerspective>("glTFPerspective")
        .field("yfov", &glTFPerspective::yfov)
        .field("zfar", &glTFPerspective::zfar)
        .field("znear", &glTFPerspective::znear)
        .field("aspect_ration", &glTFPerspective::aspect_ration)
        ;
    value_object<glTFPrimitive>("glTFPrimitive")
        .field("attributes", &glTFPrimitive::attributes)
        .field("indices", &glTFPrimitive::indices)
        .field("material", &glTFPrimitive::material)
        .field("mode", &glTFPrimitive::mode)
        .field("targets", &glTFPrimitive::targets)
        ;
    value_object<glTFSampler>("glTFSampler")
        .field("mag_filter", &glTFSampler::mag_filter)
        .field("min_filter", &glTFSampler::min_filter)
        .field("wrap_s", &glTFSampler::wrap_s)
        .field("wrap_t", &glTFSampler::wrap_t)
        .field("name", &glTFSampler::name)
        ;
    value_object<glTFScene>("glTFScene")
        .field("name", &glTFScene::name)
        .field("nodes", &glTFScene::nodes)
        ;
    value_object<glTFSkin>("glTFSkin")
        .field("name", &glTFSkin::name)
        .field("skeleton", &glTFSkin::skeleton)
        .field("joints", &glTFSkin::joints)
        .field("inverse_bind_matrices", &glTFSkin::inverse_bind_matrices)
        ;
    value_object<glTFSparse>("glTFSparse")
        .field("count", &glTFSparse::count)
        .field("indices", &glTFSparse::indices)
        .field("values", &glTFSparse::values)
        ;
    value_object<glTFSparseIndices>("glTFSparseIndices")
        .field("buffer_view", &glTFSparseIndices::buffer_view)
        .field("byte_offset", &glTFSparseIndices::byte_offset)
        .field("component_type", &glTFSparseIndices::component_type)
        ;
    value_object<glTFSparseValues>("glTFSparseValues")
        .field("buffer_view", &glTFSparseValues::buffer_view)
        .field("byte_offset", &glTFSparseValues::byte_offset)
        ;
    value_object<glTFTexture>("glTFTexture")
        .field("name", &glTFTexture::name)
        .field("sampler", &glTFTexture::sampler)
        .field("source", &glTFTexture::source)
        ;
    value_object<glTFTextureInfo>("glTFTextureInfo")
        .field("index", &glTFTextureInfo::index)
        .field("scale", &glTFTextureInfo::scale)
        ;
    
    // Classes
    
    // Functions
    
}
