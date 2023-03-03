#include "ParasiteScriptData.hpp"


// Parasite Script v.1.0

// Based of Parasites MSScript 

//#define ParasiteEnabled 


//#define SingleCore 
#define MultiCore

#if (defined(MultiCore))
#include <pthread.h>
#endif

#define RedText "\033[4;31m"
#define GreenText "\033[1;32m"
#define BlueText "\033[1;34m"
#define WhiteText "\033[1;37m"
static bool BenchMode = false;

auto ParasiteScriptLoadFile(const char* Path){ // Dont Use.. Use LoadScript();
    std::ifstream Input(Path);
    std::stringstream sstr;

    while(Input >> sstr.rdbuf());

    return sstr.str();
}


void ParasiteScriptInit(){ // Resets all Flags 
    ParasiteScriptCoreData.LesserFlag = false;
    ParasiteScriptCoreData.GreaterFlag = false;
    ParasiteScriptCoreData.EqualFlag = false;
    ParasiteScriptCoreData.NotEqualFlag = false;

    ParasiteScriptCoreData.CompareFlag = false;

    ParasiteScriptCoreData.ReturnLine = 0;
    ParasiteScriptCoreData.Line[0] = '\0';
    ParasiteScriptCoreData.ProgramSize = 0;
    ParasiteScriptCoreData.TextSize = 20;


    for (int i = 0 ; i <= MaxVaribles ; i++){
        VaribleMemory[i].IValue = 0;
    }
}
auto ReadValue(string Data , int Start , int End){ // Reads Value from (Start to End) 
    string Out;
    for (int i = Start ; i <= End ; i ++){
        Out += Data[i]; 
    }
    return Out;
}

auto SplitValue(string Data , int Place ){ 
    string Out;

    int PlaceCounter = 0; 

    int Start = 0;
    int End = 0;
    
    if (Place == 0){
        for (int i = 0 ; i <= Data.size() ; i ++){
            if (Data[i] == ' ' || i == Data.size()){
                End = i - 1;
                break;
            }
        }
    }
    else {
        Place = Place;
        PlaceCounter = 1;
        for (int i = 0 ; i <= Data.size() ; i ++){
            if (PlaceCounter == Place){
                Start = i + 1;
                for (int x = i+1 ; x <= Data.size(); x++){
                    if (Data[x] == ' ' || x == Data.size()){
                        End = x - 1;
                        break;
                    }
                }
            }
            if (Data[i] == ' '){
                PlaceCounter ++;
            }
        }
    }

    Out = ReadValue(Data , Start , End);

    return Out;
}


auto StringToInt(string Data){ // String To Integer Converter
    int Out = 0;
    int Place = 1;
    for (int i = Data.size() ; i >= 0; i--){
        
        switch (Data[i]){
            case '1':
                Out += 1 * Place;
                Place = Place * 10;
                break;
            case '2':
                Out += 2 * Place;
                Place = Place * 10;
                break;
            case '3':
                Out += 3 * Place;
                Place = Place * 10;
                break;
            case '4':
                Out += 4 * Place;
                Place = Place * 10;
                break;
            case '5':
                Out += 5 * Place;
                Place = Place * 10;
                break;
            case '6':
                Out += 6 * Place;
                Place = Place * 10;
                break;
            case '7':
                Out += 7 * Place;
                Place = Place * 10;
                break;
            case '8':
                Out += 8 * Place;
                Place = Place * 10;
                break;
            case '9':
                Out += 9 * Place;
                Place = Place * 10;
                break;
            case '0':
                Place = Place * 10;
                break;
            case '-':
                Out = Out * -1;
                break;
        }
        
    }
    
    return Out;
}

auto StringToChar(string Data){
    char Out[] = ""; 
    for (int i = 0 ; i <= Data.size(); i++){
        switch (Data[i]){
            case '1':
                memcpy(Out , "1" , 1);
                break;
        }
    }
    
    return Out;
}

