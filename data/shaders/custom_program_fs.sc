$input v_uv0
#include <filter.sh>
#define TAU 6.283185307179586
float spow(float x, float p) {
    return sign(x) * pow(abs(x), p);
}
void main() {
    float aspect = 1.0; //u_screen_size.x / u_screen_size.y;
    vec2 uvp = vec2(aspect, 1.0) * (2.0 * v_uv0 - 1.0);
    float r = length(uvp);
    float t = atan2(uvp.y, uvp.x) / TAU + 0.5;
    float P = 2.00;
    float Q = 1.00 + 0.5 * sin(u_time);
    float K = 0.25;
    float tw = 0.0;
    float dr = 0.0;
    for(int i = 2; i < 32; ++i) {
        float fi = float(i);
        float w = pow(K / fi, Q);
        tw += w;
        dr += w * spow(sin(fi * t * TAU + u_time / sqrt(fi)), P);
    }
    r += K * dr / tw;
    vec3 c = vec3_splat(0.0);
    float d =   exp(-sqrt(128.0 * max(0.0, r - 0.25)));
    d += 0.10 * exp(-sqrt(4.0 * max(0.0, r - 0.25)));
    d += 0.05 * exp(-sqrt(1.0 * max(0.0, r - 0.25)));
    c += mix(
        (vec3(1.1 + d, 3.0, 5.0) * d),
        (vec3(6.0, 2.3, 1.1 * d) * d),
        0.0);
    c = 1.0 - exp(-1.5 * pow(c, vec3_splat(1.25)));
    gl_FragData[0] = vec4(c, 1.0);
}
