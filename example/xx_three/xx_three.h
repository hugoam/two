//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#define UI 1

#if UI
#include <frame/Forward.h>
#include <frame/Api.h>
using ShellX = two::Shell;
using WindowX = two::ShellWindow;
#else
#include <xx_three/gfxshell.h>
using ShellX = two::GfxShell;
using WindowX = two::GfxWindow;
#endif

using namespace two;

#if UI
#define EX(name) void name(ShellX& app, Widget& parent, Dockbar& dockbar, bool init)
#else
#define EX(name) void name(ShellX& app, GfxWindow& window, bool init)
#endif

EX(xx_light_point);
EX(xx_light_hemisphere);
EX(xx_shadow_point);
EX(xx_shader);
EX(xx_shader_lava);
EX(xx_clustered);
EX(xx_tiled_forward);
EX(xx_perf);
EX(xx_perf_twosided);
EX(xx_perf_static);
EX(xx_billboards);
EX(xx_lines_dashed);
EX(xx_lines_fat);
EX(xx_geom_dynamic);
EX(xx_geom_sprites);
EX(xx_geom_lines);
EX(xx_geom_instances);
EX(xx_geom_selective);
EX(xx_geom_rawshader);
EX(xx_geom_points);
EX(xx_geom_points_hw);
EX(xx_geom_points_packed);
EX(xx_interact_cubes);
EX(xx_interact_geom);
EX(xx_marching_cubes);
EX(xx_hierarchy);
EX(xx_hierarchy2);
EX(xx_material_cubemap);
EX(xx_material_displace);
EX(xx_material_skin);
EX(xx_material_standard);
EX(xx_material_variations);
EX(xx_depth_texture);
EX(xx_effect);
EX(xx_effect_dof);
EX(xx_effect_godrays);
EX(xx_effect_halftone);
EX(xx_effect_glitch);
EX(xx_effect_sao);
EX(xx_effect_sobel);
EX(xx_effect_bloom);
EX(xx_post_fxaa);
EX(xx_cubemap_dynamic);
EX(xx_shader_ocean);
EX(xx_shader2);
EX(xx_material_translucent);
EX(xx_refraction_mesh);
EX(xx_refraction_balls);
EX(xx_loader_gltf);
EX(xx_loader_ply);

//void ex_xx_three(ShellX& app, Widget& parent, Dockbar& dockbar, bool init);
