//#include <mud/frame.h>
#include <frame/Api.h>
#include <ui/Edit/Lang.h>

#include <09_live_shader/09_live_shader.h>

using namespace mud;

string create_shader()
{
	string shader =

		"$input v_texcoord0\n"
		"\n"
		"#include \"filter/filter.sh\"\n"
		"\n"
		"#define PI 3.1415926553589793\n"
		"#define TAU 6.283185307179586\n"
		"\n"
		"float spow(float x, float p) {\n"
		"    return sign(x) * pow(abs(x), p);\n"
		"}\n"
		"\n"
		"void main() {\n"
		"    float aspect = 1.0; //u_screen_size.x / u_screen_size.y;\n"
		"    vec2 uvp = vec2(aspect, 1.0) * (2.0 * v_texcoord0.xy - 1.0);\n"
		"    float r = length(uvp);\n"
		"    float t = atan2(uvp.y, uvp.x) / TAU + 0.5;\n"
		"    float P = 2.00;\n"
		"    float Q = 1.00 + 0.5 * sin(u_time);\n"
		"    float K = 0.25;\n"
		"\n"
		"    float tw = 0.0;\n"
		"    float dr = 0.0;\n"
		"    for(int i = 2; i < 32; ++i) {\n"
		"        float fi = float(i);\n"
		"        float w = pow(K / fi, Q);\n"
		"        tw += w;\n"
		"        dr += w * spow(sin(fi * t * TAU + u_time / sqrt(fi)), P);\n"
		"    }\n"
		"    r += K * dr / tw;\n"
		"\n"
		"    vec3 c = vec3_splat(0.0);\n"
		"    float d =   exp(-sqrt(128.0 * max(0.0, r - 0.25)));\n"
		"    d += 0.10 * exp(-sqrt(4.0 * max(0.0, r - 0.25)));\n"
		"    d += 0.05 * exp(-sqrt(1.0 * max(0.0, r - 0.25)));\n"
		"    c += mix(\n"
		"        (vec3(1.1 + d, 3.0, 5.0) * d),\n"
		"        (vec3(6.0, 2.3, 1.1 * d) * d),\n"
		"        0.0);\n"
		"\n"
		"    c = 1.0 - exp(-1.5 * pow(c, vec3_splat(1.25)));\n"
		"    gl_FragData[0] = vec4(c, 1.0);\n"
		"}\n"
		;

	return shader;
}

void ex_09_live_shader(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(app);
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	Gnode& scene = viewer.m_scene.begin();

	static string source = create_shader();

	static Program program = { "custom_program", {}, { nullptr, source.c_str(), nullptr, nullptr } };
	
	auto draw_quad = [](Render& render, const Pass& render_pass)
	{
		BlockFilter& filter = *render.m_scene.m_gfx_system.m_pipeline->block<BlockFilter>();
		filter.submit_quad(*render_pass.m_target, render_pass.m_index, render_pass.m_target->m_fbo, program.default_version(), { render_pass.m_viewport->m_rect });
	};

	gfx::manual_job(scene, PassType::Solid, draw_quad);

	if(Widget* dock = ui::dockitem(dockbar, "Game", { 1U }))
	{
		Section& edit = section(*dock, "Shader Editor");
		
		if(section_action(edit, "Reload"))
			program.reload();

		TextEdit& text_edit = ui::code_edit(*edit.m_body, source, 0);
		if(text_edit.m_changed)
		{
			program.m_sources[ShaderType::Fragment] = source.c_str();
			program.reload();
		}
		text_edit.m_changed = false;
		text_edit.m_language = &LanguageGLSL();
	}
}

#ifdef _09_LIVE_SHADER_EXE
void pump(Shell& app)
{
	shell_context(app.m_ui->begin(), app.m_editor);
	ex_09_live_shader(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(MUD_RESOURCE_PATH, exec_path(argc, argv));
	app.m_gfx_system.init_pipeline(pipeline_minimal);
	app.run(pump);
}
#endif

