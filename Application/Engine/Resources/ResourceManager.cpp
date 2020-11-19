#include "pch.h"
#include "ResourceManager.h"


namespace ew {
	bool ResourceManager::startup() {
		return true;
	}

	void ResourceManager::shutdown() {
		removeAll();
	}

	void ResourceManager::update() {

	}

	void ResourceManager::removeAll() {
		for (auto resource : resources) {
			resource.second->destroy();
			delete resource.second;
		}

		resources.clear();
	}

}
