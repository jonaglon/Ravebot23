int numPatterns = 11;

void doLights() {

  allOff();

  /*if (currentLightPattern < 14) {
    doTwinkles();
  } else if (currentLightPattern < 16) {
    doPatternStripes();
  } else if (currentLightPattern < 20) {
    doRainbowPatterns();
  } else if (currentLightPattern == 10) {
    doPatternBlobs();
    //    doPatternTrains();
    //    doPatternDonuts();
  } else {
    horizontalRainbow(false, false, 20);
  }*/

  // doPatternStripes();
  // doRainbowPatterns();
  doTwinkles();

  // ***************************************************************************************
  // JR TODO - find a way of deciding which light extras should be happening at the moment.
  // * ************************ Write a load of exciting extras!  ***************************
  // knigtRiderArms();
  // sectionsInTime();
  // bodyCirclesInTime();
  // heartInTime();
  // circleSquiggleController(); - three patterns here, different ones better with different backgrounds.


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
  // newPattern = 2;
  
  currentLightPattern = newPattern;

  // if it's a twinkle call the setup code
  if (newPattern < 14) {
    setupNewTwinklePattern(currentLightPattern);
  }
}


