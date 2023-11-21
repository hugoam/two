module;
#include <infra/Cpp20.h>
#include <xx_three/ex.h>
#include <bgfx/bgfx.h>
module two.xxthree;

using namespace two;

// @author alteredq / http://alteredqualia.com/
// Convolution shader, ported from o3d sample to WebGL / GLSL
// http://o3d.googlecode.com/svn/trunk/samples/convolution.html

static string convolution_vertex =

	"$input a_position, a_texcoord0\n"
	"$output v_uv0\n"

	"#include <filter.sh>\n"

	"uniform vec4 u_bloom_blur_p0;\n"
	"#define u_increment u_bloom_blur_p0.xy\n"

	"void main() {\n"
		"v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;\n"
		"v_uv0 = v_uv0 - ((float(KERNEL_SIZE) - 1.0) / 2.0) * u_increment;\n"
		"gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));\n"
	"}\n";

static string convolution_fragment =

	"$input v_uv0\n"

	"#include <filter.sh>\n"

	//"uniform vec4 u_kernel[KERNEL_SIZE/4];\n"
	"uniform vec4 u_kernel[8];\n"

	"uniform vec4 u_bloom_blur_p0;\n"
	"#define u_increment u_bloom_blur_p0.xy\n"

	"void main()\n"
	"{\n"
		"vec2 uv = v_uv0;\n"
		"vec4 sum = vec4(0.0, 0.0, 0.0, 0.0);\n"

		"for(int i = 0; i < KERNEL_SIZE; i++)\n"
		"{\n"
			"sum += texture2D(s_source_0, uv) * u_kernel[i/4][i%4];\n"
			"uv += u_increment;\n"
		"}\n"

		"gl_FragColor = sum;\n"
	"}\n";


enum BlurOptions { KERNEL_SIZE };

Program& convolution_program(GfxSystem& gfx)
{
	static Program& program = gfx.programs().create("convolution");
	program.set_source(ShaderType::Vertex, convolution_vertex);
	program.set_source(ShaderType::Fragment, convolution_fragment);

	program.register_modes(0, { "KERNEL_SIZE" });
	return program;
}

vector<float> blur_kernel(float sigma)
{
	// We lop off the sqrt(2 * pi) * sigma term, since we're going to normalize anyway.

	auto gauss = [](float x, float sigma) { return exp(-sq(x) / (2.0 * sq(sigma))); };

	constexpr int kMaxKernelSize = 25;
	int kernelSize = 2.f * ceil(sigma * 3.f) + 1;

	if(kernelSize > kMaxKernelSize) kernelSize = kMaxKernelSize;
	float halfWidth = (kernelSize - 1) * 0.5;

	vector<float> values(kernelSize);
	float sum = 0.0;
	for(int i = 0; i < kernelSize; ++i)
	{
		values[i] = gauss(i - halfWidth, sigma);
		sum += values[i];
	}

	// normalize the kernel
	for(int i = 0; i < kernelSize; ++i) values[i] /= sum;

	return values;
}

#define PAD 0.f

void pass_bloom(GfxSystem& gfx, Render& render, Texture& source, FrameBuffer& fbo, bool clear, float strength, uint32_t kernel_size, float sigma, uvec2 resolution)
{
	static FrameBuffer targetX = { resolution, TextureFormat::RGBA8 };
	static FrameBuffer targetY = { resolution, TextureFormat::RGBA8 };

	CONSTEXPR vec2 blurX = vec2(0.001953125f, 0.0f);
	CONSTEXPR vec2 blurY = vec2(0.0f, 0.001953125f);

	static Program& convolution = convolution_program(gfx);

	constexpr uint32_t max_kernel = 8;
	vec4 kernel[max_kernel] = {};

	const vector<float> kernel_values = blur_kernel(sigma);
	const uint32_t num_values = uint32_t(kernel_values.size());
	for(size_t i = 0; i < kernel_values.size(); ++i)
	{
		kernel[i/4][i%4] = kernel_values[i];
	}

	ProgramVersion program = { convolution };
	program.set_mode(0, KERNEL_SIZE, min(num_values, kernel_size));

	auto blur_pass = [&](GfxSystem& gfx, Render& render, FrameBuffer& target, Texture& source, const ProgramVersion& program, const vec2& increment)
	{
		Pass pass = render.next_pass("bloom_blur", PassType::PostProcess);

		gfx.m_filter->uniforms4(pass, "u_kernel", kernel);

		gfx.m_filter->uniform(pass, "u_bloom_blur_p0", vec4(increment, PAD, PAD));
		gfx.m_filter->source0(source);
		//renderer.clear();

		gfx.m_filter->quad(pass, target, program);
	};

	blur_pass(gfx, render, targetX, source, program, blurX);
	blur_pass(gfx, render, targetY, targetX.m_tex, program, blurY);

	if(clear && strength != 1.f)
		pass_clear_fbo(gfx, render, fbo, Colour(0.f, 0.f));

	Pass merge = render.next_pass("bloom_merge", PassType::PostProcess);

	if(strength != 1.f)
	{
		gfx.m_filter->multiply(strength);
		gfx.m_copy->quad(merge, fbo, targetY.m_tex, BGFX_STATE_BLEND_ADD);
	}
	else
		gfx.m_copy->quad(merge, fbo, targetY.m_tex);
}

#undef PAD
