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

// Define LightInfo struct with position and intensity of a light source
struct LightInfo
{
	vec4 Position;
	vec3 Intensity;
};
uniform LightInfo uni_lights[5];

// Material parameter
uniform vec3 Kd;			// Diffuse reflectivity
uniform vec3 Ka;			// Ambient reflectivity
uniform vec3 Ks;			// Specular reflectivity
uniform float Shininess;	// Specular shininess factor

// Matrix transform
uniform mat4 uni_mvmatrix;
uniform mat3 uni_normalmatrix;
uniform mat4 uni_mvpmatrix;

// Attributes
attribute vec3 attr_vertex;
attribute vec3 attr_normal;

// Varying
varying vec3 vary_color;

// Method to convert vertex and normal to eye coordinate
void GetEyeCoordinate(out vec4 position, out vec3 norm)
{
	norm = normalize(uni_normalmatrix * attr_normal);
	position = uni_mvmatrix * vec4(attr_vertex, 1.0);
}

// Ambient-Diffuse-Specular method
vec3 ADS(int index, vec4 position, vec3 norm)
{
	vec3 s = normalize(vec3(uni_lights[index].Position - position));
	vec3 v = normalize(-position.xyz);
	vec3 r = reflect(-s, norm);
	float sDOTn = max(dot(s, norm), 0.0);
	float rDOTv = max(dot(r, v), 0.0);
	vec3 I = uni_lights[index].Intensity; // Light intensity
	return (I * (Ka + (Kd * sDOTn) + (Ks * pow(rDOTv, Shininess))));
}

void main()
{
	vec3 tnorm;
	vec4 eyeposition;
	GetEyeCoordinate(eyeposition, tnorm);

	// Calculate color for each of light
	vary_color = vec3(0.0);
	for (int i = 0; i < 5; i++)
	{
		vary_color += ADS(i, eyeposition, tnorm);
	}

	//Convert vertex position to clip-coordinate
	gl_Position = uni_mvpmatrix * vec4(attr_vertex, 1.0);
}

///////////////////////////////////////////////////////////////////////////////
