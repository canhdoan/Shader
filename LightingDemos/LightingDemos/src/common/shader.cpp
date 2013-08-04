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

	if (!CompileShaderFromFile(pFragFile, GLSLShader::GLSLShaderType::FRAGMENT))
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
		if (nLengthInfo > 1)
		{
			m_bLinked = false;
			//char *pLog = (char*)malloc(sizeof(char) * nLengthInfo);
		 //   // show error
		 //   glGetProgramInfoLog(m_nProgramID, nLengthInfo, &nLengthInfo, &pLog);
		 //   printf("ERROR: %s\n", pLog);
		 //   free(pLog);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////

void Shader::Use(bool bUse)
{
	if (bUse)
		glUseProgram(m_nProgramID); // Use
	else
		glUseProgram(0); // Unuse
}

///////////////////////////////////////////////////////////////////////////////

bool Shader::CompileShaderFromFile(const char *pFileName, GLSLShader::GLSLShaderType type)
{
	GLint compile;
	GLint nLengthInfo = 0;
	const char *source = NULL;
	source = TextHelper::ReadFile(pFileName);

	if (type == GLSLShader::GLSLShaderType::VERTEX)
	{
		// Load shader source
		glShaderSource(m_nVertexID, 1, &source, NULL);
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
		glShaderSource(m_nFragmentID, 1, &source, NULL);
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

int Shader::GetSubroutine(GLSLShader::GLSLShaderType type, const char *pSub)
{
	int location = 0;

	if (type == GLSLShader::GLSLShaderType::VERTEX)
	{
		location = glGetSubroutineIndex(m_nProgramID, GL_VERTEX_SHADER, pSub);
	}
	else if (type == GLSLShader::GLSLShaderType::FRAGMENT)
	{
		location = glGetSubroutineIndex(m_nProgramID, GL_FRAGMENT_SHADER, pSub);
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
	return (location < 0) ? -1 : location;
}

///////////////////////////////////////////////////////////////////////////////

void Shader::SetUniform(const char *szName, const glm::vec3 &v)
{
	// Get location of uniform
	int nUniformLoc = GetUniformLocation(szName);
	if (nUniformLoc < 0)
		printf("DEBUG: The %s uniform not exist.\n", szName);
	else
		glUniform3fv(nUniformLoc, 1, glm::value_ptr(v));
}

///////////////////////////////////////////////////////////////////////////////

void Shader::SetUniform(const char *szName, const glm::vec4 &v)
{
	// Get location of uniform
	int nUniformLoc = GetUniformLocation(szName);
	if (nUniformLoc < 0)
		printf("DEBUG: The %s uniform not exist.\n", szName);
	else
		glUniform4fv(nUniformLoc, 1, glm::value_ptr(v));
}

///////////////////////////////////////////////////////////////////////////////

void Shader::SetUniform(const char *szName, const glm::mat3 &m)
{
	// Get location of uniform
	int nUniformLoc = GetUniformLocation(szName);
	if (nUniformLoc < 0)
		printf("DEBUG: The %s uniform not exist.\n", szName);
	else
		glUniformMatrix3fv(nUniformLoc, 1, GL_FALSE, glm::value_ptr(m));
}

///////////////////////////////////////////////////////////////////////////////

void Shader::SetUniform(const char *szName, const glm::mat4 &m)
{
	// Get location of uniform
	int nUniformLoc = GetUniformLocation(szName);
	if (nUniformLoc < 0)
		printf("DEBUG: The %s uniform not exist.\n", szName);
	else
		glUniformMatrix4fv(nUniformLoc, 1, GL_FALSE, glm::value_ptr(m));
}

///////////////////////////////////////////////////////////////////////////////

void Shader::SetUniform(const char *szName, bool val)
{
	// Get location of uniform
	int nUniformLoc = GetUniformLocation(szName);
	if (nUniformLoc < 0)
		printf("DEBUG: The %s uniform not exist.\n", szName);
	else
		glUniform1i(nUniformLoc, val);
}

///////////////////////////////////////////////////////////////////////////////

void Shader::SetUniform(const char *szName, int val)
{
	// Get location of uniform
	int nUniformLoc = GetUniformLocation(szName);
	if (nUniformLoc < 0)
		printf("DEBUG: The %s uniform not exist.\n", szName);
	else
		glUniform1i(nUniformLoc, val);
}

///////////////////////////////////////////////////////////////////////////////

void Shader::SetUniform(const char *szName, float val)
{
	// Get location of uniform
	int nUniformLoc = GetUniformLocation(szName);
	if (nUniformLoc < 0)
		printf("DEBUG: The %s uniform not exist.\n", szName);
	else
		glUniform1f(nUniformLoc, val);
}

///////////////////////////////////////////////////////////////////////////////

void Shader::SetUniform(const char *szName, float x, float y, float z)
{
	// Get location of uniform
	int nUniformLoc = GetUniformLocation(szName);
	if (nUniformLoc < 0)
		printf("DEBUG: The %s uniform not exist.\n", szName);
	else
		glUniform3f(nUniformLoc, x, y, z);
}

///////////////////////////////////////////////////////////////////////////////

bool Shader::FileExists(const char *pPath)
{
	return true;
}
///////////////////////////////////////////////////////////////////////////////
