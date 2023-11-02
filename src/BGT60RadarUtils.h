/*
  BGT60RadarUtils.h - Library for .
  Created by Yunior Cabrera (yvcabrerago@gmail.com), October 31, 2023.
  Released into the public domain.
*/

#ifndef BGT60RadarUtils_h
#define BGT60RadarUtils_h

#include "Arduino.h"
#include <bgt60-ino.hpp>
#include <bgt60-platf-ino.hpp>

typedef void (*FunctionPtr)();

class BGT60RadarUtils {
  public:
    BGT60RadarUtils(Bgt60Ino* radar);
    void checkStatus();
    Bgt60::Direction_t getCurrentDirection();
    Bgt60::Direction_t getPreviousDirection();
    FunctionPtr StatusFunctions[3][3];

  private:
    Bgt60Ino* _radar;
    Bgt60::Direction_t _curDirection   = Bgt60::NO_DIR;
    Bgt60::Direction_t _prevDirection  = Bgt60::NO_DIR;
    bool _stateChanged() {
      return _prevDirection != _curDirection;
    }
};

#endif