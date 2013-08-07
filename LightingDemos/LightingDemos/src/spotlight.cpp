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

Spotlight::Spotlight(void):
 m_pShader(NULL)
{

}

///////////////////////////////////////////////////////////////////////////////

Spotlight::~Spotlight(void)
{
	free(m_pShader);
	m_pShader = NULL;
}

///////////////////////////////////////////////////////////////////////////////

void Spotlight::Construct(void)
{
	// Initialize object model
	m_pPlane = new Plane();
	m_pTeapot = new Teapot();
	m_pTorus = new Torus();
	m_pPlane->Construct(50.0f, 50.0f, 1, 1);
    m_pTeapot->Construct(14, glm::mat4(1.0f));
    m_pTorus->Construct(1.75f * 0.75f, 0.75f * 0.75f, 50, 50);

	// Set view matrix
	m_mViewMatrix = glm::lookAt(vec3(5.0f,5.0f,7.5f), vec3(0.0f,0.75f,0.0f), vec3(0.0f,1.0f,0.0f));
	m_mProjectionMatrix = mat4(1.0f);

	// Initialize shader program
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

	m_pShader->SetUniform("SpotLight.Intensity", 0.9f, 0.9f, 0.9f);
    m_pShader->SetUniform("SpotLight.Exponent", 30.0f);
    m_pShader->SetUniform("SpotLight.Cutoff", 15.0f);

    // Unuse program
    m_pShader->Use(false);
}

///////////////////////////////////////////////////////////////////////////////

void Spotlight::Update(int w, int h)
{
	m_mProjectionMatrix = perspective(60.0f, (float)w/h, 0.3f, 100.0f);
}

///////////////////////////////////////////////////////////////////////////////

void Spotlight::Render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_pShader->Use(true);

	vec4 lightPos = vec4(10.0f * cos(g_fAngle), 10.0f, 10.0f * sin(g_fAngle), 1.0f);
    m_pShader->SetUniform("SpotLight.Position", m_mViewMatrix * lightPos);
    mat3 normalMatrix = mat3( vec3(m_mViewMatrix[0]), vec3(m_mViewMatrix[1]), vec3(m_mViewMatrix[2]) );
    m_pShader->SetUniform("SpotLight.Direction", normalMatrix * vec3(-lightPos) );

    m_pShader->SetUniform("Kd", 0.9f, 0.5f, 0.3f);
    m_pShader->SetUniform("Ks", 0.95f, 0.95f, 0.95f);
    m_pShader->SetUniform("Ka", 0.9f * 0.3f, 0.5f * 0.3f, 0.3f * 0.3f);
    m_pShader->SetUniform("Shininess", 100.0f);

    m_mModelMatrix = mat4(1.0f);
    m_mModelMatrix = glm::translate(m_mModelMatrix, vec3(0.0f,0.0f,-2.0f));
    m_mModelMatrix = glm::rotate(m_mModelMatrix, 45.0f, vec3(0.0f,1.0f,0.0f));
    m_mModelMatrix = glm::rotate(m_mModelMatrix, -90.0f, vec3(1.0f,0.0f,0.0f));
    SetMatrices();
    m_pTeapot->Render();

    // m_pShader->SetUniform("Kd", 0.9f, 0.5f, 0.3f);
    // m_pShader->SetUniform("Ks", 0.95f, 0.95f, 0.95f);
    // m_pShader->SetUniform("Ka", 0.9f * 0.3f, 0.5f * 0.3f, 0.3f * 0.3f);
    // m_pShader->SetUniform("Shininess", 100.0f);

    // m_mModelMatrix = mat4(1.0f);
    // m_mModelMatrix = glm::translate(m_mModelMatrix, vec3(-1.0f,0.75f,3.0f));
    // m_mModelMatrix = glm::rotate(m_mModelMatrix, -90.0f, vec3(1.0f,0.0f,0.0f));
    // SetMatrices();
    // m_pTorus->Render();

    // m_pShader->SetUniform("Kd", 0.7f, 0.7f, 0.7f);
    // m_pShader->SetUniform("Ks", 0.9f, 0.9f, 0.9f);
    // m_pShader->SetUniform("Ka", 0.2f, 0.2f, 0.2f);
    // m_pShader->SetUniform("Shininess", 180.0f);

    // m_mModelMatrix = mat4(1.0f);
    // SetMatrices();
    // m_pPlane->Render();

	m_pShader->Use(false);
	glutSwapBuffers();
}

///////////////////////////////////////////////////////////////////////////////

void Spotlight::SetMatrices(void)
{
	mat4 mv = m_mViewMatrix * m_mModelMatrix;
    m_pShader->SetUniform("ModelViewMatrix", mv);
    mat3 normalmatrix = mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2]));
    m_pShader->SetUniform("NormalMatrix", normalmatrix);
    mat4 mvp = m_mProjectionMatrix * mv;
    m_pShader->SetUniform("MVP", mvp);
}

///////////////////////////////////////////////////////////////////////////////
