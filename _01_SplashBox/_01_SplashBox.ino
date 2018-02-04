// INITIALIZATION
/////////////////

#include <Gamebuino-Meta.h>
//#include <Gamebuino-EEPROM.h>
#include <math.h>

#define LCDWIDTH 160
#define LCDHEIGHT 128

#define SCALE 8
#define VFORCE 5

#define BCOUNT 8 //14

#define STARTLENGHT 40 //110

#define BouncyMath1 0.0322580//6452
#define BouncyMath2 -0.0483870f//9677
#define BouncyMath3 -0.0393700f//7874
#define BouncyMath4 0.0236220f//4724


int cameraX, cameraY, shakeTimeLeft, shakeAmplitude;

bool IsPlaying = false;
bool FreezePlayers = true;

int AnimationTimer;

bool LastDirection = true;
byte curX = 48;
byte curY = 24;

byte* D;
byte V0 = 0;
byte V1 = 0;
byte V2 = 0;
byte V3 = 0;
byte V4 = 0;
byte V5 = 0;
byte V6 = 0;
byte V7 = 0;
byte cC = 0;

Color palette[] = {  
  (Color)0xf779,
  (Color)0xacd0,
  (Color)0x730b,
  (Color)0x2923,
  (Color)0xb15a,
  (Color)0xc9ae,
  (Color)0xe985,
  (Color)0xfc03,
  (Color)0xf5a2,
  (Color)0x8624,
  (Color)0x34a4,
  (Color)0x3291,
  (Color)0x3415,
  (Color)0x461b,
  (Color)0xf62f,
  (Color)0xcc47
};
