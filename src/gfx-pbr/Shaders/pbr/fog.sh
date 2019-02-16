#ifndef MUD_SHADER_FOG
#define MUD_SHADER_FOG

 #include "common.sh"

uniform vec4 u_fog_params_0;
#define u_fog_density u_fog_params_0.x
#define u_fog_color u_fog_params_0.yzw

uniform vec4 u_fog_params_1;
#define u_fog_depth_enabled u_fog_params_1.x
#define u_fog_depth_begin u_fog_params_1.y
#define u_fog_depth_curve u_fog_params_1.z

uniform vec4 u_fog_params_2;
#define u_fog_height_enabled u_fog_params_2.x
#define u_fog_height_min u_fog_params_2.y
#define u_fog_height_max u_fog_params_2.z
#define u_fog_height_curve u_fog_params_2.w

uniform vec4 u_fog_params_3;
#define u_fog_transmit_enabled u_fog_params_3.x
#define u_fog_transmit_curve u_fog_params_3.y


void apply_fog_0(Fragment fragment, inout vec3 color)
{
    float dist = length(fragment.position);
    float fog_distance = max(dist - u_fog_depth_begin, 0.0);
    
    //float eye_y = u_view[3][2];
    float eye_y = u_view[2][3];
    float fog_at_eye = exp(-u_fog_height_curve * eye_y);
    float fog_depth_intensity = fog_distance * fog_at_eye;
    
    float height = fragment.position.y * (fog_distance / dist);
    float t = u_fog_height_curve * height;
    const float threshold = 0.01;
    float fog_height_intensity = abs(t) > threshold ? (1.0 - exp(-t)) / t : 1.0;
    
    float fog = exp(-u_fog_density * fog_depth_intensity * fog_height_intensity);
    
#ifdef DIRECT_LIGHT
    float sun_highlight = saturate(dot(fragment.view, u_light_direction_attenuation[0].xyz));
    sun_highlight = pow(sun_highlight, 8.0);
    
    const vec3 u_fog_highlight_color = vec3(1.0, 1.0, 1.0);
    vec3 fog_color = mix(u_fog_color, u_fog_highlight_color, sun_highlight);
#else
    vec3 fog_color = u_fog_color.rgb;
#endif

    color = mix(fog_color, color, fog);
}


void apply_fog(Fragment fragment, inout vec3 emission, inout vec3 ambient, inout vec3 diffuse, inout vec3 specular)
{
    float fog_amount = 0.0;

#if 0
//#ifdef DIRECT_LIGHT
    float attenuation = pow(max(dot(normalize(fragment.position), -u_light_direction_attenuation[0].xyz), 0.0), 8.0);
    vec3 fog_color = mix(u_fog_color.rgb, u_fog_sun_color_amount.rgb, u_fog_sun_color_amount.a * attenuation);
#else
    vec3 fog_color = u_fog_color.rgb;
#endif

    if (bool(u_fog_depth_enabled)) {

        float fog_z = smoothstep(u_fog_depth_begin, u_z_far, -fragment.position.z);
        fog_amount = pow(fog_z, u_fog_depth_curve);
        
        if (bool(u_fog_transmit_enabled)) {
            vec3 total_light = emission + ambient + diffuse + specular;
            float transmit = pow(fog_z, u_fog_transmit_curve);
            fog_color = mix(max(total_light, fog_color), fog_color, transmit);
        }
    }

    if (bool(u_fog_height_enabled)) {
        float y = mul(u_invView, vec4(fragment.position, 1.0)).y;
        fog_amount = max(fog_amount, pow(1.0 - smoothstep(u_fog_height_min, u_fog_height_max, y), u_fog_height_curve));
    }

    float rev_amount = 1.0 - fog_amount;

    //emission = vec3(1.0, 0.0, 1.0);
    emission = emission * rev_amount + fog_color * fog_amount;
    ambient *= rev_amount;
    specular *= rev_amount;
    diffuse *= rev_amount;
}

#endif
