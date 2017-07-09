#ifndef EDIT_REQUEST_PRESENTER_HPP
#define EDIT_REQUEST_PRESENTER_HPP

class edit_request_view;
class edit_body_view;
class response_body_view;
class edit_history_view;
class request_sender;
class history_repository;

class edit_request_presenter
{
public:
    edit_request_presenter(edit_request_view *view, request_sender *sender, history_repository *repository);

    void set_edit_body_view(edit_body_view *view);
    void set_response_body_view(response_body_view *view);
    void set_edit_history_view(edit_history_view *view);

    void on_send_request_clicked();
    void on_clear_clicked();

private:
    edit_request_view * const _edit_request_view;
    request_sender * const _request_sender;
    history_repository *const _history_repository;
    edit_body_view *_edit_body_view = nullptr;
    response_body_view *_response_body_view = nullptr;
    edit_history_view *_edit_history_view = nullptr;
};

#endif // EDIT_REQUEST_PRESENTER_HPP
