/*
 * i2c_slave_control.ino
 * Copyright (C) 2013 Wen Yuzhong <supermartian@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 *
 * I2C on Arduino UNO: A4 (SDA), A5 (SCL)
 * Servo X: A7  Servo Y: A6
 * Main motor: F: 8, B: 9, PWM: 10
 * Veer motor: L: 11, R:12  
 */

#include <Servo.h>
#include <Wire.h>

Servo servx;
Servo servy;
int m1a = 8;   // Main motor control
int m1b = 9;
int m1s = 10;  // Main motor PWM control
int m2a = 11;  // Veer motor control
int m2b = 12;  
int m1speed;

void setup()
{
  Wire.begin(0x32);             // Start as an I2C slave at 0x32
  Wire.onReceive(receiveEvent); // Register the callback on receive
  servx.attach(7);              // Servo on x-axis is attached to 7
  servy.attach(6);              // Servo on y-axis is attached to 6  
  
  pinMode(m1a, OUTPUT);
  pinMode(m1b, OUTPUT);
  pinMode(m1s, OUTPUT);
  pinMode(m2a, OUTPUT);
  pinMode(m2b, OUTPUT);
  
  m1speed = 0;
}

void speedControl(int s)
{
  int pwm;
  if (s > 0) {
    digitalWrite(m1a, HIGH);
    digitalWrite(m1b, LOW);
    pwm = s;
  } else {
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, HIGH);
    pwm = 0 - s;
  }
  
  pwm = pwm > 100 ? 100 : pwm;
  digitalWrite(m1s, HIGH);
  delayMicroseconds(pwm * 10);
  digitalWrite(m1s, LOW);  
  delayMicroseconds(1000 - pwm * 10);
}

void veerControl(int d)
{
  if (d > 0) {
    digitalWrite(m2a, HIGH);
    digitalWrite(m2b, LOW);
  } else {
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, HIGH);
  }
}

void loop()
{
  speedControl(m1speed);
}

void receiveEvent(int howMany) {
  char a = Wire.read();         // The control number.

  while (0 < Wire.available()) {
    char c = Wire.read();       // The servo rotation angle

    switch (a) {
      case 0x01:
        servx.write(c);
        return;
      case 0x02:
        servy.write(c);
        return;
      case 0x03:
        speedControl(c);
        m1speed = c;
        return;
      case 0x04:
        veerControl(c);
        return;
      default:
        return;
    }
  }
}
