

void doPatternStripes() {
  if (currentLightPattern == 14) {
    stripesPattern1(32);
  } else if (currentLightPattern == 15) {
    stripesPattern2Old();
  }  
}

byte stripe1r, stripe1g, stripe1b, stripe1w;
void stripesPattern1(int speedyo) {

  int stripeBeatPos1 = 4096-((timeyInTime / speedyo) % 4096);
  int stripeBeatPos2 = (stripeBeatPos1 + 512) % 4096;

  if (beatCycle && stripeBeatPos1 > 3000) {
    setGoodRandomColorVars();
    stripe1r = goodColR;
    stripe1g = goodColG;
    stripe1b = goodColB;
    stripe1w = goodColW;
  }

  for(int j = 0; j < numLeds; j++) {
    int xCoord = getCoord(j,1);
    if ((xCoord > stripeBeatPos1) && (xCoord < stripeBeatPos1+256)) {
      setLedDirect(j, stripe1r, stripe1g, stripe1b, stripe1w, false);
    }
    /* if ((xCoord > stripeBeatPos2) && (xCoord < stripeBeatPos2+200)) {
      setLedDirect(j, 0, 255, 0, 0, false);
    } */
  }
}


// JR TODO: ...
// OK. These patterns are both shit and need deleting. What might be good? Use below to implement above.
// Herm. 
//  1 Wipes, on the beat top-bot, r-l, bot-top, l-r, repeat. Use good colours.
//  2 Constant stripes. l-r good colours non stop would be nice.
//  3 KinghtRider with big-ish LUT
//  The stripe based rainbows probly belong here.



void stripesPattern1Old() {

  SetRgbwWheelVars((timeyInTime / 512) % 256);

  int sixteenBeatPos = (sixteenBeats / 4) % 4;
  int stripeBeatPos=0;
  int xyCord=0;
  
  if (sixteenBeatPos == 0) {
    stripeBeatPos = (timeyInTime / 32) % 1024;
  } else if (sixteenBeatPos == 1) {
    stripeBeatPos = 2048-((timeyInTime / 32) % 2048);
    xyCord=1;
  } else if (sixteenBeatPos == 2) {
    stripeBeatPos = 615-((timeyInTime / 32) % 1024);
  } else if (sixteenBeatPos == 3) {
    stripeBeatPos = (timeyInTime / 32) % 2048;
    xyCord=1;
  }

  for(int j = 0; j < numLeds; j++) {
    int yCoord = getCoord(j,xyCord);
    if ((yCoord > stripeBeatPos) && (yCoord < stripeBeatPos+200)) {
      setLedDirect(j, wheelR, wheelG, wheelB, 0, false);
    }
  }
}

void stripesPattern2Old() {

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
      setLedDirect(j, 255, 0, 0, 0, false);

    if ((yCoord < 1024-stripeBeatPos) && (yCoord > 1024-stripeBeatPos-400))
      setLedDirect(j, rVal, gVal, bVal, wVal, false);
      
  }
}

