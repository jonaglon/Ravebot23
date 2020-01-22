  

void SetRgbwWheelVars(uint8_t WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    wheelR = 255 - WheelPos * 3;
    wheelG = 0;
    wheelB = WheelPos * 3;
    return;
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    wheelR = 0;
    wheelG = WheelPos * 3;
    wheelB = 255 - WheelPos * 3;
    return;
  }
  WheelPos -= 170;
  wheelR = WheelPos * 3;
  wheelG = 255 - WheelPos * 3;
  wheelB = 0;
  return;
}

void setGoodRandomColorVars() {
  uint16_t randomNum = random(20);
  switch (randomNum) {
    case 0: 
      goodColR = 255;
      goodColG = 0;
      goodColB = 0;
      goodColW = 0;
      break;
    case 1: 
      goodColR = 0;
      goodColG = 255;
      goodColB = 0;
      goodColW = 0;
      break;
    case 2: 
      goodColR = 0;
      goodColG = 0;
      goodColB = 255;
      goodColW = 0;
      break;
    case 3: 
      goodColR = 0;
      goodColG = 0;
      goodColB = 0;
      goodColW = 100;
      break;
    case 4: 
      goodColR = 245;
      goodColG = 7;
      goodColB = 225;
      goodColW = 0;
      break;
    case 5: 
      goodColR = 245;
      goodColG = 140;
      goodColB = 7;
      goodColW = 0;
      break;
    case 6: 
      goodColR = 2;
      goodColG = 133;
      goodColB = 142;
      goodColW = 0;
      break;
    case 7: 
      goodColR = 0;
      goodColG = 40;
      goodColB = 160;
      goodColW = 80;
      break;
    case 8: 
      goodColR = 82;
      goodColG = 104;
      goodColB = 4;
      goodColW = 0;
      break;
    case 9: 
      goodColR = 120;
      goodColG = 50;
      goodColB = 130;
      goodColW = 0;
      break;
    default: 
      SetRgbwWheelVars(random(255));
      goodColR = wheelR;
      goodColG = wheelG;
      goodColB = wheelB;
      goodColW = 0;
      break;
  }
}

uint16_t getCoord(uint16_t ledNum, uint16_t xOrY) {
  if (ledNum < 203)
     return binCoords[ledNum][xOrY]+ledPosOffset[0][xOrY];
  else if (ledNum < 378)
    return bigHeartCoords[ledNum-203][xOrY]+ledPosOffset[1][xOrY];
  else if (ledNum < 463)
    return smHeartCoords[ledNum-378][xOrY]+ledPosOffset[2][xOrY];
  else if (ledNum < 482)
    return armCoords[ledNum-463][xOrY]+ledPosOffset[3][xOrY];
  else if (ledNum < 506)
    return armCoords[ledNum-482][xOrY]+ledPosOffset[4][xOrY];
  else if (ledNum < 599)
    return eyeCoords[ledNum-506][xOrY]+ledPosOffset[5][xOrY];
  else if (ledNum < 692)
    return eyeCoords[ledNum-599][xOrY]+ledPosOffset[6][xOrY];
  else if (ledNum < 710)
    return horizCoords[ledNum-692][xOrY]+ledPosOffset[7][xOrY];
  else if (ledNum < 744)
    return tapeCoords[ledNum-710][xOrY]+ledPosOffset[8][xOrY];
  else if (ledNum < 770)
    return horizCoords[ledNum-744][xOrY]+ledPosOffset[9][xOrY];
  else if (ledNum < 774)
    return horizCoords[ledNum-770][xOrY]+ledPosOffset[10][xOrY];
  else if (ledNum < 797)
    return armCoords[ledNum-774][xOrY]+ledPosOffset[11][xOrY];
  else if (ledNum < 825)
    return armCoords[ledNum-797][xOrY]+ledPosOffset[12][xOrY];
  else if (ledNum < 911)
    return tubeCoords[ledNum-825][xOrY]+ledPosOffset[13][xOrY];
  else if (ledNum < 1001)
    return tubeCoords[ledNum-911][xOrY]+ledPosOffset[14][xOrY];
  else if (ledNum < 1090)
    return tubeCoords[ledNum-1001][xOrY]+ledPosOffset[15][xOrY];
  else if (ledNum < 1180)
    return tubeCoords[ledNum-1090][xOrY]+ledPosOffset[16][xOrY];
  else if (ledNum < 1302) {
    return portLCoords[(ledNum-1180)%19][xOrY]+ledPosOffset[17][xOrY];
  } else if (ledNum < 1442) {
    return portRCoords[(ledNum-1302)%19][xOrY]+ledPosOffset[18][xOrY];
  }
}

