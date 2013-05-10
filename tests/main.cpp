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
	bool useSecureHttp = true; // You can specify whether to use HTTPS to communicate with pusher or not
	
	Pusherpp::CPusher pusher("YOUR_APP_ID", "YOUR_KEY", "YOUR_SECRET", useSecureHttp);
	Pusherpp::CPusherReply response; // To store response received from Pusher
	
	// Note that all calls within the library are blocking

	// Get info about a channel -- note that subscription_count is not enabled by default
	response = pusher.getChannelInfo("test_channel", Pusherpp::CPusher::CH_INFO_SUBS_COUNT);
	std::cout << response.message << std::endl;

	// Get info about a presence channel
	response = pusher.getChannelInfo("presence-ghost",
			  Pusherpp::CPusher::CH_INFO_SUBS_COUNT | Pusherpp::CPusher::CH_INFO_USERCOUNT);
	std::cout << response.message << std::endl;

	// Get a list of occupied channels
	response = pusher.getChannels();
	std::cout << response.message << std::endl;

	// Get a list of occupied channels, filtered by prefix
	response = pusher.getChannels("test");
	std::cout << response.message << std::endl;

	// Get count of users in all presence channels
	response = pusher.getChannels("presence-", Pusherpp::CPusher::CH_INFO_USERCOUNT);
	std::cout << response.message << std::endl;

	// Trigger an event on a single channel
	response = pusher.trigger("test_channel", "my_event", "Stuff");
	std::cout << response << std::endl; // You may also output a CPusherReply object. Debug-friendly.

	// Trigger an event on a set of channels
	response = pusher.trigger(std::vector<std::string>({"test_channel", "test_channel2"}),
		"my_event", "Lots of Stuff");
	std::cout << response << std::endl;

	// Trigger an event on a set of channels, excluding a socket_id
	response = pusher.trigger(std::vector<std::string>({"test_channel", "test_channel2"}),
		"my_event", "Lots of Stuff", "28716.7338");
	std::cout << response << std::endl;

	return 0;
}