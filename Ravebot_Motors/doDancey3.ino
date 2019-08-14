
/* ***************************** Dance 2 Beat Moves *********************************** */
void doDance3BeatMoves() {
  if ((currentBar % 64) < 16) {
    if ((currentBar % 64) < 3) {
      moveLArm(120);
      moveRArm(120);
    } else if ((currentBar % 64) < 4) {
      moveLArm(60);
      moveRArm(60);
    } else {
      moveLArm(0);
      moveRArm(0);
    }
  } else if ((currentBar % 64) < 32) {
    if ((currentBar % 64) < 19) {
      moveLArm(-120);
      moveRArm(-120);
    } else if ((currentBar % 64) < 20) {
      moveLArm(-60);
      moveRArm(-60);
    } else {
      moveLArm(0);
      moveRArm(0);
    }
  } else if ((currentBar % 64) < 48) {
    if ((currentBar % 64) < 35) {
      moveLArm(120);
      moveRArm(120);
    } else if ((currentBar % 64) < 36) {
      moveLArm(60);
      moveRArm(60);
    } else {
      moveLArm(0);
      moveRArm(0);
    }
  } else {
    if ((currentBar % 64) < 51) {
      moveLArm(-120);
      moveRArm(-120);
    } else if ((currentBar % 64) < 52) {
      moveLArm(-60);
      moveRArm(-60);
    } else {
      moveLArm(0);
      moveRArm(0);
    }
  }
}

/* ******************************************* Dance 2 Constant Moves *********************************/

void dance3Movements() {
  if ((currentBar % 64) < 16) {
    if ((currentBar % 64) < 3) {
      leftWristPos(2);
      rightWristPos(2);
    } else if ((currentBar % 64) < 4) {
      rightArmMiddleRightElbowDown();
      leftArmMiddleLeftElbowDown();
      leftWristLRPer2Beat();
      rightWristLRPer2Beat();
    } else {
      leftWristLRPer2Beat();
      rightWristLRPer2Beat();
    }
  } else if ((currentBar % 64) < 32) {
    if ((currentBar % 64) < 19) {
      leftWristPos(2);
      rightWristPos(2);
    } else if ((currentBar % 64) < 20) {
      // rightArmMiddleRightElbowUp();
      // leftArmMiddleLeftElbowUp();
      rightArmMiddleRightElbowDown();
      leftArmMiddleLeftElbowDown();
      leftWristLRPer2Beat();
      rightWristLRPer2Beat();
    } else {
      leftWristLRPer2Beat();
      rightWristLRPer2Beat();
    }
  } else if ((currentBar % 64) < 48) {
    if ((currentBar % 64) < 35) {
      leftWristPos(2);
      rightWristPos(2);
    } else if ((currentBar % 64) < 36) {
      rightArmMiddleRightElbowDown();
      leftArmMiddleLeftElbowDown();
      leftWristLRPer2Beat();
      rightWristLRPer2Beat();
    } else {
      leftWristLRPer2Beat();
      rightWristLRPer2Beat();
    }
  } else {
    if ((currentBar % 64) < 51) {
      leftWristPos(2);
      rightWristPos(2);
    } else if ((currentBar % 64) < 52) {
      // rightArmMiddleRightElbowUp();
      // leftArmMiddleLeftElbowUp();
      rightArmMiddleRightElbowDown();
      leftArmMiddleLeftElbowDown();
      leftWristLRPer2Beat();
      rightWristLRPer2Beat();
    } else {
      leftWristLRPer2Beat();
      rightWristLRPer2Beat();
    }
  }
}



