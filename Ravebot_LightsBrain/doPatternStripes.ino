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
uint8_t stripe4w = 255;

void doPatternStripes(uint8_t stripePattern) {
  // StripeSpeed is 0=fast,1=med,2=slow. Fast is 1 per beat
  /* I am a great stripe pattern! */
  if (stripePattern == 1) {
    doDUStripe(1, 1200, 2, 1);
    doUDStripe(2,  600, 1, 1, false);
    doRLStripe(3,  500, 2, 1);
    doLRStripe(4,  500, 2, 1);
  } else if (stripePattern == 2) {
    doRLStripe(3, 400, 1, 1);
    doLRStripe(4, 400, 1, 1);
    doDUStripe(1, 1200, 2, 1);
  } else  if (stripePattern == 2) {
    doUDStripe(3, 500, 0, 1, true);
  }
}

void doUDStripe(uint8_t stripeNum, uint16_t stripeLength, uint8_t stripeSpeed, uint8_t stripeCol, bool colChange) {
  int32_t stripeBeatPos = 0; 
  uint16_t offset = 0;
  if (stripeSpeed == 0) {
    offset=1000;
    stripeBeatPos = ((timeyInTime/16)+offset)%2048;
    if (beatCycle && stripeBeatPos > 1000) {
      setNewColorForStripey(stripeNum, stripeCol);
    }
  } else if (stripeSpeed == 1) {
    offset=1150;
    stripeBeatPos = ((timeyInTime/32)+offset)%2048;
    if (beatCycle && ((sixteenBeats%4) == 1)) {
      setNewColorForStripey(stripeNum, stripeCol);
    }
  } else {
    offset=910; // 750 slightly late;
    stripeBeatPos = ((timeyInTime/64)+offset)%2048;
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
  uint16_t offset = 0;
  if (stripeSpeed == 0) {
    offset=1000;
    stripeBeatPos = ((timeyInTime/16)+offset)%2048;
    if (beatCycle && stripeBeatPos > 1000) {
      setNewColorForStripey(stripeNum, stripeCol);
    }
  } else if (stripeSpeed == 1) {
    offset=1150;
    stripeBeatPos = ((timeyInTime/32)+offset)%2048;
    if (beatCycle && ((sixteenBeats%4) == 1)) {
      setNewColorForStripey(stripeNum, stripeCol);
    }
  } else {
    offset=750;
    stripeBeatPos = ((timeyInTime/64)+offset)%2048;
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

void doLRStripe(uint8_t stripeNum, uint16_t stripeLength, uint8_t stripeSpeed, uint8_t stripeCol) {
  int32_t stripeBeatPos = 0; 
  if (stripeSpeed == 0)
    stripeBeatPos = (timeyInTime/16)%2048;
  else if (stripeSpeed == 1)
    stripeBeatPos = (timeyInTime/32)%2048;
  else
    stripeBeatPos = (timeyInTime/64)%2048;

  if (beatCycle && stripeBeatPos == 0) {
    setNewColorForStripey(stripeNum, stripeCol);
  }

  for(int16_t j = 0; j < numLeds; j++) {
    uint16_t coord = getCoord(j,0)+stripeLength;
    if ((coord > stripeBeatPos) && (coord < stripeBeatPos+stripeLength)) {
      setStripeLed(j, stripeNum);
    }
  }
}

void doRLStripe(uint8_t stripeNum, uint16_t stripeLength, uint8_t stripeSpeed, uint8_t stripeCol) {
  int32_t stripeBeatPos = 0; 
  if (stripeSpeed == 0)
    stripeBeatPos = (timeyInTime/16)%2048;
  else if (stripeSpeed == 1)
    stripeBeatPos = (timeyInTime/32)%2048;
  else
    stripeBeatPos = (timeyInTime/64)%2048;

  if (beatCycle && stripeBeatPos == 0) {
    setNewColorForStripey(stripeNum, stripeCol);
  }

  stripeBeatPos = 2190-stripeLength-stripeBeatPos;

  for(int16_t j = 0; j < numLeds; j++) {
    uint16_t coord = getCoord(j,0)+stripeLength;
    if ((coord > stripeBeatPos) && (coord < stripeBeatPos+stripeLength)) {
      setStripeLed(j, stripeNum);
    }
  }
}

void setStripeLed(uint16_t ledNum, uint8_t stripeNum) {
  if (stripeNum == 1) {
    setLedDirect(ledNum, stripe1r, stripe1g, stripe1b, stripe1w, false);
  } else if (stripeNum == 2) {
    setLedDirect(ledNum, stripe2r, stripe2g, stripe2b, stripe2w, false);
  } else if (stripeNum == 3) {
    setLedDirect(ledNum, stripe3r, stripe3g, stripe3b, stripe3w, false);
  } else {
    setLedDirect(ledNum, stripe4r, stripe4g, stripe4b, stripe4w, false);
  }
}

void setNewColorForStripey(uint8_t stripeNum, uint8_t stripeCol) {
  uint8_t stripeR = 0;
  uint8_t stripeG = 0;
  uint8_t stripeB = 0;  
  uint8_t stripeW = 0;  
  
  if (stripeCol == 0) {
    stripeR = 0;
    stripeG = 0;
    stripeB = 0;
    stripeW = 100;
  } else {
    setGoodRandomColorVars();
    stripeR = goodColR;
    stripeG = goodColG;
    stripeB = goodColB;
    stripeW = goodColW;
  }  

  if (stripeNum == 1) {
    stripe1r = stripeR;
    stripe1g = stripeG;
    stripe1b = stripeB;
    stripe1w = stripeW;
  } else if (stripeNum == 2) {
    stripe2r = stripeR;
    stripe2g = stripeG;
    stripe2b = stripeB;
    stripe2w = stripeW;
  } else if (stripeNum == 3) {
    stripe3r = stripeR;
    stripe3g = stripeG;
    stripe3b = stripeB;
    stripe3w = stripeW;
  } else if (stripeNum == 4) {
    stripe4r = stripeR;
    stripe4g = stripeG;
    stripe4b = stripeB;
    stripe4w = stripeW;
  }
}


