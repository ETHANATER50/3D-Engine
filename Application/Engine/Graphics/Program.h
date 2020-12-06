#pragma once

#include "../Resources/Resource.h"
#include <pch.cpp>

namespace ew {
	class Program : public Resource {
	public:
		
		bool create(const std::string& name, void* null) override;
		void destroy() override;

		void createShaderFromFile(const std::string& filename, GLenum shader_type);
		void createShaderFromSource(const std::string& source, GLenum shader_type);

		void link();
		void use();

		GLuint getProgramID() { return program; }

		bool IsLinked() { return linked; }
		
		void setUniform(const std::string& name, float x, float y, float z); 
		void setUniform(const std::string& name, const glm::vec2& v2); 
		void setUniform(const std::string& name, const glm::vec3& v3); 
		void setUniform(const std::string& name, const glm::vec4& v4); 
		void setUniform(const std::string& name, const glm::mat4& mx4); 
		void setUniform(const std::string& name, const glm::mat3& mx3); 
		void setUniform(const std::string& name, float value); 
		void setUniform(const std::string& name, int value); 
		void setUniform(const std::string& name, bool value); 
		void setUniform(const std::string& name, GLuint value);

	private:
		GLint getUniform(const std::string& name);

	private:
		GLuint program{ 0 };
		bool linked{ false };
		std::map<std::string, GLuint> uniforms;
	};
}