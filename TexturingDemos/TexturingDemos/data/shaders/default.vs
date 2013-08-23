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

///////////////////////////////////////////////////////////////////////////////
// Attributes
attribute vec3 attr_vertex;
attribute vec3 attr_normal;
attribute vec2 attr_uv;


///////////////////////////////////////////////////////////////////////////////
// Uniform
uniform mat4 uni_mvmatrix;		// The model-view matrix
uniform mat3 uni_normalmatrix;	// The normal matrix
uniform mat4 uni_mvpmatrix;		// The model-view-projection matrix


///////////////////////////////////////////////////////////////////////////////
// Out variables
varying vec2 vary_uv;



void main()
{
	// Pass texture coordinate data to fragment shader
	vary_uv = attr_uv;

	// Set the vertex coordinate to gl_Position after transform to clip-space
	gl_Position = uni_mvpmatrix * vec4(attr_vertex, 1.0);
}
