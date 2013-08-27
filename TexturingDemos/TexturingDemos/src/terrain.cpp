///////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2010 AsNet Co., Ltd.
// All Rights Reserved. These instructions, statements, computer
// programs, and/or related material (collectively, the "Source")
// contain unpublished information proprietary to AsNet Co., Ltd
// which is protected by US federal copyright law and by 
// international treaties. This Source may NOT be disclosed to 
// third parties, or be copied or duplicated, in whole or in 
// part, without the written consent of AsNet Co., Ltd.
///////////////////////////////////////////////////////////////////////////////
// Author: Canh Doan
///////////////////////////////////////////////////////////////////////////////

#include "package.h"

///////////////////////////////////////////////////////////////////////////////

Terrain::Terrain(void) :
 m_nVertexVBO(0),
 m_nIndexVBO(0),
 m_nTotalVertices(0),
 m_nTotalIndices(0),
 m_pHeightMap(NULL)
{
}

///////////////////////////////////////////////////////////////////////////////

void Terrain::Construct(int nSize, int nGrid, float fScale)
{
	m_pHeightMap = new HeightMap();
	m_pHeightMap->Construct(nSize, nGrid, fScale);
	m_pHeightMap->GenerationDiamondSquareFractal();

	// Create terrain
	// Generate vertex  buffer
	m_nTotalVertices = nSize * nSize;
	glGenBuffers(1, &m_nVertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_nVertexVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sVertex) * m_nTotalVertices,0, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	// Generate index buffer
	m_nTotalIndices = (nSize - 1) * (nSize * 2 + 1);
	glGenBuffers(1, &m_nIndexVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_nIndexVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * m_nTotalIndices, 0, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	// Generate indices & vertices
	GenerateIndices();
	GenerateVertices();	
}

///////////////////////////////////////////////////////////////////////////////

void Terrain::Terminal(void)
{
	if (m_nVertexVBO)
    {
        glDeleteBuffers(1, &m_nVertexVBO);
    }
	m_nVertexVBO = 0;
    m_nTotalVertices = 0;

    if (m_nIndexVBO)
    {
        glDeleteBuffers(1, &m_nIndexVBO);
    }
	m_nIndexVBO = 0;
    m_nTotalIndices = 0;
}

///////////////////////////////////////////////////////////////////////////////

void Terrain::OnUpdate(/*vec3 vCameraPos*/)
{

}

///////////////////////////////////////////////////////////////////////////////

void Terrain::OnRender(void)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_nVertexVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_nIndexVBO);

    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, sizeof(sVertex), (GLvoid *)(sizeof(GLfloat) * 6));

    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, sizeof(sVertex), (GLvoid *)(sizeof(GLfloat) * 3));

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(sVertex), 0);

    glDrawElements(GL_TRIANGLE_STRIP, m_nTotalIndices, GL_UNSIGNED_SHORT, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

///////////////////////////////////////////////////////////////////////////////

bool Terrain::GenerateVertices(void)
{
	sVertex *pVertices = 0;
    sVertex *pVertex = 0;
    int currVertex = 0;
    int size = m_pHeightMap->GetSize();
    int gridSpacing = m_pHeightMap->GetGridSpacing();
    float heightScale = m_pHeightMap->GetHeightScale();
    vec3 normal;

    glBindBuffer(GL_ARRAY_BUFFER, m_nVertexVBO);
    pVertices = (sVertex*)(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

    if (!pVertices)
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        return false;
    }

    for (int z = 0; z < size; ++z)
    {
        for (int x = 0; x < size; ++x)
        {
            currVertex = z * size + x;
            pVertex = &pVertices[currVertex];

            pVertex->vPosition.x = (float)(x * gridSpacing);
            pVertex->vPosition.y = m_pHeightMap->GetHeightAtPixel(x, z) * heightScale;
            pVertex->vPosition.z = (float)(z * gridSpacing);

            m_pHeightMap->GetNormalAtPixel(x, z, normal);
            pVertex->vNormal.x = normal.x;
            pVertex->vNormal.y = normal.y;
            pVertex->vNormal.z = normal.z;
            
            pVertex->vUV.x = (float)(x) / (float)(size);
            pVertex->vUV.y = (float)(z) / (float)(size);
        }
    }

    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return true;
}

///////////////////////////////////////////////////////////////////////////////

bool Terrain::GenerateIndices(void)
{
	void *pBuffer = 0;
    int size = m_pHeightMap->GetSize();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_nIndexVBO);
    
    if (!(pBuffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY)))
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        return false;
    }
	
	unsigned short *pIndex = (unsigned short *)(pBuffer);

        for (int z = 0; z < size - 1; ++z)
        {
            if (z % 2 == 0)
            {
                for (int x = 0; x < size; ++x)
                {
                    *pIndex++ = (unsigned short)(x + z * size);
                    *pIndex++ = (unsigned short)(x + (z + 1) * size);
                }

                // Add degenerate triangles to stitch strips together.
                *pIndex++ = (unsigned short)((size - 1) + (z + 1) * size);
            }
            else
            {
                for (int x = size - 1; x >= 0; --x)
                {
                    *pIndex++ = (unsigned short)(x + z * size);
                    *pIndex++ = (unsigned short)(x + (z + 1) * size);
                }

                // Add degenerate triangles to stitch strips together.
                *pIndex++ = (unsigned short)((z + 1) * size);
            }
        }
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
