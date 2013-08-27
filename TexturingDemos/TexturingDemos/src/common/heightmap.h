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

#ifndef APP_COMMON_HEIGHTMAP_H
#define APP_COMMON_HEIGHTMAP_H

class HeightMap
{
public:
	/**
	 * The constructor of this class
	 */
	HeightMap(void);

	/**
	 * The destructor of this class
	 */
	~HeightMap(void) { Terminal(); }

	/**
	 * The construct method
	 */
	void Construct(int nSize, int nGrid, float fVerScale);

	/**
	 * The terminal method
	 */
	void Terminal(void);


public:
	/**
	 * Get methods
	 */
	int GetSize(void) { return m_nSize; }
	int GetGridSpacing(void) { return m_nGridSpacing; }
	float *GetHeight(void) { return m_pHeightMap; }
	float GetHeightAt(float &fX, float &fZ);
	float GetHeightAtIndex(int &nX, int &nZ);
	void GetNormalAt(float &fX, float &fZ, vec3 &vNormal);
	void GetNormalAtIndex(int &nX, int &nZ, vec &vNormal);
	
	/**
	 * Method return the index of height map from the height map coordinate
	 * that it's pass through nX & nZ. This method works around the height map
	 * have coordinate large than height map size.
	 *
	 * @param nX: the x coordinate of height map
	 * @param nZ: the z coordinate of height map
	 */
	int GetHeightIndexAt(int &nX, int &nZ);


private:
	/**
	 * Generation height map use the Diamond Square algorithm
	 */
	void GenerationDiamondSquareFractal(void);

	/**
	 * Blur function for heightmap
	 */
	void Blur(void);

	/**
	 * Smooth function for heightmap
	 */
	void Smooth(void);


private:
	// Size of height map
	int 				m_nSize;
	// Number of grid spacing
	int 				m_nGridSpacing;
	// Vertical scale
	float 				m_fVerticalScale;
	// Height map array
	float 				*m_pHeightMap;
};


#endif // APP_COMMON_HEIGHTMAP_H

///////////////////////////////////////////////////////////////////////////////
