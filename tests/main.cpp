/* 
 * File:   main.cpp
 * Author: mazen
 *
 * Created on April 27, 2013, 12:44 AM
 */

#include <iostream>
#include <pusherpp/CPusher.hpp>
#include <string>

int main(int argc, char** argv)
{
    // Parameters obtained from Pusher.com
    std::string appId  = "YOUR APP ID HERE";
    std::string key    = "YOUR KEY HERE";
    std::string secret = "YOUR SECRET HERE";

    Pusherpp::CPusher pusher(appId, key, secret);

    // This call will block until the reply is received from pusher
    std::cout << "Server says: " << pusher.sendMessage("test_channel", "my_event", "Stuff") << std::endl;

    return 0;
}