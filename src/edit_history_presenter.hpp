#ifndef EDIT_HISTORY_PRESENTER_HPP
#define EDIT_HISTORY_PRESENTER_HPP

class edit_request_view;
class edit_body_view;
class response_body_view;
class edit_history_view;
class history_repository;

class edit_history_presenter
{
public:
    edit_history_presenter(edit_history_view *view, history_repository *repository);

    void on_item_clicked();
    void on_remove_clicked();

    void set_edit_request_view(edit_request_view *view);
    void set_edit_body_view(edit_body_view *view);
    void set_response_body_view(response_body_view *view);

private:
    edit_history_view *_edit_history_view;
    history_repository *_history_repository;
    edit_request_view *_edit_request_view = nullptr;
    edit_body_view *_edit_body_view = nullptr;
    response_body_view *_response_body_view = nullptr;
};

#endif // EDIT_HISTORY_PRESENTER_HPP
