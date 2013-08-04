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

#ifndef APP_SINGLELIGHT_H
#define APP_SINGLELIGHT_H

/**
 * This class is an simple example about lighting effect with shader
 * It's only use diffuse component for this demo.
 * Class contains default methods, for instance Construct, Destruct,
 * Update, Render.
 */
class SingleLight
{
public:
	/**
	 * The constructor for this class
	 */
	SingleLight(void);

	/**
	 * The destructor for this class
	 */
	~SingleLight(void);

	/**
	 * Contruct method of this class
	 */
	void Construct(void);

	/**
	 * Update method
	 */
	void Update(int w, int h);

	/*
	 * Render method
	 */
	void Render(void);

private:
	// Shader program
	Shader			*m_pShader;
	// Object
	OBJECT_3DS		m_Object;
	// List attribute location
	GLuint			m_nVertexLoc;
	GLuint			m_nNormalLoc;
	// List vertex buffer
	GLuint 			m_nVertexVAO;
	GLuint			m_nVerticesVBO;
	GLuint			m_nNormalVBO;
	GLuint			m_nIndicesVBO;
	// Variable for storage data of uniform
	glm::vec4		m_vLightPos;
	glm::vec3 		m_vDiffuse; // Kd: diffuse reflectivity (diffuse color)
	glm::vec3 		m_vLight; // Ld: light intensity (light color)

	glm::mat4 		m_mModelViewMatrix; // Model-View matrix
	glm::mat3 		m_mNormalMatrix; // Normal matrix
	glm::mat4		m_mProjectionMatrix; // Projection matrix
	glm::mat4 		m_mMVPMatrix; // Model-View-Projection matrix
	// Internal matrix
	glm::mat4		m_mTranslate;
	glm::mat4		m_mRotateX;
	glm::mat4		m_mRotateY;
};

#endif // APP_SINGLELIGHT_H

///////////////////////////////////////////////////////////////////////////////
