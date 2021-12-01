  /*   __                 _           _               __ _       _     _
    /__\ __ ___   _____| |__   ___ | |_            / /(_) __ _| |__ | |_ ___
   / \/// _` \ \ / / _ \ '_ \ / _ \| __|  _____   / / | |/ _` | '_ \| __/ __|
  / _  \ (_| |\ V /  __/ |_) | (_) | |_  |_____| / /__| | (_| | | | | |_\__ \
  \/ \_/\__,_| \_/ \___|_.__/ \___/ \__|         \____/_|\__, |_| |_|\__|___/
int8_t = -128 to 127                                     |___/         
uint8_t = 0 to 255
int16_t = -32,768 to 32,767
uint16_t = 0 to 65,535
int32_t = -2,147,483,648 to 2,147,483,647
uint32_t = 0 to 4,294,967,295
int64_t = −9,223,372,036,854,775,808 to 9,223,372,036,854,775,807
uint64_t = 0 to 18,446,744,073,709,551,615      */

#include<Arduino.h>
#include<Wire.h>
#include<FastLED.h>

const bool testMode = false;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            ;
const bool beatTestMode = false;
const bool megaAttached = false;

bool robotSwitchedOn = true;
bool robotManualMode = true;

uint32_t timey;
uint32_t lastBeatTime = 0;
uint32_t lastEyeMoveTime = 0;
uint32_t timeyInTime, twinkleTime; // This is like timey but in time, counting 16384 per beat

uint32_t lastBeatLength = 1;
uint16_t percentThroughBeat = 0;  // Not really a percent, beat divides into 16384 parts
uint32_t fakeBeatCount = 0;
uint8_t thisBeat32 = 0;
uint8_t thisBeat16 = 0;
uint8_t thisBeat8 = 0;
uint8_t thisBeat4 = 0;

const uint32_t animLength=524288;
const uint32_t animLength32th=16384;

uint8_t currentDance = 1;
uint8_t numPatterns = 25;
uint8_t currentLightPattern = 0;
bool overlayPatternActive = false;
bool cutUpPatternActive = false;
bool extraPatternActive = false;
uint8_t overlayPatternNumber = 0;
uint8_t cutUpPatternNumber = 0;
uint8_t extraPatternNumber = 0;

int32_t fakeBeatLengh = 420;

// Set by midi in to be 1-16 with beat.
uint8_t sixteenBeats = 0;
uint32_t totalBeats = 0;
bool beatCycle = false;

uint8_t mainVolume = 40; // 127 actual max but we won't exceed 100.
uint8_t tempMainVolume = 40; // 127 actual max but we won't exceed 100.
uint16_t currentBar = 0;
uint16_t mixCurrentBar = 0; // This counts from the start of a mix
uint8_t currentGenre = 0;
uint8_t currentTrack = 0;
uint16_t dropCountdown = 0;

bool robotTalking = false;
int32_t robotTalkingOnTime;
int32_t robotTalkingOffTime;
bool leftEyeClockwise = true;
bool rightEyeClockwise = true;

const uint16_t numLeds = 1443;
CRGB rgbwLeds[2440]; // 488 * 5

// LED Intensity
uint8_t lastSentLedIntensity = 10;
uint8_t ledIntensity = 10;
uint8_t wheelR, wheelG, wheelB;
uint8_t goodColR, goodColG, goodColB, goodColW;


int16_t leftEyeX = 0;
int16_t leftEyeY = 0;
int16_t rightEyeX = 0;
int16_t rightEyeY = 0;
uint8_t eyePrimaryR = 110;
uint8_t eyePrimaryG = 150;
uint8_t eyePrimaryB = 150;

