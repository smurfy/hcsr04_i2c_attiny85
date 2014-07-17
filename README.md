# HC-SR04 to I2C
 
This sketch uses the cheap HC-SR04 and an Attiny85
to emulate the MaxBotix I2C XL.

Code by smurfy 2014 (github@smurfy.de)

Its mainly tested on a "Digispark USB" but 
also runs directly on an Attiny85.

You need the following hardware:
- Attiny85 (or Digispark USB)
- HC-SR04 sonar
- optional 2 x 4.7K resistors (as pull ups)

Connection Schema:
    HC-SR04:
       |-------------
       |(  )    (  )|
       --------------
           1 2 3 4

     (1) VCC      ->    VCC 5V
     (2) TRIG     ->    Pin 2 on Attiny85 (PB3)
     (3) ECHO     ->    Pin 3 on Attiny85 (PB4)
     (4) GRD      ->    Ground

    Attiny85:
      1 |--U--| 8
      2 |-----| 7
      3 |-----| 6
      4 |-----| 5

     (1) RESET    ->    nothing
     (2) PB3      ->    TRIG on HC-SR04
     (3) PB4      ->    ECHO on HC-SR04
     (4) GND      ->    Ground 
     (5) PB0, SDA ->    SDA of the I2C Bus
     (6) PB1      ->    nothing
     (7) PB2, SCL ->    SCL of the I2C Bus
     (8) VCC      ->    VCC 5V or 3.3V
     
    Optional pull-up 4.7K resistors:
      1 ---[xxxxx]--- 2
     
     (1) one side   ->  VCC 5V or 3.3V
     (2) the other  ->  SDA or SCL of the I2C Bus

    Connect the first pull-up resistor between VCC and SDA
    and the second one between VCC and SCL.
     
Library dependencies:
- TinyWireS (https://github.com/rambo/TinyWire)
- arduino-tiny (https://code.google.com/p/arduino-tiny/)
- PinChangeInterrupt (https://code.google.com/p/arduino-tiny/)