#ifndef HISTORY_REPOSITORY_HPP
#define HISTORY_REPOSITORY_HPP

#include <map>
#include <list>
#include <string>
#include <sqlite3.h>

#include "http_method.hpp"

class history_repository
{
public:
    struct entry
    {
        int id = 0;
        std::string url;
        http_method method = http_method::GET_HTTP_METHOD;
        std::string body;
        std::string response;
    };

public:
    explicit history_repository(const std::string &filename);
    ~history_repository();

    int add_entry(const entry &e);
    entry get_entry(int id) const;
    const std::list<entry> &get_entry_list() const;
    bool has_entry(int id) const;
    void remove_entry(int id);

private:
    int create_table();
    int fetch_table();

private:
    std::list<entry> _entry_list;
    sqlite3 *_db;
    std::map<http_method, std::string> _http_method_to_name_map;
    std::map<std::string, http_method> _name_to_http_method_map;
};

#endif // HISTORY_REPOSITORY_HPP
