#include "edit_request_presenter.hpp"

#include "edit_request_view.hpp"
#include "edit_body_view.hpp"
#include "response_body_view.hpp"
#include "edit_history_view.hpp"
#include "request_sender.hpp"
#include "history_repository.hpp"

edit_request_presenter::edit_request_presenter(edit_request_view *view, request_sender *sender, history_repository *repository)
    : _edit_request_view(view),
      _request_sender(sender),
      _history_repository(repository)
{
}

void edit_request_presenter::set_edit_body_view(edit_body_view *view)
{
    _edit_body_view = view;
}

void edit_request_presenter::set_response_body_view(response_body_view *view)
{
    _response_body_view = view;
}

void edit_request_presenter::set_edit_history_view(edit_history_view *view)
{
    _edit_history_view = view;
}

void edit_request_presenter::on_send_request_clicked()
{
    const std::string url = _edit_request_view->get_url();
    const http_method method = _edit_request_view->get_http_method();
    const std::string body = _edit_body_view != nullptr ? _edit_body_view->get_text() : std::string{};

    _edit_request_view->set_send_enabled(false);

    _request_sender->send_request(url, method, body, [this, url, method, body] (auto e, auto b) {
        _edit_request_view->set_send_enabled(true);
        int id = _history_repository->add_entry({0, url, method, body, b});

        if (_response_body_view != nullptr)
            _response_body_view->set_text(b);

        if (_edit_history_view != nullptr)
            _edit_history_view->add_history_line(id, url, method);
    });
}

void edit_request_presenter::on_clear_clicked()
{
    _edit_request_view->set_url({});
    _edit_request_view->set_http_method(http_method::GET_HTTP_METHOD);

    if (_edit_body_view != nullptr)
        _edit_body_view->set_text({});
}
