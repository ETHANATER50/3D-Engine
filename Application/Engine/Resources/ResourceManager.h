#pragma once
#include "../Core/System.h"
#include "Resource.h"
#include <map>

namespace ew {
	class ResourceManager : public System {
	public:

		virtual bool startup() override;
		virtual void shutdown() override;
		virtual void update() override;

		template<typename T>
		T* get(const std::string& name, void* data = nullptr);

		void removeAll();

	protected:
		std::map<std::string, Resource*> resources;

	};
	template<typename T>
	inline T* ResourceManager::get(const std::string& name, void* data) {
		T* resource = dynamic_cast<T*>(resources[name]);
		if (!resource) {
			resource = new T;
			resource->create(name, data);

			resources[name] = resource;
		}
		return resource;
	}
}