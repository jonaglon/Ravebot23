// JR TODO - what the actual f is going on in here??! 



int16_t numLedsTube = 88;
int16_t numLedsPerBeat=22;
int16_t beatCompNum = 16384/numLedsPerBeat; // this is the 16384 beat% / those 30 leds. (182/546 - for 30/90)
void tubesInTime() {
  for(int16_t j = 0; j < numLedsTube; j++) {
    int32_t distanceFromBeat = quickAbsolute(((j%numLedsPerBeat)*beatCompNum)-percentThroughBeat);

    int16_t ledColour = 255 - (distanceFromBeat/10);
    if (ledColour < 0)
      ledColour = 0;

    setSectionLed(13, j, ledColour, 0, 0, 0);
    setSectionLed(14, j, 0, ledColour, 0, 0);
    setSectionLed(15, j, 0, 0, ledColour, 0);
    setSectionLed(16, j, 0, 0, 0, ledColour);
  }
}

void bigSpeakerThreeRevolvers() {
  int16_t thisLed1 = ((timeyInTime/512)-12)%203;
  int16_t thisLed2 = ((timeyInTime/512)+56)%203;
  int16_t thisLed3 = ((timeyInTime/512)+113)%203;

  setSectionLed(0, thisLed1, 0, 0, 0, 20);
  setSectionLed(0, thisLed1+1, 0, 0, 0, 40);
  setSectionLed(0, thisLed1+2, 0, 0, 0, 80);
  for(int8_t j = 3; j < 11; j++)
    setSectionLed(0, thisLed1+j, 0, 0, 0, 255);
  setSectionLed(0, thisLed1+11, 0, 0, 0, 80);
  setSectionLed(0, thisLed1+12, 0, 0, 0, 40);
  setSectionLed(0, thisLed1+13, 0, 0, 0, 20);
  
  setSectionLed(0, thisLed2, 0, 0, 0, 20);
  setSectionLed(0, thisLed2+1, 0, 0, 0, 40);
  setSectionLed(0, thisLed2+2, 0, 0, 0, 80);
  for(int8_t j = 3; j < 11; j++)
    setSectionLed(0, thisLed2+j, 0, 0, 0, 255);
  setSectionLed(0, thisLed2+11, 0, 0, 0, 80);
  setSectionLed(0, thisLed2+12, 0, 0, 0, 40);
  setSectionLed(0, thisLed2+13, 0, 0, 0, 20);
  
  setSectionLed(0, thisLed3, 0, 0, 0, 20);
  setSectionLed(0, thisLed3+1, 0, 0, 0, 40);
  setSectionLed(0, thisLed3+2, 0, 0, 0, 80);
  for(int8_t j = 3; j < 11; j++)
    setSectionLed(0, thisLed3+j, 0, 0, 0, 255);
  setSectionLed(0, thisLed3+11, 0, 0, 0, 80);
  setSectionLed(0, thisLed3+12, 0, 0, 0, 40);
  setSectionLed(0, thisLed3+13, 0, 0, 0, 20);
  
}

uint8_t r1 = 0;
uint8_t g1 = 0;
uint8_t b1 = 0;
uint8_t w1 = 0;
uint8_t r2 = 0;
uint8_t g2 = 0;
uint8_t b2 = 0;
uint8_t w2 = 0;
uint8_t r3 = 0;
uint8_t g3 = 0;
uint8_t b3 = 0;
uint8_t w3 = 0;
uint8_t r4 = 0;
uint8_t g4 = 0;
uint8_t b4 = 0;
uint8_t w4 = 0;
void bigSpeakerInTimeFourTings() {
  int16_t thisLed1 = ((timeyInTime/512)-12)%203;
  int16_t thisLed2 = ((timeyInTime/512)+39)%203;
  int16_t thisLed3 = ((timeyInTime/512)+89)%203;
  int16_t thisLed4 = ((timeyInTime/512)+139)%203;

  if (beatCycle) {
    setGoodRandomColorVars();
    r1 = goodColR; g1 = goodColG; b1 = goodColB; w1 = goodColW;
    setGoodRandomColorVars();
    r2 = goodColR; g2 = goodColG; b2 = goodColB; w2 = goodColW;
    setGoodRandomColorVars();
    r3 = goodColR; g3 = goodColG; b3 = goodColB; w3 = goodColW;
    setGoodRandomColorVars();
    r4 = goodColR; g4 = goodColG; b4 = goodColB; w4 = goodColW;
  }

  for(int8_t j = 0; j < 9; j++)
    setSectionLed(0, thisLed1+j, r1, g1, b1, w1);
  
  for(int8_t j = 0; j < 9; j++)
    setSectionLed(0, thisLed2+j, r2, g2, b2, w2);
  
  for(int8_t j = 0; j < 9; j++)
    setSectionLed(0, thisLed3+j, r3, g3, b3, w3);
  
  for(int8_t j = 0; j < 9; j++)
    setSectionLed(0, thisLed4+j, r4, g4, b4, w4);

}


