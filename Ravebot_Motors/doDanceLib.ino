/*  
2 - L claw
3 - l wrist ud
4 - R elbow
5 - R wrist lr
6 - R claw increase to grab
7 - r wrist ud
8 - l elbow
9 - l wrist lr
10 - l new nod
11 - l new tilt
12 - l new shake  */

int numDances = 3;
int currentDance = 3;

/* ************** Dance Move Functions - Called Every Cycle ********************* */
void doDancing() {
  if (currentDance == 1)
    dance1Movements();
   else if (currentDance == 2)
    dance2Movements();
   else if (currentDance == 3)
    dance3Movements();
    
}

/* ************* Dance BEAT moves called by beat signal from the Due *************** */
void doBeatDanceMove() {
  if (robotManualMode || !robotSwitchedOn)
    return;

  if (currentDance == 1)
    doDance1BeatMoves();
  else if (currentDance == 2)
    doDance2BeatMoves();
  else if (currentDance == 3)
    doDance3BeatMoves();
}

void changeDance() {
  int newDanceNumber;
  
  while (newDanceNumber != currentDance)
    newDanceNumber = random(1, numDances+1);

  currentDance = newDanceNumber;
  sendDanceNumberToLights(currentDance);

  // JR TODO - remove me! Hardcodes the dance
  currentDance = 3;
  
}


/* ******************************************* Constant Dance Functions *************************** */

void moveleftWristPos (bool moveLeft, int delayo) {
  int doLeftMove = moveLeft ? -1 : 1;
  moveServoSoft(9, doLeftMove, delayo);
}

void moveRightWristLR (bool moveLeft, int delayo) {
  int doLeftMove = moveLeft ? -1 : 1;
  moveServoSoft(5, doLeftMove, delayo);
}

void moveLeftWristUD (bool moveLeft, int delayo) {
  int doLeftMove = moveLeft ? -1 : 1;
  moveServoSoft(3, doLeftMove, delayo);
}

void moveRightWristUD (bool moveLeft, int delayo) {
  int doLeftMove = moveLeft ? -1 : 1;
  moveServoSoft(7, doLeftMove, delayo);
}

void moveLeftClaw (bool moveLeft, int delayo) {
  int doLeftMove = moveLeft ? -1 : 1;
  moveServoSoft(2, doLeftMove, delayo);
}

void moveRightClaw (bool moveLeft, int delayo) {
  int doLeftMove = moveLeft ? -1 : 1;
  moveServoSoft(6, doLeftMove, delayo);
}

void shakeHead (bool shakeLeft, int delayo) {
  int doLeftMove = shakeLeft ? -1 : 1;
  moveServoSoft(12, doLeftMove, delayo);
}

void tiltHead (bool tiltLeft, int delayo) {
  int doLeftMove = tiltLeft ? -1 : 1;
  moveServoSoft(11, doLeftMove, delayo);
  
}


/************************** Dance beat move functions **************************/

/* CLAW */
void openCloseClaw(int speedy) {
  if ((currentBeat % 2) == 0) {
    leftClaw (false, speedy);
    rightClaw (false, speedy);
  } else {
    leftClaw (true, speedy);
    rightClaw (true, speedy);
  }
}

void leftClaw(bool moveLeft, int delayo) {
  if (moveLeft) {
    //moveServoToPos(2, servos[2].leftDancePos);
    moveServoToPosSoft(2, servos[2].leftDancePos);
  } else {
    moveServoToPosSoft(2, servos[2].rightDancePos);
  }
}

void rightClaw(bool moveLeft, int delayo) {
  if (moveLeft)
    moveServoToPosSoft(6, servos[6].leftDancePos);
  else
    moveServoToPosSoft(6, servos[6].rightDancePos);
}

