#pragma once
#include "libchapter3.h"

#include <functional>
#include <vector>
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>




class CWorld
{
public:
	CWorld(std::string const & pathHeightMap, std::string const & pathNormalMap);

	void Draw(IRenderer3D &renderer)const;

private:
	CMeshP3NT2 m_mesh;
};

