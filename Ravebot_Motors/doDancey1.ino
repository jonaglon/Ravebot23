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



