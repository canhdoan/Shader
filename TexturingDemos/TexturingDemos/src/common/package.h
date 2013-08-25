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

#ifndef APP_COMMON_PACKAGE_H
#define APP_COMMON_PACKAGE_H

#pragma comment(lib, "glew32.lib")
#include <GL/glew.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <conio.h>
#include <io.h>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string.h>

using namespace std;


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;


#include "texthelper.h"
#include "texture.h"
#include "object.h"
#include "load3dobj.h"
#include "shader.h"
#include "RGBbytepixel.h"
#include "heightmap.h"
#include "mesh.h"

#define PI 3.141592653589793
#define TWOPI 6.2831853071795862

///////////////////////////////////////////////////////////////////////////////
// Structure defination
typedef unsigned long DWORD_;		// 32 bits
typedef unsigned short WORD_;		// 16 bits
typedef unsigned char BYTE_;		// 8bits


//--------------------------- BMP Structures START --------------------------

struct sBMP_header
{
	WORD_ codmag;
	DWORD_ taille;
	WORD_ reserv1;
	WORD_ reserv2;
	DWORD_ offsetImage;
};


struct sBMP_info
{
	DWORD_ TailleZoneInfo;
	DWORD_ LargeurImage;
	DWORD_ HauteurImage;
	WORD_ Nb_plans;								// toujours 1
	WORD_ BitParPixel;							// 1/4/8/24
	DWORD_ FormatCompressImage;
	DWORD_ TailleOctets;
	DWORD_ ResolutionHorizon;					// pixel par mètres
	DWORD_ ResolutionVertical;					// pixel par mètres
	DWORD_ NbCouleurUtil;						// 0 = maximum  si 24 bits alors ce champ spécifie taille palette
	DWORD_ NbIndexCouleur;						// 0 = toutes les couleur importantes						
};


struct sImageBMP
{
	sBMP_header header;
	sBMP_info info;
	cRGB_Byte_Pixel *data;
};

//--------------------------- BMP Structures END --------------------------

//-------------------- Vertex and Face structure START --------------------

struct sVertex
{
	vec3 vPosition; // postion
	vec3 vNormal; // normal
	vec2 vUV; // texture coordinate
};

struct sFace
{
	DWORD_ a, b, c; // indices of triangle
	vec3 vNormal; // normal of face
};

//-------------------- Vertex and Face structures END ---------------------


#endif // APP_COMMON_PACKAGE_H

///////////////////////////////////////////////////////////////////////////////
