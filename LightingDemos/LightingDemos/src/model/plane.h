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

#ifndef APP_MODEL_PLANE_H
#define APP_MODEL_PLANE_H

class Plane
{
public:
	/**
	 * The constructor for this class
	 */
	Plane(void);

	/**
	 * The destructor for this class
	 */
	~Plane(void);

	/**
	 * Construct method
	 */
	void Construct(float xsize, float zsize, int xdivs, int zdivs);

	/**
	 * Render method
	 */
	void Render(void);

private:
	// Vertex array object
	GLuint m_nVAO;
	// Number of faces
	unsigned int m_nFaces;
};

#endif // APP_MODEL_PLANE_H

///////////////////////////////////////////////////////////////////////////////
