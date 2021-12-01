uint8_t incomingByte;
uint8_t note;
uint8_t velocity;
int16_t channel = 1;
int16_t noteDown = LOW;
int16_t state=0;  // state machine variable 0 = command waiting : 1 = note waitin : 2 = velocity waiting

// Receive midi from ableton
void listenToAbleton() {

  if (beatTestMode)
  {
    doFakeBeatMessageFromAbleton();
    return;
  }

  while (Serial.available() > 0) {
    incomingByte = Serial.read();
    switch (state) {
    case 0:
      // look for as status-byte, our channel, note on
      if (incomingByte== (144 | channel)) { 
        state=1;
      }
      // look for as status-byte, our channel, note off
      if (incomingByte== (128 | channel)) { 
        state=1;
      }

    case 1:
      // get the note to play or stop
      if (incomingByte < 128) {
        note=incomingByte;
        state=2; 
      }
      else {
        state = 0;  // reset state machine as this should be a note number
      }
      break;

    case 2:
      // get the velocity
      if (incomingByte < 128) {
        processMessageFromAbleton(note, incomingByte, noteDown);
      }
      state = 0;  // reset state machine to start            
    }
  }
}

void setBeatTimes() {
  lastBeatLength = timey-lastBeatTime; 
  lastBeatTime = timey;
  totalBeats++;
}

void processMessageFromAbleton(uint8_t note, uint8_t velocity, int16_t down) {
  if ((note>=24 && note<88) && (velocity == 100)) {
    sixteenBeats = note - 24; // from 0 to 63 

    setBeatTimes();
    
    sendBeatToMega();

    beatCycle = true;
    
    if (dropCountdown != 0)
      dropCountdown--;

    if ((sixteenBeats % 4) == 0) {
      if (testMode) {
        Serial.print("New bar: ");
        Serial.print(currentBar);
        Serial.print("  16:");
        Serial.println(sixteenBeats);
      }
      // This is the beginning of a new bar, might need to end a mix or start a drop countdown
      currentBar++;
      mixCurrentBar++;
      percentThroughBeat=0;
      checkForDropCountdownStart();
    }
    else if ((sixteenBeats % 4) == 2) 
    {
      checkForMixStart();
    }    
    else if ((sixteenBeats % 4) == 3) 
    {
      checkForMixEnd();
    }    
    if (currentlyMixing) {
      setPercentThroughMix();
      doMixing();
    }
  }
}

void checkForMixStart() {
  if (currentBar == nextMixStart-1) {
      startNewMix();
  }
}

void checkForMixEnd() {
  if (currentBar == nextMixStart + nextMixDuration -1)
  {
    endMixAndPickNewTune();
  }
}

void checkForDropCountdownStart() {
  if (currentBar+4 == currentTune.drop)
    dropCountdown = 16;
}

/* Below is the fake beat control code */
uint32_t nextBeat = 0;

void doFakeBeatMessageFromAbleton() {
  if (timey > nextBeat) {
    processMessageFromAbleton(((fakeBeatCount+2)%16)+24, 100, 0);
    nextBeat = timey+fakeBeatLengh;
    fakeBeatCount++;
  }
}
