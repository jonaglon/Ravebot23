

void doPatternDonuts() {

  drawHexagon();
  
}

void drawHexagon() {
  int stripeBeatPos = (timeyInTime % 32768)/328; 
  
  for(int j = 0; j < numLeds; j++) {
    int xCoord = getCoord(j,0);
    int yCoord = getCoord(j,1);
    if ((yCoord > stripeBeatPos) && (yCoord < stripeBeatPos+200)) {
      if ((yCoord > stripeBeatPos) && (yCoord < stripeBeatPos+200)) {
        setLedDirect(j, 255, 0, 0, 0, false);
      }
    }
  }
}


void drawHexagon(int squareRadius, int xCoord, int  yCoord, int r, int g, int b, int w) {
  int diamondRadius=(squareRadius*1000)/1615;
  for (int j = 0; j < numLeds; j++) { 
    if ((getCoord(j,0) < (xCoord+diamondRadius)) && (getCoord(j,1) < (yCoord+diamondRadius))) {
      if ((getCoord(j,0) > (xCoord-diamondRadius)) && (getCoord(j,1) > (yCoord-diamondRadius))) {
        int x = quickAbsolute(xCoord-eyeCoords[j][0]);
        int y = quickAbsolute(yCoord-eyeCoords[j][1]);
        if (x + y < squareRadius) {
          setLedDirect(j, r, g, b, w, false);
        }
      }
    }
  }
}

