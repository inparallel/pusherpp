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
	Pusherpp::CPusher pusher("YOUR APP ID", "YOUR KEY", "YOUR SECRET");
	Pusherpp::CPusherReply response; // To store response received from Pusher
	
	// Get a list of channels
	response = pusher.getChannels();
	std::cout << response.message << std::endl;
	
	// Get a list of channels by prefix
	response = pusher.getChannels("test");
	std::cout << response.message << std::endl;
	
	// Get count of users in all presence channels
	response = pusher.getChannels("presence-", Pusherpp::CPusher::CH_INFO_USERCOUNT);
	std::cout << response.message << std::endl;
	
	// Trigger an event on a single channel (blocking call)
	response = pusher.trigger("test_channel", "my_event", "Stuff"); 
	std::cout << response << std::endl; // You may also output a CPusherReply. Debug-friendly.
	
	// Trigger an event on a set of channels
	response = pusher.trigger(std::vector<std::string>({"test_channel", "test_channel2"}), 
			  "my_event", "Lots of Stuff");
	std::cout << response << std::endl;
	
	return 0;
}