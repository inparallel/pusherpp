#include "CHTTPClient.hpp"
#include <string>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <assert.h>
#include <sstream> 

namespace Pusherpp
{
	size_t CHTTPClient::curlWrite(void *ptr, size_t size, size_t nmemb, void *stream)
	{
		// Nothing special here...
		
		std::stringstream* sstream = (std::stringstream*)(stream);
		std::string value((char*) ptr, size * nmemb);

		*sstream << value;
		
		return nmemb * size;
	}

	CHTTPClient::CHTTPClient()
	{
		
	}

	CHTTPClient::~CHTTPClient()
	{
		
	}

	std::string CHTTPClient::sendRequest(const std::string& url, const std::string& message) const
	{
		struct curl_slist* headers = NULL;
		std::stringstream  replyss;
		char*              buff;
		CURL*              curl;
		CURLcode           res;
		long               httpCode = 0;
		
		// Mazen: for some unknown reason, sending message.c_str() in the post body to Pusher doesn't work..
		// while sending a copied array does!
		buff = (char*) malloc(message.length() + 1);
		memcpy(buff, message.c_str(), message.length());
		buff[message.length()] = '\0';
	
		curl = curl_easy_init();
		
		headers = curl_slist_append(headers, "Content-Type: application/json");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_POST, 1);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &CHTTPClient::curlWrite);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&replyss);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // keep AS-IS
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, buff);
		res = curl_easy_perform(curl);
		
		if(res == CURLcode::CURLE_OK)
		{
			curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &httpCode);
		}
		else
		{
			// TODO: prepare proper error message/code6+
		}
		
		free(buff);
		curl_slist_free_all(headers);
		curl_easy_cleanup(curl);
		
		return replyss.str();
	}
}
