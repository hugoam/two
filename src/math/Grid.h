//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Generated/Forward.h>
#include <math/Vec.h>

#include <vector>
#include <functional>
#include <array>

namespace mud
{
	class Grid3
	{
	public:
		struct Dim
		{
		public:
			Dim(int period, size_t limit, int increment, size_t modulo, size_t divide)
				: m_period(period), m_limit(limit), m_increment(increment), m_modulo(modulo), m_divide(divide)
			{}

			size_t dimIndex(size_t index) { return index % m_modulo / m_divide; }

			bool hasNeighbour(size_t index) { return dimIndex(index) != m_limit; }
			size_t modNeighbour(size_t index) { return dimIndex(index) == m_limit ? index + m_increment - m_period : index + m_increment; }
			size_t neighbour(size_t index) { return index + m_increment; }

		protected:
			int m_period;
			size_t m_limit;
			int m_increment;
			size_t m_modulo;
			size_t m_divide;
		};
	};

	template <class T_Array>
	class Grided : public T_Array, public Grid3
	{
	public:
		typedef typename T_Array::value_type T;

	public:
		Grided(size_t x, size_t y, size_t z)
			: T_Array(x*y*z), m_x(x), m_y(y), m_z(z), m_sq(x*y)
			, m_dims(dims())
		{}

		Grided(size_t x, size_t y, size_t z, const T& val)
			: T_Array(x*y*z, val), m_x(x), m_y(y), m_z(z), m_sq(x*y)
			, m_dims(dims())
		{}

		Grided(size_t s)
			: Grided(s, s, s)
		{}

		Grided()
			: Grided(0, 0, 0)
		{}

		std::array<Dim, 6> dims()
		{
			Dim pos_x = { int(m_x), m_x - 1, +1, m_x, 1 };
			Dim neg_x = { -int(m_x), 0, -1, m_x, 1 };
			Dim pos_y = { int(m_x*m_y), m_y - 1, +int(m_x), m_sq, m_x };
			Dim neg_y = { -int(m_x*m_y), 0, -int(m_x), m_sq, m_x };
			Dim pos_z = { int(m_x*m_y*m_z), m_z - 1, +int(m_sq), SIZE_MAX, m_sq };
			Dim neg_z = { -int(m_x*m_y*m_z), 0, -int(m_sq), SIZE_MAX, m_sq };
			return { pos_x, neg_x, pos_y, neg_y, pos_z, neg_z };
		}

		void clear(T val)
		{
			for(size_t i = 0; i < this->size(); ++i)
				(*this)[i] = val;
		}

		void reset(size_t x, size_t y, size_t z)
		{
			m_x = x; m_y = y; m_z = z; m_sq = x*y;
			m_dims = dims();
			this->resize(x*y*z);
		}
		
		void reset(size_t x, size_t y, size_t z, T val)
		{
			reset(x, y, z);
			clear(val);
		}

		inline T& gridAt(size_t x, size_t y, size_t z = 0) { return T_Array::at(x + y*m_x + z*m_sq); }
		inline const T& gridAt(size_t x, size_t y, size_t z = 0) const { return T_Array::at(x + y*m_x + z*m_sq); }
		inline T* safeAt(size_t x, size_t y, size_t z) { if(x > m_x || y > m_y || z > m_z) return nullptr; else return &gridAt(x, y, z); }
		
		inline size_t indexAt(size_t x, size_t y, size_t z) { return x + y*m_x + z*m_sq; }

		inline size_t x(size_t index) { return index % m_x; }
		inline size_t y(size_t index) { return index % (m_x*m_y) / m_x; }
		inline size_t z(size_t index) { return index / (m_x*m_y); }

		bool border(size_t index, Side direction) { return !m_dims[size_t(direction)].hasNeighbour(index); }

		size_t neighbourMod(size_t index, Side direction) { return m_dims[size_t(direction)].modNeighbour(index); }
		size_t neighbour(size_t index, Side direction) { return m_dims[size_t(direction)].neighbour(index); }

		T& neighbourItem(size_t index, Side direction) { return T_Array::at(neighbour(index, direction)); }

		T* safeNeighbour(size_t index, Side direction) { if(!border(index, direction)) return &neighbourItem(index, direction); return nullptr; }

		template <class T_Visitor>
		bool iterateDistNeighbours(size_t x, size_t y, size_t z, size_t d, T_Visitor callback)
		{
			size_t xMin = x > d ? x - d : 0;
			size_t yMin = y > d ? y - d : 0;
			size_t xMax = x + d + 1 > m_x ? m_x : x + d + 1;
			size_t yMax = y + d + 1 > m_y ? m_y : y + d + 1;

			size_t dsquare = d * d;

			for(size_t i = xMin; i < xMax; ++i)
				for(size_t j = yMin; j < yMax; ++j)
					if(!(i == x && j == y))
						if((x - i)*(x - i) + (y - j)*(y - j) <= dsquare)
							if(!callback(this->gridAt(i, j, z)))
								return false;
			return true;
		}

