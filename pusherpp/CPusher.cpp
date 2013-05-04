#include "CPusher.hpp"

namespace Pusherpp
{
	std::string CPusher::generateHmac(const std::string& message) const
	{
		const char* key  = m_Secret.c_str();
		const char* data = message.c_str();
		unsigned char* digest;

		digest = HMAC(EVP_sha256(), key, m_Secret.length(), (unsigned char*)data, message.length(), NULL, NULL);    

		char mdString[SHA256_DIGEST_LENGTH * 2];
		for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
			  sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
	
		return std::string(mdString);
	}

	std::string CPusher::Md5(const std::string& input) const
	{
		unsigned char result[MD5_DIGEST_LENGTH];
		MD5((const unsigned char*)(input.c_str()), input.length(), result);
	
		char mdString[MD5_DIGEST_LENGTH * 2];
		for(int i = 0; i < MD5_DIGEST_LENGTH; i++)
			  sprintf(&mdString[i*2], "%02x", (unsigned int)result[i]);
	
		return std::string(mdString);
	}

	CPusher::CPusher(const std::string& appId, const std::string& key, const std::string& secret) : 
		m_AppId(appId), m_Key(key), m_Secret(secret)
	{
	
	}

	CPusher::~CPusher()
	{
	
	}

	std::string CPusher::sendMessage(const std::string& channel, const std::string& event, const std::string& jsonMsg) const
	{
		static std::string auth_version = "1.0";
		
		long int           auth_timestamp = time(0);
		std::stringstream  postss;
		std::stringstream  authss;
		std::stringstream  urlss;
		std::string        body_md5;
		std::string        auth_signature;
		
		postss << "{\"name\":\"" << event << "\",\"data\":\"" << jsonMsg << "\",\"channel\":\"" << channel << "\"}";

		// Compute the message's MD5
		body_md5 = Md5(postss.str());

		// Create the text to be HMACed
		authss << "POST\n/apps/" << m_AppId << "/events\n" << "auth_key=" << m_Key << "&auth_timestamp=" << 
				  auth_timestamp << "&auth_version=" << auth_version << "&body_md5=" << body_md5;

		auth_signature = generateHmac(authss.str());
		
		urlss << "http://api.pusherapp.com/apps/" << m_AppId        << "/events?" <<
		         "body_md5="                      << body_md5       << 
		         "&auth_version="                 << auth_version   <<
		         "&auth_key="                     << m_Key          <<
		         "&auth_timestamp="               << auth_timestamp << 
		         "&auth_signature="               << auth_signature;

		return m_Http.sendRequest(urlss.str(), postss.str());
	}
}
