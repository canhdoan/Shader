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

varying vec3 Position;
varying vec3 Normal;

uniform vec4 LightPosition;		// Light position
uniform vec3 LightIntensity;	// Light intensity
uniform vec3 Ka;				// Ambient reflectivity
uniform vec3 Kd;				// Diffuse reflectivity
uniform vec3 Ks;				// Specular reflectivity
uniform float Shininess;		// Specular shininess factor

// vec3 ADS()
// {
// 	// Must normalize the normal vector again
// 	vec3 n = normalize(Normal);
// 	vec3 s = normalize(vec3(LightPosition) - Position);
// 	vec3 v = normalize(-Position);
// 	vec3 r = reflect(-s, n);
// 	float sDOTn = max(dot(s, n), 0.0);
// 	float rDOTv = max(dot(r, v), 0.0);

// 	return LightIntensity * (Ka + (Kd * sDOTn) + (Ks * pow(rDOTv, Shininess)));
// }

vec3 ADSWithHalfwayVetor()
{
	// Must normalize the normal vector again
	vec3 n = normalize(Normal);
	vec3 s = normalize(vec3(LightPosition) - Position);
	vec3 v = normalize(-Position);
	vec3 h = normalize(v + s);
	float sDOTn = max(dot(s, n), 0.0);
	float hDOTn = max(dot(h, n), 0.0);

	return LightIntensity * (Ka + (Kd * sDOTn) + (Ks * pow(hDOTn, Shininess)));	
}

void main()
{
	gl_FragColor = vec4(ADSWithHalfwayVetor(), 1.0);
}

///////////////////////////////////////////////////////////////////////////////
