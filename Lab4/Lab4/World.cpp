#include "stdafx.h"
#include "World.h"
#include <algorithm>

namespace
{
	const glm::vec3 MAX_COLOR = { 0, 1, 1 };
	const glm::vec3 MIN_COLOR = { 1, 1, 0 };
	const glm::vec3 GREEN_COLOR = { 1.f, 1.f, 0.f };

	glm::ivec3 GetPixel(const SDLSurfacePtr & surface, unsigned x, unsigned y)
	{
		int bpp = surface->format->BytesPerPixel;
		Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return{ p[0], p[1], p[2] };
		else
			return{ p[2], p[1], p[0] };
	}


	struct CLandscapeTesselator : SMeshDataP3NT2
	{
	public:

		const float MIN_SCALE = 1.f;
		glm::ivec2 size;

		void Tesselate(std::string const & pathHeightMap, std::string const & pathNormalMap, float scale)
		{
			p_heightmap = CFilesystemUtils::LoadFileImage(pathHeightMap);
			p_normalmap = CFilesystemUtils::LoadFileImage(pathNormalMap);

			assert(p_heightmap->w == p_normalmap->w);
			assert(p_heightmap->h == p_normalmap->h);

			size = { p_heightmap->w, p_heightmap->h };
			MakeVertexAttributes(scale);
			MakeTriangleStripIndicies();
		}

	private:
		SDLSurfacePtr p_heightmap;
		SDLSurfacePtr p_normalmap;

		void MakeVertexAttributes(float scale)
		{
			const unsigned rowCount = size.x;
			const unsigned columnCount = size.y;
			for (unsigned ci = 0; ci < columnCount; ++ci)
			{
				const unsigned x = unsigned(ci);
				for (unsigned ri = 0; ri < rowCount; ++ri)
				{
					const unsigned z = unsigned(ri);

					SVertexP3NT2 vertex;
					vertex.position = GetPosition(x, z, scale);
					vertex.normal = GetNormal(x, z);
					vertex.texCoord = { float(ri) / rowCount * scale * 10, float(ci) / columnCount * scale * 10 };

					vertices.push_back(vertex);
				}
			}
		}

		void MakeTriangleStripIndicies()
		{
			const unsigned rowCount = size.x;
			const unsigned columnCount = size.y;
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

		glm::vec3 GetPosition(unsigned x, unsigned z, float scale)const
		{
			glm::ivec3 pixel = GetPixel(p_heightmap, x, z);
			const float y = float(pixel.r) / 255.f * 20.f;
			return{ x * scale, y * scale, z * scale };
		}

		glm::vec3 GetNormal(unsigned x, unsigned z)const
		{
			glm::ivec3 pixel = GetPixel(p_normalmap, x, z);
			const float nx = float(pixel.r) / 255.f;
			const float nz = float(pixel.g) / 255.f;
			const float ny = float(pixel.b) / 255.f;
			return{ nx, ny, nz };
		}
	};
}

CWorld::CWorld(std::string const & pathHeightMap, std::string const & pathNormalMap)
	: m_mesh(MeshType::TriangleStrip)
{
	float scale = 100.f;
	
	CLandscapeTesselator tesselator;
	tesselator.Tesselate(pathHeightMap, pathNormalMap, 100.f);
	
	m_mesh.Copy(tesselator);
}

void CWorld::Draw(IRenderer3D &renderer) const
{
	m_mesh.Draw(renderer);
}