uint32_t quickAbsolute(int32_t number) {
  if (number < 0)
    return number * (-1);
  else
    return number;
}

//const int pupilRadius=26;
//const int maxRadius=42;
void drawEyeHexagon(int32_t ledNumOffSet, int32_t xCoord, int32_t  yCoord, int32_t pupilRadius, int32_t maxRadius, uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  for (uint16_t j = 0; j < 93; j++) { 
    if ((eyeCoords[j][0] < (xCoord+pupilRadius)) && (eyeCoords[j][1] < (yCoord+pupilRadius))) {
      if ((eyeCoords[j][0] > (xCoord-pupilRadius)) && (eyeCoords[j][1] > (yCoord-pupilRadius))) {
        uint32_t x = quickAbsolute(xCoord-eyeCoords[j][0]);
        uint32_t y = quickAbsolute(yCoord-eyeCoords[j][1]);
        if (x + y < maxRadius) {
          setLedDirect(ledNumOffSet+j, r, g, b, w, false);
        }
      }
    }
  }
}

void drawEyeSquare(int32_t offSet, int32_t xCoord, int32_t  yCoord, int32_t radius, uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  for(uint16_t j = 0; j < 93; j++) { 
    if ((eyeCoords[j][0] < (xCoord+radius)) && (eyeCoords[j][1] < (yCoord+radius))) {
      if ((eyeCoords[j][0] > (xCoord-radius)) && (eyeCoords[j][1] > (yCoord-radius))) {
        setLedDirect(offSet+j, r, g, b, w, false);
      }
    }
  }
}

void drawEyeIrisNoPupil(int32_t ledNumOffSet, int32_t xCoord, int32_t  yCoord, uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  for (uint16_t j = 0; j < 93; j++) { 
    uint16_t eyeX = eyeCoords[j][0];
    uint16_t eyeY = eyeCoords[j][1];
    if ((eyeX < (xCoord+7)) && (eyeY < (yCoord+7))) {
      if ((eyeX > (xCoord-7)) && (eyeY > (yCoord-7))) {
        continue;
      }
    }    
    if ((eyeX < (xCoord+26)) && (eyeY < (yCoord+26))) {
      if ((eyeX > (xCoord-26)) && (eyeY > (yCoord-26))) {
        uint16_t x = quickAbsolute(xCoord-eyeX);
        uint16_t y = quickAbsolute(yCoord-eyeY);
        if (x + y < 42) {
          setLedDirect(ledNumOffSet+j, r, g, b, w, false);
        }
      }
    }
  }
}

// ledSections[17] needs 1 adding to it
void setSection(uint16_t section, uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  for(int16_t j = ledSections[section]; j < ledSections[section+1]; j++) { 
    setLedDirect(j, r, g, b, w, true);
  }
}

void setSectionLed(uint16_t section, uint16_t ledNum, uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  if (ledNum < 0)
    return;
    
  uint16_t j = ledSections[section] + ledNum;
  if (j < ledSections[section+1])
    setLedDirect(j, r, g, b, w, true);
}

uint8_t sectionToCut1 = 0;
uint8_t sectionToCut2 = 0;
void cutRandomSection() {
  if (beatCycle) {
    sectionToCut1 = getNonEyeSectionNumber();
    sectionToCut2 = getNonEyeSectionNumber();
  }
  setSection(sectionToCut1, 0, 0, 0, 0);
  setSection(sectionToCut2, 0, 0, 0, 0);
}

