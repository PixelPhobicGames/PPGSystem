#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <raylib.h>
#include <stdlib.h>
#include <cstring>

using namespace std;

#define MaxVaribles 16384 // Can Change these

#define MaxJumpPoints 16384 //

#define MaxArraySize 100

#define MaxArrays 100

static int VaribleCounter = 0;
static int LocalVaribleCounter = 0;

static int JumpPointCounter = 0;

static int ArrayCounter = 0;

static int DisplayScale = 1;

Color PDBlue = {22, 114, 136 , 255};
Color PLBlue = {140, 218, 236 , 255};
Color PDRed = {180, 82, 72, 255};
Color PLRed = {212, 140, 132 , 255};
Color PDYellow = {168, 154, 73, 255};
Color PLYellow = {214, 207, 162 , 255};
Color PDGreen = {60, 180, 100, 255};
Color PLGreen = {155, 221, 177 , 255};
Color PDPurple = {100, 60, 106, 255};
Color PLPurple = {131, 99, 148 , 255};


typedef struct Memory{
    string Name;
    string Value;
    int IValue;
}Memory;


static Memory VaribleMemory[MaxVaribles];

static Memory LocalVaribleMemory[MaxVaribles];

typedef struct ArrMemory{
    string Name;
    int Array[MaxArraySize];
    int Size;
}ArrMemory;


static ArrMemory ArrayMemory[MaxArrays];

typedef struct JumpPoint{
    string Name;
    int LineNumber;
}JumpPoint;


static JumpPoint JumpPoints[MaxJumpPoints];



typedef struct ParasiteScriptData{
   istringstream ProgramData;
   
   string Line[32768]; // 32kb
   
   int LineCounter;
   int ProgramSize;

   bool CompareFlag;

   bool EqualFlag;
   bool GreaterFlag;
   bool LesserFlag;
   bool NotEqualFlag;
   bool ContinueFlag;
   bool ElseFlag;
   bool ErrorFlag;

   int ReturnLine;
   int TextSize;
   
   Sound SFX1;
   Sound SFX2;
   Sound SFX3;
   Sound SFX4;
   Sound SFX5;

}ParasiteScriptData;

static ParasiteScriptData ParasiteScriptCoreData;


