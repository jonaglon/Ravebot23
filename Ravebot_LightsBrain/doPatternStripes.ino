
void doPatternStripes() {
  if (currentLightPattern == 14) {
    stripesPattern1();
  } else if (currentLightPattern == 15) {
    stripesPattern1();
  }  
}

struct stripies {
  byte stripeR;
  byte stripeG;
  byte stripeB;
  byte stripeW;
  byte colorPattern;
  int width;
  int offset;
  int speedDivisor;
  bool xOrY;
  bool forwardOrBack;
  stripies(byte aStripeR, byte aStripeG, byte aStripeB, byte aStripeW, byte aColorPattern, int aWidth, int aOffset, int aSpeedDivisor, bool aXOrY, bool aForwardOrBack) :
    stripeR(aStripeR), stripeG(aStripeG), stripeB(aStripeB), stripeW(aStripeW), colorPattern(aColorPattern), width(aWidth), offset(aOffset), speedDivisor(aSpeedDivisor), xOrY(aXOrY), forwardOrBack(aForwardOrBack) {
  }
};

const byte numStripesPattern1 = 4;
stripies stripePattern1[numStripesPattern1] = {
  {0, 0, 0, 0, 0, 256, -512, 32, false, false },
  {0, 0, 0, 0, 0, 256, 512, 32, true, true },
  {0, 0, 0, 0, 0, 256, 1536, 32, true, false },
  {0, 0, 0, 0, 1, 256, 2560, 32, true, true },
};

void stripesPattern1() {
  for(int stripeNum = 0; stripeNum < numStripesPattern1; stripeNum++) {
    int stripeBeatBassline = ((timeyInTime / stripePattern1[stripeNum].speedDivisor) % 4096);
    if (stripePattern1[stripeNum].xOrY) {
      stripeBeatBassline = 4096-stripeBeatBassline;
    }

    int stripeBeatPos = (stripeBeatBassline + stripePattern1[stripeNum].offset) % 4096;
  
    if (beatCycle && stripeBeatPos > 3100) {
      setNewColorForStripe(stripeNum);
    }
  
    for(int j = 0; j < numLeds; j++) {
      int xCoord = getCoord(j,0);
      if ((xCoord > stripeBeatPos) && (xCoord < stripeBeatPos+stripePattern1[stripeNum].width)) {
        setLedDirect(j, stripePattern1[stripeNum].stripeR, stripePattern1[stripeNum].stripeG, stripePattern1[stripeNum].stripeB, stripePattern1[stripeNum].stripeW, false);
      }
    }   
  }
}

void setNewColorForStripe(int stripeNum) {
  if (stripePattern1[stripeNum].colorPattern == 0) {
    setGoodRandomColorVars();
    stripePattern1[stripeNum].stripeR = goodColR;
    stripePattern1[stripeNum].stripeG = goodColG;
    stripePattern1[stripeNum].stripeB = goodColB;
    stripePattern1[stripeNum].stripeW = goodColW;
  } else if (stripePattern1[stripeNum].colorPattern == 1) {
    stripePattern1[stripeNum].stripeR = 0;
    stripePattern1[stripeNum].stripeG = 0;
    stripePattern1[stripeNum].stripeB = 0;
    stripePattern1[stripeNum].stripeW = 100;
  } else {
    setGoodRandomColorVars();
    stripePattern1[stripeNum].stripeR = goodColR;
    stripePattern1[stripeNum].stripeG = goodColG;
    stripePattern1[stripeNum].stripeB = goodColB;
    stripePattern1[stripeNum].stripeW = goodColW;
  }
}

// JR TODO: ...
// OK. These patterns are both shit and need deleting. What might be good? Use below to implement above.
// Herm. 
//  1 Wipes, on the beat top-bot, r-l, bot-top, l-r, repeat. Use good colours.
//  2 Constant stripes. l-r good colours non stop would be nice.
//  3 KinghtRider with big-ish LUT
//  The stripe based rainbows probly belong here.



