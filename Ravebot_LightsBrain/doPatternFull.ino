uint8_t fullColor1r = 255;
uint8_t fullColor1g = 0;
uint8_t fullColor1b = 0;
uint8_t fullColor1w = 0;

void doFullColours(uint8_t wholePattern) {
  if (wholePattern == 0) {
    doFullColour(8);
  } else if (wholePattern == 1) {
    uint8_t speedyo = currentBar%128;
    if (speedyo < 16)
      doFullColour(16);
    else if (speedyo < 32)
      doFullColour(8);
    else if (speedyo < 48)
      doFullColour(4);
    else if (speedyo < 64)
      doFullColour(2);
    else if (speedyo < 80)
      doFullColour(1);
    else if (speedyo < 96)
      doFullColour(2);
    else if (speedyo < 112)
      doFullColour(4);
    else
      doFullColour(8);
  } else if (wholePattern == 2) {
    doFullColour(1);
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

