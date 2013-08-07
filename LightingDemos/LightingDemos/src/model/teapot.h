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

#ifndef APP_MODEL_TEAPOT_H
#define APP_MODEL_TEAPOT_H

class Teapot
{
public:
	/**
	 * The constructor for this class
	 */
	Teapot(void);

	/**
	 * The destructor for this class
	 */
	~Teapot(void);

	/**
	 * The construct method
	 */
	void Construct(int grid, mat4 lidTransform);

	/**
	 * Render method
	 */
	void Render(void);

private:
	void generatePatches(float * v, float * n, float *tc, unsigned int* el, int grid);
    void buildPatchReflect(int patchNum,
                           float *B, float *dB,
                           float *v, float *n,
                           float *tc, unsigned int *el,
                           int &index, int &elIndex, int &tcIndex, int grid,
                           bool reflectX, bool reflectY);
    void buildPatch(vec3 patch[][4],
                    float *B, float *dB,
                    float *v, float *n, float *tc,
                    unsigned int *el,
                    int &index, int &elIndex, int &tcIndex, int grid, mat3 reflect,
                    bool invertNormal);
    void getPatch( int patchNum, vec3 patch[][4], bool reverseV);

    void computeBasisFunctions( float * B, float * dB, int grid);
    vec3 evaluate( int gridU, int gridV, float *B, vec3 patch[][4]);
    vec3 evaluateNormal( int gridU, int gridV, float *B, float *dB, vec3 patch[][4]);
    void moveLid(int grid, float *v, mat4 lidTransform);

private:
	// Vertex array object
	GLuint m_nVAO;
	// Number of faces
	unsigned int m_nFaces;
};

#endif // APP_MODEL_TEAPOT_H

///////////////////////////////////////////////////////////////////////////////
