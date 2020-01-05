/*
uint8_t stripe1r = 255;
uint8_t stripe1g = 0;
uint8_t stripe1b = 0;
uint8_t stripe1w = 0;
uint8_t stripe2r = 0;
uint8_t stripe2g = 255;
uint8_t stripe2b = 0;
uint8_t stripe2w = 0;
uint8_t stripe3r = 0;
uint8_t stripe3g = 0;
uint8_t stripe3b = 255;
uint8_t stripe3w = 0;
uint8_t stripe4r = 0;
uint8_t stripe4g = 0;
uint8_t stripe4b = 0;
uint8_t stripe4w = 255;*/
uint8_t stripeCols[4][4] = {{255, 0, 0, 0}, {0, 255, 0, 0}, {0, 0, 255, 0}, {0, 0, 0, 255}};

void doPatternStripes(uint8_t stripePattern) {
  // StripeSpeed is 0=fast,1=med,2=slow. Fast is 1 per beat

  if (stripePattern == 1) {
    doRLStripe(1, 512, 2, 0);
    doLRStripe(1, 512, 2, 2); // speed 2 works with 512
  } else if (stripePattern == 2) {
    if (sixteenBeats < 8)
      doLRStripe(1, 100, 0, 2);
    else
      doRLStripe(2, 100, 0, 1);
    doUDStripe(3, 800, 2, 2, false);
    doDUStripe(4, 800, 2, 2);
  } else  if (stripePattern == 2) {
    doUDStripe(3, 500, 2, 2, true);
  }
}

void doLRStripe(uint8_t stripeNum, uint16_t stripeLength, uint8_t stripeSpeed, uint8_t stripeCol) {
  int32_t stripeBeatPos = 0; 
  if (stripeSpeed == 0) {
    stripeBeatPos = (((timeyInTime/16)+512)-stripeLength)%2048;
    if (beatCycle && stripeBeatPos == 0) {
      setNewColorForStripey(stripeNum, stripeCol);
    }
  } else if (stripeSpeed == 1) {
    stripeBeatPos = (((timeyInTime/32)+1512)-stripeLength)%2048;
    if (beatCycle && stripeBeatPos > 1500) {
      setNewColorForStripey(stripeNum, stripeCol);
    }
  } else {
    stripeBeatPos = (((timeyInTime/64)+205)-stripeLength)%2048; // 250 early 1212 good higher makes for earlier
    if (beatCycle && stripeBeatPos > 1500) {
      setNewColorForStripey(stripeNum, stripeCol);
    }
  }

  for(int16_t j = 0; j < numLeds; j++) {
    uint16_t coord = getCoord(j,0)+stripeLength;
    if ((coord > stripeBeatPos) && (coord < stripeBeatPos+stripeLength)) {
      setStripeLed(j, stripeNum);
    }
  }
}

// JR TODO - when you change the length of the strip the timings change except for this RL which subtracts stripeLen, do this for the others!

void doRLStripe(uint8_t stripeNum, uint16_t stripeLength, uint8_t stripeSpeed, uint8_t stripeCol) {
  int32_t stripeBeatPos = 0; 
  if (stripeSpeed == 0) {
    stripeBeatPos = (((timeyInTime/16)+876)-stripeLength)%2048;
    if (beatCycle && stripeBeatPos < 500) {
      setNewColorForStripey(stripeNum, stripeCol);
    }
  } else if (stripeSpeed == 1) {
    stripeBeatPos = (((timeyInTime/32)+176)-stripeLength)%2048;
    if (beatCycle && stripeBeatPos < 450) {
      setNewColorForStripey(stripeNum, stripeCol);
    }
  } else {
    stripeBeatPos = (((timeyInTime/64)+975)-stripeLength)%2048;
    if (beatCycle && stripeBeatPos < 400) {
      setNewColorForStripey(stripeNum, stripeCol);
    }
  }
  
  stripeBeatPos = 2048-stripeBeatPos;

  for(int16_t j = 0; j < numLeds; j++) {
    uint16_t coord = getCoord(j,0)+stripeLength;
    if ((coord > stripeBeatPos) && (coord < stripeBeatPos+stripeLength)) {
      setStripeLed(j, stripeNum);
    }
  }
}


