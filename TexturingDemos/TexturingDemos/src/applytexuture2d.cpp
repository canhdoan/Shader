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

ApplyTexture2D::ApplyTexture2D(void) :
 m_pShader(NULL),
 m_nVAO(0),
 m_nVertexVBO(0),
 m_nNormalVBO(0),
 m_nUVVBO(0),
 m_nIndicesVBO(0),
 m_nVertexLoc(-1),
 m_nNormalLoc(-1),
 m_nUVLoc(-1),
 m_mViewMatrix(mat4(0)),
 m_mModelMatrix(mat4(0)),
 m_mProjectionMatrix(mat4(0)),
 m_mNormalMatrix(mat3(0))
{
	// TODO: Construct
}

///////////////////////////////////////////////////////////////////////////////

ApplyTexture2D::~ApplyTexture2D(void)
{
	Terminate();
}

///////////////////////////////////////////////////////////////////////////////

void ApplyTexture2D::Construct(void)
{
	// Load 3D model from file .obj
	Load3DObj::LoadObjModel("data/objects/...", &m_Object);
	
	// Init shader program
	char *pVertex = "data/shaders/default.vs";
	char *pFragment = "data/shaders/default.fs";

	m_pShader = new Shader();
	m_pShader->Construct(pVertex, pFragment);
	if (!m_pShader->Link())
	{
		printf("ERROR: Can not link shader program!");
		exit(0);
	}
	// User program
	m_pShader->Use(true);
	// Get location of attribute
	m_nVertexLoc = m_pShader->GetAttributeLocation("attr_vertex");
	m_nNormalLoc = m_pShader->GetAttributeLocation("attr_normal");
	m_nUVLoc = m_pShader->GetAttributeLocation("attr_uv");

	// Gen vertex array and vertex buffer object
	glGenVertexArrays(1, &m_nVAO);
	glGenBuffers(1, &m_nVertexVBO);
	glGenBuffers(1, &m_nNormalVBO);
	glGenBuffers(1, &m_nUVVBO);
	glGenBuffers(1, &m_nIndicesVBO);

	// Bind data
	glBindVertexArray(m_nVAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_nVertexVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*3*m_Object.num_vertices,
			&m_Object.vertex[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(m_nVertexLoc);
		glVertexAttribPointer(m_nVertexLoc, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*3, 0);

		glBindBuffer(GL_ARRAY_BUFFER, m_nNormalVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*3*m_Object.num_vertices, 
			&m_Object.normal[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(m_nNormalLoc);
		glVertexAttribPointer(m_nNormalLoc, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*3, 0);

		glBindBuffer(GL_ARRAY_BUFFER, m_nUVVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*2*m_Object.num_vertices, 
			&m_Object.textcoord[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(m_nUVLoc);
		glVertexAttribPointer(m_nUVLoc, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*3, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_nIndicesVBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*3*m_Object.num_polygons,
			&m_Object.polygon[0], GL_STATIC_DRAW);
	glBindVertexArray(0);
}

///////////////////////////////////////////////////////////////////////////////

void ApplyTexture2D::Terminate(void)
{
	glDeleteBuffers(1, &m_nVertexVBO);
	glDeleteBuffers(1, &m_nNormalVBO);
	glDeleteBuffers(1, &m_nUVVBO);
	glDeleteBuffers(1, &m_nIndicesVBO);
	glDeleteVertexArrays(1, &m_nVAO);
	free(m_pShader);
	m_pShader = NULL;
}

///////////////////////////////////////////////////////////////////////////////

void ApplyTexture2D::Update(int w, int h)
{
	m_mProjectionMatrix = perspective(90.0f, (GLfloat)w/h, 10.f, 10000.f);
}

///////////////////////////////////////////////////////////////////////////////

void ApplyTexture2D::Render(void)
{
	glClear(GL_COLO_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//
}

///////////////////////////////////////////////////////////////////////////////
