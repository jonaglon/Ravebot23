void doRainbowOverlay(uint16_t width, uint16_t speedDivisor) {
  int32_t stripeTop = (timeyInTime/1024) % 2048;
  for(uint16_t j = 0; j < numLeds; j++) {
    int32_t xCoord = getCoord(j,0)+1024;
    if ((xCoord > stripeTop) && (xCoord < stripeTop+300)) {
      SetRgbwWheelVars(xCoord+stripeTop);
      setLedDirect(j, wheelR, wheelG, wheelB, 0, false);    
    }
  }
}

void doRainbowPattern(uint8_t rainbowPattern) {
  if (rainbowPattern == 0) {
    horizontalRainbow();
  } else if (rainbowPattern == 1) {
    horizontalRainbowJoin();
  } else if (rainbowPattern == 2) {
    allOverRainbow1();
  } else if (rainbowPattern == 3) {
    allOverRainbow2();
  }  
}

void horizontalRainbow() {
  for(uint16_t j = 0; j < numLeds; j++) {
    int32_t xCoord = 614+getCoord(j,0)+getCoord(j,1);
    SetRgbwWheelVars((xCoord+(timeyInTime/512))%256);
    setLedDirect(j, wheelR, wheelG, wheelB, 0, false);    
  }
}

void horizontalRainbowJoin() {
  for(uint16_t j = 0; j < numLeds; j++) {
    int32_t xCoord = getCoord(j,0);
    if (xCoord < 307) {
      xCoord = 600-xCoord;
      SetRgbwWheelVars((xCoord+(timeyInTime/512))%256);
      setLedDirect(j, wheelR, wheelG, wheelB, 0, false);    
    } else {
      SetRgbwWheelVars((xCoord+(timeyInTime/512))%256);
      setLedDirect(j, wheelR, wheelG, wheelB, 0, false);    
    }
  }
}

void allOverRainbow1() {
  for(uint16_t j = 0; j < numLeds; j++) {
    int32_t xCoord = 614-getCoord(j,0);
    int32_t yCoord = getCoord(j,1);
    SetRgbwWheelVars((xCoord+yCoord+(timeyInTime/256))%256);
    setLedDirect(j, wheelR, wheelG, wheelB, 0, false);    
  }
}

void allOverRainbow2() {
  for(uint16_t j = 0; j < numLeds; j++) {
    SetRgbwWheelVars((j*3)+(timeyInTime/512));
    setLedDirect(j, wheelR, wheelG, wheelB, 0, false);    
  }
}

