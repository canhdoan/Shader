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
/*
namespace Shader
{
	void LoadShader(const char* pVertexFile, const char *pFragFile, GLuint &programID)
	{
		GLuint vertexID, fragmentID;
		GLint compile;
		GLint nLengthInfo = 0;

		char *pVertexSource = NULL;
		const char *pVS = NULL;
		
		// Get vertex source from file
		pVertexSource = TextHelper::ReadFile(pVertexFile);
		pVS = pVertexSource;
		// Create vertex shader
		vertexID = glCreateShader(GL_VERTEX_SHADER);
		if (vertexID == 0)
			printf("ERROR: Can not create vertex shader!");
		// Load shader source
		glShaderSource(vertexID, 1, &pVS);
		// Compile the vertex shader
		glCompileShader(vertexID);
		// Check compile status
		glGetShaderiv(vertexID, GL_COMPILE_STATUS, &compile);
		if (!compile)
		{
			nLengthInfo = 0;
			glGetShaderiv(vertexID, GL_INFO_LOG_LENGTH, &nLengthInfo);
			if (nLengthInfo > 1)
			{
				// Show log content
				char *pLog = (char*)malloc(sizeof(char) * nLengthInfo);
				glGetShaderInfoLog(vertexID, nLengthInfo, NULL, pLog);
				printf("SHADER COMPILE ERROR: %s\n", pLog);
				free(pLog);
			}
		}


		char *pFragSource = NULL;
		const char *pFS = NULL;
		// Get fragment source from file
		pFragSource = TextHelper::ReadFile(pFragFile);
		pFS = pVertexSource;
		// Create fragment shader
		fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
		if (fragmentID == 0)
			printf("ERROR: Can not create fragment shader!");
		// Load shader source
		glShaderSource(fragmentID, 1, &pFS);
		// Compile the fragment shader
		glCompileShader(fragmentID);
		// Check compile status
		glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &compile);
		if (!compile)
		{
			nLengthInfo = 0;
			glGetShaderiv(nLengthInfo, GL_INFO_LOG_LENGTH, &nLengthInfo);
			if (nLengthInfo > 1)
			{
				char *pLog = (char*)malloc(sizeof(char) * nLengthInfo);
				glGetShaderInfoLog(fragmentID, nLengthInfo, NULL, pLog);
				printf("SHADER COMPILE ERROR: %s\n", pLog);
				free(pLog);
			}
		}


		// Create programe
		programID = glCreateProgram();
		// Attach shader
		glAttachShader(programID, vertexID);
		glAttachShader(programID, fragmentID);
		// Link the program
		glLinkProgram(programID);
		// Validate program
		glValidateProgram(programID);
		// Check status of the compile and link
		nLengthInfo = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &nLengthInfo);
		if (nLengthInfo > 0)
		{
			char *pLog = (char*)malloc(sizeof(char) * nLengthInfo);
		    // show error
		    glGetProgramInfoLog(programID, nLengthInfo, &nLengthInfo, &pLog);
		    fprintf("LINK PROGRAM ERROR: %s\n", pLog);
		    free(pLog);
		}
		// Release vertex & fragment shader
		glDeleteShader(vertexID);
		glDeleteShader(fragmentID);
	}
};*/

///////////////////////////////////////////////////////////////////////////////

Shader::Shader(void) : 
 m_nProgramID(0),
 m_nVertexID(0),
 m_nFragmentID(0),
 m_bLinked(false)
{}

///////////////////////////////////////////////////////////////////////////////

Shader::~Shader(void)
{}

///////////////////////////////////////////////////////////////////////////////

void Shader::Construct(const char *pVertexFile, const char *pFragFile)
{
	// Create two shader program
	m_nVertexID = glCreateShader(GL_VERTEX_SHADER);
	m_nFragmentID = glCreateShader(GL_FRAGMENT_SHADER);
}

///////////////////////////////////////////////////////////////////////////////

bool Shader::CompileShaderFromFile(const char *pFileName, GLSLShader::GLSLShaderType type)
{
	GLint compile;
	GLint nLengthInfo = 0;
	char *source = NULL;
	source = TextHelper::ReadFile(pFileName);

	if (type == GLSLShader::GLSLShaderType::VERTEX)
	{
		// Load shader source
		glShaderSource(m_nVertexID, 1, &pVS);
		// Compile the vertex shader
		glCompileShader(m_nVertexID);
		// Check compile status
		glGetShaderiv(m_nVertexID, GL_COMPILE_STATUS, &compile);
		if (!compile)
		{
			nLengthInfo = 0;
			glGetShaderiv(m_nVertexID, GL_INFO_LOG_LENGTH, &nLengthInfo);
			if (nLengthInfo > 1)
			{
				// Show log content
				char *pLog = (char*)malloc(sizeof(char) * nLengthInfo);
				glGetShaderInfoLog(m_nVertexID, nLengthInfo, NULL, pLog);
				printf("SHADER COMPILE ERROR: %s\n", pLog);
				free(pLog);
			}
		}
	}
	else if (type == GLSLShader::GLSLShaderType::FRAGMENT)
	{

	}
	else if (type == GLSLShader::GLSLShaderType::GEOMETRY)
	{
		
	}
	else if (type == GLSLShader::GLSLShaderType::TESS_CONTROL)
	{
		
	}
	else if (type == GLSLShader::GLSLShaderType::TESS_EVALUATION)
	{
		
	}
	else
	{
		printf("Shader type wrong!\n");
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

bool Shader::FileExists(const char *pPath)
{
	return true;
}
///////////////////////////////////////////////////////////////////////////////
