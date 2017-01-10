#include "stdafx.h"
#include "Renderer3D.h"
//#include "ProgramContext.h"


CRenderer3D::CRenderer3D(CVertexAttribute const & vertexAttr, CVertexAttribute const & normalAttr, CVertexAttribute const & texCoordAttr)
	: m_vertexAttr(vertexAttr)
	, m_normalAttr(normalAttr)
	, m_texCoordAttr(texCoordAttr)
{
	//m_context.Use();
	m_vertexAttr.EnablePointer();
	m_normalAttr.EnablePointer();
	m_texCoordAttr.EnablePointer();
}

CRenderer3D::~CRenderer3D()
{
	m_vertexAttr.DisablePointer();
	m_normalAttr.DisablePointer();
	m_texCoordAttr.DisablePointer();
}

void CRenderer3D::SetTexCoord2DOffset(size_t offset, size_t stride)
{
	m_texCoordAttr.SetVec2Offset(offset, stride);
}

void CRenderer3D::SetPosition3DOffset(size_t offset, size_t stride)
{
	m_vertexAttr.SetVec3Offset(offset, stride, false);
}

void CRenderer3D::SetNormalOffset(size_t offset, size_t stride)
{
	m_normalAttr.SetVec3Offset(offset, stride, false);
}