// MIXING VARS
uint8_t nextTrack = 0;
uint8_t nextGenre = 0;
int16_t nextMixDuration = 0;
int16_t nextMixStart = 0;
int16_t abletonBpm = 0;
bool stayWithinGenre = false;
bool currentlyMixing = false;
bool deckASelected = true;
int16_t currentMixerPosition = 0;
uint8_t percentThroughMix = 0;  // not really % through, it's 0-256
uint8_t last20Genres[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
uint8_t last20Tracks[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

void setup() {
  delay(500);

  // Talk to Ableton using midi over USB, or debug.
  Serial.begin(115200);

  // Communicate with the Mega
  Serial1.begin(28800); // rx for receiving
  Serial1.begin(28800); // tx for sending

  // Make random more random
  randomSeed(analogRead(0));

  LEDS.addLeds<WS2811_PORTD, 6>(rgbwLeds, 488); // Hardcoded to ports:25,26,27,28,14,15
  LEDS.setBrightness(128); // 128 good max, 255 actual /max

  setMainVolume(mainVolume);
  
  if (currentLightPattern < 14)
    setupNewTwinklePattern(currentLightPattern);

  if (!robotSwitchedOn)
    changeOnOff(0);
      
  playTune(3, 8, false);
}

void loop() {
  timey = millis();

  beatCycle = false;
  listenToAbleton();

  setTimes();

  if (robotSwitchedOn)
    doLights();

  receiveFromMega();

  checkForTurnRobotVoiceDown();
}

void setTimes() {

  if (timey > (lastBeatTime + lastBeatLength)) {
    percentThroughBeat = 16383;
  } else {
    percentThroughBeat = (((timey - lastBeatTime) * 16384) / lastBeatLength);
    if (percentThroughBeat > 16383)
      percentThroughBeat = 16383;
  }

  // this is a number to be used in animations, it counts up from the start of a tune, 16384 per beat.
  timeyInTime = (totalBeats * 16384) + percentThroughBeat;
  twinkleTime = timeyInTime % animLength;

  if (beatCycle) {
    thisBeat32 = totalBeats%32;
    thisBeat16 = (sixteenBeats+15)%16;
    thisBeat8 = (sixteenBeats+15)%8;
    thisBeat4 = (sixteenBeats+15)%4;
  }
}

struct twinkle {
  uint16_t ledNum;
  uint8_t rCol;
  uint8_t gCol;
  uint8_t bCol;
  uint8_t wCol;
  uint8_t rToCol;
  uint8_t gToCol;
  uint8_t bToCol;
  uint8_t wToCol;
  int32_t start;
  int32_t lengthy;
  uint16_t widthy;
  int32_t fadeIn;
  int32_t fadeOut;
  uint16_t speedy;
  uint16_t sideFade;
  bool hasTwinked;

  twinkle(uint16_t aLedNum, uint8_t aRCol, uint8_t aGCol, uint8_t aBCol, uint8_t aWCol, uint8_t aToRCol, uint8_t aToGCol, uint8_t aToBCol, uint8_t aToWCol, int32_t aStart, int32_t aLengthy, uint16_t aWidthy, int32_t aFadeIn, int32_t aFadeOut, uint16_t aSpeedy, uint16_t aSideFade, bool aHasTwinked) :
    ledNum(aLedNum), rCol(aRCol), gCol(aGCol), bCol(aBCol), wCol(aWCol), rToCol(aToRCol), gToCol(aToGCol), bToCol(aToBCol), wToCol(aToWCol), start(aStart), lengthy(aLengthy), widthy(aWidthy), fadeIn(aFadeIn), fadeOut(aFadeOut), speedy(aSpeedy), sideFade(aSideFade), hasTwinked(aHasTwinked) {  }

  twinkle() : ledNum(0), rCol(0), gCol(0), bCol(0), wCol(0), rToCol(0), gToCol(0), bToCol(0), wToCol(0), start(0), lengthy(0), widthy(0), fadeIn(0), fadeOut(0), speedy(0), sideFade(0), hasTwinked(0) { }
};

const uint16_t numTwinks = 1024;
twinkle myTwinkles[numTwinks];
const uint16_t usedTwinkleCount[14] = {1024, 512, 750, 1024, 1024, 512, 750, 600, 256, 512, 512, 300, 20, 1024};


struct tuneInfo {
  uint8_t bpm;
  uint8_t drop;
  uint8_t tuneLength;
  uint8_t maxFadeIn;
  uint8_t minFadeOut;
  uint8_t maxFadeOut;
  bool playOut;
  tuneInfo(uint8_t aBpm, uint8_t aDrop, uint8_t aTuneLength, uint8_t aMaxFadeIn, uint8_t aMinFadeOut, uint8_t aMaxFadeOut, bool aPlayOut) :
    bpm(aBpm), drop(aDrop), tuneLength(aTuneLength), maxFadeIn(aMaxFadeIn), minFadeOut(aMinFadeOut), maxFadeOut(aMaxFadeOut), playOut(aPlayOut) {
  }
};

// Genre 0, RAVE!
const tuneInfo tuneLibRave[35] = {
  {149, 68, 144, 16,  0, 16, false},  // 1  TripToTheMoonPt2-Acen
  {136, 80, 104, 16,  0, 16, false},  // 2  Bombscare-2BadMice
  {126,  0, 118,  8,  0, 16, false},  // 3  LFO-LFO
  {131,  0, 128,  8,  0, 16, true},   // 4  Infiltrate202-Altern8
  {122,  0, 118,  8,  0, 16, true},   // 5  DirtyCash-SoldOutMix
  {122,  0, 132,  8,  0, 16, true},   // 6  Break4Love-Raze
  {124, 44,  96, 16,  0, 16, true},   // 7  IsThereAnybodyOutThere-Bassheads
  {128,  0, 119,  8,  4, 16, false},  // 8  PacificState-808State
  {150,  0, 156, 16,  0, 16, false},  // 9  OutOfSpace-Prodigy
  {132,  0, 122,  8,  0, 16, true},   // 10 Breathe-Prodigy
  {138,  0, 148, 16,  0, 16, false},  // 11 SmackMyBitchUp-Prodigy
  {128,  0, 116, 16,  0, 16, false},  // 12 BreakOfDawn-RhythmOnTheLoose
  {132,  0, 116, 16,  0, 16, false},  // 13 BlueMonday-NewOrder
  {132, 60, 128, 16,  0, 16, false},  // 14 PlayingWithKnives-BizzarreInc
  {120, 16, 128, 16,  0, 16, false},  // 15 KillerFeatTopCat-BoozooBajou
  {136, 60, 128, 16,  8, 16, false},  // 16 LivingLegends-RaggaTwins
  {135, 48, 132, 16,  0, 16, false},  // 17 FeelingForYou-Cassius
  {138,128, 168,  8,  8, 16, false},  // 18 DidIt-Sticky
  {135, 72, 106, 16,  0, 16, false},  // 19 HowLoveBegins-HighContrastDizee
  {130, 80, 122, 16,  0, 16, false},  // 20 StringsOfLife-DerrickMay
  {137, 80, 112, 16,  0, 16, false},  // 21 SweetHarmony-Liquid
  {126,  0, 113, 16,  0, 16, true},   // 22 WhereLoveLives-AlisonLimerick
  {135,  0, 110, 16,  0, 16, false},  // 23 DontGo-Awesome3
  {128, 74, 118,  8,  0, 16, true},   // 24 GoodLife-InnerCity
  {140, 56, 136, 16,  0, 16, false},  // 25 OnARaggaTip-SL2
  {126, 88, 112, 16,  0, 16, false},  // 26 Anthem-NJoi
  {122, 64, 104,  8,  0, 16, true},   // 27 RhythmIsAMystery-KKlass
  {121, 60,  96, 16,  0, 16, false},  // 28 Chime-Orbital
  {130, 92, 121,  0, 16, 12, false},  // 29 High-HyperGoGo
  {135, 92, 144,  8,  0, 16, false},  // 30 FarOut-SonzOfALoopDeLoopEra
  {126, 34, 133, 16, 16, 16, false},  // 31 TakeMeAway-FinalCut
  {128, 44, 104, 12,  8, 16, false},  // 32 Kinetic-GoldenGirls
  {132, 56, 144, 16,  8, 16, false},  // 33 Activ8-Altern8
  {145, 96, 160, 16,  8, 16, false},  // 34 NoGoodStartTheDance-TheProdigy
  {135, 61, 180, 16,  8, 16, false},  // 35 ALittleBitOfLuck_OraclesMix
};

// Genre 1, Disco
tuneInfo tuneLibDisco[30] = {
  {125,  0, 101,  8,  4,  8, false},  // 1 ILoveTheNightlife - Alecia Bridges
  {110,  0, 128,  8,  4, 16, true},   // 2 LastNightADjSavedMyLife-Indeep
  {134,  0, 149,  8,  0, 16, true},   // 3 LayAllYourLoveOnMe-Abba
  {121,  0, 157,  8,  4, 16, false},  // 4 HotStuff-DonnaSummer
  {128,  0, 110,  8,  4,  8, true},   // 5 RingMyBell-AnitaWard
  {128,  0, 209, 16,  0, 16, true},   // 6 EverybodyDance-Chic
  {111,  0, 100,  8,  0, 16, true},   // 7 GoodTimes-Chic
  {102,  0, 112,  8,  4,  8, true},   // 8 ThinkingOfYou-SisSledge
  {117,  0, 104,  8,  0,  8, true},   // 9 SheCantLoveYou-Chemise
  {112,  0, 130,  8,  0, 16, true},   // 10 Automatic-PointerSisters
  {105,  0, 120,  8,  0,  8, true},   // 11 StayinAlive-BeeGees
  {114,  0, 101,  4,  4,  8, false},  // 12 BestOfMyLove-TheEmotions
  {125,  0,  95,  4,  0, 16, true},   // 13 ILoveTheNightlife-AliciaBridges
  {110,  0,  96,  8,  0, 16, true},   // 14 NightFever-BeeGees
  {111,  0, 102,  8,  0, 16, true},   // 15 GiveMeTheNight-GeorgeBenson
  {118,  0, 135,  8,  0,  8, true},   // 16 YesSirICanBoogie-Baccara
  {129,  0, 149,  8,  0,  8, true},   // 17 LayAllYourLoveOnMe-Abba
  {116,  0,  96, 16,  4, 16, false},  // 18 HesTheGreatestDancer-SisSledge
  {108,  0,  80,  8,  0,  8, true},   // 19 FeelLikeIDo-Disclosure
  {108,  0, 108,  8,  8,  8, true},   // 20 TakeAChanceOnMe-Abba
  { 92,  0, 100,  8,  0,  8, true},   // 21 StrawberryLetter23-TheBrothersJohnson
  {126,  0, 105,  8,  0,  8, true},   // 22 DaddyCool-BoneyM
  {126,  0, 112,  8,  0,  8, false},  // 23 IFeelLove-DonnaSummer
  {131,  0, 112,  8,  0,  8, true},   // 24 DiscoInferno-TheTrammps
  {118,  0, 112, 16,  4, 16, true},   // 25 LeFreak-Chic
  {118,  0, 141,  8,  0,  8, true},   // 26 BoogieWonderland-EarthWindAndFire
  {132,  0, 154, 16,  4,  8, false},  // 27 Shame-EvelynChampageKing
  {123,  0,  98,  8,  4 , 8, false},  // 28 DISCO-Ottowan
  {106,  0, 104,  4,  4 , 8, true},   // 29 ShameShameShame-ShirleyAndCo
  {114,  0, 124,  4,  4 , 8, false},   // 30 LetTheBeatHitEm-LisaLisa_CultJam
};


// Genre 2, Reggae
tuneInfo tuneLibReggae[29] = {
  {170,  0, 132,  8,  0, 16, false},  // 1 RingTheAlarm-TenorSaw
  {102,  0, 118,  8,  0,  8, false},  // 2 FunkyKingston-Toots
  {164,  0, 164,  8,  0, 16, false},  // 3 UnderMeSlengTeng-WayneSmith
  {162,  0, 126,  8,  0, 16, true},   // 4 BamBam-SisNancy
  {162,  0, 156,  8,  4, 16, true},   // 5 StrictlyRoots-Althea&Donna
  {156,  0, 134,  0,  6, 10, true},   // 6 WelcomeToJamrock-DamianMarley
  {148,  0, 150,  0,  4, 16, true},   // 7 ItsAPity-TanyaStevens
  {172,  0, 144,  8,  4,  8, true},   // 8 FeelLikeJumping-MarciaG
  {164,  0, 164,  8,  0, 16, false},  // 9 CantStopNow-MajorLazer
  {148,  0, 106,  8,  0, 16, true},   // 10 PressureDrop-Toots
  {104,  0, 100,  4,  0, 16, true},   // 11 CouldYouBeLoved-BobMarley
  { 92,  0, 100,  8,  0, 16, true},   // 12 DidYouReallyKnow-MungoHiFi
  {131,  0, 129,  0,  0,  8, true},   // 13 ThingsInLife-BarryBrown
  {180,  0, 140,  8,  4,  8, false},  // 14 StandUp-MrBenn
  { 96,  0, 120,  8,  4, 16, false},  // 15 LongTime-MrBenn
  {161,  0, 148,  8,  8, 12, true},   // 16 YouthDemCold-RichieSpice
  { 93,  0, 102,  0,  4, 12, true},   // 17 HavingAParty-LeeScratchPerry
  {138,  0, 160,  8,  4,  8, true},   // 18 Behold-Culture
  {144,  0,  78,  0,  4,  8, true},   // 19 SunIsShining-BobMarley
  {128,  0,  88,  8,  0,  8, false},  // 20 RoadBlock-GeneralLevy
  {174,  0,  88,  8,  0, 16, true},   // 21 HereICome-BarringtonLevy
  {161,  0, 124,  0,  0,  8, true},   // 22 JohnnyTooBad-Slickers
  {161,  0, 124,  8,  0,  8, true},   // 23 DoubleBarrel-DaveAndAnsellCollins
  {102,  0, 124,  0,  0,  4, true},   // 24 LoveOfTheCommonPeople-NickyThomas
  {178,  0, 156,  8,  4,  8, false},  // 25 DayIntoNight-Katalyst
  {143,  0, 116,  8,  4,  8, true},   // 26 ThatVeryNight-HollieCook
  {144,  0, 126,  4,  4,  8, true},   // 27 PoliceInHelicopter-JohnHolt
  {142,  0, 132,  4,  4,  8, true},   // 28 GanjaSmuggling-EekAMouse
  { 96,  0,  96,  4,  4,  8, false},  // 29 MurderSheWrote_ChakaDemus_Pliers
};

//  bpm drp len mxIn mnOut mxOut bestEnd playOut */
//  Genre 3, Rock&Pop
tuneInfo tuneLibRockAndPop[33] = {
  { 82,  0,  66,  8,  0,  4, true},  // 1 KidsInAmerica-KimWilde
  {130,  0, 120, 16,  0, 16, false}, // 2 CantGetYouOut-Kylie
  {112,  0, 102,  8,  0,  8, true},  // 3 ICantGoForThat-Hall&Oates
  { 98,  0,  63,  0,  0,  0, true},  // 4 Faith-GeorgeMichael
  {122, 44, 102,  4,  4, 12, true},  // 5 GrooveIsInTheHeart-DeeLite
  {128,  0, 110,  4,  0,  8, true},  // 6 SweetDreams-Euritmics
  {126, 37, 100,  4,  0,  8, true},  // 7 StuckInTheMiddle-SteelersWheel
  { 82,  0,  68,  4,  0,  4, true},  // 8 Martha&Muffins Echo Beach
  {103,  0,  58,  2,  0,  2, true},  // 9 DreamingOfYou-TheCoral
  {100,  0,  58,  0,  0,  2, true},  // 10 BlisterInTheSun-VoilentFemmes
  {116,  0,  99,  4,  4,  8, true},  // 11 ALittleRespect-Erasure
  { 99,  0, 102,  4,  0,  8, true},  // 12 Superstition-StevieWonder
  {114,  0, 104,  0,  0,  4, true},  // 13 Kiss-Prince
  {112, 26, 114, 16,  0, 16, false}, // 14 WatchOutForThis-MajorLazer
  {134,  0, 138,  8,  0,  8, true},  // 15 YouCantTouchThis-MCHammer
  {112,  0,  83,  1,  4,  8, true},  // 16 Crazy-GnarlesBarkley
  {170,  0, 166, 16,  0,  2, true},  // 17 CostaDelEssex-Someone  **
  {110, 18,  87,  4,  4,  8, true},  // 18 IWantToBreakFree-Queen
  {145,  0, 123,  1,  4,  8, true},  // 19 CallMe-Blondie
  {131,  0, 116,  8,  0,  8, true},  // 20 RockTheCasbah-TheClash
  {118,  0,  34,  0,  0,  8, true},  // 21 Minder
  { 90,  0,  78,  2,  0,  8, true},  // 22 SummerDay-SoomTn
  { 94,  0,  57,  8,  0,  2, true},  // 23 Mutha'uckas-FlightOfTheChonchordes
  { 90,  0,  77,  8,  0,  8, true},  // 24 GetUrFreakOn-MissyElliot
  { 86,  0,  44,  4,  4,  8, true},  // 25 HitTheRoadJack - RayCharles
  { 86,  0,  44,  2,  1,  2, false}, // 26 Crash-ThePrimitives
  {119,  0, 124,  8,  4,  8, true},  // 27 OnceInALifetime-TalkingHeads
  { 85,  0,  54,  2,  0,  2, true},  // 28 BoysDontCry-TheCure
  {125,  0, 108,  4,  0,  2, false}, // 29 PumpUpTheJam-Technotronic
  {130,  0, 144,  8,  2, 16, false}, // 30 GraceJones_Libertango
  {110,  0,  86,  4,  2,  8, true},  // 31 Queen_IWantToBreakFree
  { 90,  0, 113,  6,  0,  6, false}, // 32 WhatIdSayParts1And2-RayCharles
  {108,  0, 104,  8,  0, 16, true},  // 33 LadiesFirst_QueenLatifah
};

//  Genre 4, Easy
tuneInfo tuneLibEasy[33] = {
  {122,  0, 134,  8,  2,  4, false},  // 1 BackToMyRoots - RichieHavens
  {104,  0,  59,  4,  0,  4, true},   // 2 Think - Aretha
  {100,  0, 182,  8,  4,  8, false},  // 3 As - Wonder
  {174,  0, 158,  4,  0,  8, true},   // 4 Roady - FatFreddyNextmen
  {132,  0,  88,  2,  2,  4, true},   // 5 Beggin - FrankieValli
  { 98,  0,  72,  1,  4,  8, true},   // 6 IGotAWoman - RayCharles
  {156,  0, 144,  2,  2,  8, true},   // 7 MilkAndHoney-PrinceFatty
  {126,  0, 122,  2,  4,  4, true},   // 8 BackToBlack - Amy
  {132,  0, 166,  4,  4,  4, true},   // 9 MasterBlaster-StevieWonder
  {109,  0, 112,  8,  0,  8, true},   // 10 AllNightLong - LionelRichie
  { 96,  0,  96,  4,  0,  6, true},   // 11 INeedADollar-AloeBlacc
  {122,  0, 124,  4,  0,  8, true},   // 12 GotToGiveItUp-MarvinGaye
  {139, 37, 124,  4,  0,  8, true},   // 13 TheHumansAreDead-FOTC
  {175,  0, 176,  8,  0,  8, false},  // 14 AgainAndAgain-RootsManuva
  {116,  0, 134,  8,  0,  6, true},   // 15 JamacianBoy-LoneRanger
  {171,  0, 186,  8,  0,  8, true},   // 16 TheLook-Metronomy
  {129,  0, 124,  4,  0,  8, false},  // 17 ReadyForTheFloor-HotChip
  {170,  0,  96, 16,  0,  8, true},   // 18 Roygbiv-BoardsOfCanada
  {102,  0, 136,  8,  0,  8, false},  // 19 Ageopolis-AphexTwin
  {103,  0, 110,  8,  0,  8, false},  // 20 ICouldNeverBeYourMan-WhiteTown
  {154,  0, 140,  8,  0, 16, true},   // 21 Bigger than hip hop-DedPrez
  { 95,  0,  72,  8,  4,  8, false},  // 22 PutItOn-Danger Mouse/BigL
  {118,  0,  74,  8,  0,  8, false},  // 23 Air-Remember
  { 86, 10,  76, 10,  0,  8, true},   // 24 Somersault-DangerMouse/Zero7/MFDoom
  { 93,  0,  96,  8,  0,  8, false},  // 25 MySound-SkarraMucci
  { 90,  0,  82,  4,  2,  6, false},  // 26 TheSong-SkarraMucchi
  {102,  0,  74,  8,  2,  6, true},   // 27 IfYouWantMeToStay-SlyAndTheFamilyStone
  {102,  0,  82,  8,  4,  8, true},   // 28 Rocksteady-Aretha
  { 98,  0, 100,  8,  4,  8, false},  // 29 SoManyGirls-Nextmen
  {112,  0, 148,  8,  4,  8, true},   // 30 Candy-Cameo
  { 86,  0,  92, 16,  0,  8, false},  // 31 PureGold_Calyx_TeeBee_Kemo
  {132,  0, 152, 16,  4, 16, false},  // 32 SomethingInYourEyes-KWarrenEdCaseShelleyNelson
  {124,  0, 128,  8,  0, 16, false},  // 33 Mondo77-Looper
};

//  bpm drp len mxIn mnOut mxOut bestEnd playOut 
//  Genre 5, Dance
tuneInfo tuneLibDance[41] = {
  {134, 30, 124,  8 , 0, 16, false},  // 1 A rinky dinky
  {110, 58,  88, 16,  0, 16, true},   // 2 Kelis - Trick Me
  {153,  0, 128, 16,  0, 16, false},  // 3 Dubbleedge - Lips to the floor
  {134,106, 168, 16,  0, 16, false},  // 4 Zero Emit Collect
  {126, 72,  92,  0,  2, 10, false},  // 5 Dizee Bonkers
  {118,  0,  88,  8,  0,  8, true},   // 6 DownWithTheTrumpets-RizzleKicks
  {112, 85, 104,  8,  0,  8, true},   // 7 PraiseYou-FatBoySlim
  {132,  0, 162, 16,  0,  8, true},   // 8 WileOut - DJ Zinc - DownWithTheTrumpets
  {146,  0, 128, 16,  0, 12, false},  // 9 Aphex - Polynomial C
  {124,  0, 189,  2,  2,  8, false},  // 10 Aphex WindowLicker
  {122,  0, 155,  8,  4, 16, false},  // 11 OverAndOver-HotChip
  {142,  0, 124,  4,  4, 16, false},  // 12 Omen - Prodigy
  {128,  0, 108,  8,  0, 16, false},  // 13 DibbyDibbySound-MajorLazer
  {132,  0, 120,  8,  0, 16, false},  // 14 ClintEastwood-EdCaseGorillaz
  {128,  0, 104,  8,  0,  8, true},   // 15 AllAboutThatBass-MeganTrainor -- move to rock pop
  {126,  0, 109,  8,  0,  9, false},  // 16 WeDontCare-AudioBullys
  {128,  0, 108,  8,  0, 12, false},  // 17 TooOriginal-MajorLazer
  {140,  0, 117, 16,  0, 16, true},   // 18 BasslineJunkie-DizzeeRascal
  {140,  0, 161, 16,  0, 16, false},  // 19 FeelLikeJumping-KraftyKuts
  {173,  0, 139,  8,  0, 11, false},  // 20 TotallyAddictedToBass-SonicBoomSix
  {152,  0, 150,  8,  0,  4, true},   // 21 TheRockerfellerSkank-FatboySlim
  {152,  0, 136,  8,  0,  8, true},   // 22 InForTheKill-LaRoux
  {130,  0, 144,  8,  0,  8, true},   // 23 HeyBoyHeyGirl-ChemicalBrothers
  {126,  0, 112, 16,  0,  8, false},  // 24 LikeAG6-FarEastMovement
  {124,  0, 120, 16,  0, 16, false},  // 25 ButIFeelGood-GrooveArmada
  {116,  0, 128,  8,  0, 16, false},  // 26 UptownFunk-MarkRonson 
  {137,  0, 114,  0,  1,  1, true},   // 27 DaftPunkIsPlayingAtMyHouse-LCDSoundSystem
  {114,  0, 116, 16,  4, 16, false},  // 28 DaFunk-DaftPunk
  {150,  0, 152, 16,  4,  8, false},  // 29 I3USo-SkreamCassius
  {136,  0,  84,  8,  2,  8, false},  // 30 BillieEilish_BadGuy  
  {138,  0, 192, 16, 16, 16, false},  // 31 DidIt_FyrusLarraineCatoSticky
  {136,  0, 144, 16,  8, 16, false},  // 32 BumpNGrind-MDubsLadySaw
  {135,  0, 176, 16,  4, 16, false},  // 33 AintNoStoppinUs-OraclesDjLuckMcNeat  
  {135,  0, 180, 16,  4, 16, false},  // 34 Boooo_StickyMsDynamiteJasonKaye
  {132,  0, 156, 16,  4, 16, false},  // 35 BodyGroove-Architechs_NayNay
  {128,  0, 112, 16,  4, 16, false},  // 36 ItsALondonThing-ScottGarcia
  {130,  0, 144, 16,  0, 16, false},  // 37 NeighbourhoodBioSonic_ZedBias_MCRumpusMickyPrince
  { 96,  0, 112,  8,  0, 16, false},  // 38 Gasolina-PitbullDaddyYankeeLilJon
  {128,  0, 128,  8,  0, 16, false},  // 39 ClubAction-YoMajesty
  {128,  0,  88,  6,  0, 12, false},  // 40 GetDown_GrooveArmadaStushRedRat
  {128,  0, 120, 16,  0, 16, false},  // 41 Low-TPain_FloRider
};

//  bpm drp len mxIn mnOut mxOut bestEnd playOut */
//  Genre 6, Drum&Bass
tuneInfo tuneLibDrumAndBass[36] = {
  {176,  0, 208, 32,  2, 32, false},  // 1 Girls-DJHypeAndPotential
  {176,  0, 192, 32,  2, 32, false},  // 2 DuppyMan-ChaseAndStatusCapleton
  {180,  0, 204, 32,  2, 32, false},  // 3 PullUp-ResonatGenLevy
  {176,  0, 196, 32,  2, 32, false},  // 4 GoldDigger-HighContrast
  {177,  0, 192, 32,  2, 32, false},  // 5 ShakeUrBody-ShyFX
  {174,  0, 144, 32,  2, 32, false},  // 6 KingOfTheBeats2016-Aphrodite
  {180,  0, 184, 32,  2, 32, false},  // 7 LastNight-BennyPage
  {176,  0, 208, 32,  2, 32, false},  // 8 TurnDownTheLights-BennyPage
  {175,  0, 152, 32,  2, 32, false},  // 9 PassTheKutchie-BennyPage
  {175,  0, 184, 32,  2, 32, false},  // 10 PassMeTheRizla-Deekline
  {176,  0, 192, 32,  2, 32, false},  // 11 CryingOut-BennyPageSerialKillazMix
  {176,  0, 160, 32,  2, 32, false},  // 12 ProfessionalGangaSmoker-GenLevy
  {175,  0, 160, 32,  2, 32, false},  // 13 TopRankSkank-BennyPage
  {176,  0, 200, 32,  2, 32, false},  // 14 BamBam-SerialKillaz
  {176,  0, 184, 32,  2, 32, false},  // 15 NoNoNo-SerialKillaz
  {175,  0, 176, 32,  2, 32, false},  // 16 RaggaTip-EdSolo
  {174,  0, 192, 32,  2, 32, false},  // 17 KissKissBangBang-HighContrast
  {174,  0, 192, 32,  2, 32, false},  // 18 Deep-TC
  {177,  0, 132, 24,  2, 32, false},  // 19 GoldDust-ShyFXMix
  {177,  0, 184, 32,  2, 32, false},  // 20 BlazingFire-BennyPage
  {175,  0, 176, 32,  2, 32, false},  // 21 HitTheRoadJack-DeeklineEdSoloGala
  {176,  0, 160, 32,  2, 32, false},  // 22 Incredible-MBeat
  {174,  0, 176, 32,  2, 32, false},  // 23 Workout-AndyC
  {174,  0, 168, 32,  2, 32, false},  // 24 RemindMe-HighContrast
  {174,  0, 168, 32,  2, 32, false},  // 25 PassOutDCBreaks-TinyTempah
  {170,  0, 136, 16,  2, 32, false},  // 26 OriginalNuttah-ShyFX
  {180,  0, 128, 32,  2, 32, false},  // 27 HandsUp-DjHype
  {174,  0, 176, 32,  2, 32, false},  // 28 Pendulum_Tarantula
  {176,  0, 176, 32,  2, 32, false},  // 29 WalkAndSkank-SerialKillaz
  {176,  0, 208, 32,  2, 32, false},  // 30 IllBehaviour-DannyBirdIKay
  {178,  0, 192, 32,  2, 32, false},  // 31 GetReady-CongoNatty
  {176,  0, 208, 32,  2, 32, false},  // 32 SeeTheVibe-EdSoloFardnaTiffJuno
  {178,  0, 216, 32,  2, 32, false},  // 33 BlowThemAway-SerumInja
  {178,  0, 176, 16,  2, 32, false},  // 34 Jump+Move+Rock-BennyPageWrongtom
  {176,  0, 160, 16,  2, 32, false},  // 35 Solar_Metrik
  {176,  0, 144, 16,  2, 32, false},  // 36 Fire-Hamilton
};

//  bpm drp len mxIn mnOut mxOut bestEnd playOut */
// Genre 7, HipHop
tuneInfo tuneLibHipHop[30] = {
  {101,  0,  80,  4,  0, 16, false},  //1 Lets get ill
  { 90,  0, 108,  4,  0, 16, false},  //2 No Diggidy
  { 97,  0,  66,  8,  4, 16, true},   //3 ShimmyShimmyYa-ODB
  {104,  0, 114,  4,  4, 16, false},  //4 Moma said knock you out
  { 93,  0,  70,  8,  0,  8, false},  //5 InDaClub-50Cent
  { 95,  0, 100,  8,  0, 16, false},  //6 DropItLikeItsCloseToMe-Snoop
  { 98,  0, 100,  4,  0,  8, false},  //7 OPP-NaughtyByNature
  {100,  0, 102,  8,  0, 16, true},   //8 HipHopHooray
  {108,  0,  88,  8,  0,  8, false},  //9 JumpAround-HouseOfPain
  {102,  0,  86,  8,  0,  8, true},   //10 InsazlleInTheBazzle-CyprusHazzle
  {108,  0,  98,  4,  2,  8, false},  //11 KingKunta-KendrickLamar
  { 95,  0,  82,  8,  0,  8, false},  //12 GinAndJuice-Snoop
  {106,  0,  96,  8,  0,  8, false},  //13 HotInHere-Nelly
  {120,  0, 115,  8,  0,  8, true},   //14 GravelPit-WuTangClan
  { 98,  0,  80,  8,  0,  8, false},  //15 TheOnlyOne-DangermouseJemini
  { 93,  0, 100,  8,  0,  8, false},  //16 FamilyAffair-MaryJBlige
  { 93,  0,  60,  8,  0,  8, true},   //17 HitsFromTheBong-CypressHill
  { 96,  0,  96,  8,  0,  8, false},  //18 Regulate-WarrenG
  {102,  0,  88,  8,  0,  8, true},   //19 GetBusy-SeanPaul
  { 96,  0,  80,  8,  2,  8, false},  //20 GoldDigger-Kanye
  { 92,  0,  80,  4,  4,  8, false},  //21 Breathe-BluCantrell
  {102,  0,  80,  4,  0,  4, false},  //22 NoLie-SeanPaul
  { 95,  0, 100,  8,  0,  8, true},   //23 MsJackson-Outkast
  { 95,  0,  86,  4,  0,  8, true},   //24 XGonGiveItToYa-DMX
  {134,  0, 124,  8,  0,  8, true},   //25 ForgotAboutDre-DreEminem
  { 93,  0, 104,  8,  0,  8, false},  //26 StillDRE-DrDre
  { 98,  0, 100,  8,  0,  8, true},   //27 X-Xzibit X Go
  { 93,  0, 100,  4,  0,  8, true},   //28 ExpressYourself-NWA
  {108,  0,  96,  8,  0,  8, false},  // 29 GotYourMoney-ODB
  { 92,  0, 100,  8,  0,  8, false},  // 30 KeepOnKeepinOn_MCLyteXscape
};

tuneInfo currentTune = tuneLibHipHop[0];
tuneInfo nextTune = tuneLibHipHop[0];


uint16_t eyeCoords[93][2] = {
  { 55, 107}, { 64, 106}, { 75, 104}, { 84, 98}, { 92, 93}, { 98, 85}, {103, 76}, {107, 66}, {108, 56}, {107, 45},
  {103, 35}, { 98, 27}, { 92, 18}, { 84, 12}, { 75,  7}, { 64,  3}, { 55,  2}, { 45,  3}, { 35,  7}, { 26, 12},
  { 18, 18}, { 12, 27}, {  7, 35}, {  4, 45}, {  3, 56}, {  4, 66}, {  7, 76}, { 12, 85}, { 18, 93}, { 26, 98},
  { 35, 104}, { 45, 106}, { 55, 98}, { 66, 97}, { 76, 92}, { 85, 86}, { 91, 77}, { 96, 66}, { 97, 55}, { 96, 44},
  { 91, 35}, { 84, 26}, { 76, 18}, { 66, 14}, { 55, 13}, { 45, 14}, { 34, 18}, { 26, 26}, { 18, 35}, { 14, 44},
  { 12, 55}, { 14, 66}, { 18, 77}, { 25, 85}, { 34, 92}, { 44, 97}, { 55, 88}, { 67, 86}, { 77, 78}, { 85, 68},
  { 87, 55}, { 85, 43}, { 77, 33}, { 67, 25}, { 55, 23}, { 43, 25}, { 32, 33}, { 25, 43}, { 23, 55}, { 25, 68},
  { 32, 78}, { 43, 86}, { 55, 78}, { 66, 75}, { 74, 67}, { 77, 55}, { 75, 44}, { 67, 36}, { 55, 33}, { 44, 36},
  { 36, 44}, { 33, 55}, { 35, 67}, { 43, 75}, { 55, 68}, { 64, 64}, { 67, 55}, { 64, 47}, { 55, 43}, { 46, 47},
  { 43, 55}, { 46, 64}, { 55, 55}
};   //
uint16_t armCoords[24][2] = {
  { 0,  6}, { 0, 13}, { 0, 19}, { 0, 25}, { 0, 31}, { 0, 38}, { 0, 44}, { 0, 50}, { 0, 57}, { 0, 62},
  { 0, 69}, { 0, 75}, { 0, 82}, { 0, 88}, { 0, 94}, { 0, 100}, { 0, 106}, { 0, 113}, { 0, 119}, { 0, 125},
  { 0, 131}, { 0, 138}, { 0, 144}, { 0, 150}
};
uint16_t horizCoords[26][2] = {
  {  7, 0}, { 13, 0}, { 20, 0}, { 27, 0}, { 33, 0}, { 40, 0}, { 47, 0}, { 53, 0}, { 60, 0}, { 67, 0},
  { 73, 0}, { 80, 0}, { 87, 0}, { 93, 0}, {100, 0}, {107, 0}, {113, 0}, {120, 0}, {127, 0}, {133, 0},
  {140, 0}, {147, 0}, {153, 0}, {160, 0}, {167, 0}, {173, 0}
};
uint16_t tapeCoords[34][2] = {
  { 00,  7}, { 00, 13}, { 00, 20}, { 00, 27}, { 00, 33}, { 00, 40}, { 00, 47}, { 00, 53}, { 00, 60}, {  4, 60},
  { 10, 60}, { 17, 60}, { 24, 60}, { 30, 60}, { 36, 60}, { 44, 60}, { 50, 60}, { 57, 60}, { 64, 60}, { 70, 60},
  { 77, 60}, { 84, 60}, { 90, 60}, { 97, 60}, {104, 60}, {104, 60}, {104, 53}, {104, 47}, {104, 40}, {104, 33},
  {104, 27}, {104, 20}, {104, 13}, {104,  7}
};
uint16_t tubeCoords[90][2] = {
  {100, 197}, {108, 197}, {113, 196}, {122, 194}, {129, 191}, {137, 188}, {143, 186}, {150, 181}, {157, 178}, {162, 172},
  {167, 168}, {172, 163}, {177, 158}, {183, 152}, {187, 145}, {190, 138}, {193, 131}, {195, 124}, {197, 118}, {198, 111},
  {198, 105}, {198, 98}, {197, 92}, {196, 84}, {195, 78}, {194, 72}, {193, 65}, {190, 59}, {188, 52}, {183, 46},
  {179, 40}, {175, 34}, {170, 29}, {166, 26}, {161, 22}, {156, 18}, {149, 16}, {143, 11}, {138,  8}, {134,  5},
  {128,  4}, {122,  3}, {116,  2}, {112,  2}, {105,  1}, {100,  0}, { 93,  1}, { 87,  2}, { 79,  4}, { 71,  8},
  { 63, 10}, { 58, 12}, { 50, 16}, { 44, 20}, { 38, 23}, { 33, 28}, { 29, 32}, { 24, 36}, { 20, 42}, { 16, 48},
  { 12, 74}, {  8, 59}, {  5, 67}, {  3, 74}, {  2, 82}, {  2, 88}, {  1, 94}, {  0, 100}, {  1, 108}, {  2, 114},
  {  3, 119}, {  5, 127}, {  6, 134}, {  8, 140}, { 12, 146}, { 15, 154}, { 19, 158}, { 23, 162}, { 27, 166}, { 30, 170},
  { 37, 175}, { 42, 179}, { 48, 182}, { 55, 185}, { 62, 189}, { 69, 193}, { 77, 194}, { 83, 196}, { 88, 197}, { 95, 198}
};
uint16_t binCoords[203][2] = {  // 3               // 5                             // 8                  // 0
  {230, 460}, {238, 459}, {245, 459}, {251, 458}, {258, 458}, {266, 458}, {272, 457}, {277, 455}, {285, 453}, {292, 450},
  {299, 447}, {305, 444}, {324, 439}, {329, 436}, {335, 432}, {340, 430}, {347, 425}, {352, 421}, {357, 416}, {360, 410}, // 20
  {365, 406}, {370, 402}, {375, 400}, {380, 394}, {385, 386}, {390, 382}, {394, 378}, {398, 373}, {402, 396}, {406, 363},
  {410, 359}, {414, 352}, {418, 348}, {421, 342}, {424, 336}, {425, 331}, {429, 322}, {433, 317}, {435, 311}, {438, 305}, // 40
  {440, 296}, {442, 288}, {443, 283}, {444, 277}, {445, 269}, {446, 261}, {448, 253}, {448, 248}, {449, 239}, {449, 230},
  {450, 225}, {449, 219}, {448, 212}, {447, 205}, {446, 198}, {446, 191}, {445, 188}, {443, 178}, {440, 170}, {438, 166}, // 60
  {436, 161}, {434, 155}, {432, 147}, {429, 140}, {426, 135}, {424, 130}, {420, 122}, {416, 114}, {413, 108}, {409, 103},
  {405, 100}, {402, 94}, {398, 87}, {394, 82}, {390, 77}, {385, 73}, {380, 69}, {375, 63}, {368, 56}, {364, 51}, // 80
  {357, 48}, {352, 45}, {346, 42}, {341, 39}, {335, 34}, {331, 31}, {325, 28}, {319, 25}, {313, 22}, {306, 20},
  {300, 18}, {294, 16}, {285, 14}, {279, 13}, {273, 12}, {266, 10}, {259,  9}, {251,  7}, {245,  5}, {238,  5}, // 100
  {232,  5}, {225,  6}, {221,  7}, {214,  8}, {208,  9}, {200, 10}, {192, 12}, {184, 13}, {174, 13}, {168, 14},
  {162, 16}, {154, 18}, {148, 22}, {141, 25}, {137, 27}, {132, 29}, {125, 32}, {118, 36}, {112, 39}, {106, 42}, // 120
  {101, 46}, { 97, 48}, { 91, 53}, { 85, 59}, { 80, 65}, { 75, 70}, { 71, 75}, { 65, 78}, { 60, 85}, { 56, 92},
  { 52, 98}, { 48, 101}, { 45, 107}, { 40, 112}, { 36, 119}, { 32, 127}, { 28, 134}, { 26, 138}, { 24, 144}, { 21, 152}, // 140
  { 18, 158}, { 17, 164}, { 15, 171}, { 14, 178}, { 13, 186}, { 12, 192}, { 11, 198}, { 10, 206}, {  9, 214}, {  9, 221},
  {  8, 228}, {  9, 235}, {  9, 244}, {  9, 249}, { 10, 254}, { 11, 260}, { 12, 268}, { 13, 275}, { 15, 282}, { 16, 288}, // 160
  { 17, 292}, { 18, 302}, { 21, 308}, { 22, 312}, { 25, 318}, { 28, 322}, { 31, 330}, { 34, 336}, { 36, 342}, { 39, 346},
  { 43, 352}, { 45, 360}, { 49, 366}, { 53, 370}, { 60, 376}, { 65, 379}, { 68, 386}, { 71, 392}, { 78, 399}, { 82, 402}, // 180
  { 88, 405}, { 93, 408}, { 98, 412}, {103, 418}, {108, 423}, {112, 427}, {119, 430}, {125, 433}, {132, 436}, {137, 439},
  {144, 440}, {151, 442}, {156, 445}, {162, 447}, {168, 450}, {175, 452}, {182, 454}, {188, 456}, {195, 457}, {204, 458}, // 200
  {212, 459}, {217, 460}, {222, 460}
};
uint16_t bigHeartCoords[175][2] = {      // 3        // 4                             // 7                  // 9
  { 48, 267}, { 45, 273}, { 42, 280}, { 37, 287}, { 33, 295}, { 28, 303}, { 26, 309}, { 23, 317}, { 20, 325}, { 17, 333},
  { 15, 338}, { 14, 344}, { 12, 352}, { 10, 359}, {  9, 365}, {  8, 372}, {  7, 378}, {  6, 385}, {  8, 392}, {  9, 401},
  { 10, 409}, { 12, 416}, { 15, 423}, { 18, 430}, { 21, 438}, { 23, 443}, { 27, 451}, { 30, 456}, { 34, 463}, { 40, 469},
  { 35, 473}, { 52, 478}, { 57, 482}, { 63, 484}, { 68, 487}, { 74, 489}, { 80, 493}, { 86, 495}, { 94, 497}, {100, 498},
  {107, 499}, {115, 499}, {120, 500}, {125, 500}, {132, 500}, {138, 499}, {144, 499}, {153, 499}, {158, 498}, {165, 497}, // 49
  {172, 497}, {178, 496}, {185, 495}, {192, 493}, {200, 491}, {206, 489}, {212, 487}, {218, 485}, {225, 482}, {232, 479},
  {238, 475}, {244, 472}, {252, 470}, {258, 468}, {265, 466}, {270, 463}, {276, 459}, {282, 456}, {287, 454}, {292, 450}, // 69
  {298, 455}, {303, 458}, {309, 462}, {315, 466}, {322, 470}, {328, 473}, {334, 476}, {340, 479}, {348, 481}, {354, 484},
  {361, 485}, {367, 488}, {373, 490}, {379, 491}, {386, 493}, {393, 494}, {401, 496}, {408, 497}, {414, 498}, {421, 499}, // 89
  {428, 499}, {434, 497}, {441, 495}, {448, 492}, {454, 490}, {462, 488}, {468, 487}, {475, 484}, {482, 481}, {488, 478},
  {494, 472}, {500, 469}, {506, 467}, {512, 466}, {518, 463}, {522, 460}, {529, 456}, {535, 452}, {540, 448}, {547, 442}, // 109
  {550, 438}, {555, 432}, {560, 428}, {563, 420}, {566, 412}, {568, 406}, {570, 401}, {572, 395}, {573, 388}, {574, 380},
  {574, 376}, {573, 369}, {572, 363}, {572, 358}, {571, 352}, {569, 345}, {566, 338}, {564, 328}, {562, 322}, {559, 315}, // 129
  {556, 308}, {553, 300}, {551, 292}, {549, 287}, {546, 278}, {545, 273}, {542, 268}, {539, 261}, {536, 254}, {533, 248},
  {531, 243}, {528, 238}, {526, 231}, {523, 225}, {521, 220}, {490, 230}, {490, 230}, {385, 63}, {380, 58}, {375, 52}, // 149
  {370, 44}, {364, 43}, {358, 39}, {352, 33}, {346, 30}, {341, 25}, {334, 21}, {329, 17}, {323, 12}, {318,  9},
  {309,  6}, {300,  8}, {294, 12}, {289, 14}, {283, 18}, {278, 22}, {272, 26}, {268, 30}, {263, 35}, {258, 40}, // 169
  {251, 45}, {246, 49}, {239, 54}, {232, 60}, {228, 65}
};
uint16_t smHeartCoords[85][2] = {        // 3        // 4                             // 7                  // 9
  { 00, 00}, { 00, 00}, { 00, 00}, { 24,  6}, { 22, 12}, { 19, 18}, { 17, 26}, { 14, 32}, { 11, 38}, {  9, 44},
  {  8, 49}, {  7, 56}, {  4, 62}, {  3, 68}, {  3, 76}, {  4, 85}, {  5, 92}, {  5, 98}, {  6, 104}, {  9, 112},
  { 12, 120}, { 14, 125}, { 18, 128}, { 20, 134}, { 24, 139}, { 29, 144}, { 36, 148}, { 40, 153}, { 48, 158}, { 57, 162},
  { 61, 163}, { 67, 164}, { 73, 165}, { 80, 165}, { 87, 164}, { 95, 163}, {102, 162}, {109, 159}, {115, 155}, {119, 152},
  {125, 150}, {132, 147}, {139, 143}, {145, 140}, {150, 138}, {145, 140}, {164, 144}, {170, 148}, {176, 152}, {182, 158},
  {188, 160}, {194, 163}, {203, 165}, {209, 168}, {217, 169}, {224, 169}, {232, 168}, {238, 167}, {246, 164}, {252, 162},
  {258, 160}, {265, 153}, {270, 148}, {275, 145}, {282, 140}, {287, 133}, {290, 126}, {292, 118}, {294, 112}, {296, 106},
  {297, 98}, {298, 92}, {298, 85}, {295, 78}, {294, 70}, {294, 65}, {293, 60}, {292, 54}, {290, 48}, {288, 42},
  {286, 37}, {282, 28}, {278, 21}, {273, 15}, {269,  9}
};
uint16_t portRCoords[19][2] = {          // 3        // 4                             // 7                  // 9
  { 12, 80}, { 22, 90}, { 38, 96}, { 54, 96}, { 70, 95}, { 82, 87}, { 92, 75}, { 98, 62}, { 98, 48}, { 95, 32},
  { 88, 20}, { 75, 10}, { 60,  3}, { 40,  3}, { 26,  8}, { 12, 18}, {  5, 32}, {  2, 50}, {  5, 65}
};
uint16_t portLCoords[19][2] = {          // 3        // 4                             // 7                  // 9
  { 82, 87}, { 70, 95}, { 54, 96}, { 38, 96}, { 22, 90}, { 12, 80}, {  5, 65}, {  2, 50}, {  5, 32}, { 12, 18},
  { 26,  8}, { 40,  3}, { 60,  3}, { 75, 10}, { 88, 20}, { 95, 32}, { 98, 48}, { 98, 62}, { 92, 75}
};


uint16_t ledPosOffset[19][2] = {
  { 70, 90},       // 00 bottomRing
  { 0, 945},       // 01 bigHeart
  { 150, 1224},    // 02 smallHeart
  { 612, 1400},    // 03 underarm left
  { 612, 1210},    // 04 overarm left
  { 384, 1550},    // 05 eyeLeft
  { 110, 1550},    // 06 rightEye
  { 246, 1536},    // 07 mouth
  { 250, 1600},    // 08 tape
  { 239, 1710},    // 09 tuner
  { 180, 1714},    // 10 indicator
  { 1, 1400},      // 11 underArm right
  { 1, 1240},      // 12 overArm right
  { 315, 800},     // 13 tubeBottomright
  { 80, 800},      // 14 tubeBottomleft
  { 80, 1020},     // 15 tubeTopleft
  { 315, 1020},    // 16 tubeTopright
  { 100, 555},      // 17 port left // 50 change to 100 to try to move tube left a little
  { 400, 555},     // 18 port right
};

uint16_t ledSections[20] = {
  0,     // 0  bottom ring *
  203,   // 1  big heart
  378,   // 2  small heart
  463,   // 3 underarm left
  482,   // 4 overarm left
  506,   // 5  eye left
  599,   // 6  eye right
  692,   // 7  mouth                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
  710,   // 8  tape
  744,   // 9  tuner *
  770,   // 10 indiciator *
  774,   // 11 underarm right
  797,   // 12 overarm right
  825,   // 13 tube bottomright *
  911,   // 14 tube bottomleft *
  1001,  // 15 tube topleft *
  1090,  // 16 tube topright * starred sections are shifted and / or reversed
  1180,  // 17 port left
  1302,  // 18 port right
  1442
};

uint16_t numLedsInSection(uint16_t sectionNum) {
  return ledSections[sectionNum + 1] - ledSections[sectionNum];
}

uint16_t eyeSmileyLeds[24] = {
  34, 35, 40, 41, 42, 43, 44, 45, 46,
  47, 48, 53, 54, 57, 58, 61, 62, 63,
  64, 65, 66, 67, 70, 71
};
uint16_t eyeHeartLeds[56] = {
  4,  5,  6, 16, 26, 27, 28, 34, 35, 36,
  37, 38, 43, 44, 45, 50, 51, 52, 53, 54,
  57, 58, 59, 60, 61, 62, 63, 64, 65, 66,
  67, 68, 69, 70, 71, 72, 73, 74, 75, 76,
  77, 78, 79, 80, 81, 82, 83, 84, 85, 86,
  87, 88, 89, 90, 91, 92
};

bool pacManAnimationMask [16][93] = {
  { 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,      // 9    - frame 0
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 19
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 29
    1, 1, 1, 1, 1, 1, 1, 1, 0, 1,      // 39
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 49
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 59
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 69
    1, 1, 1, 1, 1, 0, 1, 1, 1, 1,      // 79
    1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0
  },
  { 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,      // 9    - frame 1
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 19
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 29
    1, 1, 1, 1, 1, 1, 1, 0, 0, 0,      // 39
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 49
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 59
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 69
    1, 1, 1, 1, 1, 0, 1, 1, 1, 1,      // 79
    1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0
  },
  { 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,      // 9    - frame 2
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 19
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 29
    1, 1, 1, 1, 1, 1, 1, 0, 0, 0,      // 39
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 49
    1, 1, 1, 1, 1, 1, 1, 1, 1, 0,      // 59
    0, 0, 1, 1, 1, 1, 1, 1, 1, 1,      // 69
    1, 1, 1, 1, 1, 0, 1, 1, 1, 1,      // 79
    1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0
  },
  { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,      // 9    - frame 3
    0, 0, 1, 1, 1, 1, 1, 1, 1, 1,      // 19
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 29
    1, 1, 1, 1, 1, 1, 0, 0, 0, 0,      // 39
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 49
    1, 1, 1, 1, 1, 1, 1, 1, 1, 0,      // 59
    0, 0, 1, 1, 1, 1, 1, 1, 1, 1,      // 69
    1, 1, 1, 1, 0, 0, 0, 1, 1, 1,      // 79
    1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0
  },
  { 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,      // 9    - frame 4
    0, 0, 0, 1, 1, 1, 1, 1, 1, 1,      // 19
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 29
    1, 1, 1, 1, 1, 0, 0, 0, 0, 0,      // 39
    0, 0, 1, 1, 1, 1, 1, 1, 1, 1,      // 49
    1, 1, 1, 1, 1, 1, 1, 1, 0, 0,      // 59
    0, 0, 0, 1, 1, 1, 1, 1, 1, 1,      // 69
    1, 1, 1, 1, 0, 0, 0, 1, 1, 1,      // 79
    1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0
  },
  { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,      // 9    - frame 5
    0, 0, 0, 0, 1, 1, 1, 1, 1, 1,      // 19
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 29
    1, 1, 1, 1, 0, 0, 0, 0, 0, 0,      // 39
    0, 0, 0, 1, 1, 1, 1, 1, 1, 1,      // 49
    1, 1, 1, 1, 1, 1, 1, 1, 0, 0,      // 59
    0, 0, 0, 1, 1, 1, 1, 1, 1, 1,      // 69
    1, 1, 1, 0, 0, 0, 0, 0, 1, 1,      // 79
    1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0
  },
  { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,      // 9    - frame 6
    0, 0, 0, 0, 0, 1, 1, 1, 1, 1,      // 19
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 29
    1, 1, 1, 1, 0, 0, 0, 0, 0, 0,      // 39
    0, 0, 0, 1, 1, 1, 1, 1, 1, 1,      // 49
    1, 1, 1, 1, 1, 1, 1, 0, 0, 0,      // 59
    0, 0, 0, 0, 1, 1, 1, 1, 1, 1,      // 69
    1, 1, 1, 0, 0, 0, 0, 0, 1, 1,      // 79
    1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0
  },
  { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,      // 9    - frame 7
    0, 0, 0, 0, 0, 1, 1, 1, 1, 1,      // 19
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 29
    1, 1, 1, 1, 0, 0, 0, 0, 0, 0,      // 39
    0, 0, 0, 1, 1, 1, 1, 1, 1, 1,      // 49
    1, 1, 1, 1, 1, 1, 1, 0, 0, 0,      // 59
    0, 0, 0, 0, 1, 1, 1, 1, 1, 1,      // 69
    1, 1, 1, 0, 0, 0, 0, 0, 1, 1,      // 79
    1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0
  },
  { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,      // 9    - frame 8
    0, 0, 0, 0, 0, 1, 1, 1, 1, 1,      // 19
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 29
    1, 1, 1, 1, 0, 0, 0, 0, 0, 0,      // 39
    0, 0, 0, 1, 1, 1, 1, 1, 1, 1,      // 49
    1, 1, 1, 1, 1, 1, 1, 0, 0, 0,      // 59
    0, 0, 0, 0, 1, 1, 1, 1, 1, 1,      // 69
    1, 1, 1, 0, 0, 0, 0, 0, 1, 1,      // 79
    1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0
  },
  { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,      // 9    - frame 9
    0, 0, 0, 0, 1, 1, 1, 1, 1, 1,      // 19
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 29
    1, 1, 1, 1, 0, 0, 0, 0, 0, 0,      // 39
    0, 0, 0, 1, 1, 1, 1, 1, 1, 1,      // 49
    1, 1, 1, 1, 1, 1, 1, 1, 0, 0,      // 59
    0, 0, 0, 1, 1, 1, 1, 1, 1, 1,      // 69
    1, 1, 1, 0, 0, 0, 0, 0, 1, 1,      // 79
    1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0
  },
  { 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,      // 9    - frame 10
    0, 0, 0, 1, 1, 1, 1, 1, 1, 1,      // 19
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 29
    1, 1, 1, 1, 1, 0, 0, 0, 0, 0,      // 39
    0, 0, 1, 1, 1, 1, 1, 1, 1, 1,      // 49
    1, 1, 1, 1, 1, 1, 1, 1, 0, 0,      // 59
    0, 0, 0, 1, 1, 1, 1, 1, 1, 1,      // 69
    1, 1, 1, 1, 0, 0, 0, 1, 1, 1,      // 79
    1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0
  },
  { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,      // 9    - frame 11
    0, 0, 1, 1, 1, 1, 1, 1, 1, 1,      // 19
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 29
    1, 1, 1, 1, 1, 1, 0, 0, 0, 0,      // 39
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 49
    1, 1, 1, 1, 1, 1, 1, 1, 1, 0,      // 59
    0, 0, 1, 1, 1, 1, 1, 1, 1, 1,      // 69
    1, 1, 1, 1, 0, 0, 0, 1, 1, 1,      // 79
    1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0
  },
  { 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,      // 9    - frame 12
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 19
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 29
    1, 1, 1, 1, 1, 1, 1, 0, 0, 0,      // 39
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 49
    1, 1, 1, 1, 1, 1, 1, 1, 1, 0,      // 59
    0, 0, 1, 1, 1, 1, 1, 1, 1, 1,      // 69
    1, 1, 1, 1, 1, 0, 1, 1, 1, 1,      // 79
    1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0
  },
  { 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,      // 9    - frame 13
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 19
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 29
    1, 1, 1, 1, 1, 1, 1, 0, 0, 0,      // 39
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 49
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 59
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 69
    1, 1, 1, 1, 1, 0, 1, 1, 1, 1,      // 79
    1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0
  },
  { 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,      // 9    - frame 14
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 19
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 29
    1, 1, 1, 1, 1, 1, 1, 1, 0, 1,      // 39
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 49
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 59
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 69
    1, 1, 1, 1, 1, 0, 1, 1, 1, 1,      // 79
    1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0
  },
  { 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,      // 9    - frame 15
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 19
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 29
    1, 1, 1, 1, 1, 1, 1, 1, 0, 1,      // 39
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 49
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 59
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 69
    1, 1, 1, 1, 1, 0, 1, 1, 1, 1,      // 79
    1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0
  },
};

bool pacManAnimationMask2 [8][93] = {
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 9    - frame 0
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 19
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 29
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 39
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 49
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 59
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 69
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 79
    1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 9    - frame 1
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 19
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 29
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 39
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 49
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 59
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 69
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 79
    0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0
  },
  { 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,      // 9    - frame 2
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 19
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 29
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 39
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 49
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 59
    1, 1, 1, 1, 1, 1, 1, 0, 0, 0,      // 69
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 79
    0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1
  },
  { 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,      // 9    - frame 3
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 19
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 29
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 39
    1, 1, 1, 1, 1, 1, 1, 1, 1, 0,      // 49
    0, 0, 1, 1, 1, 1, 1, 1, 1, 1,      // 59
    1, 1, 1, 1, 1, 1, 1, 0, 0, 0,      // 69
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 79
    1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  },
  { 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,      // 9    - frame 4
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 19
    1, 1, 1, 0, 0, 0, 1, 1, 1, 1,      // 29
    1, 1, 1, 1, 1, 1, 1, 0, 0, 0,      // 39
    1, 1, 1, 1, 1, 1, 1, 1, 1, 0,      // 49
    0, 0, 1, 1, 1, 1, 1, 1, 1, 1,      // 59
    0, 1, 1, 1, 1, 1, 1, 1, 0, 1,      // 69
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 79
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 9    - frame 5
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 19
    1, 1, 1, 0, 0, 0, 1, 1, 1, 1,      // 29
    1, 1, 1, 1, 1, 1, 1, 0, 0, 0,      // 39
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 49
    0, 1, 1, 1, 1, 1, 1, 1, 1, 0,      // 59
    0, 0, 1, 1, 1, 1, 1, 1, 1, 1,      // 69
    1, 1, 1, 1, 1, 0, 1, 1, 1, 1,      // 79
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 9    - frame 6
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 19
    1, 1, 1, 1, 0, 1, 1, 1, 1, 1,      // 29
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 39
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 49
    1, 1, 1, 1, 1, 1, 1, 1, 1, 0,      // 59
    0, 0, 1, 1, 1, 1, 1, 1, 1, 1,      // 69
    1, 1, 1, 1, 0, 0, 0, 1, 1, 1,      // 79
    1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1
  },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 9    - frame 7
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 19
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 29
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 39
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 49
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 59
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,      // 69
    1, 1, 1, 1, 0, 0, 0, 1, 1, 1,      // 79
    1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0
  },
};
