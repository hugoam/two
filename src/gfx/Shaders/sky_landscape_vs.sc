$input a_position, a_normal, a_texcoord0
$output v_normal, v_uv0

/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <common.sh>

void main()
{
	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0) );

	vec3 normal = a_normal * 2.0 - 1.0;
	v_normal = mul(u_model[0], vec4(normal, 0.0) ).xyz;

	v_uv0 = a_texcoord0;
}
