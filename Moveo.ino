// Copyright (c) 2018 Enric Balletbo i Serra <eballetbo@gmail.com>
// SPDX-License-Identifier: GPL-3.0+
// -*- mode: C++ -*-

#include <AccelStepper.h>
#include <Servo.h>
#include <MultiStepper.h>

// For RAMPS 1.4
#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62

#define A_STEP_PIN         26 // E0_STEP_PIN
#define A_DIR_PIN          28 // E0_DIR_PIN
#define A_ENABLE_PIN       24 // E0_ENABLE_PIN

#define B_STEP_PIN         36 // E1_STEP_PIN
#define B_DIR_PIN          34 // E1_DIR_PIN
#define B_ENABLE_PIN       30 // E1_ENABLE_PIN

#define SERVO0_PIN         11

// The number of steppers that we want to manage
#define MULTISTEPPER_NUM_STEPPERS 5

// Define the steppers and the pins it will use
AccelStepper StepperX(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
AccelStepper StepperY(AccelStepper::DRIVER, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper StepperZ(AccelStepper::DRIVER, Z_STEP_PIN, Z_DIR_PIN);
AccelStepper StepperA(AccelStepper::DRIVER, A_STEP_PIN, A_DIR_PIN);
AccelStepper StepperB(AccelStepper::DRIVER, B_STEP_PIN, B_DIR_PIN);

// Up to 10 steppers can be handled as a group by MultiStepper
MultiStepper steppers;
// Create servo object to control the nipper
Servo nipper;
// String to hold input command
String inString = "";

String getSubstring(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void setup()
{  
  long positions[MULTISTEPPER_NUM_STEPPERS];

  // Configure stepper X
  StepperX.setMaxSpeed(1000);
  StepperX.setSpeed(2 * 200);
  StepperX.setEnablePin(X_ENABLE_PIN);
  // Configure stepper Y
  StepperY.setMaxSpeed(1000);
  StepperY.setSpeed(2 * 200);
  StepperY.setEnablePin(Y_ENABLE_PIN);
  // Configure stepper Z
  StepperZ.setMaxSpeed(1000);
  StepperZ.setSpeed(2 * 200);
  StepperZ.setEnablePin(Z_ENABLE_PIN);
  // Configure stepper A
  StepperA.setMaxSpeed(1000);
  StepperA.setSpeed(2 * 200);
  StepperA.setEnablePin(A_ENABLE_PIN);
  // Configure stepper B
  StepperB.setMaxSpeed(1000);
  StepperB.setSpeed(2 * 200);
  StepperB.setEnablePin(B_ENABLE_PIN);

  // Then give them to MultiStepper to manage
  steppers.addStepper(StepperX);
  steppers.addStepper(StepperY);
  steppers.addStepper(StepperZ);
  steppers.addStepper(StepperA);
  steppers.addStepper(StepperB);

  // Set all the steppers to the initial position
  for (int i = 0; i < MULTISTEPPER_NUM_STEPPERS; i++)
    positions[i] = 0;
  steppers.moveTo(positions);
  steppers.runSpeedToPosition();  // Blocks until all are in position

  // Attach to the servo
  nipper.attach(SERVO0_PIN);

  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // Wait for serial port to connect. Needed for native USB port only
  }
}

void loop()
{
  long positions[MULTISTEPPER_NUM_STEPPERS];  // Array of desired stepper positions
  String gcode;
  long steps;
  int i;

  // Read serial input:
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    // If you get a newline or a carry return, parse the string
    if (inChar == '\r' || inChar == '\n') {
      // The first substring is the G-code
      gcode = getSubstring(inString, ' ', 0);
      // G01: Linear interpolation
      if (gcode == "G01") {
        Serial.print("G01");
        for (i = 0; i < MULTISTEPPER_NUM_STEPPERS; i++) {
          String str = getSubstring(inString, ' ', i + 1);
          positions[i] = str.toInt();
          Serial.print(' ');
          Serial.print(positions[i]);
        }
        Serial.println();
        steppers.moveTo(positions);
        steppers.runSpeedToPosition();  // Blocks until all are in position
      } else if (gcode == "M280") { // M280: Set servo positon
        String str = getSubstring(inString, ' ', 1);
        long angle = str.toInt();
        if (angle >= 0 && angle <= 180) {
          nipper.write(angle);
          Serial.print("M280 ");
          Serial.println(angle);
        } else {
          Serial.println("M280: Invalid parameter");
        }
      } else {
        Serial.println("Unknown G-code");
      }

      // Clear the string for new input
      inString = "";
    } else {
      // Convert the incoming byte to a char and add it to the string
      inString += (char)inChar;
    }
  }
}

