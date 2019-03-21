//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.geom;
#else
#include <stl/array.h>
#include <math/Vec.hpp>
#include <geom/Shape/Cube.h>
#include <geom/Shapes.h>
#include <geom/ShapesComplex.h>
#include <geom/Primitive.hpp>
#include <geom/Shape/Quad.h>
#endif

#include <stl/vector.hpp>

namespace mud
{
	ShapeSize size_cube_corners_lines(const ProcShape& shape, const Box& box)
	{
		UNUSED(shape); UNUSED(box);
		return { 8 * 4, 8 * 3 * 2 };
	}

	void draw_cube_corners_lines(const ProcShape& shape, const Box& box, MeshAdapter& writer)
	{
		for(int i = 0; i < 8; ++i)
		{
			vec3 position = box.m_center + box.m_vertices[i];

			static const vec3 components[3] = { X3, Y3, Z3 };
			float size_factor = 0.2f;
			
			writer.position(position)
				  .colour(shape.m_symbol.m_outline);

			for(int j = 0; j < 3; ++j)
				writer.position(position - position * components[j] * size_factor)
					  .colour(shape.m_symbol.m_outline);
		}


		for(uint16_t i = 0; i < 8 * 4; i+=4)
		{
			writer.line(i, i + 1);
			writer.line(i, i + 2);
			writer.line(i, i + 3);
		}
	}

	ShapeSize size_shape_lines(const ProcShape& shape, const Box& box)
	{
		//return size_cube_corners_lines(shape, box);
		UNUSED(shape); UNUSED(box);
		return { 8, 24 };
	}

	void draw_shape_lines(const ProcShape& shape, const Box& box, MeshAdapter& writer)
	{
		//return draw_cube_corners_lines(shape, box, writer);

		for(int i = 0; i < 8; ++i)
			writer.position(box.m_center + box.m_vertices[i])
				  .colour(shape.m_symbol.m_outline);

		for(uint16_t i = 0; i < 4; ++i)
			writer.line(i, (i + 1) % 4);

		for(uint16_t i = 4; i < 8; ++i)
			writer.line(i,  i == 7 ? 4 : i + 1);

		writer.line(1, 4);
		writer.line(2, 7);
		writer.line(0, 5);
		writer.line(3, 6);
	}

#define CUBE_NORMALS 1

	ShapeSize size_shape_triangles(const ProcShape& shape, const Box& box)
	{
		UNUSED(shape); UNUSED(box);
#if CUBE_NORMALS
		return { 24, 36 };
#else
		return { 16, 36 };
#endif
	}

	void draw_cube_quad(const ProcShape& shape, const Box& box, MeshAdapter& writer, uint32_t a, uint32_t b, uint32_t c, uint32_t d)
	{
		draw_shape_triangles(shape, Quad(box.m_vertices[a], box.m_vertices[b], box.m_vertices[c], box.m_vertices[d]), writer);
		writer.m_offset += 4;
	}

	void draw_shape_triangles(const ProcShape& shape, const Box& box, MeshAdapter& writer)
	{
#if CUBE_NORMALS
		draw_cube_quad(shape, box, writer, 0, 1, 2, 3);
		draw_cube_quad(shape, box, writer, 4, 5, 6, 7);
		draw_cube_quad(shape, box, writer, 0, 3, 6, 5);
		draw_cube_quad(shape, box, writer, 4, 7, 2, 1);
		draw_cube_quad(shape, box, writer, 3, 2, 7, 6);
		draw_cube_quad(shape, box, writer, 5, 4, 1, 0);
#else
		static vec2 quadUVs[4] = { { 1.f, 1.f }, { 1.f, 0.f }, { 0.f, 0.f }, { 0.f, 1.f } };

		for(int i = 0; i < 8; ++i)
			writer.position(shape.m_position + box.m_vertices[i])
				  .colour(Colour::White)
				  .uv0(quadUVs[i%4]);

		int i = 0;
		for(int v : { 3, 2, 7, 6, 5, 4, 1, 0 })
			writer.position(shape.m_position + box.m_vertices[v])
				  .colour(Colour::White)
				  .uv0(quadUVs[i++ % 4]);

		writer.quad(0, 1, 2, 3);
		writer.quad(4, 5, 6, 7);

		writer.quad(0, 3, 6, 5);
		writer.quad(4, 7, 2, 1);

		writer.quad(8, 9, 10, 11);
		writer.quad(12, 13, 14, 15);
#endif
	}

