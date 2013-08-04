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

SingleLight::SingleLight(void) :
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

SingleLight::~SingleLight(void)
{
	free(m_pShader);
	m_pShader = NULL;
	glDeleteBuffers(1, &m_nVerticesVBO);
	glDeleteBuffers(1, &m_nNormalVBO);
	glDeleteBuffers(1, &m_nIndicesVBO);
	glDeleteVertexArrays(1, &m_nVertexVAO);
}

///////////////////////////////////////////////////////////////////////////////

void SingleLight::Construct(void)
{
	// Init 3ds model object
	Load3DObj::Load3dsModel("data/objects/spaceship.3DS", &m_Object);
	Load3DObj::CalcNormalVector(&m_Object);
	// Init data for update uniform
	m_vLightPos = glm::vec4(100.0f, 0.0f, -10.0f, 1.0f);
	m_vDiffuse = glm::vec3(0.2f, 0.6f, 0.1f);
	m_vLight = glm::vec3(1.0f, 1.0f, 1.0f);

	// Init shader program
	char *pVertex = "data/shaders/singlelight.vs";
	char *pFragment = "data/shaders/singlelight.fs";
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

void SingleLight::Update(int w, int h)
{
	m_mProjectionMatrix = glm::perspective(90.0f, (GLfloat)w/h, 10.f, 10000.f);
}

///////////////////////////////////////////////////////////////////////////////

void SingleLight::Render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Update data for uniform
	m_mTranslate = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f, 0.0f, -300));
    m_mRotateX = glm::rotate(m_mTranslate,  rotation_x, glm::vec3(1.0f, 0.0f, 0.0f));
    m_mRotateY = glm::rotate(m_mRotateX, rotation_y, glm::vec3(0.0f, 1.0f, 0.0f));
    m_mModelViewMatrix = glm::rotate(m_mRotateY, rotation_z, glm::vec3(0.0f, 0.0f, 1.0f));
    m_mMVPMatrix = m_mProjectionMatrix*m_mModelViewMatrix;

    glBindVertexArray(m_nVertexVAO);
    // Use program
	m_pShader->Use(true);
	m_pShader->SetUniform("uni_light_position", m_vLightPos);
	m_pShader->SetUniform("uni_diffuse_color", m_vDiffuse);
	m_pShader->SetUniform("uni_light_color", m_vLight);

	m_pShader->SetUniform("uni_mvmatrix", m_mModelViewMatrix);
	m_pShader->SetUniform("uni_normalmatrix", m_mNormalMatrix);
	// m_pShader->SetUniform("uni_projectionmatrix", m_mProjectionMatrix);
	m_pShader->SetUniform("uni_mvpmatrix", m_mMVPMatrix);

	glDrawElements(GL_TRIANGLES, m_Object.num_polygons*3, GL_UNSIGNED_SHORT, 0);
	m_pShader->Use(false);
	glutSwapBuffers();
}

///////////////////////////////////////////////////////////////////////////////
