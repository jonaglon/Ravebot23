/* ***************************** Dance 1 Beat Moves *********************************** */
void doDance1BeatMoves() {
  if ((currentBar % 32) < 8) {
    if (currentBar == 0 && currentBeat == 0) {
      // go to move 1 initial positions0
      //moveLArm(120);
      //moveRArm(120);
    }
    dance1BeatMoves1();
  } else if ((currentBar % 32) < 16) {
    /*if ((currentBar % 32) == 8 && currentBeat == 0) {
      // go to move 2 initial positions
      moveLArm(-120);
      moveRArm(-120);
      rightArmDownRightElbowUp();
      leftArmDownLeftElbowUp();
    }*/
    dance1BeatMoves1();
  } else if ((currentBar % 32) < 24) {
    /*if ((currentBar % 32) == 16 && currentBeat == 0) {
      // go to move 3 initial positions
      moveLArm(120);
      moveRArm(120);
      rightArmUpRightElbowDown();
      leftArmUpLeftElbowDown();
    }*/
    dance1BeatMoves1();
  } else {
    /*if ((currentBar % 32) == 24 && currentBeat == 0) {
      // go to move 4 initial positions
      moveLArm(-120);
      moveRArm(-120);
      rightArmDownRightElbowDown();
      leftArmDownLeftElbowDown();
    }*/
    dance1BeatMoves1();
  }
}

void dance1BeatMoves1() {
  if ((currentBeat % 8) == 0) {
    //leftWristPos (1);
    //rightWristPos (1);
    rightArmUpRightElbowUp();
    leftArmUpLeftElbowUp();
  } else if ((currentBeat % 8) == 2) {
    //leftWristPos (0);
    //rightWristPos (0);
    leftElbowPos(2);
    rightElbowPos(2);
  } else if ((currentBeat % 8) == 4) {
    //leftWristPos (3);
    //rightWristPos (3);
    rightArmUpRightElbowUp();
    leftArmUpLeftElbowUp();
  } else if ((currentBeat % 8) == 6) {
    //leftWristPos (0);
    //rightWristPos(0);
    leftElbowPos(2);
    rightElbowPos(2);
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

