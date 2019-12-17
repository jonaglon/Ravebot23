uint8_t stripe1r = 255;
uint8_t stripe1g = 0;
uint8_t stripe1b = 0;
uint8_t stripe1w = 0;

void doPatternStripes() {
  // StripeSpeed is 0=fast,1=med,2=slow. Fast is 1 per beat
  doUDStripe(1200, 1, 1);
}

void doUDStripe(uint16_t stripeLength, uint8_t stripeSpeed, uint8_t stripeCol) {
  int32_t stripeBeatPos = 0; 
  uint16_t offset = 0;
  if (stripeSpeed == 0) {
    offset=1000;
    stripeBeatPos = ((timeyInTime/16)+offset)%2048;
    if (beatCycle && stripeBeatPos > 1000) {
      setNewColorForStripey(stripeCol);
    }
  } else if (stripeSpeed == 1) {
    offset=1150;
    stripeBeatPos = ((timeyInTime/32)+offset)%2048;
    if (beatCycle && stripeBeatPos > 1400) {
      setNewColorForStripey(stripeCol);
    }
  } else {
    offset=750;
    stripeBeatPos = ((timeyInTime/64)+offset)%2048;
    if (beatCycle && stripeBeatPos > 1850) {
      setNewColorForStripey(stripeCol);
    }
  }


  for(int16_t j = 0; j < numLeds; j++) {
    uint16_t coord = (getCoord(j,1)/2)+stripeLength;
    if ((coord > stripeBeatPos) && (coord < stripeBeatPos+stripeLength)) {
        setLedDirect(j, stripe1r, stripe1g, stripe1b, stripe1w, false);
    }
  }
}

void doLRStripe(uint16_t stripeLength, uint8_t stripeSpeed, uint8_t stripeCol) {
  int32_t stripeBeatPos = 0; 
  if (stripeSpeed == 0)
    stripeBeatPos = (timeyInTime/16)%2048;
  else if (stripeSpeed == 1)
    stripeBeatPos = (timeyInTime/32)%2048;
  else
    stripeBeatPos = (timeyInTime/64)%2048;

  if (beatCycle && stripeBeatPos == 0) {
    setNewColorForStripey(stripeCol);
  }

  for(int16_t j = 0; j < numLeds; j++) {
    uint16_t coord = getCoord(j,0)+stripeLength;
    if ((coord > stripeBeatPos) && (coord < stripeBeatPos+stripeLength)) {
        setLedDirect(j, stripe1r, stripe1g, stripe1b, stripe1w, false);
    }
  }
}

void doRLStripe(uint16_t stripeLength, uint8_t stripeSpeed, uint8_t stripeCol) {
  int32_t stripeBeatPos = 0; 
  if (stripeSpeed == 0)
    stripeBeatPos = (timeyInTime/16)%2048;
  else if (stripeSpeed == 1)
    stripeBeatPos = (timeyInTime/32)%2048;
  else
    stripeBeatPos = (timeyInTime/64)%2048;

  if (beatCycle && stripeBeatPos == 0) {
    setNewColorForStripey(stripeCol);
  }

  stripeBeatPos = 2190-stripeLength-stripeBeatPos;

  for(int16_t j = 0; j < numLeds; j++) {
    uint16_t coord = getCoord(j,0)+stripeLength;
    if ((coord > stripeBeatPos) && (coord < stripeBeatPos+stripeLength)) {
        setLedDirect(j, stripe1r, stripe1g, stripe1b, stripe1w, false);
    }
  }
}


void setNewColorForStripey(uint8_t stripeCol) {
  if (stripeCol == 0) {
    stripe1r = 0;
    stripe1g = 0;
    stripe1b = 0;
    stripe1w = 100;
  } else {
    setGoodRandomColorVars();
    stripe1r = goodColR;
    stripe1g = goodColG;
    stripe1b = goodColB;
    stripe1w = goodColW;
  }  
}


