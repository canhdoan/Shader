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

#ifndef APP_SPOTLIGHT_H
#define APP_SPOTLIGHT_H

class Spotlight
{
public:
	/**
	 * The constructor for this class
	 */
	Spotlight(void);

	/**
	 * The destructor for this class
	 */
	~Spotlight(void);

	/**
	 * Construct method
	 */
	void Construct(void);

	/**
	 * Update method
	 */
	void Update(int w, int h);

	/**
	 * Render method
	 */
	void Render(void);


private:
	void SetMatrices(void);


private:
	// Shader program
	Shader			*m_pShader;
	// Object model
	Plane			*m_pPlane;
	Teapot			*m_pTeapot;
	Torus			*m_pTorus;

	// Matrix transpose
	mat4			m_mModelMatrix;
	mat4			m_mViewMatrix;
	mat4			m_mProjectionMatrix;
};

#endif // APP_SPOTLIGHT_H

///////////////////////////////////////////////////////////////////////////////
