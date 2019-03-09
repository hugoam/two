//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <infra/Global.h>
#include <type/Dispatch.h>
#include <type/DispatchDecl.h>
#endif
#include <geom/Forward.h>
#include <geom/Shape/ProcShape.h>
#include <geom/Shape/CompoundShape.h>

namespace mud
{
	export_ struct MUD_GEOM_EXPORT DispatchDrawProcShape : public Global<DispatchDrawProcShape>
	{
		DispatchDrawProcShape();

		Dispatch<void, ProcShape&> m_compound_shape;
		Dispatch<ShapeSize, const ProcShape&> m_size_lines;
		Dispatch<ShapeSize, const ProcShape&> m_size_triangles;
		Dispatch<void, const ProcShape&, MeshAdapter&> m_draw_lines;
		Dispatch<void, const ProcShape&, MeshAdapter&> m_draw_triangles;
	};

	template <class T_Shape>
	inline void decl_shape_lines(DispatchDrawProcShape& dispatch)
	{
		dispatch_branch<T_Shape>(dispatch.m_size_lines, +[](T_Shape& shape, const ProcShape& procshape) { return size_shape_lines(procshape, shape); });
		dispatch_branch<T_Shape>(dispatch.m_draw_lines, +[](T_Shape& shape, const ProcShape& procshape, MeshAdapter& writer) { draw_shape_lines(procshape, shape, writer); });
	}

	template <class T_Shape>
	inline void decl_shape_triangles(DispatchDrawProcShape& dispatch)
	{
		dispatch_branch<T_Shape>(dispatch.m_size_triangles, +[](T_Shape& shape, const ProcShape& procshape) { return size_shape_triangles(procshape, shape); });
		dispatch_branch<T_Shape>(dispatch.m_draw_triangles, +[](T_Shape& shape, const ProcShape& procshape, MeshAdapter& writer) { draw_shape_triangles(procshape, shape, writer); });
	}

	template <class T_Shape>
	inline void decl_shape(DispatchDrawProcShape& dispatch)
	{
		decl_shape_lines<T_Shape>(dispatch);
		decl_shape_triangles<T_Shape>(dispatch);
	}

	template <class T_Shape>
	inline void decl_compound_shape(DispatchDrawProcShape& dispatch)
	{
		dispatch_branch<T_Shape>(dispatch.m_size_lines, +[](T_Shape& shape, const ProcShape& procshape) { CompoundShape compound = shape_compound(procshape, shape); return size_shape_lines(procshape, compound); });
		dispatch_branch<T_Shape>(dispatch.m_draw_lines, +[](T_Shape& shape, const ProcShape& procshape, MeshAdapter& writer) { CompoundShape compound = shape_compound(procshape, shape); draw_shape_lines(procshape, compound, writer); });

		dispatch_branch<T_Shape>(dispatch.m_size_triangles, +[](T_Shape& shape, const ProcShape& procshape) { CompoundShape compound = shape_compound(procshape, shape); return size_shape_triangles(procshape, compound); });
		dispatch_branch<T_Shape>(dispatch.m_draw_triangles, +[](T_Shape& shape, const ProcShape& procshape, MeshAdapter& writer) { CompoundShape compound = shape_compound(procshape, shape); draw_shape_triangles(procshape, compound, writer); });
	}
}
