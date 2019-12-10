
void drawRGBHexagons() {
  int yStripeBeatPos = (timeyInTime % 65536)/64; // 0-958
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

byte hex1R = 0;
byte hex1G = 0;
byte hex1B = 0;
byte hex1W = 0;
bool hexagonOverlayOn = false;
void drawHexagonOverlay() {
  if (beatCycle) {
    byte thisBeat = totalBeats % 32;
    if (thisBeat == 26) {
      setGoodRandomColorVars();
      hex1R = goodColR;
      hex1G = goodColG;
      hex1B = goodColB;
      hex1W = goodColW; 
      hexagonOverlayOn = false;
      return;
    } else if (thisBeat == 26 || thisBeat == 27 || thisBeat == 28 || thisBeat == 29) {
      hexagonOverlayOn = true;
    } else {
      hexagonOverlayOn = false;
      return;
    } 
  }

  if (hexagonOverlayOn) {
    int yStripeBeatPos = ((timeyInTime+32768  ) % 65536)/64;
    drawHexagon(yStripeBeatPos, hex1R, hex1G, hex1B, hex1W);
  }
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

