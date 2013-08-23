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
	 * The constructor for this class
	 */
	Terrain(void);

	/**
	 * The destructor for this class
	 */
	~Terrain(void);

	/**
	 * The construct method
	 */
	void Terrain(void);

	/**
	 * The termial method
	 */
	void Terminal(void);


public:
	/**
	 * 
	 */
	void ConvertToGrayScale(void);

	/**
	 *
	 */
	void CreateTerrain(void);


private:
	// Terrain pointer
	float		m_pTerrain[256 * 256];

	// Map pixel
	RGBbytepixel *m_pPixelMap;

	// Verticale scale value
	float 		m_fVerticlaScale;

	// number of subdivision
	int 		m_nTerrainSubdivision;
};


#endif // APP_TERRAIN_H

///////////////////////////////////////////////////////////////////////////////
