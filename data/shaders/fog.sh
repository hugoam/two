#ifndef MUD_SHADER_FOG
#define MUD_SHADER_FOG

 #include <common.sh>
 #include <pbr/pbr.sh>

uniform vec4 u_fog_p0;
#define u_fog_density u_fog_p0.x
#define u_fog_color u_fog_p0.yzw

uniform vec4 u_fog_p1;
#define u_fog_depth_enabled u_fog_p1.x
#define u_fog_depth_begin u_fog_p1.y
#define u_fog_depth_end u_fog_p1.z
#define u_fog_depth_curve u_fog_p1.w

#define u_fog_near u_fog_p1.y
#define u_fog_far u_fog_p1.z

uniform vec4 u_fog_p2;
#define u_fog_height_enabled u_fog_p2.x
#define u_fog_height_min u_fog_p2.y
#define u_fog_height_max u_fog_p2.z
#define u_fog_height_curve u_fog_p2.w

uniform vec4 u_fog_p3;
#define u_fog_transmit_enabled u_fog_p3.x
#define u_fog_transmit_curve u_fog_p3.y

uniform vec4 u_fog_p4;
#define u_fog_sun_color u_fog_p3.xyz
#define u_fog_sun_amount u_fog_p3.w

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
    
    vec3 fog_color;
    if(u_light_counts[LIGHT_DIRECT] > 0)
    {
        Light light = read_light(0);
        float sun_highlight = saturate(dot(fragment.view, light.direction));
        sun_highlight = pow(sun_highlight, 8.0);
        
        const vec3 u_fog_highlight_color = vec3(1.0, 1.0, 1.0);
        fog_color = mix(u_fog_color, u_fog_highlight_color, sun_highlight);
    }
    else
    {
        fog_color = u_fog_color.rgb;
    }

    color = mix(fog_color, color, fog);
}


void apply_fog(Fragment fragment, inout vec3 emission, inout vec3 ambient, inout vec3 diffuse, inout vec3 specular)
{
    float fog_amount = 0.0;

    vec3 fog_color;
    if(u_light_counts[LIGHT_DIRECT] > 0)
    {
        Light light = read_light(0);
        float attenuation = pow(max(dot(normalize(fragment.position), -light.direction), 0.0), 8.0);
        fog_color = mix(u_fog_color, u_fog_sun_color, u_fog_sun_amount * attenuation);
    }
    else
    {
        fog_color = u_fog_color;
    }

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
