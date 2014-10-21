---
layout:     post
title:      "Logging Simplified"
date:       2014-10-21T15:12:48-05:00
categories: update
---

As with the goal of this project, I like things simple. If things aren't simple then you wouldn't want to do them. I spent a bit of time making logging a little nicer. My reasoning for spending the time to make a small update to the logging is that it'll be a pain to log things using the old method and if it's difficult or annoying to do I'll find reasons why I shouldn't log something that might prove helpful later. Logging now looks a little something like this:

	#include "log.h"

	void test(void)
	{
		global_log_debug << "yay!";
	}

There is also some code in there for working with other loggers than the global logger but I expect the global logger will be the most helpful.

