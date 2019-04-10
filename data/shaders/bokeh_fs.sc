$input v_uv0
#include <filter.sh>
uniform vec4 u_bokeh_p0;
#define u_focus    u_bokeh_p0.x
#define u_aperture u_bokeh_p0.y
#define u_maxblur  u_bokeh_p0.z
float getViewZ(float depth) {
	return perspectiveDepthToViewZ(depth);
}
void main() {
vec2 aspect = vec2(1.0, u_aspect);
float depth = texture2D(s_source_depth, v_uv0).x;
float viewZ = getViewZ(depth);
float factor = (u_focus + viewZ);
vec2 dofblur = vec2_splat(clamp(factor * u_aperture, -u_maxblur, u_maxblur));
vec2 dofblur9 = dofblur * 0.9;
vec2 dofblur7 = dofblur * 0.7;
vec2 dofblur4 = dofblur * 0.4;
vec4 col = vec4_splat(0.0);
col += texture2D(s_source_0, v_uv0);
col += texture2D(s_source_0, v_uv0 + (vec2( 0.0,   0.4 ) * aspect) * dofblur);
col += texture2D(s_source_0, v_uv0 + (vec2( 0.15,  0.37) * aspect) * dofblur);
col += texture2D(s_source_0, v_uv0 + (vec2( 0.29,  0.29) * aspect) * dofblur);
col += texture2D(s_source_0, v_uv0 + (vec2(-0.37,  0.15) * aspect) * dofblur);
col += texture2D(s_source_0, v_uv0 + (vec2( 0.40,  0.0 ) * aspect) * dofblur);
col += texture2D(s_source_0, v_uv0 + (vec2( 0.37, -0.15) * aspect) * dofblur);
col += texture2D(s_source_0, v_uv0 + (vec2( 0.29, -0.29) * aspect) * dofblur);
col += texture2D(s_source_0, v_uv0 + (vec2(-0.15, -0.37) * aspect) * dofblur);
col += texture2D(s_source_0, v_uv0 + (vec2( 0.0,  -0.4 ) * aspect) * dofblur);
col += texture2D(s_source_0, v_uv0 + (vec2(-0.15,  0.37) * aspect) * dofblur);
col += texture2D(s_source_0, v_uv0 + (vec2(-0.29,  0.29) * aspect) * dofblur);
col += texture2D(s_source_0, v_uv0 + (vec2( 0.37,  0.15) * aspect) * dofblur);
col += texture2D(s_source_0, v_uv0 + (vec2(-0.4,   0.0 ) * aspect) * dofblur);
col += texture2D(s_source_0, v_uv0 + (vec2(-0.37, -0.15) * aspect) * dofblur);
col += texture2D(s_source_0, v_uv0 + (vec2(-0.29, -0.29) * aspect) * dofblur);
col += texture2D(s_source_0, v_uv0 + (vec2( 0.15, -0.37) * aspect) * dofblur);
col += texture2D(s_source_0, v_uv0 + (vec2( 0.15,  0.37) * aspect) * dofblur9);
col += texture2D(s_source_0, v_uv0 + (vec2(-0.37,  0.15) * aspect) * dofblur9);
col += texture2D(s_source_0, v_uv0 + (vec2( 0.37, -0.15) * aspect) * dofblur9);
col += texture2D(s_source_0, v_uv0 + (vec2(-0.15, -0.37) * aspect) * dofblur9);
col += texture2D(s_source_0, v_uv0 + (vec2(-0.15,  0.37) * aspect) * dofblur9);
col += texture2D(s_source_0, v_uv0 + (vec2( 0.37,  0.15) * aspect) * dofblur9);
col += texture2D(s_source_0, v_uv0 + (vec2(-0.37, -0.15) * aspect) * dofblur9);
col += texture2D(s_source_0, v_uv0 + (vec2( 0.15, -0.37) * aspect) * dofblur9);
col += texture2D(s_source_0, v_uv0 + (vec2( 0.29,  0.29) * aspect) * dofblur7);
col += texture2D(s_source_0, v_uv0 + (vec2( 0.40,  0.0 ) * aspect) * dofblur7);
col += texture2D(s_source_0, v_uv0 + (vec2( 0.29, -0.29) * aspect) * dofblur7);
col += texture2D(s_source_0, v_uv0 + (vec2( 0.0,  -0.4 ) * aspect) * dofblur7);
col += texture2D(s_source_0, v_uv0 + (vec2(-0.29,  0.29) * aspect) * dofblur7);
col += texture2D(s_source_0, v_uv0 + (vec2(-0.4,   0.0 ) * aspect) * dofblur7);
col += texture2D(s_source_0, v_uv0 + (vec2(-0.29, -0.29) * aspect) * dofblur7);
col += texture2D(s_source_0, v_uv0 + (vec2( 0.0,   0.4 ) * aspect) * dofblur7);
col += texture2D(s_source_0, v_uv0 + (vec2( 0.29,  0.29) * aspect) * dofblur4);
col += texture2D(s_source_0, v_uv0 + (vec2( 0.4,   0.0 ) * aspect) * dofblur4);
col += texture2D(s_source_0, v_uv0 + (vec2( 0.29, -0.29) * aspect) * dofblur4);
col += texture2D(s_source_0, v_uv0 + (vec2( 0.0,  -0.4 ) * aspect) * dofblur4);
col += texture2D(s_source_0, v_uv0 + (vec2(-0.29,  0.29) * aspect) * dofblur4);
col += texture2D(s_source_0, v_uv0 + (vec2(-0.4,   0.0 ) * aspect) * dofblur4);
col += texture2D(s_source_0, v_uv0 + (vec2(-0.29, -0.29) * aspect) * dofblur4);
col += texture2D(s_source_0, v_uv0 + (vec2( 0.0,   0.4 ) * aspect) * dofblur4);
gl_FragColor = vec4(col.rgb / 41.0, 1.0);
}