/* Wristy */
void leftWristLRStepsPer8Beat() {
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

void rightWristLRStepsPer8Beat() {
  if ((currentBar % 8) == 0) {
    rightWristPos(0);
  } else if ((currentBar % 8) == 1) {
    rightWristPos(1);
  } else if ((currentBar % 8) == 2) {
    rightWristPos(2);
  } else if ((currentBar % 8) == 3) {
    rightWristPos(3);
  } else if ((currentBar % 8) == 4) {
    rightWristPos(4);
  } else if ((currentBar % 8) == 5) {
    rightWristPos(3);
  } else if ((currentBar % 8) == 6) {
    rightWristPos(2);
  } else if ((currentBar % 8) == 7) {
    rightWristPos(1);
  }; 
}

void leftWristLRPer4Beat() {
  if ((currentBar % 4) < 2) {
    leftWristPos(1);
  } else {
    leftWristPos(3);
  }; 
}
void rightWristLRPer4Beat() {
  if ((currentBar % 4) < 2) {
    rightWristPos(1);
  } else {
    rightWristPos(3);
  }; 
}
void leftWristLRPer2Beat() {
  if ((currentBar % 2) < 1) {
    leftWristPos(1);
  } else {
    leftWristPos(3);
  }; 
}
void rightWristLRPer2Beat() {
  if ((currentBar % 2) < 1) {
    rightWristPos(1);
  } else {
    rightWristPos(3);
  }; 
}


void leftWristPos (int ServoPos) {
  switch (ServoPos) {
  case 0:
    moveServoToPosSoft(9, servos[9].rightDancePos2);
    break;
  case 1:
    moveServoToPosSoft(9, servos[9].rightDancePos);
    break;
  case 2:
    moveServoToPosSoft(9, servos[9].servoCenter);
    break;
  case 3:
    moveServoToPosSoft(9, servos[9].leftDancePos);
    break;
  default:
    moveServoToPosSoft(9, servos[9].leftDancePos2);
    break;
  }
}

void rightWristPos (int ServoPos) {
  switch (ServoPos) {
  case 0:
    moveServoToPosSoft(5, servos[5].leftDancePos2);
    break;
  case 1:
    moveServoToPosSoft(5, servos[5].leftDancePos);
    break;
  case 2:
    moveServoToPosSoft(5, servos[5].servoCenter);
    break;
  case 3:
    moveServoToPosSoft(5, servos[5].rightDancePos);
    break;
  default:
    moveServoToPosSoft(5, servos[5].rightDancePos2);
    break;
  }
}

void leftWristUD (bool moveLeft) {
  if (moveLeft)
    moveServoToPosSoft(3, servos[3].leftDancePos);
  else
    moveServoToPosSoft(3, servos[3].rightDancePos);
}

void rightWristUD (bool moveLeft) {
  if (moveLeft)
    moveServoToPosSoft(7, servos[7].leftDancePos);
  else
    moveServoToPosSoft(7, servos[7].rightDancePos);
}


/*  Elbow    */
void rightElbowPos (int ServoPos) {
  switch (ServoPos) {
  case 0:
    moveServoToPosSoft(4, servos[4].leftDancePos2);
    break;
  case 1:
    moveServoToPosSoft(4, servos[4].leftDancePos);
    break;
  case 2:
    moveServoToPosSoft(4, servos[4].servoCenter);
    break;
  case 3:
    moveServoToPosSoft(4, servos[4].rightDancePos);
    break;
  default:
    moveServoToPosSoft(4, servos[4].rightDancePos2);
    break;
  }
}

void leftElbowPos(byte ServoPos) {
  switch (ServoPos) {
  case 0:
    moveServoToPosSoft(8, servos[8].leftDancePos2);
    break;
  case 1:
    moveServoToPosSoft(8, servos[8].leftDancePos);
    break;
  case 2:
    moveServoToPosSoft(8, servos[8].servoCenter);
    break;
  case 3:
    moveServoToPosSoft(8, servos[8].rightDancePos);
    break;
  default:
    moveServoToPosSoft(8, servos[8].rightDancePos2);
    break;
  }
}


void beatShake (bool moveLeft, int delayo) {
  if (moveLeft)
    moveServoToPosSoft(12, servos[12].leftDancePos);
  else
    moveServoToPosSoft(12, servos[12].rightDancePos);
}


void nodHead(bool headUp) {
  if (headUp) {
    moveServoToPosSoft(10, servos[10].rightDancePos);
  } else {
    moveServoToPosSoft(10, servos[10].leftDancePos);
  }
}

void moveWristsToCenter() {
  moveServoToPosSoft(3, servos[3].servoCenter);
  moveServoToPosSoft(5, servos[5].servoCenter);
  moveServoToPosSoft(7, servos[7].servoCenter);
  moveServoToPosSoft(9, servos[9].servoCenter);
}

// Right Arm / Elbow positions
void rightArmUpRightElbowUp() {
  moveServoToPosSoft(4, 420);
}
void rightArmUpRightElbowMiddle() {
  moveServoToPosSoft(4, 280);
}
void rightArmUpRightElbowDown() {
  moveServoToPosSoft(4, 190);
}

void rightArmMiddleRightElbowUp() {
  moveServoToPosSoft(4, 486);
}
void rightArmMiddleRightElbowMiddle() {
  moveServoToPosSoft(4, 350);
}
void rightArmMiddleRightElbowDown() {
  moveServoToPosSoft(4, 200);
}

void rightArmDownRightElbowUp() {
  moveServoToPosSoft(4, 510);
}
void rightArmDownRightElbowMiddle() {
  moveServoToPosSoft(4, 396);
}
void rightArmDownRightElbowDown() {
  moveServoToPosSoft(4, 236);
}



// Left Arm / Elbow positions
void leftArmUpLeftElbowUp() {
  moveServoToPosSoft(8, 290);
}
void leftArmUpLeftElbowMiddle() {
  moveServoToPosSoft(8, 430);
}
void leftArmUpLeftElbowDown() {
  moveServoToPosSoft(8, 510);
}

void leftArmMiddleLeftElbowUp() {
  moveServoToPosSoft(8, 210);
}
void leftArmMiddleLeftElbowMiddle() {
  moveServoToPosSoft(8, 340);
}
void leftArmMiddleLeftElbowDown() {
  moveServoToPosSoft(8, 496);
}

void leftArmDownLeftElbowUp() {
  moveServoToPosSoft(8, 180);
}
void leftArmDownLeftElbowMiddle() {
  moveServoToPosSoft(8, 266);
}
void leftArmDownLeftElbowDown() {
  moveServoToPosSoft(8, 430);
}


