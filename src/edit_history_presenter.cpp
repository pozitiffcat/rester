#include "edit_history_presenter.hpp"

#include "edit_request_view.hpp"
#include "edit_body_view.hpp"
#include "response_body_view.hpp"
#include "edit_history_view.hpp"
#include "history_repository.hpp"

edit_history_presenter::edit_history_presenter(edit_history_view *view, history_repository *repository)
    : _edit_history_view(view),
      _history_repository(repository)
{
    const std::list<history_repository::entry> &history_entry_list = _history_repository->get_entry_list();

    for (const history_repository::entry &e : history_entry_list)
    {
        _edit_history_view->add_history_line(e.id, e.url, e.method);
    }
}

void edit_history_presenter::on_item_clicked()
{
    const int id = _edit_history_view->get_current_id();

    if (_history_repository->has_entry(id))
    {
        const history_repository::entry entry = _history_repository->get_entry(id);

        if (_edit_request_view != nullptr)
        {
            _edit_request_view->set_url(entry.url);
            _edit_request_view->set_http_method(entry.method);
        }

        if (_edit_body_view != nullptr)
            _edit_body_view->set_text(entry.body);

        if (_response_body_view != nullptr)
            _response_body_view->set_text(entry.response);
    }
    else
    {
        _edit_history_view->show_message(error_message::INDEX_OUT_OF_BOUNDS);
    }
}

void edit_history_presenter::on_remove_clicked()
{
    const int id = _edit_history_view->get_current_id();

    if (_history_repository->has_entry(id))
    {
        _edit_history_view->remove(id);
        _history_repository->remove_entry(id);
    }
    else
    {
        _edit_history_view->show_message(error_message::INDEX_OUT_OF_BOUNDS);
    }
}

void edit_history_presenter::set_edit_request_view(edit_request_view *view)
{
    _edit_request_view = view;
}

void edit_history_presenter::set_edit_body_view(edit_body_view *view)
{
    _edit_body_view = view;
}

void edit_history_presenter::set_response_body_view(response_body_view *view)
{
    _response_body_view = view;
}
