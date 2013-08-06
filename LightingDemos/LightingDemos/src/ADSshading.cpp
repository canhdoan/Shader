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

ADSShading::ADSShading(void) :
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

ADSShading::~ADSShading(void)
{
	// Release shader object
	free(m_pShader);
	m_pShader = NULL;
	glDeleteBuffers(1, &m_nVerticesVBO);
	glDeleteBuffers(1, &m_nNormalVBO);
	glDeleteBuffers(1, &m_nIndicesVBO);
	glDeleteVertexArrays(1, &m_nVertexVAO);
}

///////////////////////////////////////////////////////////////////////////////

void ADSShading::Construct(void)
{
	// Initialize object from file .3ds
	Load3DObj::Load3dsModel("data/objects/spaceship.3DS", &m_Object);
	Load3DObj::CalcNormalVector(&m_Object);
	// Init data for uniform
	m_vLightPos = vec4(2.0f,4.0f,1.0f,1.0f);
	// Initialize shader program
	char *pVertex = "data/shaders/adsshading.vs"; // Use the vertex shader without function called
	// char *pVertex = "data/shaders/adsshading_usingfunction.vs"; // Use the vertex shader with function called
	// char *pVertex = "data/shaders/adstwosideshading.vs"; // Use the vertex shader for render front and back face of model
	// char *pVertex = "data/shaders/adsshading_subroutine.vs"; // Use the vertex shader with subroutine

	char *pFragment = "data/shaders/adsshading.fs";
	// char *pFragment = "data/shaders/adstwosideshading.fs"; // Use the fragment shader for render front and back face of model
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
	m_nVertexLoc = m_pShader->GetAttributeLocation("attr_vertex");
	m_nNormalLoc = m_pShader->GetAttributeLocation("attr_normal");
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
}

///////////////////////////////////////////////////////////////////////////////

void ADSShading::Update(int w, int h)
{
	m_mProjectionMatrix = perspective(90.0f, (GLfloat)w/h, 10.f, 10000.f);
}

///////////////////////////////////////////////////////////////////////////////

