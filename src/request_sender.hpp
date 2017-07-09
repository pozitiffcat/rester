#ifndef REQUEST_SENDER_HPP
#define REQUEST_SENDER_HPP

#include <map>
#include <string>
#include <functional>

#include "http_method.hpp"

class ui_handler;

class request_sender
{
public:
    typedef std::function<void (int, const std::string &)> handler_func;

public:
    explicit request_sender(ui_handler *handler);

    void send_request(const std::string &url, http_method method, const std::string &body, handler_func handler);

private:
    ui_handler *_ui_handler;
    std::map<http_method, std::string> _http_method_name_map;
};

#endif // REQUEST_SENDER_HPP
