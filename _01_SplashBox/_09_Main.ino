// MAIN STUFF
////////////////

bool WeaponRecharged = false;
uint32_t WeaponResetTimer = 0;

void ClampCamera () { //Clamp the camera in the world
  if(AnimationTimer > 0) {
    return;
  } 
  
  if(world.MapWidth < 11) {
    cameraX = (LCDWIDTH - Mul8(world.MapWidth))/2;
  } else {
    cameraX = ClampInt(0,(world.MapWidth*8)-LCDWIDTH,cameraX);
  }
  cameraY = ClampInt(0,(world.MapHeight*8)-LCDHEIGHT,cameraY);
}

void PrepareMap () {
  world.CurrentLoadedMap = 0;
  player.mainPlayer.x = ((GetMap[world.CurrentLoadedMap][2]*8)-4)*SCALE;
  player.mainPlayer.y = (GetMap[world.CurrentLoadedMap][3]*8)*SCALE;
  world.MapWidth = GetMap[world.CurrentLoadedMap][0];
  world.MapHeight = GetMap[world.CurrentLoadedMap][1];
  
  player.mainPlayer.vx = 0;
  player.mainPlayer.vy = 0;

  player.Initialize();

  IsPlaying = true;

  AnimationTimer = STARTLENGHT;
}

