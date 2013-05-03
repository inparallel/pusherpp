pusherpp
=========

Pusher Server Library in C++

About
-----
A C++ server library to push message through Pusher.com service.

Prerequisites
-------------
+ A compiler that supports std::thread and the compiler directive -std=c++0x
+ The following libraries must be installed in your system:
	- libcurl
	- libcrypto (from OpenSSL)

Installing
----------
+ The usual
	- ./configure
	- make
	- [sudo] make install

Linking
-------
+ Make sure you either have /ust/local/lib in your LIBDIR, or include it in you linker lookup dir (e.g. -L/usr/local/lib)
+ To link to the library, use -lpusherpp
+ You also need to link to the following libraries:
	- libcurl (-lcurl)
	- libcrypto (-lcrypto)
	- pthreads (-lpthread)

Features
--------
+ Blocking calls; adding parallelism is up to you (well, so far).
+ Thread-safe
+ Supports pushing to a particular event in a user's channel

TODO
----
+ Adding a threadpool
+ Support for other Pusher features:
	- Publishing an event on multiple channels
	- Querying application state 

License
-------
MIT license

Changelog
---------
+ May 3, 2013
	- Autoconf enabled, now you  can configure/make/make install
	- Changed to blocking calls
+ May 1, 2013
	- Created

