//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <08_sky/08_sky.h>
#include <01_shapes/01_shapes.h>
#include <03_materials/03_materials.h>

#include <stl/vector.hpp>

#include <map>

#include <bx/math.h>

using namespace mud;

// Represents color. Color-space depends on context.
// In the code below, used to represent color in XYZ, and RGB color-space
using Color = bx::Vec3;

// Performs piecewise linear interpolation of a Color parameter.
class DynamicValueController
{
	typedef Color ValueType;
	typedef std::map<float, ValueType> KeyMap;
public:
	DynamicValueController() {}
	~DynamicValueController() {}

	void SetMap(const KeyMap& keymap);
	ValueType GetValue(float time) const;
	void clear();

private:
	const ValueType interpolate(float lowerTime, const ValueType& lowerVal, float upperTime, const ValueType& upperVal, float time) const;

	KeyMap	m_keyMap;
};

// Controls sun position according to time, month, and observer's latitude.
// Sun position computation based on Earth's orbital elements: https://nssdc.gsfc.nasa.gov/planetary/factsheet/earthfact.html
export_ class MUD_GFX_EXPORT SunController
{
public:
	SunController() {}

	void Update(float time);

	vec3 m_north_direction = { 0.f, 0.f, -1.f }; //-Z3; // @kludge somehow meta generator doesn't like this ?
	quat m_sun_rotation = ZeroQuat;
	vec3 m_sun_direction = vec3(0.f);
	vec3 m_up = Y3;
	float m_latitude = 50.f;
	Month m_month = Month::June;

	float m_ecliptic_obliquity = 0.408407f; //bx::toRad(23.4f);
	float m_delta = 0.0f;
};
// Renders a screen-space grid of triangles.
// Because of performance reasons, and because sky color is smooth, sky color is computed in vertex shader.
// 32x32 is a reasonable size for the grid to have smooth enough colors.
export_ struct MUD_GFX_EXPORT ProceduralSky
{
	void init(GfxSystem& gfx, ivec2 vertex_count);
	void shutdown();
	void submit(Render& render, Pass& render_pass);

	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle m_ibh;

	bgfx::ProgramHandle m_program;
	bgfx::ProgramHandle m_program_colorBandingFix;

	bool m_preventBanding;
};

export_ struct MUD_GFX_EXPORT PerezSky
{
	struct SkyUniform
	{
		void createUniforms()
		{
			u_sun_luminance = bgfx::createUniform("u_sun_luminance", bgfx::UniformType::Vec4);
			u_sky_luminance_xyz = bgfx::createUniform("u_sky_luminance_xyz", bgfx::UniformType::Vec4);
			u_sky_luminance = bgfx::createUniform("u_sky_luminance", bgfx::UniformType::Vec4);
			u_sun_direction = bgfx::createUniform("u_sun_direction", bgfx::UniformType::Vec4);
			u_sky_params = bgfx::createUniform("u_sky_params", bgfx::UniformType::Vec4);
			u_perez_coeff = bgfx::createUniform("u_perez_coeff", bgfx::UniformType::Vec4, 5);
		}

		bgfx::UniformHandle u_sun_luminance;
		bgfx::UniformHandle u_sky_luminance_xyz;
		bgfx::UniformHandle u_sky_luminance;
		bgfx::UniformHandle u_sun_direction;
		bgfx::UniformHandle u_sky_params;
		bgfx::UniformHandle u_perez_coeff;

	} u_uniform;

	ProceduralSky m_sky;
	SunController m_sun;

	DynamicValueController m_sun_luminance_xyz;
	DynamicValueController m_sky_luminance_xyz;

	float m_time = 0.0f;
	float m_time_scale = 1.0f;

	float m_turbidity = 2.15f;

	bool m_initialized = false;

	void init(GfxSystem& gfx);
	void render(Render& render);
};

#include <map>

