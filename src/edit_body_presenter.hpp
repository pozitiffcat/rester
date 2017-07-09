#ifndef EDIT_BODY_PRESENTER_HPP
#define EDIT_BODY_PRESENTER_HPP

class edit_body_view;

class edit_body_presenter
{
public:
    explicit edit_body_presenter(edit_body_view *view);

    void on_clear_clicked();

private:
    edit_body_view *_edit_body_view;
};

#endif // EDIT_BODY_PRESENTER_HPP
