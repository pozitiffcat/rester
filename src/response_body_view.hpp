#ifndef RESPONSE_BODY_VIEW_HPP
#define RESPONSE_BODY_VIEW_HPP

#include <string>

class response_body_view
{
public:
    virtual ~response_body_view() = default;

    virtual void set_text(const std::string &text) = 0;
};

#endif // RESPONSE_BODY_VIEW_HPP
