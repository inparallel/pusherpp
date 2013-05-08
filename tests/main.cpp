/* 
 * File:   main.cpp
 * Author: mazen
 *
 * Created on April 27, 2013, 12:44 AM
 */

#include <iostream>
#include <pusherpp/CPusher.hpp>
#include <pusherpp/CPusherReply.hpp>
#include <string>
#include <vector>

int main(int argc, char** argv)
{
	// Parameters obtained from Pusher.com
	std::string appId = "YOUR APP ID HERE";
	std::string key = "YOUR KEY HERE";
	std::string secret = "YOUR SECRET HERE";

	Pusherpp::CPusher pusher(appId, key, secret);
	Pusherpp::CPusherReply reply;

	std::cout << "Pushing to one channel..." << std::endl;
	reply = pusher.trigger("test_channel", "my_event", 
			  "Stuff"); // This call will block until the reply is received from pusher
	std::cout << "Got the following HTTP code from server: " << reply.error << std::endl;
	std::cout << "And the following message: " << reply.message << std::endl;
	std::cout << "---------------------------------" << std::endl;

	// Publish to multiple channels...
	std::cout << "Pushing to multiple channels..." << std::endl;
	reply = pusher.trigger(std::vector<std::string>({"test_channel", "test_channel2"}), 
			  "my_event", "Lots of Stuff");
	std::cout << "Server says: " << 
			  reply << std::endl; // You can directly output the CPusherReply object

	return 0;
}