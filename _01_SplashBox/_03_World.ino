// MAIN FUNCTIONS
/////////////////

byte floorToBound (byte Value, byte Bound) {
  return floor((double)Value/Bound) * Bound;
}

byte clamp(byte n, byte lower, byte upper) {
    n = ( n > lower ) * n + !( n > lower ) * lower;
    return ( n < upper ) * n + !( n < upper ) * upper;
}

int toScreenX(int x) {
  return x - cameraX;
}

int toScreenY(int y) {
  return y - cameraY;
}

boolean inRay (byte Min, byte Max, byte Value) {
  return Value <= Max && Value >= Min;
}

boolean inRange (byte r, byte v) {
  return inRay(r,r+8,v+2) || inRay(r,r+8,v+6);
}

int ClampInt (int minv, int16_t maxv, int16_t value) {
  if(value < minv)
    return minv;
  else if(value >= maxv)
    return maxv;
  else
    return value;
}


// WORLD MANAGER
/////////////////

#define MaxMapW 48 //64
#define MaxMapH 32 //64

class World {
  public:
  byte MapWidth = 0;
  byte MapHeight = 0;
  byte CurrentLoadedMap = 0;
  
  byte splashMemory[MaxMapW][MaxMapH];
  byte splashMemoryColor[(int)ceil(MaxMapW*MaxMapH/8)];

  void SMSetPaintValueNoColor (byte Paint0, byte Paint1, byte Paint2, byte Paint3, byte setX, byte setY) {
    if(getTile(setX,setY) == 0) {
      return; 
    }
    splashMemory[setX][setY] = (Paint3 << 6) + (Paint2 << 4) + (Paint1 << 2) + Paint0;
  }
  
  void SMSetPaintValue (byte Paint0, byte Paint1, byte Paint2, byte Paint3, byte setX, byte setY, byte color) {
    //TODO: instead of resetting value to 0, reduce the value each call and change the color once the values reach 0
    if(SMGetColor(setX,setY)!=color) {
      SMSetPaintValueNoColor(0,0,0,0,setX,setY);
      SMSetColor(setX, setY, color);
      return;
    }
    
    SMSetColor(setX, setY, color);
    
    if(getTile(setX,setY) == 0) {
      return; 
    }
    splashMemory[setX][setY] = (Paint3 << 6) + (Paint2 << 4) + (Paint1 << 2) + Paint0;
  }
  
  void SMSetColor (byte setX, byte setY, byte Color) {
    int16_t offset = (setX + (setY * MaxMapW)) / 8;
    byte i = (setX + (setY * MaxMapW)) % 8;
  
    byte mask = 1 << i;
    if(Color) {
      splashMemoryColor[offset] |= mask;
    } else {
      splashMemoryColor[offset] &= ~mask;
    }
  }
  
  byte SMGetColor (byte getX, byte getY) {
    int16_t offset = (getX + (getY * MaxMapW)) / 8;
    byte i = (getX + (getY * MaxMapW)) % 8;
    return ((splashMemoryColor[offset] >> i) & B00000001);
  }
  
  byte SMGetRaw (byte getX, byte getY) {
    return splashMemory[getX][getY];
  }

  byte SMGetPaintValueAt (byte getX, byte getY, byte index) {
    if(index == 0) {
      return splashMemory[getX][getY] & B00000011;
    } else if(index == 1) {
      return (splashMemory[getX][getY] >> 2) & B00000011;
    } else if(index == 2) {
      return (splashMemory[getX][getY] >> 4) & B00000011;
    } else if(index == 3) {
      return (splashMemory[getX][getY] >> 6) & B00000011;
    } else if(index == 4) {
      return MergeWalls(splashMemory[getX][getY] & B00000011,(splashMemory[getX][getY] >> 2) & B00000011);
    } else if(index == 5) {
      return MergeWalls((splashMemory[getX][getY] >> 2) & B00000011,(splashMemory[getX][getY] >> 4) & B00000011);
    } else if(index == 6) {
      return MergeWalls((splashMemory[getX][getY] >> 4) & B00000011,(splashMemory[getX][getY] >> 6) & B00000011);
    } else if(index == 7) {
      return MergeWalls((splashMemory[getX][getY] >> 6) & B00000011,splashMemory[getX][getY] & B00000011);
    }
  }

  void SMResetMap () {
    for(byte x = 0; x < MapWidth; x++) {
      for(byte y = 0; y < MapHeight; y++) {
        splashMemory[x][y] = 0;
      }
    }
  }
  
  int16_t MergeWalls (int a, int16_t b) {
    return (a+b)/2;
  }
  
  int16_t PixelInCollider (byte PIMX, byte PIMY, byte PICX, byte PICY) { //PIM = Pos in map (0-255), PIC = Pos in cube (0-8)
    switch (getTile(PIMX,PIMY) != 0) {
      case 0:
        return 0;
      case 1:
        return 1;
      default:
        return 0;
    }
  }

  byte getTile(byte x, byte y){
    return GetMap[CurrentLoadedMap][4 + (x+y*MapWidth)];
  }

