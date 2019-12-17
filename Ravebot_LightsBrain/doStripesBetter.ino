
// Urgh, here again. Really want a 4 stripes either way pattern which performs better than the first. It's a good pattern so worth fighting to get right motherfucker.
uint8_t stripe1r;
uint8_t stripe1g;
uint8_t stripe1b;
uint8_t stripe1w;

void doStripes2() {
  doLRStripe(800, 1);
  
}

void doLRStripe(uint16_t stripeLength, uint8_t stripeSpeed) {

  uint32_t stripe1Start = 0;
  uint32_t stripe1End = stripeLength;
  uint32_t stripeBeatPos = 0; 
  if (stripeSpeed == 0)
    stripeBeatPos = (timeyInTime/16)%2048;
  else if (stripeSpeed == 1)
    stripeBeatPos = (timeyInTime/32)%2048;
  else
    stripeBeatPos = (timeyInTime/64)%2048;

  if (beatCycle && stripeBeatPos == 0) {
    setNewColorForStripey(1);
  }

  for(int16_t j = 0; j < numLeds; j++) {
    uint16_t coord = getCoord(j,0)+stripeLength;
    if ((coord > stripeBeatPos+stripe1Start) && (coord < stripeBeatPos+stripe1End)) {
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


