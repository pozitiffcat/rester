#include "history_repository.hpp"

#include <algorithm>

history_repository::history_repository(const std::string &filename)
{
    _http_method_to_name_map[http_method::GET_HTTP_METHOD] = "GET";
    _http_method_to_name_map[http_method::POST_HTTP_METHOD] = "POST";
    _http_method_to_name_map[http_method::PUT_HTTP_METHOD] = "PUT";
    _http_method_to_name_map[http_method::DELETE_HTTP_METHOD] = "DELETE";

    _name_to_http_method_map["GET"] = http_method::GET_HTTP_METHOD;
    _name_to_http_method_map["POST"] = http_method::POST_HTTP_METHOD;
    _name_to_http_method_map["PUT"] = http_method::PUT_HTTP_METHOD;
    _name_to_http_method_map["DELETE"] = http_method::DELETE_HTTP_METHOD;

    int rc = sqlite3_open(filename.c_str(), &_db);
    // todo: check rc

    rc = create_table();
    // todo: check rc

    rc = fetch_table();
    // todo: check rc
}

history_repository::~history_repository()
{
    sqlite3_close(_db);
}

int history_repository::add_entry(const entry &e)
{
    int rc = SQLITE_OK;
    sqlite3_stmt *stmt = NULL;

    const std::string insert_sql
    (
        "insert into history(url, method, body, response)   "
        "             values(?, ?, ?, ?);                   "
    );

    rc = sqlite3_prepare(_db, insert_sql.c_str(), -1, &stmt, NULL);
    // todo: check rc

    rc = sqlite3_bind_text(stmt, 1, e.url.c_str(), -1, SQLITE_STATIC);
    // todo: check rc

    rc = sqlite3_bind_text(stmt, 2, _http_method_to_name_map[e.method].c_str(), -1, SQLITE_STATIC);
    // todo: check rc

    rc = sqlite3_bind_text(stmt, 3, e.body.c_str(), -1, SQLITE_STATIC);
    // todo: check rc

    rc = sqlite3_bind_text(stmt, 4, e.response.c_str(), -1, SQLITE_STATIC);
    // todo: check rc

    rc = sqlite3_step(stmt);
    // todo: check rc

    sqlite3_finalize(stmt);

    const int id = sqlite3_last_insert_rowid(_db);
    entry entry_to_add = e;
    entry_to_add.id = id;

    _entry_list.push_back(entry_to_add);

    return id;
}

history_repository::entry history_repository::get_entry(int id) const
{
    auto foundIt = std::find_if(_entry_list.begin(), _entry_list.end(), [id] (auto &e) { return e.id == id; });

    // todo: if not fount then exception

    return *foundIt;
}

const std::list<history_repository::entry> &history_repository::get_entry_list() const
{
    return _entry_list;
}

bool history_repository::has_entry(int id) const
{
    return std::find_if(_entry_list.begin(), _entry_list.end(), [id] (auto &e) { return e.id == id; }) != _entry_list.end();
}

void history_repository::remove_entry(int id)
{
    int rc = SQLITE_OK;
    sqlite3_stmt *stmt = NULL;

    std::string select_sql
    (
        "delete from history where id = ?;"
    );

    rc = sqlite3_prepare(_db, select_sql.c_str(), -1, &stmt, NULL);
    // todo: check rc

    rc = sqlite3_bind_int(stmt, 1, id);
    // todo: check rc

    rc = sqlite3_step(stmt);
    // todo: check rc

    sqlite3_finalize(stmt);

    auto foundIt = std::find_if(_entry_list.begin(), _entry_list.end(), [id] (auto &e) { return e.id == id; });
    _entry_list.erase(foundIt);
}

int history_repository::create_table()
{
    const std::string create_table_sql
    (
        "create table if not exists history         "
        "(                                          "
        "   id integer primary key autoincrement,   "
        "   url text,                               "
        "   method text,                            "
        "   body text,                              "
        "   response text                           "
        ");"
    );

    return sqlite3_exec(_db, create_table_sql.c_str(), NULL, NULL, NULL);
}

int history_repository::fetch_table()
{
    int rc = SQLITE_OK;
    sqlite3_stmt *stmt = NULL;

    std::string select_sql
    (
        "select id, url, method, body, response "
        "  from history;                        "
    );

    rc = sqlite3_prepare(_db, select_sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK)
        return rc;

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        entry e;

        e.id = sqlite3_column_int(stmt, 0);
        e.url = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        e.body = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        e.response = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
        std::string method_name(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));

        auto method_it = _name_to_http_method_map.find(method_name);
        if (method_it != _name_to_http_method_map.end())
            e.method = method_it->second;

        _entry_list.push_back(e);
    }

    sqlite3_finalize(stmt);

    if (rc != SQLITE_DONE)
    {
        return rc;
    }

    return SQLITE_OK;
}
