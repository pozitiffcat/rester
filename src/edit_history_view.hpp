#ifndef EDIT_HISTORY_VIEW_HPP
#define EDIT_HISTORY_VIEW_HPP

#include <string>

#include "http_method.hpp"
#include "error_message.hpp"

class edit_history_view
{
public:
    virtual ~edit_history_view() = default;

    virtual void add_history_line(int id, const std::string &url, http_method method) = 0;
    virtual int get_current_id() const = 0;
    virtual void remove(int id) = 0;

    virtual void show_message(error_message message) = 0;
};

#endif // EDIT_HISTORY_VIEW_HPP
