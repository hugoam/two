$input v_view, v_position, v_normal, v_tangent, v_color, v_uv0, v_uv1, v_binormal

#include <encode.sh>
#include <pbr/pbr.sh>
#include <pbr/light.sh>
#define BRDF_STANDARD
#include <pbr/light_brdf_three.sh>
#include <pbr/radiance.sh>
#include <gi/conetrace.sh>
#include <fog.sh>

void main()
{
#include "fs_fragment.sh"

#include "fs_pbr_material.sh"

#include "fs_three.sh"
#include "fs_out_pbr.sh"
#include "fs_fog_simple.sh"
}
