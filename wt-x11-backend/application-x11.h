#include <X11/Xlib.h>

#include <map>

class WindowX11;

class ApplicationX11
{
public:
    ApplicationX11();
    ~ApplicationX11();

    void run();

    static ApplicationX11 *instance();

    void addWindow(WindowX11 * win);

private:
    void leaveEventLoop();

    bool                        m_running;
    std::map<Window,WindowX11*> m_windows;
    static ApplicationX11*      m_instance;

    friend class WindowX11;
};
