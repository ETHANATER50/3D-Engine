#pragma once

#include <glad/glad.h>

#include <vector>

#include "Graphics/Renderer.h"
#include "Graphics/Program.h"
#include "Graphics/Texture.h"
#include "Graphics/Model.h"

#include "Resources/ResourceManager.h"
#include "Input/InputSystem.h"

#include "Core/Timer.h"
#include "Core/File.h"
#include "Core/Assert.h"



namespace ew {
	class Engine {
	public:

		bool startup();
		void shutdown();

		void update();

		template<typename T>
		T* getSystem();

		FrameTimer& getTimer() { return timer; }

	protected:
		std::vector<class System*> systems;
		FrameTimer timer;
	};

	template<typename T>
	T* Engine::getSystem() {
		T* result{ nullptr };
		for (auto system : systems) {
			result = dynamic_cast<T*>(system);
			if (result) break;
		}
		return result;
	}
}