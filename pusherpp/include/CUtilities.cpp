#include "CUtilities.hpp"

namespace Pusherpp
{
	std::string CUtilities::generateHmac(const std::string& message, const std::string& secret)
	{
		const char* key = secret.c_str();
		const char* data = message.c_str();
		unsigned char* digest;

		digest = HMAC(EVP_sha256(), key, secret.length(), (unsigned char*) data, message.length(), NULL, NULL);

		char mdString[SHA256_DIGEST_LENGTH * 2];
		for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
			sprintf(&mdString[i * 2], "%02x", (unsigned int) digest[i]);

		return std::string(mdString);
	}

	std::string CUtilities::Md5(const std::string& input)
	{
		unsigned char result[MD5_DIGEST_LENGTH];
		MD5((const unsigned char*) (input.c_str()), input.length(), result);

		char mdString[MD5_DIGEST_LENGTH * 2];
		for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
			sprintf(&mdString[i * 2], "%02x", (unsigned int) result[i]);

		return std::string(mdString);
	}

	std::string CUtilities::escapeString(const std::string& str)
	{
		std::stringstream ss;
		for (int i = 0; i < str.length(); i++)
		{
			if (unsigned(str[i]) < '\x20' || str[i] == '\\' || str[i] == '"')
			{
				ss << "\\u" << std::setfill('0') << std::setw(4) << std::hex << (unsigned) str[i];
			} 
			else
			{
				ss << str[i];
			}
		}
		
		return ss.str();
	}
}