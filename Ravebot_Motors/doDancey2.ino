
/* ***************************** Dance 2 Beat Moves *********************************** */
void doDance2BeatMoves() {
  if ((currentBar % 32) < 8) {
    if ((currentBar % 32) < 2) {
      moveLArm(20);
      moveRArm(20);
      rightArmUpRightElbowUp();
      leftArmUpLeftElbowUp();
      moveServoToPos(3, servos[3].servoCenter);
      moveServoToPos(5, servos[5].servoCenter);
      moveServoToPos(7, servos[7].servoCenter);
      moveServoToPos(9, servos[9].servoCenter);
    } else {
      leftWristLRPer2Beat();
      rightWristLRPer2Beat();
      openCloseClaw(32);
    }
  } else if ((currentBar % 32) < 16) {
    if ((currentBar % 32) < 18) {
      moveLArm(-20);
      moveRArm(-20);
      rightArmDownRightElbowUp();
      leftArmDownLeftElbowUp();
      moveServoToPos(3, servos[3].servoCenter);
      moveServoToPos(5, servos[5].servoCenter);
      moveServoToPos(7, servos[7].servoCenter);
      moveServoToPos(9, servos[9].servoCenter);
    } else {
      leftWristLRPer2Beat();
      rightWristLRPer2Beat();
      openCloseClaw(32);
    }
  } else if ((currentBar % 32) < 24) {
    if ((currentBar % 32) < 26) {
      moveLArm(20);
      moveRArm(20);
      rightArmUpRightElbowUp();
      leftArmUpLeftElbowUp();
      moveServoToPos(3, servos[3].servoCenter);
      moveServoToPos(5, servos[5].servoCenter);
      moveServoToPos(7, servos[7].servoCenter);
      moveServoToPos(9, servos[9].servoCenter);
    } else {
      leftWristLRPer2Beat();
      rightWristLRPer2Beat();
      openCloseClaw(32);
    }
  } else {
    if ((currentBar % 32) < 34) {
      moveLArm(-20);
      moveRArm(-20);
      rightArmDownRightElbowUp();
      leftArmDownLeftElbowUp();
      moveServoToPos(3, servos[3].servoCenter);
      moveServoToPos(5, servos[5].servoCenter);
      moveServoToPos(7, servos[7].servoCenter);
      moveServoToPos(9, servos[9].servoCenter);
    } else {
      leftWristLRPer2Beat();
      rightWristLRPer2Beat();
      openCloseClaw(32);
    }
  }
}


