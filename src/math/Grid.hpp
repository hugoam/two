//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Forward.h>
#include <math/Grid.h>

namespace mud
{
	inline GridDim::GridDim() {}
	inline GridDim::GridDim(int period, size_t limit, int increment, size_t modulo, size_t divide)
		: m_period(period), m_limit(limit), m_increment(increment), m_modulo(modulo), m_divide(divide)
	{}

	inline size_t GridDim::dim_index(size_t index) { return index % m_modulo / m_divide; }

	inline bool GridDim::has_neighbour(size_t index) { return dim_index(index) != m_limit; }
	inline size_t GridDim::neighbour_mod(size_t index) { return dim_index(index) == m_limit ? index + m_increment - m_period : index + m_increment; }
	inline size_t GridDim::neighbour(size_t index) { return index + m_increment; }

	template <class T>
	inline vector2d<T>::vector2d(size_t x, size_t y, size_t z)
		: vector<T>(x*y*z), m_x(x), m_y(y), m_z(z), m_sq(x*y)
	{
		this->reset_dims();
	}

	template <class T>
	inline vector2d<T>::vector2d(size_t x, size_t y, size_t z, const T& val)
		: vector<T>(x*y*z, val), m_x(x), m_y(y), m_z(z), m_sq(x*y)
	{
		this->reset_dims();
	}

	template <class T>
	inline vector2d<T>::vector2d(size_t s)
		: vector2d(s, s, s)
	{}

	template <class T>
	inline vector2d<T>::vector2d()
		: vector2d(0, 0, 0)
	{}

	template <class T>
	inline void vector2d<T>::reset_dims()
	{
		dim(SignedAxis::PlusX) = { int(m_x), m_x - 1, +1, m_x, 1 };
		dim(SignedAxis::MinusX) = { -int(m_x), 0, -1, m_x, 1 };
		dim(SignedAxis::PlusY) = { int(m_x*m_y), m_y - 1, +int(m_x), m_sq, m_x };
		dim(SignedAxis::MinusX) = { -int(m_x*m_y), 0, -int(m_x), m_sq, m_x };
		dim(SignedAxis::PlusZ) = { int(m_x*m_y*m_z), m_z - 1, +int(m_sq), SIZE_MAX, m_sq };
		dim(SignedAxis::MinusZ) = { -int(m_x*m_y*m_z), 0, -int(m_sq), SIZE_MAX, m_sq };
	}

	template <class T>
	inline void vector2d<T>::clear(T val)
	{
		for(size_t i = 0; i < this->size(); ++i)
			(*this)[i] = val;
	}

	template <class T>
	inline void vector2d<T>::reset(size_t x, size_t y, size_t z)
	{
		m_x = x; m_y = y; m_z = z; m_sq = x * y;
		this->reset_dims();
		this->resize(x*y*z);
	}

	template <class T>
	inline void vector2d<T>::reset(size_t x, size_t y, size_t z, T val)
	{
		reset(x, y, z);
		clear(val);
	}

	template <class T>
	inline bool vector2d<T>::border(size_t index, Side direction) { return !m_dims[size_t(direction)].has_neighbour(index); }

	template <class T>
	inline size_t vector2d<T>::neighbour_mod(size_t index, Side direction) { return m_dims[size_t(direction)].neighbour_mod(index); }

	template <class T>
	inline size_t vector2d<T>::neighbour(size_t index, Side direction) { return m_dims[size_t(direction)].neighbour(index); }

	template <class T>
	inline T& vector2d<T>::neighbour_item(size_t index, Side direction) { return at(neighbour(index, direction)); }

	template <class T>
	inline T* vector2d<T>::safe_neighbour(size_t index, Side direction) { if(!border(index, direction)) return &neighbour_item(index, direction); return nullptr; }

	template <class T>
	template <class Visitor>
	inline bool vector2d<T>::visit_near_dist(size_t x, size_t y, size_t z, size_t d, Visitor callback)
	{
		size_t x_min = x > d ? x - d : 0;
		size_t y_min = y > d ? y - d : 0;
		size_t x_max = x + d + 1 > m_x ? m_x : x + d + 1;
		size_t y_max = y + d + 1 > m_y ? m_y : y + d + 1;

		size_t dsquare = d * d;

		for(size_t i = x_min; i < x_max; ++i)
			for(size_t j = y_min; j < y_max; ++j)
				if(!(i == x && j == y))
					if((x - i)*(x - i) + (y - j)*(y - j) <= dsquare)
						if(!callback(this->at(i, j, z)))
							return false;
		return true;
	}

