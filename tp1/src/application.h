#ifndef APPLICATION
#define APPLICATION

#include "common.h"
#include "keyboard_listener.h"
#include "mouse_listener.h"
#include "window_listener.h"

class CommandLine;
class Window;
class Logger;

class Application : public KeyboardListener, MouseListener, WindowListener
{
public:
    Application(CommandLine* commandLine);
    virtual ~Application();

    void start();
    void stop();

    inline Logger* getLogger();

    virtual void   windowClosed(WindowEvent& event);

protected:
    Application(const Application&);
    Application& operator=(const Application& rightSide);

    virtual void    consumeCommandLine();
    virtual void    initialize();

    virtual void    process() = 0;
    virtual STRING& getName() = 0;

    CommandLine* mCommandLine;
    BOOL         mIsWindowed;
    BOOL         mContinueApplication;
    Logger*      mLogger;
    Window*      mWindow;

};

#include "application.inl"

#endif