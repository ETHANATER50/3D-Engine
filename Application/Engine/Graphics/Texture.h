#pragma once

#include <SDL.h>
#include "../Resources/Resource.h"
#include <string>


namespace ew {
	class Texture : public Resource{
	public:
		bool create(const std::string& name, void* _renderer) override;
		void destroy() override;

		bool createTexture(const std::string& filename, GLenum target = GL_TEXTURE_2D, GLuint unit = GL_TEXTURE0);

	protected:
		GLenum target{ GL_TEXTURE_2D }; 
		GLuint unit{ GL_TEXTURE0 }; 
		GLuint texture{ 0 };
	};
}