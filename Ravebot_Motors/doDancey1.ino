/* ***************************** Dance 1 Beat Moves *********************************** */
void doDance1BeatMoves() {
  if ((currentBar % 32) < 8) {
    dance1ElbowDownBeatMoves1();
  } else if ((currentBar % 32) < 16) {
    /*if ((currentBar % 32) == 8 && currentBeat == 0) {
      // go to move 2 initial positions - don't know if this'll work
      //moveLArm(-120);
      //moveRArm(-120);
    }*/
    dance1ElbowUpBeatMoves1();
  } else if ((currentBar % 32) < 24) {
    dance1ElbowDownBeatMoves1();
  } else {
    dance1ElbowUpBeatMoves1();
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

