
void doLights() {

  allOff();

  /*
  doMainLightPattern();

  doOverlayPattern();

  doCutUpPattern();

  doExtraPatterns(); */
  doPatternStripes(3);

  doFace();
  
  LEDS.show();
}


void doMainLightPattern() {
  if (currentLightPattern < 14) {
    doTwinkles();
  } else if (currentLightPattern < 15) {
    doPatternStripes(1);
  } else if (currentLightPattern < 16) {
    doPatternStripes(2);
  } else if (currentLightPattern < 17) {
    doPatternStripes(3);
  } else if (currentLightPattern < 18) {
    doPatternStripes(4);
  } else if (currentLightPattern < 19) {
    doRainbowPattern(1);
  } else if (currentLightPattern < 20) {
    doRainbowPattern(2);
  } else if (currentLightPattern < 21) {
    doRainbowPattern(3);
  } else if (currentLightPattern < 22) {
    doRainbowPattern(4);
  } else if (currentLightPattern < 23) {
    doPatternBlobs();
  } else if (currentLightPattern < 24) {
    drawRGBHexagons(); // TODO this isn't what it looks like!
  } else if (currentLightPattern < 25) {
    drawRGBHexagons();
  }
}

void doOverlayPattern() {
  if (!overlayPatternActive)
    return;

  // TODO! Overlays can be either a second pattern OR a black out pattern

  if (overlayPatternNumber == 0) {
    cutRandomSection();
  } else if (overlayPatternNumber == 1) {
    lightRandomSection();
  } else if (overlayPatternNumber == 2) {
    lightWholeRobotBriefly();
  } else if (overlayPatternNumber == 3) {
    drawHexagonOverlay();
  } else if (overlayPatternNumber == 4) {
    doRainbowOverlay1();
  }
}

void doCutUpPattern() {
  // As above, if active then replace patterns with, different pattern, full colour, darkness for some / all of   
}

void doExtraPatterns() {

  // * ************************ Write more exciting extras!  ***************************
  // knigtRiderArms();
  // sectionsInTime();
  // bodyCirclesInTime();
  // heartInTime();
  // turnOffTubes();
  // circleSquiggleController(); // three patterns here, different ones better with different backgrounds.
  bigSpeakerThreeRevolvers();
  //bigSpeakerInTimeFourTings();
  //tubesInTime();
  // TODO - BeatFlash()

}

void changeLightPattern() {
  // choose a new pattern, different from the current one
  uint8_t newPattern = currentLightPattern;
  while (newPattern == currentLightPattern) {
    newPattern = random(numPatterns);
  }
  currentLightPattern = newPattern;
  // JR TODO - CHEAT ********************************************************  CHEAT * * 
  // currentLightPattern = 14;

  // if it's a twinkle call the setup code
  if (newPattern < 14) {
    setupNewTwinklePattern(currentLightPattern);
  }

  /* ************************************************ */
  short randomNo = random(2);
  if (randomNo == 0) {
    overlayPatternActive = true;
    overlayPatternNumber = random(5); /* numOverlays */
  } else {
    overlayPatternActive = false;
  }
  // TODO test CODE *******************************************************
  //  overlayPatternActive = true;
  // overlayPatternNumber = 4; 

  /* ************************************************ */
  
}


