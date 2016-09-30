#include "stdafx.h"
#include "Bodies.h"
#include <stdint.h>

namespace
{

typedef glm::vec3 Vertex;

// Вершины куба служат материалом для формирования треугольников,
// составляющих грани куба.
const Vertex CUBE_VERTICIES[] = {
	/*{ -0.5, -1.2, 0.5 },
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
	{ -0.5, 1.2, -0.5 }*/
	{-0.5, 1.2, -0.5}, // 1
	{0.5, 1.2, -0.5}, // 2
	{0.5, 1.2, 0.5},// 3
	{-0.5, 1.2, 0.5},// 4

	{-0.5, 0.5, 1.2},// 5
	{0.5, 0.5, 1.2},// 6
	{1.2, 0.5, 0.5},// 7
	{1.2, 0.5, -0.5},// 8
	{0.5, 0.5, -1.2},// 9
	{-0.5, 0.5, -1.2},// 10
	{-1.2, 0.5, -0.5},// 11
	{-1.2, 0.5, 0.5},// 12

	{-1.2, -0.5, 0.5}, // 13
	{-0.5, -0.5, 1.2}, // 14
	{0.5, -0.5, 1.2}, // 15
	{1.2, -0.5, 0.5}, // 16
	{1.2, -0.5, -0.5}, // 17
	{0.5, -0.5, -1.2}, // 18
	{-0.5, -0.5, -1.2}, // 19
	{-1.2, -0.5, -0.5}, // 20

	{ -0.5, -1.2, -0.5 },// 21
	{ 0.5, -1.2, -0.5 },// 22
	{ 0.5, -1.2, 0.5 },// 23
	{ -0.5, -1.2, 0.5 }// 24
};


struct STriangleFace
{
	uint16_t vertexIndex1;
	uint16_t vertexIndex2;
	uint16_t vertexIndex3;
	uint16_t colorIndex;
};

// Привыкаем использовать 16-битный unsigned short,
// чтобы экономить память на фигурах с тысячами вершин.
const STriangleFace CUBE_FACES[] = {
	{ 0, 1, 2, static_cast<uint16_t>(CubeFace::Top) }, 
	{ 0, 2, 3, static_cast<uint16_t>(CubeFace::Top) }, 

	{ 1, 7, 6, static_cast<uint16_t>(CubeFace::Front) }, 
	{ 1, 6, 2, static_cast<uint16_t>(CubeFace::Front) },
	{ 2, 6, 5, static_cast<uint16_t>(CubeFace::Left) },
	{ 2, 5, 4, static_cast<uint16_t>(CubeFace::Left) }, 
	{ 2, 4, 3, static_cast<uint16_t>(CubeFace::Left) }, 
	{ 3, 11, 10, static_cast<uint16_t>(CubeFace::Front) }, 
	{ 3, 10, 0, static_cast<uint16_t>(CubeFace::Front) },
	{ 0, 10, 9, static_cast<uint16_t>(CubeFace::Front) }, 
	{ 0, 9, 8, static_cast<uint16_t>(CubeFace::Right) },
	{ 0, 8, 1, static_cast<uint16_t>(CubeFace::Right) }, 
	{ 11, 3, 4, static_cast<uint16_t>(CubeFace::Front) },
	{ 1, 8, 7, static_cast<uint16_t>(CubeFace::Left) }, 

	{ 9, 8, 17, static_cast<uint16_t>(CubeFace::Back) },
	{ 9, 17, 18, static_cast<uint16_t>(CubeFace::Back) },
	{ 8, 17, 16, static_cast<uint16_t>(CubeFace::Back) },
	{ 8, 16, 7, static_cast<uint16_t>(CubeFace::Back) },
	{ 7, 16, 15, static_cast<uint16_t>(CubeFace::Back) },
	{ 7, 15, 6, static_cast<uint16_t>(CubeFace::Back) },
	{ 6, 15, 14, static_cast<uint16_t>(CubeFace::Front) },
	{ 6, 14, 5, static_cast<uint16_t>(CubeFace::Front) },
	{ 5, 14, 13, static_cast<uint16_t>(CubeFace::Front) },
	{ 5, 13, 4, static_cast<uint16_t>(CubeFace::Front) },
	{ 11, 4, 13, static_cast<uint16_t>(CubeFace::Back) },
	{ 13, 12, 11, static_cast<uint16_t>(CubeFace::Back) },
	{ 19, 12, 11, static_cast<uint16_t>(CubeFace::Right) },
	{ 19, 11, 10, static_cast<uint16_t>(CubeFace::Left) },
	{ 10, 9, 18, static_cast<uint16_t>(CubeFace::Right) },
	{ 10, 18, 19, static_cast<uint16_t>(CubeFace::Left) },

	{ 20, 19, 18, static_cast<uint16_t>(CubeFace::Right) },
	{ 20, 18, 17, static_cast<uint16_t>(CubeFace::Back) },
	{ 20, 17, 21, static_cast<uint16_t>(CubeFace::Back) },
	{ 17, 16, 21, static_cast<uint16_t>(CubeFace::Right) },
	{ 21, 16, 15, static_cast<uint16_t>(CubeFace::Right) },
	{ 21, 15, 22, static_cast<uint16_t>(CubeFace::Right) },
	{ 14, 15, 22, static_cast<uint16_t>(CubeFace::Back) },
	{ 23, 22, 14, static_cast<uint16_t>(CubeFace::Left) },
	{ 23, 14, 13, static_cast<uint16_t>(CubeFace::Left) },
	{ 23, 13, 12, static_cast<uint16_t>(CubeFace::Back) },
	{ 12, 19, 20, static_cast<uint16_t>(CubeFace::Right) },
	{ 12, 20, 23, static_cast<uint16_t>(CubeFace::Right) },

	{ 20, 21, 22, static_cast<uint16_t>(CubeFace::Bottom) },
	{ 20, 22, 23, static_cast<uint16_t>(CubeFace::Bottom) },
};

}

CIdentityCube::CIdentityCube()
	: m_alpha(1)
{
	// Используем белый цвет по умолчанию.
	for (glm::vec3 &color : m_colors)
	{
		color.x = 1;
		color.y = 1;
		color.z = 1;
	}
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

void CIdentityCube::SetFaceColor(CubeFace face, const glm::vec3 &color)
{
	const size_t index = static_cast<size_t>(face);
	assert(index < COLORS_COUNT);
	m_colors[index] = color;
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
		glm::vec3 color = m_colors[face.colorIndex];

		glColor4f(color.x, color.y, color.z, m_alpha);
		glNormal3fv(glm::value_ptr(normal));
		glVertex3fv(glm::value_ptr(v1));
		glVertex3fv(glm::value_ptr(v2));
		glVertex3fv(glm::value_ptr(v3));
	}
	glEnd();
}


