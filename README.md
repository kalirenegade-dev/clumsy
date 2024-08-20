This version adds some additional features such as the following:
hotkey toggles (custom keybind)
function presets (save and set variables)
updated bandwidth module with a queue for bandwidth limit (with a KB/MB toggle) based off of https://github.com/kuhnliu/clumsy
Hotspot support (with the ability to toggle local/remore) based off of https://github.com/abaza121/clumsy-hotspot

# clumsy

__clumsy makes your network condition on Windows significantly worse, but in a managed and interactive manner.__

Leveraging the awesome [WinDivert](http://reqrypt.org/windivert.html), clumsy stops living network packets and capture them, lag/drop/tamper/.. the packets on demand, then send them away. Whether you want to track down weird bugs related to broken network, or evaluate your application on poor connections, clumsy will come in handy:

* No installation.
* No need for proxy setup or code change in your application.
* System wide network capturing means it works on any application.
* Works even if you're offline (ie, connecting from localhost to localhost).
* Your application keeps running, while clumsy can start and stop anytime.
* Interactive control how bad the network can be, with enough visual feedback to tell you what's going on.

See [this page](http://jagt.github.io/clumsy) for more info and build instructions.


## Details

Simulate network latency, delay, packet loss with clumsy on Windows 7/8/10:

![](clumsy-demo.gif)


## License

MIT
