#ifndef EDIT_REQUEST_VIEW_HPP
#define EDIT_REQUEST_VIEW_HPP

#include <string>

#include "http_method.hpp"

class edit_request_view
{
public:
    virtual ~edit_request_view() = default;

    virtual void set_url(const std::string &url) = 0;
    virtual std::string get_url() const = 0;

    virtual void set_http_method(http_method method) = 0;
    virtual http_method get_http_method() const = 0;

    virtual void set_send_enabled(bool enabled) = 0;
};

#endif // EDIT_REQUEST_VIEW_HPP
