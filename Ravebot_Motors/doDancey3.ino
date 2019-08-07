
/* ***************************** Dance 2 Beat Moves *********************************** */
void doDance3BeatMoves() {
  if ((currentBar % 64) < 16) {
    if ((currentBar % 64) < 3) {
      moveLArm(120);
      moveRArm(120);
    } else if ((currentBar % 64) < 4) {
      moveLArm(60);
      moveRArm(60);
      rightArmUpRightElbowUp();
      leftArmUpLeftElbowUp();      
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
      rightArmDownRightElbowUp();
      leftArmDownLeftElbowUp();
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
      rightArmUpRightElbowUp();
      leftArmUpLeftElbowUp();      
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
      rightArmDownRightElbowUp();
      leftArmDownLeftElbowUp();
    } else {
      moveLArm(0);
      moveRArm(0);
    }
  }
}


