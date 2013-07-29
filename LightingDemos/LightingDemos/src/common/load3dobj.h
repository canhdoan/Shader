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

#ifndef APP_COMMON_LOAD3DOBJ_H
#define APP_COMMON_LOAD3DOBJ_H

#include "object.h"

namespace Load3DObj
{
	/**
	 * Load 3D model from file *.3ds format, result is stored to 3DS object
	 * structure that it is defined in the package file.
	 *
	 * @param pFileName		: the .3ds file to need load
	 * @param pObject		: the 3ds object structure
	 */
	void Load3dsModel(char *pFileName, OBJECT_3DS_PTR pObject);

	/**
	 * Load 3D model from file *.obj format, result is stored to object structure 
	 * that it is defined in the package file
	 */
	void LoadObjModel(void);
	
	/**
	 * Calculate normal vector
	 */
	void CalcNormalVector(void);
	
	/**
	 * Calculate tangent vector
	 */
	void CalcTangentVector(void);
	 
	/**
	 * Calculate bitangent(binormal) vector
	 */
	void CalcBiTangentVector(void);
	
};

#endif // APP_COMMON_LOAD3DOBJ_H

///////////////////////////////////////////////////////////////////////////////