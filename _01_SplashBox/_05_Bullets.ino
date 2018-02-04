int inkX = 0;
int inkY = 0;

#define BulletTimeLimit 300

class Bullets:
  public Object {
  public:
    short Timer = 0;
    bool IsDead = true;
    byte color = 0;
    byte Owner = 0;
    virtual int16_t getWidth() {
      return 3;
    };
    virtual int16_t getHeight() {
      return 3;
    };
    virtual int16_t getGravity() {
      return 10;
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
      return 1;
    };
    virtual int16_t getDamage() {
      return 30;
    };

    void Draw () {
      if(isOffScreen())
        return; //skip boxes which are out of the screen
      if(vx>0) {
        gb.display.drawBitmap(toScreenX(x/SCALE-3), toScreenY(y/SCALE-3), bulletsSprite[ClampInt(0,4,Timer/12)],0,FLIPH);
      } else {
        gb.display.drawBitmap(toScreenX(x/SCALE-3), toScreenY(y/SCALE-3), bulletsSprite[ClampInt(0,4,Timer/12)],0,NOFLIP);
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
        inkX = (x/SCALE/8);//+(vx>=0?1:-1)
        inkY = (y/SCALE/8);//+(vy>=0?1:-1)

        UpdateGrounding();
        if(IsGroundedDown) {
          inkY+=1;
        } else if(IsGroundedUp) {
          inkY+=-1;
        } else if(IsGroundedLeft) {
          inkX+=-1;
        } else if(IsGroundedRight) {
          inkX+=1;
        }
        
        inkX = constrain(inkX,0,world.MapWidth-1);
        inkY = constrain(inkY,0,world.MapHeight-1);
        
        if(IsGroundedRight) {
          V0 = constrain(world.SMGetPaintValueAt(inkX,inkY,0), 0, 3);
          V1 = constrain(world.SMGetPaintValueAt(inkX,inkY,1), 0, 3);
          V2 = constrain(world.SMGetPaintValueAt(inkX,inkY,2), 0, 3);
          V3 = constrain(world.SMGetPaintValueAt(inkX,inkY,3)+1, 0, 3);
        } else if(IsGroundedLeft) {
          V0 = constrain(world.SMGetPaintValueAt(inkX,inkY,0), 0, 3);
          V1 = constrain(world.SMGetPaintValueAt(inkX,inkY,1)+1, 0, 3);
          V2 = constrain(world.SMGetPaintValueAt(inkX,inkY,2), 0, 3);
          V3 = constrain(world.SMGetPaintValueAt(inkX,inkY,3), 0, 3);
        } else if(IsGroundedUp) {
          V0 = constrain(world.SMGetPaintValueAt(inkX,inkY,0), 0, 3); 
          V1 = constrain(world.SMGetPaintValueAt(inkX,inkY,1), 0, 3); 
          V2 = constrain(world.SMGetPaintValueAt(inkX,inkY,2)+1, 0, 3); 
          V3 = constrain(world.SMGetPaintValueAt(inkX,inkY,3), 0, 3);
        } else if(IsGroundedDown) {
          V0 = constrain(world.SMGetPaintValueAt(inkX,inkY,0)+1, 0, 3);
          V1 = constrain(world.SMGetPaintValueAt(inkX,inkY,1), 0, 3);
          V2 = constrain(world.SMGetPaintValueAt(inkX,inkY,2), 0, 3);
          V3 = constrain(world.SMGetPaintValueAt(inkX,inkY,3), 0, 3);
        }

        world.SMSetPaintValue(
          constrain(V0, 0, 3),
          constrain(V1, 0, 3),
          constrain(V2, 0, 3),
          constrain(V3, 0, 3),
          constrain(inkX,0,world.MapWidth-1),
          constrain(inkY,0,world.MapHeight-1),
          color
        );
        
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

  void spawnBullet (int x, int16_t y, int16_t vx, int16_t vy, byte color, byte owner) {
    for(byte i = 0; i < BCOUNT; i++) {
      if(bullets[i].IsDead) {
        bullets[i].Recreate();
        bullets[i].x = x;
        bullets[i].y = y;
        bullets[i].vx = vx;
        bullets[i].vy = vy;
        bullets[i].color = color;
        bullets[i].Owner = owner;
        break;
      }
    }
  }

  void Update () {
    for(byte i = 0; i < BCOUNT; i++) {
      bullets[i].Update();
    }
  }
};

BulletsManager bulletsManager;
