#include "CPusher.hpp"
#include "CPusherReply.hpp"
#include <assert.h>
#include <cstddef>
#include <functional>

namespace Pusherpp
{

	CPusher::CPusher(const std::string& appId, const std::string& key, const std::string& secret, bool useSecure) :
	m_AppId(appId), m_Key(key), m_Secret(secret), m_UseSecure(useSecure)
	{
		// A note for future me:
		// Typically, I'd call m_Log = nullptr, but since this might not be supported
		// in GCC < 4.7.1; this is currently not an option.
	}

	CPusher::~CPusher()
	{
		
	}

	const CPusherReply CPusher::sendMessage(const std::string& channel, const std::string& event, const std::string& msg) const
	{
		if(m_Log != NULL) // C++11-ish: m_Log != nullptr
		{
			std::stringstream log;
			log << "pusherpp: " << __func__ << ": " << "WARNING: YOU ARE CALLING A DEPRECATED FUNCTION"
					  ", USE trigger() INSTEAD.";
			
			m_Log(log.str());
		}
		
		return trigger(channel, event, msg);
	}

	const CPusherReply CPusher::sendMessage(const std::vector<std::string>& channels, const std::string& event, const std::string& msg) const
	{
		if(m_Log != NULL)
		{
			std::stringstream log;
			log << "pusherpp: " << __func__ << ": " << "WARNING: YOU ARE CALLING A DEPRECATED FUNCTION"
					  ", USE trigger() INSTEAD.";
			
			m_Log(log.str());
		}
		
		return trigger(channels, event, msg);
	}

	const CPusherReply CPusher::trigger(const std::string& channel, const std::string& event, const std::string& msg,
			  const std::string& socketId) const
	{
		std::vector<std::string> lCh;
		lCh.push_back(channel);

		return trigger(lCh, event, msg, socketId);
	}

	const CPusherReply CPusher::trigger(const std::vector<std::string>& channels, const std::string& event, const std::string& msg,
			  const std::string& socketId) const
	{
		if(m_Log != NULL)
		{
			std::stringstream log;
			log << "pusherpp: " << __func__ << ": " << "triggering an event named \"" <<  event << "\" on channel(s) [";
			
			for(auto it = channels.begin(); it != channels.end(); it++) // dropped foreach in favor of GCC 4.4 support
			{
				log << *it << (std::distance(it, channels.end()) != 1 ? ", " : "");
			}
			log << "]. The payload is: \"" << msg << "\". ";
			
			if(socketId.size() != 0)
				log << "Excluding socketId: " << socketId;
			
			m_Log(log.str());
		}
		
		long httpCode;
		CPusherReply ret;
		std::stringstream postss;
		std::string url;

		postss << "{\"name\":\"" << event << "\",\"data\":\"" << CUtilities::escapeString(msg) << "\",\"channels\":[";
		for (auto it = channels.begin(); it != channels.end(); it++)
		{
			postss << "\"" << *it << "\"" << (std::distance(it, channels.end()) > 1 ? "," : "");
		}
		postss << "], \"socket_id\":\""<< socketId << "\"}";

		url = this->generatePostUrl("/events", postss.str());
		ret.message = m_Http.postRequest(url, postss.str(), httpCode);
		ret.error = this->interpretCode(httpCode);


		return ret;
	}

	const CPusherReply CPusher::getChannelInfo(const std::string& channel, long vAddInfo)
	{
		if(m_Log != NULL)
		{
			std::stringstream log;
			log << "pusherpp: " << __func__ << ": " << "getting channel [" << channel << "] info...";
			
			m_Log(log.str());
		}
		
		long httpCode;
		CPusherReply ret;

		std::map<std::string, std::string> params;
		std::stringstream buff;
		std::stringstream chss;
		std::string url;
		bool addComma = false;

		// too lazy to think of a smarter solution..
		buff << "[";
		if ((vAddInfo & CPusher::EChannelInfo::CH_INFO_SUBS_COUNT) != 0)
		{
			buff << "subscription_count";
			addComma = true;
		}

		if ((vAddInfo & CPusher::EChannelInfo::CH_INFO_USERCOUNT) != 0)
		{
			buff << (addComma ? "," : "") << "user_count";
		}
		buff << "]";

		params["info"] = buff.str();

		chss << "/channels/" << channel;
		url = CPusher::generateGetUrl(chss.str(), params);

		ret.message = m_Http.getRequest(url, httpCode);
		ret.error = this->interpretCode(httpCode);

		return ret;
	}

	const CPusherReply CPusher::getChannels(const std::string& filterByPrefix, CPusher::EChannelInfo info)
	{
		if(m_Log != NULL)
		{
			std::stringstream log;
			log << "pusherpp: " << __func__ << ": " << "getting all channels info";
			
			if(filterByPrefix.size() != 0)
				log << ", filtered by prefix: \"" << filterByPrefix << "\"";
			log << "...";
			
			m_Log(log.str());
		}
		
		long httpCode;
		CPusherReply ret;
		
		std::map<std::string, std::string> params;
		params["filter_by_prefix"] = filterByPrefix;
		params["info"] = (info == CPusher::CH_INFO_USERCOUNT ? "user_count" : "");

		std::string url = CPusher::generateGetUrl("/channels", params);

		ret.message = m_Http.getRequest(url, httpCode);
		ret.error = this->interpretCode(httpCode);

		return ret;
	}
	
	void CPusher::setLogFunction(const std::function<void(const std::string&)>& logFunc)
	{
		m_Log = logFunc;
		
		if(m_Log != NULL)
		{
			std::stringstream log;
			log << "pusherpp: " << __func__ << ": " << "logging is all set.";
			
			m_Log(log.str());
		}
	}
	
	std::string CPusher::authPrivateChannel(const std::string& channelName, const std::string& socketId)
	{
		std::stringstream authss;
		std::stringstream json;
		std::string hmac;
		
		authss << socketId << ":" << channelName;
		hmac = CUtilities::generateHmac(authss.str(), m_Secret);
		
		// Construct 'em JSON
		json << "{\"auth\":\"" << hmac << "\"}";
		
		if(m_Log != NULL)
		{
			std::stringstream log;
			log << "pusherpp: " << __func__ << ": " << "authenticating socket \"" << socketId <<
					  "\" to use private channel \"" << channelName << "\"... The generated auth message is " <<
					  json.str();
			
			m_Log(log.str());
		}
		
		return json.str();
	}
}
