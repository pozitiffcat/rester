#include "rester.h"

#include <map>

#include "../src/history_repository.hpp"
#include "../src/edit_request_presenter.hpp"
#include "../src/edit_request_view.hpp"
#include "../src/edit_body_view.hpp"
#include "../src/edit_history_view.hpp"
#include "../src/edit_body_presenter.hpp"
#include "../src/response_body_presenter.hpp"
#include "../src/edit_history_presenter.hpp"
#include "../src/response_body_view.hpp"
#include "../src/request_sender.hpp"
#include "../src/ui_handler.hpp"

class c_edit_request_view : public edit_request_view
{
public:
    explicit c_edit_request_view(edit_request_view_data *data)
        : _data(data)
    {
    }

    void set_url(const std::string &url)
    {
        _data->set_url(_data, url.c_str());
    }

    std::string get_url() const
    {
        return _data->get_url(_data);
    }

    void set_http_method(http_method method)
    {
        _data->set_http_method(_data, int(method));
    }

    http_method get_http_method() const
    {
        return http_method(_data->get_http_method(_data));
    }

    void set_send_enabled(bool enabled)
    {
        _data->set_send_enabled(_data, int(enabled));
    }

private:
    edit_request_view_data *_data;
};

class c_edit_body_view : public edit_body_view
{
public:
    explicit c_edit_body_view(edit_body_view_data *data)
        : _data(data)
    {
    }

    void set_text(const std::string &text)
    {
        _data->set_text(_data, text.c_str());
    }

    std::string get_text() const
    {
        return _data->get_text(_data);
    }

private:
    edit_body_view_data *_data;
};

class c_response_body_view : public response_body_view
{
public:
    explicit c_response_body_view(response_body_view_data *data)
        : _data(data)
    {
    }

    void set_text(const std::string &text)
    {
        _data->set_text(_data, text.c_str());
    }

private:
    response_body_view_data *_data;
};

class c_edit_history_view : public edit_history_view
{
public:
    explicit c_edit_history_view(edit_history_view_data *data)
        : _data(data)
    {
    }

    void add_history_line(int id, const std::string &url, http_method method)
    {
        _data->add_history_line(_data, id, url.c_str(), int(method));
    }

    int get_current_id() const
    {
        return _data->get_current_id(_data);
    }

    void remove(int id)
    {
        _data->remove(_data, id);
    }

    void show_message(error_message message)
    {
        _data->show_message(_data, int(message));
    }

private:
    edit_history_view_data *_data;
};

class c_ui_handler : public ui_handler
{
public:
    explicit c_ui_handler(ui_handler_handler handler)
        : _handler(handler)
    {
    }

    void run_on_ui(handler_func handler)
    {
        static handler_func hf = handler;

        _handler([] {
            hf();
        });

//        auto target_func = *handler.target<base_function>();
//        if (target_func != nullptr)
//            _func(target_func);

        //todo: else exception
    }

private:
    ui_handler_handler _handler;
};

edit_request_view *new_edit_request_view(struct edit_request_view_data *data)
{
    return new c_edit_request_view(data);
}

void delete_edit_request_view(edit_request_view *view)
{
    delete view;
}

edit_body_view *new_edit_body_view(struct edit_body_view_data *data)
{
    return new c_edit_body_view(data);
}

void delete_edit_body_view(edit_body_view *view)
{
    delete view;
}

response_body_view *new_response_body_view(struct response_body_view_data *data)
{
    return new c_response_body_view(data);
}

void delete_response_body_view(response_body_view *view)
{
    delete view;
}

edit_history_view *new_edit_history_view(struct edit_history_view_data *data)
{
    return new c_edit_history_view(data);
}

void delete_edit_history_view(edit_history_view *view)
{
    delete view;
}

ui_handler *create_ui_handler(ui_handler_handler callback)
{
    return new c_ui_handler(callback);
}

void delete_ui_handler(ui_handler *handler)
{
    delete handler;
}

request_sender *new_request_sender(ui_handler *handler)
{
    return new request_sender(handler);
}

void delete_request_sender(request_sender *sender)
{
    delete sender;
}

history_repository *new_history_repository(const char *dbname)
{
    return new history_repository(dbname);
}

void delete_history_repository(history_repository *repo)
{
    delete repo;
}

edit_request_presenter *new_edit_request_presenter(edit_request_view *view, request_sender *sender, history_repository *repo)
{
    return new edit_request_presenter(view, sender, repo);
}

void delete_edit_request_presenter(edit_request_presenter *presenter)
{
    delete presenter;
}

void edit_request_presenter_on_send_request_clicked(edit_request_presenter *presenter)
{
    presenter->on_send_request_clicked();
}

void edit_request_presenter_on_clear_clicked(edit_request_presenter *presenter)
{
    presenter->on_clear_clicked();
}

void edit_request_presenter_set_response_body_view(edit_request_presenter *presenter, response_body_view *view)
{
    presenter->set_response_body_view(view);
}

void edit_request_presenter_set_edit_body_view(edit_request_presenter *presenter, edit_body_view *view)
{
    presenter->set_edit_body_view(view);
}

void edit_request_presenter_set_edit_history_view(edit_request_presenter *presenter, edit_history_view *view)
{
    presenter->set_edit_history_view(view);
}

edit_body_presenter *new_edit_body_presenter(edit_body_view *view)
{
    return new edit_body_presenter(view);
}

void delete_edit_body_presenter(edit_body_presenter *presenter)
{
    delete presenter;
}

void edit_body_presenter_on_clear_clicked(edit_body_presenter *presenter)
{
    presenter->on_clear_clicked();
}

response_body_presenter *new_response_body_presenter(response_body_view *view)
{
    return new response_body_presenter(view);
}

void delete_response_body_presenter(response_body_presenter *presenter)
{
    delete presenter;
}

void response_body_presenter_on_clear_clicked(response_body_presenter *presenter)
{
    presenter->on_clear_clicked();
}

edit_history_presenter *new_edit_history_presenter(edit_history_view *view, history_repository *repo)
{
    return new edit_history_presenter(view, repo);
}

void delete_edit_history_presenter(edit_history_presenter *presenter)
{
    delete presenter;
}

void edit_history_presenter_on_item_clicked(edit_history_presenter *presenter)
{
    presenter->on_item_clicked();
}

void edit_history_presenter_on_remove_clicked(edit_history_presenter *presenter)
{
    presenter->on_remove_clicked();
}

void edit_history_presenter_set_edit_request_view(edit_history_presenter *presenter, edit_request_view *view)
{
    presenter->set_edit_request_view(view);
}

void edit_history_presenter_set_edit_body_view(edit_history_presenter *presenter, edit_body_view *view)
{
    presenter->set_edit_body_view(view);
}

void edit_history_presenter_set_response_body_view(edit_history_presenter *presenter, response_body_view *view)
{
    presenter->set_response_body_view(view);
}
