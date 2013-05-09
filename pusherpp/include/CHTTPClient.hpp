#ifndef CHTTPCLIENT_H
#define	CHTTPCLIENT_H

#include <curl/curl.h>
#include <thread>
#include <string>

namespace Pusherpp
{
	/**
	 * \brief A HTTP client utility class that sends POST requests.
	 * 
	 * Each call to sendRequest() is wrapped inside a thread that executes the actual request
	 * using libcurl.
	 */
	class CHTTPClient
	{

		
		/**
		 * \brief The callback function of curl_easy_perform(). In our case, we're ignoring anything coming from
		 * the HTTP server (yes, bad design)
		 * 
       * \param ptr pointer to actual data
       * \param size size defined in memory blocks
       * \param nmemb size of a memory block of data
       * \param stream where data shall be stored in user land. In this implementation, stream should be of type
		 * std::stringstream
       * \return 
       */
		static size_t curlWrite(void *ptr, size_t size, size_t nmemb, void *stream);
	
	public:
		CHTTPClient();
	
		~CHTTPClient();
	
		/**
		 * \brief Wraps the provided message in an HTTP POST request and ships it to the provided url, and BLOCKS 
		 * until the response is received.
		 * \param url The URL to which the message will be POSTed
		 * \param message The message to be sent. JSON format is welcome.
		 * \param httpCode A buffer to store the HTTP error code returned
		 * 
		 * \return Reply from server
		 */
		std::string postRequest(const std::string& url, const std::string& message, long& httpCode) const;
	
		/**
		 * \brief Wraps the provided message in an HTTP get request and ships it to the provided url, and BLOCKS 
		 * until the response is received.
		 * \param url The URL to which the message will be GETed
		 * \param httpCode A buffer to store the HTTP error code returned
		 * 
		 * \return Reply from server
		 */
		std::string getRequest(const std::string& url, long& httpCode) const;
	};
}

#endif /* CHTTPCLIENT_H */
