#ifndef UI_HANDLER_HPP
#define UI_HANDLER_HPP

#include <functional>

class ui_handler
{
public:
    typedef std::function<void()> handler_func;

public:
    virtual ~ui_handler() = default;

    virtual void run_on_ui(handler_func handler) = 0;
};

#endif // UI_HANDLER_HPP
