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