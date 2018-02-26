// INITIALIZATION
/////////////////

#include <Gamebuino-Meta.h>
#include <math.h>

#define LCDWIDTH 80
#define LCDHEIGHT 64

#define AnimWALKSPEED 4
#define AnimRUNSPEED 2

#define SCALE 8
#define VFORCE 5

#define BCOUNT 16

#define STARTLENGHT 70
#define STARTLENGHT2 130

#define MapHeader 4

byte cinematicSkip = 0;

byte revertColors = 0;
int16_t colorGroup = 1;

int16_t cameraX, cameraY, shakeTimeLeft, shakeAmplitude;

uint8_t cpuLoad = 0;
uint8_t lastLoad[8];

uint32_t Coin = 0;
uint8_t Level = 1;

//UI and Screen parameters
bool IsPlaying = false; //Starts game (GameState define mode, 0:Classic, 1:Rainmaker, 2:Zones, 3:Tower, 4:Clam, 5:SalmonRun)
uint8_t GameState = 0; //0: TitleScreen, //1: Inkopolis, //2: WeaponShop, //3: HatShop, //4: GearSelect, //5: PlaySelection, //6: SalmonRunSelection, //7: CharSelect
bool FreezePlayers = true;
int16_t AnimationTimer;
int32_t AnimationTimer2;
int32_t AnimationTimer3;
int32_t AnimationTimer4;
int32_t AnimationTimer5;

byte SelectedGender = 2; //0: F, 1: M, 2: N/A
byte SelectedHaircut = 4; //4: N/A

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
  (Color)0xf779, //(Color)0xf779 White
  (Color)0xacd0, //(Color)0xacd0 Grey
  (Color)0x730b, //(Color)0x730b Dark Grey
  (Color)0x2923, //(Color)0x2923 Black
  (Color)0xb15a, //(Color)0xb15a Purple
  (Color)0xc9ae, //(Color)0xc9ae Magenta
  (Color)0xe985, //(Color)0xe985 Red
  (Color)0xfc03, //(Color)0xfc03 Orange
  (Color)0xf5a2, //(Color)0xf5a2 Yellow
  (Color)0x8624, //(Color)0x8624 Green
  (Color)0x34a4, //(Color)0x34a4 Dark Green
  (Color)0x3291, //(Color)0x3291 Dark Blue
  (Color)0x3415, //(Color)0x3415 Blue
  (Color)0x461b, //(Color)0x461b Light Blue
  (Color)0xf62f, //(Color)0xf62f Beige (Light Skin)
  (Color)0xcc47  //(Color)0xcc47 Brown (Dark Skin)
};

Color palettePYellow[] = {  
  (Color)0xf779, //(Color)0xf779 White
  (Color)0xacd0, //(Color)0xacd0 Grey
  (Color)0x730b, //(Color)0x730b Dark Grey
  (Color)0x2923, //(Color)0x2923 Black
  (Color)0xb15a, //(Color)0xb15a Purple
  (Color)0xc9ae, //(Color)0xc9ae Magenta
  (Color)0xfc03, //(Color)0xe985 Red
  (Color)0xe985, //(Color)0xfc03 Orange
  (Color)0xf5a2, //(Color)0xf5a2 Yellow
  (Color)0x8624, //(Color)0x8624 Green
  (Color)0x34a4, //(Color)0x34a4 Dark Green
  (Color)0x3291, //(Color)0x3291 Dark Blue
  (Color)0x3415, //(Color)0x3415 Blue
  (Color)0x461b, //(Color)0x461b Light Blue
  (Color)0xf62f, //(Color)0xf62f Beige (Light Skin)
  (Color)0xcc47  //(Color)0xcc47 Brown (Dark Skin)
};