void LoadScript(const char *ScriptPath){ // Loads Script
    istringstream ProgramData(ParasiteScriptLoadFile(ScriptPath));
    string CurrentLine;

    while (getline(ProgramData, CurrentLine)) {

        if (ReadValue(CurrentLine, 0 , 0) == ":"){            
            JumpPoints[JumpPointCounter].Name = ReadValue(CurrentLine, 1 , 4);
            JumpPoints[JumpPointCounter].LineNumber = ParasiteScriptCoreData.LineCounter;
            JumpPointCounter ++;
        }
        if (ReadValue(CurrentLine, 0 , 0) == " "){
            int SpaceCounter = 0;
            for (int i = 0 ; i <= CurrentLine.size() ; i ++){
                if (ReadValue(CurrentLine, i , i) == " ")SpaceCounter ++;
                else {
                    break;
                }
            }
            string Temp = ReadValue(CurrentLine, SpaceCounter , CurrentLine.size() - 1);
            CurrentLine = Temp;
        }
        ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] = CurrentLine;
        ParasiteScriptCoreData.LineCounter ++;

    } 
    ParasiteScriptCoreData.ProgramSize = ParasiteScriptCoreData.LineCounter;

    ParasiteScriptCoreData.LineCounter = 0;

    //exit(0);
} 

static bool TickFlag = false;

static int CycleCounter = 0;
static int TimeCounter = 0;

