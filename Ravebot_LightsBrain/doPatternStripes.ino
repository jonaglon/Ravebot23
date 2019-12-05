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

const byte numStripesPattern1 = 16;
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

const byte numStripesPattern2 = 16;
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

const byte numStripesPattern3 = 8;
stripies stripePattern3[8] = {
  {0, 0, 0, 0, 1, 3000,    0, 64, false, false },
  {0, 0, 0, 0, 2, 3000, 2048, 64, true, false },
  {0, 0, 0, 0, 3, 3000, 4096, 64, false, true },
  {0, 0, 0, 0, 4, 3000, 6144, 64, true, true },
  {0, 0, 0, 0, 1, 3000, 8192, 64, false, false },
  {0, 0, 0, 0, 2, 3000,10240, 64, true, false },
  {0, 0, 0, 0, 3, 3000,12288, 64, false, true },
  {0, 0, 0, 0, 4, 3000,14336, 64, true, true }
};


void doPatternStripes() {
  if (currentLightPattern == 14) {
    stripesPattern(numStripesPattern1, stripePattern1);
  } else if (currentLightPattern == 15) {
    // stripesPattern(numStripesPattern2, stripePattern2);
    stripesPattern(numStripesPattern3, stripePattern3);
  }
}

 
void stripesPattern(byte numStripesInPattern, struct stripies *stripePatterns) {
  for(int stripeNum = 0; stripeNum < numStripesInPattern; stripeNum++) {
    int stripeBeatPos = (((timeyInTime / stripePatterns[stripeNum].speedDivisor) + stripePatterns[stripeNum].offset) % 16384);
    
    if (beatCycle && stripeBeatPos > 14336) {
      setNewColorForStripe(stripeNum, stripePatterns);
    }
    
    if (stripePatterns[stripeNum].forwardOrBack) {
      if (stripePatterns[stripeNum].xOrY)
        stripeBeatPos = 15932-stripeBeatPos;      // Top to bottom
      else
        stripeBeatPos = 14752-stripeBeatPos;      // Right to left
    } else {
      if (stripePatterns[stripeNum].xOrY)
        stripeBeatPos = stripeBeatPos+2068;       // Bottom to top
      else
        stripeBeatPos = stripeBeatPos+1922;       // Left to right
    }
    
    stripeBeatPos = stripeBeatPos % 16384;
    
    for(int j = 0; j < numLeds; j++) {
      byte xOrY = 0;
      if (stripePatterns[stripeNum].xOrY)
        xOrY = 1;
      int xCoord = getCoord(j,xOrY);

      if (testMode && j == 0 && beatCycle) {
        Serial.print("xCoord:");
        Serial.print(xCoord);
        Serial.print("   stripeBeatPos:");
        Serial.println(stripeBeatPos);
      }
      
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
void setNewColorForStripe(byte stripeNum, struct stripies *stripePatterns) {
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




