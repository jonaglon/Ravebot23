uint8_t fullColor1r = 255;
uint8_t fullColor1g = 0;
uint8_t fullColor1b = 0;
uint8_t fullColor1w = 0;

void doWholeColours(uint8_t wholePattern) {
  if (wholePattern == 1) {
    doFullColour(8);
  } else if (wholePattern == 2) {
    if (currentBar < 32)
      doFullColour(16);
    else if (currentBar < 64)
      doFullColour(8);
    else if (currentBar < 32)
      doFullColour(4);
    else if (currentBar < 96)
      doFullColour(2);
    else if (currentBar < 128)
      doFullColour(1);
    else
      doFullColour(4);
  }
}

void doFullColour(uint8_t changeSpeed) {
  if (beatCycle && (((sixteenBeats+15)%changeSpeed) == 0)) {
    setGoodRandomColorVars();
    fullColor1r = goodColR;
    fullColor1g = goodColG;
    fullColor1b = goodColB;
    fullColor1w = goodColW;
  }

  for(int16_t j = 0; j < numLeds; j++) {
    setLedDirect(j, fullColor1r, fullColor1g, fullColor1b, fullColor1w, false);
  }
 }
