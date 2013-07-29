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
 m_bLinked(true),
 m_bCompile(true)
{}

///////////////////////////////////////////////////////////////////////////////

Shader::~Shader(void)
{
	glDeleteShader(m_nVertexID);
	glDeleteShader(m_nFragmentID);
}

///////////////////////////////////////////////////////////////////////////////

void Shader::Construct(const char *pVertexFile, const char *pFragFile)
{
	// Create two shader program
	m_nVertexID = glCreateShader(GL_VERTEX_SHADER);
	m_nFragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	// Compile vertex and fragment shader from file
	if (!CompileShaderFromFile(pVertexFile, GLSLShader::GLSLShaderType::VERTEX))
	{
		printf("ERROR: Can not compile vertex shader from %s\n", pVertexFile);
		m_bCompile = false;
	}

	if (!CompileShaderFromFile(pVertexFile, GLSLShader::GLSLShaderType::FRAGMENT))
	{
		printf("ERROR: Can not compile fragment shader from %s\n", pFragFile);
		m_bCompile = false;
	}

	if (m_bCompile)
	{
		GLint nLengthInfo = 0;
		// Create programe
		m_nProgramID = glCreateProgram();
		// Attach shader
		glAttachShader(m_nProgramID, m_nVertexID);
		glAttachShader(m_nProgramID, m_nFragmentID);
		// Link the program
		glLinkProgram(m_nProgramID);
		// Validate program
		glValidateProgram(m_nProgramID);
		// Check status of the compile and link
		nLengthInfo = 0;
		glGetProgramiv(m_nProgramID, GL_INFO_LOG_LENGTH, &nLengthInfo);
		if (nLengthInfo > 0)
		{
			m_bLinked = false;
			char *pLog = (char*)malloc(sizeof(char) * nLengthInfo);
		    // show error
		    glGetProgramInfoLog(m_nProgramID, nLengthInfo, &nLengthInfo, &pLog);
		    printf("ERROR: %s\n", pLog);
		    free(pLog);
		}
	}
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
		glShaderSource(m_nVertexID, 1, &source);
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
				printf("ERROR: %s\n", pLog);
				free(pLog);
			}
		}
	}
	else if (type == GLSLShader::GLSLShaderType::FRAGMENT)
	{
		// Load shader source
		glShaderSource(m_nFragmentID, 1, &source);
		// Compile fragment shader
		glCompileShader(m_nFragmentID);
		// Check compile status
		glGetShaderiv(m_nFragmentID, GL_COMPILE_STATUS, &compile);
		if (!compile)
		{
			nLengthInfo = 0;
			glGetShaderiv(m_nFragmentID, GL_INFO_LOG_LENGTH, &nLengthInfo);
			if (nLengthInfo > 1)
			{
				// Show log content
				char *pLog = (char*)malloc(sizeof(char) * nLengthInfo);
				glGetShaderInfoLog(m_nFragmentID, nLengthInfo, NULL, pLog);
				printf("ERROR: %s\n", pLog);
				free(pLog);
			}
		}
	}
	else if (type == GLSLShader::GLSLShaderType::GEOMETRY)
	{
		// TODO: ...
	}
	else if (type == GLSLShader::GLSLShaderType::TESS_CONTROL)
	{
		// TODO: ...
	}
	else if (type == GLSLShader::GLSLShaderType::TESS_EVALUATION)
	{
		// TODO: ...
	}
	else
	{
		printf("ERROR: Shader type wrong!\n");
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////

int Shader::GetUniformLocation(const char *pUniform)
{
	int location = 0;
	location = glGetUniformLocation(m_nProgramID, pUniform);
	return (location < 0) ? -1 : location;	
}

///////////////////////////////////////////////////////////////////////////////

int Shader::GetAttributeLocation(const char *pAttr)
{
	int location = 0;
	location = glGetAttribLocation(m_nProgramID, pAttr);
	return (location < 0) ? -1 : location;
}

///////////////////////////////////////////////////////////////////////////////

void SetUniform(const char *szName, const glm::vec3 &v)
{
	
}

///////////////////////////////////////////////////////////////////////////////

void SetUniform(const char *szName, const glm::vec4 &v)
{

}

///////////////////////////////////////////////////////////////////////////////

void SetUniform(const char *szName, const glm::mat3 &v)
{

}

///////////////////////////////////////////////////////////////////////////////

void SetUniform(const char *szName, const glm::mat4 &v)
{

}

///////////////////////////////////////////////////////////////////////////////

void SetUniform(const char *szName, bool val)
{

}

///////////////////////////////////////////////////////////////////////////////

void SetUniform(const char *szName, int val)
{

}

///////////////////////////////////////////////////////////////////////////////

void SetUniform(const char *szName, float val)
{

}

///////////////////////////////////////////////////////////////////////////////

bool Shader::FileExists(const char *pPath)
{
	return true;
}
///////////////////////////////////////////////////////////////////////////////
