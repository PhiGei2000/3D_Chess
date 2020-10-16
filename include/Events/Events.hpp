#pragma once

class GameWindow;

struct Event {
    GameWindow* window;

    Event(GameWindow* window);
};

struct WindowSizeEvent : public Event {
    int width;
    int height;

    WindowSizeEvent(GameWindow* window, int width, int height);
};

struct KeyEvent : public Event {
    int key;
    int scancode;
    int action;
    int mods;

    KeyEvent(GameWindow* window, int key, int scancode, int action, int mods);
};

struct MouseMoveEvent : public Event {
    double prevX;
    double prevY;
    double x;
    double y;

    MouseMoveEvent(GameWindow* window, double prevX, double prevY, double x, double y);
};

struct ScrollEvent : public Event {
    double dx;
    double dy;

    ScrollEvent(GameWindow* window, double dx, double dy);
};
