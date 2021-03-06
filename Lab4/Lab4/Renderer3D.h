#pragma once
#include "stdafx.h"

class CProgramContext;

class CRenderer3D : public IRenderer3D
{
public:
	CRenderer3D(CVertexAttribute const & vertexAttr, CVertexAttribute const & normalAttr, CVertexAttribute const & texCoordAttr);
	~CRenderer3D();

	// IRenderer3D interface
	void SetTexCoord2DOffset(size_t offset, size_t stride) override;
	void SetPosition3DOffset(size_t offset, size_t stride) override;
	void SetNormalOffset(size_t offset, size_t stride) override;

private:
	CVertexAttribute m_vertexAttr;
	CVertexAttribute m_normalAttr;
	CVertexAttribute m_texCoordAttr;
};