	// Angle around the Y axis, counter-clockwise when looking from above.
	inline float azimuth(const vec3& v) { return atan2(v.z, -v.x); };

	// Angle above the XZ plane.
	inline float inclination(const vec3& v) { return atan2(-v.y, sqrt((v.x * v.x) + (v.z * v.z))); };

#if 1
	void draw_polyhedron(const ProcShape& shape, MeshAdapter& writer, span<vec3> points, span<uint32_t> indices, float radius = 1.f, int detail = 0)
	{
		// the subdivision creates the vertex buffer data

		vector<vec3> vertices;
		vector<vec2> uvs;

		auto vertex = [&](vec3 v) {
			//writer.position(v);
			vertices.push_back(v);
		};

		auto subdivideFace = [&](vec3 a, vec3 b, vec3 c, int detail) {

			size_t cols = pow(2, detail);

			// we use this multidimensional array as a data structure for creating the subdivision

			vector<vector<vec3>> v;
			v.resize(cols+1);

			// construct all of the vertices for this subdivision

			for(int i = 0; i <= cols; i++) {

				vec3 aj = lerp(a, c, float(i) / float(cols));
				vec3 bj = lerp(b, c, float(i) / float(cols));

				int rows = cols - i;

				v[i].resize(rows+1);

				for(int j = 0; j <= rows; j++)
				{
					if(j == 0 && i ==  cols)
						v[i][j] = aj;
					else
						v[i][j] = lerp(aj, bj, float(j) / float(rows));
				}
			}

			// construct all of the faces

			for(int i = 0; i < cols; i++)
				for(int j = 0; j < 2 * (cols - i) - 1; j++)
				{
					int k = floor(j / 2);

					if(j % 2 == 0) {
						vertex(v[i][k + 1]);
						vertex(v[i + 1][k]);
						vertex(v[i][k]);
					}
					else {
						vertex(v[i][k + 1]);
						vertex(v[i + 1][k + 1]);
						vertex(v[i + 1][k]);
					}
				}
		};

		auto subdivide = [&](int detail) {

			// iterate over all faces and apply a subdivison with the given detail value

			for(int i = 0; i < indices.size(); i += 3) {

				// get the vertices of the face
				vec3 a = points[indices[i + 0]];
				vec3 b = points[indices[i + 1]];
				vec3 c = points[indices[i + 2]];

				// perform subdivision
				subdivideFace(a, b, c, detail);
			}
		};

		auto correctUV = [](vec2& uv, const vec3& p, float azimuth) {

			if((azimuth < 0) && (uv.x == 1.f))
				uv.x = uv.x - 1.f;
			if((p.x == 0.f) && (p.z == 0.f))
				uv.x = azimuth / 2.f / c_pi + 0.5f;
		};

		auto correctUVs = [&]() {

			for(int i = 0; i < vertices.size(); i += 3) {

				vec3 a = vertices[i+0];
				vec3 b = vertices[i+1];
				vec3 c = vertices[i+2];

				vec3 centroid = (a + b + c) / 3.f;

				float azi = azimuth(centroid);

				correctUV(uvs[i+0], a, azi);
				correctUV(uvs[i+1], b, azi);
				correctUV(uvs[i+2], c, azi);
			}
		};

		auto correctSeam = [&]() {

			// handle case when face straddles the seam, see #3269
			for(int i = 0; i < uvs.size(); ++i) {

				// uv data of a single face
				float x0 = uvs[i + 0].x;
				float x1 = uvs[i + 1].x;
				float x2 = uvs[i + 2].x;

				float hi = max(x0, max(x1, x2));
				float lo = min(x0, min(x1, x2));

				// 0.9 is somewhat arbitrar
				if(hi > 0.9f && lo < 0.1f)
				{
					if(x0 < 0.2) uvs[i + 0].x += 1.f;
					if(x1 < 0.2) uvs[i + 1].x += 1.f;
					if(x2 < 0.2) uvs[i + 2].x += 1.f;
				}
			}
		};

		auto generateUVs = [&]() {

			for(int i = 0; i < vertices.size(); ++i) {

				vec3 vertex = vertices[i + 0];

				float u = azimuth(vertex) / 2.f / c_pi + 0.5f;
				float v = inclination(vertex) / c_pi + 0.5f;
				uvs.push_back(vec2(u, 1.f - v));
			}

			correctUVs();
			correctSeam();
		};

		subdivide(detail);

		// all vertices should lie on a conceptual sphere with a given radius

		auto appplyRadius = [&](float radius) {

			// iterate over the entire buffer and apply the radius to each vertex
			for(int i = 0; i < vertices.size(); ++i)
			{
				vec3& v = vertices[i];
				v = normalize(v) * radius;
			}

		};

		appplyRadius(radius);

		// finally, create the uv data

		generateUVs();

		const size_t num = vertices.size();
		for(size_t i = 0; i < vertices.size(); ++i)
		{
			writer.position(vertices[i])
				  .colour(shape.m_symbol.m_fill)
				  .normal(normalize(vertices[i]))
				  .uv0(uvs[i]);
		}
		//if(flat) this.computeVertexNormals(); // flat normals
		//else this.normalizeNormals(); // smooth normals

	}
#endif

