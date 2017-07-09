#ifndef RESPONSE_BODY_PRESENTER_HPP
#define RESPONSE_BODY_PRESENTER_HPP

class response_body_view;

class response_body_presenter
{
public:
    explicit response_body_presenter(response_body_view *view);

    void on_clear_clicked();

private:
    response_body_view * const _response_body_view;
};

#endif // RESPONSE_BODY_PRESENTER_HPP