		bool iterateFlatNeighbours(size_t x, size_t y, size_t z, size_t d, const std::function<bool(T&)>& callback)
		{
			size_t xMin = x > d ? x - d : 0;
			size_t yMin = y > d ? y - d : 0;
			size_t xMax = x + d + 1 > m_x ? m_x : x + d + 1;
			size_t yMax = y + d + 1 > m_y ? m_y : y + d + 1;

			//size_t dsquare = d*d;
			//if(sq(x - i) + sq(y - j) > dsquare)
			//	continue;

			for(size_t i = xMin; i < xMax; ++i)
				for(size_t j = yMin; j < yMax; ++j)
					if(!(i == x && j == y))
						if(!callback(this->gridAt(i, j, z)))
							return false;
			return true;
		}

		bool iterateNeighbours(size_t x, size_t y, size_t z, size_t d, const std::function<bool(T&)>& callback)
		{
			size_t xMin = x > d ? x - d : 0;
			size_t yMin = y > d ? y - d : 0;
			size_t zMin = z > d ? z - d : 0;
			size_t xMax = x + d + 1 > m_x ? m_x : x + d + 1;
			size_t yMax = y + d + 1 > m_y ? m_y : y + d + 1;
			size_t zMax = z + d + 1 > m_z ? m_z : z + d + 1;

			for(size_t i = xMin; i < xMax; ++i)
				for(size_t j = yMin; j < yMax; ++j)
					for(size_t k = zMin; k < zMax; ++k)
						if(!(i == x && j == y && k == z))
							if(!callback(this->gridAt(i, j, k)))
								return false;
			return true;
		}

		bool iterateDistNeighbours(size_t index, size_t dist, const std::function<bool(T&)>& callback)
		{
			return this->iterateDistNeighbours(this->x(index), this->y(index), this->z(index), dist, callback);
		}

		bool iterateFlatNeighbours(size_t index, size_t dist, const std::function<bool(T&)>& callback)
		{
			return this->iterateFlatNeighbours(this->x(index), this->y(index), this->z(index), dist, callback);
		}

		bool iterateNeighbours(size_t index, size_t dist, const std::function<bool(T&)>& callback)
		{
			return this->iterateNeighbours(this->x(index), this->y(index), this->z(index), dist, callback);
		}

		std::vector<T*> neighbours(size_t index, size_t dist)
		{
			std::vector<T*> result;
			this->iterateNeighbours(index, dist, [&](T& obj){ result.push_back(&obj); return true; });
			return result;
		}

		std::vector<T*> flatNeighbours(size_t index, size_t dist)
		{
			std::vector<T*> result;
			this->iterateFlatNeighbours(index, dist, [&](T& obj){ result.push_back(&obj); return true; });
			return result;
		}

	public:
		size_t m_x, m_y, m_z;
		size_t m_sq;

		//enum_array<Side, Dim> m_dims;
		std::array<Dim, 6> m_dims;
	};

	template <class T_Element>
	struct _refl_ _struct_ Grid : public Grided<std::vector<T_Element>>
	{
		using Grided<std::vector<T_Element>>::Grided;
	};


	template <class T_Element>
	struct _refl_ _struct_ array_3d : public std::vector<T_Element>
	{
	public:
		typedef T_Element T;

	public:
		array_3d(size_t x, size_t y, size_t z)
			: std::vector<T_Element>(x*y*z), m_x(x), m_y(y), m_z(z)
		{}

		array_3d(size_t x, size_t y, size_t z, const T& val)
			: std::vector<T_Element>(x*y*z, val), m_x(x), m_y(y), m_z(z)
		{}

		array_3d(size_t s)
			: array_3d(s, s, s)
		{}

		array_3d()
			: array_3d(0, 0, 0)
		{}

		void clear(T val)
		{
			for(size_t i = 0; i < this->size(); ++i)
				(*this)[i] = val;
		}

		void reset(size_t x, size_t y, size_t z)
		{
			m_x = x; m_y = y; m_z = z;
			this->resize(x*y*z);
		}

		void reset(size_t x, size_t y, size_t z, T val)
		{
			reset(x, y, z);
			clear(val);
		}

		inline T& at(size_t x, size_t y, size_t z = 0) { return std::vector<T_Element>::at(x + y*m_x + z*m_x*m_y); }
		inline const T& at(size_t x, size_t y, size_t z = 0) const { return std::vector<T_Element>::at(x + y*m_x + z*m_x*m_y); }
		inline T* safeAt(size_t x, size_t y, size_t z) { if(x > m_x || y > m_y || z > m_z) return nullptr; else return &at(x, y, z); }

		inline size_t indexAt(size_t x, size_t y, size_t z) { return x + y*m_x + z*m_x*m_y; }

		inline size_t x(size_t index) { return index % m_x; }
		inline size_t y(size_t index) { return index % (m_x*m_y) / m_x; }
		inline size_t z(size_t index) { return index / (m_x*m_y); }

	public:
		size_t m_x, m_y, m_z;
	};

	MUD_MATH_EXPORT _func_ void grid(uvec3 size, std::vector<uvec3>& output_coords);
	MUD_MATH_EXPORT _func_ void grid_center(uvec3 coord, float cell_size, vec3& output_center);
}
