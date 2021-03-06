#ifndef MOUSE_LISTENER_H
#define MOUSE_LISTENER_H

#include "common.h"

#define NO_BUTTON          -1
#define MOUSE_BUTTON_LEFT   0
#define MOUSE_BUTTON_MIDDLE 1
#define MOUSE_BUTTON_RIGHT  2

class Window;

class MouseEvent
{
public:
    MouseEvent() : 
        window(NULL), button(NO_BUTTON), x(0), y(0), lastX(0), lastY(0) { }

    MouseEvent(Window* window, INT button, INT x, INT y) : 
        window(window), button(button), x(x), y(y), lastX(x), lastY(y) { }

    MouseEvent(Window* window, INT button, INT x, INT y, INT lastX, INT lastY) : 
        window(window), button(button), x(x), y(y), lastX(lastX), lastY(lastY) { }

    Window* window;
    INT button;
    INT x, y;
    INT lastX, lastY;
};

class MouseListener
{
public:
    virtual ~MouseListener() { };

    virtual void mousePressed(MouseEvent& event);
    virtual void mouseReleased(MouseEvent& event);
    virtual void mouseDoubleClicked(MouseEvent& event);

    virtual void mouseMoved(MouseEvent& event);
    virtual void mouseDragged(MouseEvent& event);

    virtual void mouseWheel(MouseEvent& event);

};

#endif