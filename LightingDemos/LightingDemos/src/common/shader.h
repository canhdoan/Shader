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

#ifndef APP_COMMON_SHADER_H
#define APP_COMMON_SHADER_H

/**
 * Define all function to use for prepare shader program, include :
 * + Load shader(vertex and fragment) from text file
 * + Compile shader
 * + Link to shader program
 *
 */
namespace GLSLShader
{
	enum GLSLShaderType
	{
		VERTEX = 0,
		FRAGMENT,
		GEOMETRY,
		TESS_CONTROL,
		TESS_EVALUATION
	};
	/**
	 * Method load shader to create vertex & fragment shader, compile it and link to
	 * shader programe
	 * @param pVertexFile	: path of vertex shader text file
	 * @param pFragFile		: path of fragment shader text file
	 * @param programID		: shader program will return to use
	 */
	//void LoadShader(const char* pVertexFile, const char *pFragFile, GLuint &programID);
};

/**
 * Define Shader class to support for work with shader program in OpenGL.
 * This class will support load a shader source from file, compile shader program
 * linking and release all resource if not use. Otherwise, it's contain methods used to
 * work with shader program. For instance, get location of attribute and uniform, log status
 * of compile process, bind data to attribute, etc.
 *
 */
class Shader
{
///////////////////////////////////////////////////////////////////////////////
// Life-cycle
///////////////////////////////////////////////////////////////////////////////
public:
	/**
	 * The constructor of this class
	 */
	Shader(void);
	
	/**
	 * The destructor of this class
	 */
	~Shader(void);
	
	/**
	 * Construct method
	 *
	 * @param pVertexFile: The vertex shader source
	 * @param pFragFile: The fragment shader source
	 */
	void Construct(const char *pVertexFile, const char *pFragFile);
	
	/**
	 * Release method
	 */
	void Terminate(void);
	
	
///////////////////////////////////////////////////////////////////////////////
// Public Functions
///////////////////////////////////////////////////////////////////////////////
public:
	/**
	 * Compile shader from file
	 */
	bool CompileShaderFromFile(const char *pFileName, GLSLShader::GLSLShaderType type);
	
	/**
	 * Compile shader from string
	 */
	bool CompileShaderFromString(const string &source, GLSLShader::GLSLShaderType type);
	
	/**
	 * Link program
	 */
	// bool Link(void);
	
	/**
	 * Use program
	 */	 
	// void Use(void);

	/**
	 * 
	 */
	// string Log(void);
	
	/**
	 * Get handle
	 */
	// int GetHandle(void);
	
	/**
	 *
	 */
	// bool IsLinked(void);
	
	/**
	 *
	 */
	// void BindAttribLocation(GLuint location, const char *pName);
	
	/**
	 * Set unifrom data
	 */
	void SetUniform(const char *szName, const glm::vec3 &v);
	void SetUniform(const char *szName, const glm::vec4 &v);
	void SetUniform(const char *szName, const glm::mat3 &v);
	void SetUniform(const char *szName, const glm::mat4 &v);
	void SetUniform(const char *szName, bool val);
	void SetUniform(const char *szName, int val);
	void SetUniform(const char *szName, float val);
	
	
	
///////////////////////////////////////////////////////////////////////////////
// Private Functions
///////////////////////////////////////////////////////////////////////////////
private:
	/**
	 * Get location of uniform
	 */
	int GetUniformLocation(const char *pUniform);
	
	/**
	 * Get location of attribute
	 */
	int GetAttributeLocation(const char *pAttr);
	
	/**
	 * Check the file is exist or not
	 */
	bool FileExists(const char *pPath);
	

///////////////////////////////////////////////////////////////////////////////
// Attributes
///////////////////////////////////////////////////////////////////////////////
private:
	// Shader program
	GLuint				m_nProgramID;
	// Vertex shader
	GLuint				m_nVertexID;
	// Fragment shader
	GLuint				m_nFragmentID;
	// Flag for compile status
	bool				m_bCompile;
	// Flag for link status of program
	bool 				m_bLinked;
};


#endif // APP_COMMON_SHADER_H

///////////////////////////////////////////////////////////////////////////////
