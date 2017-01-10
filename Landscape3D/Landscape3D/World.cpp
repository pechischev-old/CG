#include "stdafx.h"
#include "World.h"
#include "WorldTesselator.h"


CWorld::CWorld(std::string const & pathHeightMap, std::string const & pathNormalMap)
	: m_mesh(MeshType::TriangleStrip)
{
	float scaleMap = 100.f;
	
	CWorldTesselator tesselator(pathHeightMap, pathNormalMap);
	tesselator.Tesselate(scaleMap);
	
	m_mesh.Copy(tesselator);
}

void CWorld::Draw(IRenderer3D &renderer) const
{
	m_mesh.Draw(renderer);
}