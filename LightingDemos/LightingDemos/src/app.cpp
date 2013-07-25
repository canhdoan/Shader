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
	printf("******************** INITIALIZE STAGE ********************");
	InitializeGLUT();
	InitializeGL();
	InitializeShader();
	InitializeVAO();
}

///////////////////////////////////////////////////////////////////////////////

void InitializeGL(void)
{
	printf("******************** INITIALIZE OPENGL STAGE ********************");
	glClearColor(0.0f,0.0f,0.2f,0.0f); // Set background color
	glEnable(GL_DEPTH_TEST); // We enable the depth test (also called z buffer)
	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode
}

///////////////////////////////////////////////////////////////////////////////

void InitializeShader(void)
{
	printf("******************** INITIALIZE SHADER STAGE ********************");
}

///////////////////////////////////////////////////////////////////////////////

void InitializeVAO(void)
{
	printf("******************** INITIALIZE VAO STAGE ********************");
}

///////////////////////////////////////////////////////////////////////////////

void OnUpdate(int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}

///////////////////////////////////////////////////////////////////////////////

void Paint(void)
{

}

///////////////////////////////////////////////////////////////////////////////

void OnPaint(void)
{

}

///////////////////////////////////////////////////////////////////////////////