Color palettePOrange[] = {  
  (Color)0xf779, //(Color)0xf779 White
  (Color)0xacd0, //(Color)0xacd0 Grey
  (Color)0x730b, //(Color)0x730b Dark Grey
  (Color)0x2923, //(Color)0x2923 Black
  (Color)0xb15a, //(Color)0xb15a Purple
  (Color)0xc9ae, //(Color)0xc9ae Magenta
  (Color)0xe985, //(Color)0xe985 Red
  (Color)0xf5a2, //(Color)0xfc03 Orange
  (Color)0xfc03, //(Color)0xf5a2 Yellow
  (Color)0x8624, //(Color)0x8624 Green
  (Color)0x34a4, //(Color)0x34a4 Dark Green
  (Color)0x3291, //(Color)0x3291 Dark Blue
  (Color)0x3415, //(Color)0x3415 Blue
  (Color)0x461b, //(Color)0x461b Light Blue
  (Color)0xf62f, //(Color)0xf62f Beige (Light Skin)
  (Color)0xcc47  //(Color)0xcc47 Brown (Dark Skin)
};

Color palettePRed[] = {  
  (Color)0xf779, //(Color)0xf779 White
  (Color)0xacd0, //(Color)0xacd0 Grey
  (Color)0x730b, //(Color)0x730b Dark Grey
  (Color)0x2923, //(Color)0x2923 Black
  (Color)0xf5a2, //(Color)0xb15a Purple
  (Color)0xc9ae, //(Color)0xc9ae Magenta
  (Color)0xb15a, //(Color)0xe985 Red
  (Color)0xfc03, //(Color)0xfc03 Orange
  (Color)0xe985, //(Color)0xf5a2 Yellow
  (Color)0x8624, //(Color)0x8624 Green
  (Color)0x34a4, //(Color)0x34a4 Dark Green
  (Color)0x3291, //(Color)0x3291 Dark Blue
  (Color)0x3415, //(Color)0x3415 Blue
  (Color)0x461b, //(Color)0x461b Light Blue
  (Color)0xf62f, //(Color)0xf62f Beige (Light Skin)
  (Color)0xcc47  //(Color)0xcc47 Brown (Dark Skin)
};

Color palettePMagenta[] = {  
  (Color)0xf779, //(Color)0xf779 White
  (Color)0xacd0, //(Color)0xacd0 Grey
  (Color)0x730b, //(Color)0x730b Dark Grey
  (Color)0x2923, //(Color)0x2923 Black
  (Color)0xb15a, //(Color)0xb15a Purple
  (Color)0xf5a2, //(Color)0xc9ae Magenta
  (Color)0xe985, //(Color)0xe985 Red
  (Color)0xfc03, //(Color)0xfc03 Orange
  (Color)0xc9ae, //(Color)0xf5a2 Yellow
  (Color)0x8624, //(Color)0x8624 Green
  (Color)0x34a4, //(Color)0x34a4 Dark Green
  (Color)0x3291, //(Color)0x3291 Dark Blue
  (Color)0x3415, //(Color)0x3415 Blue
  (Color)0x461b, //(Color)0x461b Light Blue
  (Color)0xf62f, //(Color)0xf62f Beige (Light Skin)
  (Color)0xcc47  //(Color)0xcc47 Brown (Dark Skin)
};

Color palettePBlue[] = {  
  (Color)0xf779, //(Color)0xf779 White
  (Color)0xacd0, //(Color)0xacd0 Grey
  (Color)0xe985, //(Color)0x730b Dark Grey
  (Color)0x2923, //(Color)0x2923 Black
  (Color)0xb15a, //(Color)0xb15a Purple
  (Color)0xc9ae, //(Color)0xc9ae Magenta
  (Color)0x730b, //(Color)0xe985 Red
  (Color)0xfc03, //(Color)0xfc03 Orange
  (Color)0x3291, //(Color)0xf5a2 Yellow
  (Color)0x8624, //(Color)0x8624 Green
  (Color)0x34a4, //(Color)0x34a4 Dark Green
  (Color)0xf5a2, //(Color)0x3291 Dark Blue
  (Color)0x3415, //(Color)0x3415 Blue
  (Color)0x461b, //(Color)0x461b Light Blue
  (Color)0xf62f, //(Color)0xf62f Beige (Light Skin)
  (Color)0xcc47  //(Color)0xcc47 Brown (Dark Skin)
};

