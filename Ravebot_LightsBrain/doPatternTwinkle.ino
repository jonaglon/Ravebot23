const short speedDivisor = 4096;  /* small numbers equals faster strips! */

int ledToLight;

void doTwinkles() {

  for (int twinky = 0; twinky < usedTwinkleCount[currentLightPattern]; twinky++) {

    int newLedNum = myTwinkles[twinky].ledNum;
    if (myTwinkles[twinky].speedy != 0)
    {
        int ticky = (twinkleTime / speedDivisor)/quickAbsolute(myTwinkles[twinky].speedy);
        if (myTwinkles[twinky].speedy < 0) {
          newLedNum = numLeds-((myTwinkles[twinky].ledNum + ticky)%numLeds);
        } else {
          newLedNum = (myTwinkles[twinky].ledNum + ticky)%numLeds;
        }
    }

    int twinkLength = myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy + myTwinkles[twinky].fadeOut;

    if ((twinkleTime > (myTwinkles[twinky].start)) && (twinkleTime < (myTwinkles[twinky].start + myTwinkles[twinky].fadeIn))) {
      setLedsFadeIn(newLedNum, twinky, false);
      if (!myTwinkles[twinky].hasTwinked)
        myTwinkles[twinky].hasTwinked = true;
    } else if (((myTwinkles[twinky].start + myTwinkles[twinky].fadeIn) > animLength) && (twinkleTime < ((myTwinkles[twinky].start + myTwinkles[twinky].fadeIn) % animLength))) {
      setLedsFadeIn(newLedNum, twinky, true);
      if (!myTwinkles[twinky].hasTwinked)
        myTwinkles[twinky].hasTwinked = true;
    } else if ((twinkleTime >= (myTwinkles[twinky].start + myTwinkles[twinky].fadeIn)) && (twinkleTime < (myTwinkles[twinky].start + myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy))) {
      setLedsOnFull(newLedNum, twinky, false);
      if (!myTwinkles[twinky].hasTwinked)
        myTwinkles[twinky].hasTwinked = true;
    } else if (((myTwinkles[twinky].start + myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy) > animLength) && (twinkleTime < ((myTwinkles[twinky].start + myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy) % animLength))) {
      setLedsOnFull(newLedNum, twinky, true);
      if (!myTwinkles[twinky].hasTwinked)
        myTwinkles[twinky].hasTwinked = true;
    } else if ((twinkleTime >= (myTwinkles[twinky].start + myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy)) && (twinkleTime < (myTwinkles[twinky].start + twinkLength)) ) {
      setLedsFadeOut(newLedNum, twinky, false);
      if (!myTwinkles[twinky].hasTwinked)
        myTwinkles[twinky].hasTwinked = true;
    } else if (((myTwinkles[twinky].start + myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy + myTwinkles[twinky].fadeOut) > animLength) && (twinkleTime < ((myTwinkles[twinky].start + myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy + myTwinkles[twinky].fadeOut) % animLength))) {
      setLedsFadeOut(newLedNum, twinky, true);
      if (!myTwinkles[twinky].hasTwinked)
        myTwinkles[twinky].hasTwinked = true;
    } else if ((twinkleTime >= (((myTwinkles[twinky].start + myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy + myTwinkles[twinky].fadeOut) % animLength))) && myTwinkles[twinky].hasTwinked) {
      resetTwink(twinky);
    }
  }
}

void setupNewTwinklePattern(int newTwinklePattern) {
  currentLightPattern = newTwinklePattern;
  for (int twink = 0; twink < usedTwinkleCount[currentLightPattern]; twink++) {
    switch (newTwinklePattern) {
      case 0:
        setupTwinkle0(twink);
        break;
      case 1:
        setupTwinkle1(twink);
        break;
      case 2:
        setupTwinkle2(twink);
        break;
      case 3:
        setupTwinkle3(twink);
        break;
      case 4:
        setupTwinkle4(twink);
        break;
      case 5:
        setupTwinkle5(twink);
        break;
      case 6:
        setupTwinkle6(twink);
        break;
      case 7:
        setupTwinkle7(twink);
        break;
      case 8:
        setupTwinkle8(twink);
        break;
      case 9:
        setupTwinkle9(twink);
        break;
      case 10:
        setupTwinkle10(twink);
        break;
      case 11:
        setupTwinkle11(twink);
        break;
      case 12:
        setupTwinkle12(twink);
        break;
      case 13:
        setupTwinkle13(twink);
        break;
    }
  }
}

