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

#ifndef APP_MULTILIGHT_H
#define APP_MULTILIGHT_H

class MultiLight
{
public:
	/**
	 * The constructor for this class
	 */
	MultiLight(void);

	/**
	 * The destructor for this class
	 */
	~MultiLight(void);

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
	// Shader program
	Shader			*m_pShader;
	// Object
	OBJECT_3DS		m_Object;
	// List vertex buffer

	// Variable for uniform

	
};

#endif // APP_MULTILIGHT_H

///////////////////////////////////////////////////////////////////////////////