void DrawCursor() {
  if(player.mainPlayer.RespawnTimer > 0) {
    return;
  }
  
  if(gb.buttons.repeat(BUTTON_RIGHT,0) && !gb.buttons.repeat(BUTTON_B,0)) {
    if(!LastDirection && curX<48) {
      curX = 84 - curX;
    }
    LastDirection = true;
  }

  if(gb.buttons.repeat(BUTTON_LEFT,0) && !gb.buttons.repeat(BUTTON_B,0)) {
    if(LastDirection && curX>48) {
      curX = 84 - curX;
    }
    LastDirection = false;
  }

  if(gb.buttons.repeat(BUTTON_B,0) || gb.buttons.released(BUTTON_B)) {
    player.mainPlayer.ShootCall = true;
    if(gb.buttons.repeat(BUTTON_UP,0)) {
      curY-=4;
      curY = constrain(curY, 0+5, LCDHEIGHT-4);
    }
    if(gb.buttons.repeat(BUTTON_LEFT,0)) {
      curX-=4;
      curX = constrain(curX, 0+5, LCDWIDTH-4);
    }
    if(gb.buttons.repeat(BUTTON_RIGHT,0)) {
      curX+=4;
      curX = constrain(curX, 0+5, LCDWIDTH-4);
    }
    if(gb.buttons.repeat(BUTTON_DOWN,0)) {
      curY+=4;
      curY = constrain(curY, 0+5, LCDHEIGHT-4);
    }
    
    switch(Weapons[mainWeapon][0]) {
      case 0: //--Classic Shooters
      if(gb.buttons.repeat(BUTTON_A,Weapons[mainWeapon][5]) && !gb.buttons.pressed(BUTTON_A)) {
        float aimingAngle = 0;
        for(uint8_t b = 0; b < Weapons[mainWeapon][8]; b++) {
          int16_t rootX = player.mainPlayer.x/SCALE;
          int16_t rootY = player.mainPlayer.y/SCALE;
          int16_t targetX = cameraX+curX;
          int16_t targetY = cameraY+curY;

          if(player.mainPlayer.PlayerDir == 1) {
            //root = + 22,9 from player
            rootX+=14;
            rootY+=5;
          } else if(player.mainPlayer.PlayerDir == -1) {
            //root = + 2,9 from player
            rootX-=7;
            rootY+=5;
          }

          if(player.mainPlayer.PlayerDir == 1) {
            aimingAngle = atan2(rootX-targetX,rootY-targetY)+1.5708F+(random(-Weapons[mainWeapon][4],Weapons[mainWeapon][4])/50.0F);; //In radians
          } else {
            aimingAngle = atan2(rootX-targetX,rootY-targetY)+1.5708F+(random(-Weapons[mainWeapon][4],Weapons[mainWeapon][4])/50.0F);; //In radians
          }
          bool shoot = true;
          if(player.mainPlayer.PlayerDir == 1) {
            if(aimingAngle-1.5708F != constrain(aimingAngle-1.5708F,-PI,0)) {
              shoot = false;
            }
          } else {
            if(aimingAngle-1.5708F != constrain(aimingAngle-1.5708F,0,PI)) {
              shoot = false;
            }
          }

          if(shoot) {
            gb.display.setColor(BLACK);
            gb.display.drawLine(toScreenX(rootX),toScreenY(rootY),toScreenX(targetX),toScreenY(targetY));
            
            int8_t bulletID = bulletsManager.spawnBullet(
              rootX*SCALE+(2*SCALE),
              rootY*SCALE+(2*SCALE),
              -(int16_t)(cos(aimingAngle)*Weapons[mainWeapon][1]+random(-Weapons[mainWeapon][2]*10,Weapons[mainWeapon][2]*10)/10.0F),
              (int16_t)(sin(aimingAngle)*Weapons[mainWeapon][1]+random(-Weapons[mainWeapon][2]*10,Weapons[mainWeapon][2]*10)/10.0F),
              player.mainPlayer.PlayerColor,
              0
            );
            if(bulletID!=-1) {
              bulletsManager.bullets[bulletID].gravity = Weapons[mainWeapon][3];
              bulletsManager.bullets[bulletID].Damage = Weapons[mainWeapon][6];
              bulletsManager.bullets[bulletID].BulletTimeLimit = Weapons[mainWeapon][7];
            }
          }
        }
      }
      break;
      case 1: //--Rollers
      if(gb.buttons.held(BUTTON_B,Weapons[mainWeapon][5]) && !(gb.buttons.timeHeld(BUTTON_B) > Weapons[mainWeapon][5]+Weapons[mainWeapon][9])) { //Attack (If not rolling)
        float aimingAngle = 0;
        shakeTimeLeft += 3;
        shakeAmplitude += 2;
        for(uint8_t b = 0; b < Weapons[mainWeapon][8]; b++) {
          int16_t rootX = player.mainPlayer.x/SCALE;
          int16_t rootY = player.mainPlayer.y/SCALE;
          
          if(player.mainPlayer.PlayerDir == 1) {
            //root = + 22,9 from player
            rootX+=14;
            rootY+=5;
    
            aimingAngle = (0)+(random(-Weapons[mainWeapon][4],Weapons[mainWeapon][4])/50.0F);
          } else if(player.mainPlayer.PlayerDir == -1) {
            //root = + 2,9 from player
            rootX-=7;
            rootY+=5;
    
            aimingAngle = (PI)+(random(-Weapons[mainWeapon][4],Weapons[mainWeapon][4])/50.0F);
          }
          int8_t bulletID = bulletsManager.spawnBullet(
            rootX*SCALE+(2*SCALE),
            rootY*SCALE+(2*SCALE),
            -(int16_t)(cos(aimingAngle)*(Weapons[mainWeapon][1]+random(-Weapons[mainWeapon][2]*10,Weapons[mainWeapon][2]*10)/10.0F)),
            (int16_t)(sin(aimingAngle)*(Weapons[mainWeapon][1]+random(-Weapons[mainWeapon][2]*10,Weapons[mainWeapon][2]*10)/10.0F))+-Weapons[mainWeapon][11],
            player.mainPlayer.PlayerColor,
            0
          );
          if(bulletID!=-1) {
            bulletsManager.bullets[bulletID].gravity = Weapons[mainWeapon][3];
            bulletsManager.bullets[bulletID].Damage = Weapons[mainWeapon][6];
            bulletsManager.bullets[bulletID].BulletTimeLimit = Weapons[mainWeapon][7];
          }
        }
      }
      if(gb.buttons.timeHeld(BUTTON_B) > Weapons[mainWeapon][5]+Weapons[mainWeapon][9] && gb.buttons.repeat(BUTTON_B,1)) { //Rolling (After attack length)
        float aimingAngle = 0;
        for(uint8_t b = 0; b < Weapons[mainWeapon][8]/2; b++) {
          int16_t rootX = player.mainPlayer.x/SCALE;
          int16_t rootY = player.mainPlayer.y/SCALE;
          
          if(player.mainPlayer.PlayerDir == 1) {
            //root = + 22,9 from player
            rootX+=14;
            rootY+=5;
    
            aimingAngle = (0)+(random(-Weapons[mainWeapon][4],Weapons[mainWeapon][4])/50.0F);
          } else if(player.mainPlayer.PlayerDir == -1) {
            //root = + 2,9 from player
            rootX-=7;
            rootY+=5;
    
            aimingAngle = (PI)+(random(-Weapons[mainWeapon][4],Weapons[mainWeapon][4])/50.0F);
          }
          int8_t bulletID = bulletsManager.spawnBullet(
            rootX*SCALE+(2*SCALE),
            rootY*SCALE+(2*SCALE),
            0,
            -Weapons[mainWeapon][1],
            player.mainPlayer.PlayerColor,
            0
          );
          if(bulletID!=-1) {
            bulletsManager.bullets[bulletID].gravity = Weapons[mainWeapon][3];
            bulletsManager.bullets[bulletID].Damage = Weapons[mainWeapon][6]*2;
            bulletsManager.bullets[bulletID].BulletTimeLimit = Weapons[mainWeapon][7]/5;
          }
        }
      }
      break;
      case 2: //--Chargers
      if(gb.buttons.repeat(BUTTON_B,0)) {
        WeaponResetTimer += 1;
      }
      if(WeaponResetTimer > Weapons[mainWeapon][5]) { //Recharge Indicator
        int16_t rootX = player.mainPlayer.x/SCALE;
        int16_t rootY = player.mainPlayer.y/SCALE;
        int16_t targetX = cameraX+curX;
        int16_t targetY = cameraY+curY;
        if(player.mainPlayer.PlayerDir == 1) {
          //root = + 22,9 from player
          rootX+=14;
          rootY+=5;
        } else if(player.mainPlayer.PlayerDir == -1) {
          //root = + 2,9 from player
          rootX-=7;
          rootY+=5;
        }

        gb.display.setColor((ColorIndex)3);
        gb.display.drawLine(toScreenX(rootX),toScreenY(rootY),toScreenX(targetX),toScreenY(targetY));
        WeaponRecharged = true;
      }
      if(WeaponRecharged && gb.buttons.released(BUTTON_B)) { //Held for a certain length then released
        WeaponRecharged = false;
        WeaponResetTimer = 0;
        
        float aimingAngle = 0;
        float driftX = 0;
        float driftY = 0;
        int16_t rootX = player.mainPlayer.x/SCALE;
        int16_t rootY = player.mainPlayer.y/SCALE;
        int16_t targetX = cameraX+curX;
        int16_t targetY = cameraY+curY;
        if(player.mainPlayer.PlayerDir == 1) {
          //root = + 22,9 from player
          rootX+=14;
          rootY+=5;
        } else if(player.mainPlayer.PlayerDir == -1) {
          //root = + 2,9 from player
          rootX-=7;
          rootY+=5;
        }
        if(player.mainPlayer.PlayerDir == 1) {
          aimingAngle = atan2(rootX-targetX,rootY-targetY)+1.5708F+(random(-Weapons[mainWeapon][4],Weapons[mainWeapon][4])/50.0F); //In radians
        } else {
          aimingAngle = atan2(rootX-targetX,rootY-targetY)+1.5708F+(random(-Weapons[mainWeapon][4],Weapons[mainWeapon][4])/50.0F); //In radians
        }
        if(player.mainPlayer.PlayerDir == 1) {
          if(aimingAngle-1.5708F != constrain(aimingAngle-1.5708F,-PI,0)) {
            break;
          }
        } else {
          if(aimingAngle-1.5708F != constrain(aimingAngle-1.5708F,0,PI)) {
            break;
          }
        }
        shakeTimeLeft += 3;
        shakeAmplitude += 1;
        for(uint8_t b = 0; b < Weapons[mainWeapon][8]; b++) {
          gb.display.setColor((ColorIndex)0);
          gb.display.drawLine(toScreenX(rootX),toScreenY(rootY),toScreenX(targetX),toScreenY(targetY));

          driftX += cos(aimingAngle)*(Weapons[mainWeapon][1]/3.0F);
          driftY += sin(aimingAngle)*(Weapons[mainWeapon][1]/3.0F);

          //gb.display.setColor(RED);
          //gb.display.drawRect(toScreenX((rootX+2+driftX/SCALE)/8*8),toScreenY((rootY+2-driftY/SCALE)/8*8),8,8);
          if(world.getTile((rootX+2+driftX/SCALE)/8,(rootY+2-driftY/SCALE)/8) != 0) {
            break;
          }
          
          int8_t bulletID = bulletsManager.spawnBullet(
            rootX*SCALE+(2*SCALE)+(int16_t)driftX,
            rootY*SCALE+(2*SCALE)-(int16_t)driftY,
            -(int16_t)(cos(aimingAngle)*50),
            (int16_t)(sin(aimingAngle)*50),
            player.mainPlayer.PlayerColor,
            0
          );
          if(bulletID!=-1) {
            bulletsManager.bullets[bulletID].gravity = Weapons[mainWeapon][3];
            bulletsManager.bullets[bulletID].Damage = Weapons[mainWeapon][6];
            bulletsManager.bullets[bulletID].BulletTimeLimit = Weapons[mainWeapon][7];
          }
        }
      }
      break;
      case 3: //--Rush attack weapons
      if(gb.buttons.held(BUTTON_B,Weapons[mainWeapon][5])) {
        float aimingAngle = 0;
        for(uint8_t b = 0; b < Weapons[mainWeapon][8]; b++) {
          int16_t rootX = player.mainPlayer.x/SCALE;
          int16_t rootY = player.mainPlayer.y/SCALE;
          
          if(player.mainPlayer.PlayerDir == 1) {
            //root = + 22,9 from player
            rootX+=14;
            rootY+=5;
    
            aimingAngle = (0)+(random(-Weapons[mainWeapon][4],Weapons[mainWeapon][4])/50.0F);
          } else if(player.mainPlayer.PlayerDir == -1) {
            //root = + 2,9 from player
            rootX-=7;
            rootY+=5;
    
            aimingAngle = (PI)+(random(-Weapons[mainWeapon][4],Weapons[mainWeapon][4])/50.0F);
          }
          int8_t bulletID = bulletsManager.spawnBullet(
            rootX*SCALE+(2*SCALE),
            rootY*SCALE+(2*SCALE),
            -(int16_t)(cos(aimingAngle)*(Weapons[mainWeapon][1]+random(-Weapons[mainWeapon][2]*10,Weapons[mainWeapon][2]*10)/10.0F)),
            (int16_t)(sin(aimingAngle)*(Weapons[mainWeapon][1]+random(-Weapons[mainWeapon][2]*10,Weapons[mainWeapon][2]*10)/10.0F))+-Weapons[mainWeapon][11],
            player.mainPlayer.PlayerColor,
            0
          );
          if(bulletID!=-1) {
            bulletsManager.bullets[bulletID].gravity = Weapons[mainWeapon][3];
            bulletsManager.bullets[bulletID].Damage = Weapons[mainWeapon][6];
            bulletsManager.bullets[bulletID].BulletTimeLimit = Weapons[mainWeapon][7];
          }
        }
      }
      break;
    }

    gb.display.setColor(BLACK);
    gb.display.fillRect(curX-4,curY-5,7,9);
    gb.display.fillRect(curX-5,curY-4,9,7);

    gb.display.setColor(WHITE); //Was Invert
    gb.display.drawBitmap(curX-4,curY-4,Cursor);
    gb.display.drawBitmap(84-curX-4,curY-4,Cursor);
  } else {
    gb.display.setColor(BLACK);
    gb.display.drawBitmap(curX-4,curY-4,Cursor);

    WeaponRecharged = false;
  }
}

