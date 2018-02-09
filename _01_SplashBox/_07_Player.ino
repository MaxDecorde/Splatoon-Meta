class Player :
  public Object {
  public:
    bool InputControl = true;
    short Live = 100;
    short RespawnTimer = 0;
    byte PlayerCode = 0;

    byte PlayerGender = 0;
    byte PlayerHaircut = 0;

    bool ShootCall = false;
    
    int8_t LVelX = 0;
    int8_t LVelY = 0;
    bool LastGrounded = false;
    
    int8_t PlayerDir = 1; //Was Going Right
    bool IsSwiming = false;
    byte blinkEye = 60;
    byte eyeSize = 2;
    byte hat = 0;
    byte DuckPosY = 0;

    byte SquisheVertical = 8;      //Player squishness :)
    byte SquisheHorizontal = 8;

    byte PlayerColor = 0;
    short GroundPoundTime = 0;
    
    bool LeftInk = false;
    bool BottomInk = false;
    bool RightInk = false;

    bool EBottomInk = false;

    bool A_PRESSED;
    bool A_HOLD;
    bool B_PRESSED;
    bool B_HOLD;
    
    bool UP_HOLD;
    bool DOWN_HOLD;
    bool LEFT_HOLD;
    bool RIGHT_HOLD;
    bool DOWN_PRESSED;

    virtual int16_t getWidth() {
      if(IsSwiming) {
        return 10;
      } else {
        return 10; //10
      }
    };
    virtual int16_t getHeight() {
      if(IsSwiming) {
        return 6;
      } else {
        return 14; //14
      }
    };

    void MoveUpdate () {
      if(FreezePlayers) {
        return;
      }
      
      if(!InputControl) {
        ControlUpdate();
      } else {
        A_HOLD = gb.buttons.repeat(BUTTON_A,0);
        B_HOLD = gb.buttons.repeat(BUTTON_B,0);
        A_PRESSED = gb.buttons.pressed(BUTTON_A);
        B_PRESSED = gb.buttons.pressed(BUTTON_B);

        UP_HOLD = gb.buttons.repeat(BUTTON_UP,0);
        DOWN_HOLD = gb.buttons.repeat(BUTTON_DOWN,0);
        LEFT_HOLD = gb.buttons.repeat(BUTTON_LEFT,0);
        RIGHT_HOLD = gb.buttons.repeat(BUTTON_RIGHT,0);
        DOWN_PRESSED = gb.buttons.pressed(BUTTON_DOWN);
      }
      
      BottomInk = world.SMGetPaintValueAt(constrain((x/SCALE+4)/8,0,world.MapWidth-1),constrain((y/SCALE)/8+2,0,world.MapHeight-1),0) > 0 
      && world.SMGetColor(constrain((x/SCALE+4)/8,0,world.MapWidth-1),constrain((y/SCALE)/8+1,0,world.MapHeight-1)) == PlayerColor;
      
      RightInk = world.SMGetPaintValueAt(constrain((x/SCALE+4)/8+1,0,world.MapWidth-1),constrain((y/SCALE+4)/8,0,world.MapHeight-1),3) > 0 
      && world.SMGetColor(constrain((x/SCALE+4)/8+1,0,world.MapWidth-1),constrain((y/SCALE+4)/8,0,world.MapHeight-1)) == PlayerColor;
      
      LeftInk = world.SMGetPaintValueAt(constrain((x/SCALE+4)/8-1,0,world.MapWidth-1),constrain((y/SCALE+4)/8,0,world.MapHeight-1),1) > 0 
      && world.SMGetColor(constrain((x/SCALE+4)/8-1,0,world.MapWidth-1),constrain((y/SCALE+4)/8,0,world.MapHeight-1)) == PlayerColor;
  
      EBottomInk = world.SMGetPaintValueAt(constrain((x/SCALE+4)/8,0,world.MapWidth-1),constrain((y/SCALE)/8+2,0,world.MapHeight-1),0) > 0 
      && world.SMGetColor(constrain((x/SCALE+4)/8,0,world.MapWidth-1),constrain((y/SCALE)/8+1,0,world.MapHeight-1)) != PlayerColor;
  
      //Mouvement SlowDown
      if(!RIGHT_HOLD && !LEFT_HOLD && !B_HOLD) {
        vx = vx * 0.75f;
      }
      
      if(EBottomInk) {
        vx = constrain(vx,-9,9);
      }
  
      //Gravity
      if(UP_HOLD) {
        vy = max(vy-3,-22);
      }
  
      //Swimming
      DuckPosY = 0;
      IsSwiming = false;
      
      if(DOWN_HOLD && ((Object::IsGroundedRight && RightInk) || (BottomInk && Object::IsGroundedDown) || (Object::IsGroundedLeft && LeftInk)) && !B_HOLD) {
        IsSwiming = true;
        DuckPosY = 1;
        SquisheVertical = 5;
        SquisheHorizontal = constrain(abs(vx/VFORCE),7,10);
        
        LVelY = max(LVelY-1,-8);
  
        if(PlayerDir == -1 && Object::IsGroundedLeft && LeftInk) {
          LVelX = min(LVelX+1,7);
  
          SquisheVertical = 5;
          SquisheHorizontal = 5;
          if(LEFT_HOLD) {
            vy = 52;
            vx = 22;
          }
        } else if(PlayerDir == 1 && Object::IsGroundedRight && RightInk) {
          LVelX = max(LVelX-1,-7);
  
          SquisheVertical = 5;
          SquisheHorizontal = 5;
          if(RIGHT_HOLD) {
            vy = 52;
            vx = -22;
          }
        } else {
          if(LVelX < 0) {
            LVelX++;
          } else if(LVelX > 0) {
            LVelX--;
          }
  
          if((Object::IsGroundedLeft && LEFT_HOLD) || (Object::IsGroundedRight && RIGHT_HOLD)) {
            vy = -25;
          }
        }
  
        //Mouvement
        if(RIGHT_HOLD && !B_HOLD) {
          if(vx - 9 > -82) {
            vx -= 9;
          }
          PlayerDir = 1;
        }
        if(LEFT_HOLD && !B_HOLD) {
          if(vx + 9 < 82) {
            vx += 9;
          }
          PlayerDir = -1;
        }
      } else {
        if(LVelY < 0) {
          LVelY++;
        } else if(LVelY > 0) {
          LVelY--;
        }
        
        if(LVelX < 0) {
          LVelX++;
        } else if(LVelX > 0) {
          LVelX--;
        }
        
        if(RIGHT_HOLD && !B_HOLD) {
          if(EBottomInk) {
            if(vx - 3 > -9) {
              vx -= 3;
            }
          } else {
            if(vx - 5 > -56) {
              vx -= 5;
            }
          }
          PlayerDir = 1;
        }
        if(LEFT_HOLD && !B_HOLD) {
          if(EBottomInk) {
            if(vx + 3 < 9) {
              vx += 3;
            }
          } else {
            if(vx + 5 < 56) {
              vx += 5;
            }
          }
          PlayerDir = -1;
        }
      }
  
      //Mouvement Particle
      //if(GoingRight && VelocityX > 0) {
      //  WalkParticle = 2+(blinkEye/60.0F*2);
      //}
      //
      //if(!GoingRight && VelocityX < 0) {
      //  WalkParticle = 2+(blinkEye/60.0F*2);
      //}
  
      //Jumps
      if(A_PRESSED && Object::IsGroundedDown  && !B_HOLD) {
        sfx(0, 0);
        if(EBottomInk) {
          vy = 7;
        } else {
          vy = 112;
        }
      }
      if(A_PRESSED && Object::IsGroundedRight && !Object::IsGroundedDown  && !B_HOLD) { 
        vx = 60;
        vy = 96;
        sfx(1, 0);
      }
      if(A_PRESSED && Object::IsGroundedLeft && !Object::IsGroundedDown  && !B_HOLD) { 
        vx = -60;
        vy = 96;
        sfx(1, 0);
      }
  
      //GroundPound
      if(DOWN_PRESSED && GroundPoundTime == 0 && !Object::IsGroundedDown  && !B_HOLD && !IsSwiming) { 
        GroundPoundTime = 1;
      }
      if(A_PRESSED && GroundPoundTime > 0 && !Object::IsGroundedDown  && !B_HOLD) {
        if(PlayerDir == 1) {
          vx = -33;
          vy = 56;
        } else {
          vx = 33;
          vy = 56;
        }
        GroundPoundTime = 0;
        sfx(8, 0);
      }
      if(Object::IsGroundedDown && GroundPoundTime > 0) {
        GroundPoundTime = 0;
        if(!BottomInk) {
          vy = 36;
        }
        sfx(3, 0);
      }
      if(GroundPoundTime > 0) {
        vx *= 0.7F;
        if(GroundPoundTime < 2) {
          vy = 28;
        } else if(GroundPoundTime > 3 && GroundPoundTime < 5) {
          vy = 0;
        }
        if(GroundPoundTime > 6) {
          vy = constrain(vy - 45, -127, 127);
        }
        GroundPoundTime++;
      }
    }

    byte MoveTimer = 0;

    void ControlUpdate () {
      LEFT_HOLD = false;
      RIGHT_HOLD = false;
      if(random(0,12) == 0 && Object::IsGroundedDown) {
        A_PRESSED = true;
      }
      if(random(0,32) == 0 && Object::IsGroundedRight && !Object::IsGroundedDown) {
        A_PRESSED = true;
        LEFT_HOLD = true;
        PlayerDir = -PlayerDir;
        MoveTimer = random(80,141);
      }
      if(random(0,32) == 0 && Object::IsGroundedLeft && !Object::IsGroundedDown) { 
        A_PRESSED = true;
        RIGHT_HOLD = true;
        PlayerDir = -PlayerDir;
        MoveTimer = random(80,141);
      }

      if(random(0,78) == 0) {
        float aimingAngleV = random(0,360);
      
        bulletsManager.spawnBullet(
          Object::x+4,
          Object::y+4,
          (int)(cos(aimingAngleV)*110.0F),
          (int)(sin(aimingAngleV)*110.0F),
          PlayerColor,
          PlayerCode
        );
      }
      
      if(random(0,89) == 0) {
        MoveTimer = random(80,230);
        PlayerDir = random(0,2)*2-1;
      }

      if(MoveTimer > 0) {
        if(PlayerDir == 1) {
          RIGHT_HOLD = true;
        } else {
          LEFT_HOLD = true;
        }
        MoveTimer--;
      }
    }

    void BlinkingUpdate () {
      blinkEye--;
      if(blinkEye == 0) {
        eyeSize = 0;
        blinkEye = 60;
      } else if(blinkEye == 1) {
        eyeSize = 1;
      } else {
        eyeSize = 2;
      }
    }

    void DrawInkHider() {
      if(abs(LVelX) == 0 && abs(LVelY) == 0) {
        return;
      }
      
      if(world.getTile((x/SCALE+4)/8+1,y/SCALE/8+1) != 0) {
        gb.display.setColor(WHITE);
        gb.display.fillRect(toScreenX(((x/SCALE+4)/8+1)*8), toScreenY((y/SCALE/8+1)*8), 8, 8);
        gb.display.setColor(BLACK);
      }
      if(world.getTile((x/SCALE+4)/8,y/SCALE/8+1) != 0) {
        gb.display.setColor(WHITE);
        gb.display.fillRect(toScreenX(((x/SCALE+4)/8)*8), toScreenY((y/SCALE/8+1)*8), 8, 8);
        gb.display.setColor(BLACK);
      }
      if(world.getTile((x/SCALE+4)/8-1,y/SCALE/8+1) != 0) {
        gb.display.setColor(WHITE);
        gb.display.fillRect(toScreenX(((x/SCALE+4)/8-1)*8), toScreenY((y/SCALE/8+1)*8), 8, 8);
        gb.display.setColor(BLACK);
      }
    }

    void Draw () {
      if(isOffScreen())
        return; //skip boxes which are out of the screen
      
      switch(colorGroup) {
        case 0:
        if(PlayerColor == 0) {
          gb.display.colorIndex = palettePYellow;
        } else {
          gb.display.colorIndex = palettePBlue;
        }
        break;
        case 1:
        if(PlayerColor == 0) {
          gb.display.colorIndex = palettePMagenta;
        } else {
          gb.display.colorIndex = palettePGreen;
        }
        break;
        case 2:
        if(PlayerColor == 0) {
          gb.display.colorIndex = palettePOrange;
        } else {
          gb.display.colorIndex = palettePBlue;
        }
        break;
        case 3:
        if(PlayerColor == 0) {
          gb.display.colorIndex = palettePMagenta;
        } else {
          gb.display.colorIndex = palettePBlue;
        }
        break;
        case 4:
        if(PlayerColor == 0) {
          gb.display.colorIndex = palettePRed;
        } else {
          gb.display.colorIndex = palettePBlue;
        }
        break;
        case 5:
        if(PlayerColor == 0) {
          gb.display.colorIndex = palettePMagenta;
        } else {
          gb.display.colorIndex = palettePOrange;
        }
        break;
        case 6:
        if(PlayerColor == 0) {
          gb.display.colorIndex = palettePGreen;
        } else {
          gb.display.colorIndex = palettePBlue;
        }
        break;
      }
      
      int8_t sizeX = InklingF.width();
      int8_t sizeY = InklingF.height();
      uint8_t playerImageID = 0;

      if(IsSwiming) {
        if(!IsGroundedDown) {
          if(vy > 75) {
            playerImageID = 11;
          } else if(vy < 75) {
            playerImageID = 13;
          } else {
            playerImageID = 12;
          }
        } else {
          playerImageID = 10;
        }

        if(PlayerGender == 0) {
          InklingF.setFrame(playerImageID);
          gb.display.drawImage(toScreenX(x/SCALE-8),toScreenY(y/SCALE-7),InklingF,(sizeX*PlayerDir),(sizeY));
        } else {
          InklingM.setFrame(playerImageID);
          gb.display.drawImage(toScreenX(x/SCALE-8),toScreenY(y/SCALE-7),InklingM,(sizeX*PlayerDir),(sizeY));
        }
      } else {
        if(IsGroundedDown && vx == 0) {
          playerImageID = 0;
        }
        if(!IsGroundedDown && vy >= 0) {
          playerImageID = 7;
        }
        if(!IsGroundedDown && vy < 0) {
          playerImageID = 8;
        }
        if(IsGroundedDown && abs(vx) > 5 && abs(vx) < 120 && (RIGHT_HOLD||LEFT_HOLD)) {
          playerImageID = 1+((blinkEye/AnimWALKSPEED)%3);
        }
        if(IsGroundedDown && abs(vx) > 120 && (RIGHT_HOLD||LEFT_HOLD)) {
          playerImageID = 4+((blinkEye/AnimRUNSPEED)%3);
        }

        if(ShootCall) {
          playerImageID = 9;
          ShootCall = false;
        }

        if(PlayerGender == 0) {
          switch(PlayerHaircut) {
            case 0:
            InklingF.setFrame(playerImageID);
            H0InklingF.setFrame(playerImageID);
            gb.display.drawImage(toScreenX(x/SCALE-8),toScreenY(y/SCALE-7),InklingF,sizeX*PlayerDir,sizeY);
            gb.display.drawImage(toScreenX(x/SCALE-8),toScreenY(y/SCALE-7),H0InklingF,sizeX*PlayerDir,sizeY);
            break;
            case 1:
            InklingF.setFrame(playerImageID);
            H1InklingF.setFrame(playerImageID);
            gb.display.drawImage(toScreenX(x/SCALE-8),toScreenY(y/SCALE-7),InklingF,sizeX*PlayerDir,sizeY);
            gb.display.drawImage(toScreenX(x/SCALE-8),toScreenY(y/SCALE-7),H1InklingF,sizeX*PlayerDir,sizeY);
            break;
            case 2:
            InklingF.setFrame(playerImageID);
            H2InklingF.setFrame(playerImageID);
            gb.display.drawImage(toScreenX(x/SCALE-8),toScreenY(y/SCALE-7),InklingF,sizeX*PlayerDir,sizeY);
            gb.display.drawImage(toScreenX(x/SCALE-8),toScreenY(y/SCALE-7),H2InklingF,sizeX*PlayerDir,sizeY);
            break;
            case 3:
            InklingF.setFrame(playerImageID);
            H3InklingF.setFrame(playerImageID);
            gb.display.drawImage(toScreenX(x/SCALE-8),toScreenY(y/SCALE-7),InklingF,sizeX*PlayerDir,sizeY);
            gb.display.drawImage(toScreenX(x/SCALE-8),toScreenY(y/SCALE-7),H3InklingF,sizeX*PlayerDir,sizeY);
            break;
          }
        } else {
          switch(PlayerHaircut) {
            case 0:
            InklingM.setFrame(playerImageID);
            H0InklingM.setFrame(playerImageID);
            gb.display.drawImage(toScreenX(x/SCALE-8),toScreenY(y/SCALE-7),InklingM,sizeX*PlayerDir,sizeY);
            gb.display.drawImage(toScreenX(x/SCALE-8),toScreenY(y/SCALE-7),H0InklingM,sizeX*PlayerDir,sizeY);
            break;
            case 1:
            InklingM.setFrame(playerImageID);
            H1InklingM.setFrame(playerImageID);
            gb.display.drawImage(toScreenX(x/SCALE-8),toScreenY(y/SCALE-7),InklingM,sizeX*PlayerDir,sizeY);
            gb.display.drawImage(toScreenX(x/SCALE-8),toScreenY(y/SCALE-7),H1InklingM,sizeX*PlayerDir,sizeY);
            break;
            case 2:
            InklingM.setFrame(playerImageID);
            H2InklingM.setFrame(playerImageID);
            gb.display.drawImage(toScreenX(x/SCALE-8),toScreenY(y/SCALE-7),InklingM,sizeX*PlayerDir,sizeY);
            gb.display.drawImage(toScreenX(x/SCALE-8),toScreenY(y/SCALE-7),H2InklingM,sizeX*PlayerDir,sizeY);
            break;
            case 3:
            InklingM.setFrame(playerImageID);
            H3InklingM.setFrame(playerImageID);
            gb.display.drawImage(toScreenX(x/SCALE-8),toScreenY(y/SCALE-7),InklingM,sizeX*PlayerDir,sizeY);
            gb.display.drawImage(toScreenX(x/SCALE-8),toScreenY(y/SCALE-7),H3InklingM,sizeX*PlayerDir,sizeY);
            break;
          }
        }
      }
      
      //gb.display.setColor(BLACK);
      //gb.display.drawRect(toScreenX(x/SCALE),toScreenY(y/SCALE),getWidth(),getHeight());

      gb.display.colorIndex = palette;
    }

    void BulletCollision () {
      for(byte i = 0; i < BCOUNT; i++) {
        if(gb.collidePointRect(bulletsManager.bullets[i].x,bulletsManager.bullets[i].y,x,y,getWidth(),getHeight())) {
          if(bulletsManager.bullets[i].color != PlayerColor) {
            Live-=bulletsManager.bullets[i].getDamage();
          }
          if(bulletsManager.bullets[i].Owner != PlayerCode) {
            bulletsManager.bullets[i].Die();
          }
        }
      }
    }
    
    void Update () {
      if(Live < 0) {
        Die();
      } else if(RespawnTimer > 0) {
        RespawnTimer--;
        if(RespawnTimer == 0) {
          if(PlayerColor == 0) {
            x = 8*pgm_read_byte(GetMap[world.CurrentLoadedMap] + 2)*SCALE;
            y = 8*pgm_read_byte(GetMap[world.CurrentLoadedMap] + 3)*SCALE;
          } else {
            x = 8*pgm_read_byte(GetMap[world.CurrentLoadedMap] + 0)*SCALE - 8*pgm_read_byte(GetMap[world.CurrentLoadedMap] + 2)*SCALE - 8*SCALE;
            y = 8*pgm_read_byte(GetMap[world.CurrentLoadedMap] + 3)*SCALE;
          }
        }
        return;
      }
      
      MoveUpdate();
      Object::Update();
      BlinkingUpdate();
      Draw();
      DrawInkHider();
      BulletCollision();

      if(EBottomInk) {
        Live = constrain(Live, 0, 90);
      }

      A_PRESSED = false;
      B_PRESSED = false;
      DOWN_PRESSED = false;
    }

    void Die () {
      RespawnTimer = 230;
      Live = 100;
    }
};

