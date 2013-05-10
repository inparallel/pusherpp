#include <string>
#include "CPusherReply.hpp"

namespace Pusherpp
{

	CPusherReply::CPusherReply(const std::string& msg, ErrorCode err) :
	message(msg), error(err)
	{

	}

	CPusherReply::CPusherReply()
	{

	}

	CPusherReply::~CPusherReply()
	{

	}

	std::ostream& operator <<(std::ostream& os, const CPusherReply& rep)
	{
		os << "{Error Code: " << rep.error << " ";

		switch(rep.error)
		{
			case Pusherpp::CPusherReply::PSH_AUTH_ERROR:
			std::cout << "(Authentication error)" << std::endl;
			break;

			case Pusherpp::CPusherReply::PSH_FORBIDDEN:
			std::cout << "(Forbidden)" << std::endl;
			break;

			case Pusherpp::CPusherReply::PSH_GENERIC_ERROR:
			std::cout << "(Generic error, see message)" << std::endl;
			break;

			case Pusherpp::CPusherReply::PSH_OVERFLOW:
			std::cout << "(Data size is > 10KB)" << std::endl;
			break;

			case Pusherpp::CPusherReply::PSH_UNKNOWN:
			std::cout << "(Unknown Error)" << std::endl;
			break;

		}
		
		std::cout << ", Reply Message: " << (rep.message.size() != 0 ? rep.message : "(No message)") << "}";

		return os;
	}
}


