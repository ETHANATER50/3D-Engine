#pragma once

#include <SDL.h>
#include "../Resources/Resource.h"
#include <string>


namespace ew {
	class Texture : public Resource{
	public:
		bool create(const std::string& name, void* _renderer) override;
		void destroy() override;

	protected:
		SDL_Texture* texture{ nullptr };
		SDL_Renderer* renderer{ nullptr };
	};
}