void DrawUI() {
  gb.display.setColor(WHITE);
  gb.display.fillRect(0,0,84,6);
  
  gb.display.setColor(BLACK);
  gb.display.setCursor(0,0);
  //gb.display.print(gb.getFreeRam());
  //gb.display.print(player.mainPlayer.Live);
  gb.display.print(cpuLoad);

  lastLoad[0] = lastLoad[1];
  lastLoad[1] = lastLoad[2];
  lastLoad[2] = lastLoad[3];
  lastLoad[3] = lastLoad[4];
  lastLoad[4] = lastLoad[5];
  lastLoad[5] = lastLoad[6];
  lastLoad[6] = lastLoad[7];
  lastLoad[7] = gb.getCpuLoad();
  
  cpuLoad = Div8(lastLoad[0]+lastLoad[1]+lastLoad[2]+lastLoad[3]+lastLoad[4]+lastLoad[5]+lastLoad[6]+lastLoad[7]);
}

void setup() {
  gb.begin();
  gb.pickRandomSeed();
  colorGroup = random(0,7);
  gb.display.colorIndex = palette;
  PrepareMap();
}

byte Mode = 0;
long r1 = 0;
long r2 = 0;

void loop () {
  if(gb.update()) {
    gb.display.setColor((ColorIndex)12);
    gb.display.fill();
    //gb.display.drawImage(0,8,BackGCity0);
    //gb.display.drawImage(-cameraX/5,(world.MapHeight*2-cameraY)/5,BackGCity0);
    //gb.display.setColor((ColorIndex)13);
    //gb.display.fillRect(-cameraX/5,((world.MapHeight*2-cameraY)+BackGCity0.height()*4)/5,BackGCity0.width(),BackGCity0.height());
    
    if(IsPlaying) {
      if(gb.buttons.pressed(BUTTON_MENU)) {
        if(gb.buttons.repeat(BUTTON_B, 0)) {
          mainWeapon++;
          if(mainWeapon > WeaponCount) {
            mainWeapon = 0;
          }
        } else if(gb.buttons.repeat(BUTTON_A, 0)) {
          player.mainPlayer.PlayerColor = (player.mainPlayer.PlayerColor+1)%2;
        } else {
          long BlackScore = 0;
          long WhiteScore = 0;
          
          for(byte x = 0; x < world.MapWidth; x++) {
            for(byte y = 0; y < world.MapHeight; y++) {
              if(world.getTile(x,y) != 0) {
                if(world.SMGetColor(x,y) == 0) {
                  //Black
                  BlackScore += (world.SMGetPaintValueAt(x,y,0)+world.SMGetPaintValueAt(x,y,1)+world.SMGetPaintValueAt(x,y,2)+world.SMGetPaintValueAt(x,y,3));
                } else if(world.SMGetColor(x,y) == 1) {
                  //White
                  WhiteScore += (world.SMGetPaintValueAt(x,y,0)+world.SMGetPaintValueAt(x,y,1)+world.SMGetPaintValueAt(x,y,2)+world.SMGetPaintValueAt(x,y,3));
                }
              }
            }
          }

          r1 = BlackScore;
          r2 = WhiteScore;

          Mode = 1;
        }
      }
      
      if(Mode == 0) {
        player.UpdateGlobal();
        world.Update();
        
        bulletsManager.Update();
        DrawCursor();

        if((Weapons[mainWeapon][0]) == 2 && gb.buttons.repeat(BUTTON_B,0)) {
          cameraX = (cameraX*5+(player.mainPlayer.x/SCALE+4-(LCDWIDTH/2) + ((curX-LCDWIDTH/2)/6)*10 + (-player.mainPlayer.vx/5)))/6;
          cameraY = (cameraY*4+(player.mainPlayer.y/SCALE+4-(LCDHEIGHT/2) + ((curY-LCDWIDTH/2)/6)*12 + (-player.mainPlayer.vy/5)))/5;
        } else {
          cameraX = (cameraX*5+(player.mainPlayer.x/SCALE+4-(LCDWIDTH/2) + ((curX-LCDWIDTH/2)/4)*3 + (-player.mainPlayer.vx/5)))/6;
          cameraY = (cameraY*4+(player.mainPlayer.y/SCALE+4-(LCDHEIGHT/2) + ((curY-LCDWIDTH/2)/6)*4 + (-player.mainPlayer.vy/5)))/5;
        }

        /*if(gb.buttons.repeat(BUTTON_UP,0)) {
          cameraY+=1;
        }
        if(gb.buttons.repeat(BUTTON_DOWN,0)) {
          cameraY-=1;
        }
        if(gb.buttons.repeat(BUTTON_LEFT,0)) {
          cameraX-=1;
        }
        if(gb.buttons.repeat(BUTTON_RIGHT,0)) {
          cameraX+=1;
        }*/
        
        if(shakeTimeLeft > 0) {
          shakeTimeLeft--;
          cameraX += random(-1, 2) * shakeAmplitude;
          cameraY += random(-1, 2) * shakeAmplitude;
        } else {
          shakeAmplitude = 0;
        }

        ClampCamera();

        if(AnimationTimer<=0) {
          DrawUI();
        }
      } else if(Mode == 1) {
        gb.display.setColor(WHITE);
        gb.display.fillRect(0,0,84,6+6);
        
        gb.display.setColor(BLACK);
        gb.display.cursorX = 0;
        gb.display.cursorY = 0;
        gb.display.print(r1);
        gb.display.cursorX = 0;
        gb.display.cursorY = 7;
        gb.display.print(r2);

        if(gb.buttons.repeat(BUTTON_A, 0)) {
          Mode = 0;
        }
      }

      if(AnimationTimer > 0) {
        if(AnimationTimer > STARTLENGHT/3*2) {
          cameraX = ClampInt(0,(world.MapWidth*8)-LCDWIDTH,(GetMap[world.CurrentLoadedMap][2]*8)+4-(LCDWIDTH/2));
          cameraY = ClampInt(0,(world.MapHeight*8)-LCDHEIGHT,(GetMap[world.CurrentLoadedMap][3])+4-(LCDHEIGHT/2));
        } else if(AnimationTimer > STARTLENGHT/3) {
          cameraX = ClampInt(0,(world.MapWidth*8)-LCDWIDTH,(GetMap[world.CurrentLoadedMap][0]*8) - 8*pgm_read_byte(GetMap[world.CurrentLoadedMap] + 2)+4-(LCDWIDTH/2));
          cameraY = ClampInt(0,(world.MapHeight*8)-LCDHEIGHT,(GetMap[world.CurrentLoadedMap][3])+4-(LCDHEIGHT/2));
        } else {
          if(AnimationTimer > (STARTLENGHT/3/2)) {
            cameraX = ClampInt(0,(world.MapWidth*8)-LCDWIDTH,(GetMap[world.CurrentLoadedMap][2]*8)+4-(LCDWIDTH/2));
            cameraY = ClampInt(0,(world.MapHeight*8)-LCDHEIGHT,(GetMap[world.CurrentLoadedMap][3]*8)+4-(LCDHEIGHT/2));
            gb.display.setColor(BLACK);
            gb.display.cursorX = 12;
            gb.display.cursorY = 24;
            gb.display.fontSize = 2;
            gb.display.print(F("READY?"));
          } else {
            gb.display.setColor(BLACK);
            gb.display.cursorX = 12;
            gb.display.cursorY = 24;
            gb.display.fontSize = 3;
            gb.display.print(F("GO!"));
            FreezePlayers = false;
          }
        }
        
        AnimationTimer--;
        if(AnimationTimer <= 0) {
          gb.display.setColor(BLACK);
          gb.display.cursorX = 0;
          gb.display.cursorY = 0;
          gb.display.fontSize = 1;
          gb.display.print(F(""));
        }
      }
    }
  }
}
