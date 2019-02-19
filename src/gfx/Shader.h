//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Forward.h>
#include <gfx/Program.h>
#include <stdint.h>

namespace mud
{
	enum ShaderOption : unsigned int
	{
		SKELETON,
		INSTANCING,
		BILLBOARD,
		QNORMALS,
		MRT,
		DEFERRED,
		CLUSTERED,
		BUFFER_ZONES,
		BUFFER_LIGHTS,
		BUFFER_MATERIALS,
	};

	export_ struct MUD_GFX_EXPORT ShaderVersion
	{
		ShaderVersion() {}
		ShaderVersion(const Program* program) : m_program(program) {}

		const Program* m_program = nullptr;
		uint32_t m_options = 0;
		uint8_t m_modes[4] = {};

		void clear() { m_options = 0; }

		inline void set(uint8_t option, bool active = true)
		{
			if(active)
				m_options |= (1 << option);
			else
				m_options &= ~(1 << option);
		}

		inline void set_option(uint8_t block, uint8_t option, bool active = true)
		{
			this->set(m_program->block_option_shift(block) + option, active);
		}

		inline void set_mode(uint8_t block, uint8_t mode, uint8_t value)
		{
			m_modes[m_program->block_mode_shift(block) + mode] = value;
		}

		uint32_t hash_modes() const { return (m_modes[0] << 0) + (m_modes[1] << 8) + (m_modes[2] << 16) + (m_modes[3] << 24); }
		uint64_t hash() const {	return uint64_t(m_options) + (uint64_t(hash_modes()) << 32); }
	};
}
