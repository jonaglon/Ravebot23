
// called from init, set all servos to their initial position
void initServos() {
  int range=4;
  
  for (int servoNum = 0; servoNum < 16; servoNum++) {
    if (servoNum != 4 && servoNum != 11) {
      moveServoToPos(servoNum, servos[servoNum].servoCenter+range);
    }
  }
  delay(200);
  for (int servoNum = 0; servoNum < 16; servoNum++) {
    if (servoNum != 4 && servoNum != 11) {
      moveServoToPos(servoNum, servos[servoNum].servoCenter-range);
    }
  }
  delay(200);
  for (int servoNum = 0; servoNum < 16; servoNum++) {
    if (servoNum == 4 || servoNum == 11) {
      moveServoToPos(4, 486);
      moveServoToPos(11, 210);
    } else {
      moveServoToPos(servoNum, servos[servoNum].servoCenter+range);    
    }
  }
}

void doServos() {

  if (ps2.readButton(PS2_RIGHT_1) == 0) {
    doHead();
  }

  // dont do the wrists if any mod button is pressed
  if (ps2.readButton(PS2_LEFT_1) == 0) {
    ps2LeftWrist();
    ps2RightWrist();
    ps2LeftClaw();
    ps2RightClaw();
    ps2RightElbow();
    ps2LeftElbow();
  }
}

void doHead() {
  doNod();
  doShake();
  // doTilt();
}

int readPs2LYVar = 0;
void doNodDirect() {
  readPs2LYVar=-(ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS)-128)/3;
  moveServoToPos(13, servos[13].servoCenter-readPs2LYVar);
}

// movement control vars
bool nodding = false;
unsigned long noddingTime;
void doNod() {
  readPs2LYVar=(ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS)-128)/33;

  // nod
  if (readPs2LYVar != 0) {
    moveServoSoft(13, readPs2LYVar, 16);
    nodding = true;
    noddingTime = timey;
  }
  else if (nodding) {
    if (timey > noddingTime+1800)
      nodding = false;
  }
  else if (servos[13].servoPos > servos[13].servoCenter) {
    moveServoSoft(13, -2, 16);
  }
  else if  (servos[13].servoPos < servos[13].servoCenter) {
    moveServoSoft(13, 2, 16);
  }
}

// movement control vars
bool shaking = false;
unsigned long shakingTime;
int readPs2RXVar = 0;
void doShake() {
  // shake
  readPs2RXVar=(ps2.readButton(PS2_JOYSTICK_RIGHT_X_AXIS)-128)/38;

  if (readPs2RXVar != 0) {
    moveServoSoft(15, readPs2RXVar, 16);
    shaking = true;
    shakingTime = timey;
  }
  else if (shaking) {
    if (timey > shakingTime+1800)
      shaking = false;
  }
  else if (servos[15].servoPos > servos[15].servoCenter) {
    moveServoSoft(15, -2, 16);
  }
  else if  (servos[15].servoPos < servos[15].servoCenter) {
    moveServoSoft(15, 2, 16);
  }
}

int readPs2LXVar = 0;
bool tilting = false;
unsigned long tiltTime;
// TODO This is commented for the time being as the tilt doesn't work properly
void doTilt() {
  readPs2LXVar=-(ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS)-128)/63;

  // tilt
  if (readPs2LXVar != 0) {
    moveServoSoft(14, readPs2LXVar, 16);
    tilting = true;
    tiltTime = timey;
  }
  else if (tilting) {
    if (timey > tiltTime+1800)
      tilting = false;
  }
  else if (servos[14].servoPos > servos[14].servoCenter) {
    moveServoSoft(14, -2, 16);
  }
  else if  (servos[14].servoPos < servos[14].servoCenter) {
    moveServoSoft(14, 2, 16);
  }
}

void ps2LeftClaw() {
  if (ps2.readButton(PS2_SQUARE) == 0) {
    moveServo(2, servos[2].servoSpeed);
  }
  if (ps2.readButton(PS2_CIRCLE) == 0) {
    moveServo(2, -servos[2].servoSpeed);
  }
}

void ps2RightClaw() {
  if (ps2.readButton(PS2_RIGHT) == 0) {
    moveServo(6, servos[6].servoSpeed);
  }
  if (ps2.readButton(PS2_LEFT) == 0) {
    moveServo(6, -servos[6].servoSpeed);
  }
}

void ps2LeftWrist() {
  moveServoToPos(12, (-(ps2.readButton(PS2_JOYSTICK_RIGHT_X_AXIS)-128))+servos[12].servoCenter);
  moveServoToPos(3, (-(ps2.readButton(PS2_JOYSTICK_RIGHT_Y_AXIS)-128))+servos[3].servoCenter);
}

void ps2RightWrist() {
  moveServoToPos(5, (ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS)-128)+servos[5].servoCenter);
  moveServoToPos(7, (-(ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS)-128))+servos[7].servoCenter);
}


void ps2LeftElbow() {
  if (ps2.readButton(PS2_CROSS) == 0) {
    moveServo(11, servos[11].servoSpeed);
  }
  if (ps2.readButton(PS2_TRIANGLE) == 0) {
    moveServo(11, -servos[11].servoSpeed);
  }
}

void ps2RightElbow() {
  if (ps2.readButton(PS2_DOWN) == 0) {
    moveServo(4, -servos[4].servoSpeed);
  }
  if (ps2.readButton(PS2_UP) == 0) {
    moveServo(4, servos[4].servoSpeed);
  }
}

void moveServo(int servoNum, int velocity) {
  int newPosition = servos[servoNum].servoPos + velocity;
  if (newPosition < servos[servoNum].maxPosition && newPosition > servos[servoNum].minPosition && newPosition != servos[servoNum].servoPos) {
    setServo(servoNum, newPosition);
  }
}

void moveServoSoft(int servoNum, int velocity, int timeBeforeNextMove) {
  int newPosition = servos[servoNum].servoPos + velocity;
  if (newPosition < servos[servoNum].maxPosition && newPosition > servos[servoNum].minPosition && newPosition != servos[servoNum].servoPos) {
    if (timey > (servos[servoNum].servoMoveTime + timeBeforeNextMove)) {
      setServo(servoNum, newPosition);
    }
  }
}

void moveServoToPos(int servoNum, int newPosition) {
  if (newPosition < servos[servoNum].maxPosition && newPosition > servos[servoNum].minPosition && newPosition != servos[servoNum].servoPos) {
    setServo(servoNum, newPosition);
  }
}

void moveServoToPosSoft(int servoNum, int newPosition) {
  if (newPosition < servos[servoNum].maxPosition && newPosition > servos[servoNum].minPosition && newPosition != servos[servoNum].servoPos) {
    int posToMoveTo;
    if (newPosition > servos[servoNum].servoPos) {
      posToMoveTo = servos[servoNum].servoPos + 2;
    } else {
      posToMoveTo = servos[servoNum].servoPos - 2;
    }
    setServo(servoNum, posToMoveTo);
  }
}

void setServo(int servoNum, int newPosition) {
  if (servoNum > 7) {
    servoPwm2.setPWM(servoNum, 0, newPosition);
  }
  else {
    servoPwm1.setPWM(servoNum, 0, newPosition);
  }
  servos[servoNum].servoPos = newPosition;
  servos[servoNum].servoMoveTime = timey;
}