void doUDStripe(uint8_t stripeNum, uint16_t stripeLength, uint8_t stripeSpeed, uint8_t stripeCol, bool colChange) {
  int32_t stripeBeatPos = 0;
  if (stripeSpeed == 0) {
    stripeBeatPos = ((timeyInTime/16)+1000)%2048;
    if (beatCycle && stripeBeatPos > 1000) {
      setNewColorForStripey(stripeNum, stripeCol);
    }
  } else if (stripeSpeed == 1) {
    stripeBeatPos = ((timeyInTime/32)+1150)%2048;
    if (beatCycle && ((sixteenBeats%4) == 1)) {
      setNewColorForStripey(stripeNum, stripeCol);
    }
  } else {
    stripeBeatPos = ((timeyInTime/64)+910)%2048;
    if (beatCycle && colChange && ((sixteenBeats%4) == 1)) {
      setNewColorForStripey(stripeNum, stripeCol);
    } else if (beatCycle && ((sixteenBeats%8) == 5)) {
      setNewColorForStripey(stripeNum, stripeCol);
    }
  }

  stripeBeatPos = 2048-stripeBeatPos;

  for(int16_t j = 0; j < numLeds; j++) {
    uint16_t coord = (getCoord(j,1)/2)+stripeLength;
    if ((coord > stripeBeatPos) && (coord < stripeBeatPos+stripeLength)) {
      setStripeLed(j, stripeNum);
    }
  }
}


void doDUStripe(uint8_t stripeNum, uint16_t stripeLength, uint8_t stripeSpeed, uint8_t stripeCol) {
  int32_t stripeBeatPos = 0; 
  if (stripeSpeed == 0) {
    stripeBeatPos = ((timeyInTime/16)+1000)%2048;
    if (beatCycle && stripeBeatPos > 1000) {
      setNewColorForStripey(stripeNum, stripeCol);
    }
  } else if (stripeSpeed == 1) {
    stripeBeatPos = ((timeyInTime/32)+1150)%2048;
    if (beatCycle && ((sixteenBeats%4) == 1)) {
      setNewColorForStripey(stripeNum, stripeCol);
    }
  } else {
    stripeBeatPos = ((timeyInTime/64)+750)%2048;
    if (beatCycle && stripeBeatPos > 1850) {
      setNewColorForStripey(stripeNum, stripeCol);
    }
  }


  for(int16_t j = 0; j < numLeds; j++) {
    uint16_t coord = (getCoord(j,1)/2)+stripeLength;
    if ((coord > stripeBeatPos) && (coord < stripeBeatPos+stripeLength)) {
        setStripeLed(j, stripeNum);
    }
  }
}


void setStripeLed(uint16_t ledNum, uint8_t stripeNum) {
  /*
  if (stripeNum == 1) {
    setLedDirect(ledNum, stripe1r, stripe1g, stripe1b, stripe1w, false);
  } else if (stripeNum == 2) {
    setLedDirect(ledNum, stripe2r, stripe2g, stripe2b, stripe2w, false);
  } else if (stripeNum == 3) {
    setLedDirect(ledNum, stripe3r, stripe3g, stripe3b, stripe3w, false);
  } else {
    setLedDirect(ledNum, stripe4r, stripe4g, stripe4b, stripe4w, false);
  } */
  setLedDirect(ledNum, stripeCols[stripeNum][0], stripeCols[stripeNum][1], stripeCols[stripeNum][2], stripeCols[stripeNum][3], false);
}

void setNewColorForStripey(uint8_t stripeNum, uint8_t stripeCol) {
  if (stripeCol == 0) {
    return;
  } else if (stripeCol == 1) {
    stripeCols[stripeNum][0] = 0;
    stripeCols[stripeNum][1] = 0;
    stripeCols[stripeNum][2] = 0;
    stripeCols[stripeNum][3] = 100;
  } else {
    setGoodRandomColorVars();
    stripeCols[stripeNum][0] = goodColR;
    stripeCols[stripeNum][1] = goodColG;
    stripeCols[stripeNum][2] = goodColB;
    stripeCols[stripeNum][3] = goodColW;
  }  
}


