$input v_color, v_uv0

#include <common.sh>

float remap(float number, float from_low, float from_high, float low, float high)
{
    float slope = (high - low) / (from_high - from_low);
    float result = low + slope * (number - from_low);
    return result;
}

float random(float co)
{
    return fract(sin(co * 12.989) * 43758.545);
}

void main()
{
    vec2 coord = v_uv0 - vec2(0.5,0.5);
    //float size = v_uv0.w;
    float ratio = remap(sin(u_time), -1.0, 1.0, 0.5, 1.0);
    float size = 0.4 * ratio;
    
    float r = length(coord);
    float angle = atan2(coord.y, coord.x) + v_uv0.z;
    
    float intensity = remap(sin(5.0 * (angle + u_time * 0.5)), -1.0, 1.0, 0.1, 1.0)
    		  		+ remap(sin(12.0 * (angle)), -1.0, 1.0, 0.1, 0.6);
    
    
    float roffset = remap(sin(5.0 * (angle + 1.3 + sin(u_time))), -1.0, 1.0, 0.0, 0.1)
    		  	  + remap(sin(12.0 * (angle + 1.3 + sin(u_time))), -1.0, 1.0, 0.0, 0.06);
    
    
    float goffset = remap(sin(5.0 * (angle - 1.3 - sin(u_time))), -1.0, 1.0, 0.0, 0.1)
    		  	  + remap(sin(12.0 * (angle - 1.3 - sin(u_time))), -1.0, 1.0, 0.0, 0.06);
    
    float dist = r / size;
    float factor = 0.05 / (dist * dist);
    float power = intensity * factor;
    float rscat = roffset * factor;
    float gscat = goffset * factor;
    
    vec4 rgba = vec4(power - rscat, power - gscat, power, power);
    //vec4 rgba = vec4_splat(v_uv0.z);
    
	//rgba.rgb = rgba.rgb * v_color.rgb * rgba.a * v_color.a;
	//rgba.a   = rgba.a * v_color.a * (1.0f - v_uv0.z);
	gl_FragColor = rgba;
}
