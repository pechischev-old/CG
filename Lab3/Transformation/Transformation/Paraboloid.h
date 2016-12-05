#pragma once

#include <functional>
#include <vector>
#include <glm/fwd.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

using Function2D = std::function<glm::vec3(float, float)>;

// Вершина с трёхмерной позицией и нормалью.
struct SVertexP3N
{
    glm::vec3 position;
    glm::vec3 normal;

	SVertexP3N() = default;
	SVertexP3N(const glm::vec3 &position)
		: position(position)
	{
	}
};


class CParaboloid
{
public:
	CParaboloid(const Function2D &fn);

	void Draw()const;
	void Tesselate(const glm::vec2 &rangeX, const glm::vec2 &rangeZ, float step);
	
private:
	Function2D m_fn;
	std::vector<SVertexP3N> m_vertices;
	std::vector<uint32_t> m_indicies;
};
