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

#define AVERAGE_OFFSET 				200.0f
#define SEED						0.0f
#define ROUGHNESS					1.2f // This is a magic value

///////////////////////////////////////////////////////////////////////////////

HeightMap::HeightMap(void) :
 m_nSize(0),
 m_nGridSpacing(0),
 m_fVerticalScale(0.0f),
 m_pHeightMap(NULL)
{
}

///////////////////////////////////////////////////////////////////////////////

void HeightMap::Construct(int nSize, int nGrid, float fVerScale)
{
	m_nSize = nSize;
	m_nGridSpacing = nGrid;
	m_fVerticalScale = fVerScale;
	m_pHeightMap = new float[m_nSize * m_nSize];
}

///////////////////////////////////////////////////////////////////////////////

void HeightMap::Terminal(void)
{
	m_nSize = 0;
	m_nGridSpacing = 0;
	m_fVerticalScale = 0.0f;

	if (m_pHeightMap)
		delete m_pHeightMap;
	m_pHeightMap = NULL;
}

///////////////////////////////////////////////////////////////////////////////

float HeightMap::GetHeightAt(float &fX, float &fZ)
{
	return 0.0;
}

///////////////////////////////////////////////////////////////////////////////

float HeightMap::GetHeightAtIndex(int &nX, int &nZ)
{
	return 0.0f;
}

///////////////////////////////////////////////////////////////////////////////

void HeightMap::GetNormalAt(float &fX, float &fZ, vec3 &vNormal)
{
	vNormal.x = 0.0f;
	vNormal.y = 0.0f;
	vNormal.z = 0.0f;
}

///////////////////////////////////////////////////////////////////////////////

void HeightMap::GetNormalAtIndex(int &nX, int &nZ, vec3 &vNormal)
{
	vNormal.x = 0.0f;
	vNormal.y = 0.0f;
	vNormal.z = 0.0f;
}

///////////////////////////////////////////////////////////////////////////////

int HeightMap::GetHeightIndexAt(int &nX, int &nZ)
{
	return (((nX + m_nSize) % m_nSize) + ((nZ + m_nSize) % m_nSize) * m_nSize);
}

///////////////////////////////////////////////////////////////////////////////

void HeightMap::GenerationDiamondSquareFractal(void)
{	
	// Declare some internal variable
	int w, x, z;
	float dH, dHFactor;
	int nP1, nP2, nP3, nP4, nPmid;
	//float fMinH, fMaxH;
	dH = m_nSize * 0.5f; // dH is length of height map in one dimension
	dHFactor = pow(2.0f, -ROUGHNESS);
	//fMinH = fMaxH = 0.0f;
	
	// Fill initial value for height map
	for (w = 0 ; w < m_nSize*m_nSize ; ++w)
		m_pHeightMap[w] = SEED;
		
	for (w = m_nSize ; w > 0 ; w /= 2, dH *= dHFactor)
	{
		// Diamond stage
		for (z = 0; z < m_nSize; ++z)
		{
			for (x = 0; x < m_nSize; ++x)
			{
				nP1 = GetHeightIndexAt(x, z);
				nP2 = GetHeightIndexAt(x + w, z);
				nP3 = GetHeightIndexAt(x, z + w);
				nP4 = GetHeightIndexAt(x + w, z + w);
				nPmid = GetHeightIndexAt(x + w/2, z + w/2);
				
				m_pHeightMap[nPmid] = 
			}
		}
		
		// Square stage
		for (z = 0; z < m_nSize; ++z)
		{
			for (x = 0; x < m_nSize; ++x)
			{
			
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////

void HeightMap::Blur(void)
{

}

///////////////////////////////////////////////////////////////////////////////

void HeightMap::Smooth(void)
{
	
}

///////////////////////////////////////////////////////////////////////////////
