int numPatterns = 11;

void doLights() {

  allOff();
  // allOffBySection();

  if (currentLightPattern < 7) {
    doTwinkles();
  } else if (currentLightPattern < 9) {
    doPatternStripes();
  } else if (currentLightPattern == 9) {
    horizontalRainbow(false, false, 80);
  } else if (currentLightPattern == 10) {
    doPatternBlobs();
    //     doPatternTrains();
  } else  {
    horizontalRainbow(false, false, 20);
  }

  // ***************************************************************************************
  // JR TODO - find a way of deciding which light extras should be happening at the moment.
  // * ************************ Write a load of exciting extras!  ***************************
  // knigtRiderAms();
  // circleInTime();
  // sectionsInTime();

  doFace();
  LEDS.show();
}

void changeLightPattern() {
  // choose a new pattern, different from the current one
  int newPattern = currentLightPattern;
  while (newPattern == currentLightPattern) {
    newPattern = random(numPatterns);
  }

  // JR TODO - this is the cheat setting the lights pattern ******************
  newPattern = 4;
  
  currentLightPattern = newPattern;

  // if it's a twinkle call the setup code
  if (newPattern < 7) {
    setupNewTwinklePattern(currentLightPattern);
  }

  
}


/* ******************************* EYES & MOUTH ********************************** */

// Eye types are used when the robot is in manual mode, in auto eye dances are used
int currentEyeType = 0;
void changeEyeType() {
  resetEyes();
  currentEyeType = (currentEyeType+1)%5;
}

void doFace() {
  eyeController();
  doTalkingLights();
}

void eyeController() {

  if (robotManualMode) {
    switch (currentEyeType) {
      case 0:
        doNormalEyes();
        break;
      case 1: doStonerEyes();
        break;
      case 2: heartEyes();
        break;
      case 3: pacManEyes();
        break;
      case 4: smileyEyes();
        break;
    }
  } else {
    switch (currentBar%8) {
      case 0:
      case 1:
        doNormalEyes();
        break;
      case 2:
      case 3:
        leftEyeX = (sixteenBeats * 10)-80;
        rightEyeX = (sixteenBeats * 10)-80;
        break;
      case 4: 
        eyePrimaryR = 255;
        eyePrimaryG = 0;
        eyePrimaryB = 0;
        heartEyes();
        break;
      case 5:
        eyePrimaryR = 0;
        eyePrimaryG = 255;
        eyePrimaryB = 0;
        doNormalEyes();
        break;
      case 6:
      case 7:
        pacManEyes();
        break;
    }
  }
  
}

void resetEyes() {
  eyePrimaryR = 110;
  eyePrimaryG = 150;
  eyePrimaryB = 150;
  eyeSecondaryR = 0;
  eyeSecondaryG = 0;
  eyeSecondaryB = 0;
  leftEyeX = 0;
  leftEyeY = 0;
  rightEyeX = 0;
  rightEyeY = 0;
}

int eyeRColours[9] = {255,  0,   0,  255, 255,   0, 110, 0, 255 };
int eyeGColours[9] = {0,  255,   0,  255,   0, 255, 150, 0,   6 };
int eyeBColours[9] = {0,    0, 255,    0, 255, 255, 150, 0,  80 };
int numEyeColors = 9;

int currentEyePrimaryPos = 3;
void changePrimaryEyeColour() {
  currentEyePrimaryPos = (currentEyePrimaryPos+1)%numEyeColors;
  eyePrimaryR = eyeRColours[currentEyePrimaryPos];
  eyePrimaryG = eyeGColours[currentEyePrimaryPos];
  eyePrimaryB = eyeBColours[currentEyePrimaryPos];
}

int currentEyeSecondaryPos = 4;
void changeSecondaryEyeColour() {
  currentEyeSecondaryPos = (currentEyeSecondaryPos+1)%numEyeColors;
  eyeSecondaryR = eyeRColours[currentEyeSecondaryPos];
  eyeSecondaryG = eyeGColours[currentEyeSecondaryPos];
  eyeSecondaryB = eyeBColours[currentEyeSecondaryPos];
}

