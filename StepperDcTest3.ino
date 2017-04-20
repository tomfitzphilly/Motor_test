/*

For use with the Adafruit Motor Shield v2
---->	http://www.adafruit.com/products/1438

Runs a stepper and DC Motor if the switch is on
*/


#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x60);
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);
//Set up button pin;
boolean button = 40;
boolean LED = 30;
int cycle = 0;
int rounds = 0;

// Connect a stepper motor to motor port #2 (M3 and M4)
Adafruit_StepperMotor *Step = AFMS.getStepper(200, 2);
Adafruit_DCMotor *DC = AFMS.getMotor(1); //motor port #1 pins 1 and 2

//setup to debounce the button
boolean lastButton = LOW;
boolean currentButton = LOW;
boolean OnOff = LOW;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("STARTING RUN!");

  pinMode(Button,INPUT);
  pinMode(LED,OUTPUT);

  cycle = 1;
  AFMS.begin();  // create with the default frequency 1.6KHz
  DC->setSpeed(150);

  Serial.println("Starting cycle 1");

  digitalWrite(Button,LOW);
  digitalWrite(LED,LOW);

  Serial.println("*************************");
  //Serial.println("How many CYCLES would you line to run?");
  OnOff = button;
}

void loop() {
    rounds = 5;
    digitalWrite (LED, HIGH);
    DC->run(FORWARD);
    Step->step(500, FORWARD, DOUBLE);
    Step->step(500, BACKWARD, DOUBLE);
    cycle = cycle+1;

    Serial.print("cycle---");
    Serial.println(cycle);

    if ( (OnOff = HIGH) && (cycle > rounds) ) {
      digitalWrite (LED, LOW);

      Serial.println("Please shut On/Off to Off");
      Step->release();
      DC->run(RELEASE);
      delay(10000);

      Serial.println ("You have run "), (cycle), ("cycles");
    }

    if (OnOff = LOW) {
      digitalWrite (LED, LOW);

      Serial.println("System Off");
      Step->release();
      DC->run(RELEASE);
    }
}
