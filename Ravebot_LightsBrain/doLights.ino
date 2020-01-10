
void doLights() {

  allOff();

  eyeBackground();

  doMainLightPattern();

  doOverlayPattern();

  doCutUpPattern();

  doExtraPatterns();
  
  doFace();
  
  LEDS.show();
}


void doMainLightPattern() {
  if (currentLightPattern < 14) {
    doTwinkles();
  } else if (currentLightPattern < 15) {
    doPatternStripes(0);
  } else if (currentLightPattern < 16) {
    doPatternStripes(1);
  } else if (currentLightPattern < 17) {
    doPatternStripes(2);
  } else if (currentLightPattern < 18) {
    doPatternStripes(3);
  } else if (currentLightPattern < 19) {
    doRainbowPattern(0);
  } else if (currentLightPattern < 20) {
    doRainbowPattern(1);
  } else if (currentLightPattern < 21) {
    doRainbowPattern(2);
  } else if (currentLightPattern < 22) {
    doRainbowPattern(3);
  } else if (currentLightPattern < 23) {
    doPatternBlobs();
  } else if (currentLightPattern < 24) {
    doFullColours(0);
  } else if (currentLightPattern < 25) {
    doFullColours(1);
  }
}

void doOverlayPattern() {
  if (!overlayPatternActive)
    return;

  if (overlayPatternNumber == 0) {
    cutRandomSection();
  } else if (overlayPatternNumber == 1) {
    lightRandomSection();
  } else if (overlayPatternNumber == 2) {
    lightWholeRobotBriefly();
  } else if (overlayPatternNumber == 3) {
    doStripeOverlay(0);
  } else if (overlayPatternNumber == 4) {
    doStripeOverlay(1);
  } else if (overlayPatternNumber == 5) {
    doStripeOverlay(2);
  } else if (overlayPatternNumber == 6) {
    doStripeOverlay(3);
  } else if (overlayPatternNumber == 7) {
    doRainbowOverlay(256, 1024);
  } else if (overlayPatternNumber == 8) {
    doRainbowOverlay(512, 256);
  }
}

void doCutUpPattern() {
  if (!cutUpPatternActive)
    return;

  if (cutUpPatternNumber == 0) {    
    if (thisBeat16 < 4) {
      doRainbowPattern(3);
    } else if (thisBeat16 < 8) {
      doPatternStripes(3);
    } else if (thisBeat16 < 12) {
      doPatternBlobs();
    }
  } else if (cutUpPatternNumber == 1) {    
    if (thisBeat16 < 4) {
      doRainbowPattern(2);
    } else if (thisBeat16 < 8) {
      doPatternStripes(1);
    } else if (thisBeat16 < 12) {
      doFullColours(2);
    }
  } else if (cutUpPatternNumber == 2) {    
    if (thisBeat8 < 2) {
      doFullColours(2);
    } else if (thisBeat8 < 4) {
      doPatternStripes(2);
    } else if (thisBeat8 < 8) {
      doPatternBlobs();
    }
  }
}

void doExtraPatterns() {
  
  if (!extraPatternActive)
    return;

  if (extraPatternNumber == 0) {    
    tubesInTime();
  } else if (extraPatternNumber == 1) {    
    sectionsInTime();
  } else if (extraPatternNumber == 2) {    
    bodyCirclesInTime();
  } else if (extraPatternNumber == 3) {    
    heartInTime();
  } else if (extraPatternNumber == 4) {    
    turnOffTubes();
  } else if (extraPatternNumber == 5) {    
    circleSquiggleRainbow1();
  } else if (extraPatternNumber == 6) {    
    circleSquiggleWhiteEight();
  } else if (extraPatternNumber == 7) {  
    circleSquiggleGood();  
  } else if (extraPatternNumber == 8) {    
    bigSpeakerThreeRevolvers();
  } else if (extraPatternNumber == 9) {    
    bigSpeakerInTimeFourTings();
  }
}

void changeLightPattern() {
  // choose a new pattern, different from the current one
  uint8_t newPattern = currentLightPattern;
  while (newPattern == currentLightPattern) {
    newPattern = random(numPatterns);
  }
  currentLightPattern = newPattern;

  // if it's a twinkle call the setup code
  if (currentLightPattern < 14) {
    setupNewTwinklePattern(currentLightPattern);
  }

  short randomNo = random(2);
  if (randomNo == 0) {
    overlayPatternActive = true;
    overlayPatternNumber = random(9);
  } else {
    overlayPatternActive = false;
  }

  randomNo = random(5);
  if (randomNo == 0) {
    cutUpPatternActive = true;
    cutUpPatternNumber = random(3);
  } else {
    cutUpPatternActive = false;
  }  

  randomNo = random(2);
  if (randomNo == 0) {
    extraPatternActive = true;
    extraPatternNumber = random(10);
  } else {
    extraPatternActive = false;
  }  
  
}


