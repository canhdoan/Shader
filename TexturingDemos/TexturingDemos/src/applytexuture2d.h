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

#ifndef APP_APPLYTEXTURE2D_H
#define APP_APPLYTEXTURE2D_H

/**
 * This class will render a texture 2d on a 3d model(cube model). It will use 
 * default shader to render it. Just render 2d texture, don't have a effect is
 * used to it.
 *
 */
class ApplyTexture2D
{
public:
	/** 
	 * The constructor for this class
	 */
	ApplyTexture2D(void);

	/**
	 * The destructor for this class
	 */
	~ApplyTexture2D(void);

	/**
	 * Construct method. In this method, all attribute of this class will initialized.
	 */
	void Construct(void);

	/**
	 * Terminate 
	 */

private:
};


#endif // APP_APPLYTEXTURE2D_H

///////////////////////////////////////////////////////////////////////////////
