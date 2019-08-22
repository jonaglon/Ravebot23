
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

void circleSquiggle() {
  circleSquiggle(0, 0, 0, 0, 255);
  circleSquiggle(728, 0, 0, 0, 255);
  circleSquiggle(1456, 0, 0, 0, 255);
  circleSquiggle(2185, 0, 0, 0, 255);
  circleSquiggle(2913, 0, 0, 0, 255);
  circleSquiggle(3641, 0, 0, 0, 255);
  circleSquiggle(4369, 0, 0, 0, 255);
  circleSquiggle(5097, 0, 0, 0, 255);
  circleSquiggle(5825, 0, 0, 0, 255);
  circleSquiggle(6554, 0, 0, 0, 255);
  circleSquiggle(7282, 0, 0, 0, 255);
  circleSquiggle(8010, 0, 0, 0, 255);
  circleSquiggle(8738, 0, 0, 0, 255);
  circleSquiggle(9466, 0, 0, 0, 255);
  circleSquiggle(10194, 0, 0, 0, 255);
  circleSquiggle(10923, 0, 0, 0, 255);
  circleSquiggle(11651, 0, 0, 0, 255);
}

void circleSquiggle(int offset, int r, int g, int b, int w) {
  int placeInQueue = (timeyInTime % 262144) / 16384;
  int thisPattern = (timeyInTime % 2621440) / 262144;

  byte tube = squigglePattern[thisPattern][placeInQueue][0];
  byte startLed = squigglePattern[thisPattern][placeInQueue][1];
  int percentThroughPattern = percentThroughBeat/712;

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


