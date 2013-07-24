///////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2010 AsNet Co., Ltd.
// All Rights Reserved. These instructions, statements, computer
// programs, and/or related material (collectively, the "Source")
// contain unpublished information propietary to AsNet Co., Ltd
// which is protected by US federal copyright law and by 
// international treaties. This Source may NOT be disclosed to 
// third parties, or be copied or duplicated, in whole or in 
// part, without the written consent of AsNet Co., Ltd.
///////////////////////////////////////////////////////////////////////////////
// Author: Canh Doan
///////////////////////////////////////////////////////////////////////////////

#ifndef APP_COMMON_SHADER_H
#define APP_COMMON_SHADER_H

/**
 * Define all function to use for prepare shader program, include :
 * + Load shader(vertex and fragment) from text file
 * + Compile shader
 * + Link to shader program
 *
 */
namespace Shader
{
	/**
	 * Method load shader to create vertex & fragment shader, compile it and link to
	 * shader programe
	 * @param pVertexFile	: path of vertex shader text file
	 * @param pFragFile		: path of fragment shader text file
	 * @param programID		: shader program will return to use
	 */
	void LoadShader(const char* pVertexFile, const char *pFragFile, GLuint &programID);
};


#endif // APP_COMMON_SHADER_H

///////////////////////////////////////////////////////////////////////////////
