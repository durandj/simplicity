---
layout:     post
title:      "Logging Debug"
date:       2014-10-20 18:37:00
categories: update
---
I've been working on getting logging added since that will definitely help with tracking down issues and makeing sure all goes as it should. Since I'm already using Boost I decided to go with Boost.Log. It took a bit of work to get setup since I'm still new to using the AutoConf toolchain with Boost and I'm a bit rusty with C++ but in the end I got it. It does some really basic logging. My next goal is to make logging a bit easier to use since I'll be more inclined to log things if I don't have to jump through hoops to do it. Currently logging looks something like this:

	#include <boost/log/core.hpp>

	#include "main.h"

	void log_something(void)
	{
		BOOST_LOG_SEV(get_global_logger(), boost::log::trivial::debug) << "Yay!";
	}

I ommitted a bit more code but that's the general idea. That's not very friendly. I want to make this a bit easier to do so I'm going to add some helper functions so that you can just do this:

	log_debug() << "Yay!";

That's what I'm looking at for now. I would like to make things even better but I need to do some testing first and I want to keep my one step at a time approach.

I also need to do some work on the blog. I want to theme it at some point and it really needs some tools to make generating posts a bit easier. I'll do some work on that when I need a break.

