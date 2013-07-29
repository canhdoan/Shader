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

#ifndef APP_COMMON_TEXTURE_H
#define APP_COMMON_TEXTURE_H

/**
 * Define a texture helper, methods used to load texture image will implement here
 *
 */
namespace Texture
{
	/**
	 * Load bitmap texture method
	 *
	 * @param pImage: the path of bitmap file
	 */
	GLuint LoadBmpTexture(const char *pImage);

};

#endif // APP_COMMON_TEXTURE_H

///////////////////////////////////////////////////////////////////////////////