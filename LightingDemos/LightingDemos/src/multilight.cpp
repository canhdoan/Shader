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

MultiLight::MultiLight(void):
 m_pShader(NULL),
 m_nVertexLoc(-1),
 m_nNormalLoc(-1),
 m_nVertexVAO(0),
 m_nVerticesVBO(0),
 m_nNormalVBO(0),
 m_nIndicesVBO(0)
{

}

///////////////////////////////////////////////////////////////////////////////

MultiLight::~MultiLight(void)
{
	free(m_pShader);
	m_pShader = NULL;
	glDeleteBuffers(1, &m_nVerticesVBO);
	glDeleteBuffers(1, &m_nNormalVBO);
	glDeleteBuffers(1, &m_nIndicesVBO);
	glDeleteVertexArrays(1, &m_nVertexVAO);
}

///////////////////////////////////////////////////////////////////////////////

void MultiLight::Construct(void)
{
	// Initialize 3ds model
	Load3DObj::Load3dsModel("data/objects/spaceship.3DS", &m_Object);
	Load3DObj::CalcNormalVector(&m_Object);
	// Initialize all light data
	m_vLight0 = glm::vec3(0.0f, 0.8f, 0.8f);
	m_vLight1 = glm::vec3(0.0f, 0.0f, 0.8f);
	m_vLight2 = glm::vec3(0.8f, 0.0f, 0.0f);
	m_vLight3 = glm::vec3(0.0f, 0.8f, 0.0f);
	m_vLight4 = glm::vec3(0.8f, 0.8f, 0.8f);
	m_fAngle = 0.0f;

	// Set view matrix
	m_mViewMatrix = glm::lookAt(glm::vec3(0.5f, 0.75f, 0.75f), 
		glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	// Initialize shader program
	// char *pVertex = "data/shaders/multilight.vs";
	// char *pFragment = "data/shaders/multilight.fs";
	// char *pVertex = "data/shaders/phongshading.vs";
	// char *pFragment = "data/shaders/phongshading.fs";
	char *pVertex = "data/shaders/spotlight.vs";
	char *pFragment = "data/shaders/spotlight.fs";
	m_pShader = new Shader();
	m_pShader->Construct(pVertex, pFragment);
	if (!m_pShader->Link())
	{
		printf("ERROR: Can not link shader program!");
		exit(0);
	}
	// Use program
	m_pShader->Use(true);
	// Get location of attributes
	m_nVertexLoc = m_pShader->GetAttributeLocation("VertexPosition");
	m_nNormalLoc = m_pShader->GetAttributeLocation("VertexNormal");

	// Create vertex array and vertex buffer object
	glGenVertexArrays(1, &m_nVertexVAO);
	glGenBuffers(1, &m_nVerticesVBO);
	glGenBuffers(1, &m_nNormalVBO);
	glGenBuffers(1, &m_nIndicesVBO);

	// Bind data
	glBindVertexArray(m_nVertexVAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_nVerticesVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*3*m_Object.num_vertices, 
			&m_Object.vertex[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(m_nVertexLoc);
		glVertexAttribPointer(m_nVertexLoc, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*3, 0);

		glBindBuffer(GL_ARRAY_BUFFER, m_nNormalVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*3*m_Object.num_vertices, 
			&m_Object.normal[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(m_nNormalLoc);
		glVertexAttribPointer(m_nNormalLoc, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*3, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_nIndicesVBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*3*m_Object.num_polygons, &m_Object.polygon[0], GL_STATIC_DRAW);
    glBindVertexArray(0);
    // Unuse program
    m_pShader->Use(false);
}

///////////////////////////////////////////////////////////////////////////////

void MultiLight::Update(int w, int h)
{
	m_fAngle += 0.01f;
    if( m_fAngle > TWOPI) m_fAngle -= TWOPI;

	m_mProjectionMatrix = glm::perspective(70.0f, (GLfloat)w/h, 10.0f, 10000.f);
}

///////////////////////////////////////////////////////////////////////////////

void MultiLight::Render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//-------------------------------------------------------------------------------------
	// Code for multi-light demo
	// Update data for uniform
	// m_mTranslate = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f, 0.0f, -300));
 	// m_mRotateX = glm::rotate(m_mTranslate,  rotation_x, glm::vec3(1.0f, 0.0f, 0.0f));
 	// m_mRotateY = glm::rotate(m_mRotateX, rotation_y, glm::vec3(0.0f, 1.0f, 0.0f));
 	// m_mModelViewMatrix = glm::rotate(m_mRotateY, rotation_z, glm::vec3(0.0f, 0.0f, 1.0f));
 	// m_mMVPMatrix = m_mProjectionMatrix*m_mModelViewMatrix;

 	// glBindVertexArray(m_nVertexVAO);
 	// // Use program
	// m_pShader->Use(true);
	// // Set uniform for light
	// // Set position
	// char name[256];
	// glm::vec4 vLightPosition = glm::vec4(0.0);
	// float x, z;
	// for (int i = 0; i < 5; i++)
	// {
	// 	_snprintf(name, 256, "uni_lights[%d].Position", i);
	// 	x = 2.0f * cos((TWOPI/5) * i);
	// 	z = 2.0f * sin((TWOPI/5) * i);
	// 	vLightPosition = m_mViewMatrix*glm::vec4(x, 1.2f, z+1.0f, 1.0f);
	// 	m_pShader->SetUniform(name, vLightPosition);
	// }
	// // Set light intensity
	// m_pShader->SetUniform("uni_lights[0].Intensity", m_vLight0);
	// m_pShader->SetUniform("uni_lights[1].Intensity", m_vLight1);
	// m_pShader->SetUniform("uni_lights[2].Intensity", m_vLight2);
	// m_pShader->SetUniform("uni_lights[3].Intensity", m_vLight3);
	// m_pShader->SetUniform("uni_lights[4].Intensity", m_vLight4);

	// // Set uniform for material of light
	// m_pShader->SetUniform("Kd", 0.4f, 0.4f, 0.4f);
 	// m_pShader->SetUniform("Ks", 0.9f, 0.9f, 0.9f);
 	// m_pShader->SetUniform("Ka", 0.1f, 0.1f, 0.1f);
 	// m_pShader->SetUniform("Shininess", 180.0f);

	// // Set uniform for transform matrix
	// m_pShader->SetUniform("uni_mvmatrix", m_mModelViewMatrix);
	// m_pShader->SetUniform("uni_normalmatrix", m_mNormalMatrix);
	// m_pShader->SetUniform("uni_mvpmatrix", m_mMVPMatrix);

	// glDrawElements(GL_TRIANGLES, m_Object.num_polygons*3, GL_UNSIGNED_SHORT, 0);
	// m_pShader->Use(false);
	// glutSwapBuffers();
	//-------------------------------------------------------------------------------------


	//-------------------------------------------------------------------------------------
	// Code for Phong shading demo
	// Update data for uniform
	// m_mTranslate = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f, 0.0f, -300));
	// m_mRotateX = glm::rotate(m_mTranslate,  309.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	// m_mRotateY = glm::rotate(m_mRotateX, 333.5f, glm::vec3(0.0f, 1.0f, 0.0f));
	// m_mModelViewMatrix = glm::rotate(m_mRotateY, 200.123f, glm::vec3(0.0f, 0.0f, 1.0f));
	// m_mMVPMatrix = m_mProjectionMatrix*m_mModelViewMatrix;

	// glBindVertexArray(m_nVertexVAO);
	// // Use program
	// m_pShader->Use(true);
	// // Set uniform for light
	// // Set position
	// glm::vec4 vLightPosition = glm::vec4(0.0);
	// float x, z;
	// x = 2.0f * cos((TWOPI/5));
	// z = 2.0f * sin((TWOPI/5));
	// vLightPosition = m_mViewMatrix*glm::vec4(x, 1.2f, z+1.0f, 1.0f);
	// m_pShader->SetUniform("LightPosition", vLightPosition);
	// // Set light intensity
	// m_pShader->SetUniform("LightIntensity", m_vLight0);

	// // Set uniform for material of light
	// m_pShader->SetUniform("Kd", 0.4f, 0.4f, 0.4f);
	// m_pShader->SetUniform("Ks", 0.9f, 0.9f, 0.9f);
	// m_pShader->SetUniform("Ka", 0.1f, 0.1f, 0.1f);
	// m_pShader->SetUniform("Shininess", 180.0f);

	// // Set uniform for transform matrix
	// m_pShader->SetUniform("ModelViewMatrix", m_mModelViewMatrix);
	// m_pShader->SetUniform("NormalMatrix", m_mNormalMatrix);
	// m_pShader->SetUniform("MVP", m_mMVPMatrix);

	// glDrawElements(GL_TRIANGLES, m_Object.num_polygons*3, GL_UNSIGNED_SHORT, 0);
	// m_pShader->Use(false);
	// glutSwapBuffers();
	//-------------------------------------------------------------------------------------


	//-------------------------------------------------------------------------------------
	// Code for Spotlight shading demo
	// Update data for uniform
	m_mTranslate = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f, 0.0f, -300));
	m_mRotateX = glm::rotate(m_mTranslate,  309.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	m_mRotateY = glm::rotate(m_mRotateX, 333.5f, glm::vec3(0.0f, 1.0f, 0.0f));
	m_mModelViewMatrix = glm::rotate(m_mRotateY, 200.123f, glm::vec3(0.0f, 0.0f, 1.0f));
	m_mMVPMatrix = m_mProjectionMatrix*m_mModelViewMatrix;

	glBindVertexArray(m_nVertexVAO);
	// Use program
	m_pShader->Use(true);
	// Set uniform for light
	glm::vec4 lightPos = glm::vec4(10.0f * glm::cos(m_fAngle), 10.0f, 10.0f * glm::sin(m_fAngle), 1.0f);
    m_pShader->SetUniform("SpotLight.Position", m_mViewMatrix * lightPos);
    glm::mat3 normalMatrix = glm::mat3( glm::vec3(m_mViewMatrix[0]), glm::vec3(m_mViewMatrix[1]), glm::vec3(m_mViewMatrix[2]));
	m_pShader->SetUniform("SpotLight.Direction", normalMatrix * glm::vec3(-lightPos));

	m_pShader->SetUniform("SpotLight.Intensity", glm::vec3(0.9f,0.9f,0.9f) );
    m_pShader->SetUniform("SpotLight.Exponent", 30.0f );
    m_pShader->SetUniform("SpotLight.Cutoff", 15.0f );

	// Set uniform for material of light
	m_pShader->SetUniform("Kd", 0.9f, 0.5f, 0.3f);
	m_pShader->SetUniform("Ks", 0.95f, 0.95f, 0.95f);
	m_pShader->SetUniform("Ka", 0.9f * 0.3f, 0.5f * 0.3f, 0.3f * 0.3f);
	m_pShader->SetUniform("Shininess", 100.0f);

	// Set uniform for transform matrix
	m_pShader->SetUniform("ModelViewMatrix", m_mModelViewMatrix);
	m_pShader->SetUniform("NormalMatrix", m_mNormalMatrix);
	m_pShader->SetUniform("MVP", m_mMVPMatrix);

	glDrawElements(GL_TRIANGLES, m_Object.num_polygons*3, GL_UNSIGNED_SHORT, 0);
	m_pShader->Use(false);
	glutSwapBuffers();
	//-------------------------------------------------------------------------------------
}

///////////////////////////////////////////////////////////////////////////////
