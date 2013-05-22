/*
 * i2c_slave_control.ino
 * Copyright (C) 2013 Wen Yuzhong <supermartian@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

#include <Servo.h>
#include <Wire.h>

Servo servx;
Servo servy;

void setup()
{
  Serial.begin(115200);
  servx.attach(7);              // Servo on x-axis is attached to 7
  servy.attach(6);              // Servo on x-axis is attached to 6
  Wire.begin(0x32);             // Start as an I2C slave at 0x32
  Wire.onReceive(receiveEvent); // Register the callback on receive
  Serial.println("coming");
}

void loop()
{
}

void receiveEvent(int howMany) {
  Serial.print("n: ");          // How many bytes we've got
  Serial.println(howMany, DEC);

  char a = Wire.read();         // The control number.
  Serial.print("a: ");          // 0x01: set the servo of x-axis
  Serial.println(a, HEX);       // 0x02: set the servo of y-axis

  while (0 < Wire.available()) {
    char c = Wire.read();       // The servo rotation angle
    Serial.print("c: ");
    Serial.println(c, HEX);

    switch (a) {
      case 0x01:
        servx.write(c);
        return;
      case 0x02:
        servy.write(c);
        return;
      default:
        return;
    }
  }
}
