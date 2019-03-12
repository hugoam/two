#ifndef MUD_SHADER_CONVERT
#define MUD_SHADER_CONVERT

vec3 convertRGB2XYZ(vec3 _rgb)
{
	// Reference:
	// RGB/XYZ Matrices
	// http://www.brucelindbloom.com/index.html?Eqn_RGB_XYZ_Matrix.html
	vec3 xyz;
	xyz.x = dot(vec3(0.4124564, 0.3575761, 0.1804375), _rgb);
	xyz.y = dot(vec3(0.2126729, 0.7151522, 0.0721750), _rgb);
	xyz.z = dot(vec3(0.0193339, 0.1191920, 0.9503041), _rgb);
	return xyz;
}

vec3 convertXYZ2RGB(vec3 _xyz)
{
	vec3 rgb;
	rgb.x = dot(vec3( 3.2404542, -1.5371385, -0.4985314), _xyz);
	rgb.y = dot(vec3(-0.9692660,  1.8760108,  0.0415560), _xyz);
	rgb.z = dot(vec3( 0.0556434, -0.2040259,  1.0572252), _xyz);
	return rgb;
}

vec3 convertXYZ2Yxy(vec3 _xyz)
{
	// Reference:
	// http://www.brucelindbloom.com/index.html?Eqn_XYZ_to_xyY.html
	float inv = 1.0/dot(_xyz, vec3(1.0, 1.0, 1.0) );
	return vec3(_xyz.y, _xyz.x*inv, _xyz.y*inv);
}

vec3 convertYxy2XYZ(vec3 _Yxy)
{
	// Reference:
	// http://www.brucelindbloom.com/index.html?Eqn_xyY_to_XYZ.html
	vec3 xyz;
	xyz.x = _Yxy.x*_Yxy.y/_Yxy.z;
	xyz.y = _Yxy.x;
	xyz.z = _Yxy.x*(1.0 - _Yxy.y - _Yxy.z)/_Yxy.z;
	return xyz;
}

vec3 convertRGB2Yxy(vec3 _rgb)
{
	return convertXYZ2Yxy(convertRGB2XYZ(_rgb) );
}

vec3 convertYxy2RGB(vec3 _Yxy)
{
	return convertXYZ2RGB(convertYxy2XYZ(_Yxy) );
}

vec3 convertRGB2Yuv(vec3 _rgb)
{
	vec3 yuv;
	yuv.x = dot(_rgb, vec3(0.299, 0.587, 0.114) );
	yuv.y = (_rgb.x - yuv.x)*0.713 + 0.5;
	yuv.z = (_rgb.z - yuv.x)*0.564 + 0.5;
	return yuv;
}

vec3 convertYuv2RGB(vec3 _yuv)
{
	vec3 rgb;
	rgb.x = _yuv.x + 1.403*(_yuv.y-0.5);
	rgb.y = _yuv.x - 0.344*(_yuv.y-0.5) - 0.714*(_yuv.z-0.5);
	rgb.z = _yuv.x + 1.773*(_yuv.z-0.5);
	return rgb;
}

vec3 convertRGB2YIQ(vec3 _rgb)
{
	vec3 yiq;
	yiq.x = dot(vec3(0.299,     0.587,     0.114   ), _rgb);
	yiq.y = dot(vec3(0.595716, -0.274453, -0.321263), _rgb);
	yiq.z = dot(vec3(0.211456, -0.522591,  0.311135), _rgb);
	return yiq;
}

vec3 convertYIQ2RGB(vec3 _yiq)
{
	vec3 rgb;
	rgb.x = dot(vec3(1.0,  0.9563,  0.6210), _yiq);
	rgb.y = dot(vec3(1.0, -0.2721, -0.6474), _yiq);
	rgb.z = dot(vec3(1.0, -1.1070,  1.7046), _yiq);
	return rgb;
}

vec3 hsv_to_rgb(vec3 hsv)
{
    hsv.x = mod(100.0 + hsv.x, 1.0);       // Ensure [0,1[

    float slice = 6.0 * hsv.x;             // In [0,6[
    float islice = floor(slice);
    float interp_slice = slice - islice;   // In [0,1[ for each hue slice

    vec3 rgb_no_hue = vec3(hsv.z * (1.0 - hsv.y),
                           hsv.z * (1.0 - hsv.y * interp_slice),
                           hsv.z * (1.0 - hsv.y * (1.0 - interp_slice)) );

    float is_odd = mod(islice, 2.0);                 // 0 if even (slices 0, 2, 4), 1 if odd (slices 1, 3, 5)
    float slice_index = 0.5 * (islice - is_odd);     // (0, 1, 2) corresponding to slices (0, 2, 4) and (1, 3, 5)

    vec3 rgb_even_slices = vec3(hsv.z, rgb_no_hue.zx);               // (V, Temp Blue, Temp Red) for even slices (0, 2, 4)
    vec3 rgb_odd_slices = vec3(rgb_no_hue.y, hsv.z, rgb_no_hue.x);   // (Temp Green, V, Temp Red) for odd slices (1, 3, 5)
    vec3 rgb_slices = mix(rgb_even_slices, rgb_odd_slices, is_odd);

    float is_not_first_slice = saturate(slice_index);                   // 1 if NOT the first slice (true for slices 1 and 2)
    float is_not_second_slice = saturate(slice_index - 1.0);            // 1 if NOT the first or second slice (true only for slice 2)

    return mix(rgb_slices.xyz, mix(rgb_slices.zxy, rgb_slices.yzx, is_not_second_slice), is_not_first_slice);    // Make the RGB rotate right depending on final slice index
}

vec3 hue_to_rgb(float hue)
{
    hue = mod(hue, 1.0);
    float r = abs(hue * 6.0 - 3.0) - 1.0;
    float g = 2.0 - abs(hue * 6.0 - 2.0);
    float b = 2.0 - abs(hue * 6.0 - 4.0);
    return clamp(vec3(r,g,b), 0.0, 1.0);
}

vec3 hsl_to_rgb(vec3 hsl)
{
    vec3 rgb = hue_to_rgb(hsl.x);
    float C = (1.0 - abs(2.0 * hsl.z - 1.0)) * hsl.y;
    return (rgb - 0.5) * C + hsl.z;
}

vec3 adjustHue(vec3 _rgb, float _hue)
{
    vec3 yiq = convertRGB2YIQ(_rgb);
    float angle = _hue + atan2(yiq.z, yiq.y);
    float len = length(yiq.yz);
    return convertYIQ2RGB(vec3(yiq.x, len*cos(angle), len*sin(angle) ) );
}

#endif // MUD_SHADER_CONVERT
