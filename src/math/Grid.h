//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stdint.h>
#include <stl/vector.h>
#include <infra/EnumArray.h>
#include <math/Forward.h>
#include <math/Vec.h>
#include <math/Axis.h>

namespace mud
{
	struct GridDim
	{
	public:
		GridDim();
		GridDim(int period, size_t limit, int increment, size_t modulo, size_t divide);

		size_t dim_index(size_t index);

		bool has_neighbour(size_t index);
		size_t neighbour_mod(size_t index);
		size_t neighbour(size_t index);

	protected:
		int m_period;
		size_t m_limit;
		int m_increment;
		size_t m_modulo;
		size_t m_divide;
	};

	export_ template <class T>
	class refl_ struct_ vector2d : public vector<T>
	{
	public:
		vector2d(size_t x, size_t y, size_t z);
		vector2d(size_t x, size_t y, size_t z, const T& val);
		vector2d(size_t s);
		vector2d();

		GridDim& dim(SignedAxis axis) { return m_dims[Side(axis)]; }

		void reset_dims();

		void clear(T val);

		void reset(size_t x, size_t y, size_t z);
		void reset(size_t x, size_t y, size_t z, T val);

		inline T& at(size_t i) { return vector<T>::operator[](i); }
		inline const T& at(size_t i) const { return vector<T>::operator[](i); }

		inline T& at(size_t x, size_t y, size_t z = 0) { return at(x + y * m_x + z * m_sq); }
		inline const T& at(size_t x, size_t y, size_t z = 0) const { return at(x + y * m_x + z * m_sq); }

		inline T* safe_at(size_t x, size_t y, size_t z) { if(x > m_x || y > m_y || z > m_z) return nullptr; else return &at(x, y, z); }

		inline size_t index_at(size_t x, size_t y, size_t z) { return x + y * m_x + z * m_sq; }

		inline size_t x(size_t index) { return index % m_x; }
		inline size_t y(size_t index) { return index % (m_x*m_y) / m_x; }
		inline size_t z(size_t index) { return index / (m_x*m_y); }

		bool border(size_t index, Side direction);

		size_t neighbour_mod(size_t index, Side direction);
		size_t neighbour(size_t index, Side direction);

		T& neighbour_item(size_t index, Side direction);
		T* safe_neighbour(size_t index, Side direction);

		template <class Visitor>
		bool visit_near_dist(size_t x, size_t y, size_t z, size_t d, Visitor callback);

		template <class Visitor>
		bool visit_near_2d(size_t x, size_t y, size_t z, size_t d, Visitor callback);

		template <class Visitor>
		bool visit_near(size_t x, size_t y, size_t z, size_t d, Visitor callback);

		template <class Visitor>
		bool visit_near_dist(size_t index, size_t dist, Visitor callback);

		template <class Visitor>
		bool visit_near_2d(size_t index, size_t dist, Visitor callback);

		template <class Visitor>
		bool visit_near(size_t index, size_t dist, Visitor callback);

		vector<T*> neighbours(size_t index, size_t dist);

		vector<T*> neighbours_2d(size_t index, size_t dist);

	public:
		size_t m_x, m_y, m_z;
		size_t m_sq;

		enum_array<Side, GridDim> m_dims = {};
		//GridDim m_dims[6] = {};
	};

	export_ template <class T>
	struct refl_ struct_ vector3d : public vector<T>
	{
	public:
		vector3d(size_t x, size_t y, size_t z);
		vector3d(size_t x, size_t y, size_t z, const T& val);
		vector3d(size_t s);
		vector3d();

		void clear(T val);

		void reset(size_t x, size_t y, size_t z);
		void reset(size_t x, size_t y, size_t z, T val);

		inline T& at(size_t x, size_t y, size_t z = 0) { return vector<T>::operator[](x + y * m_x + z * m_x*m_y); }
		inline const T& at(size_t x, size_t y, size_t z = 0) const { return vector<T>::operator[](x + y * m_x + z * m_x*m_y); }
		inline T* safeAt(size_t x, size_t y, size_t z) { if(x > m_x || y > m_y || z > m_z) return nullptr; else return &at(x, y, z); }

		inline size_t indexAt(size_t x, size_t y, size_t z) { return x + y * m_x + z * m_x*m_y; }

		inline size_t x(size_t index) { return index % m_x; }
		inline size_t y(size_t index) { return index % (m_x*m_y) / m_x; }
		inline size_t z(size_t index) { return index / (m_x*m_y); }

	public:
		size_t m_x, m_y, m_z;
	};

	export_ MUD_MATH_EXPORT func_ void grid(const uvec3& size, vector<uvec3>& output_coords);
	export_ MUD_MATH_EXPORT func_ vec3 grid_center(const uvec3& coord, const vec3& cell_size);

	export_ MUD_MATH_EXPORT func_ void index_list(uint32_t size, vector<uint32_t>& output_indices);
}
