#include "pch.h"
#include "Engine.h"

namespace ew {
	bool Engine::startup() {
		srand(static_cast<unsigned int>(time(nullptr)));

		systems.push_back(new Renderer);
		systems.push_back(new ResourceManager);
		systems.push_back(new InputSystem);

		for (auto system : systems) {
			system->startup();
		}

		getSystem<Renderer>()->create("GAT350", 800, 600);


		return true;
	}

	void Engine::shutdown() {
		for (auto system : systems) {
			system->shutdown();
			delete system;
		}
		systems.clear();
		SDL_Quit();
	}

	void Engine::update() {
		timer.tick();
		for (auto system : systems) {
			system->update();
		}
	}

}