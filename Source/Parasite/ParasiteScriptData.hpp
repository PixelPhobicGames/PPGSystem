#include <iostream>
#include <string>
#include <sstream>

#include <fstream>
#include <raylib.h>
#include <stdlib.h>
#include <cstring>

using namespace std;

#define MaxVaribles 1000 // Can Change these

#define MaxJumpPoints 100 //

static int VaribleCounter = 0;

static int JumpPointCounter = 0;

typedef struct Memory{
    string Name;
    string Value;
    int IValue;
}Memory;


static Memory VaribleMemory[MaxVaribles];

typedef struct JumpPoint{
    string Name;
    int LineNumber;
}JumpPoint;


static JumpPoint JumpPoints[MaxJumpPoints];



typedef struct ParasiteScriptData{
   istringstream ProgramData;
   
   string Line[10000];
   
   int LineCounter;
   int ProgramSize;

   bool CompareFlag;

   bool EqualFlag;
   bool GreaterFlag;
   bool LesserFlag;
   bool NotEqualFlag;

   int ReturnLine;
   int TextSize;
   
   Sound SFX1;
   Sound SFX2;
   Sound SFX3;
   Sound SFX4;
   Sound SFX5;

}ParasiteScriptData;

static ParasiteScriptData ParasiteScriptCoreData;


