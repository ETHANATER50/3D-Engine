#include "pch.h"
#include "Texture.h"
#include "Renderer.h"

namespace ew {
	bool Texture::create(const std::string& name, void* _renderer) {
		renderer = static_cast<Renderer*>(_renderer)->renderer;
		SDL_Surface* surface = nullptr;// IMG_Load(name.c_str());
		if (surface == nullptr) {
			std::cout << "Error: " << SDL_GetError() << std::endl;
			return false;
		}
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		if (texture == nullptr) {
			std::cout << "Error: " << SDL_GetError() << std::endl;
			return false;
		}
		return true;
	}

	void Texture::destroy() {
		SDL_DestroyTexture(texture);
	}
}

