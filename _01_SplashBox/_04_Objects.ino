// OBJECT MANAGER
/////////////////

class Object {
  public:
  int16_t x,y,vx,vy;
  bool IsGroundedDown,IsGroundedLeft,IsGroundedRight,IsGroundedUp;
  bool collided = false;
  
  virtual int16_t getWidth() {
    return 8;
  };
  virtual int16_t getHeight() {
    return 8;
  };
  virtual int16_t getGravity() {
    return 55;
  };
  virtual int16_t getXFriction() {
    return 62;
  };
  virtual int16_t getYFriction() {
    return 0;
  };
  virtual int16_t getXBounce() {
    return 0;
  };
  virtual int16_t getYBounce() {
    return 0;
  };
  virtual byte getCollisionQuality() {
    return 0;
  };

  boolean isOffScreen() {
    return (toScreenX(x/SCALE) + toScreenX(x/SCALE + getWidth()) < 0) || (toScreenX(x/SCALE) > LCDWIDTH) || (toScreenY(y/SCALE) + toScreenY(y/SCALE + getHeight()) < 0) || (toScreenY(y/SCALE) > LCDHEIGHT);
  }

  virtual void Draw () {
    if(isOffScreen())
        return; //skip boxes which are out of the screen
      gb.display.fillRect(toScreenX(x/SCALE), toScreenY(y/SCALE), getWidth(), getHeight());
  }
  
  bool CheckForCollisionX (int8_t Dir) {
    if(Dir != 0) {
      byte ColX[getHeight()];
      if(Dir == 1) {
        for(int16_t xd = 0; xd < getHeight(); xd++) { //yd = Y Down
          ColX[xd] = world.PixelInCollider(
            Div8(x/SCALE-1),
            Div8(y/SCALE),
            (x/SCALE+getWidth()-1)%8,
            (y/SCALE)%8+xd
          );
        }
        for(int16_t xd = 0; xd < getHeight(); xd++) {
          if(ColX[xd] == 1) {
            IsGroundedLeft = true;
            return false;
          }
        }
      }
      if(Dir == -1) {
        for(int16_t xd = 0; xd < getHeight(); xd++) { //yd = Y Down
          ColX[xd] = world.PixelInCollider(
            Div8(x/SCALE+getWidth()),
            Div8(y/SCALE),
            (x/SCALE+getWidth())%8,
            (y/SCALE)%8+xd
          );
        }
        for(int16_t xd = 0; xd < getHeight(); xd++) {
          if(ColX[xd] == 1) {
            IsGroundedRight = true;
            return false;
          }
        }
      }
    }
    return true;
  }
  
  bool CheckForCollisionY (int8_t Dir) {
    if(Dir != 0) {
      byte ColY[getWidth()];
      if(Dir == 1) {
        for(int16_t yd = 0; yd < getWidth(); yd++) { //yd = Y Down
          ColY[yd] = world.PixelInCollider(
            Div8(x/SCALE),
            Div8(y/SCALE-1),
            (x/SCALE)%8+yd,
            (y/SCALE+getHeight())%8
          );
        }
        for(int16_t yd = 0; yd < getWidth(); yd++) {
          if(ColY[yd] == 1) {
            IsGroundedUp = true;
            return false;
          }
        }
      }
      if(Dir == -1) {
        for(int16_t yd = 0; yd < getWidth(); yd++) { //yd = Y Down
          ColY[yd] = world.PixelInCollider(
            Div8(x/SCALE),
            Div8(y/SCALE+getHeight()),
            (x/SCALE)%8+yd,
            (y/SCALE+getHeight())%8
          );
        }
        for(int16_t yd = 0; yd < getWidth(); yd++) {
          if(ColY[yd] == 1) {
            IsGroundedDown = true;
            return false;
          }
        }
      }
    }
    return true;
  }

  void UpdateGrounding () {
    byte ColY[getWidth()];
    for(int16_t yd = 0; yd < getWidth(); yd++) { //yd = Y Down
      ColY[yd] = world.PixelInCollider(
        Div8(x/SCALE),
        Div8(y/SCALE-1),
        (x/SCALE)%8+yd,
        (y/SCALE+getHeight())%8
      );
    }
    for(int16_t yd = 0; yd < getWidth(); yd++) {
      if(ColY[yd] == 1) {
        IsGroundedUp = true;
      }
    }
    
    for(int16_t yd = 0; yd < getWidth(); yd++) { //yd = Y Down
      ColY[yd] = world.PixelInCollider(
        Div8(x/SCALE),
        Div8(y/SCALE+getHeight()),
        (x/SCALE)%8+yd,
        (y/SCALE+getHeight())%8
      );
    }
    for(int16_t yd = 0; yd < getWidth(); yd++) {
      if(ColY[yd] == 1) {
        IsGroundedDown = true;
      }
    }

    byte ColX[getHeight()];
    for(int16_t xd = 0; xd < getHeight(); xd++) { //yd = Y Down
      ColX[xd] = world.PixelInCollider(
        Div8(x/SCALE-1),
        Div8(y/SCALE),
        (x/SCALE+getWidth()-1)%8,
        (y/SCALE)%8+xd
      );
    }
    for(int16_t xd = 0; xd < getHeight(); xd++) {
      if(ColX[xd] == 1) {
        IsGroundedLeft = true;
      }
    }
    for(int16_t xd = 0; xd < getHeight(); xd++) { //yd = Y Down
      ColX[xd] = world.PixelInCollider(
        Div8(x/SCALE+getWidth()),
        Div8(y/SCALE),
        (x/SCALE+getWidth())%8,
        (y/SCALE)%8+xd
      );
    }
    for(int16_t xd = 0; xd < getHeight(); xd++) {
      if(ColX[xd] == 1) {
        IsGroundedRight = true;
      }
    }
  }

