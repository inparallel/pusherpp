#include <iomanip>
#include <string>
#include <sstream>

#include <openssl/x509.h>
#include <openssl/hmac.h>
#include <openssl/md5.h>
#include <openssl/evp.h>

namespace Pusherpp
{

	/**
	 * \brief A set of useful swiss-knife utility functions
	 */
	class CUtilities
	{
		public:
			
		/**
		 * \brief A utility function that will generate an HMAC-SHA256 of the provided message. 
		 * 
		 * Uses libcrypto implementation of HMAC-SHA256.
		 * 
		 * \param message The message to be HMACed
		 * \param secret The secret key through which the HMAC is generated
		 * \return The HMAC-SHA256 of the provided message
		 */
		static std::string generateHmac(const std::string& message, const std::string& secret);
	
		/**
		 * \brief A utility function that will generate an MD5 of the provided message. 
		 * 
		 * Uses libcrypto implementation of MD5.
		 * 
		 * \param message The message to be MD5ed
		 * \return The MD5 of the provided message
		 */
		static std::string Md5(const std::string& input);
		
		/**
		 * \brief Escapes the provided string. BETA VERSION. Please report errors to the developers, if any.
		 * 
       * \param str The string to be escaped
       * \return The escaped string
       */
		static std::string escapeString(const std::string& str);
	};
}