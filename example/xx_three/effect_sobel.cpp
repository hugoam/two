//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

// @author alteredq / http://alteredqualia.com/
// Luminosity http://en.wikipedia.org/wiki/Luminosity

static string luminosity_vertex()
{
	string shader =

		"$input a_position, a_texcoord0\n"
		"$output v_uv0\n"

		"#include <filter.sh>\n"

		"void main()\n"
		"{\n"
		"	v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;\n"
		"	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));\n"
		"}\n";

	return shader;
}

static string luminosity_fragment()
{
	string shader =

		"$input v_uv0\n"

		"#include <filter.sh>\n"

		"float linearToRelativeLuminance(const in vec3 color) {\n"
		"	vec3 weights = vec3(0.2126, 0.7152, 0.0722);\n"
		"	return dot(weights, color.rgb);\n"
		"}\n"

		"void main()\n"
		"{\n"
			"vec4 texel = texture2D(s_source_0, v_uv0);\n"
			"float l = linearToRelativeLuminance(texel.rgb);\n"

			"gl_FragColor = vec4(l, l, l, texel.w);\n"
		"}";

	return shader;
}

// @author Mugen87 / https://github.com/Mugen87
// Sobel Edge Detection (see https://youtu.be/uihBwtPIBxM)

static string sobel_vertex()
{
	string shader =

		"$input a_position, a_texcoord0\n"
		"$output v_uv0\n"

		"#include <filter.sh>\n"

		"void main()\n"
		"{\n"
		"	v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;\n"
		"	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));\n"
		"}\n";

	return shader;
}

static string sobel_fragment()
{
	string shader =

		"$input v_uv0\n"

		"#include <filter.sh>\n"

		"void main() {\n"

			"vec2 texel = u_pixel_size;\n"

			// kernel definition (in glsl matrices are filled in column-major order)

			"const mat3 Gx = mat3(-1, -2, -1, 0, 0, 0, 1, 2, 1);\n" // x direction kernel
			"const mat3 Gy = mat3(-1, 0, 1, -2, 0, 2, -1, 0, 1);\n" // y direction kernel

			// fetch the 3x3 neighbourhood of a fragment

			// first column

			"float tx0y0 = texture2D(s_source_0, v_uv0 + texel * vec2(-1, -1)).r;\n"
			"float tx0y1 = texture2D(s_source_0, v_uv0 + texel * vec2(-1,  0)).r;\n"
			"float tx0y2 = texture2D(s_source_0, v_uv0 + texel * vec2(-1,  1)).r;\n"

			// second column

			"float tx1y0 = texture2D(s_source_0, v_uv0 + texel * vec2(0, -1)).r;\n"
			"float tx1y1 = texture2D(s_source_0, v_uv0 + texel * vec2(0,  0)).r;\n"
			"float tx1y2 = texture2D(s_source_0, v_uv0 + texel * vec2(0,  1)).r;\n"

			// third column

			"float tx2y0 = texture2D(s_source_0, v_uv0 + texel * vec2(1, -1)).r;\n"
			"float tx2y1 = texture2D(s_source_0, v_uv0 + texel * vec2(1,  0)).r;\n"
			"float tx2y2 = texture2D(s_source_0, v_uv0 + texel * vec2(1,  1)).r;\n"

			// gradient value in x direction

			"float valueGx = Gx[0][0] * tx0y0 + Gx[1][0] * tx1y0 + Gx[2][0] * tx2y0 + \n"
				"Gx[0][1] * tx0y1 + Gx[1][1] * tx1y1 + Gx[2][1] * tx2y1 + \n"
				"Gx[0][2] * tx0y2 + Gx[1][2] * tx1y2 + Gx[2][2] * tx2y2; \n"

			// gradient value in y direction

			"float valueGy = Gy[0][0] * tx0y0 + Gy[1][0] * tx1y0 + Gy[2][0] * tx2y0 + \n"
				"Gy[0][1] * tx0y1 + Gy[1][1] * tx1y1 + Gy[2][1] * tx2y1 + \n"
				"Gy[0][2] * tx0y2 + Gy[1][2] * tx1y2 + Gy[2][2] * tx2y2; \n"

			// magnitute of the total gradient

			"float G = sqrt((valueGx * valueGx) + (valueGy * valueGy));\n"

			"gl_FragColor = vec4(vec3_splat(G), 1);\n"

		"}";

	return shader;
}

