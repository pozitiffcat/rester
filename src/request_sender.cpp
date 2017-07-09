#include "request_sender.hpp"

#include <math.h>
#include <thread>
#include <memory>
#include <vector>
#include <unistd.h>
#include <string.h>
#include <curl/curl.h>

#include "ui_handler.hpp"

size_t curl_write_data(const char *src, size_t size, size_t nmemb, std::vector<char> *dest)
{
    size_t sz = size * nmemb;
    dest->insert(dest->end(), src, src + sz);
    return sz;
}

size_t curl_read_data(char *dst, size_t size, size_t nmemb, std::vector<char> *src)
{
    size_t sz = std::min(size * nmemb, src->size());
    memcpy(dst, src->data(), sz);
    src->erase(src->begin(), src->begin() + sz);
    return sz;
}

request_sender::request_sender(ui_handler *handler)
    : _ui_handler(handler)
{
    _http_method_name_map[http_method::GET_HTTP_METHOD] = "GET";
    _http_method_name_map[http_method::POST_HTTP_METHOD] = "POST";
    _http_method_name_map[http_method::PUT_HTTP_METHOD] = "PUT";
    _http_method_name_map[http_method::DELETE_HTTP_METHOD] = "DELETE";
}

void request_sender::send_request(const std::string &url, http_method method, const std::string &body, handler_func handler)
{
    std::thread thread([this, url, method, body, handler] {
        curl_global_init(CURL_GLOBAL_ALL);
        CURL *curl = curl_easy_init();

        std::vector<char> responseData;
        std::vector<char> bodyData(body.begin(), body.end());

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, _http_method_name_map[method].c_str());

        const bool is_request_with_body =
                method == http_method::POST_HTTP_METHOD ||
                method == http_method::PUT_HTTP_METHOD;

        if (is_request_with_body)
        {
            struct curl_slist *headers = NULL;
            headers = curl_slist_append(headers, "Content-Type: application/json");
            headers = curl_slist_append(headers, "charsets: utf-8");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

            curl_easy_setopt(curl, CURLOPT_READFUNCTION, curl_read_data);
            curl_easy_setopt(curl, CURLOPT_READDATA, &bodyData);
            curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        }

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        curl_global_cleanup();

        responseData.push_back(0);

        _ui_handler->run_on_ui([responseData, handler] {
            handler(200, responseData.data());
        });
    });

    thread.detach();
}
