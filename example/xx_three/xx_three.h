//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <frame/Forward.h>

using namespace mud;

void xx_lights_point(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_shadow_point(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_shader(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_shader_lava(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_tiled_forward(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_perf(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_perf_twosided(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_perf_static(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_billboards(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_lines_dashed(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_lines_fat(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_geom(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_geom_sprites(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_geom_lines(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_geom_instances(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_geom_selective(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_geom_rawshader(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_geom_points(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_geom_points_packed(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_geom_points_instanced(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_interact_cubes(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_interact_geom(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_marching_cubes(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_hierarchy(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_hierarchy2(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_materials_skin(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_materials_standard(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_materials_variations(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_depth_texture(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_effect_dof(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_effect_godrays(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_effect_glitch(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_effect_sao(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
void xx_effect_sobel(Shell& app, Widget& parent, Dockbar& dockbar, bool init);

void ex_xx_three(Shell& app, Widget& parent, Dockbar& dockbar, bool init);