  void UpdateCollision () {
    //Finds how much pixel you need to move
    int16_t pxXr = vx/VFORCE; //pixel on X axis require to move
    int8_t dirX = vx > 0 ? 1 : -1;
    
    int16_t pxYr = vy/VFORCE; //pixel on Y axis require to move
    int8_t dirY = vy >= 0 ? 1 : -1;
  
    //Finds the number of iteration needed to move everything
    byte pxr = (abs(pxXr)+abs(pxYr));
  
    //Loops for each move iteration
    for(byte i = 0; i < pxr; i++) {
  
      //Finds what axis it should do first
      if(pxYr != 0) {
  
        //Check if there's nothing next to the object
        if(CheckForCollisionY(dirY)) {
  
          //If nothing is here, find in what direction the object need to move
          if(dirY == -1) {
  
            //Move then remove a pixel (or less) from the to-move list (By remove, I mean get closer to zero)
            if(getCollisionQuality()==1) {
              y -= pxYr;
              pxYr = 0;
            } else if(getCollisionQuality()==0) {
              y -= constrain(pxYr,-1,0);
              pxYr -= constrain(pxYr,-1,0);
            }
          } else if(dirY == 1) {
  
            //Move then remove a pixel (or less) from the to-move list (By remove, I mean get closer to zero)
            if(getCollisionQuality()==1) {
              y -= pxYr;
              pxYr = 0;
            } else if(getCollisionQuality()==0) {
              y -= constrain(pxYr,0,1);
              pxYr -= constrain(pxYr,0,1);
            }
          }
        } else {
  
          //If something is here, stop the player from moving
          if(getCollisionQuality()==0) {
            vy = -(vy*getYBounce())/100;
          }
          collided = true;
          //vy = 0;
  
          //Remove all the pixel (or less) from the to-move list (By remove, I mean get closer to zero)
          pxYr = 0;
        }
      } else {
  
        //Check if there's nothing next to the object
        if(CheckForCollisionX(dirX)) {
  
          //If nothing is here, find in what direction the objects need to move
          if(dirX == -1) {
  
            //Move then remove a pixel (or less) from the to-move list (By remove, I mean get closer to zero)
            if(getCollisionQuality()==1) {
              x -= pxXr;
              pxXr = 0;
            } else if(getCollisionQuality()==0) {
              x -= constrain(pxXr,-1,0);
              pxXr -= constrain(pxXr,-1,0);
            }
          } else if(dirX == 1) {
  
            //Move then remove a pixel (or less) from the to-move list (By remove, I mean get closer to zero)
            if(getCollisionQuality()==1) {
              x -= pxXr;
              pxXr = 0;
            } else if(getCollisionQuality()==0) {
              x -= constrain(pxXr,0,1);
              pxXr -= constrain(pxXr,0,1);
            }
          }
        } else {
          
          //If something is here, stop the object from moving
          if(getCollisionQuality()==0) {
            vx = (-vx*getXBounce())/100;
          }
          collided = true;
          //vx = 0;
  
          //Remove all the pixel (or less) from the to-move list (By remove, I mean get closer to zero)
          pxXr = 0;
        }
      }
    }
  }

  void Update () {
    collided = false;
    
    IsGroundedLeft = false;
    IsGroundedRight = false;
    IsGroundedDown = false;
    IsGroundedUp = false;
    vy -= getGravity()/VFORCE;
    vy = constrain(vy, -127, 127);
    if(getCollisionQuality()==0) {
      vx = (vx * (1000 - getXFriction())) / 1000;
      vy = (vy * (1000 - getYFriction())) / 1000;
    }
    UpdateCollision();
    //UpdateGrounding();
  }
};

class UISplash {
  public:
  byte x,y;
  byte sizev;
  byte timer = 0;
  byte cgroup = 0;
  byte cside = 0;

  void Init (byte nx, byte ny, byte nsizev, byte ncgroup, byte ncside) {
    x = nx;
    y = ny;
    sizev = nsizev;
    cgroup = ncgroup;
    cside = ncside;
  }

  void Draw () {
    setPaletteToColorGroup(cside,cgroup);
    byte s = (int)(sizev/3.0F*timer);
    gb.display.drawImage(x-(s/2),y-(s/2),SplashUI,s,s);
    gb.display.colorIndex = palette;
  }

  void Update () {
    Draw();
    if(timer < 3) {
      timer++;
    }
  }
};

UISplash uiSplashes[5];

