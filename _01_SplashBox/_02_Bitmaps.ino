// COLLIDERS
/////////////////

const byte Col_0[] = {
  8,8,0,0,0,0,0,0,0,0
};
const byte Col_1[] = {
  8,8,255,255,255,255,255,255,255,255
};
const byte Col_2[] = {
  8,8,0,0,0,0,255,255,255,255
};
const byte Col_3[] = {
  8,8,255,255,255,255,0,0,0,0
};
const byte Col_4[] = {
  8,8,
  B00001111,
  B00001111,
  B00001111,
  B00001111,255,255,255,255
};
const byte Col_5[] = {
  8,8,
  B11110000,
  B11110000,
  B11110000,
  B11110000,255,255,255,255
};
const byte Col_6[] =
{
  8,8,255,255,255,255,
  B11110000,
  B11110000,
  B11110000,
  B11110000
};
const byte Col_7[] = {
  8,8,255,255,255,255,
  B00001111,
  B00001111,
  B00001111,
  B00001111
};

const byte* Colliders[] = {
  Col_0,
  Col_1,
  Col_2,
  Col_3,
  Col_4,
  Col_5,
  Col_6,
  Col_7
};

// GENERAL
/////////////////
const byte Cursor[] =
{
  8,8,
  B00111000,
  B00010000,
  B10000010,
  B11000110,
  B10000010,
  B00010000,
  B00111000,
  B00000000
};

