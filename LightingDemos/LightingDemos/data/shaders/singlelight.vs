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

uniform vec4 uni_light_position;
uniform vec3 uni_diffuse_color;
uniform vec3 uni_light_color;

uniform mat4 uni_mvmatrix;
uniform mat3 uni_normalmatrix;
// uniform mat4 uni_projectionmatrix;
uniform mat4 uni_mvpmatrix;

attribute vec3 attr_vertex;
attribute vec3 attr_normal;

varying vec3 vary_light_intensity;

void main()
{
	// Convert normal and vertex position to eye coordinate
	vec3 tnorm = normalize(uni_normalmatrix * attr_normal);
	vec4 eyeCoords = uni_mvmatrix * vec4(attr_vertex, 1.0);

	// Calculate light direction
	vec3 lightdir = normalize(vec3(uni_light_position - eyeCoords));

	// Diffuse shading equation
	// -------------------------------------------------------------------------------------
	// LightIntensity = LightColor * DiffuseColor * max(dot(LightDir, VertexNormal), 0.0); -
	// -------------------------------------------------------------------------------------
	vary_light_intensity = uni_light_color*uni_diffuse_color*max(dot(lightdir, tnorm), 0.0);

	// Convert vertex position to clip-coordinate
	gl_Position = uni_mvpmatrix * vec4(attr_vertex, 1.0);
}

///////////////////////////////////////////////////////////////////////////////
