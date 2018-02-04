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
    return 15;
  };
  virtual int16_t getXFriction() {
    return 0;
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
      byte ColX[8];
      if(Dir == 1) {
        for(int16_t xd = 0; xd < getWidth(); xd++) { //yd = Y Down
          ColX[xd] =  world.PixelInCollider((x/SCALE-1)/8 , (y/SCALE+xd)/8 , (x/SCALE+getWidth()-1) - ((x/SCALE-1)/8)*8 , (y/SCALE+xd) - ((y/SCALE+xd)/8)*8);
        }
        for(int16_t xd = 0; xd < getWidth(); xd++) {
          if(ColX[xd] == 1) {
            IsGroundedLeft = true;
            return false;
          }
        }
      }
      if(Dir == -1) {
        for(int16_t xd = 0; xd < getWidth(); xd++) { //yd = Y Down
          ColX[xd] = world.PixelInCollider((x/SCALE+getWidth())/8, (y/SCALE+xd)/8 , (x/SCALE) - ((x/SCALE+getWidth())/8)*8 , (y/SCALE+xd) - ((y/SCALE+xd)/8)*8);
        }
        for(int16_t xd = 0; xd < getWidth(); xd++) {
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
      byte ColY[8];
      if(Dir == 1) {
        for(int16_t yd = 0; yd < getHeight(); yd++) { //yd = Y Down
          ColY[yd] = world.PixelInCollider((x/SCALE+yd)/8 , (y/SCALE-1)/8 , (x/SCALE+yd) - ((x/SCALE+yd)/8)*8 , (y/SCALE-1) - ((y/SCALE+getHeight())/8)*8);
        }
        for(int16_t yd = 0; yd < getHeight(); yd++) {
          if(ColY[yd] == 1) {
            IsGroundedUp = true;
            return false;
          }
        }
      }
      if(Dir == -1) {
        for(int16_t yd = 0; yd < getHeight(); yd++) { //yd = Y Down
          ColY[yd] = world.PixelInCollider((x/SCALE+yd)/8 , (y/SCALE+getHeight())/8 , (x/SCALE+yd) - ((x/SCALE+yd)/8)*8 , (y/SCALE+getHeight()) - ((y/SCALE)/8)*8);
        }
        for(int16_t yd = 0; yd < getHeight(); yd++) {
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
    byte ColY[8];
    for(int16_t yd = 0; yd < getHeight(); yd++) { //yd = Y Down
      ColY[yd] = world.PixelInCollider((x/SCALE+yd)/8 , (y/SCALE+getHeight())/8 , (x/SCALE+yd) - ((x/SCALE+yd)/8)*8 , (y/SCALE+getHeight()) - ((y/SCALE)/8)*8);
    }
    for(int16_t yd = 0; yd < getHeight(); yd++) {
      if(ColY[yd] == 1) {
        IsGroundedDown = true;
      }
    }

    for(int16_t yd = 0; yd < getHeight(); yd++) { //yd = Y Down
      ColY[yd] = world.PixelInCollider((x/SCALE+yd)/8 , (y/SCALE-1)/8 , (x/SCALE+yd) - ((x/SCALE+yd)/8)*8 , (y/SCALE-1) - ((y/SCALE+getHeight())/8)*8);
    }
    for(int16_t yd = 0; yd < getHeight(); yd++) {
      if(ColY[yd] == 1) {
        IsGroundedUp = true;
      }
    }

    byte ColX[8];
    for(int16_t xd = 0; xd < getWidth(); xd++) { //yd = Y Down
      ColX[xd] =  world.PixelInCollider((x/SCALE-1)/8 , (y/SCALE+xd)/8 , (x/SCALE+getWidth()-1) - ((x/SCALE-1)/8)*8 , (y/SCALE+xd) - ((y/SCALE+xd)/8)*8);
    }
    for(int16_t xd = 0; xd < getWidth(); xd++) {
      if(ColX[xd] == 1) {
        IsGroundedLeft = true;
      }
    }

    for(int16_t xd = 0; xd < getWidth(); xd++) { //yd = Y Down
      ColX[xd] = world.PixelInCollider((x/SCALE+getWidth())/8, (y/SCALE+xd)/8 , (x/SCALE) - ((x/SCALE+getWidth())/8)*8 , (y/SCALE+xd) - ((y/SCALE+xd)/8)*8);
    }
    for(int16_t xd = 0; xd < getWidth(); xd++) {
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
          vy = (int16_t)(-vy*(getYBounce()/100.0F));
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
              x += pxXr;
              pxXr = 0;
            } else if(getCollisionQuality()==0) {
              x -= constrain(pxXr,-1,0);
              pxXr -= constrain(pxXr,-1,0);
            }
          } else if(dirX == 1) {
  
            //Move then remove a pixel (or less) from the to-move list (By remove, I mean get closer to zero)
            if(getCollisionQuality()==1) {
              x += pxXr;
              pxXr = 0;
            } else if(getCollisionQuality()==0) {
              x -= constrain(pxXr,0,1);
              pxXr -= constrain(pxXr,0,1);
            }
          }
        } else {
          
          //If something is here, stop the object from moving
          vx = (int16_t)(-vx*(getXBounce()/100.0F));
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
    vx = (int16_t)(vx * ((1000 - getXFriction()) / 1000.0F));
    vy = (int16_t)(vy * ((1000 - getYFriction()) / 1000.0F));
    UpdateCollision();
    UpdateGrounding();
  }
};
