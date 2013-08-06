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


attribute vec3 VertexPosition;
attribute vec3 VertexNormal;

varying vec3 Position;
varying vec3 Normal;


uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

void main()
{
	// Convert vector normal to eyecoordinate and pass to fragment shader
	Normal = normalize(NormalMatrix * VertexNormal);
	// Convert vertex position to eyecoordinate and pass to fragment shader
	Position = vec3(ModelViewMatrix * vec4(VertexPosition, 1.0));
	// Set vertex position to built-in variable gl_Position
	gl_Position = MVP * vec4(VertexPosition, 1.0);
}

///////////////////////////////////////////////////////////////////////////////
