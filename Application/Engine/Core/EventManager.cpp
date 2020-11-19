#include "pch.h"
#include "EventManager.h"

namespace ew {
	void EventManager::subscribe(const std::string& type, function_t function, Object* owner) {
		Observer observer;
		observer.function = function;
		observer.owner = owner;

		observers[type].push_back(observer);
	}

	void EventManager::notify(const Event& event) {
		auto _observers = observers[event.type];
		for (auto& observer : _observers) {
			if(event.reciever == nullptr || event.reciever == observer.owner)
			observer.function(event);
		}
	}

}