uint8_t section1R = 0;
uint8_t section1G = 0;
uint8_t section1B = 0;
uint8_t section1W = 0;
uint8_t section2R = 0;
uint8_t section2G = 0;
uint8_t section2B = 0;
uint8_t section2W = 0;
bool randomSectionSwitchedOn = false;
void lightRandomSection(uint8_t offset) {

  if (beatCycle) {
    if (thisBeat8+offset == 6 || thisBeat8+offset == 7) {
      randomSectionSwitchedOn = true;
    } else {
      randomSectionSwitchedOn = false;
      return;
    }
    
    sectionToCut1 = getNonEyeSectionNumber();
    sectionToCut2 = getNonEyeSectionNumber();
    setGoodRandomColorVars();
    section1R = goodColR;
    section1G = goodColG;
    section1B = goodColB;
    section1W = goodColW;
    setGoodRandomColorVars();
    section2R = goodColR;
    section2G = goodColG;
    section2B = goodColB;
    section2W = goodColW;
  }

  if (randomSectionSwitchedOn) {
    setSection(sectionToCut1, section1R, section1G, section1B, section1W);
    setSection(sectionToCut2, section2R, section2G, section2B, section2W);
  }
}

uint8_t getNonEyeSectionNumber() {
  uint8_t sectionNumber = 5;
  while (sectionNumber == 5 || sectionNumber == 6) {
    sectionNumber = random(18);
  }
  return sectionNumber;
}

bool wholeRobotBrieflySwitchedOn = false;
void lightWholeRobotBriefly() {

  if (beatCycle) {
    if (sixteenBeats == 13 || sixteenBeats == 14 || sixteenBeats == 15 || sixteenBeats == 0) {
      wholeRobotBrieflySwitchedOn = true;
    } else {
      wholeRobotBrieflySwitchedOn = false;
      return;
    }
    
    setGoodRandomColorVars();
    section1R = goodColR;
    section1G = goodColG;
    section1B = goodColB;
    section1W = goodColW;
  }

  if (wholeRobotBrieflySwitchedOn) {
    everySingleLight(section1R, section1G, section1B, section1W);
  }
}

void everySingleLight(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  for(uint16_t j = 0; j < numLeds; j++) { 
    setLedDirect(j, r, g, b, w, false);
  }
}

void lightEyes(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  for(uint16_t j = 506; j < 693; j++) { 
    setLedDirect(j, r, g, b, w, false);
  }
}

void allOff() {
  for(uint16_t j = 0; j < numLeds; j++) {
    setLedDirect(j, 0, 0, 0, 0, true);
  }
}
void eyeBackground() {
  setSection(5, 20, 20, 20, 0);
  setSection(6, 20, 20, 20, 0);
}

void allOffBySection() {
  for(uint16_t j = 0; j < 19; j++) {
    setSection(j, 0, 0, 0, 0);
  }
}

void setLedDirect(uint16_t ledNum, uint8_t rVal, uint8_t gVal, uint8_t bVal, uint8_t wVal, bool showMouth) {
  if (ledNum < 0)
    return;

  //if (ledNum == 506 || ledNum == 507)
  //  return;

  if (ledNum < 203) {
    // Big bottom ring
    setRgbwLed((ledNum+178)%203, rVal, gVal, bVal, wVal);
  }
  else if (ledNum < 463) {
    // Body hearts
    setRgbwLed(ledNum+170, rVal, gVal, bVal, wVal);
  }
  else if (ledNum < 506) {
    // Left arm
    setRgbwLed(ledNum+275, rVal, gVal, bVal, wVal);
  }
  else if (ledNum < 692) {  
    // Eyes!693
    rVal = rVal/ledIntensity;
    gVal = gVal/ledIntensity;
    bVal = bVal/ledIntensity;
    wVal = wVal/ledIntensity;
    rgbwLeds[ledNum+536].b = gVal+(wVal/2) % 256;
    rgbwLeds[ledNum+537].g = rVal+wVal % 256;
    rgbwLeds[ledNum+537].r = bVal+wVal % 256;
  }
  else if (ledNum < 825) {
    if (!showMouth && ledNum < 710) {
      return;
    }
    
    // reverse indicator and tuner direction
    if (ledNum > 744 && ledNum < 774)
      ledNum = 1517-ledNum;

    // Rest of head and right arm
    setRgbwLedAfterEyes(ledNum+230, rVal, gVal, bVal, wVal);
  }
  else if (ledNum < 911) {
    // Body tube bottomright - 
    // setRgbwLed(ledNum+282, rVal, gVal, bVal, wVal); - 
    if (ledNum < 866)
      setRgbwLed(1972-ledNum, rVal, gVal, bVal, wVal);  // was 1968
    else
      setRgbwLed(2058-ledNum, rVal, gVal, bVal, wVal);
  }
  else if (ledNum < 1001) {
    // Body tube bottomleft
    if (ledNum < 992)
      setRgbwLed(2184-ledNum, rVal, gVal, bVal, wVal);
    else
      setRgbwLed(2274-ledNum, rVal, gVal, bVal, wVal);
  }
  else if (ledNum < 1090) {
    // Body tube topleft
    if (ledNum < 1042)
      setRgbwLed(2324-ledNum, rVal, gVal, bVal, wVal);
    else
      setRgbwLed(2413-ledNum, rVal, gVal, bVal, wVal);
  }
  else if (ledNum < 1180) {
    // Body tube topright
    if (ledNum < 1160)
      setRgbwLed(2531-ledNum, rVal, gVal, bVal, wVal);
    else
      setRgbwLed(2620-ledNum, rVal, gVal, bVal, wVal);
  }
  else if (ledNum < 1443) {
    // Bass holes!
    setRgbwLed(ledNum+285, rVal, gVal, bVal, wVal);
  }
}

