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

#include "package.h"

///////////////////////////////////////////////////////////////////////////////
// Variables
SingleLight *g_pSingleLight = NULL;
ADSShading *g_pADS = NULL;
MultiLight *g_pMultiLight = NULL;
Spotlight *g_pSpotlight = NULL;

// Rotate variables
float rotation_x=0.0, rotation_x_increment=0.1f;
float rotation_y=0.0, rotation_y_increment=0.05f;
float rotation_z=0.0, rotation_z_increment=0.03f;
float g_fAngle = 0.0;

///////////////////////////////////////////////////////////////////////////////
// Declare all methods

/**
 * Initialize method
 */
void Initialize(void);

/**
 * Initialize for OpenGL
 */
void InitializeGL(void);

/**
 * Initialize shader, get location of attribute and uniform
 */
void InitializeShader(void);

/**
 * Initialize vertex array object
 */
void InitializeVAO(void);

/**
 * Update function
 */
void OnUpdate(int w, int h);

/**
 * Paint function, this method is used for paint first time.
 */
void Paint(void);

/**
 * Paint function, this method is used for paint in run-time
 */
void OnPaint(void);

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	// Init for GLUT
	// Init display window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(1024,768);
	glutCreateWindow("Lighting Demo by Canh Doan ^^");

	// Init function handle
	glutReshapeFunc(OnUpdate);
	glutDisplayFunc(Paint);
	glutIdleFunc(OnPaint);

	// Init GLEW
	glewInit();

	Initialize();

	glutMainLoop();

	return 0;
}

///////////////////////////////////////////////////////////////////////////////

void Initialize(void)
{
	printf("******************** INITIALIZE STAGE ********************\n");
	InitializeGL();
	InitializeShader();
	InitializeVAO();

	// Init SingleLight effect
	// g_pSingleLight = new SingleLight();
	// g_pSingleLight->Construct();

	// Init ADS effect
	// g_pADS = new ADSShading();
	// g_pADS->Construct();

	// Init MultiLight effect
	// g_pMultiLight = new MultiLight();
	// g_pMultiLight->Construct();

	// Init spot light effect
	// g_pSpotlight = new Spotlight();
	// g_pSpotlight->Construct();
}

///////////////////////////////////////////////////////////////////////////////

void InitializeGL(void)
{
	printf("******************** INITIALIZE OPENGL STAGE ********************\n");
	glClearColor(0.0f,0.0f,0.2f,0.0f); // Set background color
	glEnable(GL_DEPTH_TEST); // We enable the depth test (also called z buffer)
	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode
}

///////////////////////////////////////////////////////////////////////////////

void InitializeShader(void)
{
	printf("******************** INITIALIZE SHADER STAGE ********************\n");
}

///////////////////////////////////////////////////////////////////////////////

void InitializeVAO(void)
{
	printf("******************** INITIALIZE VAO STAGE ********************\n");
}

///////////////////////////////////////////////////////////////////////////////

void OnUpdate(int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	// g_pSingleLight->Update(w, h);
	// g_pADS->Update(w,h);
	// g_pMultiLight->Update(w, h);
	g_pSpotlight->Update(w, h);
}

///////////////////////////////////////////////////////////////////////////////

void Paint(void)
{
	// g_pSingleLight->Render();
	// g_pADS->Render();
	// g_pMultiLight->Render();
	g_pSpotlight->Render();
}

///////////////////////////////////////////////////////////////////////////////

void OnPaint(void)
{
	rotation_x = rotation_x + rotation_x_increment;
	rotation_y = rotation_y + rotation_y_increment;
	rotation_z = rotation_z + rotation_z_increment;

	if (rotation_x > 359) rotation_x = 0;
	if (rotation_y > 359) rotation_y = 0;
	if (rotation_z > 359) rotation_z = 0;

	g_fAngle += 0.01f;
	if(g_fAngle > TWOPI)
		g_fAngle -= TWOPI;
	
	glutPostRedisplay();
}

///////////////////////////////////////////////////////////////////////////////
