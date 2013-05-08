pusherpp
=========

Pusher Server Library in C++

About
-----
A C++ server library to push message through Pusher.com service.

Prerequisites
-------------
+ A compiler that supports `std::thread` and the compiler directive `-std=c++0x`
+ The following libraries are required:
	- libcurl
	- libcrypto (from OpenSSL)

Installing
----------
+ The usual
	- `./configure`
	- `make`
	- `[sudo] make install`

Linking
-------
+ Make sure you either have `/ust/local/lib` in your `LIBDIR`, or include it in you linker lookup dir (e.g. `-L/usr/local/lib`)
+ To link to the library, use `-lpusherpp`
+ You also need to link to the following libraries:
	- libcurl (`-lcurl`)
	- libcrypto (`-lcrypto`)
	- pthreads (`-lpthread`)

Features
--------
+ Blocking calls; adding parallelism is up to you (well, so far).
+ Thread-safe
+ Supports pushing to a particular event in to one or multiple channels

Examples
--------
### Simple Example
```C++
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
```

### Multithreaded Example
```C++
#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include <pusherpp/CPusher.hpp>

void threadWork(const Pusherpp::CPusher& pusha, const std::string& msg, int tid)
{
	std::cout << "Thread #" << tid << " | Pushing..." << std::endl;
	std::cout << "Thread #" << tid << " | " << "Message from server: " <<
			  pusha.trigger("test_channel", "my_event", msg) << std::endl;
}

int main(int argc, char** argv)
{
	Pusherpp::CPusher pusher("YOUR APP ID", "YOUR KEY", "YOUR SECRET");

	std::vector<std::thread> tlist;

	// Spawn some threads, each one will post a message to pusher
	for (int i = 0; i < 10; i++)
	{
		tlist.emplace_back(std::thread(threadWork, pusher, std::to_string(i), i));
	}

	// Do something here..
	// .. another thing here..
	// .. search for the Higgs Boson..

	// Wait for all threads to complete
	for (auto& t : tlist)
	{
		t.join();
	}

	return 0;
}

```

TODO
----
+ Supporting async calls
+ Support for other Pusher features:
	- Querying application state 

Changelog
---------
+ May 8, 2013
	- sendMessage() is now deprecated, use trigger() instead
+ May 7, 2013
	- Error messages reported from Pusher are stored
+ May 5, 2013
	- Now supports pushing to multiple channels
+ May 3, 2013
	- Autoconf enabled, now you  can configure/make/make install
	- Changed to blocking calls
+ May 1, 2013
	- Created
	
License
-------
The MIT License (MIT)

Copyright (c) 2013 Futures Business Development

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
