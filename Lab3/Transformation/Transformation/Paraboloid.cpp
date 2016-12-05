#include "stdafx.h"
#include "Paraboloid.h"
#include <algorithm>
#include <cmath>
#define USE_MATH_DEFINES

namespace
{
	const unsigned MIN_PRECISION = 4;
	const float UV_DELTA = 0.05f;

	typedef glm::vec3 Vertex;

	void CalculateTriangleStripIndicies(std::vector<uint32_t> &indicies,
		unsigned columnCount, unsigned rowCount)
	{
		indicies.clear();
		indicies.reserve((columnCount - 1) * rowCount * 2);
		// вычисляем индексы вершин.
		for (unsigned ci = 0; ci < columnCount - 1; ++ci)
		{
			if (ci % 2 == 0)
			{
				for (unsigned ri = 0; ri < rowCount; ++ri)
				{
					unsigned index = ci * rowCount + ri;
					indicies.push_back(index + rowCount);
					indicies.push_back(index);
				}
			}
			else
			{
				for (unsigned ri = rowCount - 1; ri < rowCount; --ri)
				{
					unsigned index = ci * rowCount + ri;
					indicies.push_back(index);
					indicies.push_back(index + rowCount);
				}
			}
		}
	}

	/// Привязывает вершины к состоянию OpenGL,
	/// затем вызывает 'callback'.
	template <class T>
	void DoWithBindedArrays(const std::vector<SVertexP3N> &vertices, T && callback)
	{
		// Включаем режим vertex array и normal array.
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		// Выполняем привязку vertex array и normal array
		const size_t stride = sizeof(SVertexP3N);
		glNormalPointer(GL_FLOAT, stride, glm::value_ptr(vertices[0].normal));
		glVertexPointer(3, GL_FLOAT, stride, glm::value_ptr(vertices[0].position));
		//glTexCoordPointer(2, GL_FLOAT, stride, glm::value_ptr(vertices[0].texCoord));

		// Выполняем внешнюю функцию.
		callback();

		// Выключаем режим vertex array и normal array.
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	}

	void CalculateNormals(SVertexP3N &vertice, const Function2D &fn, float step, float u, float v)
	{
		glm::vec3 directionV1 = fn(u, v + step) - vertice.position;
		glm::vec3 directionV2 = (fn(u + step, v) - vertice.position);
		vertice.normal = glm::normalize(glm::cross(directionV1, directionV2));
	}
}

CParaboloid::CParaboloid(const Function2D &fn)
	: m_fn(fn)
{
}

void CParaboloid::Draw() const
{
	DoWithBindedArrays(m_vertices, [this] {
		glDrawElements(GL_TRIANGLE_STRIP, GLsizei(m_indicies.size()),
			GL_UNSIGNED_INT, m_indicies.data());
	});
	//DoWithBindedArrays(m_vertices);
}

void CParaboloid::Tesselate(const glm::vec2 &rangeX, const glm::vec2 &rangeZ, float step)
{
	const unsigned columnCount = unsigned((rangeX.y - rangeX.x) / step) + 2;
	const unsigned rowCount = unsigned((rangeZ.y - rangeZ.x) / step) + 1;
	m_vertices.clear();
	m_vertices.reserve(columnCount * rowCount);

	// вычисляем позиции вершин.
	for (unsigned ci = 0; ci < columnCount; ++ci)
	{
		const float u = rangeX.x + step * float(ci);
		for (unsigned ri = 0; ri < rowCount; ++ri)
		{
			const float v = rangeZ.x + step * float(ri);
			auto vertice = SVertexP3N(m_fn(u, v));

			float yParam = vertice.position.y;

			CalculateNormals(vertice, m_fn, step, u, v);

			m_vertices.push_back(vertice);
		}
	}
	CalculateTriangleStripIndicies(m_indicies, columnCount, rowCount);
}
