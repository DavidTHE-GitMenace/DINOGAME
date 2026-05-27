#include "ApiClient.hpp"

#include <curl/curl.h>
#include <iostream>

static const std::string BASE_URL = "https://dino-api-986544070781.us-central1.run.app";

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

ApiResponse postJsonToApi(const std::string& endpoint, const std::string& jsonBody) {
    ApiResponse response;
    response.statusCode = 0;

    CURL* curl = curl_easy_init();

    if (!curl) {
        response.body = "Failed to initialize libcurl";
        return response;
    }

    std::string fullUrl = BASE_URL + endpoint;

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, fullUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonBody.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_CAINFO, "ca-bundle.crt");

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response.body);

    CURLcode result = curl_easy_perform(curl);

    if (result != CURLE_OK) {
        response.body = curl_easy_strerror(result);
    } else {
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response.statusCode);
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    return response;
}

ApiResponse getFromApi(const std::string& endpoint) {
    ApiResponse response;
    response.statusCode = 0;

    CURL* curl = curl_easy_init();

    if (!curl) {
        response.body = "Failed to initialize libcurl";
        return response;
    }

    std::string fullUrl = BASE_URL + endpoint;

    curl_easy_setopt(curl, CURLOPT_URL, fullUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_CAINFO, "ca-bundle.crt");

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response.body);

    CURLcode result = curl_easy_perform(curl);

    if (result != CURLE_OK) {
        response.body = curl_easy_strerror(result);
    } else {
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response.statusCode);
    }

    curl_easy_cleanup(curl);

    return response;
}