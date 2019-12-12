// JR TODO - what the actual f is going on in here??! 

void doPatternTrains() {
  tubesInTime();
  bigSpeakerInTime();
}

int numLedsTube = 88;
int numLedsPerBeat=22;
int beatCompNum = 16384/numLedsPerBeat; // this is the 16384 beat% / those 30 leds. (182/546 - for 30/90)
void tubesInTime() {
  for(int j = 0; j < numLedsTube; j++) {
    int distanceFromBeat = quickAbsolute(((j%numLedsPerBeat)*beatCompNum)-percentThroughBeat);

    int ledColour = 255 - (distanceFromBeat/10);
    if (ledColour < 0)
      ledColour = 0;

    setSectionLed(13, j, ledColour, 0, 0, 0);
    setSectionLed(14, j, 0, ledColour, 0, 0);
    setSectionLed(15, j, 0, 0, ledColour, 0);
    setSectionLed(16, j, 0, 0, 0, ledColour);
  }
}

void bigSpeakerInTime() {
  // Not in time you drongo.
  // int thisLed = (timeyInTime/811)%203;
  // setSectionLed(0, thisLed, 255, 0, 0, 0);

  int thisLed = percentThroughBeat / 81;
  setSectionLed(0, thisLed, 255, 0, 0, 0);
}

int numLedsPerBeat2=51;
int beatCompNum2 = 16384/numLedsPerBeat2; // this is the 16384 beat% / those 30 leds. (182/546 - for 30/90)
void bigSpeakerInTimeOLD() {

  int sixteenBeatPos = (sixteenBeats/2) % 4;

  for(int j = 0; j < 204; j++) {
    int distanceFromBeat = quickAbsolute(((j%numLedsPerBeat2)*beatCompNum2)-percentThroughBeat);

    int ledColour = 255 - (distanceFromBeat/10);
    if (ledColour < 0)
      ledColour = 0;
    
    if (sixteenBeatPos == 0) {
      setSectionLed(0, j, ledColour, 0, 0, 0);
    } else if (sixteenBeatPos == 1) {
      setSectionLed(0, j, 0, ledColour, 0, 0);
    } else if (sixteenBeatPos == 2) {
      setSectionLed(0, j, 0, 0, ledColour, 0);
    } else {
      setSectionLed(0, j, 0, 0, 0, ledColour);
    }
  }  
}

/*
  // 00 bottomRing
  // 01 bigHeart
  // 02 smallHeart
  // 03 underarm left
  // 04 overarm left
  // 05 eyeLeft 
  // 06 rightEye
  // 07 mouth
  // 08 tape
  // 09 tuner 
  // 10 indicator
  // 11 underArm right
  // 12 overArm right
  // 13 tubeBottomright
  // 14 tubeBottomleft
  // 15 tubeTopleft
  // 16 tubeTopright
  // 17 port left
  // 18 port right 
  
int ledSections[20] = {
  0,     // 0  bottom ring *
  203,   // 1  big heart
  378,   // 2  small heart
  463,   // 3 underarm left
  482,   // 4 overarm left
  506,   // 5  eye left
  599,   // 6  eye right
  692,   // 7  mouth
  710,   // 8  tape
  744,   // 9  tuner *
  770,   // 10 indiciator *
  774,   // 11 underarm right
  797,   // 12 overarm right
  825,   // 13 tube bottomright *
  911,   // 14 tube bottomleft *
  1001,  // 15 tube topleft *
  1090,  // 16 tube topright * starred sections are shifted and / or reversed
  1180,  // 17 port left
  1302,  // 18 port right
  1442
};  
  */
