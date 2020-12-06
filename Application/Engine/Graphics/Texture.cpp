#include "pch.h"
#include "Texture.h"
#include "Renderer.h"

namespace ew {
	bool Texture::create(const std::string& name, void* null) { 
		return createTexture(name); 
	}    
	void Texture::destroy() { 
		glDeleteTextures(1, &texture); 
	}    
	bool Texture::createTexture(const std::string& filename, GLenum target, GLuint unit) {
		SDL_Surface* surface = IMG_Load(filename.c_str());
		if (surface == nullptr) {
			SDL_Log("Failed to create surface: %s", SDL_GetError());
			return false; 
		}
		glGenTextures(1, &texture);
		glBindTexture(target, texture);
		GLenum format = (surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D(target, 0, format, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP);
        return true;
	}
}

