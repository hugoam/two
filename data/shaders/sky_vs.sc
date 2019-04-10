$input a_position
$output v_world, v_sundir, v_sunp0, v_betaR, v_betaM
#include <common.sh>
CONST(vec3) up = vec3(0.0, 1.0, 0.0);
CONST(float) e = 2.71828182845904523536028747135266249775724709369995957;
CONST(float) pi = 3.141592653589793238462643383279502884197169;
CONST(vec3) lambda = vec3(680E-9, 550E-9, 450E-9);
CONST(vec3) totalRayleigh = vec3(5.804542996261093E-6, 1.3562911419845635E-5, 3.0265902468824876E-5);
CONST(float) v = 4.0;
CONST(vec3) K = vec3(0.686, 0.678, 0.666);
CONST(vec3) MieConst = vec3(1.8399918514433978E14, 2.7798023919660528E14, 4.0790479543861094E14);
CONST(float) cutoffAngle = 1.6110731556870734;
CONST(float) steepness = 1.5;
CONST(float) EE = 1000.0;
float sunIntensity(float zenithAngleCos) {
	zenithAngleCos = clamp(zenithAngleCos, -1.0, 1.0);
	return EE * max(0.0, 1.0 - pow(e, -((cutoffAngle - acos(zenithAngleCos)) / steepness)));
}
vec3 totalMie(float T) {
	float c = (0.2 * T) * 10E-18;
	return 0.434 * c * MieConst;
}
void main() {
int material_index = int(u_state_material_vertex);
UserMaterial mat = read_user_material(material_index);
vec3 sunposition     = mat.p0.xyz;
float turbidity      = mat.p1.x;
float rayleigh       = mat.p1.y;
float mieCoefficient = mat.p2.x;
vec4 worldPosition = mul(u_model[0], vec4(a_position.xyz, 1.0));
v_world = worldPosition.xyz;
gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
gl_Position.z = gl_Position.w;
v_sundir = normalize(sunposition);
float sunE = sunIntensity(dot(v_sundir, up));
float sunfade = 1.0 - clamp(1.0 - exp((sunposition.y / 450000.0)), 0.0, 1.0);
v_sunp0 = vec2(sunfade, sunE);
float rayleighCoefficient = rayleigh - (1.0 * (1.0 - sunfade));
v_betaR = totalRayleigh * rayleighCoefficient;
v_betaM = totalMie(turbidity) * mieCoefficient;
}