void resetTwink(int twink) {
  switch (currentLightPattern) {
    case 0:
      setupTwinkle0(twink);
      break;
    case 1:
      setupTwinkle1(twink);
      break;
    case 2:
      setupTwinkle2(twink);
      break;
    case 3:
      setupTwinkle3(twink);
      break;
    case 4:
      setupTwinkle4(twink);
      break;
    case 5:
      setupTwinkle5(twink);
      break;
    case 6:
      setupTwinkle6(twink);
      break;
    case 7:
      setupTwinkle7(twink);
      break;
    case 8:
      setupTwinkle8(twink);
      break;
    case 9:
      setupTwinkle9(twink);
      break;
    case 10:
      setupTwinkle10(twink);
      break;
    case 11:
      setupTwinkle11(twink);
      break;
    case 12:
      setupTwinkle12(twink);
      break;
    case 13:
      setupTwinkle13(twink);
      break;  
    }
}


void setLedsFadeIn(int ledNum, int twinky, bool rolledOver) {

  int percentThroughFade = 0;
  if (rolledOver) {
    percentThroughFade = (((twinkleTime + animLength) - myTwinkles[twinky].start) * 100) / myTwinkles[twinky].fadeIn;
  } else {
    percentThroughFade = ((twinkleTime - myTwinkles[twinky].start) * 100) / myTwinkles[twinky].fadeIn;
  }

  int percentThroughPatternCalc = 0;
  if (rolledOver) {
    percentThroughPatternCalc = ((twinkleTime + animLength) - myTwinkles[twinky].start) * 100;
  } else {
    percentThroughPatternCalc = (twinkleTime - myTwinkles[twinky].start) * 100;
  }
  int percentThroughPattern = percentThroughPatternCalc / (myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy + myTwinkles[twinky].fadeOut);
  
  int newRed = ((myTwinkles[twinky].rCol + (((myTwinkles[twinky].rToCol - myTwinkles[twinky].rCol) * percentThroughPattern) / 100)) * percentThroughFade) / 100;
  int newGreen = ((myTwinkles[twinky].gCol + (((myTwinkles[twinky].gToCol - myTwinkles[twinky].gCol) * percentThroughPattern) / 100)) * percentThroughFade) / 100;
  int newBlue = ((myTwinkles[twinky].bCol + (((myTwinkles[twinky].bToCol - myTwinkles[twinky].bCol) * percentThroughPattern) / 100)) * percentThroughFade) / 100;
  int newWhite = ((myTwinkles[twinky].wCol + (((myTwinkles[twinky].wToCol - myTwinkles[twinky].wCol) * percentThroughPattern) / 100)) * percentThroughFade) / 100;

  if (rgbwLeds[ledNum].r > newRed) { newRed = rgbwLeds[ledNum].r; }
  if (rgbwLeds[ledNum].g > newGreen) { newGreen = rgbwLeds[ledNum].g; }
  if (rgbwLeds[ledNum].b > newBlue) { newBlue = rgbwLeds[ledNum].b; }

  for (int ledToLight = 0; ledToLight < myTwinkles[twinky].widthy; ledToLight++) {
    int minusFade = myTwinkles[twinky].sideFade * ledToLight;
    setLedDirect(ledNum + ledToLight, newRed-minusFade < 0 ? 0 : newRed-minusFade, newGreen-minusFade < 0 ? 0 : newGreen-minusFade, newBlue-minusFade < 0 ? 0 : newBlue-minusFade, newWhite-minusFade < 0 ? 0 : newWhite-minusFade, false);
    setLedDirect(ledNum - ledToLight, newRed-minusFade < 0 ? 0 : newRed-minusFade, newGreen-minusFade < 0 ? 0 : newGreen-minusFade, newBlue-minusFade < 0 ? 0 : newBlue-minusFade, newWhite-minusFade < 0 ? 0 : newWhite-minusFade, false);
  }
}

