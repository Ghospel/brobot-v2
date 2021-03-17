#pragma once
#include "motor.h"
#include <string>
#include "main.ino"
class Robot
{
  public:
  std::string forwardState = "off";
  std::string backwardState = "off";
  std::string leftState = "off";
  std::string rightState = "off";
  std::string tuuterState = "off";
  Motor _motor1;
  Motor _motor2;
  Motor _motor3;
  Motor _motor4;

  Robot(){};

  void SetTuuterState(bool tuuter){
    if(tuuter) {
      tuuterState = "on";
      Serial.println("tuut");
      for(int i=0;i<256;i+=32){
        dacWrite(25,i);
        delay(1500);            
      } 
    } else {
      tuuterState = "off";
      Serial.println("niet tuut");
      dacWrite(25,0);
    }
  }

  // Import motors to robot
  void SetMotors(Motor motor1, Motor motor2, Motor motor3, Motor motor4) {
    _motor1 = motor1;
    _motor2 = motor2;
    _motor3 = motor3;
    _motor4 = motor4;
  }
  
  void MoveForward() {
    _motor1.Direction(Forward);
    _motor2.Direction(Forward);
    _motor3.Direction(Forward);
    _motor4.Direction(Forward);
  }
  
  void MoveBackward() {
    _motor1.Direction(Backward);
    _motor2.Direction(Backward);
    _motor3.Direction(Backward);
    _motor4.Direction(Backward);
  }
  
  void MoveLeft() {
    _motor1.Direction(Backward);
    _motor2.Direction(Forward);
    _motor3.Direction(Backward);
    _motor4.Direction(Forward);
  }
  
  void MoveRight() {
    _motor1.Direction(Forward);
    _motor2.Direction(Backward);
    _motor3.Direction(Forward);
    _motor4.Direction(Backward);
  }

  void Stop() {
    _motor1.Stop();
    _motor2.Stop();
    _motor3.Stop();
    _motor4.Stop();
  }

  void TurnOffAllMotionStates() {
    forwardState = "off";
    backwardState = "off";
    leftState = "off";
    rightState = "off";
  }

  void SetMotionState(Direction dir, bool motionState) {
    switch (dir)
    {
    case Forward:
      if (motionState == true) {
        robot.TurnOffAllMotionStates();
        forwardState = "on";
      } else {
        forwardState = "off";
      }
      break;
    case Backward:
      if (motionState == true) {
        robot.TurnOffAllMotionStates();
        backwardState = "on";
      } else {
        backwardState = "off";
      }
      break;
    case Left:
      if (motionState == true) {
        robot.TurnOffAllMotionStates();
        leftState = "on";
      } else {
        leftState = "off";
      }
      break;
    case Right:
      if (motionState == true) {
        robot.TurnOffAllMotionStates();
        rightState = "on";
      } else {
        rightState = "off";
      }
      break;
    default:
        robot.TurnOffAllMotionStates();
      break;
    }
  }
};

