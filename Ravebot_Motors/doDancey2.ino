
/* ***************************** Dance 2 Beat Moves *********************************** */
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
      openCloseClaw(32);
    }
  } else if ((currentBar % 32) < 16) {
    if ((currentBar % 32) < 10) {
      moveLArm(-20);
      moveRArm(-20);
    } else if ((currentBar % 32) < 11) {
      moveLArm(-20);
      moveRArm(-20);
      rightArmDownRightElbowUp();
      leftArmDownLeftElbowUp();
      leftWristLRPer2Beat();
      rightWristLRPer2Beat();
    } else {
      leftWristLRPer2Beat();
      rightWristLRPer2Beat();
      openCloseClaw(32);
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
      openCloseClaw(32);
    }
  } else {
    if ((currentBar % 32) < 26) {
      moveLArm(-20);
      moveRArm(-20);
    } else if ((currentBar % 32) < 27) {
      moveLArm(-20);
      moveRArm(-20);
      rightArmDownRightElbowUp();
      leftArmDownLeftElbowUp();
      leftWristLRPer2Beat();
      rightWristLRPer2Beat();
    } else {
      leftWristLRPer2Beat();
      rightWristLRPer2Beat();
      openCloseClaw(32);
    }
  }
}


