$input v_view, v_position, v_normal, v_tangent, v_color, v_texcoord0/*, v_texcoord1*/, v_binormal

#include "pbr.sh"

#include "light.sh"
#include "radiance.sh"

void main()
{
    Fragment fragment;
	fragment.position = v_view.xyz;
	fragment.view = normalize(-v_view.xyz);
	fragment.normal = normalize(v_normal);
	fragment.binormal = normalize(v_binormal);
	fragment.tangent = normalize(v_tangent);
	fragment.uv = v_texcoord0.xy;
	//fragment.uv2 = v_texcoord1.xy;
	fragment.color = v_color;
    
#include "fs_depth.sh"
#include "fs_normal.sh"

    Material material;
	material.albedo = u_albedo.rgb * sample_material_texture(s_albedo, fragment.uv).rgb;
    material.roughness = u_roughness * sample_material_texture(s_roughness, fragment.uv)[ int(u_roughness_channel) ];
	material.metallic = u_metallic * sample_material_texture(s_metallic, fragment.uv)[ int(u_metallic_channel) ];
    material.specular = u_specular;
	material.alpha = 1.0;

    // metallic energy conservation
	vec3 dielectric = vec3_splat(0.034) * material.specular * 2.0;
	material.f0 = mix(dielectric, material.albedo, material.metallic);
    material.albedo = mix(material.albedo, vec3_splat(0.0), material.metallic);
        
#include "fs_emission.sh"
#include "fs_anisotropy.sh"
#include "fs_ao.sh"

	fragment.NoV = saturate(dot(fragment.normal, fragment.view));
    
    // Radiance radiance;
	vec3 specular = vec3_splat(0.0);
	vec3 diffuse = vec3_splat(0.0);
	vec3 ambient = vec3_splat(0.0);

#ifdef RADIANCE_ENVMAP
    ambient += radiance_ambient(fragment.normal);
    specular += radiance_reflection(fragment.view, fragment.normal, material.roughness);
#else
	ambient += u_radiance_color * u_ambient;
#endif
	ambient *= material.albedo;
    
#ifdef AMBIENT_OCCLUSION
	ambient *= material.ao;
#endif

#if BGFX_SHADER_LANGUAGE_HLSL
    fragment.depth = gl_FragCoord.w;
#else
    fragment.depth = -fragment.position.z;
#endif

#ifdef DIRECTIONAL_LIGHT
	directional_light(fragment, material, fragment.depth, diffuse, specular);
#endif

    //apply_reflections(specular, ambient);
	apply_lights(fragment, material, diffuse, specular);
    
#ifdef DIFFUSE_TOON
	specular *= material.specular * material.metallic * material.albedo * 2.0;
#else
    specular *= brdf_specular_term(fragment, material);
#endif

#ifdef MRT
	gl_FragData[0] = vec4(emission + diffuse + ambient, material.alpha);
	gl_FragData[1] = vec4(specular, material.metallic);
	gl_FragData[2] = vec4(normalize(fragment.normal) * 0.5 + 0.5, material.roughness);
#ifdef SUBSURFACE
	gl_FragData[3] = subsurface;
#endif

#else
	gl_FragColor = vec4(emission + ambient + diffuse + specular, material.alpha);
	//gl_FragColor = vec4(fragment.normal, material.alpha);
#endif

}
