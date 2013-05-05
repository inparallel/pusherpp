#include "CPusher.hpp"

namespace Pusherpp
{
	CPusher::CPusher(const std::string& appId, const std::string& key, const std::string& secret) :
	m_AppId(appId), m_Key(key), m_Secret(secret)
	{

	}

	CPusher::~CPusher()
	{

	}

	std::string CPusher::sendMessage(const std::string& channel, const std::string& event, const std::string& msg) const
	{
		std::vector<std::string> vecCh;
		vecCh.push_back(channel);

		return sendMessage(vecCh, event, msg);
	}

	std::string CPusher::sendMessage(const std::vector<std::string>& channels, const std::string& event, const std::string& msg) const
	{
		static std::string authVersion = "1.0";

		long int authTimestamp = time(0);
		std::stringstream postss;
		std::stringstream authss;
		std::stringstream urlss;
		std::string bodyMd5;
		std::string authSignature;
		std::string escMsg;
		
		escMsg = CUtilities::escapeString(msg);
		
		postss << "{\"name\":\"" << event << "\",\"data\":\"" << escMsg << "\",\"channels\":[";
		for(int i = 0; i < channels.size(); i++)
		{
			postss << "\"" << channels[i] << "\"" << (i != channels.size() - 1 ? "," : "");
		}
		postss << "]}";
		
		std::cout << postss.str() << std::endl;

		// Compute the message's MD5
		bodyMd5 = CUtilities::Md5(postss.str());

		// Create the text to be HMACed
		authss << "POST\n/apps/" << m_AppId << "/events\n" << "auth_key=" << m_Key << "&auth_timestamp=" <<
				  authTimestamp << "&auth_version=" << authVersion << "&body_md5=" << bodyMd5;

		authSignature = CUtilities::generateHmac(authss.str(), m_Secret);

		urlss << "http://api.pusherapp.com/apps/" << m_AppId << "/events?" <<
				  "body_md5=" << bodyMd5 <<
				  "&auth_version=" << authVersion <<
				  "&auth_key=" << m_Key <<
				  "&auth_timestamp=" << authTimestamp <<
				  "&auth_signature=" << authSignature;

		return m_Http.sendRequest(urlss.str(), postss.str());
	}
}
