
/* ***************************** Dance 2 Beat Moves *********************************** */

/* If you come back to this there are bugs, look at dance 3 - we moveLArm to 0 in the else and lifts are too short */

void doDance2BeatMoves() {
  if ((currentBar % 32) < 8) {
    if ((currentBar % 32) < 2) {
      moveLArm(20);
      moveRArm(20);
    } else if ((currentBar % 32) < 3) {
      moveLArm(20);
      moveRArm(20);
      rightArmUpRightElbowUp();
      leftArmUpLeftElbowUp();
      leftWristLRPer2Beat();
      rightWristLRPer2Beat();
    } else {
      leftWristLRPer2Beat();
      rightWristLRPer2Beat();
      // openCloseClaw(32);
    }
  } else if ((currentBar % 32) < 16) {
    if ((currentBar % 32) < 10) {
      moveLArm(-20);
      moveRArm(-20);
    } else if ((currentBar % 32) < 11) {
      moveLArm(-20);
      moveRArm(-20);
      rightArmMiddleRightElbowUp();
      leftArmMiddleLeftElbowUp();
      leftWristLRPer2Beat();
      rightWristLRPer2Beat();
    } else {
      leftWristLRPer2Beat();
      rightWristLRPer2Beat();
      // openCloseClaw(32);
    }
  } else if ((currentBar % 32) < 24) {
    if ((currentBar % 32) < 18) {
      moveLArm(20);
      moveRArm(20);
    } else if ((currentBar % 32) < 19) {
      moveLArm(20);
      moveRArm(20);
      rightArmUpRightElbowUp();
      leftArmUpLeftElbowUp();
      leftWristLRPer2Beat();
      rightWristLRPer2Beat();
    } else {
      leftWristLRPer2Beat();
      rightWristLRPer2Beat();
      // openCloseClaw(32);
    }
  } else {
    if ((currentBar % 32) < 26) {
      moveLArm(-20);
      moveRArm(-20);
    } else if ((currentBar % 32) < 27) {
      moveLArm(-20);
      moveRArm(-20);
      rightArmMiddleRightElbowUp();
      leftArmMiddleLeftElbowUp();
      leftWristLRPer2Beat();
      rightWristLRPer2Beat();
    } else {
      leftWristLRPer2Beat();
      rightWristLRPer2Beat();
      // openCloseClaw(32);
    }
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
  if ((currentBar % 2) == 0) {
    moveLeftWristUD(true, 32);
    moveRightWristUD(true, 32);
  } else {
    moveLeftWristUD(false, 32);
    moveRightWristUD(false, 32);
  }
}
void dance2Moves2() {
  if ((currentBar % 4) < 2) {
    moveLeftClaw(true, 32);
    moveRightClaw(true, 32);
  } else {
    moveLeftClaw(false, 32);
    moveRightClaw(false, 32);
  } 
}



