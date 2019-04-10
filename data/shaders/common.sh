#ifndef MUD_SHADER_COMMON
#define MUD_SHADER_COMMON

#include <bgfx_shader.sh>
#include <srgb.sh>
#include <gpu/material.sh>

//#define PI M_PI

#define PI 3.14159265359
#define PI2 6.28318530718
#define PIh 1.5707963267949
#define rPI 0.31830988618
#define rPI2 0.15915494
#define LOG2 1.442695
#define EPSILON 1e-6

#define saturate(a) clamp(a, 0.0, 1.0)

float pow2(float x) { return x*x; }
float pow3(float x) { return x*x*x; }
float pow4(float x) { float x2 = x*x; return x2*x2; }
float average(vec3 color) { return dot(color, vec3_splat(0.3333)); }

uniform vec4 u_render_p0;
#define u_time u_render_p0.x
#define u_origin_bottom_left u_render_p0.y
#define u_point_size u_render_p0.zw

uniform vec4 u_viewport_p0;
#define u_screen_size u_viewport_p0.xy
#define u_pixel_size u_viewport_p0.zw

uniform vec4 u_camera_p0;
#define u_z_near u_camera_p0.x
#define u_z_far u_camera_p0.y
#define u_fov u_camera_p0.z
#define u_aspect u_camera_p0.w

#ifdef MATERIALS_BUFFER
uniform vec4 u_state;
uniform vec4 u_state_vertex;
#define u_state_zone u_state.x
#define u_state_material u_state.y
#define u_state_material_vertex u_state_vertex.y
#else
#define u_state_zone 0
#define u_state_material 0
#define u_state_material_vertex 0
#endif

uniform vec4 u_morph_weights;

SAMPLER2D(s_color, 0);
SAMPLER2D(s_alpha, 1);

SAMPLER2D(s_user0, 12);
SAMPLER2D(s_user1, 13);
SAMPLER2D(s_user2, 14);
SAMPLER2D(s_user3, 15);
SAMPLER2D(s_user4, 6);
SAMPLER2D(s_user5, 7);

#ifdef DISPLACEMENT
SAMPLER2D(s_displace, 7);
#endif

float rand(vec2 uv)
{
    const float a = 12.9898; const float b = 78.233; const float c = 43758.5453;
    float dt = dot(uv.xy, vec2(a, b)), sn = mod(dt, PI);
    return fract(sin(sn) * c);
}

#if BGFX_SHADER_LANGUAGE_GLSL == 110
mat4 transpose(in mat4 mat)
{
    vec4 i0 = mat[0];
    vec4 i1 = mat[1];
    vec4 i2 = mat[2];
    vec4 i3 = mat[3];

    mat4 result = mat4(
        vec4(i0.x, i1.x, i2.x, i3.x),
        vec4(i0.y, i1.y, i2.y, i3.y),
        vec4(i0.z, i1.z, i2.z, i3.z),
        vec4(i0.w, i1.w, i2.w, i3.w)
    );

    return result;
}
#endif

#if BGFX_SHADER_LANGUAGE_GLSL <= 120
mat4 inverse(mat4 m) {
  float
      a00 = m[0][0], a01 = m[0][1], a02 = m[0][2], a03 = m[0][3],
      a10 = m[1][0], a11 = m[1][1], a12 = m[1][2], a13 = m[1][3],
      a20 = m[2][0], a21 = m[2][1], a22 = m[2][2], a23 = m[2][3],
      a30 = m[3][0], a31 = m[3][1], a32 = m[3][2], a33 = m[3][3],

      b00 = a00 * a11 - a01 * a10,
      b01 = a00 * a12 - a02 * a10,
      b02 = a00 * a13 - a03 * a10,
      b03 = a01 * a12 - a02 * a11,
      b04 = a01 * a13 - a03 * a11,
      b05 = a02 * a13 - a03 * a12,
      b06 = a20 * a31 - a21 * a30,
      b07 = a20 * a32 - a22 * a30,
      b08 = a20 * a33 - a23 * a30,
      b09 = a21 * a32 - a22 * a31,
      b10 = a21 * a33 - a23 * a31,
      b11 = a22 * a33 - a23 * a32,

      det = b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06;

  return mat4(
      a11 * b11 - a12 * b10 + a13 * b09,
      a02 * b10 - a01 * b11 - a03 * b09,
      a31 * b05 - a32 * b04 + a33 * b03,
      a22 * b04 - a21 * b05 - a23 * b03,
      a12 * b08 - a10 * b11 - a13 * b07,
      a00 * b11 - a02 * b08 + a03 * b07,
      a32 * b02 - a30 * b05 - a33 * b01,
      a20 * b05 - a22 * b02 + a23 * b01,
      a10 * b10 - a11 * b08 + a13 * b06,
      a01 * b08 - a00 * b10 - a03 * b06,
      a30 * b04 - a31 * b02 + a33 * b00,
      a21 * b02 - a20 * b04 - a23 * b00,
      a11 * b07 - a10 * b09 - a12 * b06,
      a00 * b09 - a01 * b07 + a02 * b06,
      a31 * b01 - a30 * b03 - a32 * b00,
      a20 * b03 - a21 * b01 + a22 * b00) / det;
}
#endif

vec4 sample_material_texture(sampler2D tex, vec2 uv)
{
    return texture2D(tex, uv);
}

float linear_depth(float depth)
{
    depth = 2.0 * depth - 1.0;
    return 2.0 * u_z_near * u_z_far / (u_z_far + u_z_near - depth * (u_z_far - u_z_near));
}

float linearize_depth(float depth)
{
    float w = depth * ((u_z_far - u_z_near) / (-u_z_far * u_z_near)) + u_z_far / (u_z_far * u_z_near);
    return -1.0 / w;
    //return rcp(w);
}

float viewZToOrthographicDepth(float viewZ)
{
    return (viewZ + u_z_near) / (u_z_near - u_z_far);
}

float orthographicDepthToViewZ(float linearClipZ)
{
    return linearClipZ * (u_z_near - u_z_far) - u_z_near;
}

float viewZToPerspectiveDepth(float viewZ)
{
    return ((u_z_near + viewZ) * u_z_far) / ((u_z_far - u_z_near) * viewZ);
}

float perspectiveDepthToViewZ(float invClipZ)
{
    return (u_z_near * u_z_far) / ((u_z_far - u_z_near) * invClipZ - u_z_far);
}

vec4 LinearToGamma(vec4 value, float gammaFactor) {
    return vec4(pow(value.rgb, vec3_splat(1.0 / gammaFactor)), value.a);
}

mat4 mat4_from_vec4(vec4 v0, vec4 v1, vec4 v2, vec4 v3)
{
    mat4 mat;
    mat[0] = v0;
    mat[1] = v1;
    mat[2] = v2;
    mat[3] = v3;
#if BGFX_SHADER_LANGUAGE_HLSL
    return transpose(mat);
#else
    return mat;
#endif
}

float random(vec2 _uv)
{
    return fract(sin(dot(_uv.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

#endif
