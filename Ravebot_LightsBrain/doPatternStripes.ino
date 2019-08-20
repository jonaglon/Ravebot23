

void doPatternStripes() {

  if (currentLightPattern == 7) {
    stripesPattern1();
  } else if (currentLightPattern == 8) {
    stripesPattern2();
  } 
}



void stripesPattern1() {

  SetRgbwWheelVars((timeyInTime/512)%256);

  int sixteenBeatPos = (sixteenBeats/4) % 4;
  int stripeBeatPos=0;
  int xyCord=0;
  
  if (sixteenBeatPos == 0) {
    stripeBeatPos = (timeyInTime / 32)%1024;
  } else if (sixteenBeatPos == 1) {
    stripeBeatPos = 2048-((timeyInTime / 32)%2048);
    xyCord=1;
  } else if (sixteenBeatPos == 2) {
    stripeBeatPos = 615-((timeyInTime / 32)%1024);
  } else if (sixteenBeatPos == 3) {
    stripeBeatPos = (timeyInTime / 32)%2048;
    xyCord=1;
  }
    
  for(int j = 0; j < numLeds; j++) {
    int yCoord = getCoord(j,xyCord);
    /* if (yCoord < stripeBeatPos)
      setLedDirect(j, 0, 0, 0, 0, false);
    else if (yCoord < stripeBeatPos+200)
      setLedDirect(j, wheelR, wheelG, wheelB, 0, false);
    else
      setLedDirect(j, 0, 0, 0, 0, false);  */
    if ((yCoord > stripeBeatPos) && (yCoord < stripeBeatPos+200)) {
      setLedDirect(j, wheelR, wheelG, wheelB, 0, false);
    }
  }
}

void stripesPattern2() {

  int rVal = 0;
  int gVal = 0;
  int bVal = 0;
  int wVal = 0;
  int fourBeatPos = (sixteenBeats/4) % 4;
  if (fourBeatPos == 0) {
    rVal = 255;
  } else if (fourBeatPos == 1) {
    gVal = 255;
  } else if (fourBeatPos == 2) {
    bVal = 255;
  } else {
    wVal = 255;
  } 

  int stripeBeatPos = ((timeyInTime / 32)%2048)-1024;
  for(int j = 0; j < numLeds; j++) {
    int yCoord = getCoord(j,0);
    if ((yCoord > stripeBeatPos) && (yCoord < stripeBeatPos+400))
      setLedDirect(j, rVal, gVal, bVal, wVal, false);
  }
}

void stripesPattern3() {

// int percentThroughPattern = (timeyInTime % 32768)/364;     // 0-90 hopefully 

  int stripeBeatPos = (timeyInTime / 32) % 2048;
  for(int j = 0; j < numLeds; j++) {
    int yCoord = getCoord(j,0);
    if ((yCoord > stripeBeatPos) && (yCoord < stripeBeatPos+400))
      setLedDirect(j, 148, 0, 211, 0, false);
    else if ((yCoord > stripeBeatPos+400) && (yCoord < stripeBeatPos+800))
      setLedDirect(j, 75, 0, 130, 0, false);
    else if ((yCoord > stripeBeatPos+800) && (yCoord < stripeBeatPos+1200))
      setLedDirect(j, 0, 0, 255, 0, false);
    else if ((yCoord > stripeBeatPos+1200) && (yCoord < stripeBeatPos+1600))
      setLedDirect(j, 0, 255, 0, 0, false);
    else if ((yCoord > stripeBeatPos+1600) && (yCoord < stripeBeatPos+2000))
      setLedDirect(j, 255, 255, 0, 0, false);
    else if ((yCoord > stripeBeatPos+2000) && (yCoord < stripeBeatPos+2400))
      setLedDirect(j, 255, 122, 0, 0, false);
    else if ((yCoord > stripeBeatPos+2400) && (yCoord < stripeBeatPos+2800))
      setLedDirect(j, 255, 0, 0, 0, false);

  }
}



