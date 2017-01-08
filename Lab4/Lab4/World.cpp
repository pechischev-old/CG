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
		//assert(bpp == 3);
		Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return{ p[0], p[1], p[2] };
		else
			return{ p[2], p[1], p[0] };
	}

	glm::ivec2 GetIndex(glm::vec2 const & position, float scale)
	{
		const unsigned ci = int(std::roundf(std::roundf(position.x) / scale));
		const unsigned ri = int(std::roundf(std::roundf(position.y) / scale));
		return{ ci, ri };
	}

	unsigned GetSingleIndex(glm::ivec2 indices, glm::ivec2 size)
	{
		return indices.x * size.y + indices.y;
	}

	struct CLandscapeTesselator : SMeshDataP3NT2
	{
	public:

		const float MIN_SCALE = 1.f;
		glm::ivec2 size;

		std::string pathHeightMap;
		std::string pathNormalMap;

		void Tesselate(float scale)
		{
			assert(scale >= MIN_SCALE);
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

	float NormalizeValue(float value, glm::vec2 const& range)
	{
		const float length = (std::abs(range.x - range.y));
		return std::abs(range.y - value) / length;
	}
}

CWorld::CWorld(std::string const & pathHeightMap, std::string const & pathNormalMap)
	: m_mesh(MeshType::TriangleStrip)
{
	CLandscapeTesselator tesselator;
	tesselator.pathHeightMap = pathHeightMap;
	tesselator.pathNormalMap = pathNormalMap;
	tesselator.Tesselate(100.f);
	m_surfaceData = tesselator.vertices;
	m_size = tesselator.size;
	m_mesh.Copy(tesselator);
}

void CWorld::Draw(IRenderer3D &renderer) const
{
	//glDisable(GL_CULL_FACE);
	m_mesh.Draw(renderer);
	//glEnable(GL_CULL_FACE);
}

