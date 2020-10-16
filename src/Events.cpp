#include "../include/Events.hpp"

#include "../include/GameWindow.hpp"

Event::Event(GameWindow* window)
    : window{window} {
}

WindowSizeEvent::WindowSizeEvent(GameWindow* window, int width, int height)
    : Event{window}, width{width}, height{height} {
}

KeyEvent::KeyEvent(GameWindow* window, int key, int scancode, int action, int mods)
    : Event{window}, key{key}, scancode{scancode}, action{action}, mods{mods} {
}

MouseMoveEvent::MouseMoveEvent(GameWindow* window, double prevX, double prevY, double x, double y)
    : Event{window}, prevX{prevX}, prevY{prevY}, x{x}, y{y} {
}

ScrollEvent::ScrollEvent(GameWindow* window, double dx, double dy)
    : Event{window}, dx{dx}, dy{dy} {
}
