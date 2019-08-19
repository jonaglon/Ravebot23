const int knigtRiderLightTimes[24] = {80, 112, 140, 182, 216, 256, 304, 370, 440, 526, 660, 810,
                                      810, 660, 526, 440, 370, 304, 256, 216, 182, 140, 112, 80};
void knigtRiderAms() {
  int pixNum = 0;
  int currTime = 0;
  for (pixNum = 0; pixNum < 24; pixNum++) {
    currTime = currTime + (knigtRiderLightTimes[pixNum] * 2);
    if (currTime > percentThroughBeat) {
      break;
    }
  }

  if ((sixteenBeats % 2) == 0) {
    pixNum = 24-pixNum;
  }
  
  for (int pixSum = -5; pixSum < 6; pixSum++) {
    if (pixNum+pixSum < 0)
      pixSum = 0;
    if (pixNum+pixSum > 24)
      pixSum = 24;

    int brightness = 255-(quickAbsolute(pixSum)*50);
    setSectionLed(3,  pixNum+pixSum, brightness, 0, 0, brightness);
    setSectionLed(4,  pixNum+pixSum, brightness, 0, 0, brightness);
    setSectionLed(11, pixNum+pixSum, brightness, 0, 0, brightness);
    setSectionLed(12, pixNum+pixSum, brightness, 0, 0, brightness);
  }
}

/////////////////////
// Generic patters //
/////////////////////

void circleInTime() {
  int numToLight = percentThroughBeat / 182;

  for(int j = 0; j < 90; j++) {
    setSectionLed(14, j, 0, 0, 0, 0);
  }
  
  for(int j = 0; j < numToLight; j++) {
    setSectionLed(14, j, 0, 0, 255, 0);
  }
  
}

void heartInTime() {
  // we want a heartbeat
  int ledValue1 = currentHeartBeatValue(0, 255, 4);
  int ledValue2 = currentHeartBeatValue(7, 170, 2);

  if (ledValue1 > ledValue2)
    setSection(1, ledValue1, 0, 0, 0);
  else
    setSection(1, ledValue2, 0, 0, 0);
}

// the shorter dropoff divisor the longer the trail
int currentHeartBeatValue(int sixteenBeatShift, int maxValue, int dropoffLengthDivisor) {
  int sixteenBeatVal = (sixteenBeats + sixteenBeatShift) % 8;
  int returnVal = 0;
  
  if (sixteenBeatVal < 1) {
    returnVal = (((percentThroughBeat * 100) / 8192)*255)/100;
  } else if (sixteenBeatVal < 5) {
    returnVal = 255-(((((((sixteenBeatVal-1)*8192)+percentThroughBeat)*100)/(65536/dropoffLengthDivisor))*255)/100);
  }
  return returnVal;
}



void horizontalRainbow(bool includeEyes, bool includeMouth, int speedFactor) {
  int ticko = (timey / speedFactor) % 1024;
  
  for(int j = 0; j < numLeds; j++) {
    int xCoord = (getCoord(j,0)+ticko)%1024;
    SetRgbwWheelVars(xCoord/4);
    setLedDirect(j, wheelR, wheelG, wheelB, 0, false);    
  }
}


void sectionsInTime() {
  int beat4 = sixteenBeats % 4;  
  if (beat4 == 0) {
    setSection(13, 255, 0, 0, 0);
    setSection(14, 0, 255, 0, 0);
    setSection(15, 0, 0, 255, 0);
    setSection(16, 0, 0, 0, 255);
  } else if (beat4 == 1) {
    setSection(14, 255, 0, 0, 0);
    setSection(15, 0, 255, 0, 0);
    setSection(16, 0, 0, 255, 0);
    setSection(13, 0, 0, 0, 255);
  } else if (beat4 == 2) {
    setSection(15, 255, 0, 0, 0);
    setSection(16, 0, 255, 0, 0);
    setSection(13, 0, 0, 255, 0);
    setSection(14, 0, 0, 0, 255);
  } else if (beat4 == 3) {
    setSection(16, 255, 0, 0, 0);
    setSection(13, 0, 255, 0, 0);
    setSection(14, 0, 0, 255, 0);
    setSection(15, 0, 0, 0, 255);
  };
}


