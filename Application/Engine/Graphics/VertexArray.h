#pragma once
#include "../Resources/Resource.h"
#include "../../pch.h"

namespace ew {
	class VertexArray : public Resource{
	public:
		bool create(const std::string& name, void* null = nullptr) override; 
		void destroy() override; 
		void createBuffer(GLsizei size, GLsizei count, void* data); 
		void setAttribute(int index, GLint size, GLsizei stride, size_t offset); 
		virtual void draw(GLenum primitiveType = GL_TRIANGLES); void Bind() { glBindVertexArray(vao); }
	protected:
		GLuint count = 0;
		GLuint vao = 0;
		std::vector<GLuint> vbos;
	};
}