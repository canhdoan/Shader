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

#ifndef APP_COMMON_RGB_BYTEPIXEL_H
#define APP_COMMON_RGB_BYTEPIXEL_H

class RGBbytepixel
{
public:
	/**
	 * The constructor for this class
	 */
	RGBbytepixel(BYTE_ r = 0, BYTE_ g = 0, BYTE_ b = 0)
	{
		m_R = r; m_G = g; m_B = b;
	}

	/**
	 * Set byte pixel
	 */
	void SetBytePixel(BYTE_ r, BYTE_ g, BYTE_ b)
	{ m_R = r; m_G = g; m_B = b }

	void SetBytePixel(RGBbytepixel *pixel)
	{
		m_R = pixel->m_R;
		m_G = pixel->m_G;
		m_B = pixel->m_B;
	}


public:
	BYTE_ m_R;
	BYTE_ m_G;
	BYTE_ m_B;
};

#endif // APP_COMMON_RGB_BYTEPIXEL_H

///////////////////////////////////////////////////////////////////////////////
