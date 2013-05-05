/* 
 * File:   main.cpp
 * Author: mazen
 *
 * Created on April 27, 2013, 12:44 AM
 */

#include <iostream>
#include <pusherpp/CPusher.hpp>
#include <string>
#include <vector>

int main(int argc, char** argv)
{
    // Parameters obtained from Pusher.com
    std::string appId  = "YOUR APP ID HERE";
    std::string key    = "YOUR KEY HERE";
    std::string secret = "YOUR SECRET HERE";

    Pusherpp::CPusher pusher(appId, key, secret);

    // This call will block until the reply is received from pusher
    std::cout << "Server says: " << pusher.sendMessage("test_channel", "my_event", "Stuff") << std::endl;

    // Publish to multiple channels...
    std::cout << "Server says: " << pusher.sendMessage(std::vector<std::string>({"test_channel", "test_channel2"}), 
				"my_event", "Stuff") << std::endl;

    return 0;
}