// HDTV rec. 709 matrix.
static float M_XYZ2RGB[] =
{
	3.240479f, -0.969256f, 0.055648f,
	-1.53715f, 1.875991f, -0.204043f,
	-0.49853f, 0.041556f, 1.057311f
};


// Converts color repesentation from CIE XYZ to RGB color-space.
Color XYZToRGB(const Color& xyz)
{
	Color rgb;
	rgb.x = M_XYZ2RGB[0] * xyz.x + M_XYZ2RGB[3] * xyz.y + M_XYZ2RGB[6] * xyz.z;
	rgb.y = M_XYZ2RGB[1] * xyz.x + M_XYZ2RGB[4] * xyz.y + M_XYZ2RGB[7] * xyz.z;
	rgb.z = M_XYZ2RGB[2] * xyz.x + M_XYZ2RGB[5] * xyz.y + M_XYZ2RGB[8] * xyz.z;
	return rgb;
};


// Precomputed luminance of sunlight in XYZ colorspace.
// Computed using code from Game Engine Gems, Volume One, chapter 15. Implementation based on Dr. Richard Bird model.
// This table is used for piecewise linear interpolation. Transitions from and to 0.0 at sunset and sunrise are highly inaccurate
static std::map<float, Color> sunLuminanceXYZTable = {
	{ 5.0f, { 0.000000f, 0.000000f, 0.000000f } },
	{ 7.0f, { 12.703322f, 12.989393f, 9.100411f } },
	{ 8.0f, { 13.202644f, 13.597814f, 11.524929f } },
	{ 9.0f, { 13.192974f, 13.597458f, 12.264488f } },
	{ 10.0f, { 13.132943f, 13.535914f, 12.560032f } },
	{ 11.0f, { 13.088722f, 13.489535f, 12.692996f } },
	{ 12.0f, { 13.067827f, 13.467483f, 12.745179f } },
	{ 13.0f, { 13.069653f, 13.469413f, 12.740822f } },
	{ 14.0f, { 13.094319f, 13.495428f, 12.678066f } },
	{ 15.0f, { 13.142133f, 13.545483f, 12.526785f } },
	{ 16.0f, { 13.201734f, 13.606017f, 12.188001f } },
	{ 17.0f, { 13.182774f, 13.572725f, 11.311157f } },
	{ 18.0f, { 12.448635f, 12.672520f, 8.267771f } },
	{ 20.0f, { 0.000000f, 0.000000f, 0.000000f } }
};


// Precomputed luminance of sky in the zenith point in XYZ colorspace.
// Computed using code from Game Engine Gems, Volume One, chapter 15. Implementation based on Dr. Richard Bird model.
// This table is used for piecewise linear interpolation. Day/night transitions are highly inaccurate.
// The scale of luminance change in Day/night transitions is not preserved.
// Luminance at night was increased to eliminate need the of HDR render.
static std::map<float, Color> skyLuminanceXYZTable = {
	{ 0.0f, { 0.308f, 0.308f, 0.411f } },
	{ 1.0f, { 0.308f, 0.308f, 0.410f } },
	{ 2.0f, { 0.301f, 0.301f, 0.402f } },
	{ 3.0f, { 0.287f, 0.287f, 0.382f } },
	{ 4.0f, { 0.258f, 0.258f, 0.344f } },
	{ 5.0f, { 0.258f, 0.258f, 0.344f } },
	{ 7.0f, { 0.962851f, 1.000000f, 1.747835f } },
	{ 8.0f, { 0.967787f, 1.000000f, 1.776762f } },
	{ 9.0f, { 0.970173f, 1.000000f, 1.788413f } },
	{ 10.0f, { 0.971431f, 1.000000f, 1.794102f } },
	{ 11.0f, { 0.972099f, 1.000000f, 1.797096f } },
	{ 12.0f, { 0.972385f, 1.000000f, 1.798389f } },
	{ 13.0f, { 0.972361f, 1.000000f, 1.798278f } },
	{ 14.0f, { 0.972020f, 1.000000f, 1.796740f } },
	{ 15.0f, { 0.971275f, 1.000000f, 1.793407f } },
	{ 16.0f, { 0.969885f, 1.000000f, 1.787078f } },
	{ 17.0f, { 0.967216f, 1.000000f, 1.773758f } },
	{ 18.0f, { 0.961668f, 1.000000f, 1.739891f } },
	{ 20.0f, { 0.264f, 0.264f, 0.352f } },
	{ 21.0f, { 0.264f, 0.264f, 0.352f } },
	{ 22.0f, { 0.290f, 0.290f, 0.386f } },
	{ 23.0f, { 0.303f, 0.303f, 0.404f } }
};


