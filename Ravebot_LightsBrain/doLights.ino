
void doLights() {

  allOff();

  /*
  if (currentLightPattern < 14) {
    doTwinkles();
  } else if (currentLightPattern < 16) {
    doPatternStripes();
  } else if (currentLightPattern < 20) {
    doRainbowPatterns();
  } else if (currentLightPattern == 10000) {
    //    doPatternBlobs();
    //    doPatternTrains();
    //    doPatternDonuts();
  }    */
  // allOverRainbow1(); - is AMaZing!
  //doTwinkles();
  doPatternStripes();

  // ***************************************************************************************
  // JR TODO - find a way of deciding which light extras should be happening at the moment.
  // Some should be for the whole duration of the song, say 1 in 10 that turnOffTubes, and randomly one of the 3 circleSquiggle for the whole tune
  // Some should be every x bars do knightRiderArms for x bars for the duration of the tune
  // * ************************ Write a load of exciting extras!  ***************************
  // knigtRiderArms();
  // sectionsInTime();
  // bodyCirclesInTime();
  // heartInTime();
  // turnOffTubes();
  // circleSquiggleController(); // three patterns here, different ones better with different backgrounds.


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
  newPattern = 14;
  
  currentLightPattern = newPattern;

  // if it's a twinkle call the setup code
  if (newPattern < 14) {
    setupNewTwinklePattern(currentLightPattern);
  }
}


