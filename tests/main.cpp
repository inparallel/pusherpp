/* 
 * File:   main.cpp
 * Author: mazen
 *
 * Created on April 27, 2013, 12:44 AM
 */

#include <cstdlib>
#include "CPusher.hpp"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) 
{
	CPusher pusher("42773", "6ad70f7e8fe55b3046b0", "3981719d6eec722aa91a");
	
	pusher.sendMessage("test_channel", "my_event", "Yellow!");
	
	usleep(100000000);
	
	return 0;
}

