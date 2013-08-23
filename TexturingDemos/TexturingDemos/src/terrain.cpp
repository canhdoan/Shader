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
 m_pPixelMap(NULL), 
 m_fVerticlaScale(2.0f),
 m_nTerrainSubdivision(32)
{
}

///////////////////////////////////////////////////////////////////////////////

Terrain::~Terrain(void)
{
}

///////////////////////////////////////////////////////////////////////////////

void Terrain::Construct(void)
{

}

///////////////////////////////////////////////////////////////////////////////

void Terrain::Terminal(void)
{
	
}

///////////////////////////////////////////////////////////////////////////////

void Terrain::ConvertToGrayScale(void)
{
	long i, j;
	long offset;

	if( !m_pTerrain || !m_pPixelMap ) return;

	for( j=0; j<256; j++ )
	{
		for( i=0; i<256; i++ )
		{
			offset = j*256 + i;

			m_pTerrain[offset] = 0.3*(float)m_pPixelMap[offset].r + 0.59*(float)m_pPixelMap[offset].g + 0.11*(float)m_pPixelMap[offset].b;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////

void Terrain::CreateTerrain(void)
{
	int i, j;
	float pas = 20.0/(float)m_nTerrainSubdivision;
	sVertex *p1, *p2, *p3, *p4;
	sVertex v1, v2, v3;
	Dword_ face;
	float heightMap;

	float norme, root;
	float incx, incy, incz;

	mesh.m_numFaces = m_nTerrainSubdivision*m_nTerrainSubdivision*2;
	mesh.m_numVertices = (m_nTerrainSubdivision+1)*(m_nTerrainSubdivision+1);

	mesh.m_verticesList = new sVertex[mesh.m_numVertices];
	mesh.m_facesList = new sFace[mesh.m_numFaces];

	// Fill the vertices list /////////////////////////////
	for( j=0; j<m_nTerrainSubdivision+1; j++ )
	{
		for( i=0; i<m_nTerrainSubdivision+1; i++ )
		{
			mesh.m_verticesList[j*(m_nTerrainSubdivision+1) + i].x = -10.0 + (float)i*pas;
			heightMap = elevation(i, j, (float)m_nTerrainSubdivision, m_fVerticlaScale );
			if( heightMap > g_threshold )
			{
				mesh.m_verticesList[j*(m_nTerrainSubdivision+1) + i].y = heightMap;
			}
			else
			{
				mesh.m_verticesList[j*(m_nTerrainSubdivision+1) + i].y = g_threshold;
			}

			mesh.m_verticesList[j*(m_nTerrainSubdivision+1) + i].z = -10.0 + (float)j*pas;
			mesh.m_verticesList[j*(m_nTerrainSubdivision+1) + i].u = (float)i/m_nTerrainSubdivision;
			mesh.m_verticesList[j*(m_nTerrainSubdivision+1) + i].v = (float)j/m_nTerrainSubdivision;
		}
	}

	// Fill the faces list /////////////////////////////
	face=0;
	for( j=0; j<m_nTerrainSubdivision; j++ )
	{
		for( i=0; i<m_nTerrainSubdivision; i++ )
		{
			
			// Triangle 1 du quad ////////////////////////////////
			p1 = &mesh.m_verticesList[j*(m_nTerrainSubdivision+1) + i];
			p2 = &mesh.m_verticesList[j*(m_nTerrainSubdivision+1) + (i+1)];
			p3 = &mesh.m_verticesList[(j+1)*(m_nTerrainSubdivision+1) + (i+1)];

			v1.x = p2->x - p1->x;
			v1.y = p2->y - p1->y;
			v1.z = p2->z - p1->z;

			v2.x = p3->x - p1->x;
			v2.y = p3->y - p1->y;
			v2.z = p3->z - p1->z;

			incx = v2.y*v1.z - v2.z*v1.y;
			incy = v2.z*v1.x - v2.x*v1.z;
			incz = v2.x*v1.y - v2.y*v1.x;

			norme = incx*incx + incy*incy + incz*incz;
			root =(float)( 1.0f/(float)sqrt(norme+0.000001) );
			incx *= root;
			incy *= root;
			incz *= root;

			p1->n.x += incx;
			p1->n.y += incy;
			p1->n.z += incz;

			p2->n.x += incx;
			p2->n.y += incy;
			p2->n.z += incz;

			p3->n.x += incx;
			p3->n.y += incy;
			p3->n.z += incz;

			mesh.m_facesList[face].a = j*(m_nTerrainSubdivision+1) + i; // p1
			mesh.m_facesList[face].c = j*(m_nTerrainSubdivision+1) + (i+1); // p2
			mesh.m_facesList[face].b = (j+1)*(m_nTerrainSubdivision+1) + (i+1); // p3
			mesh.m_facesList[face].n.x = incx;
			mesh.m_facesList[face].n.y = incy;
			mesh.m_facesList[face].n.z = incz;
			face++;

			// Triangle 2 du quad ////////////////////////////////
			p4 = &mesh.m_verticesList[(j+1)*(m_nTerrainSubdivision+1) + i];
				
			v3.x = p4->x - p1->x;
			v3.y = p4->y - p1->y;
			v3.z = p4->z - p1->z;

			incx = v3.y*v1.z - v3.z*v1.y;
			incy = v3.z*v1.x - v3.x*v1.z;
			incz = v3.x*v1.y - v3.y*v1.x;

			norme = incx*incx + incy*incy + incz*incz;
			root =(float)( 1.0f/(float)sqrt(norme+0.000001) );
			incx *= root;
			incy *= root;
			incz *= root;

			p1->n.x += incx;
			p1->n.y += incy;
			p1->n.z += incz;

			p3->n.x += incx;
			p3->n.y += incy;
			p3->n.z += incz;

			p4->n.x += incx;
			p4->n.y += incy;
			p4->n.z += incz;

			mesh.m_facesList[face].a = j*(m_nTerrainSubdivision+1) + i; // p1
			mesh.m_facesList[face].c = (j+1)*(m_nTerrainSubdivision+1) + (i+1); // p3
			mesh.m_facesList[face].b = (j+1)*(m_nTerrainSubdivision+1) + i; // p4
			mesh.m_facesList[face].n.x = incx;
			mesh.m_facesList[face].n.y = incy;
			mesh.m_facesList[face].n.z = incz;
			face++;

		}
	}

	// Normalisation des normales ///////////////////////////////////////
	for( j=0; j<m_nTerrainSubdivision+1; j++ )
	{
		for( i=0; i<m_nTerrainSubdivision+1; i++ )
		{
			mesh.m_verticesList[j*(m_nTerrainSubdivision+1) + i].n.normalize();
		}
	}
}

///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
