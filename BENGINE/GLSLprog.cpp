
#include "GLSLprog.h"
#include "Error.h"
#include<fstream>

#include<vector>

namespace bengine
{
	GLSLprog::GLSLprog() :_numAttribs(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0)
	{
	}


	GLSLprog::~GLSLprog()
	{
	}

	void GLSLprog::use()
	{
		glUseProgram(_programID);
		for (int i = 0; i < _numAttribs; i++)
			glEnableVertexAttribArray(i);
	}
	void GLSLprog::unUse()
	{
		glUseProgram(0);
		for (int i = 0; i < _numAttribs; i++)
			glDisableVertexAttribArray(i);
	}
	void GLSLprog::compileShaders(const std::string& vertexShaderFP, const std::string& fragmentShaderFP)
	{
		_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (_vertexShaderID == 0)
			fatalError(" fatal error: vertexShader not initialized");
		_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (_fragmentShaderID == 0)
			fatalError(" fatal error: fragmentShader not initialized");


		//vertex compile
		compileShader(vertexShaderFP, _vertexShaderID);

		//fragment compile
		compileShader(fragmentShaderFP, _fragmentShaderID);

		_programID = glCreateProgram();

	}

	void GLSLprog::linkShaders()
	{
		//Vertex and fragment shaders are successfully compiled.
		//Now time to link them together into a program.
		//Get a program object.


		//Attach our shaders to our program
		glAttachShader(_programID, _vertexShaderID);
		glAttachShader(_programID, _fragmentShaderID);

		//Link our program
		glLinkProgram(_programID);


		//error checking
		//Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLog[0]);

			//We don't need the program anymore.
			glDeleteProgram(_programID);
			//Don't leak shaders either.
			glDeleteShader(_vertexShaderID);
			glDeleteShader(_fragmentShaderID);



			//error print and exit
			std::printf("%s\n", &infoLog[0]);//trick

			fatalError("Shader failed to link!!!!!!!!!!!");

		}

		//Always detach shaders after a successful link.
		glDetachShader(_programID, _vertexShaderID);
		glDetachShader(_programID, _fragmentShaderID);



	}

	void GLSLprog::compileShader(std::string filePath, GLuint id)
	{
		//open as file

		std::ifstream shaderFile(filePath);
		if (shaderFile.fail())
			fatalError("cannot open" + filePath);

		//all content in one string
		std::string fileContents = "";

		std::string line;
		while (std::getline(shaderFile, line))
		{
			fileContents += line + "\n";//adding content to one string
		}
		shaderFile.close();
		const char* contentsPtr = fileContents.c_str(); //trick for bellow
		glShaderSource(id, 1, &contentsPtr, nullptr);

		glCompileShader(id);


		//error check 
		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			// Provide the infolog in whatever manor you deem best.
			// Exit with failure.
			glDeleteShader(id); // Don't leak the shader.

			std::printf("%s\n", &errorLog[0]);//trick

			fatalError("Shader" + filePath + "failed to compile");

		}


	}


	void GLSLprog::addAttrib(const std::string& attribName)
	{
		glBindAttribLocation(_programID, _numAttribs++, attribName.c_str());

	}

	GLint GLSLprog::getUniformLocation(std::string uniformName)
	{
		GLint location = glGetUniformLocation(_programID, uniformName.c_str());
		if (location == GL_INVALID_INDEX)
			fatalError("Uniform " + uniformName + " not found");
		return location;

	}
}