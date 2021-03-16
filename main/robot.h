#pragma once
#include "motor.h"
#include <string>
class Robot
{
  public:
  std::string forwardState = "off";
  std::string backwardState = "off";
  std::string leftState = "off";
  std::string rightState = "off";
  std::string tuuterState = "off";

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

  void SetMotionState(Direction dir, bool motionState) {
    switch (dir)
    {
    case Forward:
      if (motionState == true) {
        forwardState = "on";
      } else {
        forwardState = "off";
      }
      break;
    case Backward:
      if (motionState == true) {
        backwardState = "on";
      } else {
        backwardState = "off";
      }
      break;
    case Left:
      if (motionState == true) {
        leftState = "on";
      } else {
        leftState = "off";
      }
      break;
    case Right:
      if (motionState == true) {
        rightState = "on";
      } else {
        rightState = "off";
      }
      break;
    default:
      break;
    }
  }
};

