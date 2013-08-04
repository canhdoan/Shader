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


///////////////////////////////////////////////////////////////////////////////
// THEORY
///////////////////////////////////////////////////////////////////////////////
// This is vertex shader of ADS(Ambient-Diffuse-Specular) demo. In this demo, 
// we need to know about equations of ADS.
//
// 1. Ambient
// ----------------
// | Ia = La * Ka |
// ----------------
// Where Ia, La and Ka?
// - Ia: is ambient intensity
// - La: is ambient light source intensity
// - Ka: is surface reflectivity(abient material color)
// 
// 2. Diffuse
// ------------------------
// | Id = Ld * Kd * (s.n) |
// ------------------------
// Where Id, Ld, Kd, s and n?
// - Id: is diffuse intensity
// - Ld: is diffuse light source intensity
// - Kd: is diffuse reflectivity(diffuse material color)
// - s: light direction(vector from vertex toward light source)
// - n: vector normal
//
// 3. Specular
// ----------------------------
// | Is = (Ls * Ks * (r.v))^f |
// ----------------------------
// Where Is, Ls, Ks, r and v
// - Is: is specular intensity
// - Ls: is specular light source intensity
// - Ks: is specular reflectivity(specular material color)
// - r: is perfect reflection vector. It can calculate by equation:
// 		--------------------------
// 		| r = -s + 2 * (s.n) * n |
// 		--------------------------
// 		+ s: is vector from vertex toward light source
//		+ n: is vector normal
// - v: is vector from vertex toward view
// - f: is shininess factor
//
// So, when we putting all of components together, we have the shading equation:
// --------------------
// | I = Ia + Id + Is |
// --------------------
//
///////////////////////////////////////////////////////////////////////////////

#version 120

struct LightInfo
{
	vec4 Position; 	// Light position in eye coordinate
	vec3 La;		// Ambient light intensity
	vec3 Ld;		// Diffuse light intensity
	vec3 Ls;		// Specular light intensity
};

struct MaterialInfo
{
	vec3 Ka;		// Ambient reflectivity
	vec3 Kd;		// Diffuse reflectivity
	vec3 Ks;		// Specular reflectivity
	float Shininess;// Specular shininess factor
};

uniform LightInfo uni_light;
uniform MaterialInfo uni_material;

uniform mat4 uni_mvmatrix;
uniform mat3 uni_normalmatrix;
// uniform mat4 uni_projectionmatrix;
uniform mat4 uni_mvpmatrix;

attribute vec3 attr_vertex;
attribute vec3 attr_normal;

varying vec3 vary_light_intensity;

void GetEyeCoordinate(out vec3 norm, out vec4 position)
{
	norm = normalize(uni_normalmatrix * attr_normal);
	position = uni_mvmatrix * vec4(attr_vertex, 1.0);
}

vec3 PhongModel(vec4 position, vec3 norm)
{
	vec3 s = normalize(vec3(uni_light.Position - position));
	vec3 v = normalize(-position.xyz);
	vec3 r = reflect(-s, norm);
	vec3 ambient = uni_light.La * uni_material.Ka;
	float sDOTn = max(dot(s, norm), 0.0);
	vec3 diffuse = uni_light.Ld * uni_material.Kd * sDOTn;
	vec3 specular = vec3(0.0);
	if (sDOTn > 0)
	{
		specular = (uni_light.Ls * uni_material.Ks * (pow(max(dot(r,v), 0.0), uni_material.Shininess)));
	}

	return (ambient + diffuse + specular);
}

void main()
{
	// Convert normal and vertex position to eye coordinate
	vec3 tnorm;
	vec4 eyeCoords;
	GetEyeCoordinate(tnorm, eyeCoords);

	// Light intensity out
	vary_light_intensity = PhongModel(eyeCoords, tnorm);

	// Convert vertex position to clip-coordinate
	gl_Position = uni_mvpmatrix * vec4(attr_vertex, 1.0);
}

///////////////////////////////////////////////////////////////////////////////
