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

#ifndef APP_ADSSHADING_H
#define APP_ADSSHADING_H

/**
 * ADS is abbreviato of Ambient-Diffuse-Specular
 * This is an example about ADS effect, it's use all three components
 * ambient, diffuse and specular.
 */
class ADSShading
{
public:
	/**
	 * The constructor for this class
	 */
	ADSShading(void);

	/**
	 * The destructor of this class
	 */
	~ADSShading(void);

	/**
	 * The construct method
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
	Shader				*m_pShader;
	// Object to render
	OBJECT_3DS			m_Object;
	// List attributes location
	GLuint				m_nVertexLoc;
	GLuint				m_nNormalLoc;
	// List vertex buffer
	GLuint				m_nVertexVAO;
	GLuint				m_nVerticesVBO;
	GLuint				m_nNormalVBO;
	GLuint				m_nIndicesVBO;
	// Variable for storage data of uniform
	vec4				m_vLightPos;
	mat4 				m_mModelViewMatrix; // Model-View matrix
	mat3 				m_mNormalMatrix; // Normal matrix
	mat4				m_mProjectionMatrix; // Projection matrix
	mat4 				m_mMVPMatrix; // Model-View-Projection matrix
	// Internal matrix
	mat4				m_mTranslate;
	mat4				m_mRotateX;
	mat4				m_mRotateY;
};


#endif // APP_ADSSHADING_H

///////////////////////////////////////////////////////////////////////////////