void setLedsOnFull(int ledNum, int twinky, bool rolledOver) {

  int percentThroughFade = 0;
  if (rolledOver) {
    percentThroughFade = ((twinkleTime + animLength) - myTwinkles[twinky].start) * 100;
  } else {
    percentThroughFade = (twinkleTime - myTwinkles[twinky].start) * 100;
  }
  int percentThroughPattern = percentThroughFade / (myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy + myTwinkles[twinky].fadeOut);

  int newRed = ((myTwinkles[twinky].rCol + (((myTwinkles[twinky].rToCol - myTwinkles[twinky].rCol) * percentThroughPattern) / 100)));
  int newGreen = ((myTwinkles[twinky].gCol + (((myTwinkles[twinky].gToCol - myTwinkles[twinky].gCol) * percentThroughPattern) / 100)));
  int newBlue = ((myTwinkles[twinky].bCol + (((myTwinkles[twinky].bToCol - myTwinkles[twinky].bCol) * percentThroughPattern) / 100)));
  int newWhite = ((myTwinkles[twinky].wCol + (((myTwinkles[twinky].wToCol - myTwinkles[twinky].wCol) * percentThroughPattern) / 100)));

  if (rgbwLeds[ledNum].r > newRed) { newRed = rgbwLeds[ledNum].r; }
  if (rgbwLeds[ledNum].g > newGreen) { newGreen = rgbwLeds[ledNum].g; }
  if (rgbwLeds[ledNum].b > newBlue) { newBlue = rgbwLeds[ledNum].b; }

  for (int ledToLight = 0; ledToLight < myTwinkles[twinky].widthy; ledToLight++) {
    int minusFade = myTwinkles[twinky].sideFade * ledToLight;
    setLedDirect(ledNum + ledToLight, newRed-minusFade < 0 ? 0 : newRed-minusFade, newGreen-minusFade < 0 ? 0 : newGreen-minusFade, newBlue-minusFade < 0 ? 0 : newBlue-minusFade, newWhite-minusFade < 0 ? 0 : newWhite-minusFade, false);
    setLedDirect(ledNum - ledToLight, newRed-minusFade < 0 ? 0 : newRed-minusFade, newGreen-minusFade < 0 ? 0 : newGreen-minusFade, newBlue-minusFade < 0 ? 0 : newBlue-minusFade, newWhite-minusFade < 0 ? 0 : newWhite-minusFade, false);
  }
}


void setLedsFadeOut(int ledNum, int twinky, bool rolledOver) {
  int percentThroughFade = 0;
  int start = (myTwinkles[twinky].start + myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy);
  int endy = (myTwinkles[twinky].start + myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy + myTwinkles[twinky].fadeOut);
  if (rolledOver) {
    percentThroughFade = 100 - quickAbsolute((((twinkleTime + animLength) - start) * 100) / (endy-start));
  } else {
    percentThroughFade = 100 - quickAbsolute(((twinkleTime - start) * 100) / (endy-start));
  }

  int percentThroughPatternCalc = 0;
  if (rolledOver) {
    percentThroughPatternCalc = ((twinkleTime + animLength) - myTwinkles[twinky].start) * 100;
  } else {
    percentThroughPatternCalc = (twinkleTime - myTwinkles[twinky].start) * 100;
  }
  int percentThroughPattern = (percentThroughPatternCalc / (myTwinkles[twinky].fadeIn + myTwinkles[twinky].lengthy + myTwinkles[twinky].fadeOut));

  int newRed = ((myTwinkles[twinky].rCol + (((myTwinkles[twinky].rToCol - myTwinkles[twinky].rCol) * percentThroughPattern) / 100)) * percentThroughFade) / 100;
  int newGreen = ((myTwinkles[twinky].gCol + (((myTwinkles[twinky].gToCol - myTwinkles[twinky].gCol) * percentThroughPattern) / 100)) * percentThroughFade) / 100;
  int newBlue = ((myTwinkles[twinky].bCol + (((myTwinkles[twinky].bToCol - myTwinkles[twinky].bCol) * percentThroughPattern) / 100)) * percentThroughFade) / 100;
  int newWhite = ((myTwinkles[twinky].wCol + (((myTwinkles[twinky].wToCol - myTwinkles[twinky].wCol) * percentThroughPattern) / 100)) * percentThroughFade) / 100;

  if (rgbwLeds[ledNum].r > newRed) { newRed = rgbwLeds[ledNum].r; }
  if (rgbwLeds[ledNum].g > newGreen) { newGreen = rgbwLeds[ledNum].g; }
  if (rgbwLeds[ledNum].b > newBlue) { newBlue = rgbwLeds[ledNum].b; }

  for (int ledToLight = 0; ledToLight < myTwinkles[twinky].widthy; ledToLight++) {
    int minusFade = myTwinkles[twinky].sideFade * ledToLight;
    setLedDirect(ledNum + ledToLight, newRed-minusFade < 0 ? 0 : newRed-minusFade, newGreen-minusFade < 0 ? 0 : newGreen-minusFade, newBlue-minusFade < 0 ? 0 : newBlue-minusFade, newWhite-minusFade < 0 ? 0 : newWhite-minusFade, false);
    setLedDirect(ledNum - ledToLight, newRed-minusFade < 0 ? 0 : newRed-minusFade, newGreen-minusFade < 0 ? 0 : newGreen-minusFade, newBlue-minusFade < 0 ? 0 : newBlue-minusFade, newWhite-minusFade < 0 ? 0 : newWhite-minusFade, false);
  }
}