void* CycleInstruction(void* VInstruction){
    string Instruction = *static_cast<string*>(VInstruction);

    if (ParasiteScriptCoreData.LineCounter != ParasiteScriptCoreData.ProgramSize){
        if (SplitValue(Instruction, 0 ) == "stop"){
            
        }
        if (SplitValue(Instruction , 0 ) == "tick"){
            TickFlag = true;
        }

        if (SplitValue(Instruction, 0 ) == "var" || SplitValue(Instruction, 0 ) == "spr"){
            VaribleMemory[VaribleCounter].Name = SplitValue(Instruction, 1 );

            string VaribleData = SplitValue(Instruction, 2 );
            int VaribleType = 0;

            cout << RedText << "VD: " << VaribleData << " ";

            if (ReadValue(VaribleData , 0 , 0) == "'"){
                cout << "String Type\n";
                VaribleType = 1;
            }
            else {
                cout << "Int Type\n";
                VaribleType = 0;

            }
            
            if (VaribleType == 1){
                string StoredData = "";
                for (int i = 0 ; i <= VaribleData.size() ; i ++){
                    if (ReadValue(VaribleData , i , i) != "'"){
                        StoredData += ReadValue(VaribleData , i , i);
                    }
                }
                cout << "Parsed String: " << StoredData << "\n"; 
                VaribleMemory[VaribleCounter].Value = StoredData;
                VaribleMemory[VaribleCounter].IValue = 0;
            }
            else {
                VaribleMemory[VaribleCounter].IValue = StringToInt(VaribleData);
                VaribleMemory[VaribleCounter].Value = " ";

            }
            VaribleCounter++;   
            }

            if (SplitValue(Instruction, 0 ) == "jumpl"){   
                for (int i = 0 ; i <= JumpPointCounter ; i ++){
                    if (JumpPoints[i].Name == ReadValue(Instruction, 6 , 9)){
                            ParasiteScriptCoreData.ReturnLine = ParasiteScriptCoreData.LineCounter;
                            ParasiteScriptCoreData.LineCounter = JumpPoints[i].LineNumber;
                    }
                }
            }
            else {
                if (SplitValue(Instruction, 0 ) == "jump"){   
                    ParasiteScriptCoreData.LineCounter = StringToInt(SplitValue(Instruction, 1 )) - 2;
                }
            }

            if (SplitValue(Instruction, 0 ) == "addv"){   
                int Value1 = 0;
                int Value2 = 0;
                for (int i = 0 ; i <= VaribleCounter; i++){
                    if (VaribleMemory[i].Name == SplitValue(Instruction, 1 )){
                        Value1 = VaribleMemory[i].IValue;
                    }
                    if (VaribleMemory[i].Name == SplitValue(Instruction, 2 )){
                        Value2 = VaribleMemory[i].IValue;
                    }
                }

                for (int i = 0 ; i <= VaribleCounter; i++){
                    if (VaribleMemory[i].Name == SplitValue(Instruction, 1 )){
                        VaribleMemory[i].IValue = Value1 + Value2;
                        cout << BlueText << "addv Result:"<< VaribleMemory[i].IValue << "\n";
                    }
                }
            }

            if (SplitValue(Instruction, 0 ) == "subv"){   
                int Value1 = 0;
                int Value2 = 0;

                for (int i = 0 ; i <= VaribleCounter; i++){
                    if (VaribleMemory[i].Name == SplitValue(Instruction, 2 )){
                        Value2 = VaribleMemory[i].IValue;
                    }
                }


                for (int i = 0 ; i <= VaribleCounter; i++){
                    if (VaribleMemory[i].Name == SplitValue(Instruction, 1 )){
                        VaribleMemory[i].IValue = VaribleMemory[i].IValue - Value2;
                        cout << BlueText << "subv Result:"<< VaribleMemory[i].IValue << "\n";
                    }
                }
            }

            if (SplitValue(Instruction, 0 ) == "mulv"){   
                int Value1 = 0;
                int Value2 = 0;
                for (int i = 0 ; i <= VaribleCounter; i++){
                    if (VaribleMemory[i].Name == SplitValue(Instruction, 1 )){
                        Value1 = VaribleMemory[i].IValue;
                    }
                    if (VaribleMemory[i].Name == SplitValue(Instruction, 2 )){
                        Value2 = VaribleMemory[i].IValue;
                    }
                }

                for (int i = 0 ; i <= VaribleCounter; i++){
                    if (VaribleMemory[i].Name == SplitValue(Instruction, 1 )){
                        VaribleMemory[i].IValue = Value1 * Value2;
                        cout << BlueText << "mulv Result:"<< VaribleMemory[i].IValue << "\n";
                    }
                }
            }

            if (SplitValue(Instruction, 0 ) == "divv"){   
                int Value1 = 0;
                int Value2 = 0;
                for (int i = 0 ; i <= VaribleCounter; i++){
                    if (VaribleMemory[i].Name == SplitValue(Instruction, 1 )){
                        Value1 = VaribleMemory[i].IValue;
                    }
                    if (VaribleMemory[i].Name == SplitValue(Instruction, 2 )){
                        Value2 = VaribleMemory[i].IValue;
                    }
                }

                for (int i = 0 ; i <= VaribleCounter; i++){
                    if (VaribleMemory[i].Name == SplitValue(Instruction, 1 )){
                        VaribleMemory[i].IValue = Value1 / Value2;
                        cout << BlueText << "divv Result:"<< VaribleMemory[i].IValue << "\n";
                    }
                }
            }

            if (SplitValue(Instruction, 0 ) == "add"){   
                for (int i = 0 ; i <= VaribleCounter; i++){
                    if (VaribleMemory[i].Name == SplitValue(Instruction, 1 )){
                        VaribleMemory[i].IValue += StringToInt(SplitValue(Instruction, 2 ));
                        cout << BlueText << "add Result:"<< VaribleMemory[i].IValue << "\n";
                    }
                }
            }

            if (SplitValue(Instruction, 0 ) == "sub"){   
                for (int i = 0 ; i <= VaribleCounter; i++){
                    if (VaribleMemory[i].Name == SplitValue(Instruction, 1 )){
                        VaribleMemory[i].IValue -= StringToInt(SplitValue(Instruction, 2 ));
                        cout << BlueText << "sub Result:"<< VaribleMemory[i].IValue << "\n";
                    }
                }
            }

            if (SplitValue(Instruction, 0 ) == "mul"){   
                for (int i = 0 ; i <= VaribleCounter; i++){
                    if (VaribleMemory[i].Name == SplitValue(Instruction, 1 )){
                        VaribleMemory[i].IValue = VaribleMemory[i].IValue * StringToInt(SplitValue(Instruction, 2 ));
                        cout << BlueText << "mul Result:"<< VaribleMemory[i].IValue << "\n";
                    }
                }
            }

            if (SplitValue(Instruction, 0 ) == "div"){   
                for (int i = 0 ; i <= VaribleCounter; i++){
                    if (VaribleMemory[i].Name == SplitValue(Instruction, 1 )){
                        VaribleMemory[i].IValue = VaribleMemory[i].IValue / StringToInt(SplitValue(Instruction, 2 ));
                        cout << BlueText << "div Result:"<< VaribleMemory[i].IValue << "\n";
                    }
                }
            }
        
            if (SplitValue(Instruction, 0 ) == "set"){
                for (int i = 0 ; i <= VaribleCounter; i++){
                    if (VaribleMemory[i].Name == SplitValue(Instruction, 1 )){

                        string VaribleData = SplitValue(Instruction, 2 );

                        int VaribleType = 0;

                        cout << RedText << "set: " << VaribleData << " ";

                        if (ReadValue(VaribleData , 0 , 0) == "'"){
                            cout << "String Type\n";
                            VaribleType = 1;
                        }
                        else {
                            cout << "Int Type\n";
                            VaribleType = 0;

                        }
                        
                        if (VaribleType == 1){
                            string StoredData = "";
                            for (int i = 0 ; i <= VaribleData.size() ; i ++){
                                if (ReadValue(VaribleData , i , i) != "'"){
                                    StoredData += ReadValue(VaribleData , i , i);
                                }
                            }
                            cout << "Parsed String: " << StoredData << "\n"; 
                            VaribleMemory[i].Value = StoredData;
                        }
                        else {
                            VaribleMemory[i].IValue = StringToInt(VaribleData);
                        }
                    }
                }
            }

            if (SplitValue(Instruction, 0 ) == "setv"){   

                int InValue = 0;

                string InStringValue = "";
            

                for (int i = 0 ; i <= VaribleCounter; i++){
                    if (VaribleMemory[i].Name == SplitValue(Instruction, 2 )){
                        InValue = VaribleMemory[i].IValue;
                        InStringValue = VaribleMemory[i].Value;
                    }
                }
            

                for (int i = 0 ; i <= VaribleCounter; i++){
                    if (VaribleMemory[i].Name == SplitValue(Instruction, 1 )){
                        VaribleMemory[i].IValue = InValue;   
                        VaribleMemory[i].Value = InStringValue;   

                        cout << RedText << "setv: " << InValue << " \n" ;
                    }
                }
            }
            
            if (SplitValue(Instruction, 0 ) == "end"){   
                exit(0);
            }

            if (SplitValue(Instruction, 0 ) == "settextsize"){   
                ParasiteScriptCoreData.TextSize = StringToInt(SplitValue(Instruction, 1 ));
            }

        
            if (SplitValue(Instruction, 0 ) == "cmpvv"){   
                ParasiteScriptCoreData.CompareFlag = true;

                int V1 = false;
                int V2 = false;
                string V1Value;
                string V2Value; 

                int V1IValue = 0;
                int V2IValue = 0; 

                for (int i = 0 ; i <= VaribleCounter; i++){
                    if (VaribleMemory[i].Name == SplitValue(Instruction, 1 )){
                        V1 = true;
                        if (VaribleMemory[i].IValue != 0){
                            V1IValue = VaribleMemory[i].IValue;
                        }
                        else {
                            V1Value = VaribleMemory[i].Value;
                        }
                    }
                    if (VaribleMemory[i].Name == SplitValue(Instruction, 2 )){
                        V2 = true;
                        if (VaribleMemory[i].IValue != 0){
                            V2IValue = VaribleMemory[i].IValue;
                        }
                        else {
                            V2Value = VaribleMemory[i].Value;
                        }
                    }
                }
                if (V1 && V2){
                    if (V2IValue == 0 && V1IValue == 0){
                        if (V1Value == V2Value){
                            ParasiteScriptCoreData.EqualFlag = true;
                        }
                        else {
                            ParasiteScriptCoreData.NotEqualFlag = true;
                        }
                    }
                    else {
                        if (V1IValue == V2IValue){
                            ParasiteScriptCoreData.EqualFlag = true;
                        }
                        if (V1IValue != V2IValue){
                            ParasiteScriptCoreData.NotEqualFlag = true;
                        }
                        if (V1IValue >= V2IValue){
                            ParasiteScriptCoreData.GreaterFlag = true;
                        }
                        if (V1IValue <= V2IValue){
                            ParasiteScriptCoreData.LesserFlag = true;
                        }
                    }
                }
            }

            if (SplitValue(Instruction, 0 ) == "cmpvi"){   
                ParasiteScriptCoreData.CompareFlag = true;

                int V1 = false;
                int V2 = true;

                int V1IValue = 0;
                int V2IValue = StringToInt(SplitValue(Instruction, 2 )); 

                for (int i = 0 ; i <= VaribleCounter; i++){
                    if (VaribleMemory[i].Name == SplitValue(Instruction, 1 )){
                        V1 = true;
                        V1IValue = VaribleMemory[i].IValue;
                    }
                }
                if (V1 && V2){
                    if (V1IValue == V2IValue){
                        ParasiteScriptCoreData.EqualFlag = true;
                    }
                    if (V1IValue != V2IValue){
                        ParasiteScriptCoreData.NotEqualFlag = true;
                    }
                    if (V1IValue >= V2IValue){
                        ParasiteScriptCoreData.GreaterFlag = true;
                    }
                    if (V1IValue <= V2IValue){
                        ParasiteScriptCoreData.LesserFlag = true;
                    }
                }
            }


            if ( SplitValue(Instruction, 0 ) == "jifne"){  
                if(ParasiteScriptCoreData.NotEqualFlag){
                    for (int i = 0 ; i <= JumpPointCounter ; i ++){
                        if (JumpPoints[i].Name == ReadValue(Instruction, 6 , 9)){
                            ParasiteScriptCoreData.ReturnLine = ParasiteScriptCoreData.LineCounter + 2;
                            ParasiteScriptCoreData.LineCounter = JumpPoints[i].LineNumber;
                            ParasiteScriptCoreData.NotEqualFlag = false;
                        }
                    }
                }
            }

            if (SplitValue(Instruction, 0 ) == "jife"){  
                if(ParasiteScriptCoreData.EqualFlag){
                    for (int i = 0 ; i <= JumpPointCounter ; i ++){
                        if (JumpPoints[i].Name == ReadValue(Instruction, 5 , 8)){
                            ParasiteScriptCoreData.ReturnLine = ParasiteScriptCoreData.LineCounter + 2;
                            ParasiteScriptCoreData.LineCounter = JumpPoints[i].LineNumber;
                            ParasiteScriptCoreData.EqualFlag = false;
                        }
                    }
                }
            }

            if (SplitValue(Instruction, 0 ) == "jifg"){  
                if(ParasiteScriptCoreData.GreaterFlag){
                    for (int i = 0 ; i <= JumpPointCounter ; i ++){
                        if (JumpPoints[i].Name == ReadValue(Instruction, 5 , 8)){
                            ParasiteScriptCoreData.ReturnLine = ParasiteScriptCoreData.LineCounter + 2;
                            ParasiteScriptCoreData.LineCounter = JumpPoints[i].LineNumber;
                            ParasiteScriptCoreData.LesserFlag = false;
                        }
                    }
                }
            }

            if (SplitValue(Instruction, 0 ) == "jifl"){  
                if(ParasiteScriptCoreData.LesserFlag){
                    for (int i = 0 ; i <= JumpPointCounter ; i ++){
                        if (JumpPoints[i].Name == ReadValue(Instruction, 5 , 8)){
                            ParasiteScriptCoreData.ReturnLine = ParasiteScriptCoreData.LineCounter + 2;
                            ParasiteScriptCoreData.LineCounter = JumpPoints[i].LineNumber;
                            ParasiteScriptCoreData.LesserFlag = false;
                        }
                    }
                }
            }

            if (SplitValue(Instruction, 0 ) == "wipe"){  
                ParasiteScriptCoreData.LesserFlag = false;
                ParasiteScriptCoreData.GreaterFlag = false;
                ParasiteScriptCoreData.EqualFlag = false;
                ParasiteScriptCoreData.NotEqualFlag = false;
            }

            if (SplitValue(Instruction, 0 ) == "ret"){
                cout << GreenText << "ret: Line " <<  ParasiteScriptCoreData.ReturnLine << "\n";
                ParasiteScriptCoreData.LineCounter = ParasiteScriptCoreData.ReturnLine;
            }


            if (SplitValue(Instruction, 0 ) == "pullinp"){

                int InpValue = 0;

                if (IsKeyDown(KEY_LEFT)){
                    InpValue = 4;
                }
                if (IsKeyDown(KEY_RIGHT)){
                    InpValue = 2;
                }
                if (IsKeyDown(KEY_UP)){
                    InpValue = 1;
                }
                if (IsKeyDown(KEY_DOWN)){
                    InpValue = 3;
                }    
                if (IsKeyDown(KEY_SPACE)){
                    InpValue = 5;
                }
                if (IsKeyDown(KEY_A)){
                    InpValue = 6;
                }
                if (IsKeyDown(KEY_S)){
                    InpValue = 7;
                }
                
                for (int i = 0 ; i <= VaribleCounter; i++){
                    if (VaribleMemory[i].Name == SplitValue(Instruction, 1 )){
                        VaribleMemory[i].IValue = InpValue;
                    }
                }
            }

            if (SplitValue(Instruction, 0 ) == "drawspr"){   
                int X = 0;
                int Y = 0;
                int Scale = 1;
                int Size = 16;

                for (int i = 0 ; i <= VaribleCounter; i++){
                    if (VaribleMemory[i].Name == SplitValue(Instruction, 2 )){
                        X = VaribleMemory[i].IValue;
                    }
                    if (VaribleMemory[i].Name == SplitValue(Instruction, 3 )){
                        Y = VaribleMemory[i].IValue;
                    }
                    if (VaribleMemory[i].Name == SplitValue(Instruction, 4 )){
                        Scale = VaribleMemory[i].IValue;
                    }
                    if (VaribleMemory[i].Name == SplitValue(Instruction, 5 )){
                        Size = VaribleMemory[i].IValue;

                    }
                }

                for (int i = 0 ; i <= VaribleCounter; i++){
                    if (VaribleMemory[i].Name == SplitValue(Instruction, 1 )){
                        for (int x = 0 ; x <= Size - 1 ; x ++){
                            for (int y = 0 ; y <= Size - 1 ; y ++){
                                switch(VaribleMemory[i].Value[y * Size + x]){
                                    case L'0':
                                        DrawRectangle((x * Scale) + X, (y * Scale) + Y , Scale , Scale, PDBlue);
                                        break;
                                    case L'1':
                                        DrawRectangle((x * Scale) + X, (y * Scale) + Y , Scale , Scale, PLBlue);
                                        break;
                                    case L'2':
                                        DrawRectangle((x * Scale) + X, (y * Scale) + Y , Scale , Scale, PDRed);
                                        break;
                                    case L'3':
                                        DrawRectangle((x * Scale) + X, (y * Scale) + Y , Scale , Scale, PLRed);
                                        break;
                                    case L'4':
                                        DrawRectangle((x * Scale) + X, (y * Scale) + Y , Scale , Scale, PDYellow);
                                        break;
                                    case L'5':
                                        DrawRectangle((x * Scale) + X, (y * Scale) + Y , Scale , Scale, PLYellow);
                                        break;
                                    case L'6':
                                        DrawRectangle((x * Scale) + X, (y * Scale) + Y , Scale , Scale, PDPurple);
                                        break;
                                    case L'7':
                                        DrawRectangle((x * Scale) + X, (y * Scale) + Y , Scale , Scale, PLPurple);
                                        break;
                                    case L'8':
                                        DrawRectangle((x * Scale) + X, (y * Scale) + Y , Scale , Scale, PDGreen);
                                        break;
                                    case L'9':
                                        DrawRectangle((x * Scale) + X, (y * Scale) + Y , Scale , Scale, PLGreen);
                                        break;
                                }
                            }
                        }
                    }
                }
            }
        }

    if (BenchMode){
        CycleCounter ++;
    }
}

static int InstructionsPerTick = 2;


auto ParasiteScriptInterperate(){ // Quick Interperater
    #if (defined(SingleCore))
    for (int i = 0 ; i <= ParasiteScriptCoreData.ProgramSize ; i ++){
        if (ParasiteScriptCoreData.LineCounter != ParasiteScriptCoreData.ProgramSize){

            CycleInstruction(&ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter]);
            ParasiteScriptCoreData.LineCounter ++;

            if (TickFlag){
                TickFlag = false;
                i = ParasiteScriptCoreData.ProgramSize;
            }

        }
    }
    #endif
    #if (defined(MultiCore))
    if (ParasiteScriptCoreData.LineCounter != ParasiteScriptCoreData.ProgramSize){
        
        for (int i = 0; i <= InstructionsPerTick; i++){
            pthread_t ChildThread;
            pthread_create( &ChildThread, NULL, &CycleInstruction, &ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter + i]);
        }
        
        ParasiteScriptCoreData.LineCounter += InstructionsPerTick;

        if (TickFlag){
            TickFlag = false;
        }
    }
    #endif

}
