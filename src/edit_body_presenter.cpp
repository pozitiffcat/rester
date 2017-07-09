#include "edit_body_presenter.hpp"

#include "edit_body_view.hpp"

edit_body_presenter::edit_body_presenter(edit_body_view *view)
    : _edit_body_view(view)
{
}

void edit_body_presenter::on_clear_clicked()
{
    _edit_body_view->set_text({});
}
