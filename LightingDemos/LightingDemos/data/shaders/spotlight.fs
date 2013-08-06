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

struct SpotLightInfo
{
	vec4 Position;		// Positioni in eye-coordinate
	vec3 Intensity;		// Ambient, Diffuse and Specular intensity
	vec3 Direction;		// Normalize direction of spotlight
	float Exponent;		// Angle exponent
	float Cutoff;		// Cutoff angle(0 - 90)
};

uniform SpotLightInfo SpotLight;

varying vec3 Position;
varying vec3 Normal;

uniform vec4 LightPosition;		// Light position
uniform vec3 LightIntensity;	// Light intensity
uniform vec3 Ka;				// Ambient reflectivity
uniform vec3 Kd;				// Diffuse reflectivity
uniform vec3 Ks;				// Specular reflectivity
uniform float Shininess;		// Specular shininess factor

vec3 ADSWithSpotLight()
{
	vec3 s = normalize(vec3(SpotLight.Position) - Position);
	float angle = acos(dot(-s, SpotLight.Direction));
	float cutoff = radians(clamp(SpotLight.Cutoff, 0.0, 90.0));
	vec3 ambient = SpotLight.Intensity * Ka;
	if (angle < cutoff)
	{
		float SpotFactor = pow(dot(-s, SpotLight.Direction), SpotLight.Exponent);

		vec3 v = normalize(vec3(-Position));
		vec3 h = normalize(v + s);

		float sDOTn = max(dot(s, Normal), 0.0);
		float hDOTn = max(dot(h, Normal), 0.0);

		return ambient 
			+ (SpotFactor * SpotLight.Intensity * ((Kd * sDOTn) 
			+ (Ks * pow(hDOTn, Shininess))));
	}
	else
		return ambient;
}

void main()
{
	// Code for debug
	vec3 Spot_Color = ADSWithSpotLight();

	if (Spot_Color.x == 0 && Spot_Color.y == 0 && Spot_Color.z == 0)
	{
		gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	}
	else if (Spot_Color.x != 0 && Spot_Color.y == 0 && Spot_Color.z == 0)
	{
		gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);
	}
	else if (Spot_Color.x == 0 && Spot_Color.y != 0 && Spot_Color.z == 0)
	{
		gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0);
	}
	else if (Spot_Color.x == 0 && Spot_Color.y == 0 && Spot_Color.z != 0)
	{
		gl_FragColor = vec4(1.0, 0.0, 1.0, 1.0);
	}
	else
	{
		gl_FragColor = vec4(Spot_Color, 1.0);
	}



	// gl_FragColor = vec4(ADSWithSpotLight(), 1.0);
}

///////////////////////////////////////////////////////////////////////////////
