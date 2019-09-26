# Simple home automation IoT device to water your plants
## Project featuring ESP8266 DeepSleep and IoT communication.
## Autho: Alvaro Munhoz Mota
### About
This is a simple project I've made to keep my plants alive while travelling and make sure they are ok.
Feel free to use it.
#### What I used for the final hardware
- WeMos D1 Mini (**be careful, since it's operating voltage is 3.3V !**).
- 125V, 0.5m water pump
- 125V, 5A relay module
- jumpers
- 1 led (just to show me when WeMos wakes up)
- 5V Micro USB power source
- cables and power plugs (so you don't need to destroy the pump power cable)
  ![plug](https://github.com/B21Munhoz/irrigationWemos/blob/master/images/plug.jpg)
- a 2m rubber hose (some T connectors may be a nice addition too. I'll try to find them, and if it works good, I'll update the list).

#### Connecting things together
You can connect everything as follows in the sketch.
![sketch](https://github.com/B21Munhoz/irrigationWemos/blob/master/images/deviceSketch_bb.png)
*Sketch*

It will look something like this (this corner is a bit dusty, sorry :sweat_smile:):
![device1](https://github.com/B21Munhoz/irrigationWemos/blob/master/images/IMG_20190314_141032476.jpg)
*The Device*

![device2](https://github.com/B21Munhoz/irrigationWemos/blob/master/images/IMG_20190314_141430375.jpg)
*Sleeping*

![device3](https://github.com/B21Munhoz/irrigationWemos/blob/master/images/IMG_20190314_141307645.jpg)
*Awake*

![device4](https://github.com/B21Munhoz/irrigationWemos/blob/master/images/IMG_20190314_141200792.jpg)
*Water supply with the pump inside*

#### Coding
To write the code I used the Arduino IDE. It's free and have nice tools, like the serial plotter (altho we won't use the plotter here). To use it with ESP, you will need to do a quick setup. [Here](https://averagemaker.com/2018/03/wemos-d1-mini-setup.html) is a nice guide that will help you.
To make the schematics, I used [Fritzing](fritzing.org/home/).

#### IoT control and monitoration
To control the device and keep track of it's activity, I made use of [ThingSpeak](thingspeak.com) platform. Create a channel and two fields. One will store the activation command flag so every 10 minutes, the device will wake up, get the command flag value from the field and do what is needed. The other field will store your device activity, so you can keep track of whatever is happening.

![charts](https://github.com/B21Munhoz/irrigationWemos/blob/master/images/thingspeakcharts.jpg)
*My charts looklike this*

#### Why DeepSleep is important
ESP8266 DeepSleep function can lower your device power consumption by a good ammount. It makes your ESP enter in a state where the only thing working is the RTC. If you plan on creating more awesome stuff or some serious IoT projects, it's good to keep in mind that efficient power consumption is essential.
Take a look [here](https://www.losant.com/blog/making-the-esp8266-low-powered-with-deep-sleep) for better understanding.
If for any reason you need to store some kind of data locally while using DeepSleep, you can make use of it's persistent memmory. It's not used here, since the control flag is stored at a ThingSpeak Field.

#### Conclusion
This is a simple project I've made in one day for fun and to keep my plants alive while I'm visiting my parents. Let me know if you like it or have any suggestion :grin:.
