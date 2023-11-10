
#include <xx_three/xx_three.h>

void pass_bloom(GfxSystem& gfx, Render& render, Texture& source, FrameBuffer& fbo, 
	            bool clear = true, float strength = 1.f, uint32_t kernel_size = 25, float sigma = 4.f, uvec2 resolution = uvec2(256U));