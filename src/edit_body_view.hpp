#ifndef EDIT_BODY_VIEW_HPP
#define EDIT_BODY_VIEW_HPP

#include <string>

class edit_body_view
{
public:
    virtual ~edit_body_view() = default;

    virtual void set_text(const std::string &text) = 0;
    virtual std::string get_text() const = 0;
};

#endif // EDIT_BODY_VIEW_HPP
