

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



