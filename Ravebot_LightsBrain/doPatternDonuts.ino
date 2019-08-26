

void doPatternDonuts() {
  //drawWhiteHexagons();

  coOdrinTits();
}

void coOdrinTits() {
  for (int j = 0; j < numLeds; j++) { 
    int xCoord = getCoord(j,0);
    int yCoord = getCoord(j,1);

    if (xCoord < 490) {
      setLedDirect(j, 0, 0, 255, 0, false);
    }

  }  
}

void drawRGBHexagons() {
  int yStripeBeatPos = (timeyInTime % 65536)/60; // 0-958
  drawHexagon(yStripeBeatPos+500, 0, 255, 0, 0);
  drawHexagon(yStripeBeatPos, 255, 0, 0, 0);
  drawHexagon(yStripeBeatPos-500, 0, 0, 255, 0);
}

void drawWhiteHexagons() {
  int yStripeBeatPos = (timeyInTime % 32768)/32;
  drawHexagon(yStripeBeatPos+50, 0, 0, 0, 255);
  drawHexagon(yStripeBeatPos, 0, 0, 0, 255);
  drawHexagon(yStripeBeatPos-50, 0, 0, 0, 0);
}

void drawHexagon(int squareRadius, int r, int g, int b, int w) {
  int xCoord = 307;
  int yCoord = 758;
  int diamondRadius=(squareRadius*4)/3;
  for (int j = 0; j < numLeds; j++) { 
    if (getCoord(j,0) < (xCoord+(squareRadius/2)) && (getCoord(j,1) < (yCoord+squareRadius))) {
      if (getCoord(j,0) > (xCoord-(squareRadius/2)) && (getCoord(j,1) > (yCoord-squareRadius))) {
        int x = quickAbsolute(xCoord-getCoord(j,0));
        int y = quickAbsolute(yCoord-getCoord(j,1));
        if ((x/2) + y < diamondRadius) {
          setLedDirect(j, r, g, b, w, false);
        }
      }
    }
  }
}