	void draw_polyedr(const ProcShape& shape, MeshAdapter& writer, span<vec3> vertices, span<uint32_t> indices, float radius)
	{
		for(size_t i = 0; i < vertices.size(); ++i)
		{
			const vec3& p = vertices[i];
			const float u = azimuth(p) / 2.f / c_pi + 0.5f;
			const float v = inclination(p) / c_pi + 0.5f;

			writer.position(normalize(p) * radius)
				  .colour(shape.m_symbol.m_fill)
				  .normal(normalize(p))
				  .uv0(vec2(u, 1.f - v));
		}

		for(size_t i = 0; i < indices.size(); ++i)
			writer.index(indices[i]);
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Tetraedr& tetra)
	{
		UNUSED(shape); UNUSED(tetra);
		return { 4U, 4U * 3U };
	}

	void draw_shape_triangles(const ProcShape& shape, const Tetraedr& tetra, MeshAdapter& writer)
	{
		constexpr vec3 vertices[] = {
			vec3(1, 1, 1), vec3(-1, -1, 1), vec3(-1, 1, -1), vec3(1, -1, -1)
		};

		constexpr uint32_t indices[] = {
			2, 1, 0, 0, 3, 2, 1, 3, 0, 2, 3, 1
		};

		draw_polyedr(shape, writer, vertices, indices, tetra.m_radius);

		//draw_polyhedron(writer, vertices, indices, tetra.m_radius, 0);
	}
	
	ShapeSize size_shape_triangles(const ProcShape& shape, const Icosaedr& icosa)
	{
		UNUSED(shape); UNUSED(icosa);
		//return { 12U, 20U * 3U };
		uint32_t detail = 1U;
		uint32_t num_verts = 60U * 4U * detail;
		return { num_verts, 0U };
	}

	void draw_shape_triangles(const ProcShape& shape, const Icosaedr& icosa, MeshAdapter& writer)
	{
		static const float t = (1.f + sqrt(5.f)) / 2.f;

		static const vec3 vertices[] = {
			vec3(-1, t, 0), vec3(1, t, 0), vec3(-1, -t, 0), vec3(1, -t, 0),
			vec3(0, -1, t), vec3(0, 1, t), vec3(0, -1, -t), vec3(0, 1, -t),
			vec3(t, 0, -1), vec3(t, 0, 1), vec3(-t, 0, -1), vec3(-t, 0, 1),
		};

		static const uint32_t indices[] = {
			0, 11, 5, 	0, 5, 1, 	0, 1, 7, 	0, 7, 10, 	0, 10, 11,
			1, 5, 9, 	5, 11, 4,	11, 10, 2,	10, 7, 6,	7, 1, 8,
			3, 9, 4, 	3, 4, 2,	3, 2, 6,	3, 6, 8,	3, 8, 9,
			4, 9, 5, 	2, 4, 11,	6, 2, 10,	8, 6, 7,	9, 8, 1
		};

		//draw_polyedr(shape, writer, vertices, indices, icosa.m_radius);

		draw_polyhedron(shape, writer, vertices, indices, icosa.m_radius, 1);
	}

}
