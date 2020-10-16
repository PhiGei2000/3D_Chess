#include "../../include/Events/EventDispatcher.hpp"

#include <stdexcept>

#pragma region CallbackListCollection
CallbackListCollection::~CallbackListCollection() {
	auto it = m_collection.begin();
	while (it != m_collection.end()) {
		delete (*it).second;

		it = m_collection.erase(it);
	}
}

template<typename EventType>
CallbackList<EventType>& CallbackListCollection::getCallbackList() {
	void* list;
	try {
		list = m_collection.at(typeid(EventType));
	}
	catch (std::out_of_range) {
		list = new CallbackList<EventType>();
		m_collection.emplace(typeid(EventType), list);
	}

	return *(reinterpret_cast<CallbackList<EventType>*>(list));
}

template<typename EventType>
bool CallbackListCollection::contains() const {
	std::type_index info = typeid(EventType);

	return m_collection.contains(info);
}
#pragma endregion

#pragma region EventDispatcher
CallbackListCollection EventDispatcher::m_callbackLists;
CallbackId EventDispatcher::m_cntr = 0;

template<typename EventType>
CallbackId EventDispatcher::addCallback(const EventCallback<EventType>& callback) {
	bool addCallbackList = !m_callbackLists.contains<EventType>();
	CallbackList<EventType>& callbackList = m_callbackLists.getCallbackList<EventType>();
	if (addCallbackList) {
		callbackList = CallbackList<EventType>();
	}


	callbackList[m_cntr] = callback;

	return m_cntr++;
}

template<typename EventType>
void EventDispatcher::invoke(const EventType& event) {
	if (m_callbackLists.contains<EventType>()) {
		const CallbackList<EventType>& callbacks = m_callbackLists.getCallbackList<EventType>();

		for (const auto& [_, callback] : callbacks) {
			callback(event);
		}
	}
}

template CallbackId EventDispatcher::addCallback<WindowSizeEvent>(const EventCallback<WindowSizeEvent>&);
template CallbackId EventDispatcher::addCallback<KeyEvent>(const EventCallback<KeyEvent>&);
template CallbackId EventDispatcher::addCallback<MouseMoveEvent>(const EventCallback<MouseMoveEvent>&);
template CallbackId EventDispatcher::addCallback<ScrollEvent>(const EventCallback<ScrollEvent>&);

template void EventDispatcher::invoke<WindowSizeEvent>(const WindowSizeEvent&);
template void EventDispatcher::invoke<KeyEvent>(const KeyEvent&);
template void EventDispatcher::invoke<MouseMoveEvent>(const MouseMoveEvent&);
template void EventDispatcher::invoke<ScrollEvent>(const ScrollEvent&);

#pragma endregion