void doNormalEyes() {

  for(int j = 0; j < 93; j++) {
    setSectionLed(5, j, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(6, j, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
  }

  // iris
  drawHexagon(ledSections[5], 55+leftEyeX, 55-leftEyeY, 26, 42, eyeSecondaryR, eyeSecondaryG, eyeSecondaryB, 0);
  drawHexagon(ledSections[6], 55+rightEyeX, 55-rightEyeY, 26, 42, eyeSecondaryR, eyeSecondaryG, eyeSecondaryB, 0);

  // pupil
  drawEyeSquare(ledSections[5], 55+leftEyeX, 55-leftEyeY, 7, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
  drawEyeSquare(ledSections[6], 55+rightEyeX, 55-rightEyeY, 7, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);

  doBlinking();
  doLeftWink();
  doRightWink();
}

void doStonerEyes() {

  for(int j = 0; j < 93; j++) {
    if (eyeCoords[j][1] < 56) {
      setSectionLed(5, j, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
      setSectionLed(6, j, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    } else {
      setSectionLed(5, j, eyeSecondaryR, eyeSecondaryG, eyeSecondaryB, 0);
      setSectionLed(6, j, eyeSecondaryR, eyeSecondaryG, eyeSecondaryB, 0);
    }
  }

  // dark eye squares
  drawHexagon(ledSections[5], 55+leftEyeX, 29-leftEyeY, 20, 35, eyeSecondaryR, eyeSecondaryG, eyeSecondaryB, 0);
  drawHexagon(ledSections[6], 55+rightEyeX, 29-rightEyeY, 20, 35, eyeSecondaryR, eyeSecondaryG, eyeSecondaryB, 0);

  // pupil
  drawEyeSquare(ledSections[5], 55+leftEyeX, 29-leftEyeY, 7, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
  drawEyeSquare(ledSections[6], 55+rightEyeX, 29-rightEyeY, 7, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);

  doLeftWink();
  doRightWink();
}

void heartEyes() {

  for(int j = 0; j < 93; j++) {
    setSectionLed(5, j, eyeSecondaryR, eyeSecondaryG, eyeSecondaryB, 0);
    setSectionLed(6, j, eyeSecondaryR, eyeSecondaryG, eyeSecondaryB, 0);
  }

  for(int j = 0; j < 56; j++) {
    setSectionLed(5, eyeHeartLeds[j], eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(6, eyeHeartLeds[j], eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
  }
}

void pacManEyes() {
  // 16384 is a beat length  1365 is an 12th-ish
  //int animationStep = percentThroughBeat / 1365;
  
  int animationStep1 = (timeyInTime / 2048)%8;
  int animationStep2 = (timeyInTime / 1024)%16;
  
  for(int j = 0; j < 93; j++) {
    if (pacManAnimationMask[(animationStep2)%16][j]) {
      setSectionLed(6, j, 120, 120, 0, 0);
    } else if (pacManAnimationMask2[(animationStep1+4)%8][j]) {
      setSectionLed(6, j, 0, 0, 0, 0);
    } else {
      setSectionLed(6, j, 255, 255, 255, 0);
    }
  }
  for(int j = 0; j < 93; j++) {
    if (pacManAnimationMask2[animationStep1][j]) {
      setSectionLed(5, j, 0, 0, 0, 0);
    } else {
      setSectionLed(5, j, 255, 255, 255, 0);
    }
  }
}

void smileyEyes() {
  for(int j = 0; j < 93; j++) {
    setSectionLed(5, j, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(6, j, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
  }
  for(int j = 0; j < 24; j++) {
    setSectionLed(5, eyeSmileyLeds[j], eyeSecondaryR, eyeSecondaryG, eyeSecondaryB, 0);
    setSectionLed(6, eyeSmileyLeds[j], eyeSecondaryR, eyeSecondaryG, eyeSecondaryB, 0);
  }
}

unsigned long blinkStart=4000;
const int blinkLength=240;
void doBlinking() {
  int drawTo = 0;
  //int drawTo2 = 0;
  int blinkHeight = 60;
  
  if (timey > (blinkStart + blinkLength)) {
    // blink over, reset
    if (random(9) == 0) {
      blinkStart = timey + random(400);
    } else {
      blinkStart = timey + random(4000,9000);
    }
  } else if (timey > blinkStart) {
    int percIntoBlink = ((timey - blinkStart)*100)/(blinkLength/2);
    if (timey > (blinkStart + (blinkLength/2))) {
      // on way up
      drawTo = ((blinkHeight * percIntoBlink)/100)-blinkHeight+50;
    } else {
      // on way down
      drawTo = blinkHeight+50-((blinkHeight * percIntoBlink)/100);
    }
    for(int j = 0; j < 93; j++) {
      if (eyeCoords[j][1] < 110 - drawTo) {
          setSectionLed(5, j, 0, 0, 0, 0);
      }
      if (eyeCoords[j][1] > drawTo) {
          setSectionLed(5, j, 0, 0, 0, 0);
      }
      if (eyeCoords[j][1] < 110 - drawTo) {
          setSectionLed(6, j, 0, 0, 0, 0);
      }
      if (eyeCoords[j][1] > drawTo) {
          setSectionLed(6, j, 0, 0, 0, 0);
      }
    }
  }
}

unsigned long lWinkStart=0;
unsigned long rWinkStart=0;
unsigned long lWinkEnd=0;
unsigned long rWinkEnd=0;
bool lWinking = false;
bool rWinking = false;
const int winkLength=350;

// Note, left and right winks are copied and pasted, change both the same.
void doLeftWink() {
  if (!lWinking)
    return;

  int drawTo = 0;  
  if (lWinkEnd!=0 && (timey > (lWinkEnd + (winkLength/2)))) {
    // blink over, reset
    lWinking = false;
    lWinkEnd=0;
    drawTo = 110;
  } else if (lWinkEnd==0 && timey < (lWinkStart + (winkLength/2))) {
    // on way down
    int percIntoBlink = ((timey - lWinkStart)*100)/(winkLength/2);
    drawTo = 110-((60 * percIntoBlink)/100);
  } else if (lWinkEnd!=0) {
    // on way up
    int percIntoBlink = ((timey - lWinkEnd)*100)/(winkLength/2);
    drawTo = 50+((60 * percIntoBlink)/100);
  } else {
    // in the middle
    for(int j = 0; j < 93; j++) {
      setSectionLed(6, j, 0, 0, 0, 0);
    }
    setSectionLed(6, 24, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(6, 50, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(6, 68, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(6, 81, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(6, 90, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(6, 92, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(6, 86, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(6, 75, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(6, 60, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(6, 38, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(6,  8, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    return;
  }
  for(int j = 0; j < 93; j++) {
    if (eyeCoords[j][1] < 110 - drawTo) {
        setSectionLed(6, j, 0, 0, 0, 0);
    }
    if (eyeCoords[j][1] > drawTo) {
        setSectionLed(6, j, 0, 0, 0, 0);
    }
  }
}

void doRightWink() {
  if (!rWinking)
    return;

  int drawTo = 0;  
  if (rWinkEnd!=0 && (timey > (rWinkEnd + (winkLength/2)))) {
    // blink over, reset
    rWinking = false;
    rWinkEnd=0;
    drawTo = 110;
  } else if (rWinkEnd==0 && timey < (rWinkStart + (winkLength/2))) {
    // on way down
    int percIntoBlink = ((timey - rWinkStart)*100)/(winkLength/2);
    drawTo = 110-((60 * percIntoBlink)/100);
  } else if (rWinkEnd!=0) {
    // on way up
    int percIntoBlink = ((timey - rWinkEnd)*100)/(winkLength/2);
    drawTo = 50+((60 * percIntoBlink)/100);
  } else {
    // in the middle
    for(int j = 0; j < 93; j++) {
      setSectionLed(5, j, 0, 0, 0, 0);
    }
    setSectionLed(5, 24, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(5, 50, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(5, 68, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(5, 81, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(5, 90, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(5, 92, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(5, 86, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(5, 75, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(5, 60, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(5, 38, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    setSectionLed(5,  8, eyePrimaryR, eyePrimaryG, eyePrimaryB, 0);
    return;
  }
  for(int j = 0; j < 93; j++) {
    if (eyeCoords[j][1] < 110 - drawTo) {
        setSectionLed(5, j, 0, 0, 0, 0);
    }
    if (eyeCoords[j][1] > drawTo) {
        setSectionLed(5, j, 0, 0, 0, 0);
    }
  }
}

void winkLeftMessage(int blinkOnOffMessage) {
  if (blinkOnOffMessage == 0) {
    // start new wink
    lWinkStart=timey;
    lWinking = true;
    lWinkEnd=0;
    // push forward the next blink
    blinkStart = timey + random(3000,8000);
  } else if (blinkOnOffMessage == 1) {
    // end wink
    lWinkEnd=timey;
  }
}

void winkRightMessage(int blinkOnOffMessage) {
  if (blinkOnOffMessage == 0) {
    // start new wink
    rWinkStart=timey;
    rWinking = true;
    rWinkEnd=0;
    // push forward the next blink
    blinkStart = timey + random(3000,8000);
  } else if (blinkOnOffMessage == 1) {
    // end wink
    rWinkEnd=timey;
  }
}


void doTalkingLights() {

  for(int j = 0; j < numLedsInSection(7); j++) {
    setSectionLed(7, j, 0, 0, 0, 0);
  }
  
  if (robotTalking) {
    setLedDirect(ledSections[7]+8, 255, 60, 60, 100, true);
    setLedDirect(ledSections[7]+9, 255, 60, 60, 100, true);
    
    if (timey > (robotTalkingOnTime + 40)) {
      setLedDirect(ledSections[7]+7, 255, 60, 60, 100, true);
      setLedDirect(ledSections[7]+10, 255, 60, 60, 100, true);
    }
    
    if (timey > (robotTalkingOnTime + 80)) {
      setLedDirect(ledSections[7]+6, 255, 60, 60, 100, true);
      setLedDirect(ledSections[7]+11, 255, 60, 60, 100, true);
    }
    
    if (timey > (robotTalkingOnTime + 110)) {
      setLedDirect(ledSections[7]+5, 255, 60, 60, 100, true);
      setLedDirect(ledSections[7]+12, 255, 60, 60, 100, true);
    }
    
    if (timey > (robotTalkingOnTime + 135)) {
      setLedDirect(ledSections[7]+4, 255, 60, 60, 100, true);
      setLedDirect(ledSections[7]+13, 255, 60, 60, 100, true);
    }
    
    if (timey > (robotTalkingOnTime + 150)) {
      setLedDirect(ledSections[7]+3, 255, 60, 60, 100, true);
      setLedDirect(ledSections[7]+14, 255, 60, 60, 100, true);
    }
  }  
}
