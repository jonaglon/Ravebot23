
void doPatternStripes() {
  if (currentLightPattern == 14) {
    int currentStripePattern = (timeyInTime/524288)%2;
    stripesPattern(currentStripePattern+2);
  } else if (currentLightPattern == 15) {
    stripesPattern(1);
  }  
}

// JR TODO: ...
//  1 Get good timings for the 1-2-3-4 for each of the four directions
//  2 Wipes, on the beat l-r, top-bot, r-l, bot-top, repeat. Use good colours.
//  3 KinghtRider with big-ish LUT?
//  The stripe based rainbows probly belong here.


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

// Stripe patterns - 
// 1 - Random good colors moving slowly top to bottom
// 2 - 
const byte numStripesPattern1 = 4;
stripies stripePatterns[4][4] = {
{ {0, 0, 0, 0, 1, 256, 512, 32, true, true },
  {0, 0, 0, 0, 2, 256, 1536, 32, true, true }, 
  {0, 0, 0, 0, 3, 256, 2560, 32, true, true },
  {0, 0, 0, 0, 4, 256, 3584, 32, true, true } },
{ {0, 0, 0, 0, 1, 256, 1536, 32, false, false },
  {0, 0, 0, 0, 2, 256, 512, 32, false, false },
  {0, 0, 0, 0, 3, 256, 3584, 32, false, false },
  {0, 0, 0, 0, 4, 256, 2560, 32, false, false } },
{ {0, 0, 0, 0, 1, 256, 2560, 32, true, false },
  {0, 0, 0, 0, 2, 256, 3584, 32, true, false },
  {0, 0, 0, 0, 3, 256, 512, 32, true, false },
  {0, 0, 0, 0, 4, 256, 1536, 32, true, false } },
{ {0, 0, 0, 0, 1, 256, 2304, 32, false, true },
  {0, 0, 0, 0, 2, 256, 3328, 32, false, true },
  {0, 0, 0, 0, 3, 256, 256, 32, false, true },
  {0, 0, 0, 0, 4, 256, 1280, 32, false, true } },
};

/*
{ {0, 0, 0, 0, 1, 256, 3328, 32, false, true },
  {0, 0, 0, 0, 2, 256, 256, 32, false, true },
  {0, 0, 0, 0, 3, 256, 1280, 32, false, true },
  {0, 0, 0, 0, 4, 256, 2304, 32, false, true } },
 */

void stripesPattern(byte pattern) {
  for(int stripeNum = 0; stripeNum < numStripesPattern1; stripeNum++) {
    // I think beat stripe bassline has to start below zero 
    int stripeBeatBassline = ((timeyInTime / stripePatterns[pattern][stripeNum].speedDivisor) % 4096)-512;
    if (stripePatterns[pattern][stripeNum].forwardOrBack) {
      stripeBeatBassline = 4096-stripeBeatBassline;
    }
    int stripeBeatPos = (stripeBeatBassline + stripePatterns[pattern][stripeNum].offset) % 4096;
  
    if (beatCycle && stripeBeatPos > 3100) {
      setNewColorForStripe(pattern, stripeNum);
    }
  
    for(int j = 0; j < numLeds; j++) {
      byte xOrY = 0;
      if (stripePatterns[pattern][stripeNum].xOrY)
        xOrY = 1;
      int xCoord = getCoord(j,xOrY);
      if ((xCoord > stripeBeatPos) && (xCoord < stripeBeatPos+stripePatterns[pattern][stripeNum].width)) {
        setLedDirect(j, stripePatterns[pattern][stripeNum].stripeR, stripePatterns[pattern][stripeNum].stripeG, stripePatterns[pattern][stripeNum].stripeB, stripePatterns[pattern][stripeNum].stripeW, false);
      }
    }   
  }
}

// Stripe color setter, stripe color pattern is the colorPattern in the stripe array
// 0 = good random color
// 1 = 255 red
// 2 = 255 green
// 3 = 255 blue
// 4 = 100 white
// 5 = Red, gold and green? TODO!
void setNewColorForStripe(byte pattern, byte stripeNum) {
  if (stripePatterns[pattern][stripeNum].colorPattern == 0) {
    setGoodRandomColorVars();
    stripePatterns[pattern][stripeNum].stripeR = goodColR;
    stripePatterns[pattern][stripeNum].stripeG = goodColG;
    stripePatterns[pattern][stripeNum].stripeB = goodColB;
    stripePatterns[pattern][stripeNum].stripeW = goodColW;
  } else if (stripePatterns[pattern][stripeNum].colorPattern == 1) {
    stripePatterns[pattern][stripeNum].stripeR = 255;
    stripePatterns[pattern][stripeNum].stripeG = 0;
    stripePatterns[pattern][stripeNum].stripeB = 0;
    stripePatterns[pattern][stripeNum].stripeW = 0;
  } else if (stripePatterns[pattern][stripeNum].colorPattern == 2) {
    stripePatterns[pattern][stripeNum].stripeR = 0;
    stripePatterns[pattern][stripeNum].stripeG = 255;
    stripePatterns[pattern][stripeNum].stripeB = 0;
    stripePatterns[pattern][stripeNum].stripeW = 0;
  } else if (stripePatterns[pattern][stripeNum].colorPattern == 3) {
    stripePatterns[pattern][stripeNum].stripeR = 0;
    stripePatterns[pattern][stripeNum].stripeG = 0;
    stripePatterns[pattern][stripeNum].stripeB = 255;
    stripePatterns[pattern][stripeNum].stripeW = 0;
  } else if (stripePatterns[pattern][stripeNum].colorPattern == 4) {
    stripePatterns[pattern][stripeNum].stripeR = 0;
    stripePatterns[pattern][stripeNum].stripeG = 0;
    stripePatterns[pattern][stripeNum].stripeB = 0;
    stripePatterns[pattern][stripeNum].stripeW = 100;
  } else {
    setGoodRandomColorVars();
    stripePatterns[pattern][stripeNum].stripeR = goodColR;
    stripePatterns[pattern][stripeNum].stripeG = goodColG;
    stripePatterns[pattern][stripeNum].stripeB = goodColB;
    stripePatterns[pattern][stripeNum].stripeW = goodColW;
  }
}