// Turbidity tables. Taken from:
// A. J. Preetham, P. Shirley, and B. Smits. A Practical Analytic Model for Daylight. SIGGRAPH ’99
// Coefficients correspond to xyY colorspace.
static Color ABCDE[] =
{
	{ -0.2592f, -0.2608f, -1.4630f },
	{ 0.0008f,  0.0092f,  0.4275f },
	{ 0.2125f,  0.2102f,  5.3251f },
	{ -0.8989f, -1.6537f, -2.5771f },
	{ 0.0452f,  0.0529f,  0.3703f }
};
static Color ABCDE_t[] =
{
	{ -0.0193f, -0.0167f,  0.1787f },
	{ -0.0665f, -0.0950f, -0.3554f },
	{ -0.0004f, -0.0079f, -0.0227f },
	{ -0.0641f, -0.0441f,  0.1206f },
	{ -0.0033f, -0.0109f, -0.0670f }
};

void DynamicValueController::SetMap(const KeyMap& keymap)
{
	m_keyMap = keymap;
}

DynamicValueController::ValueType DynamicValueController::GetValue(float time) const
{
	typename KeyMap::const_iterator itUpper = m_keyMap.upper_bound(time + 1e-6f);
	typename KeyMap::const_iterator itLower = itUpper;
	--itLower;
	if(itLower == m_keyMap.end())
	{
		return itUpper->second;
	}
	if(itUpper == m_keyMap.end())
	{
		return itLower->second;
	}
	float lowerTime = itLower->first;
	const ValueType& lowerVal = itLower->second;
	float upperTime = itUpper->first;
	const ValueType& upperVal = itUpper->second;
	if(lowerTime == upperTime)
	{
		return lowerVal;
	}
	return interpolate(lowerTime, lowerVal, upperTime, upperVal, time);
}

void DynamicValueController::clear()
{
	m_keyMap.clear();
}

const DynamicValueController::ValueType DynamicValueController::interpolate(float lowerTime, const ValueType& lowerVal, float upperTime, const ValueType& upperVal, float time) const
{
	float x = (time - lowerTime) / (upperTime - lowerTime);
	ValueType result = bx::lerp(lowerVal, upperVal, x);
	return result;
}

void SunController::Update(float time)
{
	m_sun_rotation = sun_rotation(m_month, m_latitude, time - 12.0f, m_ecliptic_obliquity);
	m_sun_direction = m_sun_rotation * -m_north_direction;
}

struct ScreenPosVertex
{
	float m_x;
	float m_y;

	static void init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
			.end();
	}

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl ScreenPosVertex::ms_decl;

