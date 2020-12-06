#include "pch.h"
#include "Renderer.h"
#include "glad/glad.h"

namespace ew {
	bool Renderer::startup() {
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
			return false;
		}
		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
		return true;
	}

	void Renderer::shutdown() {

		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(window);
	}

	void Renderer::update() {
	}
	bool Renderer::create(const std::string& name, int width, int height) {
		window = SDL_CreateWindow(name.c_str(), 100, 100, width, height, SDL_WINDOW_OPENGL);

		if (window == nullptr) {
			SDL_Log("Failed to create window: %s", SDL_GetError());
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
		//SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetSwapInterval(1);
		context = SDL_GL_CreateContext(window);
		if (!gladLoadGL()) {
			SDL_Log("Failed to create OpenGL context");
			exit(-1);
		}
		return true;
	}
	void Renderer::beginFrame() {
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void Renderer::endFrame() {
		SDL_GL_SwapWindow(window);
	}
}

