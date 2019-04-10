$input v_uv0
#include <filter.sh>
float PHBeckmann(float ndoth, float m)
{
float alpha = acos(ndoth);
float ta = tan(alpha);
float val = 1.0 / (m * m * pow(ndoth, 4.0)) * exp(-(ta * ta) / (m * m));
return val;
}
float KSTextureCompute(vec2 tex)
{
return 0.5 * pow(PHBeckmann(tex.x, tex.y), 0.1);
}
void main()
{
float x = KSTextureCompute(v_uv0);
gl_FragColor = vec4(x, x, x, 1.0);
}
