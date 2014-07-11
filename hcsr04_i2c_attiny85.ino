/*
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
/*
 * HC-SR04 to I2C
 *
 * This sketch uses the cheap HC-SR04 and an Attiny85
 * to emulate the MaxBotix I2C XL.
 *
 * Code by smurfy 2014 (github@smurfy.de)
 *
 * Its mainly tested on a "Digispark USB" but 
 * also runs directly on an Attiny85.
 *
 * You need the following hardware:
 * - Attiny85 (or Digispark USB)
 * - 2 x 4.7K resistors (as pull ups)
 * - HC-SR04 sonar
 *
 * Library dependencies:
 * - TinyWireS (https://github.com/rambo/TinyWire)
 * - arduino-tiny (https://code.google.com/p/arduino-tiny/)
 * - PinChangeInterrupt (https://code.google.com/p/arduino-tiny/)
 */

#include <TinyWireS.h>
#include <PinChangeInterrupt.h>   
#define I2C_SLAVE_ADDR  0x70

#define trigPin 3
#define echoPin 4

volatile unsigned long timer_start;
volatile int pulse_time;
boolean sendSecondByte = false;
byte byteDistance = 0;

void handleSonar()
{
  if(digitalRead(echoPin) == HIGH)
  {
    timer_start = micros();
  } else {
    if(timer_start > 0)
    {
      pulse_time = ((volatile int)micros() - timer_start);
      timer_start = 0;
    }
  }
}

void triggerSonar()
{
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
}

void setup() {
  pulse_time = 123;
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  attachPcInterrupt(echoPin, handleSonar, CHANGE);
  TinyWireS.begin(I2C_SLAVE_ADDR);
  triggerSonar();
}

void loop()
{
  if (sendSecondByte) {
    TinyWireS.send(byteDistance);
    sendSecondByte = false;
    byteDistance = 0;
  } else {
    byte received = 0;
    if (TinyWireS.available())	
    {           
      received = TinyWireS.receive(); 
  		
      if (received == 0x51)
      {
        int distance = (pulse_time/2) / 29.1;
        if (distance >= 200 || distance <= 0){
           byteDistance = 0;
        } else {
           byteDistance = (byte) (distance & 0xff);
        }
        TinyWireS.send(0); 
        sendSecondByte = true;
      }
    }
  }
  
  if (timer_start == 0) {
    triggerSonar(); 
  }
}
