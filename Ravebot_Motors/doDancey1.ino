/* ***************************** Dance 1 Beat Moves *********************************** */

void doDance1BeatMoves() {
  if ((currentBar % 64) < 16) {
    rightArmUpRightElbowDown();
    leftArmUpLeftElbowDown();
    leftWristLRStepsPer8Beat();
    rightWristLRStepsPer8Beat();
  } else if ((currentBar % 64) < 32) {
    rightArmUpRightElbowDown();
    leftArmUpLeftElbowDown();
    rightWristLRPer4Beat();
    leftWristLRPer4Beat();
  } else if ((currentBar % 64) < 48) {
    rightArmUpRightElbowUp();
    leftArmUpLeftElbowUp();
    leftWristLRStepsPer8Beat();
    rightWristLRStepsPer8Beat();
  } else {
    rightArmUpRightElbowUp();
    leftArmUpLeftElbowUp();
    rightWristLRPer4Beat();
    leftWristLRPer4Beat();
  };
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

