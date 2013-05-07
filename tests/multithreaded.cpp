/* 
 * File:   main.cpp
 * Author: mazen
 *
 * Created on May 4, 2013, 12:44 AM
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include <pusherpp/CPusher.hpp>

void threadWork(const Pusherpp::CPusher& pusha, const std::string& msg, int tid)
{
    std::cout << "Thread #" << tid << " | Pushing..." << std::endl;
    std::cout << "Thread #" << tid << " | " << "Message from server: " <<
              pusha.sendMessage("test_channel", "my_event", msg) << std::endl;
}

int main2(int argc, char** argv) 
{
    Pusherpp::CPusher pusher("YOUR APP ID", "YOUR KEY", "YOUR SECRET");

    std::vector<std::thread> tlist;

    // Spawn some threads, each one will post a message to pusher
    for(int i = 0; i < 10; i++)
    {
        tlist.emplace_back(std::thread(threadWork, pusher, std::to_string(i), i));
    }

    // Do something here..
    // .. another thing here..
    // .. search for the Higgs Boson..

    // Wait for all threads to complete
    for(auto& t : tlist)
    {
        t.join();
    }

    return 0;
}