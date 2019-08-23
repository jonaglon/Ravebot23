
///////////////////// Knight Rider Armies //////////////////
const int knigtRiderLightTimes[24] = {80, 112, 140, 182, 216, 256, 304, 370, 440, 526, 660, 810,
                                      810, 660, 526, 440, 370, 304, 256, 216, 182, 140, 112, 80};
void knigtRiderArms() {
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

///////////////// Circles in time //////////////////////////////
void bodyCirclesInTime() {

  int percentThroughPattern = (timeyInTime % 32768)/364;     // 0-90 over 2 bars

  int beat4 = sixteenBeats % 4;  
  if (beat4 == 0) {
    setSectionLed(13, (percentThroughPattern + 32) % 90, 0, 0, 0, 255);
    setSectionLed(13, (percentThroughPattern + 33) % 90, 0, 0, 0, 255);
    setSectionLed(13, (percentThroughPattern + 34) % 90, 0, 0, 0, 255);
    setSectionLed(14, (percentThroughPattern + 54) % 90, 100, 50, 90, 0);
    setSectionLed(14, (percentThroughPattern + 55) % 90, 100, 50, 90, 0);
    setSectionLed(14, (percentThroughPattern + 56) % 90, 100, 50, 90, 0);
    setSectionLed(15, (percentThroughPattern + 76) % 90, 0, 130, 130, 0);
    setSectionLed(15, (percentThroughPattern + 77) % 90, 0, 130, 130, 0);
    setSectionLed(15, (percentThroughPattern + 78) % 90, 0, 130, 130, 0);
    setSectionLed(16, (percentThroughPattern + 9) % 90, 130, 0, 130, 0);
    setSectionLed(16, (percentThroughPattern + 10) % 90, 130, 0, 130, 0);
    setSectionLed(16, (percentThroughPattern + 11) % 90, 130, 0, 130, 0);
  } else if (beat4 == 1) {
    setSectionLed(13, (percentThroughPattern + 32) % 90, 130, 0, 130, 0);
    setSectionLed(13, (percentThroughPattern + 33) % 90, 130, 0, 130, 0);
    setSectionLed(13, (percentThroughPattern + 34) % 90, 130, 0, 130, 0);
    setSectionLed(14, (percentThroughPattern + 54) % 90, 0, 0, 0, 255);
    setSectionLed(14, (percentThroughPattern + 55) % 90, 0, 0, 0, 255);
    setSectionLed(14, (percentThroughPattern + 56) % 90, 0, 0, 0, 255);
    setSectionLed(15, (percentThroughPattern + 76) % 90, 100, 50, 90, 0);
    setSectionLed(15, (percentThroughPattern + 77) % 90, 100, 50, 90, 0);
    setSectionLed(15, (percentThroughPattern + 78) % 90, 100, 50, 90, 0);
    setSectionLed(16, (percentThroughPattern + 9) % 90, 0, 130, 130, 0);
    setSectionLed(16, (percentThroughPattern + 10) % 90, 0, 130, 130, 0);
    setSectionLed(16, (percentThroughPattern + 11) % 90, 0, 130, 130, 0);
  } else if (beat4 == 2) {
    setSectionLed(13, (percentThroughPattern + 32) % 90, 0, 130, 130, 0);
    setSectionLed(13, (percentThroughPattern + 33) % 90, 0, 130, 130, 0);
    setSectionLed(13, (percentThroughPattern + 34) % 90, 0, 130, 130, 0);
    setSectionLed(14, (percentThroughPattern + 54) % 90, 130, 0, 130, 0);
    setSectionLed(14, (percentThroughPattern + 55) % 90, 130, 0, 130, 0);
    setSectionLed(14, (percentThroughPattern + 56) % 90, 130, 0, 130, 0);
    setSectionLed(15, (percentThroughPattern + 76) % 90, 0, 0, 0, 255);
    setSectionLed(15, (percentThroughPattern + 77) % 90, 0, 0, 0, 255);
    setSectionLed(15, (percentThroughPattern + 78) % 90, 0, 0, 0, 255);
    setSectionLed(16, (percentThroughPattern + 9) % 90, 100, 50, 90, 0);
    setSectionLed(16, (percentThroughPattern + 10) % 90, 100, 50, 90, 0);
    setSectionLed(16, (percentThroughPattern + 11) % 90, 100, 50, 90, 0);
  } else if (beat4 == 3) {
    setSectionLed(13, (percentThroughPattern + 32) % 90, 100, 50, 90, 0);
    setSectionLed(13, (percentThroughPattern + 33) % 90, 100, 50, 90, 0);
    setSectionLed(13, (percentThroughPattern + 34) % 90, 100, 50, 90, 0);
    setSectionLed(14, (percentThroughPattern + 54) % 90, 0, 130, 130, 0);
    setSectionLed(14, (percentThroughPattern + 55) % 90, 0, 130, 130, 0);
    setSectionLed(14, (percentThroughPattern + 56) % 90, 0, 130, 130, 0);
    setSectionLed(15, (percentThroughPattern + 76) % 90, 130, 0, 130, 0);
    setSectionLed(15, (percentThroughPattern + 77) % 90, 130, 0, 130, 0);
    setSectionLed(15, (percentThroughPattern + 78) % 90, 130, 0, 130, 0);
    setSectionLed(16, (percentThroughPattern + 9) % 90, 0, 0, 0, 255);
    setSectionLed(16, (percentThroughPattern + 10) % 90, 0, 0, 0, 255);
    setSectionLed(16, (percentThroughPattern + 11) % 90, 0, 0, 0, 255);
  }
}

////////////////////////// Circle Squiggles //////////////////////////
byte squigglePattern[10][17][2] {
    //   0         1         2         3        4        5          6         7         8         9        10       11        12        13        14       15     
    {{15, 22}, {15, 44}, {15, 66}, {15,  0}, {15, 22}, {14, 67}, {14, 44}, {14, 22}, {13, 67}, {16, 22}, {16,  0}, {16, 66}, {16, 44}, {16, 22}, {16,  0}, {16, 66}, {15, 22}},
    {{15, 22}, {15, 44}, {15, 66}, {15,  0}, {15, 22}, {15, 44}, {15, 66}, {15,  0}, {15, 22}, {14, 67}, {14, 44}, {14, 22}, {13, 67}, {16, 22}, {16,  0}, {16, 66}, {15, 22}},
    {{15, 22}, {15, 44}, {15, 66}, {15,  0}, {15, 22}, {14, 67}, {14, 44}, {14, 22}, {13, 67}, {13,  0}, {13, 22}, {13, 44}, {13, 67}, {16, 22}, {16,  0}, {16, 66}, {15, 22}},
    {{15, 22}, {14, 67}, {14, 44}, {14, 22}, {13, 67}, {13,  0}, {13, 22}, {13, 44}, {13, 67}, {16, 22}, {16,  0}, {16, 66}, {16, 44}, {16, 22}, {16,  0}, {16, 66}, {15, 22}},
    {{15, 22}, {14, 67}, {14, 44}, {14, 22}, {13, 67}, {13,  0}, {13, 22}, {13, 44}, {13, 67}, {13,  0}, {13, 22}, {13, 44}, {13, 67}, {16, 22}, {16,  0}, {16, 66}, {15, 22}},
    {{15, 22}, {14, 67}, {14, 44}, {14, 22}, {14,  0}, {14, 67}, {14, 44}, {14, 22}, {13, 67}, {16, 22}, {16,  0}, {16, 66}, {16, 44}, {16, 22}, {16,  0}, {16, 66}, {15, 22}},
    {{15, 22}, {14, 67}, {14, 44}, {14, 22}, {14,  0}, {14, 67}, {14, 44}, {14, 22}, {13, 67}, {13,  0}, {13, 22}, {13, 44}, {13, 67}, {16, 22}, {16,  0}, {16, 66}, {15, 22}},
    {{15, 22}, {14, 67}, {14, 44}, {14, 22}, {13, 67}, {16, 22}, {16,  0}, {16, 66}, {16, 44}, {16, 22}, {16,  0}, {16, 66}, {16, 44}, {16, 22}, {16,  0}, {16, 66}, {15, 22}},
    {{15, 22}, {14, 67}, {14, 44}, {14, 22}, {14,  0}, {14, 67}, {14, 44}, {14, 22}, {14,  0}, {14, 67}, {14, 44}, {14, 22}, {13, 67}, {16, 22}, {16,  0}, {16, 66}, {15, 22}},
    {{15, 22}, {14, 67}, {14, 44}, {14, 22}, {14,  0}, {14, 67}, {14, 44}, {14, 22}, {13, 67}, {13,  0}, {13, 22}, {13, 44}, {13, 67}, {16, 22}, {16,  0}, {16, 66}, {15, 22}}
};

// bool moveForwards = true;
int squiggleLedDistance[17] {0, 728, 1456, 2185, 2913, 3641, 4369, 5097, 5825, 6554, 7282, 8010, 8738, 9466, 10194, 10923, 11651};

void circleSquiggleController() {
  circleSquiggleGood();
}

void circleSquiggleRainbow1() {
  for (int arrayNum=0; arrayNum < 11; arrayNum++) {
    circleSquiggle(squiggleLedDistance[arrayNum]+98304, 80, 0, 200, 0);
  }
  for (int arrayNum=0; arrayNum < 11; arrayNum++) {
    circleSquiggle(squiggleLedDistance[arrayNum]+81920, 35, 0, 65, 0);
  }
  for (int arrayNum=0; arrayNum < 11; arrayNum++) {
    circleSquiggle(squiggleLedDistance[arrayNum]+65536, 0, 0, 255, 0);
  }
  for (int arrayNum=0; arrayNum < 9; arrayNum++) {
    circleSquiggle(squiggleLedDistance[arrayNum]+49152, 0, 255, 0, 0);
  }
  for (int arrayNum=0; arrayNum < 9; arrayNum++) {
    circleSquiggle(squiggleLedDistance[arrayNum]+32768, 255, 255, 0, 0);
  }
  for (int arrayNum=0; arrayNum < 9; arrayNum++) {
    circleSquiggle(squiggleLedDistance[arrayNum]+16384, 255, 65, 0, 0);
  }
  for (int arrayNum=0; arrayNum < 9; arrayNum++) {
    circleSquiggle(squiggleLedDistance[arrayNum], 255, 0, 0, 0);
  }
}

void circleSquiggleWhiteEight() {
  for (int arrayNum=0; arrayNum < 10; arrayNum++) {
    circleSquiggle(squiggleLedDistance[arrayNum]+114688, 0, 0, 0, 255);
  }
  for (int arrayNum=0; arrayNum < 10; arrayNum++) {
    circleSquiggle(squiggleLedDistance[arrayNum]+98304, 0, 0, 0, 255);
  }
  for (int arrayNum=0; arrayNum < 10; arrayNum++) {
    circleSquiggle(squiggleLedDistance[arrayNum]+81920, 0, 0, 0, 255);
  }
  for (int arrayNum=0; arrayNum < 10; arrayNum++) {
    circleSquiggle(squiggleLedDistance[arrayNum]+65536, 0, 0, 0, 255);
  }
  for (int arrayNum=0; arrayNum < 10; arrayNum++) {
    circleSquiggle(squiggleLedDistance[arrayNum]+49152, 0, 0, 0, 255);
  }
  for (int arrayNum=0; arrayNum < 10; arrayNum++) {
    circleSquiggle(squiggleLedDistance[arrayNum]+32768, 0, 0, 0, 255);
  }
  for (int arrayNum=0; arrayNum < 10; arrayNum++) {
    circleSquiggle(squiggleLedDistance[arrayNum]+16384, 0, 0, 0, 255);
  }
  for (int arrayNum=0; arrayNum < 10; arrayNum++) {
    circleSquiggle(squiggleLedDistance[arrayNum], 0, 0, 0, 255);
  }
}

void circleSquiggleGood() {
  for (int arrayNum=0; arrayNum < 12; arrayNum++) {
    circleSquiggle(squiggleLedDistance[arrayNum]+180224, 50, 0, 240, 0);
  }
  for (int arrayNum=0; arrayNum < 12; arrayNum++) {
    circleSquiggle(squiggleLedDistance[arrayNum]+163840, 0, 100, 150, 0);
  }
  for (int arrayNum=0; arrayNum < 12; arrayNum++) {
    circleSquiggle(squiggleLedDistance[arrayNum]+147456, 150, 0, 100, 0);
  }
  for (int arrayNum=0; arrayNum < 12; arrayNum++) {
    circleSquiggle(squiggleLedDistance[arrayNum]+131072, 80, 40, 110, 0);
  }
  
  for (int arrayNum=0; arrayNum < 12; arrayNum++) {
    circleSquiggle(squiggleLedDistance[arrayNum]+114688, 50, 0, 240, 0);
  }
  for (int arrayNum=0; arrayNum < 12; arrayNum++) {
    circleSquiggle(squiggleLedDistance[arrayNum]+98304, 0, 100, 150, 0);
  }
  for (int arrayNum=0; arrayNum < 12; arrayNum++) {
    circleSquiggle(squiggleLedDistance[arrayNum]+81920, 150, 0, 100, 0);
  }
  for (int arrayNum=0; arrayNum < 12; arrayNum++) {
    circleSquiggle(squiggleLedDistance[arrayNum]+65536, 80, 40, 110, 0);
  }

  for (int arrayNum=0; arrayNum < 12; arrayNum++) {
    circleSquiggle(squiggleLedDistance[arrayNum]+49152, 50, 0, 240, 0);
  }
  for (int arrayNum=0; arrayNum < 12; arrayNum++) {
    circleSquiggle(squiggleLedDistance[arrayNum]+32768, 0, 100, 150, 0);
  }
  for (int arrayNum=0; arrayNum < 12; arrayNum++) {
    circleSquiggle(squiggleLedDistance[arrayNum]+16384, 150, 0, 100, 0);
  }
  for (int arrayNum=0; arrayNum < 12; arrayNum++) {
    circleSquiggle(squiggleLedDistance[arrayNum], 80, 40, 110, 0);
  }
}

void circleSquiggle(int offset, int r, int g, int b, int w) {
  int placeInQueue = ((timeyInTime+offset) % 262144) / 16384;
  int thisPattern = ((timeyInTime+offset) % 2621440) / 262144;

  byte tube = squigglePattern[thisPattern][placeInQueue][0];
  byte startLed = squigglePattern[thisPattern][placeInQueue][1];
  int percentThroughPattern = ((percentThroughBeat+offset)%16384)/712;

  // if (((tube == 0 || tube == 3) && moveForwards) || ((tube == 1 || tube == 2) && !moveForwards)) {

  if (tube == 13 || tube == 15) {
    setSectionLed(tube, startLed + percentThroughPattern, r, g, b, w);
  } else {
    setSectionLed(tube, startLed + (23 - percentThroughPattern), r, g, b, w);
  }
}


///////////////////// Big Circle //////////////////
void circleInTime() {
  int numToLight = percentThroughBeat / 182;

  for(int j = 0; j < 90; j++) {
    setSectionLed(14, j, 0, 0, 0, 0);
  }
  for(int j = 0; j < numToLight; j++) {
    setSectionLed(14, j, 0, 0, 255, 0);
  }
  
}

//////////////////////////// Me Hearties /////////////////

void heartInTime() {
  int percentThroughPattern = ((timeyInTime+24576) % 32768);
  if (percentThroughPattern > 0 && percentThroughPattern < 6000) {
    setSection(1, 255 - (percentThroughPattern/23), 0, 0, 0);
    setSection(2, 255 - (percentThroughPattern/23), 0, 0, 0);
  } else if (percentThroughPattern > 8192 && percentThroughPattern < 14192) {
    setSection(1, 255 - (percentThroughPattern/23), 0, 0, 0);
    setSection(2, 255 - (percentThroughPattern/23), 0, 0, 0);
  } 
}


//////////////// Sections in time, BORING //////////////////
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