int findNewStart(int newTwinkleFadeIn) {
  int newRandom = random(1, 16);
  return (animLength16th * newRandom) - newTwinkleFadeIn;
}

int findNewLength() {
  int newRandom = random(1, 16);
  return (animLength16th * newRandom);
}

void setupTwinkle0(int twinky) {
  myTwinkles[twinky].ledNum = random(numLeds);
  myTwinkles[twinky].rCol =  random(240);
  myTwinkles[twinky].gCol =  random(140);
  myTwinkles[twinky].bCol =  random(220);
  myTwinkles[twinky].wCol =  0;
  myTwinkles[twinky].rToCol =  random(240);
  myTwinkles[twinky].gToCol =  random(150);
  myTwinkles[twinky].bToCol =  random(220);
  myTwinkles[twinky].wToCol =  random(100);
  myTwinkles[twinky].lengthy = findNewLength();
  myTwinkles[twinky].fadeIn =  2048;
  myTwinkles[twinky].fadeOut = 2048;
  myTwinkles[twinky].start = findNewStart(myTwinkles[twinky].fadeIn); 
  myTwinkles[twinky].widthy =  1;
  myTwinkles[twinky].speedy = 0;
  myTwinkles[twinky].sideFade = 0;
  myTwinkles[twinky].hasTwinked = false;
}


void setupTwinkle1(int twinky) {
  myTwinkles[twinky].ledNum = random(numLeds);
  myTwinkles[twinky].rCol =  random(250);
  myTwinkles[twinky].gCol =  random(140);
  myTwinkles[twinky].bCol =  random(220);
  myTwinkles[twinky].wCol =  0;
  myTwinkles[twinky].rToCol =  random(250);
  myTwinkles[twinky].gToCol =  random(150);
  myTwinkles[twinky].bToCol =  random(220);
  myTwinkles[twinky].wToCol =  0;
  myTwinkles[twinky].lengthy = 65536;
  myTwinkles[twinky].fadeIn =  0;
  myTwinkles[twinky].fadeOut = 0;
  myTwinkles[twinky].start = findNewStart(myTwinkles[twinky].fadeIn); 
  myTwinkles[twinky].widthy =  3;
  myTwinkles[twinky].speedy = 0;
  myTwinkles[twinky].sideFade = 30;
  myTwinkles[twinky].hasTwinked = false;
}

void setupTwinkle2(int twinky) {
  myTwinkles[twinky].ledNum = random(numLeds);
  myTwinkles[twinky].rCol =  random(220);
  myTwinkles[twinky].gCol =  random(200);
  myTwinkles[twinky].bCol =  random(210);
  myTwinkles[twinky].wCol =  0;
  myTwinkles[twinky].rToCol = myTwinkles[twinky].rCol;
  myTwinkles[twinky].gToCol =  myTwinkles[twinky].gCol;
  myTwinkles[twinky].bToCol =  myTwinkles[twinky].bCol;
  myTwinkles[twinky].wToCol =  0;
  myTwinkles[twinky].lengthy =  65536;
  myTwinkles[twinky].fadeIn =  0;
  myTwinkles[twinky].fadeOut =  0;
  myTwinkles[twinky].start = findNewStart(myTwinkles[twinky].fadeIn); 
  myTwinkles[twinky].widthy = random(2,6);
  myTwinkles[twinky].speedy = 0;
  myTwinkles[twinky].sideFade = 20;
  myTwinkles[twinky].hasTwinked = false;
}

