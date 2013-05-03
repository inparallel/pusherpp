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
		struct curl_slist* m_Headers; //!< A shared HTTP header construct
	
		/**
		 * \brief The callback function of curl_easy_perform(). In our case, we're ignoring anything coming from
		 * the HTTP server (yes, bad design)
		 */
		static size_t curlWrite(void *ptr, size_t size, size_t nmemb, void *userdata);
	
		/**
		 * \brief The actual work performed by each sending thread.
		 * \param url The URL to which the message will be POSTed
		 * \param message The message to be sent
		 */
		void threadWork(std::string url, std::string message) const;
	
	public:
		CHTTPClient();
	
		~CHTTPClient();
	
		/**
		 * \brief Wraps the provided message in an HTTP POST request and ships it to the provided url. No guarantees.
		 * \param url The URL to which the message will be POSTed
		 * \param message The message to be sent
		 */
		void sendRequest(const std::string& url, const std::string& message) const;
	};
}


