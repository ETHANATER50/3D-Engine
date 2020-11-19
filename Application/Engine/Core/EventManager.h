#pragma once
#include "Singleton.h"
#include <string>
#include <list>
#include <map>
#include <functional>

namespace ew {
	class Object;

	struct Event {
		std::string type;
		Object* sender{ nullptr };
		Object* reciever{ nullptr };
		void* data;
	};

	class EventManager : public Singleton<EventManager> {
	public:
		using function_t = std::function<void(const Event&)>;

		struct Observer {
			function_t function;
			Object* owner{ nullptr };
		};

	public:
		void subscribe(const std::string& type, function_t function, Object* owner = nullptr);
		void notify(const Event& event);

	private:
		std::map<std::string, std::list<Observer>> observers;
	};
}
