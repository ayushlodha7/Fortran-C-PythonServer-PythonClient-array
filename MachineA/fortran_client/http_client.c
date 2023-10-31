#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

int send_http_request() {
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(!curl) {
        fprintf(stderr, "Failed to initialize curl for HTTP request\n");
        return -1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, "http://149.159.235.155:8080/receive_message");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "message=Hello, Python");

    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if(res != CURLE_OK) {
        fprintf(stderr, "Failed to send HTTP request: %s\n", curl_easy_strerror(res));
        return -1;
    }

    return 0;
}

int send_float_array(float arr[], int n) {
    CURL *curl;
    CURLcode res;
    struct curl_slist *headers = NULL;

    curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Failed to initialize curl for float array\n");
        return -1;
    }

    headers = curl_slist_append(headers, "Content-Type: application/octet-stream");

    curl_easy_setopt(curl, CURLOPT_URL, "http://149.159.235.155:8080/receive_float_array");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, arr);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, sizeof(float) * n);

    res = curl_easy_perform(curl);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        fprintf(stderr, "Failed to send float array: %s\n", curl_easy_strerror(res));
        return -1;
    }

    return 0;
}
