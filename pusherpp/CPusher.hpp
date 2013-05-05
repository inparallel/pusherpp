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

#include "include/CHTTPClient.hpp"
#include "include/CUtilities.hpp"
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
	
	public:
	
		/**
		 * \brief Creates a Pusher server with the provided parameters (obtained from Pusher website)
		 * 
		 * \param appId Application ID obtained from Pusher.com
		 * \param key Key obtained from Pusher.com
		 * \param secret Secret obtained from Pusher.com
		 */
		CPusher(const std::string& appId, const std::string& key, const std::string& secret);
	
		~CPusher();
	
		/**
		 * \brief Posts the provided message to the specified channel and event in Pusher. BLOCKS until the response
		 * is received from Pusher.
		 * 
		 * Note that the message is sent as-is, so make sure it's a valid JSON object.
		 * 
		 * \param channel Channel name of the user
		 * \param event The event in user's channel
		 * \param msg The message to be sent. JSON format is welcome.
		 * 
		 * \return Reply from server
		 */
		std::string sendMessage(const std::string& channel, const std::string& event, const std::string& msg) const;
	
		/**
		 * \brief Posts the provided message to the specified set of channels and event in Pusher. BLOCKS until the response
		 * is received from Pusher.
		 * 
		 * Note that the message is sent as-is, so make sure it's a valid JSON object.
		 * 
		 * \param channels Set of channels to which the message shall be posted
		 * \param event The event in user's channel
		 * \param msg The message to be sent. JSON format is welcome.
		 * 
		 * \return Reply from server
		 */
		std::string sendMessage(const std::vector<std::string>& channels, const std::string& event, const std::string& msg) const;
	};
}
#endif	/* CPUSHER_H */

