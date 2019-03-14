## Project featuring ESP8266 DeepSleep and IoT communication.

#### What I used for the hardware
- WeMos D1 Mini
- 0.5m water pump
- 125V, 5A relay
- breadborad
- jumpers
- 1 led (just to show me when WeMos wakes up)
- YwRobot breadboard power supply (to make things easy, but not necessary)
- Micro USB cable

#### DeepSleep
ESP8266 DeepSleep function can lower your device power consumption by a good ammount.
Take a look: https://www.losant.com/blog/making-the-esp8266-low-powered-with-deep-sleep
If for any reason you need to store some kind of data locally while using DeepSleep, you can
make use of it's persistent memmory. It's not used here, since the control flag is stored at
a ThingSpeak Field.

#### IoT control and monitoration
To control the device and keep track of it's activity, I made use of ThingSpeak.com.
