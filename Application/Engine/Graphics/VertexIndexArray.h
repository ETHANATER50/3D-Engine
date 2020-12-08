#pragma once
#include "VertexArray.h"

namespace ew {
	class VertexIndexArray : public VertexArray {
	public:
		bool create(const std::string& name, void* null = nullptr) override; 
		void destroy() override; 
		void createIndexBuffer(GLenum indexType, GLsizei count, void* data);
		void draw(GLenum primitiveType = GL_TRIANGLES) override; 
	
	protected:
		GLuint ibo = 0; 
		GLuint indexCount = 0; 
		GLenum indexType = 0;
	};
}