void setupTwinkle3(int twinky) {
  myTwinkles[twinky].ledNum = random(numLeds);
  myTwinkles[twinky].rCol =  0;
  myTwinkles[twinky].gCol =  0;
  myTwinkles[twinky].bCol =  0;
  myTwinkles[twinky].wCol =  255;
  myTwinkles[twinky].rToCol = 0;
  myTwinkles[twinky].gToCol =  0;
  myTwinkles[twinky].bToCol =  0;
  myTwinkles[twinky].wToCol =  255;
  myTwinkles[twinky].lengthy =  65536;
  myTwinkles[twinky].fadeIn =  0;
  myTwinkles[twinky].fadeOut =  0;
  myTwinkles[twinky].start = findNewStart(0); 
  myTwinkles[twinky].widthy = 1;
  myTwinkles[twinky].speedy = 0;
  myTwinkles[twinky].sideFade = 0;
  myTwinkles[twinky].hasTwinked = false;
}

void setupTwinkle4(int twinky) {
  SetRgbwWheelVars((timey / 90)%256);
  
  myTwinkles[twinky].ledNum = random(numLeds);
  myTwinkles[twinky].rCol =  wheelR;
  myTwinkles[twinky].gCol =  wheelG;
  myTwinkles[twinky].bCol =  wheelB;
  myTwinkles[twinky].wCol =  0;
  myTwinkles[twinky].rToCol =  myTwinkles[twinky].rCol;
  myTwinkles[twinky].gToCol =  myTwinkles[twinky].gCol;
  myTwinkles[twinky].bToCol =  myTwinkles[twinky].bCol;
  myTwinkles[twinky].wToCol =  myTwinkles[twinky].wCol;
  myTwinkles[twinky].lengthy = findNewLength();
  myTwinkles[twinky].fadeIn =  0;
  myTwinkles[twinky].fadeOut =  0;
  myTwinkles[twinky].start = findNewStart(myTwinkles[twinky].fadeIn); 
  myTwinkles[twinky].widthy =  random(3);
  myTwinkles[twinky].speedy = 0;
  myTwinkles[twinky].sideFade = 0;
  myTwinkles[twinky].hasTwinked = false;
}


void setupTwinkle5(int twinky) {
  myTwinkles[twinky].ledNum = random(numLeds);
  int myRandom = random(6);
  if (myRandom == 0) {
    myTwinkles[twinky].rCol =  255;
    myTwinkles[twinky].gCol =  0;
    myTwinkles[twinky].bCol =  0;
    myTwinkles[twinky].wCol =  0;    
  } else if (myRandom == 1) {
    myTwinkles[twinky].rCol =  0;
    myTwinkles[twinky].gCol =  255;
    myTwinkles[twinky].bCol =  0;
    myTwinkles[twinky].wCol =  0;
  } else if (myRandom == 2) {
    myTwinkles[twinky].rCol =  0;
    myTwinkles[twinky].gCol =  0;
    myTwinkles[twinky].bCol =  255;
    myTwinkles[twinky].wCol =  0;
  } else {
    myTwinkles[twinky].rCol =  0;
    myTwinkles[twinky].gCol =  0;
    myTwinkles[twinky].bCol =  0;
    myTwinkles[twinky].wCol =  255;
  }
  myTwinkles[twinky].rToCol =  myTwinkles[twinky].rCol;
  myTwinkles[twinky].gToCol =  myTwinkles[twinky].gCol;
  myTwinkles[twinky].bToCol =  myTwinkles[twinky].bCol;
  myTwinkles[twinky].wToCol =  myTwinkles[twinky].wCol;
  myTwinkles[twinky].lengthy = findNewLength();
  myTwinkles[twinky].fadeIn =  0;
  myTwinkles[twinky].fadeOut =  0;
  myTwinkles[twinky].start = findNewStart(0); 
  myTwinkles[twinky].widthy = 1;
  myTwinkles[twinky].speedy = 0;
  myTwinkles[twinky].sideFade = 0;
  myTwinkles[twinky].hasTwinked = false;
}

void setupTwinkle6(int twinky) {
  myTwinkles[twinky].ledNum = random(numLeds);
  myTwinkles[twinky].rCol =  random(250);
  myTwinkles[twinky].gCol =  random(120);
  myTwinkles[twinky].bCol =  random(240);
  myTwinkles[twinky].wCol =  0;
  myTwinkles[twinky].rToCol =  random(250);
  myTwinkles[twinky].gToCol =  random(150);
  myTwinkles[twinky].bToCol =  random(220);
  myTwinkles[twinky].wToCol =  0;
  myTwinkles[twinky].lengthy = findNewLength();
  myTwinkles[twinky].fadeIn =  0;
  myTwinkles[twinky].fadeOut = 65536;
  myTwinkles[twinky].start = findNewStart(myTwinkles[twinky].fadeIn); 
  myTwinkles[twinky].widthy =  random(30);
  myTwinkles[twinky].speedy = 0;
  myTwinkles[twinky].sideFade = 0;
  myTwinkles[twinky].hasTwinked = false;
}