  void Draw () {
    int16_t xMin = cameraX / 8;
    int16_t xMax = LCDWIDTH / 8 + cameraX / 8 + 2;
    int16_t yMin = cameraY / 8;
    int16_t yMax = LCDHEIGHT / 8 + cameraY / 8 + 2;
    
    for(int y = yMin; y < yMax; y++) {
      for(int x = xMin; x < xMax; x++ ) {
        
        if(getTile(x,y) == 0) {
          continue;
        }

        //gb.display.setColor(WHITE);
        //gb.display.fillRect(CPosX + x*8, CPosY + y*8, 8, 8);
        gb.display.setColor(BLACK);
        gb.display.drawBitmap(x*8 - cameraX, y*8 - cameraY, mapTiles[getTile(x,y)]);
        
        if(getTile(x,y) != 0) {
          //V = DebugBytes;
          cC = SMGetColor(x,y);
          V1 = SMGetPaintValueAt(x,y,0);
          V3 = SMGetPaintValueAt(x,y,1);
          V5 = SMGetPaintValueAt(x,y,2);
          V7 = SMGetPaintValueAt(x,y,3);
          
          V4 = SMGetPaintValueAt(x,y,4);
          V6 = SMGetPaintValueAt(x,y,5);
          V0 = SMGetPaintValueAt(x,y,6);
          V2 = SMGetPaintValueAt(x,y,7);
          
          for(char x1 = -1; x1 < 2; x1++) {
            for(char y1 = -1; y1 < 2; y1++) {
              if(!(x+x1<0 || x+x1>=MapWidth || y+y1<0 || y+y1>=MapHeight)) {
                if(getTile(x+x1,y+y1)==0) {

                  //Ink
                  if(cC == 1) {
                    gb.display.setColor(WHITE);
                  } else if(cC == 0) {
                    gb.display.setColor(BLACK);
                  }
                  
                  if(x1<0) {
                    if(y1<0) {
                      if(getTile(x+-1,y+0) == 1 && getTile(x+0,y+-1) == 1) {
                        gb.display.drawBitmap(x*8 - cameraX, y*8 - cameraY, splashes[4+V6], ROTCCW, NOFLIP); //WORKS //Kinda confirmed?
                      }
                    } else if(y1>0) {
                      if(getTile(x+-1,y+0) == 1 && getTile(x+0,y+1) == 1) {
                        gb.display.drawBitmap(x*8 - cameraX, y*8 - cameraY, splashes[4+V0], ROT180, NOFLIP); //WORKS
                      }
                    } else if(y1==0) {
                      gb.display.drawBitmap(x*8 - cameraX, y*8 - cameraY, splashes[V7], ROTCCW, NOFLIP);
                    }
                  }
                  if(x1>0) {
                    if(y1<0) {
                      if(getTile(x+1,y+0) == 1 && getTile(x+0,y+-1) == 1) {
                        gb.display.drawBitmap(x*8 - cameraX, y*8 - cameraY, splashes[4+V4], NOROT, NOFLIP); //WORKS
                      }
                    } else if(y1>0) {
                      if(getTile(x+0,y+1) == 1 && getTile(x+1,y+0) == 1) {
                        gb.display.drawBitmap(x*8 - cameraX, y*8 - cameraY, splashes[4+V2], ROTCW, NOFLIP); //WORKS //Kinda confirmed?
                      }
                    } else if(y1==0) {
                      gb.display.drawBitmap(x*8 - cameraX, y*8 - cameraY, splashes[V3], ROTCW, NOFLIP);
                    }
                  }
                  if(x1==0) {
                    if(y1<0) {
                      gb.display.drawBitmap(x*8 - cameraX, y*8 - cameraY, splashes[V1], NOROT, NOFLIP);
                    } else if(y1>0) {
                      gb.display.drawBitmap(x*8 - cameraX, y*8 - cameraY, splashes[V5], ROT180, NOFLIP);
                    }
                  }
                }
              }
            }
          }
          for(char x1 = -1; x1 < 2; x1++) {
            for(char y1 = -1; y1 < 2; y1++) {
              if(!(x+x1<0 || x+x1>=MapWidth || y+y1<0 || y+y1>=MapHeight)) {
                if(getTile(x+x1,y+y1)==0) {
                  //Outline
                  gb.display.setColor(BLACK);
                  if(x1<0) {
                    if(y1<0) {
                      if(getTile(x+-1,y+0) == 1 && getTile(x+0,y+-1) == 1) {
                        gb.display.drawBitmap(x*8 - cameraX, y*8 - cameraY, outlines[2+4+3]);
                      }
                    } else if(y1>0) {
                      if(getTile(x+-1,y+0) == 1 && getTile(x+0,y+1) == 1) {
                        gb.display.drawBitmap(x*8 - cameraX, y*8 - cameraY, outlines[2+4+0]);
                      }
                    } else if(y1==0) {
                      gb.display.drawBitmap(x*8 - cameraX, y*8 - cameraY, outlines[2+3]);
                    }
                  }
                  if(x1>0) {
                    if(y1<0) {
                      if(getTile(x+1,y+0) == 1 && getTile(x+0,y+-1) == 1) {
                        gb.display.drawBitmap(x*8 - cameraX, y*8 - cameraY, outlines[2+4+2]);
                      }
                    } else if(y1>0) {
                      if(getTile(x+0,y+1) == 1 && getTile(x+1,y+0) == 1) {
                        gb.display.drawBitmap(x*8 - cameraX, y*8 - cameraY, outlines[2+4+1]);
                      }
                    } else if(y1==0) {
                      gb.display.drawBitmap(x*8 - cameraX, y*8 - cameraY, outlines[2+1]);
                    }
                  }
                  if(x1==0) {
                    if(y1<0) {
                      gb.display.drawBitmap(x*8 - cameraX, y*8 - cameraY, outlines[2+0]);
                    } else if(y1>0) {
                      gb.display.drawBitmap(x*8 - cameraX, y*8 - cameraY, outlines[2+2]);
                    }
                  }
                }
              }
            }
          }
          
        }
        
      }
    }
  }

  void Update () {
    Draw();
  }
};

World world;