void setRgbwLed(uint16_t ledNumber, uint8_t rVal, uint8_t gVal, uint8_t bVal, uint8_t wVal) {
  uint16_t newNumber = (ledNumber * 4) / 3;
  int8_t mod = ledNumber % 3;

  rVal = rVal/ledIntensity > 255 ? 255 : rVal/ledIntensity;
  gVal = gVal/ledIntensity > 255 ? 255 : gVal/ledIntensity;
  bVal = bVal/ledIntensity > 255 ? 255 : bVal/ledIntensity;
  wVal = wVal/ledIntensity > 255 ? 255 : wVal/ledIntensity;

  if (mod == 0)
  {
    rgbwLeds[newNumber].r = rVal;
    rgbwLeds[newNumber].g = gVal;
    rgbwLeds[newNumber].b = bVal;
    rgbwLeds[newNumber+1].g =wVal;
  }
  else if (mod == 1)
  {
    rgbwLeds[newNumber].r = gVal;
    rgbwLeds[newNumber].b = rVal;
    rgbwLeds[newNumber+1].r =wVal;
    rgbwLeds[newNumber+1].g =bVal;
  }
  else 
  {
    rgbwLeds[newNumber].b = gVal;
    rgbwLeds[newNumber+1].r =bVal;
    rgbwLeds[newNumber+1].g =rVal;
    rgbwLeds[newNumber+1].b =wVal;
  }
}

void setRgbwLedAfterEyes(uint16_t ledNumber, uint8_t rVal, uint8_t gVal, uint8_t bVal, uint8_t wVal) {
  if (rVal < 0)
    rVal = 0;
  if (gVal < 0)
    gVal = 0;
  if (bVal < 0)
    bVal = 0;
  if (wVal < 0)
    wVal = 0;
  
  int32_t newNumber = (ledNumber * 4) / 3;
  int8_t mod = ledNumber % 3;
  
  rVal = rVal/ledIntensity > 255 ? 255 : rVal/ledIntensity;
  gVal = gVal/ledIntensity > 255 ? 255 : gVal/ledIntensity;
  bVal = bVal/ledIntensity > 255 ? 255 : bVal/ledIntensity;
  wVal = wVal/ledIntensity > 255 ? 255 : wVal/ledIntensity;

  if (mod == 0)
  {
    rgbwLeds[newNumber-1].b = rVal;
    rgbwLeds[newNumber-1].r = gVal;
    rgbwLeds[newNumber].g = bVal;
    rgbwLeds[newNumber].r = wVal;
  }
  else if (mod == 1)
  {
    rgbwLeds[newNumber].g = rVal;
    rgbwLeds[newNumber-1].b = gVal;
    rgbwLeds[newNumber].r = bVal;
    rgbwLeds[newNumber].b = wVal;
  }
  else 
  {
    rgbwLeds[newNumber].r = rVal;
    rgbwLeds[newNumber].g = gVal;
    rgbwLeds[newNumber].b = bVal;
    rgbwLeds[newNumber+1].g = wVal;
  }
}



