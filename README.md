 WORD CLOCK - NeoMatrix 8x8 Desktop Edition
================
 by [Andy Doro](https://andydoro.com/) & [Dano Wall](https://github.com/danowall)
 
https://andydoro.com/wordclockdesktop/

[Adafruit Learn Guide](https://learn.adafruit.com/neomatrix-8x8-word-clock/)

A word clock which uses NeoPixel RGB LEDs for a color shifting effect.

Forked by me (vexandmore) to show the moon phase, day, and year every few minutes. I also changed the default brightness.

How to read it
--------------
The time of day is read as usual. However, the day, month, and year are read a bit differently:
- The day of month is read close to the time, with one exception: 30 and 31 are 'twenty ten one' and 'twenty ten two' respectively
- The month of year is read by counting the number of bars that are filled in. Each bar is 1x4 LEDs in the matrix
- The year is shown as the last two digits, ie 2022 is 'twenty two'. This only works until 2029; after that, it will show the year in binary across the bottom
- The lunar phase is shown as a pictogram; I have not modified this from the original code

How to configure
----------------
Go into the ```WordClock-NeoMatrix8x8``` folder and open ```config.h```. There are many
options there, including changing the amount of time each mode stays on, the
brightness, daylight savings time, etc.

To change the order of the modes, head to ```WordClock_NeoMatrix8x8.ino``` and change 
the order of the ```states[]``` array.


Hardware
-------
 
 - [Trinket Pro 5V](https://www.adafruit.com/product/2000) (should work with other Arduino-compatibles with minor modifications) 
 - [DS1307 RTC breakout](https://www.adafruit.com/products/3296)
 - [NeoPixel NeoMatrix 8x8](https://www.adafruit.com/products/1487)
 - laser cut faceplate & enclosure
 
Software
-------
 
This code requires the following libraries:
 
 - [RTClib](https://github.com/adafruit/RTClib)
 - [DST_RTC](https://github.com/andydoro/DST_RTC)
 - [Adafruit_GFX](https://github.com/adafruit/Adafruit-GFX-Library)
 - [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
 - [Adafruit_NeoMatrix](https://github.com/adafruit/Adafruit_NeoMatrix)


Wiring
-------

 - Solder DS1307 breakout to Trinket Pro, A2 to GND, A3 to PWR, A4 to SDA, A5 to SCL  
   If you leave off / clip the unused SQW pin on the RTC breakout, the breakout can sit right on top of the Trinket Pro for a compact design! It'll be difficult to reach the Trinket Pro reset button, but you can activate the bootloader by plugging in the USB.
 - Solder NeoMatrix 5V to Trinket 5V, GND to GND, DIN to Trinket Pro pin 8.
 

grid pattern
-------

 ```
 A T W E N T Y D
 Q U A R T E R Y
 F I V E H A L F
 D P A S T O R O
 F I V E I G H T
 S I X T H R E E
 T W E L E V E N
 F O U R N I N E
 ```
 
Acknowledgements:
  - Thanks [Dano](https://github.com/danowall) for faceplate / 3D models & project inspiration! 
 

