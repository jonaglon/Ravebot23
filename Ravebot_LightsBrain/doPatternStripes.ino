struct stripies {
  uint8_t stripeR;
  uint8_t stripeG;
  uint8_t stripeB;
  uint8_t stripeW;
  uint8_t colorPattern;
  uint16_t width;
  uint16_t offset;
  uint8_t speedDivisor;
  bool xOrY;
  bool forwardOrBack;
  stripies(uint8_t aStripeR, uint8_t aStripeG, uint8_t aStripeB, uint8_t aStripeW, uint8_t aColorPattern, uint16_t aWidth, uint16_t aOffset, uint8_t aSpeedDivisor, bool aXOrY, bool aForwardOrBack) :
    stripeR(aStripeR), stripeG(aStripeG), stripeB(aStripeB), stripeW(aStripeW), colorPattern(aColorPattern), width(aWidth), offset(aOffset), speedDivisor(aSpeedDivisor), xOrY(aXOrY), forwardOrBack(aForwardOrBack) {
  }
};

const uint8_t numStripesPattern1 = 16;
const int16_t animLengthStripes1 = 16384;
stripies stripePattern1[16] = {
  {0, 0, 0, 0, 0, 256,    0, 32, true, true },      // Top to bottom
  {0, 0, 0, 0, 0, 256, 1024, 32, true, true }, 
  {0, 0, 0, 0, 0, 256, 2048, 32, true, true },
  {0, 0, 0, 0, 0, 256, 3072, 32, true, true },
  {0, 0, 0, 0, 0, 256, 4096, 32, false, false },    // Left to right
  {0, 0, 0, 0, 0, 256, 5120, 32, false, false },
  {0, 0, 0, 0, 0, 256, 6144, 32, false, false },
  {0, 0, 0, 0, 0, 256, 7168, 32, false, false },
  {0, 0, 0, 0, 0, 256, 8192, 32, true, false },     // Bottom to top
  {0, 0, 0, 0, 0, 256, 9216, 32, true, false },
  {0, 0, 0, 0, 0, 256,10240, 32, true, false },
  {0, 0, 0, 0, 0, 256,11264, 32, true, false },
  {0, 0, 0, 0, 0, 256,12288, 32, false, true },     // Right to left
  {0, 0, 0, 0, 0, 256,13312, 32, false, true },
  {0, 0, 0, 0, 0, 256,14336, 32, false, true },
  {0, 0, 0, 0, 0, 256,15360, 32, false, true },
};

const uint8_t numStripesPattern2 = 16;
int16_t animLengthStripes2 = 16384;
stripies stripePattern2[16] = {
  {0, 0, 0, 0, 0, 256,    0, 32, false, false },
  {0, 0, 0, 0, 0, 256, 1024, 32, false, false }, 
  {0, 0, 0, 0, 0, 256, 2048, 32, false, false },
  {0, 0, 0, 0, 1, 500, 3072, 64, true, true },
  {0, 0, 0, 0, 0, 256, 4096, 32, false, false },
  {0, 0, 0, 0, 0, 256, 5120, 32, false, false },
  {0, 0, 0, 0, 0, 256, 6144, 32, false, false },
  {0, 0, 0, 0, 2, 500, 7168, 64, true, true },
  {0, 0, 0, 0, 0, 256, 8192, 32, false, false },
  {0, 0, 0, 0, 0, 256, 9216, 32, false, false },
  {0, 0, 0, 0, 0, 256,10240, 32, false, false },
  {0, 0, 0, 0, 3, 500,11264, 64, true, true },
  {0, 0, 0, 0, 0, 256,12288, 32, false, false },
  {0, 0, 0, 0, 0, 256,13312, 32, false, false },
  {0, 0, 0, 0, 0, 256,14336, 32, false, false },
  {0, 0, 0, 0, 4, 500,15360, 64, true, true }
};

