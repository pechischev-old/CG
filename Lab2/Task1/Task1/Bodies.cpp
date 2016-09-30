#include "stdafx.h"
#include "Bodies.h"
#include <stdint.h>

namespace
{
	
typedef glm::vec3 Vertex;
const glm::vec3 PINK = { 1.f, 0.3f, 0.3f };
const glm::vec3 GREEN = { 0.f, 1.f, 0.f };
const glm::vec3 BLUE = { 0.f, 0.f, 1.f };
const glm::vec3 PURPLE = { 1.f, 0.f, 1.f };
const glm::vec3 CYAN = { 0.f, 0.5f, 0.7f };

const glm::vec3 colors[] = { PINK , GREEN, BLUE, PURPLE, CYAN };

enum class Colors
{
	Pink = 0,
	Green,
	Blue,
	Purple,
	Cyan,

	NumColors
};


// Вершины куба служат материалом для формирования треугольников,
// составляющих грани куба.
const Vertex CUBE_VERTICIES[] = {
	{ -0.5, -1.2, 0.5 },
	{ 0.5, -1.2, 0.5 },
	{ 0.5, -1.2, -0.5 },
	{ -0.5, -1.2, -0.5 },

	{ -0.5, -0.5, 1.2 },
	{ 0.5, -0.5, 1.2 },
	{ 1.2, -0.5, 0.5 },
	{ 1.2, -0.5, -0.5 },
	{ 0.5, -0.5, -1.2 },
	{ -0.5, -0.5, -1.2 },
	{ -1.2, -0.5, -0.5 },
	{ -1.2, -0.5, 0.5 },

	{ -0.5, 0.5, 1.2 },
	{ 0.5, 0.5, 1.2 },
	{ 1.2, 0.5, 0.5 },
	{ 1.2, 0.5, -0.5 },
	{ 0.5, 0.5, -1.2 },
	{ -0.5, 0.5, -1.2 },
	{ -1.2, 0.5, -0.5 },
	{ -1.2, 0.5, 0.5 },

	{ -0.5, 1.2, 0.5 },
	{ 0.5, 1.2, 0.5 },
	{ 0.5, 1.2, -0.5 },
	{ -0.5, 1.2, -0.5 }
};


struct STriangleFace
{
	uint16_t vertexIndex1;
	uint16_t vertexIndex2;
	uint16_t vertexIndex3;
	uint16_t colorIndex;
};


const STriangleFace CUBE_FACES[] = {
	{ 0, 3, 2, static_cast<uint16_t>(Colors::Pink) },
	{ 0, 2, 1, static_cast<uint16_t>(Colors::Pink) },

	{ 4, 11, 0, static_cast<uint16_t>(Colors::Cyan) },
	{ 5, 4, 0, static_cast<uint16_t>(Colors::Green) },
	{ 5, 0, 1, static_cast<uint16_t>(Colors::Green) },
	{ 6, 5, 1, static_cast<uint16_t>(Colors::Purple) },
	{ 7, 6, 1, static_cast<uint16_t>(Colors::Pink) },
	{ 7, 1, 2, static_cast<uint16_t>(Colors::Pink) },
	{ 8, 7, 2, static_cast<uint16_t>(Colors::Purple) },
	{ 9, 8, 2, static_cast<uint16_t>(Colors::Cyan) },
	{ 9, 2, 3, static_cast<uint16_t>(Colors::Cyan) },
	{ 10, 9, 3, static_cast<uint16_t>(Colors::Blue) },
	{ 11, 10, 3, static_cast<uint16_t>(Colors::Purple) },
	{ 11, 3, 0, static_cast<uint16_t>(Colors::Purple) },

	{ 12, 4, 5, static_cast<uint16_t>(Colors::Purple) },
	{ 13, 12, 5, static_cast<uint16_t>(Colors::Purple) },
	{ 13, 5, 6, static_cast<uint16_t>(Colors::Pink) },
	{ 14, 13, 6, static_cast<uint16_t>(Colors::Pink) },
	{ 14, 6, 7, static_cast<uint16_t>(Colors::Cyan) },
	{ 15, 14, 7, static_cast<uint16_t>(Colors::Cyan) },
	{ 15, 7, 8, static_cast<uint16_t>(Colors::Blue) },
	{ 16, 15, 8, static_cast<uint16_t>(Colors::Blue) },
	{ 16, 8, 9, static_cast<uint16_t>(Colors::Green) },
	{ 17, 16, 9, static_cast<uint16_t>(Colors::Green) },
	{ 17, 9, 10, static_cast<uint16_t>(Colors::Pink) },
	{ 18, 17, 10, static_cast<uint16_t>(Colors::Pink) },
	{ 18, 10, 11, static_cast<uint16_t>(Colors::Cyan) },
	{ 19, 18, 11, static_cast<uint16_t>(Colors::Cyan) },
	{ 19, 11, 4, static_cast<uint16_t>(Colors::Blue) },
	{ 12, 19, 4, static_cast<uint16_t>(Colors::Blue) },

	{ 19, 12, 20, static_cast<uint16_t>(Colors::Cyan) },
	{ 12, 13, 20, static_cast<uint16_t>(Colors::Green) },
	{ 13, 21, 20, static_cast<uint16_t>(Colors::Green) },
	{ 13, 14, 21, static_cast<uint16_t>(Colors::Purple) },
	{ 14, 15, 21, static_cast<uint16_t>(Colors::Pink) },
	{ 15, 22, 21, static_cast<uint16_t>(Colors::Pink) },
	{ 15, 16, 22, static_cast<uint16_t>(Colors::Purple) },
	{ 16, 17, 22, static_cast<uint16_t>(Colors::Cyan) },
	{ 17, 23, 22, static_cast<uint16_t>(Colors::Cyan) },
	{ 17, 18, 23, static_cast<uint16_t>(Colors::Blue) },
	{ 18, 19, 23, static_cast<uint16_t>(Colors::Purple) },
	{ 19, 20, 23, static_cast<uint16_t>(Colors::Purple) },

	{ 20, 21, 22, static_cast<uint16_t>(Colors::Pink) },
	{ 20, 22, 23, static_cast<uint16_t>(Colors::Pink) }
};

}

CIdentityCube::CIdentityCube()
	: m_alpha(1)
{
}

void CIdentityCube::Update(float deltaTime)
{
    (void)deltaTime;
}

void CIdentityCube::Draw() const
{
	if (m_alpha < 0.99f)
	{
		glFrontFace(GL_CW);
		OutputFaces();
		glFrontFace(GL_CCW);
	}
	OutputFaces();
}

void CIdentityCube::SetAlpha(float alpha)
{
	m_alpha = alpha;
}

void CIdentityCube::OutputFaces() const
{
	glBegin(GL_TRIANGLES);

	for (const STriangleFace &face : CUBE_FACES)
	{
		const Vertex &v1 = CUBE_VERTICIES[face.vertexIndex1];
		const Vertex &v2 = CUBE_VERTICIES[face.vertexIndex2];
		const Vertex &v3 = CUBE_VERTICIES[face.vertexIndex3];
		glm::vec3 normal = glm::normalize(glm::cross(v2 - v1, v3 - v1));
		glm::vec3 color = colors[face.colorIndex];

		glColor4f(color.x, color.y, color.z, m_alpha);
		glNormal3fv(glm::value_ptr(normal));
		glVertex3fv(glm::value_ptr(v1));
		glVertex3fv(glm::value_ptr(v2));
		glVertex3fv(glm::value_ptr(v3));
	}
	glEnd();
}


