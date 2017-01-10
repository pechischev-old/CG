#pragma once
#include "libchapter3.h"

struct CWorldTesselator : SMeshDataP3NT2
{
public:
	CWorldTesselator(std::string const & pathHeightMap, std::string const & pathNormalMap);
	void Tesselate(float scale);
private:
	void MakeVertexAttributes();
	void MakeTriangleStripIndicies();
	glm::vec3 GetPosition(unsigned x, unsigned z, float scale) const;
	glm::vec3 GetNormal(unsigned x, unsigned z) const;
private:
	SDLSurfacePtr m_pHeightMap;
	SDLSurfacePtr m_pNormalMap;
	glm::ivec2 m_size;
	float m_scale;
};

