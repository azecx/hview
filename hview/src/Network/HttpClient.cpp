#include "HttpClient.h"
#include <curl/curl.h>
#include <stdexcept>

static size_t writeToString(void* ptr, size_t size, size_t nmemb, std::string* data) {
	data->append((char*)ptr, size * nmemb);
	return size * nmemb;
}

HttpClient::HttpClient() {
	curl_global_init(CURL_GLOBAL_DEFAULT);
	curlHandle = curl_easy_init();
}

HttpClient::~HttpClient() {
	if (curlHandle) curl_easy_cleanup(curlHandle);
	curl_global_cleanup();
}

std::string HttpClient::get(const std::string& url) {
	if (!curlHandle) throw std::runtime_error("CURL not initialized!");

	std::string response;
	CURL* curl = (CURL*)curlHandle;

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeToString);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

	CURLcode res = curl_easy_perform(curl);
	if (res != CURLE_OK) {
		throw std::runtime_error(curl_easy_strerror(res));
	}
	return response;
}