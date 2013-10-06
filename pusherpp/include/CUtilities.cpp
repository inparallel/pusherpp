#include "CUtilities.hpp"

namespace Pusherpp
{
	std::string CUtilities::generateHmac(const std::string& message, const std::string& secret)
	{
		const char* key = secret.c_str();
		const char* data = message.c_str();
		unsigned char digest [EVP_MAX_MD_SIZE];
		unsigned int size = EVP_MAX_MD_SIZE;

		HMAC(EVP_sha256(), key, m_Secret.length(), (unsigned char*) data, message.length(), digest, &size);

		std::stringstream ret;
		for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
			ret << std::hex << std::setw(2) << std::setfill('0') <<  (unsigned int) digest[i];

		return ret.str();
	}

	std::string CUtilities::Md5(const std::string& input)
	{
		unsigned char result[MD5_DIGEST_LENGTH];
		MD5((const unsigned char*) (input.c_str()), input.length(), result);

		std::stringstream ret;
		for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
			ret << std::hex << std::setw(2) << std::setfill('0') <<  (unsigned int) result[i];

		return ret.str();
	}

	std::string CUtilities::escapeString(const std::string& str)
	{
		std::stringstream ss;
		for (int i = 0; i < str.length(); i++)
		{
			if (unsigned(str[i]) < '\x20' || str[i] == '\\' || str[i] == '"')
				ss << "\\\"";
			else
				ss << str[i];
		}
		
		return ss.str();
	}
}
