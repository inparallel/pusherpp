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
#include <map>
#include <unistd.h>
#include <functional>

#include "include/CHTTPClient.hpp"
#include "include/CUtilities.hpp"
#include "include/config.h"
#include "CPusherReply.hpp"

namespace Pusherpp
{

	/**
	 * \brief A small Pusher.com server library
	 */
	class CPusher
	{
	private:
		std::string m_AppId; //!< API ID Obtained from Pusher
		std::string m_Key; //!< Key obtained from Pusher
		std::string m_Secret; //!< Secret obtained from Pusher
		bool m_UseSecure; //!< Whether to use HTTP or HTTPS to talk to Pusher
		CHTTPClient m_Http; //!< The HTTP client that will post the actual requests to the server
		std::function<void(const std::string&)> m_Log; //!< A reference to the logging function 
		
		/**
		 * \brief A helper function to convert the HTTP status code returned by Pusher to an internal representation
		 * \param httpCode The HTTP status code returned from Pusher
		 * \return The corresponding \sa CPusherReply::ErrorCode
		 */
		inline CPusherReply::ErrorCode interpretCode(const long& httpCode) const
		{
			switch (httpCode)
			{
				case 200:
					return CPusherReply::PSH_SUCCESS;
					break;

				case 400:
					return CPusherReply::PSH_GENERIC_ERROR;
					break;

				case 401:
					return CPusherReply::PSH_AUTH_ERROR;
					break;

				case 403:
					return CPusherReply::PSH_FORBIDDEN;
					break;

				case 413:
					return CPusherReply::PSH_OVERFLOW;
					break;

				default:
					return CPusherReply::PSH_UNKNOWN;
			}
		}

		/**
		 * \brief Generates a pusher URL for GET requests based on the parameters passed.
		 * 
		 * \param path Path in pusher servers (e.g. /channels)
		 * \param params The query parameters as a key/value map. Note that this parameter will be modified here.
		 * \return The generated URL
		 */
		inline std::string generateGetUrl(const std::string& path, std::map<std::string, std::string>& params)
		{
			static std::string authVersion = "1.0";
			static std::string baseUrl = "http://api.pusherapp.com/apps/";
			static std::string baseSUrl = "https://api.pusherapp.com/apps/";

			std::stringstream queryss;
			std::stringstream authss;
			std::stringstream urlss;
			std::string authSignature;

			params["auth_key"] = m_Key;
			params["auth_timestamp"] = std::to_string((long long) time(0));
			params["auth_version"] = authVersion;

			for (auto it = params.begin(); it != params.end(); ++it)
			{
				queryss << it->first << "=" << it->second;

				if (std::distance(it, params.end()) != 1)
					queryss << "&";
			}

			authss << "GET" << "\n/apps/" << m_AppId
					  << path << "\n" << queryss.str();

			authSignature = CUtilities::generateHmac(authss.str(), m_Secret);

			urlss << (m_UseSecure ? baseSUrl : baseUrl) << m_AppId << path << "?" <<
					  queryss.str() <<
					  "&auth_signature=" << authSignature;

			return urlss.str();
		}

		/**
		 * \brief Generates a pusher URL for POST requests based on the parameters passed.
		 * 
		 * \param path Path in pusher servers (e.g. /events)
		 * \param postData the data to be posted
		 * \return The generated URL
		 */
		inline std::string generatePostUrl(const std::string& path, const std::string& postData) const
		{
			static std::string authVersion = "1.0";
			static std::string baseUrl = "http://api.pusherapp.com/apps/";
			static std::string baseSUrl = "https://api.pusherapp.com/apps/";

			long int authTimestamp = time(0);
			std::stringstream queryss;
			std::stringstream authss;
			std::stringstream urlss;
			std::string bodyMd5;
			std::string authSignature;

			// Compute the message's MD5
			bodyMd5 = CUtilities::Md5(postData);

			queryss << "auth_key=" << m_Key << "&auth_timestamp=" <<
					  authTimestamp << "&auth_version=" << authVersion << "&body_md5=" << bodyMd5;

			// Create the text to be HMACed
			authss << "POST\n/apps/" << m_AppId << path << "\n" << queryss.str();

			authSignature = CUtilities::generateHmac(authss.str(), m_Secret);

			urlss << (m_UseSecure ? baseSUrl : baseUrl) << m_AppId << "/events?" <<
					  queryss.str() << "&auth_signature=" << authSignature;

			return urlss.str();
		}

	public:

