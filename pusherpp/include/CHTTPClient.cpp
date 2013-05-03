#include "CHTTPClient.hpp"
#include <string>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

namespace Pusherpp
{
	size_t CHTTPClient::curlWrite(void *ptr, size_t size, size_t nmemb, void *userdata)
	{
		// Ignore server's reply...
	
		return nmemb * size;
	}

	void CHTTPClient::threadWork(std::string url, std::string message) const
	{
		// Mazen: for some unknown reason, sending message.c_str() in the post body to Pusher doesn't work..
		// while sending a copied array does!

		char* buff = (char*) malloc(message.length() + 1);
		memcpy(buff, message.c_str(), message.length());
		buff[message.length()] = '\0';
	
		CURL* curl = curl_easy_init();
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, m_Headers);
		curl_easy_setopt(curl, CURLOPT_POST, 1);
		//curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &CHTTPClient::curlWrite);
	
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // keep AS-IS
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, buff);
		std::cout << url << "\n" << message << std::endl;
		CURLcode res = curl_easy_perform(curl);
	
		free(buff);
		curl_easy_cleanup(curl);
	}

	CHTTPClient::CHTTPClient()
	{
		m_Headers = NULL;
		m_Headers = curl_slist_append(m_Headers, "Content-Type: application/json");
	}

	CHTTPClient::~CHTTPClient()
	{
		curl_slist_free_all(m_Headers);
	}

	void CHTTPClient::sendRequest(const std::string& url, const std::string& message) const
	{
		std::thread t(&CHTTPClient::threadWork, this, url, message);
		t.detach(); // Go play alone, thread. Bad design for heavy request commands
	}
}
