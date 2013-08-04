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

#version 120

varying vec3 vary_front_color;
varying vec3 vary_back_color;

void main()
{
	if (gl_FrontFacing)
	{
		gl_FragColor = vec4(vary_front_color, 1.0);
	}
	else
	{
		gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	}
}

///////////////////////////////////////////////////////////////////////////////