void ProceduralSky::init(GfxSystem& gfx, ivec2 vertex_count)
{
	// Create vertex stream declaration.
	ScreenPosVertex::init();

	m_program = gfx.programs().create("sky").default_version();
	//m_program_colorBandingFix = gfx.get_program("sky_color_banding_fix").default_version();

	m_preventBanding = false;

	vector<ScreenPosVertex> vertices = vector<ScreenPosVertex>(vertex_count.y * vertex_count.x);

	for(int i = 0; i < vertex_count.y; i++)
	{
		for(int j = 0; j < vertex_count.x; j++)
		{
			ScreenPosVertex& v = vertices[i * vertex_count.y + j];
			v.m_x = float(j) / (vertex_count.x - 1) * 2.0f - 1.0f;
			v.m_y = float(i) / (vertex_count.y - 1) * 2.0f - 1.0f;
		}
	}

	vector<uint16_t> indices = vector<uint16_t>((vertex_count.y - 1) * (vertex_count.x - 1) * 6);

	int k = 0;
	for(int i = 0; i < vertex_count.y - 1; i++)
	{
		for(int j = 0; j < vertex_count.x - 1; j++)
		{
			indices[k++] = (uint16_t)(j + 0 + vertex_count.x * (i + 0));
			indices[k++] = (uint16_t)(j + 1 + vertex_count.x * (i + 0));
			indices[k++] = (uint16_t)(j + 0 + vertex_count.x * (i + 1));

			indices[k++] = (uint16_t)(j + 1 + vertex_count.x * (i + 0));
			indices[k++] = (uint16_t)(j + 1 + vertex_count.x * (i + 1));
			indices[k++] = (uint16_t)(j + 0 + vertex_count.x * (i + 1));
		}
	}

	m_vbh = bgfx::createVertexBuffer(bgfx::copy(vertices.data() , sizeof(ScreenPosVertex) * vertex_count.y * vertex_count.x), ScreenPosVertex::ms_decl);
	m_ibh = bgfx::createIndexBuffer(bgfx::copy(indices.data(), sizeof(uint16_t) * k));
}

void ProceduralSky::shutdown()
{
	bgfx::destroy(m_ibh);
	bgfx::destroy(m_vbh);
	bgfx::destroy(m_program);
	bgfx::destroy(m_program_colorBandingFix);
}

void ProceduralSky::submit(Render& render, Pass& render_pass)
{
	UNUSED(render);
	bgfx::Encoder& encoder = *render_pass.m_encoder;

	encoder.setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_DEPTH_TEST_LEQUAL);
	encoder.setIndexBuffer(m_ibh);
	encoder.setVertexBuffer(0, m_vbh);

	encoder.submit(render_pass.m_index, m_preventBanding ? m_program_colorBandingFix : m_program);
}

void PerezSky::init(GfxSystem& gfx)
{
	m_sun_luminance_xyz.SetMap(sunLuminanceXYZTable);
	m_sky_luminance_xyz.SetMap(skyLuminanceXYZTable);

	u_uniform.createUniforms();

	m_sky.init(gfx, { 32, 32 });

	m_sun.Update(0);

	m_initialized = true;
}

void compute_perez_coeff(float turbidity, float* outPerezCoeff)
{
	const bx::Vec3 turbidity3 = { turbidity, turbidity, turbidity };
	for(uint32_t ii = 0; ii < 5; ++ii)
	{
		const bx::Vec3 tmp = bx::mad(ABCDE_t[ii], turbidity3, ABCDE[ii]);
		float* out = outPerezCoeff + 4 * ii;
		bx::store(out, tmp);
		out[3] = 0.0f;
	}
}

void PerezSky::render(Render& render)
{
	Pass sky_pass = render.next_pass("sky", PassType::Background);
	bgfx::Encoder& encoder = *sky_pass.m_encoder;

	m_time += m_time_scale * render.m_frame.m_delta_time;
	m_time = bx::mod(m_time, 24.0f);
	m_sun.Update(m_time);

	Color sun_luminance_xyz = m_sun_luminance_xyz.GetValue(m_time);
	Color sun_luminance_rgb = XYZToRGB(sun_luminance_xyz);

	Color sky_luminance_xyz = m_sky_luminance_xyz.GetValue(m_time);
	Color sky_luminance_rgb = XYZToRGB(sky_luminance_xyz);

	encoder.setUniform(u_uniform.u_sun_luminance, &sun_luminance_rgb);
	encoder.setUniform(u_uniform.u_sky_luminance_xyz, &sky_luminance_xyz);
	encoder.setUniform(u_uniform.u_sky_luminance, &sky_luminance_rgb);

	encoder.setUniform(u_uniform.u_sun_direction, &m_sun.m_sun_direction);

	float exposition[4] = { 0.02f, 3.0f, 0.1f, m_time };
	encoder.setUniform(u_uniform.u_sky_params, exposition);

	float perez_coeff[4 * 5];
	compute_perez_coeff(m_turbidity, perez_coeff);
	encoder.setUniform(u_uniform.u_perez_coeff, perez_coeff, 5);

	m_sky.submit(render, sky_pass);
}

