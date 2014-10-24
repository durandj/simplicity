---
layout:     post
title:      "Refactoring!"
date:       2014-10-24T15:12:10-05:00
categories: update
---

Finally got around to doing some refactoring. I moved most of the code out of the main point and into a class. I've been wanting to make a class and move away from the C style code. I finally got that done which means I can do things in a more OO way. I don't really like how things are really tenuous in terms of timings but I don't think there's much that can be done about that. For example, in the singletons constructor I had to make sure that any signal handling is done before the background thread is started otherwise the thread just ends up doing weird things. Not a big issue just a stupid one.

