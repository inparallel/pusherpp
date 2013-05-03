/* 
 * File:   main.cpp
 * Author: mazen
 *
 * Created on April 27, 2013, 12:44 AM
 */

#include <cstdlib>
#include <pusherpp/CPusher.hpp>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) 
{
	Pusherpp::CPusher pusher("YOUR APP ID", "YOUR KEY", "YOUR SECRET");
	
	pusher.sendMessage("test_channel", "my_event", "Yellow!");
	
	return 0;
}

