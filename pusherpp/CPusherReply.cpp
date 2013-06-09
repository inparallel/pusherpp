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
			os << "(Authentication error)" << std::endl;
			break;

			case Pusherpp::CPusherReply::PSH_FORBIDDEN:
			os << "(Forbidden)" << std::endl;
			break;

			case Pusherpp::CPusherReply::PSH_GENERIC_ERROR:
			os << "(Generic error, see message)" << std::endl;
			break;

			case Pusherpp::CPusherReply::PSH_OVERFLOW:
			os << "(Data size is > 10KB)" << std::endl;
			break;

			case Pusherpp::CPusherReply::PSH_UNKNOWN:
			os << "(Unknown Error)" << std::endl;
			break;

		}
		
		os << ", Reply Message: " << (rep.message.size() != 0 ? rep.message : "(No message)") << "}";

		return os;
	}
}


