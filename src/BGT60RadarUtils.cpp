/*
  BGT60RadarUtils.h - Library for .
  Created by Yunior Cabrera (yvcabrerago@gmail.com), October 31, 2023.
  Released into the public domain.
*/

#include "Arduino.h"
#include "BGT60RadarUtils.h"

void _noFun(){}

BGT60RadarUtils::BGT60RadarUtils(Bgt60Ino* radar) {
  _radar = radar;
  StatusFunctions[0][0] = &_noFun;
  StatusFunctions[0][1] = &_noFun;
  StatusFunctions[0][2] = &_noFun;
  StatusFunctions[1][0] = &_noFun;
  StatusFunctions[1][1] = &_noFun;
  StatusFunctions[1][2] = &_noFun;
  StatusFunctions[2][0] = &_noFun;
  StatusFunctions[2][1] = &_noFun;
  StatusFunctions[2][2] = &_noFun;
}

void BGT60RadarUtils::checkStatus() {
  Error_t result = _radar->getDirection(_curDirection);
  if (result == OK) {
    if (_stateChanged()) {
      switch (_prevDirection) {
        case Bgt60::NO_DIR:
          if (_curDirection == Bgt60::APPROACHING) {
            StatusFunctions[0][1]();
          } else {
            StatusFunctions[0][2]();
          }
          break;
        case Bgt60::APPROACHING:
          if (_curDirection == Bgt60::NO_DIR) {
            StatusFunctions[1][0]();
          }
          else {
            StatusFunctions[1][2]();
          }
          break;
        case Bgt60::DEPARTING:
          if (_curDirection == Bgt60::NO_DIR) {
            StatusFunctions[2][0]();
          }
          else {
            StatusFunctions[2][1]();
          }
          break;
      }
    }
    _prevDirection = _curDirection;
  }
}

Bgt60::Direction_t BGT60RadarUtils::getCurrentDirection() {
  return _curDirection;
}

Bgt60::Direction_t BGT60RadarUtils::getPreviousDirection() {
  return _prevDirection;
}