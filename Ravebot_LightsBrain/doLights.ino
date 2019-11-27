
void doLights() {

  allOff();

  /*
  if (currentLightPattern < 14) {
    doTwinkles();
  } else if (currentLightPattern < 16) {
    doPatternStripes();
  } else if (currentLightPattern < 20) {
    doRainbowPatterns();
  } else if (currentLightPattern < 21) {
    doPatternBlobs();
  } else if (currentLightPattern < 22) {
    doPatternTrains();
  } else if (currentLightPattern < 23) {
    doPatternDonuts();
  }
  */
 
  allOverRainbow1(); // - is AMaZing!
  // doTwinkles();
  //doPatternStripes();

  // ***************************************************************************************
  // Bigger TODO listy:
  // Stipes as wipes
  // Automatic Eye Patterns (described below)
  // Ligths extras as (described below)
  // LUT so you can do stripes in knight rider fashion
  // Get some of the new eye stuff you've done and bring it here.
  // 
  // 
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

  // Eye patterns need to kick in if manual eyes have not been touched in the last 20 seconds
  // Eye patterns need
  //    To change when the tune changes? Just every 64 bars?
  //    To be able to co-ordinate with dances? Would be good.

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
  newPattern = 15;
  
  currentLightPattern = newPattern;

  // if it's a twinkle call the setup code
  if (newPattern < 14) {
    setupNewTwinklePattern(currentLightPattern);
  }
}


