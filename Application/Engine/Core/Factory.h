#pragma once
#include <map>
#include <functional>

namespace ew {
	template<typename Base>
	class CreatorBase {
	public:
		virtual Base* create()const = 0;
	};

	template<typename T, typename Base>
	class Creator : public CreatorBase<Base> {
	public:
		Base* create() const override {
			return new T;
		}
	};

	template<typename Base>
	class Prototype : public CreatorBase<Base> {
	public:
		Prototype(Base* _instance) : instance{ _instance } {}
		Base* create() const override {
			return instance->clone();
		}

	private:
		Base* instance;
	};

	template<typename Base, typename Key>
	class Factory {
	public:
		template<typename T = Base>
		T* Create(Key key);
		void Register(Key key, CreatorBase<Base>* creator);

	protected:
		std::map<Key, CreatorBase<Base>*> registry;
	};


	template<typename Base, typename Key>
	template<typename T>
	inline T* Factory<Base, Key>::Create(Key key) {
		T* object{ nullptr };

		auto iter = registry.find(key);
		if (iter  != registry.end()) {
			CreatorBase<Base>* creator = iter->second;
			object = dynamic_cast<T*>(creator->create());
		}
		return object;
	}
	template<typename Base, typename Key>
	inline void Factory<Base, Key>::Register(Key key, CreatorBase<Base>* creator) {
		registry[key] = creator;
	}
}