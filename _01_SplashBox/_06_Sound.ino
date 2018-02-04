// SOUND
/////////////////

const int16_t soundfx[9][8] = {
  {1,27,90,2,7,7,3,7}, //jump <
  {1,27,112,1,1,1,6,4}, // walljump <
  {0,27,57,1,1,1,6,4}, // unlockdoor <
  {0,9,57,1,6,8,7,8}, // land
  {0,46,57,1,0,18,7,47}, // getkey <
  {0,38,79,3,6,7,7,20}, // finish <
  {0,30,68,3,0,0,7,5}, // click <
  {0,30,55,1,7,0,7,15}, //death <
  {1,28,51,2,2,14,7,7} // groundpound <
};

void sfx(int16_t  fxno, int16_t channel) {
  //gb.sound.command(0, soundfx[fxno][6], 0, channel); // set volume
  //gb.sound.command(1, soundfx[fxno][0], 0, channel); // set waveform
  //gb.sound.command(2, soundfx[fxno][5], -soundfx[fxno][4], channel); // set volume slide
  //gb.sound.command(3, soundfx[fxno][3], soundfx[fxno][2] - 58, channel); // set pitch slide
  //gb.sound.playNote(soundfx[fxno][1], soundfx[fxno][7], channel); // play note
  //WAVEFORM, PITCH, PMD, PMT, VMD, VMT, VOL, LENGTH
}
