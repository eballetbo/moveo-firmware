// Copyright (c) 2018 Enric Balletbo i Serra <eballetbo@gmail.com>
// SPDX-License-Identifier: GPL-3.0+
// -*- mode: C++ -*-

#include <AccelStepper.h>

// For RAMPS 1.4
#define X0_STEP_PIN         54
#define X0_DIR_PIN          55
#define X0_ENABLE_PIN       38

#define Y0_STEP_PIN         60
#define Y0_DIR_PIN          61
#define Y0_ENABLE_PIN       56

#define Z0_STEP_PIN         46
#define Z0_DIR_PIN          48
#define Z0_ENABLE_PIN       62

#define E0_STEP_PIN         26
#define E0_DIR_PIN          28
#define E0_ENABLE_PIN       24

#define E1_STEP_PIN         36
#define E1_DIR_PIN          34
#define E1_ENABLE_PIN       30
    
// Define the steppers and the pins it will use
AccelStepper StepperX0(AccelStepper::DRIVER, X0_STEP_PIN, X0_DIR_PIN);
AccelStepper StepperY0(AccelStepper::DRIVER, Y0_STEP_PIN, Y0_DIR_PIN);
AccelStepper StepperZ0(AccelStepper::DRIVER, Z0_STEP_PIN, Z0_DIR_PIN);
AccelStepper StepperE0(AccelStepper::DRIVER, E0_STEP_PIN, E0_DIR_PIN);
AccelStepper StepperE1(AccelStepper::DRIVER, E1_STEP_PIN, E1_DIR_PIN);

void setup()
{  
  // Configure stepper X0
  StepperX0.setMaxSpeed(1000);
  StepperX0.setSpeed(2 * 200);
  StepperX0.setEnablePin(X0_ENABLE_PIN);
  // Configure stepper Y0
  StepperY0.setMaxSpeed(1000);
  StepperY0.setSpeed(2 * 200);
  StepperY0.setEnablePin(Y0_ENABLE_PIN);
  // Configure stepper Z0
  StepperZ0.setMaxSpeed(1000);
  StepperZ0.setSpeed(2 * 200);
  StepperZ0.setEnablePin(Z0_ENABLE_PIN);
  // Configure stepper E0
  StepperE0.setMaxSpeed(1000);
  StepperE0.setSpeed(2 * 200);
  StepperE0.setEnablePin(E0_ENABLE_PIN);
  // Configure stepper E1
  StepperE1.setMaxSpeed(1000);
  StepperE1.setSpeed(2 * 200);
  StepperE1.setEnablePin(E1_ENABLE_PIN);

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
  stepper = &StepperX0;

  Serial.setTimeout(2000); // 2 seconds
  if (Serial.available()) {
    steps = Serial.parseInt();
    if (steps != 0)
      move(steps, stepper);
  }

  stepper->runSpeedToPosition();
}

