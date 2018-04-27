// Copyright (c) 2018 Enric Balletbo i Serra <eballetbo@gmail.com>
// SPDX-License-Identifier: GPL-3.0+
// -*- mode: C++ -*-

#include <AccelStepper.h>

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

// Define the steppers and the pins it will use
AccelStepper StepperX(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
AccelStepper StepperY(AccelStepper::DRIVER, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper StepperZ(AccelStepper::DRIVER, Z_STEP_PIN, Z_DIR_PIN);
AccelStepper StepperA(AccelStepper::DRIVER, A_STEP_PIN, A_DIR_PIN);
AccelStepper StepperB(AccelStepper::DRIVER, B_STEP_PIN, B_DIR_PIN);

void setup()
{  
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

  Serial.begin(115200);
}

void move(long steps, AccelStepper *stepper)
{
  Serial.print("Moving stepper");
  Serial.print(steps);
  Serial.println(" steps");

  stepper->move(steps);
  stepper->setSpeed(2 * 200);
}

void loop()
{
  AccelStepper *stepper;
  long steps;

  // Change this variable to point to another stepper
  stepper = &StepperX;

  Serial.setTimeout(2000); // 2 seconds
  if (Serial.available()) {
    steps = Serial.parseInt();
    if (steps != 0)
      move(steps, stepper);
  }

  stepper->runSpeedToPosition();
}

