/* 
 * File:   main.cpp
 * Author: mazen
 *
 * Created on May 4, 2013, 12:44 AM
 */

#include <cstdlib>
#include <thread>
#include "../pusherpp/CPusher.hpp"

using namespace std;

void threadWork(const Pusherpp::CPusher& pusha, const std::string& msg, int tid)
{
	std::cout << "Thread #" << tid << " | Pushing..." << std::endl;
	std::cout << "Thread #" << tid << " | " << "Message from server: " <<
			  pusha.sendMessage("test_channel", "my_event", msg) << std::endl;
}

int main(int argc, char** argv) 
{
	Pusherpp::CPusher pusher("42773", "6ad70f7e8fe55b3046b0", "3981719d6eec722aa91a"); 
	
	std::vector<std::thread> tlist;
	
	// Spawn some threads, each one will post a message to pusher
	for(int i = 0; i < 10; i++)
	{
		tlist.emplace_back(std::thread(threadWork, pusher, std::to_string(i), i));
	}
	
	// Wait for all threads to complete...
	for(int i = 0; i < 10; i++)
	{
		tlist[i].join();
	}
	
	return 0;
}

