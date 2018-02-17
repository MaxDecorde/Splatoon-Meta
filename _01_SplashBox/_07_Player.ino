class Player :
  public Object {
  public:
    bool InputControl = true;
    int8_t Live = 100;
    uint16_t RespawnTimer = 0;
    byte PlayerCode = 0;

    int8_t Kid2SquidFrames = 0;
    
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

    bool Last_DOWN_HOLD;

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
        if(Weapons[mainWeapon][0] != 1) {
          B_HOLD = gb.buttons.repeat(BUTTON_B,0);
          DOWN_HOLD = gb.buttons.repeat(BUTTON_DOWN,0);
        } else {
          B_HOLD = gb.buttons.repeat(BUTTON_B,0);
          if(B_HOLD) {
            DOWN_HOLD = false;
          }
        }
        A_PRESSED = gb.buttons.pressed(BUTTON_A);
        B_PRESSED = gb.buttons.pressed(BUTTON_B);

        UP_HOLD = gb.buttons.repeat(BUTTON_UP,0);
        LEFT_HOLD = gb.buttons.repeat(BUTTON_LEFT,0);
        RIGHT_HOLD = gb.buttons.repeat(BUTTON_RIGHT,0);
        DOWN_PRESSED = gb.buttons.pressed(BUTTON_DOWN);
      }
      
      BottomInk = world.SMGetPaintValueAt(constrain(Div8(x/SCALE+4),0,world.MapWidth-1),constrain(Div8(y/SCALE)+2,0,world.MapHeight-1),0) > 0 
      && world.SMGetColor(constrain(Div8(x/SCALE+4),0,world.MapWidth-1),constrain(Div8(y/SCALE)+2,0,world.MapHeight-1)) == PlayerColor;
      
      RightInk = world.SMGetPaintValueAt(constrain(Div8(x/SCALE+4)+1,0,world.MapWidth-1),constrain(Div8(y/SCALE+4),0,world.MapHeight-1),3) > 0 
      && world.SMGetColor(constrain(Div8(x/SCALE+4)+1,0,world.MapWidth-1),constrain(Div8(y/SCALE+4),0,world.MapHeight-1)) == PlayerColor;
      
      LeftInk = world.SMGetPaintValueAt(constrain(Div8(x/SCALE+4)-1,0,world.MapWidth-1),constrain(Div8(y/SCALE+4),0,world.MapHeight-1),1) > 0 
      && world.SMGetColor(constrain(Div8(x/SCALE+4)-1,0,world.MapWidth-1),constrain(Div8(y/SCALE+4),0,world.MapHeight-1)) == PlayerColor;
  
      EBottomInk = world.SMGetPaintValueAt(constrain(Div8(x/SCALE+4),0,world.MapWidth-1),constrain(Div8(y/SCALE)+2,0,world.MapHeight-1),0) > 0 
      && world.SMGetColor(constrain(Div8(x/SCALE+4),0,world.MapWidth-1),constrain(Div8(y/SCALE)+2,0,world.MapHeight-1)) != PlayerColor;

      //Kid to Squid to Kid collision
      if(DOWN_HOLD && !Last_DOWN_HOLD && !B_HOLD) {
        Kid2SquidFrames = 0;
        y+=Mul8(SCALE);
      }
      if(!DOWN_HOLD && Last_DOWN_HOLD && !B_HOLD) {
        Kid2SquidFrames = 0;
        y-=Mul8(SCALE);
      }

      //Put ink under player when shooting
      if(ShootCall) {
        inkX = Div8(x/SCALE);
        inkY = Div8(y/SCALE);
        
        inkX = constrain(inkX,0,world.MapWidth-1);
        inkY = constrain(inkY,0,world.MapHeight-1);

        if(world.SMGetPaintValueAt(inkX,inkY+2,0) <= 0) {
          V0 = constrain(world.SMGetPaintValueAt(inkX,inkY+2,0)+1, 0, 3);
        } else {
          V0 = constrain(world.SMGetPaintValueAt(inkX,inkY+2,0), 0, 3);
        }
        V1 = constrain(world.SMGetPaintValueAt(inkX,inkY+2,1), 0, 3);
        V2 = constrain(world.SMGetPaintValueAt(inkX,inkY+2,2), 0, 3);
        V3 = constrain(world.SMGetPaintValueAt(inkX,inkY+2,3), 0, 3);

        world.SMSetPaintValue(
          constrain(V0, 0, 3),
          constrain(V1, 0, 3),
          constrain(V2, 0, 3),
          constrain(V3, 0, 3),
          constrain(inkX,0,world.MapWidth-1),
          constrain(inkY+2,0,world.MapHeight-1),
          PlayerColor
        );
      }

      //Stairs and slopes handeling
      if(LEFT_HOLD) {
        IsSwiming = true;
        byte col = TilesParams_Array[world.getTile(Div8(x/SCALE-1),Div8(y/SCALE+11))*TileParamsCount+0];
        if(col == 7) {
          x -= 1*SCALE;
          y -= 1*SCALE;
        } else if(col == 0) {
          col = TilesParams_Array[world.getTile(Div8(x/SCALE+4),Div8(y/SCALE+16))*TileParamsCount+0];
          if(col == 7) {
            x -= 1*SCALE;
            y -= 1*SCALE;
          }
        }
      }
      if(RIGHT_HOLD) {
        byte col = TilesParams_Array[world.getTile(Div8(x/SCALE+12),Div8(y/SCALE+11))*TileParamsCount+0];
        if(col == 6) {
          x += 1*SCALE;
          y -= 1*SCALE;
        } else if(col == 0) {
          col = TilesParams_Array[world.getTile(Div8(x/SCALE+4),Div8(y/SCALE+16))*TileParamsCount+0];
          if(col == 6) {
            x += 1*SCALE;
            y -= 1*SCALE;
          }
        }
      }

      //Swim PhysX
      ////////////
      if(DOWN_HOLD && !B_HOLD) {
        bool BottomInkSquid = world.SMGetPaintValueAt(constrain(Div8(x/SCALE+4),0,world.MapWidth-1),constrain(Div8(y/SCALE)+1,0,world.MapHeight-1),0) > 0 
        && world.SMGetColor(constrain(Div8(x/SCALE+4),0,world.MapWidth-1),constrain(Div8(y/SCALE)+1,0,world.MapHeight-1)) == PlayerColor;

        bool BottomEInkSquid = world.SMGetPaintValueAt(constrain(Div8(x/SCALE+4),0,world.MapWidth-1),constrain(Div8(y/SCALE)+1,0,world.MapHeight-1),0) > 0 
        && world.SMGetColor(constrain(Div8(x/SCALE+4),0,world.MapWidth-1),constrain(Div8(y/SCALE)+1,0,world.MapHeight-1)) != PlayerColor;

        if(BottomInkSquid&&IsGroundedDown) {
          LVelY = constrain(LVelY+1, -5, 5);
        } else {
          if(LVelY > 0) LVelY = constrain(LVelY-2, 0, 5);
          if(LVelY < 0) LVelY = constrain(LVelY+2, -5, 0);
        }

        if(LeftInk&&LEFT_HOLD) {
          LVelX = constrain(LVelX-1, -4, 4);
        } else if(RightInk&&RIGHT_HOLD) {
          LVelX = constrain(LVelX+1, -4, 4);
        } else {
          if(LVelX > 0) LVelX = constrain(LVelX-2, 0, 4);
          if(LVelX < 0) LVelX = constrain(LVelX+2, -4, 0);
        }
        
        ShootCall = false;
        IsSwiming = true;
        if(RIGHT_HOLD && !IsGroundedRight) {
          if(BottomInkSquid) {
            if(vx - 15 > -112) {
              vx -= 15;
            }
          } else if(BottomEInkSquid) {
            if(vx - 3 > -14) {
              vx -= 3;
            }
          } else {
            if(vx - 7 > -78) {
              vx -= 7;
            }
          }
          PlayerDir = 1;
        } else if(RIGHT_HOLD && IsGroundedRight && RightInk) {
          vy = 90;
          PlayerDir = 1;
        }
        if(LEFT_HOLD && !IsGroundedLeft) {
          if(BottomInkSquid) {
            if(vx + 15 < 112) {
              vx += 15;
            }
          } else if(BottomEInkSquid) {
            if(vx + 3 < 14) {
              vx += 3;
            }
          } else {
            if(vx + 7 < 78) {
              vx += 7;
            }
          }
          PlayerDir = -1;
        } else if(LEFT_HOLD && IsGroundedLeft && LeftInk) {
          vy = 90;
          PlayerDir = -1;
        }
        if((IsGroundedRight&&RightInk) || (IsGroundedLeft&&LeftInk)) {
          vy = max(vy-3,-18);
        }
        if(IsGroundedDown && gb.buttons.pressed(BUTTON_A)) {
          if(BottomEInkSquid) {
            vy = 46;
          } else {
            vy = 110;
          }
        }
        if(!RIGHT_HOLD && !LEFT_HOLD) {
          vx = vx * 0.75f;
        }
        return;
      } else {
        IsSwiming = false;
      }
      
      //setColorToGroup(world.SMGetColor(constrain((x/SCALE+4)/8,0,world.MapWidth-1),constrain((y/SCALE)/8+2,0,world.MapHeight-1)));
      //gb.display.fillRect(toScreenX(constrain((x/SCALE+4)/8,0,world.MapWidth-1)*8),toScreenY(constrain((y/SCALE)/8+2,0,world.MapHeight-1)*8),8,8);
  
      //Mouvement SlowDown
      if(!RIGHT_HOLD && !LEFT_HOLD && !B_HOLD) {
        vx = vx * 0.75f;
      }
      
      if(EBottomInk) {
        if(PlayerCode == 0) {
          shakeTimeLeft = 1;
          shakeAmplitude = 1;
        }
        
        vx = constrain(vx,-9,9);
      }
  
      //Gravity
      if(UP_HOLD) {
        vy = max(vy-3,-22);
      }

      if(true) {
        //NORMAL PhysX
        //////////////
        
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

        //MOVING
        if(RIGHT_HOLD && !B_HOLD) {
          if(EBottomInk) {
            if(vx - 3 > -9) {
              vx -= 3;
            }
          } else {
            if(vx - 7 > -76) {
              vx -= 7;
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
            if(vx + 7 < 76) {
              vx += 7;
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
          vy = 26;
        } else {
          vy = 132;
        }
      }
      if(A_PRESSED && Object::IsGroundedRight && !Object::IsGroundedDown  && !B_HOLD) { 
        vx = 60;
        vy = 104;
        sfx(1, 0);
      }
      if(A_PRESSED && Object::IsGroundedLeft && !Object::IsGroundedDown  && !B_HOLD) { 
        vx = -60;
        vy = 104;
        sfx(1, 0);
      }
  
      //GroundPound
      if(DOWN_PRESSED && GroundPoundTime == 0 && !Object::IsGroundedDown  && !B_HOLD && !IsSwiming) { 
        GroundPoundTime = 1;
      }
      if(A_PRESSED && GroundPoundTime > 0 && !Object::IsGroundedDown  && !B_HOLD) {
        if(PlayerDir == 1) {
          vx = -33;
          vy = 76;
        } else {
          vx = 33;
          vy = 76;
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
        if(Kid2SquidFrames < 2) {
          switch(Kid2SquidFrames) {
            case 0:
            playerImageID = 14;
            break;
            case 1:
            playerImageID = 15;
            break;
            case 2:
            playerImageID = 13;
            break;
          }
          Kid2SquidFrames++;
        } else if(!IsGroundedDown) {
          if(vy > 70) {
            playerImageID = 11;
          } else if(vy < -70) {
            playerImageID = 13;
          } else {
            playerImageID = 12;
          }
        } else {
          playerImageID = 10;
        }

        if(abs(LVelX) > 1) {
          if(PlayerDir == 1) {
            if(PlayerGender == 0) {
              InklingF.setFrame(playerImageID);
              gb.display.drawImage(toScreenX(x/SCALE-8+LVelX+(sizeX-((sizeX*PlayerDir)/3*(4-abs(LVelX))))),toScreenY(y/SCALE-7-8+LVelY),InklingF,(sizeX*PlayerDir)/3*(4-abs(LVelX)),(sizeY));
            } else {
              InklingM.setFrame(playerImageID);
              gb.display.drawImage(toScreenX(x/SCALE-8+LVelX+(sizeX-((sizeX*PlayerDir)/3*(4-abs(LVelX))))),toScreenY(y/SCALE-7-8+LVelY),InklingM,(sizeX*PlayerDir)/3*(4-abs(LVelX)),(sizeY));
            }
          } else {
            if(PlayerGender == 0) {
              InklingF.setFrame(playerImageID);
              gb.display.drawImage(toScreenX(x/SCALE-8+LVelX),toScreenY(y/SCALE-7-8+LVelY),InklingF,(sizeX*PlayerDir)/3*(4-abs(LVelX)),(sizeY));
            } else {
              InklingM.setFrame(playerImageID);
              gb.display.drawImage(toScreenX(x/SCALE-8+LVelX),toScreenY(y/SCALE-7-8+LVelY),InklingM,(sizeX*PlayerDir)/3*(4-abs(LVelX)),(sizeY));
            }
          }
        } else {
          if(PlayerGender == 0) {
            InklingF.setFrame(playerImageID);
            gb.display.drawImage(toScreenX(x/SCALE-8+LVelX),toScreenY(y/SCALE-7-8+LVelY),InklingF,(sizeX*PlayerDir),(sizeY));
          } else {
            InklingM.setFrame(playerImageID);
            gb.display.drawImage(toScreenX(x/SCALE-8+LVelX),toScreenY(y/SCALE-7-8+LVelY),InklingM,(sizeX*PlayerDir),(sizeY));
          }
        }
      } else {
        if(Kid2SquidFrames < 2) {
          switch(Kid2SquidFrames) {
            case 0:
            playerImageID = 13;
            break;
            case 1:
            playerImageID = 15;
            break;
            case 2:
            playerImageID = 14;
            break;
          }
          Kid2SquidFrames++;

          if(PlayerGender == 0) {
          InklingF.setFrame(playerImageID);
            gb.display.drawImage(toScreenX(x/SCALE-8),toScreenY(y/SCALE-7),InklingF,(sizeX*PlayerDir),(sizeY));
          } else {
            InklingM.setFrame(playerImageID);
            gb.display.drawImage(toScreenX(x/SCALE-8),toScreenY(y/SCALE-7),InklingM,(sizeX*PlayerDir),(sizeY));
          }

          gb.display.colorIndex = palette;
          return;
        }
        
        if(IsGroundedDown && vx == 0) {
          playerImageID = 0;
        }
        if(!IsGroundedDown && vy >= 0) {
          playerImageID = 7;
        }
        if(!IsGroundedDown && vy < 0) {
          playerImageID = 8;
        }
        if(IsGroundedDown && abs(vx) > 5 && abs(vx) < 72 && (RIGHT_HOLD||LEFT_HOLD)) {
          playerImageID = 1+((blinkEye/AnimWALKSPEED)%3);
        }
        if(IsGroundedDown && abs(vx) > 72 && (RIGHT_HOLD||LEFT_HOLD)) {
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

      gb.display.colorIndex = palette;

      if(!IsSwiming && (cpuLoad < 100 && PlayerCode != 0)) {
        if(PlayerDir == 1) {
          gb.display.drawImage(toScreenX(x/SCALE-5)+HatOffset[playerImageID*2],toScreenY(y/SCALE-10)-HatOffset[playerImageID*2+1],HeadgearSprites[hat],16,16);
        } else {
          gb.display.drawImage(toScreenX(x/SCALE-3)-HatOffset[playerImageID*2],toScreenY(y/SCALE-10)-HatOffset[playerImageID*2+1],HeadgearSprites[hat],-16,16);
        }
      }
      
      //gb.display.setColor(BLACK);
      //gb.display.drawRect(toScreenX(x/SCALE),toScreenY(y/SCALE),getWidth(),getHeight());
    }

    void BulletCollision () {
      for(byte i = 0; i < BCOUNT; i++) {
        if(!bulletsManager.bullets[i].IsDead) {
          if(gb.collidePointRect(bulletsManager.bullets[i].x/SCALE,bulletsManager.bullets[i].y/SCALE,x/SCALE,y/SCALE,getWidth(),getHeight())) {
            if(bulletsManager.bullets[i].color != PlayerColor) {
              Live-=bulletsManager.bullets[i].Damage;
              bulletsManager.bullets[i].Die();
              if(PlayerCode == 0) {
                shakeTimeLeft += 3;
                shakeAmplitude += 1;
              }
            }
            if(bulletsManager.bullets[i].Owner != PlayerCode) {
              bulletsManager.bullets[i].Die();
            }
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
          if(PlayerColor == revertColors) {
            x = ((GetMap[world.CurrentLoadedMap][2]*8)-4)*SCALE;
            y = (GetMap[world.CurrentLoadedMap][3]*8)*SCALE;
          } else {
            x = (GetMap[world.CurrentLoadedMap][0]*8)*SCALE - Mul8(GetMap[world.CurrentLoadedMap][2])*SCALE - Mul8(SCALE);
            y = (GetMap[world.CurrentLoadedMap][3]*8)*SCALE;
          }
        }
        return;
      }
      
      MoveUpdate();
      Object::Update();
      BlinkingUpdate();
      Draw();
      BulletCollision();

      if(EBottomInk) {
        Live = constrain(Live, -1, 80);
      }

      A_PRESSED = false;
      B_PRESSED = false;
      DOWN_PRESSED = false;
      Last_DOWN_HOLD = DOWN_HOLD;
    }

    void Die () {
      RespawnTimer = 80;
      Live = 100;
    }
};

#define PLAYER_C 4

class PlayersOperator {
  public:
  Player mainPlayer;
  Player players[PLAYER_C-1];

  void Initialize () {
    revertColors = random(0,2);
    mainPlayer.InputControl = true;
    for(uint8_t i = 0; i < PLAYER_C; i++) {
      if(i != 0) {
        players[i-1].blinkEye = random(60);
        players[i-1].InputControl = false;

        if(i < PLAYER_C/2) {
          players[i-1].PlayerDir = 1;
          players[i-1].PlayerColor = revertColors;
          players[i-1].x = ((GetMap[world.CurrentLoadedMap][2]*8)-4)*SCALE;
          players[i-1].y = (GetMap[world.CurrentLoadedMap][3]*8)*SCALE;
        } else {
          players[i-1].PlayerDir = -1;
          players[i-1].PlayerColor = 1-revertColors;
          players[i-1].x = (GetMap[world.CurrentLoadedMap][0]*8)*SCALE - (GetMap[world.CurrentLoadedMap][2]*8)*SCALE - (SCALE*8);
          players[i-1].y = (GetMap[world.CurrentLoadedMap][3]*8)*SCALE;
        }

        players[i-1].PlayerCode = i;
        players[i-1].PlayerGender = random(0,2);
        players[i-1].PlayerHaircut = random(0,4);
        players[i-1].hat = random(0,HEADGEARCount+1);
      } else {
        mainPlayer.PlayerColor = revertColors;
        mainPlayer.PlayerCode = 0;
        mainPlayer.PlayerGender = random(0,2);
        mainPlayer.PlayerHaircut = random(0,4);
        mainPlayer.hat = random(0,HEADGEARCount+1);
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

