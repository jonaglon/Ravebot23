/* ***************************** Dance 1 Beat Moves *********************************** */

void doDance1BeatMoves() {
  //rightArmUpRightElbowDown();
  //leftArmUpLeftElbowDown();
  
  if ((currentBar % 8) == 0) {
    leftWristPos(0);
  } else if ((currentBar % 8) == 1) {
    leftWristPos(1);
  } else if ((currentBar % 8) == 2) {
    leftWristPos(2);
  } else if ((currentBar % 8) == 3) {
    leftWristPos(3);
  } else if ((currentBar % 8) == 4) {
    leftWristPos(4);
  } else if ((currentBar % 8) == 5) {
    leftWristPos(3);
  } else if ((currentBar % 8) == 6) {
    leftWristPos(2);
  } else if ((currentBar % 8) == 7) {
    leftWristPos(1);
  }; 
}



// JR TODO next - the wrists dont have nearly as much movement as the array says, maybe make dance pos 1 the extreme and do the middle, see if that makes all this work like you'd want.



void doDance1BeatMovesHELP() {
  if ((currentBar % 32) < 8) {
    dance1ElbowUpBeatMoves1();
  } else if ((currentBar % 32) < 16) {
    /*if ((currentBar % 32) == 8 && currentBeat == 0) { //moveLArm(-120); etc might work  */
    dance1ElbowUpBeatMoves2();
  } else if ((currentBar % 32) < 24) {
    dance1ElbowUpBeatMoves1 ();
  } else {
    dance1ElbowUpBeatMoves2();
  }
}

void dance1ElbowUpBeatMoves1() {
  rightArmUpRightElbowUp();
  leftArmUpLeftElbowUp();
  if ((currentBeat % 8) == 0) {
    leftWristPos (0);
    rightWristPos (0);
  } else if ((currentBeat % 8) == 2) {
    leftWristPos (1);
    rightWristPos (1);
  } else if ((currentBeat % 8) == 4) {
    leftWristPos (2);
    rightWristPos (2);
  } else if ((currentBeat % 8) == 6) {
    leftWristPos (3);
    rightWristPos(3);
  }
}

void dance1ElbowUpBeatMoves2() {
  rightArmUpRightElbowUp();
  leftArmUpLeftElbowUp();
  if ((currentBeat % 8) == 0) {
    leftWristPos (4);
    rightWristPos (4);
  } else if ((currentBeat % 8) == 2) {
    leftWristPos (3);
    rightWristPos (2);
  } else if ((currentBeat % 8) == 4) {
    leftWristPos (2);
    rightWristPos (2);
  } else if ((currentBeat % 8) == 6) {
    leftWristPos (1);
    rightWristPos(1);
  }
}

void dance1ElbowDownBeatMoves1() {
  rightArmUpRightElbowDown();
  leftArmUpLeftElbowDown();
  if ((currentBeat % 8) == 0) {
    leftWristPos (4);
    rightWristPos (4);
  } else if ((currentBeat % 8) == 2) {
    leftWristPos (3);
    rightWristPos (3);
  } else if ((currentBeat % 8) == 4) {
    leftWristPos (2);
    rightWristPos (2);
  } else if ((currentBeat % 8) == 6) {
    leftWristPos (1);
    rightWristPos(1);
  }
}

void dance1BeatMoves2() {
  if ((currentBeat % 4) == 0) {
    moveLeftClaw (false, 32);
    rightClaw (false, 32);
  } else if ((currentBeat % 4) == 2) {
    moveLeftClaw (true, 32);
    rightClaw (true, 32);
  }
}


/* ******************************************* Dance 1 Constant Moves *********************************/
void dance1Movements() {
  if ((currentBar % 32) < 8) {
    dance1Moves1();
  } else if ((currentBar % 32) < 16) {
    dance1Moves2();
  } else if ((currentBar % 32) < 24) {
    dance1Moves1();
  } else {
    dance1Moves2();
  }
}

void dance1Moves1() {
  if ((currentBar % 4) == 0) {
    moveleftWristPos(true, 32);
  } else if ((currentBar % 4) == 1) {
    moveleftWristPos(false, 32);
  } else if ((currentBar % 4) == 2) {
    moveRightWristLR(true, 32);
  } else {
    moveRightWristLR(false, 32);
  }
}

void dance1Moves2() {
  if ((currentBar % 4) == 0) {
    shakeHead(true, 32);
  } else if ((currentBar % 4) == 1) {
    shakeHead(false, 32);
  } else if ((currentBar % 4) == 2) {
    shakeHead(true, 32);
  } else {
    shakeHead(false, 32);
  }
}

