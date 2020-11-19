#pragma once

#include "../Core/System.h"
#include <string>
#include <SDL.h>

namespace ew {
	class Renderer : public System{
	public:

		virtual bool startup() override;
		virtual void shutdown() override;
		virtual void update() override;

		bool create(const std::string& name, int width, int height);
		void beginFrame();
		void endFrame();

		friend class Texture;

	protected:
		SDL_Window* window{ nullptr };
		SDL_Renderer* renderer{ nullptr };
		SDL_GLContext context;
	};
}