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
		return trigger(channel, event, msg);
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
		std::string url;

		postss << "{\"name\":\"" << event << "\",\"data\":\"" << CUtilities::escapeString(msg) << "\",\"channels\":[";
		for (int i = 0; i < channels.size(); i++)
		{
			postss << "\"" << channels[i] << "\"" << (i != channels.size() - 1 ? "," : "");
		}
		postss << "], \"socket_id\":\""<< socketId << "\"}";

		url = this->generatePostUrl("/events", postss.str());
		ret.message = m_Http.postRequest(url, postss.str(), httpCode);
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
}