#define PLAYER_C 6

class PlayersOperator {
  public:
  Player mainPlayer;
  Player players[PLAYER_C-1];
  

  void Initialize () {
    mainPlayer.InputControl = true;
    for(int16_t i = 0; i < PLAYER_C; i++) {
      if(i != 0) {
        players[i-1].blinkEye = random(60);
        players[i-1].InputControl = false;

        if(i < PLAYER_C/2) {
          players[i-1].PlayerDir = 1;
          players[i-1].PlayerColor = 0;
          players[i-1].x = 8*pgm_read_byte(GetMap[world.CurrentLoadedMap] + 2)*SCALE;
          players[i-1].y = 8*pgm_read_byte(GetMap[world.CurrentLoadedMap] + 3)*SCALE;
        } else {
          players[i-1].PlayerDir = -1;
          players[i-1].PlayerColor = 1;
          players[i-1].x = 8*pgm_read_byte(GetMap[world.CurrentLoadedMap] + 0)*SCALE - 8*pgm_read_byte(GetMap[world.CurrentLoadedMap] + 2)*SCALE - 8*SCALE;
          players[i-1].y = 8*pgm_read_byte(GetMap[world.CurrentLoadedMap] + 3)*SCALE;
        }

        players[i-1].PlayerCode = i;
        players[i-1].PlayerGender = random(0,2);
        players[i-1].PlayerHaircut = random(0,4);
      } else {
        mainPlayer.PlayerCode = 0;
        mainPlayer.PlayerGender = random(0,2);
        mainPlayer.PlayerHaircut = random(0,4);
      }
    }
  }

  void UpdateGlobal () {
    for(int16_t i = 0; i < PLAYER_C; i++) {
      if(i == 0) {
        mainPlayer.Update();
      } else {
        players[i-1].Update();
      }
    }
  }
};

PlayersOperator player;

