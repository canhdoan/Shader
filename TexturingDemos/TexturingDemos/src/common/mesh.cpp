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

Mesh::Mesh(void) :
 m_pLinePointer(NULL),
 m_pVerticesList(NULL),
 m_nNumVertices(0),
 m_pFacesList(NULL),
 m_nNumFaces(0),
 m_pMaterialAmbient(NULL),
 m_pMaterialDiffuse(NULL),
 m_pMaterialSpecular(NULL),
 m_fShininess(0.0f),
 m_pEnvColor(NULL),
 m_pMaterialColor(NULL),
 m_vScale(vec3(0)),
 m_vPosition(vec3(0)),
 m_fAngle(0.0f),
 m_nMeshId(-1),
 m_nTextureID(0),
 m_nVertex(0),
 m_nPolygonMode(-1)
{
}

///////////////////////////////////////////////////////////////////////////////

Mesh::~Mesh(void)
{
	Terminal();
}

///////////////////////////////////////////////////////////////////////////////

void Mesh::Construct(void)
{
	m_pMaterialAmbient = new float[4];
	m_pMaterialAmbient[0] = 0.9f;
	m_pMaterialAmbient[1] = 0.4f;
	m_pMaterialAmbient[2] = 0.1f;
	m_pMaterialAmbient[3] = 0.5f;

	m_pMaterialDiffuse = new float[4];
	m_pMaterialDiffuse[0] = 0.5f;
	m_pMaterialDiffuse[1] = 0.5f;
	m_pMaterialDiffuse[2] = 0.5f;
	m_pMaterialDiffuse[3] = 0.5f;

	m_pMaterialSpecular = new float[4];
	m_pMaterialSpecular[0] = 0.1f;
	m_pMaterialSpecular[1] = 0.1f;
	m_pMaterialSpecular[2] = 0.9f;
	m_pMaterialSpecular[3] = 0.5f;

	m_fShininess = 10.0f;

	m_pEnvColor = new float[4];
	m_pEnvColor[0] = 0.8f;
	m_pEnvColor[1] = 0.8f;
	m_pEnvColor[2] = 0.8f;
	m_pEnvColor[3] = 0.8f;

	m_pMaterialColor = new float[4];
	m_pMaterialColor[0] = 0.8f;
	m_pMaterialColor[1] = 0.0f;
	m_pMaterialColor[2] = 0.0f;
	m_pMaterialColor[3] = 1.0f;

	m_vScale.x = 1.0f;
	m_vScale.y = 1.0f;
	m_vScale.z = 1.0f;

	m_vPosition.x = 0.0f;
	m_vPosition.y = 0.0f;
	m_vPosition.z = 0.0f;
}

///////////////////////////////////////////////////////////////////////////////

void Mesh::Terminal(void)
{
	// Reset all value of class
	m_nNumVertices = 0;
	m_nNumFaces = 0;
	m_fShininess = 0.0f;
	m_fAngle = 0.0f;
	m_nMeshId = 0;
	m_nVertex = 0;
	m_nPolygonMode = 0;

	m_nTextureID = 0;

	// Release all pointer of class
	if (m_pLinePointer)
		delete m_pLinePointer;
	m_pLinePointer = NULL;

	if (m_pVerticesList)
		delete m_pVerticesList;
	m_pVerticesList = NULL;

	if (m_pFacesList)
		delete m_pFacesList;
	m_pFacesList = NULL;

	if (m_pMaterialAmbient)
		delete m_pMaterialAmbient;
	m_pMaterialAmbient = NULL;

	if (m_pMaterialDiffuse)
		delete m_pMaterialDiffuse;
	m_pMaterialDiffuse = NULL;

	if (m_pMaterialSpecular)
		delete m_pMaterialSpecular;
	m_pMaterialSpecular = NULL;

	if (m_pEnvColor)
		delete m_pEnvColor;
	m_pEnvColor = NULL;

	if (m_pMaterialColor)
		delete m_pMaterialColor;
	m_pMaterialColor = NULL;
}

///////////////////////////////////////////////////////////////////////////////

void Mesh::OnUpdate(void)
{

}

///////////////////////////////////////////////////////////////////////////////

void Mesh::OnPaint(void)
{

}

///////////////////////////////////////////////////////////////////////////////

int Mesh::Load(const char *filename)
{
	return 0;
}

///////////////////////////////////////////////////////////////////////////////

void Mesh::ReadLine(BYTE_ *line)
{

}

///////////////////////////////////////////////////////////////////////////////

void Mesh::PreProcess(void)
{
	
}

///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
