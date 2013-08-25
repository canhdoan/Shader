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

#ifndef APP_COMMON_MESH_H
#define APP_COMMON_MESH_H

class Mesh
{
public:
	/**
	 * The constructor for this class
	 */
	Mesh(void);

	/**
	 * The destructor for this class
	 */
	~Mesh(void);

	/**
	 * The construct method of this class
	 */
	void Construct(void);

	/**
	 * The terminal method of this class
	 */
	void Terminal(void);


public:
	/**
	 * The update method of this class
	 */
	void OnUpdate(void);

	/**
	 * The render method of this class
	 */
	void OnPaint(void);

	/**
	 * Load mesh from file
	 */
	int Load(const char *filename);

	/**
	 * Readline function
	 */
	void ReadLine(BYTE_ *line);

	/**
	 * Pre-Process function for mesh class
	 */
	void PreProcess(void);


public:
	BYTE_ *m_pLinePointer;

	////////////////////////////////////////////////////////
	// Mesh structure
    sVertex 		*m_pVerticesList;
    DWORD_ 			m_nNumVertices;
    sFace 			*m_pFacesList;
	DWORD_ 			m_nNumFaces;
	float 			*m_pMaterialAmbient;
	float 			*m_pMaterialDiffuse;
	float 			*m_pMaterialSpecular;
	float 			m_fShininess;
	float 			*m_pEnvColor;
	float 			*m_pMaterialColor;
	vec3 			m_vScale;
	vec3 			m_vPosition;
	float 			m_fAngle;

	///////////////////////////////////////////////////////
	// Mesh id used with OpenGL display List
	int 			m_nMeshId;
	DWORD_ 			m_nTextureId;
	DWORD_ 			m_nVertex;
	int 			m_nPolygonMode;
};

#endif // APP_COMMON_MESH_H

///////////////////////////////////////////////////////////////////////////////
