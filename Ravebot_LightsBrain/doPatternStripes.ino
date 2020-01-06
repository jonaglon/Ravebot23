

uint8_t stripeCols[8][4] = {{255, 0, 0, 0}, {0, 255, 0, 0}, {0, 0, 255, 0}, {0, 0, 0, 255}, {255, 0, 0, 0}, {0, 255, 0, 0}, {0, 0, 255, 0}, {0, 0, 0, 255}};

void doPatternStripes(uint8_t stripePattern) {
  // StripeSpeed is 0=fast,1=med,2=slow. Fast is 1 per beat

  if (stripePattern == 1) {    
    doRLStripe(0, 1080, 2, 0);
    doLRStripe(0, 1080, 2, 3);
    doRLStripe(1,  810, 2, 0);
    doLRStripe(1,  810, 2, 3);
    doRLStripe(2,  540, 1, 0);
    doLRStripe(2,  540, 1, 3);
    doRLStripe(3,  270, 2, 0);
    doLRStripe(3,  270, 2, 3);
  } else if (stripePattern == 2) {
    if (sixteenBeats < 8)
      doLRStripe(1, 100, 0, 3);
    else
      doRLStripe(2, 100, 0, 2);
    doUDStripe(3, 800, 2, 3, false);
    doDUStripe(0, 800, 2, 3);
  } else  if (stripePattern == 2) {
    doUDStripe(3, 500, 2, 3, true);
  }
}


void doRLStripe(uint8_t stripeNum, uint16_t stripeLength, uint8_t stripeSpeed, uint8_t stripeCol) {
  int32_t stripeBeatPos = 0; 
  if (stripeSpeed == 0) {
    stripeBeatPos = ((timeyInTime/16)+1100)%2048;
  } else if (stripeSpeed == 1) {
    stripeBeatPos = ((timeyInTime/32)+1950)%2048;
  } else {
    stripeBeatPos = ((timeyInTime/64)+1190)%2048;
  }

  if (beatCycle && stripeBeatPos < 450) {
    setNewColorForStripey(stripeNum, stripeCol);
  }
  
  stripeBeatPos = 2048-stripeBeatPos;

  for(int16_t j = 0; j < numLeds; j++) {
    uint16_t coord = getCoord(j,0)+1024;
    if ((coord > stripeBeatPos) && (coord < stripeBeatPos+stripeLength)) {
      setStripeLed(j, stripeNum);
    }
  }
}

void doLRStripe(uint8_t stripeNum, uint16_t stripeLength, uint8_t stripeSpeed, uint8_t stripeCol) {
  int32_t stripeBeatPos = 0; 
  if (stripeSpeed == 0) { 
    stripeBeatPos = ((timeyInTime/16)+652)%2048;
  } else if (stripeSpeed == 1) {
    stripeBeatPos = ((timeyInTime/32)+1512)%2048;
  } else {
    stripeBeatPos = ((timeyInTime/64)+750)%2048;
  }

  if (beatCycle && stripeBeatPos > 1600) {
    setNewColorForStripey(stripeNum, stripeCol);
  }

  for(int16_t j = 0; j < numLeds; j++) {
    uint16_t coord = getCoord(j,0);
    if ((coord < stripeBeatPos) && (coord > stripeBeatPos-stripeLength)) {
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
  setLedDirect(ledNum, stripeCols[stripeNum][0], stripeCols[stripeNum][1], stripeCols[stripeNum][2], stripeCols[stripeNum][3], false);
}

void setNewColorForStripey(uint8_t stripeNum, uint8_t stripeCol) {
  if (stripeCol == 0) {
    return;
  } else if (stripeCol == 1) {
    stripeCols[stripeNum][0] = 0;
    stripeCols[stripeNum][1] = 0;
    stripeCols[stripeNum][2] = 0;
    stripeCols[stripeNum][3] = 0;
  } else if (stripeCol == 2) {
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


