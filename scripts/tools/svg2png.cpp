// svg2png <out_dir> <size> <dark> <file.svg>...
// rasterizes each svg to a size x size png in out_dir
// with dark = 1, the neutral greys are inverted in lightness, like Visual Studio does for its dark themes, so that light theme icons read on a dark background

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

#define NANOSVG_IMPLEMENTATION
#include <nanosvg.h>
#define NANOSVGRAST_IMPLEMENTATION
#include <nanosvgrast.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

static void invert_greys(unsigned char* pixels, int count)
{
	for(int i = 0; i < count; ++i)
	{
		unsigned char* p = pixels + i * 4;
		if(p[3] == 0) continue;

		// nanosvg outputs straight alpha, so the colour can be transformed alone
		const float r = p[0] / 255.f, g = p[1] / 255.f, b = p[2] / 255.f;
		const float hi = std::max(r, std::max(g, b));
		const float lo = std::min(r, std::min(g, b));
		const float lightness = (hi + lo) * 0.5f;
		const float chroma = hi - lo;
		if(chroma > 0.15f) continue;

		// mirror the lightness, keeping the slight tint of the grey
		const float shift = (1.f - lightness) - lightness;
		p[0] = (unsigned char)std::clamp((r + shift) * 255.f + 0.5f, 0.f, 255.f);
		p[1] = (unsigned char)std::clamp((g + shift) * 255.f + 0.5f, 0.f, 255.f);
		p[2] = (unsigned char)std::clamp((b + shift) * 255.f + 0.5f, 0.f, 255.f);
	}
}

int main(int argc, char** argv)
{
	if(argc < 5)
	{
		fprintf(stderr, "usage: svg2png <out_dir> <size> <dark> <file.svg>...\n");
		return 1;
	}

	const std::string out_dir = argv[1];
	const int size = atoi(argv[2]);
	const bool dark = atoi(argv[3]) != 0;

	NSVGrasterizer* rasterizer = nsvgCreateRasterizer();
	std::vector<unsigned char> pixels(size * size * 4);

	int failed = 0;
	for(int i = 4; i < argc; ++i)
	{
		const std::string path = argv[i];
		NSVGimage* image = nsvgParseFromFile(path.c_str(), "px", 96.f);
		if(!image || image->width <= 0.f)
		{
			fprintf(stderr, "failed to parse %s\n", path.c_str());
			++failed;
			continue;
		}

		const float scale = size / std::max(image->width, image->height);
		std::fill(pixels.begin(), pixels.end(), 0);
		nsvgRasterize(rasterizer, image, 0.f, 0.f, scale, pixels.data(), size, size, size * 4);
		nsvgDelete(image);

		if(dark)
			invert_greys(pixels.data(), size * size);

		std::string name = path.substr(path.find_last_of("/\\") + 1);
		name = name.substr(0, name.rfind(".svg"));
		const std::string out = out_dir + "/" + name + ".png";
		if(!stbi_write_png(out.c_str(), size, size, 4, pixels.data(), size * 4))
		{
			fprintf(stderr, "failed to write %s\n", out.c_str());
			++failed;
		}
	}

	nsvgDeleteRasterizer(rasterizer);
	return failed;
}
