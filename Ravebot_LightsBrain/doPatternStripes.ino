

uint8_t stripeCols[8][4] = {{255, 0, 0, 0}, {0, 255, 0, 0}, {0, 0, 255, 0}, {0, 0, 0, 255}, {255, 0, 0, 0}, {0, 255, 0, 0}, {0, 0, 255, 0}, {0, 0, 0, 255}};

void doPatternStripes(uint8_t stripePattern) {
  // StripeSpeed is 0=fast,1=med,2=slow. Fast is 1 per beat

  if (stripePattern == 0) {    
    if ((sixteenBeats > 3) && (sixteenBeats < 12)) {
      doRLStripe(0, 1024, 2, 3);
      doLRStripe(1, 1024, 1, 3);
      doLRStripe(2,  768, 2, 0);
      doRLStripe(3,  768, 2, 3);
      doRLStripe(4,  512, 2, 3);
      doLRStripe(5,  512, 1, 3);
      doLRStripe(6,  256, 2, 3);
      doRLStripe(7,  256, 2, 3);
    }
    if ((sixteenBeats < 1) || (sixteenBeats > 10)) {
      doUDStripe(1,  768, 0, 3);
      doUDStripe(2,  512, 0, 1);
      doUDStripe(3,  256, 1, 3);
    }
  } else if (stripePattern == 1) {
    doUDStripe(0, 512, 2, 3);
    doDUStripe(1, 256, 1, 3);
    doDUStripe(2, 256, 2, 3);
    if (sixteenBeats < 8) {
      doLRStripe(3, 128, 2, 3);
      doDUStripe(4, 128, 1, 3);
    } else {
      doRLStripe(5, 128, 2, 3);
    }
  } else if (stripePattern == 2) {
    doUDStripe(0, 512, 2, 3);
    if ((sixteenBeats > 4) && (sixteenBeats < 10)) {
       doLRStripe(1, 540, 2, 3);
    }
    doUDStripe(1, 768, 1, 3);
    doUDStripe(2, 512, 1, 1);
    doUDStripe(3, 256, 1, 3);
  } else if (stripePattern == 3) {
    doUDStripe(1,  768, 2, 3);
    doUDStripe(2,  512, 2, 1);
    doUDStripe(3,  256, 2, 3);
    doDUStripe(4, 512, 2, 3);
    doDUStripe(5, 256, 1, 3);
    if ((sixteenBeats > 4) && (sixteenBeats < 10)) {
       doLRStripe(6, 256, 2, 3);
       doRLStripe(7, 256, 2, 3);
    }
  }
}

void doStripeOverlay(uint8_t stripeOverlay) {
  // StripeSpeed is 0=fast,1=med,2=slow. Fast is 1 per beat

  if (stripeOverlay == 0) {    
    if ((sixteenBeats < 2) || (sixteenBeats > 10)) {
      doUDStripe(7, 256, 1, 0);
      doLRStripe(7, 256, 2, 3);
    }
  } else if (stripeOverlay == 1) {
    if (sixteenBeats > 9) {
      doRLStripe(6, 256, 2, 3);
      doLRStripe(7, 256, 2, 3);
    }
  } else if (stripeOverlay == 2) {
    if ((sixteenBeats < 2) || (sixteenBeats > 9)) {
      doUDStripe(6, 512, 1, 3);
      doUDStripe(7, 256, 1, 3);
    }
  } else if (stripeOverlay == 3) {
    if ((sixteenBeats < 2) || (sixteenBeats > 10)) {
      doUDStripe(7, 256, 1, 1);
      doLRStripe(7, 256, 2, 1);
    }
  }
}


void doDUStripe(uint8_t stripeNum, uint16_t stripeLength, uint8_t stripeSpeed, uint8_t stripeCol) {
  int32_t stripeBeatPos = 0; 
  if (stripeSpeed == 0) {
    stripeBeatPos = ((timeyInTime/32)+1400)%2048;
    if (beatCycle && ((sixteenBeats%4) == 2)) {
      setNewColorForStripey(stripeNum, stripeCol);
    }
  } else if (stripeSpeed == 1) {
    stripeBeatPos = ((timeyInTime/64)+900)%2048;
    if (beatCycle && ((sixteenBeats%8) == 4)) {
      setNewColorForStripey(stripeNum, stripeCol);
    }
  } else {
    stripeBeatPos = ((timeyInTime/128)+860)%2048;
    if (beatCycle && sixteenBeats==9) {
      setNewColorForStripey(stripeNum, stripeCol);
    }
  }

  for(int16_t j = 0; j < numLeds; j++) {
    uint16_t coord = getCoord(j,1);
    if ((coord < stripeBeatPos) && (coord > stripeBeatPos-stripeLength)) {
      setStripeLed(j, stripeNum);
    }
  }
}

void doUDStripe(uint8_t stripeNum, uint16_t stripeLength, uint8_t stripeSpeed, uint8_t stripeCol) {
  int32_t stripeBeatPos = 0;
  if (stripeSpeed == 0) {
    stripeBeatPos = ((timeyInTime/32)+1500)%2048;
    if (beatCycle && ((sixteenBeats%4) == 1)) {
      setNewColorForStripey(stripeNum, stripeCol);
    }
  } else if (stripeSpeed == 1) {
    stripeBeatPos = ((timeyInTime/64)+900)%2048;
    if (beatCycle && ((sixteenBeats%8) == 4)) {
      setNewColorForStripey(stripeNum, stripeCol);
    }
  } else {
    stripeBeatPos = ((timeyInTime/128)+860)%2048;  // increase for earlier
    if (beatCycle && sixteenBeats==8) {
      setNewColorForStripey(stripeNum, stripeCol);
    }
  }

  stripeBeatPos = 2048-stripeBeatPos;

  for(int16_t j = 0; j < numLeds; j++) {
    uint16_t coord = getCoord(j,1)+500;
    if ((coord > stripeBeatPos) && (coord < stripeBeatPos+stripeLength)) {
      setStripeLed(j, stripeNum);
    }
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


