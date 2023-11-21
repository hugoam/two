//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Forward.h>
#include <gfx/Program.h>

namespace two
{
	enum ShaderOption : unsigned int
	{
		INSTANCING,
		BILLBOARD,
		SKELETON,
		MORPHTARGET,
		QNORMALS,
		VFLIP,
		MRT,
		DEFERRED,
		CLUSTERED,
		BUFFER_ZONES,
		BUFFER_LIGHTS,
		BUFFER_MATERIALS,
	};

	export_ struct refl_ TWO_GFX_EXPORT ProgramVersion
	{
		constr_ ProgramVersion() {}
		constr_ ProgramVersion(const Program& program) : m_program(&program) {}
		//constr_ explicit ProgramVersion(const Program& program) : m_program(&program) {}

		const Program* m_program = nullptr;
		uint32_t m_options = 0;
		uint8_t m_modes[4] = {};

		bgfx::ProgramHandle fetch() const { return const_cast<Program*>(m_program)->version(*this); }

		meth_ void clear() { m_options = 0; }

		inline void set(uint8_t option, bool active = true)
		{
			assert(option < 32);
			if(active) m_options |= (1 << option);
			else       m_options &= ~(1 << option);
		}

		meth_ inline void set_option(uint8_t block, uint8_t option, bool active = true)
		{
			assert(m_program->m_shader_blocks[block].m_enabled);
			const uint8_t block_shift = m_program->m_shader_blocks[block].m_option_shift;
			this->set(block_shift + option, active);
		}

		meth_ inline void set_mode(uint8_t block, uint8_t mode, uint8_t value)
		{
			assert(m_program->m_shader_blocks[block].m_enabled);
			const uint8_t mode_shift = m_program->m_shader_blocks[block].m_mode_shift;
			m_modes[mode_shift + mode] = value;
		}

		uint32_t hash_modes() const { return (m_modes[0] << 0) + (m_modes[1] << 8) + (m_modes[2] << 16) + (m_modes[3] << 24); }
		meth_ uint64_t hash() const { return uint64_t(m_options) + (uint64_t(hash_modes()) << 32); }
	};
}
