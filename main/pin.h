#pragma once
#include <string>

class Pin
{
  public:
    std::string state = "off";
    int _pinNumber;

    Pin(int pinNumber){
      _pinNumber = pinNumber;
    }

    Pin();
};
