#ifndef CLIB_RESTER_H
#define CLIB_RESTER_H

#ifdef __cplusplus
extern "C" {
#endif

/* defines for http_method */
#define HTTP_METHOD_GET 0
#define HTTP_METHOD_POST 1
#define HTTP_METHOD_PUT 2
#define HTTP_METHOD_DELETE 3

/* defines for error_message */
#define ERROR_MESSAGE_INDEX_OUT_OF_BOUNDS 0

/* other types */
typedef struct ui_handler ui_handler;
typedef struct request_sender request_sender;
typedef struct history_repository history_repository;

/* presenter types */
typedef struct edit_request_presenter edit_request_presenter;
typedef struct edit_body_presenter edit_body_presenter;
typedef struct response_body_presenter response_body_presenter;
typedef struct edit_history_presenter edit_history_presenter;

/* view types */
typedef struct edit_request_view edit_request_view;
typedef struct edit_body_view edit_body_view;
typedef struct response_body_view response_body_view;
typedef struct edit_history_view edit_history_view;

/* edit_request_view_data */
typedef struct edit_request_view_data edit_request_view_data;
typedef void(*edit_request_view_data_set_url_handler)(struct edit_request_view_data *data, const char *url);
typedef const char *(*edit_request_view_data_get_url_handler)(struct edit_request_view_data *data);
typedef void(*edit_request_view_data_set_http_method_handler)(struct edit_request_view_data *data, int method);
typedef int(*edit_request_view_data_get_http_method_handler)(struct edit_request_view_data *data);
typedef void(*edit_request_view_data_set_send_enabled_handler)(struct edit_request_view_data *data, int enabled);
struct edit_request_view_data
{
    edit_request_view_data_set_url_handler set_url;
    edit_request_view_data_get_url_handler get_url;
    edit_request_view_data_set_http_method_handler set_http_method;
    edit_request_view_data_get_http_method_handler get_http_method;
    edit_request_view_data_set_send_enabled_handler set_send_enabled;
    void *user_data;
};

/* edit_body_view_data */
typedef struct edit_body_view_data edit_body_view_data;
typedef void(*edit_body_view_data_set_text_handler)(struct edit_body_view_data *data, const char *text);
typedef const char *(*edit_body_view_data_get_text_handler)(struct edit_body_view_data *data);
struct edit_body_view_data
{
    edit_body_view_data_set_text_handler set_text;
    edit_body_view_data_get_text_handler get_text;
    void *user_data;
};

/* response_body_view_data */
typedef struct response_body_view_data response_body_view_data;
typedef void(*response_body_view_data_set_text_handler)(struct response_body_view_data *data, const char *text);
typedef const char *(*response_body_view_data_get_text_handler)(struct response_body_view_data *data);
struct response_body_view_data
{
    response_body_view_data_set_text_handler set_text;
    response_body_view_data_get_text_handler get_text;
    void *user_data;
};

/* edit_history_view_data */
typedef struct edit_history_view_data edit_history_view_data;
typedef void(*edit_history_view_data_add_history_line_handler)(struct edit_history_view_data *data, int id, const char *url, int method);
typedef int(*edit_history_view_data_get_current_id_handler)(struct edit_history_view_data *data);
typedef void(*edit_history_view_data_remove_handler)(struct edit_history_view_data *data, int id);
typedef void(*edit_history_view_data_show_message_handler)(struct edit_history_view_data *data, int error_message);
struct edit_history_view_data
{
    edit_history_view_data_add_history_line_handler add_history_line;
    edit_history_view_data_get_current_id_handler get_current_id;
    edit_history_view_data_remove_handler remove;
    edit_history_view_data_show_message_handler show_message;
    void *user_data;
};

/* ui_handler functions */
typedef void(*ui_handler_handler)(void(*runnable)());
ui_handler *create_ui_handler(ui_handler_handler callback);
void delete_ui_handler(ui_handler *handler);

/* request_sender functions */
request_sender *new_request_sender(ui_handler *handler);
void delete_request_sender(request_sender *sender);

/* history_repository funtions */
history_repository *new_history_repository(const char *dbname);
void delete_history_repository(history_repository *repo);

/* edit_request_view functions */
edit_request_view *new_edit_request_view(struct edit_request_view_data *data);
void delete_edit_request_view(edit_request_view *view);

/* edit_body_view functions */
edit_body_view *new_edit_body_view(struct edit_body_view_data *data);
void delete_edit_body_view(edit_body_view *view);

/* response_body_view functions */
response_body_view *new_response_body_view(struct response_body_view_data *data);
void delete_response_body_view(response_body_view *view);

/* edit_history_view functions */
edit_history_view *new_edit_history_view(struct edit_history_view_data *data);
void delete_edit_history_view(edit_history_view *view);

/* edit_request_presenter functions */
edit_request_presenter *new_edit_request_presenter(edit_request_view *view, request_sender *sender, history_repository *repo);
void delete_edit_request_presenter(edit_request_presenter *presenter);
void edit_request_presenter_set_edit_body_view(edit_request_presenter *presenter, edit_body_view *view);
void edit_request_presenter_set_response_body_view(edit_request_presenter *presenter, response_body_view *view);
void edit_request_presenter_set_edit_history_view(edit_request_presenter *presenter, edit_history_view *view);
void edit_request_presenter_on_send_request_clicked(edit_request_presenter *presenter);
void edit_request_presenter_on_clear_clicked(edit_request_presenter *presenter);

/* edit_body_presenter functions */
edit_body_presenter *new_edit_body_presenter(edit_body_view *view);
void delete_edit_body_presenter(edit_body_presenter *presenter);
void edit_body_presenter_on_clear_clicked(edit_body_presenter *presenter);

/* response_body_presenter functions */
response_body_presenter *new_response_body_presenter(response_body_view *view);
void delete_response_body_presenter(response_body_presenter *presenter);
void response_body_presenter_on_clear_clicked(response_body_presenter *presenter);

/* edit_history_presenter */
edit_history_presenter *new_edit_history_presenter(edit_history_view *view, history_repository *repo);
void delete_edit_history_presenter(edit_history_presenter *presenter);
void edit_history_presenter_on_item_clicked(edit_history_presenter *presenter);
void edit_history_presenter_on_remove_clicked(edit_history_presenter *presenter);
void edit_history_presenter_set_edit_request_view(edit_history_presenter *presenter, edit_request_view *view);
void edit_history_presenter_set_edit_body_view(edit_history_presenter *presenter, edit_body_view *view);
void edit_history_presenter_set_response_body_view(edit_history_presenter *presenter, response_body_view *view);

#ifdef __cplusplus
}
#endif

#endif