#if 0
static void generator_script(VisualScript& script)
{
	using Var = Valve;

	script.lock();

	Var& origin = script.getInput("origin");
	Var& height = script.function(noise).plug({});

	Var& sectors = script.function(sector_grid).plug({});
	Var& blocks = script.function(block_grid).plug({});

	script.unlock();
}
#endif

void example_options(Widget& parent, PerezSky& sky)
{
	//Widget& body = *ui::window(parent, "Procedural Sky").m_body;
	//Widget& body = ui::columns(parent, {});
	Widget& body = ui::table(parent, { "field", "value" }, {});
	ui::slider_field<float>(body, "Time scale", { sky.m_time_scale, { 0.0f, 1.0f, 0.01f } });
	ui::slider_field<float>(body, "Time", { sky.m_time, { 0.0f, 24.0f } });
	ui::slider_field<float>(body, "Latitude", { sky.m_sun.m_latitude, { -90.0f, 90.0f } });
	ui::slider_field<float>(body, "Turbidity", { sky.m_turbidity, { 1.9f, 10.0f, 0.1f } });
	ui::input_field<bool>(body, "Prevent color banding", sky.m_sky.m_preventBanding);

	static cstring months[12] =
	{
		"January",
		"February",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December"
	};

	ui::dropdown_field(body, "Month", { months, 12 }, (uint32_t&)sky.m_sun.m_month);
}

static PerezSky g_sky;

void ex_08_sky(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(app);
	if(!g_sky.m_initialized)
		g_sky.init(app.m_gfx);

	//app.m_gfx->m_renderer.block<BlockTonemap>()->m_enabled = false;

	SceneViewer& viewer = ui::scene_viewer(parent);
	//viewer.m_viewport.m_lighting = Lighting::VoxelGI;

	ui::orbit_controller(viewer);

	if(Widget* dock = ui::dockitem(dockbar, "Game", { 1U }))
		example_options(*dock, g_sky);

	Gnode& scene = viewer.m_scene.begin();

	Material& material = milky_white(app.m_gfx);

	Gnode& ground_node = gfx::node(scene, {}, { 0.f, -5.f, 0.f });
	gfx::shape(ground_node, Rect(vec2(-50.f), vec2(100.f)), Symbol(), 0U, &material);

	gfx::direct_light_node(scene, g_sky.m_sun.m_sun_rotation);
	gfx::radiance(scene, "radiance/tiber_1_1k.hdr", BackgroundMode::None);
	//gfx::gi_probe(scene, 512, vec3(50.f));

	static vector<ShapeVar> shapes = { Cube(1.f), Sphere(), Cylinder() }; // @todo Circle() looks weird
	static vector<ShapeInstance> shape_items = create_shape_grid(10U, 10U, shapes);
	static Symbol symbol;

	shape_grid(scene, { shape_items.data(), 10U, 10U }, &symbol, true, &material);

	gfx::custom_sky(scene, [](Render& render) { g_sky.render(render); });
}

#ifdef _08_SKY_EXE
void pump(Shell& app)
{
	shell_context(app.m_ui->begin(), app.m_editor);
	ex_08_sky(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(MUD_RESOURCE_PATH, exec_path(argc, argv));
	app.m_gfx.init_pipeline(pipeline_pbr);
	app.run(pump);
}
#endif
