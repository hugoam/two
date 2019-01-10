$input v_view, v_position, v_normal, v_tangent, v_color, v_texcoord0, v_texcoord1, v_binormal

#include <pbr/pbr.sh>

void main()
{
    Fragment fragment;
	fragment.position = v_view.xyz;
	fragment.view = normalize(-v_view.xyz);
	fragment.normal = normalize(v_normal);
	fragment.binormal = normalize(v_binormal);
	fragment.tangent = normalize(v_tangent);
	fragment.uv = v_texcoord0.xy;
	fragment.uv2 = v_texcoord1.xy;
	fragment.color = v_color;
    
#include "fs_depth.sh"
#include "fs_normal.sh"

    Material material;
	material.albedo = u_albedo.rgb * sample_material_texture(s_albedo, fragment.uv).rgb;
    material.roughness = u_roughness * sample_material_texture(s_roughness, fragment.uv)[ int(u_roughness_channel) ];
	material.metallic = u_metallic * sample_material_texture(s_metallic, fragment.uv)[ int(u_metallic_channel) ];
    material.specular = u_specular;
	material.alpha = 1.0;

	vec4 emission = vec4_splat(0.0);
#include "fs_emission.sh"
#include "fs_anisotropy.sh"
#include "fs_ao.sh"

#if BGFX_SHADER_LANGUAGE_HLSL
    fragment.depth = gl_FragCoord.w;
#else
    fragment.depth = -fragment.position.z;
#endif

	gl_FragData[0] = vec4(fragment.position, 1.0);
	gl_FragData[1] = vec4(fragment.normal, 1.0);
	gl_FragData[2] = vec4(material.albedo, 1.0);
	gl_FragData[3] = vec4(material.roughness, material.metallic, material.specular, 1.0);
}
