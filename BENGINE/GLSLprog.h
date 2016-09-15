#pragma once
#include<GL\glew.h>
#include<string>
//compiler of the shaders-fragment and vector
namespace bengine
{
	class GLSLprog
	{
	public:
		GLSLprog();
		~GLSLprog();

		void compileShaders(const std::string& vertexShaderFP, const std::string& fragmentShaderFP);//compiler
		/*takes in 2 file address 1)vertex shader 2) fragment shader
		->provides the unique id for the vertex shader and the fragment shader from the graphic card
		->then calls a function compileshader(filepath, gl id) for eaach file
		-> makes id for program(combined)
		*/

		void linkShaders();//combines two shader in 1 program

		void addAttrib(const std::string& attribName);//activate a given attrib(name)

		GLint getUniformLocation(std::string uniformName);// finds a uique id for an uniform

		void use();//sets an attribute to use
		void unUse();//sets to unuse

	private:
		void compileShader(std::string filePath, GLuint id);//compiles individual shaders
		int _numAttribs;//count of the total number of attributes

		GLuint _programID;//unique ids followd
		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;
	};

}