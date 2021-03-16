#pragma once

enum Direction {
  Forward,
  Backward,
  Left,
  Right
};

class Motor {
  public:
  const int freq = 30000;
  const int resolution = 8;

  int enablePin;
  int _pin1;
  int _pin2;
  int _pwmChannel;

  Motor(int enablePin, int pin1, int pin2, int pwmChannel){
    enablePin = enablePin;
    _pwmChannel = pwmChannel;
    _pin1 = pin1;
    _pin2 = pin2;
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(enablePin, OUTPUT);
    ledcAttachPin(enablePin, pwmChannel);
    SetPinState(pin1, false);
    SetPinState(pin2, false);
    ledcSetup(pwmChannel, freq, resolution);

  };

  Motor();

  void Stop(){
      SetPinState(_pin1, false);
      SetPinState(_pin2, false);
      ledcWrite(_pwmChannel, 0);
  };

  void Rotate(Direction direction, int speed = 255){
    switch (direction)
    {
    case Forward:
      Serial.print(_pin1);
      Serial.print(" ");
      Serial.print(_pin2);
      Serial.print(" ");
      Serial.print(_pwmChannel);

      SetPinState(_pin1, true);
      SetPinState(_pin2, false);
      ledcWrite(_pwmChannel, speed);
      break;
    case Backward:
      Serial.print(_pin1);
      Serial.print(" ");
      Serial.print(_pin2);
      Serial.print(" ");
      Serial.print(_pwmChannel);

      SetPinState(_pin1, false);
      SetPinState(_pin2, true);
      ledcWrite(_pwmChannel, speed);
    default:
      break;
    }
  }

  void SetSpeed(int speed) {
    if (speed < 200) {
      SetPinState(_pin1, false);
      SetPinState(_pin2, false);
      ledcWrite(_pwmChannel, 0);
    } else if (speed >= 200 && speed <= 227) {
      ledcWrite(_pwmChannel, 227);
    } else if (speed >= 228 && speed <= 255) {
      ledcWrite(_pwmChannel, 255);
    } else {
      SetPinState(_pin1, false);
      SetPinState(_pin2, false);
      ledcWrite(_pwmChannel, 0);
    }
  }

  void SetPinState(int pin, bool pinStatus) {
    if(pinStatus){
      Serial.println("GAAN MET DIE BANAAN");
      digitalWrite(pin, HIGH);
    } else {
      Serial.println("wrm wrm ????????MET DIE BANAAN");
      digitalWrite(pin, LOW);
    }
  }
};