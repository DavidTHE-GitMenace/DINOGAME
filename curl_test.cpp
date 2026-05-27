#include <curl/curl.h>
#include <iostream>
#include <string>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

int main() {
    curl_global_init(CURL_GLOBAL_DEFAULT);

    CURL* curl = curl_easy_init();

    if (!curl) {
        std::cerr << "Failed to initialize libcurl\n";
        curl_global_cleanup();
        return 1;
    }

    std::string response;

    curl_easy_setopt(curl, CURLOPT_URL, "https://dino-api-986544070781.us-central1.run.app/health");
    curl_easy_setopt(curl, CURLOPT_CAINFO, "ca-bundle.crt");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode result = curl_easy_perform(curl);

    if (result != CURLE_OK) {
        std::cerr << "Request failed: " << curl_easy_strerror(result) << "\n";
    } else {
        std::cout << "Response: " << response << "\n";
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}