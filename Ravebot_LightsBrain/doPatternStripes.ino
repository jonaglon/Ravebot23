

void doPatternStripes() {
  if (currentLightPattern == 14) {
    stripesPattern1();
  } else if (currentLightPattern == 15) {
    stripesPattern2Old();
  }  
}

struct stripies {
  byte stripeR;
  byte stripeG;
  byte stripeB;
  byte stripeW;
  int width;
  int offset;
  int speedDivisor;
  stripies(byte aStripeR, byte aStripeG, byte aStripeB, byte aStripeW, int aWidth, int aOffset, int aSpeedDivisor) :
    stripeR(aStripeR), stripeG(aStripeG), stripeB(aStripeB), stripeW(aStripeW), width(aWidth), offset(aOffset), speedDivisor(aSpeedDivisor) {
  }
};

const byte numStripesPattern1 = 4;
stripies stripePattern1[numStripesPattern1] = {
  {255, 0, 0, 0, 256, 0, 32 },
  {255, 0, 0, 0, 256, 512, 32 },
  {255, 0, 0, 0, 256, 1024, 32 },
  {255, 0, 0, 0, 256, 1536, 32 }
};

void stripesPattern1() {

  for(int x = 0; x < numStripesPattern1; x++) {
    int stripeBeatBassline = 4096-((timeyInTime / stripePattern1[x].speedDivisor) % 4096);
    int stripeBeatPos = (stripeBeatBassline + stripePattern1[x].offset) % 4096;
  
    if (beatCycle && stripeBeatPos > 3000) {
      setGoodRandomColorVars();
      stripePattern1[x].stripeR = goodColR;
      stripePattern1[x].stripeG = goodColG;
      stripePattern1[x].stripeB = goodColB;
      stripePattern1[x].stripeW = goodColW;
    }
  
    for(int j = 0; j < numLeds; j++) {
      int xCoord = getCoord(j,1);
      if ((xCoord > stripeBeatPos) && (xCoord < stripeBeatPos+stripePattern1[x].width)) {
        setLedDirect(j, stripePattern1[x].stripeR, stripePattern1[x].stripeG, stripePattern1[x].stripeB, stripePattern1[x].stripeW, false);
      }
    }
    
  }
}


// JR TODO: ...
// OK. These patterns are both shit and need deleting. What might be good? Use below to implement above.
// Herm. 
//  1 Wipes, on the beat top-bot, r-l, bot-top, l-r, repeat. Use good colours.
//  2 Constant stripes. l-r good colours non stop would be nice.
//  3 KinghtRider with big-ish LUT
//  The stripe based rainbows probly belong here.


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