const byte Empty[] = //ID: 0
{
  8,8,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

const byte Wall1[] = //ID: 2
{
  8,8,
  B11111111,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

const byte Wall2[] = //ID: 3
{
  8,8,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001
};

const byte Wall3[] = //ID: 4
{
  8,8,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B11111111
};

const byte Wall4[] = //ID: 5
{
  8,8,
  B10000000,
  B10000000,
  B10000000,
  B10000000,
  B10000000,
  B10000000,
  B10000000,
  B10000000
};

const byte Corner1[] = //ID: 6
{
  8,8,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B10000000
};

const byte Corner2[] = //ID: 7
{
  8,8,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000001
};

const byte Corner3[] = //ID: 8 WORKING
{
  8,8,
  B00000001,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

const byte Corner4[] = //ID: 9
{
  8,8,
  B10000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

//SPLASH SPRITES

const byte SWall1[] =
{
  8,8,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

const byte SWall2[] =
{
  8,8,
  B11111111,
  B01110110,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

const byte SWall3[] =
{
  8,8,
  B11111111,
  B01101110,
  B00000100,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

const byte SWall4[] =
{
  8,8,
  B11111111,
  B11111111,
  B01111110,
  B00101100,
  B00000100,
  B00000000,
  B00000000,
  B00000000
};

const byte SCorner1[] =
{
  8,8,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

const byte SCorner2[] =
{
  8,8,
  B00000111,
  B00000011,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

const byte SCorner3[] =
{
  8,8,
  B00000111,
  B00000011,
  B00000101,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

const byte SCorner4[] =
{
  8,8,
  B00001111,
  B00001111,
  B00000111,
  B00001001,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};





//BUILDING TILES HERE
//-------------------

const byte Grid[] = //ID: 0
{
  8,8,
  B01010101,
  B10101010,
  B01010101,
  B10101010,
  B01010101,
  B10101010,
  B01010101,
  B10101010
};

const byte Brick[] = //ID: 1
{
  8,8,
  B11111111,
  B01000100,
  B01000100,
  B11111111,
  B00100010,
  B00100010,
  B11111111,
  B00010001
};

const byte GroundBrick[] = //ID: 2
{
  8,8,
  B11111111,
  B00110011,
  B11001100,
  B00110011,
  B11001100,
  B00110011,
  B11001100,
  B11111111
};

const byte ClassicBrick[] = //ID: 3
{
  8,8,
  B11111111,
  B00010001,
  B11111111,
  B01000100,
  B11111111,
  B00010001,
  B11111111,
  B01000100
};

const byte TopPillar[] = //ID: 4
{
  8,8,
  B10010101,
  B11111111,
  B10000001,
  B11111111,
  B10000001,
  B01000010,
  B00100100,
  B00100100
};

const byte MiddlePillar[] = //ID: 5
{
  8,8,
  B00100100,
  B00101100,
  B00110100,
  B00100100,
  B00100100,
  B00101100,
  B00110100,
  B00100100
};

const byte BottomPillar[] = //ID: 6
{
  8,8,
  B00100100,
  B00100100,
  B01000010,
  B10000001,
  B11111111,
  B10000000,
  B11111111,
  B10010101
};

const byte ConstructionPillarHorizontal[] = //ID: 7
{
  8,8,
  B11111111,
  B00000000,
  B11011011,
  B00100100,
  B00100100,
  B11011011,
  B00000000,
  B11111111
};

const byte ConstructionPillarHorizontal2[] = //ID: 8
{
  8,8,
  B11111111,
  B00100000,
  B11111111,
  B00000000,
  B00000000,
  B11111111,
  B00000100,
  B11111111
};

const byte ConstructionPillarLeft[] = //ID: 9
{
  8,8,
  B11111111,
  B10000000,
  B11011011,
  B10100100,
  B10100100,
  B11011011,
  B10000000,
  B11111111
};

const byte ConstructionPillarRight[] = //ID: 10
{
  8,8,
  B11111111,
  B00000001,
  B11011011,
  B00100101,
  B00100101,
  B11011011,
  B00000001,
  B11111111
};

const byte ConstructionPillarVertical[] = //ID: 11
{
  8,8,
  B10100101,
  B10100101,
  B10011001,
  B10100101,
  B10100101,
  B10011001,
  B10100101,
  B10100101
};

const byte ConstructionPillarVertical2[] = //ID: 12
{
  8,8,
  B10100101,
  B10100101,
  B11100101,
  B10100101,
  B10100101,
  B10100111,
  B10100101,
  B10100101
};

const byte ConstructionPillarTop[] = //ID: 13
{
  8,8,
  B11111111,
  B10100101,
  B10011001,
  B10100101,
  B10100101,
  B10011001,
  B10100101,
  B10100101
};

const byte ConstructionPillarBottom[] = //ID: 14
{
  8,8,
  B10100101,
  B10100101,
  B10011001,
  B10100101,
  B10100101,
  B10011001,
  B10100101,
  B11111111
};

const byte TopBrickPillar[] = //ID: 15
{
  8,8,
  B11111111,
  B10000001,
  B11111111,
  B10101101,
  B10110101,
  B10101101,
  B10110101,
  B10101101
};

const byte MiddleBrickPillar[] = //ID: 16
{
  8,8,
  B10110101,
  B10101101,
  B10110101,
  B10101101,
  B10110101,
  B10101101,
  B10110101,
  B10101101
};

const byte MiddleBrickPillar2[] = //ID: 17
{
  8,8,
  B10110101,
  B10101111,
  B10110101,
  B10101101,
  B10110101,
  B11101101,
  B10110101,
  B10101101
};

const byte BottomBrickPillar[] = //ID: 18
{
  8,8,
  B10110101,
  B10101101,
  B10110101,
  B10101101,
  B10110101,
  B11111111,
  B10000001,
  B11111111
};

const byte PolishedBrick[] = //ID: 19
{
  8,8,
  B11111111,
  B11000001,
  B10100011,
  B10000111,
  B10000111,
  B10111011,
  B10111101,
  B11111111
};

const byte FancyFloorLeft[] = //ID: 20
{
  8,8,
  B11111111,
  B10100110,
  B10111001,
  B10100110,
  B10111001,
  B10100110,
  B10111001,
  B11111111
};

const byte FancyFloorMiddle[] = //ID: 21
{
  8,8,
  B11111111,
  B01100110,
  B10011001,
  B01100110,
  B10011001,
  B01100110,
  B10011001,
  B11111111
};

const byte FancyFloorRight[] = //ID: 22
{
  8,8,
  B11111111,
  B01100101,
  B10011101,
  B01100101,
  B10011101,
  B01100101,
  B10011101,
  B11111111
};

const byte FancyFloorSingle[] = //ID: 23
{
  8,8,
  B11111111,
  B10101101,
  B10110101,
  B10101101,
  B10110101,
  B10101101,
  B10110101,
  B11111111
};

const byte HalfPillarTop[] = //ID: 24
{
  8,8,
  B00000000,
  B00000000,
  B00000000,
  B11111111,
  B10000001,
  B11111111,
  B10110101,
  B10101101
};

const byte BuildingSingle[] = //ID: 25
{
  8,8,
  B00000000,
  B00000000,
  B00111100,
  B00100100,
  B00100100,
  B00111100,
  B00000000,
  B00000000
};

const byte BuildingLeft[] = //ID: 26
{
  8,8,
  B00000000,
  B00000000,
  B00111111,
  B00100000,
  B00100000,
  B00111111,
  B00000000,
  B00000000
};

const byte BuildingMiddle[] = //ID: 27
{
  8,8,
  B00000000,
  B00000000,
  B11111111,
  B00000000,
  B00000000,
  B11111111,
  B00000000,
  B00000000
};

const byte BuildingRight[] = //ID: 28
{
  8,8,
  B00000000,
  B00000000,
  B11111100,
  B00000100,
  B00000100,
  B11111100,
  B00000000,
  B00000000
};

const byte SmallRocks[] = //ID: 29
{
  8,8,
  B01100110,
  B10011001,
  B00000000,
  B01100110,
  B10011001,
  B00000000,
  B01100110,
  B10011001
};

const byte BigRocks[] = //ID: 30
{
  8,8,
  B01100111,
  B10000000,
  B10000000,
  B10000001,
  B01110110,
  B10001000,
  B10001000,
  B10010100
};

const byte Road[] = //ID: 31
{
  8,8,
  B11111111,
  B10011001,
  B11111111,
  B11010110,
  B00000000,
  B01000100,
  B00001001,
  B00100000
};

const byte UnderRoad[] = //ID: 32
{
  8,8,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

const byte SurfaceRoad[] = //ID: 33
{
  8,8,
  B11010110,
  B00000000,
  B01000100,
  B00001001,
  B00100000,
  B00000000,
  B00000000,
  B00000000
};

const byte Barrier[] = //ID: 34
{
  8,8,
  B11111111,
  B10100001,
  B11111111,
  B11111111,
  B11111111,
  B10000101,
  B11111111,
  B11111111
};

const byte CityCaseTop[] = //ID: 35
{
  8,8,
  B11111111,
  B10000001,
  B10111111,
  B10100001,
  B10100001,
  B10100001,
  B10100001,
  B10100001
};

const byte CityCaseBottom[] = //ID: 36
{
  8,8,
  B10100001,
  B10100001,
  B10100001,
  B10100001,
  B10100001,
  B10100001,
  B10100001,
  B11111111
};

const byte CityCasePipeLeft[] = //ID: 37
{
  8,8,
  B00000000,
  B00000000,
  B00000000,
  B00111111,
  B00100000,
  B00101111,
  B00101000,
  B00101000
};

const byte CityCasePipeMiddle[] = //ID: 38
{
  8,8,
  B00000000,
  B00000000,
  B00000000,
  B11111111,
  B00000000,
  B11101111,
  B00101000,
  B00101000
};

const byte CityCasePipeRight[] = //ID: 39
{
  8,8,
  B00000000,
  B00000000,
  B00000000,
  B11111000,
  B00001000,
  B11101000,
  B00101000,
  B00101000
};

const byte MetalPlateSingle[] = //ID: 40
{
  8,8,
  B11111111,
  B10000001,
  B10100101,
  B10000001,
  B10000001,
  B10100101,
  B10000001,
  B11111111
};

const byte MetalPlateHorizontalLeft[] = //ID: 41
{
  8,8,
  B11111111,
  B10000000,
  B10100000,
  B10000000,
  B10000000,
  B10100000,
  B10000000,
  B11111111
};

const byte MetalPlateHorizontalMiddle[] = //ID: 42
{
  8,8,
  B11111111,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B11111111
};

const byte MetalPlateHorizontalRight[] = //ID: 43
{
  8,8,
  B11111111,
  B00000001,
  B00000101,
  B00000001,
  B00000001,
  B00000101,
  B00000001,
  B11111111
};

const byte MetalPlateVerticalTop[] = //ID: 44
{
  8,8,
  B11111111,
  B10000001,
  B10100101,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001
};

const byte MetalPlateVerticalMiddle[] = //ID: 45
{
  8,8,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001
};

const byte MetalPlateVerticalBottom[] = //ID: 46
{
  8,8,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10100101,
  B10000001,
  B11111111
};

const byte MetalPlateBoxUpLeft[] = //ID: 47
{
  8,8,
  B11111111,
  B10000000,
  B10100000,
  B10000000,
  B10000000,
  B10000000,
  B10000000,
  B10000000
};

const byte MetalPlateBoxUpMiddle[] = //ID: 48
{
  8,8,
  B11111111,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

const byte MetalPlateBoxUpRight[] = //ID: 49
{
  8,8,
  B11111111,
  B00000001,
  B00000101,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001
};

const byte MetalPlateBoxMiddleLeft[] = //ID: 50
{
  8,8,
  B10000000,
  B10000000,
  B10000000,
  B10000000,
  B10000000,
  B10000000,
  B10000000,
  B10000000
};

const byte MetalPlateBoxMiddleMiddle[] = //ID: 51
{
  8,8,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

const byte MetalPlateBoxMiddleRight[] = //ID: 52
{
  8,8,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001
};

const byte MetalPlateBoxBottomLeft[] = //ID: 53
{
  8,8,
  B10000000,
  B10000000,
  B10000000,
  B10000000,
  B10000000,
  B10100000,
  B10000000,
  B11111111
};

const byte MetalPlateBoxBottomMiddle[] = //ID: 54
{
  8,8,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B11111111
};

const byte MetalPlateBoxBottomRight[] = //ID: 55
{
  8,8,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000001,
  B00000101,
  B00000001,
  B11111111
};

const byte CityBridgeHeader[] = //ID: 56
{
  8,8,
  B11111111,
  B00000000,
  B00111100,
  B01000010,
  B00000001,
  B10000000,
  B00000001,
  B10000000
};

const byte CityBridgeSupport[] = //ID: 57
{
  8,8,
  B10000001,
  B00000001,
  B10000000,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001
};

const byte CityBridgeBottom[] = //ID: 58
{
  8,8,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001
};

/*const byte [] = //ID: 0
{
  8,8,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};*/

const byte* outlines[] = {
  Empty,
  Empty,
  Wall1,
  Wall2,
  Wall3,
  Wall4,
  Corner1,
  Corner2,
  Corner3,
  Corner4
};

const byte* mapTiles[] = {
  Empty,
  Grid,
  Brick,
  GroundBrick,
  ClassicBrick,
  
  TopPillar,
  MiddlePillar,
  BottomPillar,
  
  ConstructionPillarHorizontal,
  ConstructionPillarHorizontal2,
  ConstructionPillarLeft,
  ConstructionPillarRight,
  ConstructionPillarVertical,
  ConstructionPillarVertical2,
  ConstructionPillarTop,
  ConstructionPillarBottom,
  
  TopBrickPillar,
  MiddleBrickPillar,
  BottomBrickPillar,
  MiddleBrickPillar2,

  PolishedBrick,

  FancyFloorLeft,
  FancyFloorMiddle,
  FancyFloorRight,
  FancyFloorSingle,

  HalfPillarTop,

  BuildingSingle,
  BuildingLeft,
  BuildingMiddle,
  BuildingRight,

  SmallRocks,
  BigRocks,

  Road,
  UnderRoad,
  SurfaceRoad,
  Barrier,

  CityCaseTop,
  CityCaseBottom,
  CityCasePipeLeft,
  CityCasePipeMiddle,
  CityCasePipeRight,

  MetalPlateSingle,
  MetalPlateHorizontalLeft,
  MetalPlateHorizontalMiddle,
  MetalPlateHorizontalRight,
  MetalPlateVerticalTop,
  MetalPlateVerticalMiddle,
  MetalPlateVerticalBottom,
  MetalPlateBoxUpLeft,
  MetalPlateBoxUpMiddle,
  MetalPlateBoxUpRight,
  MetalPlateBoxMiddleLeft,
  MetalPlateBoxMiddleMiddle,
  MetalPlateBoxMiddleRight,
  MetalPlateBoxBottomLeft,
  MetalPlateBoxBottomMiddle,
  MetalPlateBoxBottomRight,

  CityBridgeHeader,
  CityBridgeSupport,
  CityBridgeBottom
};

const byte* splashes[12] = {
  SWall1,
  SWall2,
  SWall3,
  SWall4,
  SCorner1,
  SCorner2,
  SCorner3,
  SCorner4
};

const byte Bullet1_0[] =
{
  7,7,
  B00000000,
  B00000000,
  B00111100,
  B00111100,
  B00100000,
  B00000000,
  B00000000
};

const byte Bullet1_1[] =
{
  7,7,
  B00000000,
  B00000000,
  B00011100,
  B00111100,
  B00111000,
  B00000000,
  B00000000
};

const byte Bullet1_2[] =
{
  7,7,
  B00000000,
  B00000000,
  B00001100,
  B00001100,
  B00011000,
  B00100000,
  B00000000
};

const byte Bullet1_3[] =
{
  7,7,
  B00000000,
  B00010000,
  B00001000,
  B00001100,
  B00011000,
  B01000000,
  B00000000
};

const byte Bullet1_4[] =
{
  7,7,
  B00000000,
  B00000100,
  B00100000,
  B00001000,
  B01000100,
  B00011000,
  B00000000
};

const byte* bulletsSprite[] = {
  Bullet1_0,
  Bullet1_1,
  Bullet1_2,
  Bullet1_3,
  Bullet1_4,
};

const byte Hat0_1[] =
{
  8,8,
  B00000000,
  B00000011,
  B00000011,
  B00000011,
  B00000010,
  B00000111,
  B00000000,
  B00000000
};

const byte Hat0_2[] =
{
  8,8,
  B00000000,
  B11000000,
  B11000000,
  B11000000,
  B01000000,
  B11100000,
  B00000000,
  B00000000
};

const byte Hat1_1[] =
{
  8,8,
  B00000000,
  B00000000,
  B00000000,
  B00000011,
  B00000110,
  B00000111,
  B00000000,
  B00000000
};

const byte Hat1_2[] =
{
  8,8,
  B00000000,
  B00000000,
  B00000000,
  B10000000,
  B01000000,
  B11111000,
  B00000000,
  B00000000
};

const byte Hat2_1[] =
{
  8,8,
  B00000000,
  B00000000,
  B00000011,
  B00000011,
  B00001100,
  B00000111,
  B00000000,
  B00000000
};

const byte Hat2_2[] =
{
  8,8,
  B00000000,
  B00000000,
  B01000000,
  B11000000,
  B00110000,
  B11100000,
  B00000000,
  B00000000
};

const byte Hat3_1[] =
{
  8,8,
  B00000000,
  B00010110,
  B00101111,
  B00010111,
  B00000100,
  B00000111,
  B00000000,
  B00000000
};

const byte Hat3_2[] =
{
  8,8,
  B00000000,
  B00000000,
  B00000000,
  B10000000,
  B01000000,
  B11100000,
  B00000000,
  B00000000
};

const byte Hat4_1[] =
{
  8,8,
  B00000000,
  B00000000,
  B00000011,
  B00000111,
  B00000100,
  B00111111,
  B00000000,
  B00000000
};

const byte Hat4_2[] =
{
  8,8,
  B00000000,
  B00000000,
  B11000000,
  B11100000,
  B00100000,
  B11111100,
  B00000000,
  B00000000
};

const byte Hat5_1[] =
{
  8,8,
  B00000000,
  B00000001,
  B00000001,
  B00000010,
  B00000011,
  B00000101,
  B00000000,
  B00000000
};

const byte Hat5_2[] =
{
  8,8,
  B10000000,
  B01000000,
  B10000000,
  B11000000,
  B01000000,
  B10100000,
  B00000000,
  B00000000
};

const byte Hat6_1[] =
{
  8,8,
  B00000000,
  B00000000,
  B00000000,
  B00000011,
  B00001111,
  B00011111,
  B00010000,
  B00000000
};

const byte Hat6_2[] =
{
  8,8,
  B00010000,
  B00001000,
  B00111000,
  B11111000,
  B11110000,
  B11110000,
  B00000000,
  B00000000
};

const byte* hatsSprite[] = {
  Hat0_1,
  Hat0_2,
  Hat1_1,
  Hat1_2,
  Hat2_1,
  Hat2_2,
  Hat3_1,
  Hat3_2,
  Hat4_1,
  Hat4_2,
  Hat5_1,
  Hat5_2,
  Hat6_1,
  Hat6_2
};

const byte DefaultWall[] = {
  0,0,0,0,0,0,0,0
};

const byte DebugBytes[] = {
  1,1,1,1,1,1,1,1
};

const byte Map0[] = {
  //Size X, Size Y, SpawnCoord X, SpawnCoord Y
  46, 22, 2, 8,
  35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,
  35,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,15,00,00,15,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,35,
  35,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,35,
  35,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,35,
  35,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,35,
  35,00,00,00,00,00,00,00,00,00,00,00,00,00,00,31,31,00,00,00,00,14,00,00,14,00,00,00,00,31,31,00,00,00,00,00,00,00,00,00,00,00,00,00,00,35,
  35,00,00,00,00,00,00,00,00,00,00,00,00,00,31,31,31,00,00,00,00,12,00,00,12,00,00,00,00,31,31,13,00,00,00,00,00,00,00,00,00,00,00,00,00,35,
  35,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,12,00,00,12,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,35,
  35,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,13,00,00,13,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,35,
  35,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,15,00,00,15,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,35,
  35,00,00,00,00,00,00,10, 9, 9,11,00,00,00,00,00,14,00,00,00,00,00,00,00,00,00,00,00,00,14,00,00,00,00,00,10, 9, 9,11,00,00,00,00,00,00,35,
  35,00,00,00,48,50,00,00,00,00,00,00,00,00,00,00,13,00,00,00,00,00,00,00,00,00,00,00,00,13,00,00,00,00,00,00,00,00,00,00,48,50,00,00,00,35,
  35,00,00,00,54,56,00,00,00,00,00,00,00,00,10, 9,12,00,00,00,00,26,27,29,26,00,00,00,00,12, 9,11,00,00,00,00,00,00,00,00,54,56,00,00,00,35,
  35,00,00,42,43,44,00,00,00,00,00,00,00,00,00,00,15,00,00,00,00,26,26,27,29,00,00,00,00,15,00,00,00,00,00,00,00,00,00,00,42,43,44,00,00,35,
  35,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,27,28,29,26,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,35,
  16,00,00,00,00,00,00,00,00,10, 8,11,00,00,00,00,00,00,00,00,00,00,26,26,00,00,00,00,00,00,00,00,00,00,00,10, 8,11,00,00,00,00,00,00,00,35,
  17,00,00,00,00,45,45,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,45,45,00,00,00,00,17,
  17,00,00,00,00,46,47,00,00,00,00,00,00,36,36,32,32,00,00,00,00,00,00,00,00,00,00,00,00,32,32,36,36,00,00,00,00,00,00,47,46,00,00,00,00,17,
  17,00,00,48,50,47,41,00,00,00,00,00,00,37,37,33,33,00,31,00,00,00,00,00,00,00,00,31,00,33,33,37,37,00,00,00,00,00,00,41,47,48,50,00,00,17,
  17,00,00,51,53,48,49,50,00,00,00,00,32,34,34,33,33,00,31,31,00,00,00,00,00,00,31,31,00,33,33,34,34,32,00,00,00,00,48,49,50,51,53,00,00,17,
  17,00,00,51,53,51,52,53,00,00,00,00,33,33,33,33,33,31,31,31,00,31,00,00,31,00,31,31,31,33,33,33,33,33,00,00,00,00,51,52,53,51,53,00,00,17,
  34,32,32,54,56,54,55,56,32,32,32,32,33,33,33,33,33,30,30,30,30,30,30,30,30,30,30,30,30,33,33,33,33,33,32,32,32,32,54,55,56,54,56,32,32,34
};

const byte* GetMap[] {
  Map0
};
