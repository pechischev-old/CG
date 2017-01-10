#include "stdafx.h"
#include "WorldTesselator.h"

namespace
{
	const glm::vec2 SIZE_TEXTURE = { 20.f, 20.f };
	const float SCALE_MAP_HEIGTH = 30.f;
	const float GRAYSCALE = 255.f;
	const float MIN_SCALE = 1.f;

	glm::ivec3 GetPixel(const SDLSurfacePtr & surface, unsigned x, unsigned y)
	{
		int bpp = surface->format->BytesPerPixel;
		Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return{ p[0], p[1], p[2] };
		else
			return{ p[2], p[1], p[0] };
	}
}

CWorldTesselator::CWorldTesselator(std::string const & pathHeightMap, std::string const & pathNormalMap)
	: m_scale(MIN_SCALE)
{
	m_pHeightMap = CFilesystemUtils::LoadFileImage(pathHeightMap);
	m_pNormalMap = CFilesystemUtils::LoadFileImage(pathNormalMap);

	assert(m_pHeightMap->w == m_pNormalMap->w);
	assert(m_pHeightMap->h == m_pNormalMap->h);

	m_size = { m_pHeightMap->w, m_pHeightMap->h };
}

void CWorldTesselator::Tesselate(float scale)
{
	assert(scale >= m_scale);
	m_scale = scale;
	
	MakeVertexAttributes();
	MakeTriangleStripIndicies();
}

void CWorldTesselator::MakeVertexAttributes()
{
	const unsigned rowCount = m_size.x;
	const unsigned columnCount = m_size.y;
	for (unsigned ci = 0; ci < columnCount; ++ci)
	{
		const unsigned x = unsigned(ci);
		for (unsigned ri = 0; ri < rowCount; ++ri)
		{
			const unsigned z = unsigned(ri);

			SVertexP3NT2 vertex;
			vertex.position = GetPosition(x, z, m_scale);
			vertex.normal = GetNormal(x, z);
			vertex.texCoord = { float(ri) / rowCount * m_scale * SIZE_TEXTURE.x, float(ci) / columnCount * m_scale * SIZE_TEXTURE.y };

			vertices.push_back(vertex);
		}
	}
}

void CWorldTesselator::MakeTriangleStripIndicies()
{
	const unsigned rowCount = m_size.x;
	const unsigned columnCount = m_size.y;
	indicies.clear();
	indicies.reserve((columnCount - 1) * rowCount * 2);

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

glm::vec3 CWorldTesselator::GetPosition(unsigned x, unsigned z, float scale)const
{
	glm::ivec3 pixel = GetPixel(m_pHeightMap, x, z);
	const float y = float(pixel.r) / GRAYSCALE * SCALE_MAP_HEIGTH;
	return{ x * scale, y * scale, z * scale };
}

glm::vec3 CWorldTesselator::GetNormal(unsigned x, unsigned z)const
{
	glm::ivec3 pixel = GetPixel(m_pNormalMap, x, z);
	const float nx = float(pixel.r) / GRAYSCALE;
	const float nz = float(pixel.g) / GRAYSCALE;
	const float ny = float(pixel.b) / GRAYSCALE;
	return{ nx, ny, nz };
}