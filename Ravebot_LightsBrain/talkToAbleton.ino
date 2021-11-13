bool newBeat=false;

void playRandomTune() {
 currentGenre = random(8);
 
 playRandomTune(currentGenre);
}

void playRandomTune(int16_t genre) {
  int track = 0;

  do {
    // pick next track
    track = random(numberOfTunesInGenre(genre));
  } while (playedTuneHistoryContainsTrack(genre, track));
  
  playTune(genre, track, true);
}

void playTune(int16_t genre, int16_t track, bool alterHistory) {
  setCurrentTune(genre, track);
  // setAbletonTempo(currentTune.bpm-1);
  sendFullStop();
  stopAllAbletonClips(); 
  delay(20);

  if (alterHistory)
    updateGenreAndTrackHistory(genre, track);

  currentGenre = genre % 8;
  track = (track % numberOfTunesInGenre(genre));  
  deckASelected = true;

  // change the current track in this program
  currentBar = -1;
  fakeBeatCount = 0;
  sixteenBeats = 0;
  totalBeats = 0;
  lastBeatTime = 0;
  timeyInTime = 0;

  if (testMode) {
     Serial.print("NOW PLAYING: ");
     Serial.print(genre);
     Serial.print("/");
     Serial.println(track);
  }
  currentlyMixing=false;

  setCrossfader(0);

  // tell the other arduino what you're doing
  sendSerialToMega(2,(genre*100)+track);

  // send stuff to ableton to start the new track  
  delay(80);
  playAbletonTrack(genre, track, true);
  start16BeatAbletonTrack(); // start the midi track in ableton which sends midi time codes back here
  delay(10);
  ledIntensity=lastSentLedIntensity;
  changeLightPattern();
  delay(10);
  startRobotVoiceTrack();
 
  chooseNextTrack();
  calculateMixDurationAndStart();

  if (testMode)
    showLast20Tracks();

  delay(5);
  setAbletonTempo(currentTune.bpm);

}

void updateGenreAndTrackHistory(int16_t genre, int16_t track) {

  for (int16_t x = 19; x > 0; x--)
    last20Genres[x] = last20Genres[x-1];  
  last20Genres[0] = genre;

  for (int x = 19; x > 0; x--)
    last20Tracks[x] = last20Tracks[x-1];    
  last20Tracks[0] = track;
}

void playAbletonTrack(int16_t channel, int16_t trackNumber, bool playSideA) {
  int abletonChannel = channel*2;
  if (!playSideA)
    abletonChannel++;

  sendMidi(abletonChannel+176, trackNumber+1, 127);
}

void stopAbletonChannel(int16_t channel, bool stopSideA) {
  int abletonChannel = channel*2;
  if (stopSideA)
    abletonChannel++;

  sendMidi(abletonChannel+176, 0, 127);
}


void sendFullStop() {
  sendMidi(176, 120, 127);
}

void stopAllAbletonClips() {
  sendMidi(176, 125, 127);
}

void start16BeatAbletonTrack() {
  sendMidi(176, 126, 127); // channel 1, track 126, value 127.
}

void setMainVolume(int16_t newVolume) {

  if (newVolume < 0)
    newVolume = 0;
  
  if (newVolume > 110)
    newVolume = 110;

  mainVolume = newVolume;
  
  sendMidi(176, 127, mainVolume);
}

void setAbletonTempo(int16_t tempo) { // 80 - 207 bpm only
  if (abletonBpm == tempo)
    return;
  
  sendMidi(177, 125, tempo-80);

  abletonBpm = tempo;
}

void setRobotVoiceVolume(int16_t volume) { // 0 - 127
  sendMidi(177, 126, volume);
}

void startRobotVoiceTrack() {
  sendMidi(178, 125, 127); // channel 3, track 125, value 127.
}

void setCrossfader(int value) { // 0 - 127     176
  sendMidi(177, 127, value);
}

//  plays a MIDI note.
// 176 is channel=1, 190 channel=15
void sendMidi(int16_t channel, int16_t trackNumber, int16_t velocity) {
  if (testMode) {
    sendMidiTest(channel, trackNumber, velocity);
    return;
  }
  
  if ((channel < 176) || (channel > 192))
    return;
  if ((trackNumber < 0) || (trackNumber > 127))
    return;
  if ((velocity < 0) || (velocity > 127))
    return;
  
  Serial.write(channel);
  Serial.write(trackNumber);
  Serial.write(velocity);
}

void sendMidiTest(int16_t channel, int16_t trackNumber, int16_t velocity) {
  // (176, 126, 127); // channel 1, track 126, value 127.
  
  Serial.print("Channel:");
  Serial.print(channel); // - 175);

  Serial.print(" Note:");
  Serial.print(trackNumber);

  Serial.print(" Value:");
  Serial.println(velocity);
}
