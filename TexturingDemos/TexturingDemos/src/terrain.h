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

#ifndef APP_TERRAIN_H
#define APP_TERRAIN_H

class Terrain
{
public:
	/**
	 * The constructor of this class
	 */
	Terrain(void);

	/**
	 * The destructor of this class
	 */
	~Terrain(void) { Terminal(); }

	/**
	 * The construct method
	 */
	void Construct(int nSize, int nGrid, float fScale);

	/**
	 * The terminal method
	 */
	void Terminal(void);


public:
	/**
	 * Update method
	 */
	void OnUpdate(/*vec3 vCameraPos*/);


	/**
	 * Render method
	 */
	void OnRender(void);


private:
	/**
	 * Generate indices
	 */
	bool GenerateIndices(void);

	/**
	 * Generate vertices
	 */
	bool GenerateVertices(void);


private:
	// Vertex buffer object
	unsigned int 		m_nVertexVBO;
	// Index buffer object
	unsigned int 		m_nIndexVBO;
	// Total vertices & indices
	int 				m_nTotalVertices;
	int 				m_nTotalIndices;
	// Height map object
	HeightMap 			*m_pHeightMap;
};


#endif // APP_TERRAIN_H

///////////////////////////////////////////////////////////////////////////////
