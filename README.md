# HC-SR04 to I2C
 
This sketch uses the cheap HC-SR04 and an Attiny85
to emulate the MaxBotix I2C XL.

Code by smurfy 2014 (github@smurfy.de)

Its mainly tested on a "Digispark USB" but 
also runs directly on an Attiny85.

You need the following hardware:
- Attiny85 (or Digispark USB)
- 2 x 4.7K resistors (as pull ups)
- HC-SR04 sonar

Library dependencies:
- TinyWireS (https://github.com/rambo/TinyWire)
- arduino-tiny (https://code.google.com/p/arduino-tiny/)
- PinChangeInterrupt (https://code.google.com/p/arduino-tiny/)