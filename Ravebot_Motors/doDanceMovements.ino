
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

