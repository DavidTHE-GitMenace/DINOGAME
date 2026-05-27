#ifndef API_CLIENT_HPP
#define API_CLIENT_HPP

#include <string>

struct ApiResponse {
    long statusCode;
    std::string body;
};

ApiResponse postJsonToApi(const std::string& endpoint, const std::string& jsonBody);
ApiResponse getFromApi(const std::string& endpoint);

#endif