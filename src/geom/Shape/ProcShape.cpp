//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.geom;
#else
#include <math/Vec.hpp>
#include <geom/Types.h>
#include <geom/Shape/ProcShape.h>
#include <geom/Shape/DrawShape.h>
#include <geom/Shape/Line.h>
#include <geom/Shape/Circle.h>
#include <geom/Shape/Quad.h>
#include <geom/Shape/Triangle.h>
#include <geom/Shape/Cube.h>
#include <geom/Shape/Cylinder.h>
#include <geom/Shape/Sphere.h>
#include <geom/Shape/Spheroid.h>
#include <geom/Shape/Geom.h>
#include <geom/Primitive.hpp>
#include <geom/Shapes.h>
#include <geom/ShapesComplex.h>
#include <geom/Aabb.h>
#endif

namespace mud
{
	using Draw = DispatchDrawProcShape;

	ShapeSize symbol_line_size(const ProcShape& procshape)
	{
		const Shape& shape = *procshape.m_shape;
		if(Draw::me.m_size_lines.check(Ref(&shape)))
			return Draw::me.m_size_lines.dispatch(Ref(&shape), procshape);
		return { 0, 0 };
	}

	ShapeSize symbol_triangle_size(const ProcShape& procshape)
	{
		const Shape& shape = *procshape.m_shape;
		if(Draw::me.m_size_triangles.check(Ref(&shape)))
			return Draw::me.m_size_triangles.dispatch(Ref(&shape), procshape);
		return { 0, 0 };
	}

	void symbol_draw_lines(const ProcShape& procshape, MeshAdapter& writer)
	{
		const Shape& shape = *procshape.m_shape;
		if(Draw::me.m_draw_lines.check(Ref(&shape)))
			Draw::me.m_draw_lines.dispatch(Ref(&shape), procshape, writer);
	}

	void symbol_draw_triangles(const ProcShape& procshape, MeshAdapter& writer)
	{
		const Shape& shape = *procshape.m_shape;
		if(Draw::me.m_draw_triangles.check(Ref(&shape)))
			Draw::me.m_draw_triangles.dispatch(Ref(&shape), procshape, writer);
	}

	ShapeSize size_shape_lines(const ProcShape& procshape, const CompoundShape& compound)
	{
		UNUSED(procshape);
		ShapeSize result = { 0, 0 };
		for(auto& shape : compound.m_shapes)
			result.vec += symbol_line_size(shape).vec;
		return result;
	}

	void draw_shape_lines(const ProcShape& procshape, const CompoundShape& compound, MeshAdapter& writer)
	{
		UNUSED(procshape);
		for(auto& shape : compound.m_shapes)
		{
			symbol_draw_lines(shape, writer);
			writer.next();
		}
	}

	ShapeSize size_shape_triangles(const ProcShape& procshape, const CompoundShape& compound)
	{
		UNUSED(procshape);
		ShapeSize result = { 0, 0 };
		for(auto& shape : compound.m_shapes)
			result.vec += symbol_triangle_size(shape).vec;
		return result;
	}

	void draw_shape_triangles(const ProcShape& procshape, const CompoundShape& compound, MeshAdapter& writer)
	{
		UNUSED(procshape);
		for(auto& shape : compound.m_shapes)
		{
			symbol_draw_triangles(shape, writer);
			writer.next();
		}
	}

	DispatchDrawProcShape::DispatchDrawProcShape()
	{
		decl_shape<Line>(*this);
		decl_shape<ArcLine>(*this);
		decl_shape<Circle>(*this);
		decl_shape<Ellipsis>(*this);
		decl_shape<Grid2>(*this);
		decl_shape<Grid3>(*this);
		decl_shape<Quad>(*this);
		decl_shape<Rect>(*this);
		decl_shape<Triangle>(*this);

		decl_shape<Box>(*this);
		decl_shape<Cube>(*this);
		//declare_shape<Aabb>(*this);
		decl_shape<Cylinder>(*this);
		decl_shape<Sphere>(*this);
		decl_shape<Torus>(*this);
		decl_shape_triangles<TorusKnot>(*this);

		// polyhedrons
		decl_shape_triangles<Tetraedr>(*this);
		decl_shape_triangles<Icosaedr>(*this);

		decl_shape<Geometry>(*this);

		decl_compound_shape<Spheroid>(*this);
	}
}
