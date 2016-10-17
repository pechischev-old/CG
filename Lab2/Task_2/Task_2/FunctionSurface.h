#pragma once
#include "ISceneObject.h"
#include <functional>
#include <vector>
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>

using Function2D = std::function<float(float, float)>;

// ¬ершина с трЄхмерной позицией и нормалью.
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

class CSolidFunctionSurface final : public ISceneObject
{
public:
	CSolidFunctionSurface(const Function2D &fnOnX, const Function2D &fnOnY, const Function2D &fnOnZ);

	/// »нициализирует индексированную сетку треугольников
	/// @param rangeX - диапазон, где x - нижн€€ граница, y - верхн€€ граница
	/// @param rangeZ - диапазон, где x - нижн€€ граница, y - верхн€€ граница
	void Tesselate(const glm::vec2 &rangeX, const glm::vec2 &rangeZ, float step);

	// IBody interface.
	void Update(float) final {}
	void Draw() const final;
	void ChangeMode();

private:
	Function2D m_fnOnX;
	Function2D m_fnOnY;
	Function2D m_fnOnZ;
	std::vector<SVertexP3N> m_vertices;
	std::vector<uint32_t> m_indicies;
	bool m_isFrame = false;
};