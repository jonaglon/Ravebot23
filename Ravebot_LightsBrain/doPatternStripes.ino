void doPatternStripes() {
  if (currentLightPattern == 14) {
    stripesPattern(4);
  } else if (currentLightPattern == 15) {
    stripesPattern(4);
  }
}

// JR TODO: ...
//  x 1 Get good timings for the 1-2-3-4 for each of the four directions
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
// 1 - Random good colors moving slowly top to bottom - TODO next, consider if lots of little array patterns like below are best way to handle stipes.
// 2 - 
/*const byte numStripesPatterns = 16;
stripies stripePatterns[16] = {
  {0, 0, 0, 0, 1, 256,    0, 32, true, true },      // Top to bottom
  {0, 0, 0, 0, 2, 256, 1024, 32, true, true }, 
  {0, 0, 0, 0, 3, 256, 2048, 32, true, true },
  {0, 0, 0, 0, 4, 256, 3072, 32, true, true },
  {0, 0, 0, 0, 1, 256, 4096, 32, false, false },    // Left to right
  {0, 0, 0, 0, 2, 256, 5120, 32, false, false },
  {0, 0, 0, 0, 3, 256, 6144, 32, false, false },
  {0, 0, 0, 0, 4, 256, 7168, 32, false, false },
  {0, 0, 0, 0, 1, 256, 8192, 32, true, false },     // Bottom to top
  {0, 0, 0, 0, 2, 256, 9216, 32, true, false },
  {0, 0, 0, 0, 3, 256,10240, 32, true, false },
  {0, 0, 0, 0, 4, 256,11264, 32, true, false },
  {0, 0, 0, 0, 1, 256,12288, 32, false, true },     // Right to left
  {0, 0, 0, 0, 2, 256,13312, 32, false, true },
  {0, 0, 0, 0, 3, 256,14336, 32, false, true },
  {0, 0, 0, 0, 4, 256,15360, 32, false, true },
};*/
 
const byte numStripesPatterns = 4;
stripies stripePatterns[4] = {
  {0, 0, 0, 0, 4, 256,    0, 32, false, false },    // Left to right
  {0, 0, 0, 0, 3, 256, 1024, 32, false, false },
  {0, 0, 0, 0, 2, 256, 2048, 32, false, false },
  {0, 0, 0, 0, 1, 256, 3072, 32, false, false },
};
 

void stripesPattern(byte numStripesInPattern) {
  for(int stripeNum = 0; stripeNum < numStripesInPattern; stripeNum++) {
    int stripeBeatBassline = (((timeyInTime / stripePatterns[stripeNum].speedDivisor) + stripePatterns[stripeNum].offset) % 16384);
    
    if (stripePatterns[stripeNum].forwardOrBack) {
      if (stripePatterns[stripeNum].xOrY)
        stripeBeatBassline = 16384-stripeBeatBassline+2048;   // Top to bottom
      else
        stripeBeatBassline = 16384-stripeBeatBassline;   // Bottom to top
    } else {
      if (stripePatterns[stripeNum].xOrY)
        stripeBeatBassline = stripeBeatBassline+256;       // Right to left
      else
        stripeBeatBassline = stripeBeatBassline+11520;      // Left to right    // ud du are broken as they go r g b w up from the bassline when they should go down
    }
    
    int stripeBeatPos = (stripeBeatBassline + stripePatterns[stripeNum].offset) % 16384;
  
    if (beatCycle && stripeBeatPos > 14336) {  // JR TODO - this number is now questionable, should be low / high so not too many unneeded changes.
      setNewColorForStripe(stripeNum);
    }
  
    for(int j = 0; j < numLeds; j++) {
      byte xOrY = 0;
      if (stripePatterns[stripeNum].xOrY)
        xOrY = 1;
      int xCoord = getCoord(j,xOrY);
      if ((xCoord > stripeBeatPos) && (xCoord < stripeBeatPos+stripePatterns[stripeNum].width)) {
        setLedDirect(j, stripePatterns[stripeNum].stripeR, stripePatterns[stripeNum].stripeG, stripePatterns[stripeNum].stripeB, stripePatterns[stripeNum].stripeW, false);
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
void setNewColorForStripe(byte stripeNum) {
  if (stripePatterns[stripeNum].colorPattern == 0) {
    setGoodRandomColorVars();
    stripePatterns[stripeNum].stripeR = goodColR;
    stripePatterns[stripeNum].stripeG = goodColG;
    stripePatterns[stripeNum].stripeB = goodColB;
    stripePatterns[stripeNum].stripeW = goodColW;
  } else if (stripePatterns[stripeNum].colorPattern == 1) {
    stripePatterns[stripeNum].stripeR = 255;
    stripePatterns[stripeNum].stripeG = 0;
    stripePatterns[stripeNum].stripeB = 0;
    stripePatterns[stripeNum].stripeW = 0;
  } else if (stripePatterns[stripeNum].colorPattern == 2) {
    stripePatterns[stripeNum].stripeR = 0;
    stripePatterns[stripeNum].stripeG = 255;
    stripePatterns[stripeNum].stripeB = 0;
    stripePatterns[stripeNum].stripeW = 0;
  } else if (stripePatterns[stripeNum].colorPattern == 3) {
    stripePatterns[stripeNum].stripeR = 0;
    stripePatterns[stripeNum].stripeG = 0;
    stripePatterns[stripeNum].stripeB = 255;
    stripePatterns[stripeNum].stripeW = 0;
  } else if (stripePatterns[stripeNum].colorPattern == 4) {
    stripePatterns[stripeNum].stripeR = 0;
    stripePatterns[stripeNum].stripeG = 0;
    stripePatterns[stripeNum].stripeB = 0;
    stripePatterns[stripeNum].stripeW = 100;
  } else {
    setGoodRandomColorVars();
    stripePatterns[stripeNum].stripeR = goodColR;
    stripePatterns[stripeNum].stripeG = goodColG;
    stripePatterns[stripeNum].stripeB = goodColB;
    stripePatterns[stripeNum].stripeW = goodColW;
  }
}