void setupTwinkle7(int twinky) {
  myTwinkles[twinky].ledNum = random(numLeds);
  myTwinkles[twinky].rCol =  random(240);
  myTwinkles[twinky].gCol =  random(140);
  myTwinkles[twinky].bCol =  random(220);
  myTwinkles[twinky].wCol =  0;
  myTwinkles[twinky].rToCol =  random(240);
  myTwinkles[twinky].gToCol =  random(150);
  myTwinkles[twinky].bToCol =  random(220);
  myTwinkles[twinky].wToCol =  random(100);
  myTwinkles[twinky].lengthy = findNewLength();
  myTwinkles[twinky].fadeIn =  2048;
  myTwinkles[twinky].fadeOut = 2048;
  myTwinkles[twinky].start = findNewStart(myTwinkles[twinky].fadeIn); 
  myTwinkles[twinky].widthy =  1;
  myTwinkles[twinky].speedy = random(-10, 10);
  myTwinkles[twinky].sideFade = 0;
  myTwinkles[twinky].hasTwinked = false;
}


void setupTwinkle8(int twinky) {
  myTwinkles[twinky].ledNum = random(numLeds);
  myTwinkles[twinky].rCol =  random(250);
  myTwinkles[twinky].gCol =  random(140);
  myTwinkles[twinky].bCol =  random(220);
  myTwinkles[twinky].wCol =  0;
  myTwinkles[twinky].rToCol =  random(250);
  myTwinkles[twinky].gToCol =  random(150);
  myTwinkles[twinky].bToCol =  random(220);
  myTwinkles[twinky].wToCol =  0;
  myTwinkles[twinky].lengthy = findNewLength();
  myTwinkles[twinky].fadeIn =  4096;
  myTwinkles[twinky].fadeOut = 0;
  myTwinkles[twinky].start = findNewStart(myTwinkles[twinky].fadeIn); 
  myTwinkles[twinky].widthy =  3;
  myTwinkles[twinky].speedy = random(-30, 30);
  myTwinkles[twinky].sideFade = 30;
  myTwinkles[twinky].hasTwinked = false;
}

void setupTwinkle9(int twinky) {
  myTwinkles[twinky].ledNum = random(numLeds);
  myTwinkles[twinky].rCol =  random(220);
  myTwinkles[twinky].gCol =  random(200);
  myTwinkles[twinky].bCol =  random(210);
  myTwinkles[twinky].wCol =  0;
  myTwinkles[twinky].rToCol = myTwinkles[twinky].rCol;
  myTwinkles[twinky].gToCol =  myTwinkles[twinky].gCol;
  myTwinkles[twinky].bToCol =  myTwinkles[twinky].bCol;
  myTwinkles[twinky].wToCol =  0;
  myTwinkles[twinky].lengthy =  32768;
  myTwinkles[twinky].fadeIn =  0;
  myTwinkles[twinky].fadeOut =  0;
  myTwinkles[twinky].start = findNewStart(myTwinkles[twinky].fadeIn); 
  myTwinkles[twinky].widthy = random(2,6);
  myTwinkles[twinky].speedy = random(-30, 30);
  myTwinkles[twinky].sideFade = 20;
  myTwinkles[twinky].hasTwinked = false;
}

void setupTwinkle10(int twinky) {
  myTwinkles[twinky].ledNum = random(numLeds);
  myTwinkles[twinky].rCol =  0;
  myTwinkles[twinky].gCol =  0;
  myTwinkles[twinky].bCol =  0;
  myTwinkles[twinky].wCol =  255;
  myTwinkles[twinky].rToCol = 0;
  myTwinkles[twinky].gToCol =  0;
  myTwinkles[twinky].bToCol =  0;
  myTwinkles[twinky].wToCol =  255;
  myTwinkles[twinky].lengthy =  32768;
  myTwinkles[twinky].fadeIn =  0;
  myTwinkles[twinky].fadeOut =  0;
  myTwinkles[twinky].start = findNewStart(0); 
  myTwinkles[twinky].widthy = 1;
  myTwinkles[twinky].speedy = random(-2, 2);
  myTwinkles[twinky].sideFade = 0;
  myTwinkles[twinky].hasTwinked = false;
}

