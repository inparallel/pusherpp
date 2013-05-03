/* 
 * File:   CPusher.h
 * Author: Mazen Abdulaziz <mazen.abdulaziz@gmail.com>
 *
 * Created on April 24, 2013, 1:56 PM
 */

#ifndef CPUSHER_H
#define	CPUSHER_H

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string.h>
#include <ctime>
#include <vector>
#include <unistd.h>

#include <openssl/x509.h>
#include <openssl/hmac.h>
#include <openssl/md5.h>
#include <openssl/evp.h>

#include "include/CHTTPClient.hpp"
#include "include/config.h"

#ifndef __GXX_EXPERIMENTAL_CXX0X__
#define __GXX_EXPERIMENTAL_CXX0X__
#endif

namespace Pusherpp
{
	/**
	 * \brief A small Pusher.com server library
	 */
	class CPusher
	{
	private:
		std::string m_AppId;  //!< API ID Obtained from Pusher
		std::string m_Key;    //!< Key obtained from Pusher
		std::string m_Secret; //!< Secret obtained from Pusher
		CHTTPClient m_Http;   //!< The HTTP client that will post the actual requests to the server
	
		/**
		 * \brief A utility function that will generate an HMAC-SHA256 of the provided message. 
		 * 
		 * Uses libopenssl implementation of HMAC-SHA256.
		 * 
		 * \param message The message to be HMACed
		 * \return The HMAC-SHA256 of the provided message
		 */
		std::string generateHmac(const std::string& message) const;
	
		/**
		 * \brief A utility function that will generate an MD5 of the provided message. 
		 * 
		 * Uses libopenssl implementation of MD5.
		 * 
		 * \param message The message to be MD5ed
		 * \return The MD5 of the provided message
		 */
		std::string Md5(const std::string& input) const;
	
	public:
	
		/**
		 * \brief Creates a Pusher server with the provided parameters (obtained from Pusher website)
		 * 
		 * \param appId Application ID obtained from Pusher.com
		 * \param key Key obtained from Pusher.com
		 * \param secret Secret obtained from Pusher.com
		 */
		CPusher(std::string appId, std::string key, std::string secret);
	
		~CPusher();
	
		/**
		 * \brief Posts the provided message to the specified channel and event in Pusher. BLOCKS until the response
		 * is recieved from Pusher.
		 * 
		 * Note that the message is sent as-is, so make sure it's a valid JSON object.
		 * 
		 * \param channel Channel name of the user
		 * \param event The event in user's channel
		 * \param jsonMsg The message to be sent (must be in a valid JSON format)
		 */
		void sendMessage(const std::string& channel, const std::string& event, const std::string& jsonMsg) const;
	};
}
#endif	/* CPUSHER_H */

