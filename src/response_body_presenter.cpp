#include "response_body_presenter.hpp"

#include "response_body_view.hpp"

response_body_presenter::response_body_presenter(response_body_view *view)
    : _response_body_view(view)
{
}

void response_body_presenter::on_clear_clicked()
{
    _response_body_view->set_text({});
}
