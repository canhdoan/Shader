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

#define PI 3.141592653589793
#define TWOPI 6.2831853071795862


#endif // APP_COMMON_PACKAGE_H

///////////////////////////////////////////////////////////////////////////////
