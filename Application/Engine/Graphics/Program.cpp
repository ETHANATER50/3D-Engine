#include "pch.h"
#include "Program.h"

namespace ew {
	bool Program::create(const std::string& name, void* null)
	{
		return true;
	}
	void Program::destroy()
	{
		if (program == 0) {
			return;
		}
		GLint num_shaders = 0;
		glGetProgramiv(program, GL_ATTACHED_SHADERS, &num_shaders);
		std::vector<GLuint> shaders{ (GLuint)num_shaders };
		glGetAttachedShaders(program, num_shaders, NULL, shaders.data());

		for (GLuint shader : shaders) {
			glDetachShader(program, shader);
			glDeleteShader(shader);
		}

		glDeleteProgram(program);
	}
	void Program::createShaderFromFile(const std::string& filename, GLenum shader_type)
	{
		if (program == 0) { program = glCreateProgram(); }
		std::string source;
		bool success = readFileToString(filename.c_str(), source);
		if (success == false){
			SDL_Log("Error: Failed to open file (%s).", filename.c_str());
		}
		createShaderFromSource(source, shader_type);
	}
	void Program::createShaderFromSource(const std::string& source, GLenum shader_type)
	{
		GLuint shader = glCreateShader(shader_type);
		
		const char* source_c = source.c_str();
		glShaderSource(shader, 1, &source_c, NULL);
		glCompileShader(shader);
		
		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE) {

			GLint length = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

			if (length > 0) {
				std::string infoLog(length, ' ');
				glGetShaderInfoLog(shader, length, &length, &infoLog[0]);
				SDL_Log("Error: Failed to compile shader.");
				SDL_Log("Shader Info: %s", infoLog.c_str());
			}
			glDeleteShader(shader);
		}
		else {
			glAttachShader(program, shader);
		}
	}
	void Program::link()
	{
		ASSERT(program != 0); 

		if (linked) return;
		
		glLinkProgram(program);
		
		GLint status;
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if (status == GL_FALSE) {
			GLint length = 0;
			glGetShaderiv(program, GL_INFO_LOG_LENGTH, &length);
			if (length > 0) {
				std::string infoLog(length, ' ');
				glGetProgramInfoLog(program, length, &length, &infoLog[0]);
				SDL_Log("Error: Failed to link program.");
				SDL_Log("Program Info: %s", infoLog.c_str());
			}
			glDeleteProgram(program);
		}
		else {linked = true;}
	}
	void Program::use()
	{
		ASSERT(program && linked); 
		
		glUseProgram(program);
	}
	void Program::setUniform(const std::string& name, float x, float y, float z)
	{
		GLint uniform = getUniform(name); 
		glUniform3f(uniform, x, y, z);
	}
	void Program::setUniform(const std::string& name, const glm::vec2& v2)
	{
		GLint uniform = getUniform(name); 
		glUniform2f(uniform, v2.x, v2.y);
	}
	void Program::setUniform(const std::string& name, const glm::vec3& v3)
	{
		GLint uniform = getUniform(name); 
		glUniform3f(uniform, v3.x, v3.y, v3.z);
	}
	void Program::setUniform(const std::string& name, const glm::vec4& v4)
	{
		GLint uniform = getUniform(name); 
		glUniform4f(uniform, v4.x, v4.y, v4.z, v4.w);
	}
	void Program::setUniform(const std::string& name, const glm::mat4& mx4)
	{
		GLint uniform = getUniform(name); 
		glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(mx4));
	}
	void Program::setUniform(const std::string& name, const glm::mat3& mx3)
	{
		GLint uniform = getUniform(name); 
		glUniformMatrix3fv(uniform, 1, GL_FALSE, glm::value_ptr(mx3));
	}
	void Program::setUniform(const std::string& name, float value)
	{
		GLint uniform = getUniform(name); 
		glUniform1f(uniform, value);
	}
	void Program::setUniform(const std::string& name, int value)
	{
		GLint uniform = getUniform(name); 
		glUniform1i(uniform, value);
	}
	void Program::setUniform(const std::string& name, bool value)
	{
		GLint uniform = getUniform(name); 
		glUniform1i(uniform, value);
	}
	void Program::setUniform(const std::string& name, GLuint value)
	{
		GLint uniform = getUniform(name); 
		glUniform1ui(uniform, value);
	}
	GLint Program::getUniform(const std::string& name)
	{
		auto uniform = uniforms.find(name); 
		if (uniform == uniforms.end()) {
			uniforms[name] = glGetUniformLocation(program, name.c_str());
		}
		return uniforms[name];
	}
}