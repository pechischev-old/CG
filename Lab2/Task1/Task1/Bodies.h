#pragma once

#include <glm/vec3.hpp>
#include <glm/fwd.hpp>
#include <boost/noncopyable.hpp>

enum class CubeFace
{
	Front = 0,
	Back,
	Top,
	Bottom,
	Left,
	Right,

	NumFaces
};

class CIdentityCube
{
public:
	CIdentityCube();
    void Update(float deltaTime);
    void Draw()const;

	void SetFaceColor(CubeFace face, const glm::vec3 &color);
	void SetAlpha(float alpha);

private:
	void OutputFaces()const;

	static const size_t COLORS_COUNT = static_cast<size_t>(CubeFace::NumFaces);
	glm::vec3 m_colors[COLORS_COUNT];
	float m_alpha;
};