const uint8_t numStripesPattern3 = 8;
int16_t animLengthStripes3 = 8192;
stripies stripePattern3[8] = {
  {0, 0, 0, 0, 0, 1024,    0, 64, false, false },
  {0, 0, 0, 0, 0, 1024, 1024, 64, true, false },
  {0, 0, 0, 0, 0, 1024, 2048, 64, false, true },
  {0, 0, 0, 0, 0, 1024, 3072, 64, true, true },
  {0, 0, 0, 0, 0, 1024, 4096, 64, false, false },
  {0, 0, 0, 0, 0, 1024, 5120, 64, true, false },
  {0, 0, 0, 0, 0, 1024, 6144, 64, false, true },
  {0, 0, 0, 0, 0, 1024, 7168, 64, true, true }
};

const uint8_t numStripesPattern4 = 16;
int16_t animLengthStripes4 = 8192;
stripies stripePattern4[16] = {
  {0, 0, 0, 0, 0,  522, 256, 64, false, false },
  {0, 0, 0, 0, 0, 522,  768, 64, false, false },
  {0, 0, 0, 0, 0, 522, 1280, 64, false, false },
  {0, 0, 0, 0, 0, 522, 1792, 64, false, false },
  {0, 0, 0, 0, 0, 522, 2304, 64, false, false },
  {0, 0, 0, 0, 0, 522, 2816, 64, false, false },
  {0, 0, 0, 0, 0, 522, 3328, 64, false, false },
  {0, 0, 0, 0, 0, 522, 3840, 64, false, false },
  {0, 0, 0, 0, 0, 522, 4352, 64, false, false },
  {0, 0, 0, 0, 0, 522, 4864, 64, false, false },
  {0, 0, 0, 0, 0, 522, 5376, 64, false, false },
  {0, 0, 0, 0, 0, 522, 5888, 64, false, false },
  {0, 0, 0, 0, 0, 522, 6400, 64, false, false },
  {0, 0, 0, 0, 0, 522, 6912, 64, false, false },
  {0, 0, 0, 0, 0, 522, 7424, 64, false, false },
  {0, 0, 0, 0, 0, 522, 7936, 64, false, false }
};


void doPatternStripes() {
  if (currentLightPattern == 14) {
    stripesPattern(numStripesPattern1, stripePattern1, animLengthStripes1);
  } else if (currentLightPattern == 15) {
    stripesPattern(numStripesPattern2, stripePattern2, animLengthStripes2);
  } else if (currentLightPattern == 16) {
    stripesPattern(numStripesPattern3, stripePattern3, animLengthStripes3);
  } else if (currentLightPattern == 17) {
    stripesPattern(numStripesPattern4, stripePattern4, animLengthStripes4);
  }
}

 
void stripesPattern(uint8_t numStripesInPattern, struct stripies *stripePatterns, int16_t animLength) {
  for(int stripeNum = 0; stripeNum < numStripesInPattern; stripeNum++) {
    uint16_t stripeBeatPos = (((timeyInTime / stripePatterns[stripeNum].speedDivisor) + stripePatterns[stripeNum].offset) % animLength);
    
    if (beatCycle && stripeBeatPos > (animLength - 1500)) {
      setNewColorForStripe(stripeNum, stripePatterns);
    }
    
    if (stripePatterns[stripeNum].forwardOrBack) {
      if (stripePatterns[stripeNum].xOrY)
        stripeBeatPos = 7740-stripeBeatPos;      // Top to bottom
      else
        stripeBeatPos = 6560-stripeBeatPos;      // Right to left
    } else {
      if (stripePatterns[stripeNum].xOrY)
        stripeBeatPos = stripeBeatPos+2068;       // Bottom to top
      else
        stripeBeatPos = stripeBeatPos+1922;       // Left to right
    }
    
    stripeBeatPos = stripeBeatPos % animLength;
    
    for(int16_t j = 0; j < numLeds; j++) {
      uint8_t xOrY = 0;
      if (stripePatterns[stripeNum].xOrY)
        xOrY = 1;
      uint16_t coord = getCoord2(j,xOrY);

      if ((coord > stripeBeatPos) && (coord < stripeBeatPos+stripePatterns[stripeNum].width)) {
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
void setNewColorForStripe(uint8_t stripeNum, struct stripies *stripePatterns) {
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