Color palettePGreen[] = {  
  (Color)0xf779, //(Color)0xf779 White
  (Color)0xacd0, //(Color)0xacd0 Grey
  (Color)0x730b, //(Color)0x730b Dark Grey
  (Color)0x2923, //(Color)0x2923 Black
  (Color)0xb15a, //(Color)0xb15a Purple
  (Color)0xc9ae, //(Color)0xc9ae Magenta
  (Color)0x34a4, //(Color)0xe985 Red
  (Color)0xfc03, //(Color)0xfc03 Orange
  (Color)0x8624, //(Color)0xf5a2 Yellow
  (Color)0xf5a2, //(Color)0x8624 Green
  (Color)0xe985, //(Color)0x34a4 Dark Green
  (Color)0x3291, //(Color)0x3291 Dark Blue
  (Color)0x3415, //(Color)0x3415 Blue
  (Color)0x461b, //(Color)0x461b Light Blue
  (Color)0xf62f, //(Color)0xf62f Beige (Light Skin)
  (Color)0xcc47  //(Color)0xcc47 Brown (Dark Skin)
};

void setColorToGroup (byte cC) {
  switch(colorGroup) {
    case 0:
    if(cC == 0) {
      gb.display.setColor((ColorIndex)8);
    } else {
      gb.display.setColor((ColorIndex)11);
    }
    break;
    case 1:
    if(cC == 0) {
      gb.display.setColor((ColorIndex)5);
    } else {
      gb.display.setColor((ColorIndex)9);
    }
    break;
    case 2:
    if(cC == 0) {
      gb.display.setColor((ColorIndex)7);
    } else {
      gb.display.setColor((ColorIndex)11);
    }
    break;
    case 3:
    if(cC == 0) {
      gb.display.setColor((ColorIndex)5);
    } else {
      gb.display.setColor((ColorIndex)11);
    }
    break;
    case 4:
    if(cC == 0) {
      gb.display.setColor((ColorIndex)6);
    } else {
      gb.display.setColor((ColorIndex)11);
    }
    break;
    case 5:
    if(cC == 0) {
      gb.display.setColor((ColorIndex)5);
    } else {
      gb.display.setColor((ColorIndex)7);
    }
    break;
    case 6:
    if(cC == 0) {
      gb.display.setColor((ColorIndex)9);
    } else {
      gb.display.setColor((ColorIndex)11);
    }
    break;
  }
}

void setPaletteToColorGroup (byte Color, byte Group) {
  switch(Group) {
    case 0:
    if(Color == 0) {
      gb.display.colorIndex = palettePYellow;
    } else {
      gb.display.colorIndex = palettePBlue;
    }
    break;
    case 1:
    if(Color == 0) {
      gb.display.colorIndex = palettePMagenta;
    } else {
      gb.display.colorIndex = palettePGreen;
    }
    break;
    case 2:
    if(Color == 0) {
      gb.display.colorIndex = palettePOrange;
    } else {
      gb.display.colorIndex = palettePBlue;
    }
    break;
    case 3:
    if(Color == 0) {
      gb.display.colorIndex = palettePMagenta;
    } else {
      gb.display.colorIndex = palettePBlue;
    }
    break;
    case 4:
    if(Color == 0) {
      gb.display.colorIndex = palettePRed;
    } else {
      gb.display.colorIndex = palettePBlue;
    }
    break;
    case 5:
    if(Color == 0) {
      gb.display.colorIndex = palettePMagenta;
    } else {
      gb.display.colorIndex = palettePOrange;
    }
    break;
    case 6:
    if(Color == 0) {
      gb.display.colorIndex = palettePGreen;
    } else {
      gb.display.colorIndex = palettePBlue;
    }
    break;
  }  
}

template<typename T> T Mul8 (T v) {
    return v << 3;
    //return v*8;
}

template<typename T> T Div8(T v) {
    return v >> 3;
    //return v/8;
}
