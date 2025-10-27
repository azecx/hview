#pragma once
#include <string>

class HttpClient {
public:
	HttpClient();
	~HttpClient();

	std::string get(const std::string& url);

	//todo: fetch raw binary data for images.
private:
	void initCurl();
	void cleanupCurl();

	void* curlHandle;
};