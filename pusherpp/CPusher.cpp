#include "CPusher.hpp"
#include "CPusherReply.hpp"
#include <assert.h>

namespace Pusherpp
{

	CPusher::CPusher(const std::string& appId, const std::string& key, const std::string& secret, bool useSecure) :
	m_AppId(appId), m_Key(key), m_Secret(secret), m_UseSecure(useSecure)
	{

	}

	CPusher::~CPusher()
	{

	}

	const CPusherReply CPusher::sendMessage(const std::string& channel, const std::string& event, const std::string& msg) const
	{
		std::vector<std::string> lCh;
		lCh.push_back(channel);

		return trigger(lCh, event, msg);
	}

	const CPusherReply CPusher::sendMessage(const std::vector<std::string>& channels, const std::string& event, const std::string& msg) const
	{
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
		long httpCode;
		CPusherReply ret;
		std::stringstream postss;

		postss << "{\"name\":\"" << event << "\",\"data\":\"" << CUtilities::escapeString(msg) << "\",\"channels\":[";
		for (int i = 0; i < channels.size(); i++)
		{
			postss << "\"" << channels[i] << "\"" << (i != channels.size() - 1 ? "," : "");
		}
		postss << "], \"socket_id\":\""<< socketId << "\"}";

		ret.message = m_Http.postRequest(this->generatePostUrl("/events", postss.str()), postss.str(), httpCode);
		ret.error = this->interpretCode(httpCode);


		return ret;
	}

	const CPusherReply CPusher::getChannelInfo(const std::string& channel, long vAddInfo)
	{
		long httpCode;
		CPusherReply ret;

		std::map<std::string, std::string> params;
		std::stringstream buff;
		std::stringstream chss;
		std::string url;
		bool addComma = false;

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
		long httpCode;
		CPusherReply ret;

#if 0
		// If info = "user_count", then make sure the filterByPrefix is equal to "presence-"
		bool correctParams = (info == CPusher::EChannelInfo::CH_INFO_USERCOUNT ?
				  (filterByPrefix.compare("presence-") == 0 ? true : false) :
				  true);
		assert(correctParams && "You can ask for user_count info only for channels prefixed with presence-");

		// Also, make sure that the info queried is not about subscription count (since it 
		// can only be applied for queries about one channel)
		assert(info != CPusher::EChannelInfo::CH_INFO_SUBS_COUNT &&
				  "You can not query about subscription_count for all channels");
#endif
		
		std::map<std::string, std::string> params;
		params["filter_by_prefix"] = filterByPrefix;
		params["info"] = (info == CPusher::CH_INFO_USERCOUNT ? "user_count" : "");

		std::string url = CPusher::generateGetUrl("/channels", params);

		ret.message = m_Http.getRequest(url, httpCode);
		ret.error = this->interpretCode(httpCode);

		return ret;
	}
}
