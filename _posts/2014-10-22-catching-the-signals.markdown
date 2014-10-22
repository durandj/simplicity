---
layout:     post
title:      "Catching the Signals"
date:       2014-10-22T16:51:04-05:00
categories: update
---

I've been working a bit on handling Unix process signals. This means I can actually terminate Simplicity normally instead of having to force the process to terminate. This also happens to make testing a bit easier. It's really only basic handling using Boost.ASIO and Boost.Thread. Boost.ASIO is providing the signal handling and Boost.Thread puts the handling onto a different thread. I didn't really want to have another thread doing it but that was the only way I could find to keep the io_service from being a synchronous operation. It should be a pretty lightweight thread I believe. I'm hoping anyway.

I think I'm now on to trying to get more things happening with GLib and GTK.