	template <class T>
	template <class Visitor>
	inline bool vector2d<T>::visit_near_2d(size_t x, size_t y, size_t z, size_t d, Visitor callback)
	{
		size_t x_min = x > d ? x - d : 0;
		size_t y_min = y > d ? y - d : 0;
		size_t x_max = x + d + 1 > m_x ? m_x : x + d + 1;
		size_t y_max = y + d + 1 > m_y ? m_y : y + d + 1;

		//size_t dsquare = d*d;
		//if(sq(x - i) + sq(y - j) > dsquare)
		//	continue;

		for(size_t i = x_min; i < x_max; ++i)
			for(size_t j = y_min; j < y_max; ++j)
				if(!(i == x && j == y))
					if(!callback(this->at(i, j, z)))
						return false;
		return true;
	}

	template <class T>
	template <class Visitor>
	inline bool vector2d<T>::visit_near(size_t x, size_t y, size_t z, size_t d, Visitor callback)
	{
		size_t x_min = x > d ? x - d : 0;
		size_t y_min = y > d ? y - d : 0;
		size_t z_min = z > d ? z - d : 0;
		size_t x_max = x + d + 1 > m_x ? m_x : x + d + 1;
		size_t y_max = y + d + 1 > m_y ? m_y : y + d + 1;
		size_t z_max = z + d + 1 > m_z ? m_z : z + d + 1;

		for(size_t i = x_min; i < x_max; ++i)
			for(size_t j = y_min; j < y_max; ++j)
				for(size_t k = z_min; k < z_max; ++k)
					if(!(i == x && j == y && k == z))
						if(!callback(this->at(i, j, k)))
							return false;
		return true;
	}

	template <class T>
	template <class Visitor>
	inline bool vector2d<T>::visit_near_dist(size_t index, size_t dist, Visitor callback)
	{
		return this->visit_near_dist(this->x(index), this->y(index), this->z(index), dist, callback);
	}

	template <class T>
	template <class Visitor>
	inline bool vector2d<T>::visit_near_2d(size_t index, size_t dist, Visitor callback)
	{
		return this->visit_near_2d(this->x(index), this->y(index), this->z(index), dist, callback);
	}

	template <class T>
	template <class Visitor>
	inline bool vector2d<T>::visit_near(size_t index, size_t dist, Visitor callback)
	{
		return this->visit_near(this->x(index), this->y(index), this->z(index), dist, callback);
	}

	template <class T>
	inline vector<T*> vector2d<T>::neighbours(size_t index, size_t dist)
	{
		vector<T*> result;
		this->visit_near(index, dist, [&](T& obj) { result.push_back(&obj); return true; });
		return result;
	}

	template <class T>
	inline vector<T*> vector2d<T>::neighbours_2d(size_t index, size_t dist)
	{
		vector<T*> result;
		this->visit_near_2d(index, dist, [&](T& obj) { result.push_back(&obj); return true; });
		return result;
	}

	template <class T>
	inline vector3d<T>::vector3d(size_t x, size_t y, size_t z)
		: vector<T>(x*y*z), m_x(x), m_y(y), m_z(z)
	{}

	template <class T>
	inline vector3d<T>::vector3d(size_t x, size_t y, size_t z, const T& val)
		: vector<T>(x*y*z, val), m_x(x), m_y(y), m_z(z)
	{}

	template <class T>
	inline vector3d<T>::vector3d(size_t s)
		: vector3d(s, s, s)
	{}

	template <class T>
	inline vector3d<T>::vector3d()
		: vector3d(0, 0, 0)
	{}

	template <class T>
	inline void vector3d<T>::clear(T val)
	{
		for(size_t i = 0; i < this->size(); ++i)
			(*this)[i] = val;
	}

	template <class T>
	inline void vector3d<T>::reset(size_t x, size_t y, size_t z)
	{
		m_x = x; m_y = y; m_z = z;
		this->resize(x*y*z);
	}

	template <class T>
	inline void vector3d<T>::reset(size_t x, size_t y, size_t z, T val)
	{
		reset(x, y, z);
		clear(val);
	}
}