void ADSShading::Render(void)
{
	//-------------------------------------------------------------------------------------
	// Code render for normal example
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Update data for uniform
	m_mTranslate = translate(mat4(1.0f),vec3(0.0f, 0.0f, -300));
	m_mRotateX = rotate(m_mTranslate,  rotation_x, vec3(1.0f, 0.0f, 0.0f));
	m_mRotateY = rotate(m_mRotateX, rotation_y, vec3(0.0f, 1.0f, 0.0f));
	m_mModelViewMatrix = rotate(m_mRotateY, rotation_z, vec3(0.0f, 0.0f, 1.0f));
	m_mMVPMatrix = m_mProjectionMatrix*m_mModelViewMatrix;
	glBindVertexArray(m_nVertexVAO);
	// Use program
	m_pShader->Use(true);
	// Set light uniform
	m_pShader->SetUniform("uni_light.Position", &m_vLightPos);
	m_pShader->SetUniform("uni_light.La", 0.4f, 0.4f, 0.4f);
	m_pShader->SetUniform("uni_light.Ld", 1.0f, 1.0f, 1.0f);
	m_pShader->SetUniform("uni_light.Ls", 1.0f, 1.0f, 1.0f);
	// Set matrial uniform
	m_pShader->SetUniform("uni_material.Ka", 0.9f, 0.5f, 0.3f);
	m_pShader->SetUniform("uni_material.Kd", 0.9f, 0.5f, 0.3f);
	m_pShader->SetUniform("uni_material.Ks", 0.8f, 0.8f, 0.8f);
	m_pShader->SetUniform("uni_material.Shininess", 100.0f);
	// Set matrix transform matrix
	m_pShader->SetUniform("uni_mvmatrix", m_mModelViewMatrix);
	m_pShader->SetUniform("uni_normalmatrix", m_mNormalMatrix);
	m_pShader->SetUniform("uni_mvpmatrix", m_mMVPMatrix);

	glDrawElements(GL_TRIANGLES, m_Object.num_polygons*3, GL_UNSIGNED_SHORT, 0);
	m_pShader->Use(false);
	glutSwapBuffers();
	//-------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------
	// Code render for example use subroutine
	// m_pShader->Use(true);
	// glBindVertexArray(m_nVertexVAO);

	// // Render left model
	// // Update data for uniform
	// m_mTranslate = translate(mat4(1.0f),vec3(-10.0f, 0.0f, -300));
	// m_mRotateX = rotate(m_mTranslate,  rotation_x, vec3(1.0f, 0.0f, 0.0f));
	// m_mRotateY = rotate(m_mRotateX, rotation_y, vec3(0.0f, 1.0f, 0.0f));
	// m_mModelViewMatrix = rotate(m_mRotateY, rotation_z, vec3(0.0f, 0.0f, 1.0f));
	// m_mMVPMatrix = m_mProjectionMatrix*m_mModelViewMatrix;
	// // Set ads method
	// GLuint nADSIndex = m_pShader->GetSubroutine(GLSLShader::GLSLShaderType::VERTEX, "PhongModel");
	// glUniformSubroutinesuiv( GL_VERTEX_SHADER, 1, &nADSIndex);
	// // Set light uniform
	// m_pShader->SetUniform("uni_light.Position", &m_vLightPos);
	// m_pShader->SetUniform("uni_light.La", 0.4f, 0.4f, 0.4f);
	// m_pShader->SetUniform("uni_light.Ld", 1.0f, 1.0f, 1.0f);
	// m_pShader->SetUniform("uni_light.Ls", 1.0f, 1.0f, 1.0f);
	// // Set matrial uniform
	// m_pShader->SetUniform("uni_material.Ka", 0.9f, 0.5f, 0.3f);
	// m_pShader->SetUniform("uni_material.Kd", 0.9f, 0.5f, 0.3f);
	// m_pShader->SetUniform("uni_material.Ks", 0.8f, 0.8f, 0.8f);
	// m_pShader->SetUniform("uni_material.Shininess", 100.0f);
	// // Set matrix transform matrix
	// m_pShader->SetUniform("uni_mvmatrix", m_mModelViewMatrix);
	// m_pShader->SetUniform("uni_normalmatrix", m_mNormalMatrix);
	// m_pShader->SetUniform("uni_mvpmatrix", m_mMVPMatrix);
	// glDrawElements(GL_TRIANGLES, m_Object.num_polygons*3, GL_UNSIGNED_SHORT, 0);

	// // Render right model
	// // Set ads method
	// GLuint nDiffuseIndex = m_pShader->GetSubroutine(GLSLShader::GLSLShaderType::VERTEX, "DiffuseOnly");
	// glUniformSubroutinesuiv( GL_VERTEX_SHADER, 1, &nDiffuseIndex);
	// // Update data for uniform
	// m_mTranslate = translate(mat4(1.0f),vec3(10.0f, 0.0f, -300));
	// m_mRotateX = rotate(m_mTranslate,  rotation_x, vec3(1.0f, 0.0f, 0.0f));
	// m_mRotateY = rotate(m_mRotateX, rotation_y, vec3(0.0f, 1.0f, 0.0f));
	// m_mModelViewMatrix = rotate(m_mRotateY, rotation_z, vec3(0.0f, 0.0f, 1.0f));
	// m_mMVPMatrix = m_mProjectionMatrix*m_mModelViewMatrix;
	// // Set matrix transform matrix
	// m_pShader->SetUniform("uni_mvmatrix", m_mModelViewMatrix);
	// m_pShader->SetUniform("uni_normalmatrix", m_mNormalMatrix);
	// m_pShader->SetUniform("uni_mvpmatrix", m_mMVPMatrix);
	// glDrawElements(GL_TRIANGLES, m_Object.num_polygons*3, GL_UNSIGNED_SHORT, 0);

	// m_pShader->Use(false);
	// glutSwapBuffers();
}

///////////////////////////////////////////////////////////////////////////////