void pass_grayscale(GfxSystem& gfx, Render& render)
{
	// color to grayscale conversion

	Program& program = gfx.programs().fetch("sobel_lum");

	Pass pass = render.next_pass("sobel_lum", PassType::PostProcess);
	gfx.m_filter->source0(render.m_target->m_diffuse);
	gfx.m_filter->quad(pass, render.m_target->m_post.swap(), program);
}

void pass_sobel(GfxSystem& gfx, Render& render)
{
	// you might want to use a gaussian blur filter before
	// the next pass to improve the result of the Sobel operator

	// Sobel operator

	Program& program = gfx.programs().fetch("sobel");

	Pass pass = render.next_pass("sobel", PassType::PostProcess);
	gfx.m_filter->source0(render.m_target->m_post.last());
	gfx.m_filter->quad(pass, render.m_target->m_post.swap(), program);

	gfx.m_copy->quad(render.composite_pass("flip"), *render.m_fbo, render.m_target->m_post.last());
}

void xx_effect_sobel(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controls(viewer);

	Scene& scene = viewer.m_scene;
	Camera& camera = viewer.m_camera;

	static Node3* light = nullptr;

	static bool enabled = true;

	if(init)
	{
		camera.m_fov = 70.f; camera.m_near = 1.f; camera.m_far = 1000.f;
		camera.m_eye = vec3(0.f, 10.f, 25.f);

		Program& lum = app.m_gfx.programs().create("sobel_lum");
		lum.m_sources[ShaderType::Vertex] = luminosity_vertex();
		lum.m_sources[ShaderType::Fragment] = luminosity_fragment();

		Program& sobel = app.m_gfx.programs().create("sobel");
		sobel.m_sources[ShaderType::Vertex] = sobel_vertex();
		sobel.m_sources[ShaderType::Fragment] = sobel_fragment();

		//var geometry = new THREE.TorusKnotBufferGeometry(8, 3, 256, 32, 2, 3);
		Symbol symbol; symbol.m_subdiv = uvec2(256U, 32U);
		Model& geometry = app.m_gfx.shape(TorusKnot(8.f, 3.f), symbol);

		Program& phong = app.m_gfx.programs().fetch("pbr/phong");

		Material& material = app.m_gfx.materials().create("sobel", [&](Material& m) {
			m.m_program = &phong;
			m.m_phong.m_diffuse = rgb(0xffff00);
		});

		Node3& n = gfx::nodes(scene).add(Node3());
		gfx::items(scene).add(Item(n, geometry, 0U, &material));

		scene.m_env.m_radiance.m_ambient = 0.4f;
		scene.m_env.m_radiance.m_colour = rgb(0xcccccc);
		
		Node3& ln = gfx::nodes(scene).add(Node3());
		Light& l = gfx::lights(scene).add(Light(ln, LightType::Point, false, rgb(0xffffff), 0.8f, 0.f));
		light = &ln;

		auto render = [](GfxSystem& gfx, Render& render)
		{
			begin_pbr_render(gfx, render);

			pass_clear(gfx, render);
			pass_opaque(gfx, render);

			if(enabled)
			{
				pass_grayscale(gfx, render);
				pass_sobel(gfx, render);
			}
		};

		app.m_gfx.set_renderer(Shading::Shaded, render);
	}

	light->apply(camera.m_eye);

	//gui.add(params, 'enable');
}
