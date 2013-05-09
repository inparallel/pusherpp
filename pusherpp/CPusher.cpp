#include "CPusher.hpp"
#include "CPusherReply.hpp"

namespace Pusherpp
{

	CPusher::CPusher(const std::string& appId, const std::string& key, const std::string& secret) :
	m_AppId(appId), m_Key(key), m_Secret(secret)
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

	const CPusherReply CPusher::trigger(const std::string& channel, const std::string& event, const std::string& msg) const
	{
		std::vector<std::string> lCh;
		lCh.push_back(channel);

		return sendMessage(lCh, event, msg);
	}

	const CPusherReply CPusher::trigger(const std::vector<std::string>& channels, const std::string& event, const std::string& msg) const
	{
		long httpCode;
		CPusherReply ret;
		std::stringstream postss;
		
		postss << "{\"name\":\"" << event << "\",\"data\":\"" << CUtilities::escapeString(msg) << "\",\"channels\":[";
		for (int i = 0; i < channels.size(); i++)
		{
			postss << "\"" << channels[i] << "\"" << (i != channels.size() - 1 ? "," : "");
		}
		postss << "]}";

		ret.message = m_Http.postRequest(this->generatePostUrl("/events", postss.str()), postss.str(), httpCode);
		ret.error = this->interpretCode(httpCode);
		

		return ret;
	}

	const CPusherReply CPusher::getChannelInfo(const std::string& channel)
	{
		
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
