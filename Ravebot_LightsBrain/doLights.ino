int numPatterns = 11;

void doLights() {

  allOff();
  // allOffBySection();

  /*if (currentLightPattern < 7) {
    doTwinkles();
  } else if (currentLightPattern < 9) {
    doPatternStripes();   // TODO - there are more than two stripe patterns
  } else if (currentLightPattern == 9) {
    horizontalRainbow(false, false, 80);
  } else if (currentLightPattern == 10) {
    doPatternBlobs();
    //     doPatternTrains();
  } else  {
    horizontalRainbow(false, false, 20);
  }*/

  doPatternDonuts();

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
  if (newPattern < 7) {
    setupNewTwinklePattern(currentLightPattern);
  }
}