void setupTwinkle11(int twinky) {
  SetRgbwWheelVars((timey / 90)%256);
  
  myTwinkles[twinky].ledNum = random(numLeds);
  myTwinkles[twinky].rCol =  wheelR;
  myTwinkles[twinky].gCol =  wheelG;
  myTwinkles[twinky].bCol =  wheelB;
  myTwinkles[twinky].wCol =  0;
  myTwinkles[twinky].rToCol =  myTwinkles[twinky].rCol;
  myTwinkles[twinky].gToCol =  myTwinkles[twinky].gCol;
  myTwinkles[twinky].bToCol =  myTwinkles[twinky].bCol;
  myTwinkles[twinky].wToCol =  myTwinkles[twinky].wCol;
  myTwinkles[twinky].lengthy = 32768;
  myTwinkles[twinky].fadeIn =  0;
  myTwinkles[twinky].fadeOut =  0;
  myTwinkles[twinky].start = findNewStart(myTwinkles[twinky].fadeIn); 
  myTwinkles[twinky].widthy =  random(3);
  myTwinkles[twinky].speedy = random(-10, 10);
  myTwinkles[twinky].sideFade = 0;
  myTwinkles[twinky].hasTwinked = false;
}


void setupTwinkle12(int twinky) {
  myTwinkles[twinky].ledNum = random(numLeds);
  int myRandom = random(6);
  if (myRandom == 0) {
    myTwinkles[twinky].rCol =  255;
    myTwinkles[twinky].gCol =  0;
    myTwinkles[twinky].bCol =  0;
    myTwinkles[twinky].wCol =  0;    
  } else if (myRandom == 1) {
    myTwinkles[twinky].rCol =  0;
    myTwinkles[twinky].gCol =  255;
    myTwinkles[twinky].bCol =  0;
    myTwinkles[twinky].wCol =  0;
  } else if (myRandom == 2) {
    myTwinkles[twinky].rCol =  0;
    myTwinkles[twinky].gCol =  0;
    myTwinkles[twinky].bCol =  255;
    myTwinkles[twinky].wCol =  0;
  } else {
    myTwinkles[twinky].rCol =  0;
    myTwinkles[twinky].gCol =  0;
    myTwinkles[twinky].bCol =  0;
    myTwinkles[twinky].wCol =  255;
  }
  myTwinkles[twinky].rToCol =  myTwinkles[twinky].rCol;
  myTwinkles[twinky].gToCol =  myTwinkles[twinky].gCol;
  myTwinkles[twinky].bToCol =  myTwinkles[twinky].bCol;
  myTwinkles[twinky].wToCol =  myTwinkles[twinky].wCol;
  myTwinkles[twinky].lengthy =  findNewLength();
  myTwinkles[twinky].fadeIn =  0;
  myTwinkles[twinky].fadeOut =  0;
  myTwinkles[twinky].start = findNewStart(0); 
  myTwinkles[twinky].widthy = 1;
  myTwinkles[twinky].speedy = random(-20, 20);
  myTwinkles[twinky].sideFade = 0;
  myTwinkles[twinky].hasTwinked = false;
}

void setupTwinkle13(int twinky) {
  myTwinkles[twinky].ledNum = random(numLeds);
  myTwinkles[twinky].rCol =  random(250);
  myTwinkles[twinky].gCol =  random(120);
  myTwinkles[twinky].bCol =  random(240);
  myTwinkles[twinky].wCol =  random(50);
  myTwinkles[twinky].rToCol =  random(250);
  myTwinkles[twinky].gToCol =  random(150);
  myTwinkles[twinky].bToCol =  random(220);
  myTwinkles[twinky].wToCol =  0;
  myTwinkles[twinky].lengthy = findNewLength();
  myTwinkles[twinky].fadeIn =  0;
  myTwinkles[twinky].fadeOut = 8192;
  myTwinkles[twinky].start = findNewStart(myTwinkles[twinky].fadeIn); 
  myTwinkles[twinky].widthy =  random(30);
  myTwinkles[twinky].speedy = random(-5, 5);
  myTwinkles[twinky].sideFade = 0;
  myTwinkles[twinky].hasTwinked = false;
}

