int16_t inkX = 0;
int16_t inkY = 0;

class Bullets:
  public Object {
  public:
    uint16_t Timer = 0;
    bool IsDead = true;
    byte color = 0;
    byte Owner = 0;
    byte Damage = 7;
    uint16_t BulletTimeLimit = 300;
    int16_t gravity = 0;
    virtual int16_t getWidth() {
      return 3;
    };
    virtual int16_t getHeight() {
      return 3;
    };
    virtual int16_t getGravity() {
      return gravity;
    };
    virtual int16_t getXFriction() {
      return 0;
    };
    virtual int16_t getYFriction() {
      return 0;
    };
    virtual int16_t getXBounce() {
      return 90;
    };
    virtual int16_t getYBounce() {
      return 10;
    };
    virtual byte getCollisionQuality() {
      return 0;
    };

    void Draw () {
      if(isOffScreen())
        return; //skip boxes which are out of the screen

      switch(colorGroup) {
        case 0:
        if(color == 0) {
          gb.display.setColor((ColorIndex)8);
        } else {
          gb.display.setColor((ColorIndex)11);
        }
        break;
        case 1:
        if(color == 0) {
          gb.display.setColor((ColorIndex)5);
        } else {
          gb.display.setColor((ColorIndex)9);
        }
        break;
        case 2:
        if(color == 0) {
          gb.display.setColor((ColorIndex)7);
        } else {
          gb.display.setColor((ColorIndex)11);
        }
        break;
        case 3:
        if(color == 0) {
          gb.display.setColor((ColorIndex)5);
        } else {
          gb.display.setColor((ColorIndex)11);
        }
        break;
        case 4:
        if(color == 0) {
          gb.display.setColor((ColorIndex)6);
        } else {
          gb.display.setColor((ColorIndex)11);
        }
        break;
        case 5:
        if(color == 0) {
          gb.display.setColor((ColorIndex)5);
        } else {
          gb.display.setColor((ColorIndex)7);
        }
        break;
        case 6:
        if(color == 0) {
          gb.display.setColor((ColorIndex)9);
        } else {
          gb.display.setColor((ColorIndex)11);
        }
        break;
      }

      if(Timer != 0) {
        if(/*vx>0*/true) {
          gb.display.drawBitmap(toScreenX(x/SCALE-3), toScreenY(y/SCALE-3), bulletsSprite[ClampInt(0,4,Timer/(BulletTimeLimit/4))],0,FLIPH);
        } else {
          gb.display.drawBitmap(toScreenX(x/SCALE-3), toScreenY(y/SCALE-3), bulletsSprite[ClampInt(0,4,Timer/(BulletTimeLimit/4))],0,NOFLIP);
        }
      }
    }

    void Die () {
      IsDead = true;
      Timer = 0;
    }
    
    void Recreate () {
      IsDead = false;
      collided = false;
    }

    void Update () {
      if(Timer < BulletTimeLimit && !IsDead) {
        Timer++;
      } else {
        Die();
      }
      
      if(collided && !IsDead) {
        inkX = (x/SCALE);//+(vx>=0?1:-1)
        inkY = (y/SCALE);//+(vy>=0?1:-1)

        //UpdateGrounding();
        /*if(IsGroundedDown) {
          inkY+=1;
        } else if(IsGroundedUp) {
          inkY-=1;
        } else if(IsGroundedLeft) {
          inkX-=1;
        } else if(IsGroundedRight) {
          inkX+=1;
        }*/
        
        inkX = constrain(inkX,0,(world.MapWidth-1)*8);
        inkY = constrain(inkY,0,(world.MapHeight-1)*8);

        for(int8_t x = -1; x < 2; x++) {
          for(int8_t y = -1; y < 2; y++) {
            if((inkX+x == constrain((inkX+x*4)/8,0,world.MapWidth-1))&&((inkY+y*4)/8 == constrain(inkY+y,0,world.MapWidth-1))) {
              V0 = constrain(world.SMGetPaintValueAt((inkX+x*4)/8,(inkY+y*4)/8,0), 0, 3);
              V1 = constrain(world.SMGetPaintValueAt((inkX+x*4)/8,(inkY+y*4)/8,1), 0, 3);
              V2 = constrain(world.SMGetPaintValueAt((inkX+x*4)/8,(inkY+y*4)/8,2), 0, 3);
              V3 = constrain(world.SMGetPaintValueAt((inkX+x*4)/8,(inkY+y*4)/8,3), 0, 3);
              
              if(x==-1 && y==0) {
                if(world.getTile((x/SCALE-4)/8,(y/SCALE+0)/8) != 0) {
                  V0 = constrain(world.SMGetPaintValueAt((inkX-4)/8,inkY,0), 0, 3);
                  V1 = constrain(world.SMGetPaintValueAt((inkX-4)/8,inkY,1)+1+IsGroundedLeft, 0, 3);
                  V2 = constrain(world.SMGetPaintValueAt((inkX-4)/8,inkY,2), 0, 3);
                  V3 = constrain(world.SMGetPaintValueAt((inkX-4)/8,inkY,3), 0, 3);
                }
              }
              if(x==1 && y==0) {
                if(world.getTile((x/SCALE+4)/8,(y/SCALE+0)/8) != 0) {
                  V0 = constrain(world.SMGetPaintValueAt((inkX+4)/8,inkY,0), 0, 3);
                  V1 = constrain(world.SMGetPaintValueAt((inkX+4)/8,inkY,1), 0, 3);
                  V2 = constrain(world.SMGetPaintValueAt((inkX+4)/8,inkY,2), 0, 3);
                  V3 = constrain(world.SMGetPaintValueAt((inkX+4)/8,inkY,3)+1+IsGroundedRight, 0, 3);
                }
              }
              if(y==1 && x==0) {
                if(world.getTile((x/SCALE+0)/8,(y/SCALE+4)/8) != 0) {
                  V0 = constrain(world.SMGetPaintValueAt(inkX,(inkY+4)/8,0)+1+IsGroundedDown, 0, 3);
                  V1 = constrain(world.SMGetPaintValueAt(inkX,(inkY+4)/8,1), 0, 3);
                  V2 = constrain(world.SMGetPaintValueAt(inkX,(inkY+4)/8,2), 0, 3);
                  V3 = constrain(world.SMGetPaintValueAt(inkX,(inkY+4)/8,3), 0, 3);
                }
              }
              if(y==-1 && x==0) {
                if(world.getTile((x/SCALE+0)/8,(y/SCALE-4)/8) != 0) {
                  V0 = constrain(world.SMGetPaintValueAt(inkX,(inkY-4)/8,0), 0, 3); 
                  V1 = constrain(world.SMGetPaintValueAt(inkX,(inkY-4)/8,1), 0, 3); 
                  V2 = constrain(world.SMGetPaintValueAt(inkX,(inkY-4)/8,2)+1+IsGroundedUp, 0, 3); 
                  V3 = constrain(world.SMGetPaintValueAt(inkX,(inkY-4)/8,3), 0, 3);
                }
              }

              world.SMSetPaintValue(
                constrain(V0, 0, 3),
                constrain(V1, 0, 3),
                constrain(V2, 0, 3),
                constrain(V3, 0, 3),
                constrain((inkX+x*4)/8,0,world.MapWidth-1),
                constrain((inkY+y*4)/8,0,world.MapHeight-1),
                color
              );
            }
          }
        }

        //gb.display.setColor(RED);
        //gb.display.fillRect(toScreenX(inkX*8),toScreenY(inkY*8),8,8);
        
        Die();
      }

      if(!IsDead) {
        Object::Update();

        Draw();
        /*if(!Object::isOffScreen()) {
          if(color == 0) {
            gb.display.fillRect(toScreenX(x/SCALE), toScreenY(y/SCALE), getWidth(), getHeight());
          } else {
            gb.display.drawRect(toScreenX(x/SCALE), toScreenY(y/SCALE), getWidth(), getHeight());
          }
        }*/
      }
    }
};

class BulletsManager {
  public:
  Bullets bullets[BCOUNT];

  int8_t spawnBullet (int16_t x, int16_t y, int16_t vx, int16_t vy, byte color, byte owner) {
    for(byte i = 0; i < BCOUNT; i++) {
      if(bullets[i].IsDead) {
        bullets[i].Recreate();
        bullets[i].x = x;
        bullets[i].y = y;
        bullets[i].vx = vx;
        bullets[i].vy = vy;
        bullets[i].color = color;
        bullets[i].Owner = owner;
        return i;
      }
    }
    return -1;
  }

  void Update () {
    for(byte i = 0; i < BCOUNT; i++) {
      bullets[i].Update();
    }
  }
};

BulletsManager bulletsManager;
