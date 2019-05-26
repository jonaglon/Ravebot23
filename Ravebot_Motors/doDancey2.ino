
/* ***************************** Dance 2 Beat Moves *********************************** */
void doDance2BeatMoves() {
  if ((currentBar % 32) < 8) {
    if (currentBar == 0 && currentBeat == 0) {
      // go to move 1 initial positions0
      moveLArm(100);
      moveRArm(100);
      rightArmUpRightElbowUp();
      leftArmUpLeftElbowUp();
    }
    dance2BeatMoves1();
  } else if ((currentBar % 32) < 16) {
    if ((currentBar % 32) == 8 && currentBeat == 0) {
      // go to move 2 initial positions
      rightArmUpRightElbowUp();
      leftArmUpLeftElbowUp();
    }
    openCloseClaw(32);
  } else if ((currentBar % 32) < 24) {
    if ((currentBar % 32) == 16 && currentBeat == 0) {
      // go to move 3 initial positions
      rightArmUpRightElbowDown();
      leftArmUpLeftElbowDown();
    }
    dance2BeatMoves1();
  } else {
    if ((currentBar % 32) == 24 && currentBeat == 0) {
      // go to move 4 initial positions
      rightArmUpRightElbowDown();
      leftArmUpLeftElbowDown();
    }
    openCloseClaw(32);
  }
}

void dance2BeatMoves1() {
  if ((currentBeat % 8) == 0) {
    leftWristLR (true);
    rightWristLR (false);
  } else if ((currentBeat % 8) == 2) {
    leftWristLR (false);
    rightWristLR (true);
  } else if ((currentBeat % 8) == 4) {
    leftWristLR (true);
    rightWristLR (false);
  } else if ((currentBeat % 8) == 6) {
    leftWristLR(false);
    rightWristLR(true);
  }
}

  
/* ******************************************* Dance 2 Constant Moves *********************************/
void dance2Movements() {
  if ((currentBar % 32) < 8) {
    dance2Moves1();
  } else if ((currentBar % 32) < 16) {
    dance2Moves2();
  } else if ((currentBar % 32) < 24) {
    dance2Moves1();
  } else {
    dance2Moves2();
  }
}

void dance2Moves1() {
  if ((currentBar % 4) == 0) {
    moveLeftWristUD(true, 32);
  } else if ((currentBar % 4) == 1) {
    moveLeftWristUD(false, 32);
  } else if ((currentBar % 4) == 2) {
    moveRightWristUD(true, 32);
  } else {
    moveRightWristUD(false, 32);
  }
}
void dance2Moves2() {
  if ((currentBar % 4) == 0) {
    moveLeftClaw(true, 32);
  } else if ((currentBar % 4) == 1) {
    moveLeftClaw(false, 32);
  } else if ((currentBar % 4) == 2) {
    moveLeftClaw(true, 32);
  } else {
    moveLeftClaw(false, 32);
  }
}

