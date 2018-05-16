//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifdef MUD_META_GENERATOR
namespace bx
{
	struct FileReaderI {};
	class FileReader {};
	class FileWriter {};
	struct AllocatorI {};
	class DefaultAllocator {};
	struct RngMwc {};
}

namespace bimg
{
	struct ImageContainer {};
	struct Orientation { struct Enum {}; };
}
namespace bgfx
{
#define BGFX_INVALID_HANDLE {}
#define BGFX_TEXTURE_NONE {}
	struct UniformHandle {};
	struct UniformType { struct Enum {}; };
	struct TextureHandle {};
	struct TextureInfo {};
	struct TextureFormat { struct Enum {}; };
	struct VertexBufferHandle {};
	struct IndexBufferHandle {};
	struct InstanceDataBuffer {};
	struct ProgramHandle {};
	struct FrameBufferHandle {};
	struct Memory {};
	struct VertexDecl {};

	struct Aabb {};
}
#endif
