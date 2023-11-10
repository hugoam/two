$input v_world, v_sundir, v_sunp0, v_betaR, v_betaM
#include <common.sh>
CONST(vec3) cameraPos = vec3(0.0, 0.0, 0.0);
CONST(float) pi = 3.141592653589793238462643383279502884197169;
CONST(float) n = 1.0003;
CONST(float) N = 2.545E25;
CONST(float) rayleighZenithLength = 8.4E3;
CONST(float) mieZenithLength = 1.25E3;
CONST(vec3) up = vec3(0.0, 1.0, 0.0);
CONST(float) sunAngularDiameterCos = 0.999956676946448443553574619906976478926848692873900859324;
CONST(float) d3b16pi = 0.05968310365946075;
CONST(float) d1b4pi = 0.07957747154594767;
float rayleighPhase(float cosTheta) {
	return d3b16pi * (1.0 + pow(cosTheta, 2.0));
}
float hgPhase(float cosTheta, float g) {
	float g2 = pow(g, 2.0);
	float inverse = 1.0 / pow(1.0 - 2.0 * g * cosTheta + g2, 1.5);
	return d1b4pi * ((1.0 - g2) * inverse);
}
CONST(float) A = 0.15;
CONST(float) B = 0.50;
CONST(float) C = 0.10;
CONST(float) D = 0.20;
CONST(float) E = 0.02;
CONST(float) F = 0.30;
CONST(float) whiteScale = 1.0748724675633854;
vec3 Uncharted2Tonemap(vec3 x) {
	return ((x * (A * x + C * B) + D * E) / (x * (A * x + B) + D * F)) - E / F;
}
void main() {
int material_index = int(u_state_material);
UserMaterial mat = read_user_material(material_index);
float luminance       = mat.p1.z;
float mieDirectionalG = mat.p2.y;
float zenithAngle = acos(max(0.0, dot(up, normalize(v_world - cameraPos))));
float inverse = 1.0 / (cos(zenithAngle) + 0.15 * pow(93.885 - ((zenithAngle * 180.0) / pi), -1.253));
float sR = rayleighZenithLength * inverse;
float sM = mieZenithLength * inverse;
vec3 Fex = exp(-(v_betaR * sR + v_betaM * sM));
float cosTheta = dot(normalize(v_world - cameraPos), v_sundir);
float rPhase = rayleighPhase(cosTheta * 0.5 + 0.5);
vec3 betaRTheta = v_betaR * rPhase;
float mPhase = hgPhase(cosTheta, mieDirectionalG);
vec3 betaMTheta = v_betaM * mPhase;
float sunE = v_sunp0.y;vec3 Lin = pow(sunE * ((betaRTheta + betaMTheta) / (v_betaR + v_betaM)) * (1.0 - Fex), vec3_splat(1.5));
Lin *= mix(vec3_splat(1.0), pow(sunE * ((betaRTheta + betaMTheta) / (v_betaR + v_betaM)) * Fex, vec3_splat(1.0 / 2.0)), clamp(pow(1.0 - dot(up, v_sundir), 5.0), 0.0, 1.0));
vec3 direction = normalize(v_world - cameraPos);
float theta = acos(direction.y);
float phi = atan2(direction.z, direction.x);
vec2 uv = vec2(phi, theta) / vec2(2.0 * pi, pi) + vec2(0.5, 0.0);
vec3 L0 = vec3_splat(0.1) * Fex;
float sundisk = smoothstep(sunAngularDiameterCos, sunAngularDiameterCos + 0.00002, cosTheta);
L0 += (sunE * 19000.0 * Fex) * sundisk;
vec3 texColor = (Lin + L0) * 0.04 + vec3(0.0, 0.0003, 0.00075);
vec3 curr = Uncharted2Tonemap((log2(2.0 / pow(luminance, 4.0))) * texColor);
vec3 color = curr * whiteScale;
float sunfade = v_sunp0.x;vec3 retColor = pow(color, vec3_splat(1.0 / (1.2 + (1.2 * sunfade))));
gl_FragColor = vec4(retColor, 1.0);
}