		enum EChannelInfo
		{
			CH_INFO_NONE = 0,          //!< No additional info required
			CH_INFO_USERCOUNT = 0x01,  //!< Get a list of occupied channels, alongside user count for each channel. Can only be used for presence channels.
			CH_INFO_SUBS_COUNT = 0x02, //!< Get subscription count for one channel. Can only be used with getChannelInfo()
		};

		/**
		 * \brief Creates a Pusher server with the provided parameters (obtained from Pusher website)
		 * 
		 * \param appId Application ID obtained from Pusher.com
		 * \param key Key obtained from Pusher.com
		 * \param secret Secret obtained from Pusher.com
		 * \param useSecure Set to true to use HTTPS. false by default
		 */
		CPusher(const std::string& appId, const std::string& key, const std::string& secret, bool useSecure = false);

		~CPusher();

		/**
		 * \brief Posts the provided message to the specified channel and event in Pusher. BLOCKS until the response
		 * is received from Pusher.
		 * 
		 * Note that the message is sent as-is, so make sure it's a valid JSON object.
		 * 
		 * \deprecated This method is deprecated, it will be removed in future releases. Please use \sa CPusher::trigger() instead.
		 * 
		 * \param channel Channel name of the user
		 * \param event The event in user's channel
		 * \param msg The message to be sent. JSON format is welcome.
		 * 
		 * \return Response from pusher
		 */
		const CPusherReply sendMessage(const std::string& channel, const std::string& event, const std::string& msg) const;

		/**
		 * \brief Posts the provided message to the specified set of channels and event in Pusher. BLOCKS until the response
		 * is received from Pusher.
		 * 
		 * Note that the message is sent as-is, so make sure it's a valid JSON object.
		 * 
		 * \deprecated This method is deprecated, it will be removed in future releases. Please use \sa CPusher::trigger() instead.
		 * 
		 * \param channels Set of channels to which the message shall be posted
		 * \param event The event in user's channel
		 * \param msg The message to be sent. JSON format is welcome.
		 * 
		 * \return Response from pusher
		 */
		const CPusherReply sendMessage(const std::vector<std::string>& channels, const std::string& event, const std::string& msg) const;

		/**
		 * \brief Posts the provided message to the specified channel and event in Pusher. BLOCKS until the response
		 * is received from Pusher.
		 * 
		 * Note that the message is sent as-is, so make sure it's a valid JSON object.
		 * 
		 * \deprecated This method is deprecated, it will be removed in future releases. Please use \sa CPusher::trigger() instead.
		 * 
		 * \param channel Channel name of the user
		 * \param event The event in user's channel
		 * \param msg The message to be sent. JSON format is welcome.
		 * \param socketId The socket-id to be excluded from receiving the message
		 * 
		 * \return Response from pusher
		 */
		const CPusherReply trigger(const std::string& channel, const std::string& event, const std::string& msg, 
			const std::string& socketId = "") const;

		/**
		 * \brief Posts the provided message to the specified set of channels and event in Pusher. BLOCKS until the response
		 * is received from Pusher.
		 * 
		 * Note that the message is sent as-is, so make sure it's a valid JSON object.
		 * 
		 * \param channels Set of channels to which the message shall be posted
		 * \param event The event in user's channel
		 * \param msg The message to be sent. JSON format is welcome.
		 * \param socketId The socket-id to be excluded from receiving the message
		 * 
		 * \return Response from pusher
		 */
		const CPusherReply trigger(const std::vector<std::string>& channels, const std::string& event, const std::string& msg, 
			const std::string& socketId = "") const;

		/**
		 * \brief Returns info about one channel
		 * \param channel The channel to be queried
		 * \param addInfo A list of additional info required
		 * \return Response from pusher
		 */
		const CPusherReply getChannelInfo(const std::string& channel, long addInfo = CPusher::EChannelInfo::CH_INFO_NONE);

		/**
		 * \brief Fetch info for multiple channels
		 * 
		 * \param filterByPrefix Channels prefixes, default is none.
		 * \param addInfo What info to be queried. Default is "occupied channels" (EChannelInfo::CH_INFO_OCCUPIED). You can
		 * also query about "user count" ONLY if prefix = "presence-". Note that you cannot query about "subscription 
		 * count" when getting info for multiple channels.
		 * \return 
		 */
		const CPusherReply getChannels(const std::string& filterByPrefix = "", EChannelInfo addInfo = EChannelInfo::CH_INFO_NONE);
		
		/**
		 * \brief Sets the logging function to the passed one. Use std::bind for infinite flexibility.
       * \param logFunc The function intended to log events. It should have the signature void(const std::string&)
       */
		void setLogFunction(const std::function<void(const std::string&)>& logFunc);
	};
}
#endif	/* CPUSHER_H */

