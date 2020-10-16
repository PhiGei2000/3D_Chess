#pragma once
#include "Events.hpp"

#include <functional>
#include <typeinfo>
#include <typeindex>
#include <map>
#include <vector>

#define SUBSCRIBE(EventType, callback) EventDispatcher::addCallback<EventType>([&](const EventType& e) { callback(e);})

template<typename EventType>
using EventCallback = std::function<void(const EventType&)>;
typedef unsigned int CallbackId;

template<typename EventType>
using CallbackList = std::map<CallbackId, EventCallback<EventType>>;

struct CallbackListCollection {
private:
	std::map<std::type_index, void*> m_collection;

public:
	CallbackListCollection() = default;
	~CallbackListCollection();

	template<typename EventType>
	CallbackList<EventType>& getCallbackList();	

	template<typename EventType>
	bool contains() const;
};


class EventDispatcher {
private:
	static CallbackListCollection m_callbackLists;

	static CallbackId m_cntr;		

public:	
	template<typename EventType>
	static CallbackId addCallback(const EventCallback<EventType>& callback);

	template<typename EventType>
	static void removeCallback(const CallbackId& id);
	
	template<typename EventType>
	static void invoke(const EventType& event);
};
