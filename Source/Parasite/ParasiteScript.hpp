#include "ParasiteScriptData.hpp"


// Parasite Script v.1.0

// Based of Parasites MSScript 

#define RedText "\033[4;31m"
#define GreenText "\033[1;32m"
#define BlueText "\033[1;34m"
#define WhiteText "\033[1;37m"

static bool Debug = false;


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
    ParasiteScriptCoreData.ContinueFlag = true;
    ParasiteScriptCoreData.ErrorFlag = false;

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

auto ScanVaribleMemory(string VaribleName){
    bool Found = false;
    for (int x = 0 ; x <= VaribleCounter; x++){
        if (VaribleMemory[x].Name == VaribleName){
            Found = true;
        }
    }
    return Found;
}

auto PullIntFromMemory(string VaribleName){
    bool Found = false;
    for (int x = 0 ; x <= VaribleCounter; x++){
        if (VaribleMemory[x].Name == VaribleName){
            Found = true;
            return VaribleMemory[x].IValue;
        }
    }
    if (!Found){
        cout << "Error Varible Not Declared: " << VaribleName << "\n";
        ParasiteScriptCoreData.ErrorFlag = true;
    }
}
auto PullStrFromMemory(string VaribleName){
    for (int x = 0 ; x <= VaribleCounter; x++){
        if (VaribleMemory[x].Name == VaribleName){
            return VaribleMemory[x].Value;
        }
    }
}
auto StoreIntToMemory(string VaribleName, int Value){
    if (ScanVaribleMemory(VaribleName)){
        for (int x = 0 ; x <= VaribleCounter; x++){
            if (VaribleMemory[x].Name == VaribleName){
                VaribleMemory[x].IValue = Value;
            }
        }
    }
}

auto StoreStrtoMemory(string VaribleName, string Value){
    for (int x = 0 ; x <= VaribleCounter; x++){
        if (VaribleMemory[x].Name == VaribleName){
            VaribleMemory[x].Value = Value;
        }
    }
}

string RemoveSpaces(string Data)
{
    string OutData = "";

    for (int i = 0 ; i <= Data.size() ; i ++){
        if (Data[i] != ' '){
            OutData[i] = Data[i];
        }
    }

    return OutData;
}

int ScanSpaces(string Data){
    int Spaces = 0;

    for (int i = 0 ; i <= Data.size() ; i ++){
        if (Data[i] != ' '){
            Spaces ++;
        }
    }

    return Spaces;
}

void LoadScript(const char *ScriptPath){ // Loads Script
    istringstream ProgramData(ParasiteScriptLoadFile(ScriptPath));
    string CurrentLine;

    while (getline(ProgramData, CurrentLine)) {
        if (!CurrentLine.empty()){
            if (ReadValue(CurrentLine, 0 , 0) == ":"){            
                JumpPoints[JumpPointCounter].Name = ReadValue(CurrentLine, 1 , CurrentLine.size() - 1);
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

    } 
    ParasiteScriptCoreData.ProgramSize = ParasiteScriptCoreData.LineCounter;

    ParasiteScriptCoreData.LineCounter = 0;

    //exit(0);
} 

bool IsNumber(const string& s)
{
    for (char const &ch : s) {
        if (isdigit(ch) == 0) 
            return false;
    }
    return true;
 }


static int InstructionsPerTick = 32;
static int TimeDelay = 0;

auto CycleInstruction(){
    if (TimeDelay == 0){
        if (ParasiteScriptCoreData.LineCounter != ParasiteScriptCoreData.ProgramSize){

            bool FoundInstruction = false;
            
            string Instruction = ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter];

            if (ParasiteScriptCoreData.ErrorFlag){
                cout << "Error Command: -->" << ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter - 1] << "<--\n";
                //exit(0);
            }

            if (SplitValue(Instruction, 0 ) == "end"){
                FoundInstruction = true;
                ParasiteScriptCoreData.ContinueFlag = true;
            }

            if (ParasiteScriptCoreData.ContinueFlag && SplitValue(Instruction, 0) != "//"){
                for (int i = 0 ; i <= ScanSpaces(Instruction); i ++){
                    if (SplitValue(Instruction, i) == "+"){
                        string Part1 = "";
                        string Part2 = "";
                        bool Found = false;
                        int SpaceCounter = 0 ;
                        if (!IsNumber(SplitValue(Instruction, i-1))){
                            if (IsNumber(SplitValue(Instruction, i+1))){
                                int Value = StringToInt(SplitValue(Instruction, i+1));
                                int Value1 = PullIntFromMemory(SplitValue(Instruction, i-1));
                                StoreIntToMemory(SplitValue(Instruction, i-1) , Value1 + Value);
                            }
                            else{
                                int Value = PullIntFromMemory(SplitValue(Instruction, i+1));
                                StoreIntToMemory(SplitValue(Instruction, i-1) , PullIntFromMemory(SplitValue(Instruction, i-1)) + Value);
                            }

                            for (int i = 0 ; i <= Instruction.size(); i++){
                                if (Instruction[i] == '+'){
                                    Part1 = ReadValue(Instruction , 0 , i - 1);
                                    Found = true;
                                }
                                if (Found){
                                    if (Instruction[i] == ' '){
                                        SpaceCounter ++;
                                        if (SpaceCounter == 2){
                                            Part2 = ReadValue(Instruction , i + 1, Instruction.size() - 1);
                                            Part2 += " ";
                                        }
                                    }
                                }
                            }
                        }
                        else {
                            int Value = StringToInt(SplitValue(Instruction, i-1)) + StringToInt(SplitValue(Instruction, i+1));

                            for (int i = 0 ; i <= Instruction.size(); i++){
                                if (Instruction[i] == '+'){
                                    Part1 = ReadValue(Instruction , 0 , i - 3);
                                    stringstream ss;
                                    ss << Value;
                                    Part1 += ss.str();
                                    Part1 += " ";
                                    Found = true;
                                }
                                if (Found){
                                    if (Instruction[i] == ' '){
                                        SpaceCounter ++;
                                        if (SpaceCounter == 2){
                                            Part2 = ReadValue(Instruction , i + 1, Instruction.size());
                                            Part2 += " ";
                                        }
                                    }
                                }
                            }
                        }

                    
                        Instruction = '\0';
                        Instruction = Part1 + Part2;
                        ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] = Instruction;
                         
                    }
                    if (SplitValue(Instruction, i) == "-"){
                        string Part1 = "";
                        string Part2 = "";
                        bool Found = false;
                        int SpaceCounter = 0 ;
                        if (!IsNumber(SplitValue(Instruction, i-1))){
                            if (IsNumber(SplitValue(Instruction, i+1))){
                                int Value = StringToInt(SplitValue(Instruction, i+1));
                                int Value1 = PullIntFromMemory(SplitValue(Instruction, i-1));
                                StoreIntToMemory(SplitValue(Instruction, i-1) , Value1 - Value);
                            }
                            else{
                                int Value = PullIntFromMemory(SplitValue(Instruction, i+1));
                                StoreIntToMemory(SplitValue(Instruction, i-1) , PullIntFromMemory(SplitValue(Instruction, i-1)) - Value);
                            }

                            for (int i = 0 ; i <= Instruction.size(); i++){
                                if (Instruction[i] == '-'){
                                    Part1 = ReadValue(Instruction , 0 , i - 1);
                                    Found = true;
                                }
                                if (Found){
                                    if (Instruction[i] == ' '){
                                        SpaceCounter ++;
                                        if (SpaceCounter == 2){
                                            Part2 = ReadValue(Instruction , i + 1, Instruction.size() - 1);
                                            Part2 += " ";
                                        }
                                    }
                                }
                            }
                        }
                        else {
                            int Value = StringToInt(SplitValue(Instruction, i-1)) - StringToInt(SplitValue(Instruction, i+1));

                            for (int i = 0 ; i <= Instruction.size(); i++){
                                if (Instruction[i] == '-'){
                                    Part1 = ReadValue(Instruction , 0 , i - 3);
                                    stringstream ss;
                                    ss << Value;
                                    Part1 += ss.str();
                                    Part1 += " ";
                                    Found = true;
                                }
                                if (Found){
                                    if (Instruction[i] == ' '){
                                        SpaceCounter ++;
                                        if (SpaceCounter == 2){
                                            Part2 = ReadValue(Instruction , i + 1, Instruction.size());
                                            Part2 += " ";
                                        }
                                    }
                                }
                            }
                        }

                    
                        Instruction = '\0';
                        Instruction = Part1 + Part2;
                        ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] = Instruction;
                    }

                    if (SplitValue(Instruction, i) == "*"){
                        string Part1 = "";
                        string Part2 = "";
                        bool Found = false;
                        int SpaceCounter = 0 ;
                        if (!IsNumber(SplitValue(Instruction, i-1))){
                            if (IsNumber(SplitValue(Instruction, i+1))){
                                int Value = StringToInt(SplitValue(Instruction, i+1));
                                int Value1 = PullIntFromMemory(SplitValue(Instruction, i-1));
                                StoreIntToMemory(SplitValue(Instruction, i-1) , Value1 * Value);
                            }
                            else{
                                int Value = PullIntFromMemory(SplitValue(Instruction, i+1));
                                StoreIntToMemory(SplitValue(Instruction, i-1) , PullIntFromMemory(SplitValue(Instruction, i-1)) * Value);
                            }

                            for (int i = 0 ; i <= Instruction.size(); i++){
                                if (Instruction[i] == '*'){
                                    Part1 = ReadValue(Instruction , 0 , i - 1);
                                    Found = true;
                                }
                                if (Found){
                                    if (Instruction[i] == ' '){
                                        SpaceCounter ++;
                                        if (SpaceCounter == 2){
                                            Part2 = ReadValue(Instruction , i + 1, Instruction.size() - 1);
                                            Part2 += " ";
                                        }
                                    }
                                }
                            }
                        }
                        else {
                            int Value = StringToInt(SplitValue(Instruction, i-1)) * StringToInt(SplitValue(Instruction, i+1));

                            for (int i = 0 ; i <= Instruction.size(); i++){
                                if (Instruction[i] == '*'){
                                    Part1 = ReadValue(Instruction , 0 , i - 3);
                                    stringstream ss;
                                    ss << Value;
                                    Part1 += ss.str();
                                    Part1 += " ";
                                    cout << Part1 << "\n";
                                    Found = true;
                                }
                                if (Found){
                                    if (Instruction[i] == ' '){
                                        SpaceCounter ++;
                                        if (SpaceCounter == 2){
                                            Part2 = ReadValue(Instruction , i + 1, Instruction.size());
                                            Part2 += " ";
                                        }
                                    }
                                }
                            }
                        }

                    
                        Instruction = '\0';
                        Instruction = Part1 + Part2;
                        ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] = Instruction;
                         
                    }

                    if (SplitValue(Instruction, i) == "/"){
                        string Part1 = "";
                        string Part2 = "";
                        bool Found = false;
                        int SpaceCounter = 0 ;
                        if (!IsNumber(SplitValue(Instruction, i-1))){
                            if (IsNumber(SplitValue(Instruction, i+1))){
                                int Value = StringToInt(SplitValue(Instruction, i+1));
                                int Value1 = PullIntFromMemory(SplitValue(Instruction, i-1));
                                StoreIntToMemory(SplitValue(Instruction, i-1) , Value1 / Value);
                            }
                            else{
                                int Value = PullIntFromMemory(SplitValue(Instruction, i+1));
                                StoreIntToMemory(SplitValue(Instruction, i-1) , PullIntFromMemory(SplitValue(Instruction, i-1)) / Value);
                            }

                            for (int i = 0 ; i <= Instruction.size(); i++){
                                if (Instruction[i] == '/'){
                                    Part1 = ReadValue(Instruction , 0 , i - 1);
                                    Found = true;
                                }
                                if (Found){
                                    if (Instruction[i] == ' '){
                                        SpaceCounter ++;
                                        if (SpaceCounter == 2){
                                            Part2 = ReadValue(Instruction , i + 1, Instruction.size() - 1);
                                            Part2 += " ";
                                        }
                                    }
                                }
                            }
                        }
                        else {
                            int Value = StringToInt(SplitValue(Instruction, i-1)) / StringToInt(SplitValue(Instruction, i+1));

                            for (int i = 0 ; i <= Instruction.size(); i++){
                                if (Instruction[i] == '/'){
                                    Part1 = ReadValue(Instruction , 0 , i - 3);
                                    stringstream ss;
                                    ss << Value;
                                    Part1 += ss.str();
                                    Part1 += " ";
                                    cout << Part1 << "\n";
                                    Found = true;
                                }
                                if (Found){
                                    if (Instruction[i] == ' '){
                                        SpaceCounter ++;
                                        if (SpaceCounter == 2){
                                            Part2 = ReadValue(Instruction , i + 1, Instruction.size());
                                            Part2 += " ";
                                        }
                                    }
                                }
                            }
                        }

                    
                        Instruction = '\0';
                        Instruction = Part1 + Part2;
                        ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] = Instruction;
                         
                    }
                }

                if (SplitValue(Instruction, 1) == "="){
                    FoundInstruction = true;
                    if (IsNumber(SplitValue(Instruction, 2))){
                        StoreIntToMemory(SplitValue(Instruction, 0) , StringToInt(SplitValue(Instruction, 2)));
                        if (Debug)cout << "set: " << StringToInt(SplitValue(Instruction, 2)) << "\n";
                    }
                    else {
                        int Value = PullIntFromMemory(SplitValue(Instruction, 2));
                        StoreIntToMemory(SplitValue(Instruction, 0) , Value);
                        if (Debug)cout << "set: " << Value << "\n";
                    }
                }

                if (SplitValue(Instruction, 1) == "+="){
                    FoundInstruction = true;
                    if (IsNumber(SplitValue(Instruction, 2))){
                        int Value = StringToInt(SplitValue(Instruction, 2));
                        StoreIntToMemory(SplitValue(Instruction, 0) , PullIntFromMemory(SplitValue(Instruction, 0)) + Value);

                        if (Debug)cout << "add: " << PullIntFromMemory(SplitValue(Instruction, 0))+ Value << "\n";
                    }
                    else{
                        int Value = PullIntFromMemory(SplitValue(Instruction, 2));
                        StoreIntToMemory(SplitValue(Instruction, 0) , PullIntFromMemory(SplitValue(Instruction, 0)) + Value);
                        if (Debug)cout << "add: " << PullIntFromMemory(SplitValue(Instruction, 0))+ Value << "\n";
                    }
                }

                if (SplitValue(Instruction, 1) == "-="){
                    FoundInstruction = true;
                    if (IsNumber(SplitValue(Instruction, 2))){
                        int Value = StringToInt(SplitValue(Instruction, 2));
                        StoreIntToMemory(SplitValue(Instruction, 0) , PullIntFromMemory(SplitValue(Instruction, 0)) - Value);
                        if (Debug)cout << "sub: " << PullIntFromMemory(SplitValue(Instruction, 0)) - Value << "\n";
                    }
                    else{
                        int Value = PullIntFromMemory(SplitValue(Instruction, 2));
                        StoreIntToMemory(SplitValue(Instruction, 0) , PullIntFromMemory(SplitValue(Instruction, 0)) - Value);
                        if (Debug)cout << "sub: " << PullIntFromMemory(SplitValue(Instruction, 0)) - Value << "\n";
                    }
                }

                if (SplitValue(Instruction, 1) == "*="){
                    FoundInstruction = true;
                    if (IsNumber(SplitValue(Instruction, 2))){
                        int Value = StringToInt(SplitValue(Instruction, 2));
                        StoreIntToMemory(SplitValue(Instruction, 0) , PullIntFromMemory(SplitValue(Instruction, 0)) * Value);
                        if (Debug)cout << "mul: " << PullIntFromMemory(SplitValue(Instruction, 0)) * Value << "\n";
                    }
                    else{
                        int Value = PullIntFromMemory(SplitValue(Instruction, 2));
                        StoreIntToMemory(SplitValue(Instruction, 0) , PullIntFromMemory(SplitValue(Instruction, 0)) * Value);
                        if (Debug)cout << "mul: " << PullIntFromMemory(SplitValue(Instruction, 0)) * Value << "\n";
                    }
                }

                if (SplitValue(Instruction, 1) == "/="){
                    FoundInstruction = true;
                    if (IsNumber(SplitValue(Instruction, 2))){
                        int Value = StringToInt(SplitValue(Instruction, 2));
                        StoreIntToMemory(SplitValue(Instruction, 0) , PullIntFromMemory(SplitValue(Instruction, 0)) / Value);
                        if (Debug)cout << "div: " << PullIntFromMemory(SplitValue(Instruction, 0)) / Value << "\n";
                    }
                    else{
                        int Value = PullIntFromMemory(SplitValue(Instruction, 2));
                        StoreIntToMemory(SplitValue(Instruction, 0) , PullIntFromMemory(SplitValue(Instruction, 0)) / Value);
                        if (Debug)cout << "div: " << PullIntFromMemory(SplitValue(Instruction, 0)) / Value << "\n";
                    }
                }

                if (SplitValue(Instruction, 0 ) == "if"){
                    FoundInstruction = true;

                    ParasiteScriptCoreData.ContinueFlag = true;
                    ParasiteScriptCoreData.ElseFlag = false;

                    string Operator = SplitValue(Instruction, 2 );
                    int Value1 = 0;
                    int Value2 = 0;

                    if (IsNumber(SplitValue(Instruction, 1))){
                        Value1 = StringToInt(SplitValue(Instruction, 1 ));
                    }
                    else {
                        Value1 = PullIntFromMemory(SplitValue(Instruction, 1 ));
                    }

                    if (IsNumber(SplitValue(Instruction, 3))){
                        Value2 = StringToInt(SplitValue(Instruction, 3 ));
                    }
                    else {
                        Value2 = PullIntFromMemory(SplitValue(Instruction, 3 ));
                    }

                    if (Operator == "=="){
                        if (Value1 == Value2){
                            ParasiteScriptCoreData.ContinueFlag = true;
                        }
                        else {
                            ParasiteScriptCoreData.ContinueFlag = false;
                            ParasiteScriptCoreData.ElseFlag = true;
                        }
                    }

                    if (Operator == ">"){
                        if (Value1 > Value2){
                            ParasiteScriptCoreData.ContinueFlag = true;
                        }
                        else {
                            ParasiteScriptCoreData.ContinueFlag = false;
                            ParasiteScriptCoreData.ElseFlag = true;
                        }
                    }

                    if (Operator == "<"){
                        if (Value1 < Value2){
                            ParasiteScriptCoreData.ContinueFlag = true;
                        }
                        else {
                            ParasiteScriptCoreData.ContinueFlag = false;
                            ParasiteScriptCoreData.ElseFlag = true;
                        }
                    }

                    if (Operator == ">="){
                        if (Value1 >= Value2){
                            ParasiteScriptCoreData.ContinueFlag = true;
                        }
                        else {
                            ParasiteScriptCoreData.ContinueFlag = false;
                            ParasiteScriptCoreData.ElseFlag = true;
                        }
                    }

                    if (Operator == "<="){
                        if (Value1 >= Value2){
                            ParasiteScriptCoreData.ContinueFlag = true;
                        }
                        else {
                            ParasiteScriptCoreData.ContinueFlag = false;
                            ParasiteScriptCoreData.ElseFlag = true;
                        }
                    }

                    if (Operator == "!="){
                        if (Value1 != Value2){
                            ParasiteScriptCoreData.ContinueFlag = true;
                        }
                        else {
                            ParasiteScriptCoreData.ContinueFlag = false;
                            ParasiteScriptCoreData.ElseFlag = true;
                        }
                    }
                }

                if (SplitValue(Instruction, 0 ) == "else"){
                    FoundInstruction = true;
                    if (!ParasiteScriptCoreData.ElseFlag){
                        ParasiteScriptCoreData.ContinueFlag = false;
                    }
                }

                if (SplitValue(Instruction, 0 ) == "stop"){
                    FoundInstruction = true;
                    exit(0);
                }
                if (SplitValue(Instruction, 0 ) == "clear"){
                    FoundInstruction = true;
                    BeginDrawing();
                    ClearBackground(BLACK);
                }
                if (SplitValue(Instruction, 0 ) == "vrefresh"){
                    FoundInstruction = true;
                    EndDrawing();
                }

                if (SplitValue(Instruction, 0 ) == "delay"){
                    FoundInstruction = true;
                    TimeDelay = StringToInt(SplitValue(Instruction, 1 ));
                }

                if (SplitValue(Instruction, 0 ) == "pspeed"){
                    FoundInstruction = true;
                    if (IsNumber(SplitValue(Instruction, 1 ))){
                        InstructionsPerTick = StringToInt(SplitValue(Instruction, 1 ));
                    }
                    else {
                        InstructionsPerTick = PullIntFromMemory(SplitValue(Instruction, 1 ));
                    }
                }

                if (SplitValue(Instruction, 0 ) == "arr"){
                    FoundInstruction = true;
                    ArrayMemory[ArrayCounter].Name = SplitValue(Instruction, 1 );
                    if (Debug)cout << "Initializing New Array\n";
                    for (int i = 0 ; i <= MaxArraySize; i ++){
                        ArrayMemory[ArrayCounter].Array[i] = StringToInt(SplitValue(Instruction, 2 ));
                    }
                    ArrayCounter ++;
                }

                if (SplitValue(Instruction, 0 ) == "arrwipe"){
                    FoundInstruction = true;

                    for (int i = 0 ; i <= ArrayCounter; i++){
                        if (ArrayMemory[i].Name == SplitValue(Instruction, 1 )){
                            if (Debug)cout << "Initializing Array\n";
                            for (int x = 0 ; x <= MaxArraySize; x ++){
                                ArrayMemory[i].Array[x] = StringToInt(SplitValue(Instruction, 2 ));
                            }
                        }
                        
                    }
                }

                if (SplitValue(Instruction, 0 ) == "arrload"){ // arrload TestArray 1 Varible
                    FoundInstruction = true;
                    for (int i = 0 ; i <= ArrayCounter; i++){
                        if (ArrayMemory[i].Name == SplitValue(Instruction, 1 )){

                            int IndexValue = 0;

                            if (IsNumber(SplitValue(Instruction, 2 ))){
                                IndexValue = StringToInt(SplitValue(Instruction, 2 ));
                            }
                            else {
                                for (int x = 0 ; x <= VaribleCounter; x++){
                                    if (VaribleMemory[x].Name == SplitValue(Instruction, 2 )){
                                        IndexValue = VaribleMemory[x].IValue;
                                    }
                                }
                            }

                            for (int x = 0 ; x <= VaribleCounter; x++){
                                if (VaribleMemory[x].Name == SplitValue(Instruction, 3 )){
                                    if (IndexValue <= MaxArraySize){
                                        VaribleMemory[x].IValue = ArrayMemory[i].Array[IndexValue];
                                        if (Debug)cout << "Loaded " << VaribleMemory[x].IValue  << " Into " << VaribleMemory[x].Name << " From " << ArrayMemory[i].Name << " Index " << IndexValue << "\n";
                                    }
                                }
                            }
                        }
                    }
                }

                if (SplitValue(Instruction, 0 ) == "arrset"){ // arrset TestArray 1 Varible
                    FoundInstruction = true;
                    for (int i = 0 ; i <= ArrayCounter; i++){
                        if (ArrayMemory[i].Name == SplitValue(Instruction, 1 )){

                            int IndexValue = 0;

                            if (IsNumber(SplitValue(Instruction, 2 ))){
                                IndexValue = StringToInt(SplitValue(Instruction, 2 ));
                            }
                            else {
                                for (int x = 0 ; x <= VaribleCounter; x++){
                                    if (VaribleMemory[x].Name == SplitValue(Instruction, 2 )){
                                        IndexValue = VaribleMemory[x].IValue;
                                    }
                                }
                            }

                            if (!IsNumber(SplitValue(Instruction, 3 ))){
                                for (int x = 0 ; x <= VaribleCounter; x++){
                                    if (VaribleMemory[x].Name == SplitValue(Instruction, 3 )){
                                        if (IndexValue <= MaxArraySize){
                                            ArrayMemory[i].Array[IndexValue] = VaribleMemory[x].IValue ;
                                        }
                                    }
                                }
                            }
                            else {
                                if (IndexValue <= MaxArraySize){
                                    ArrayMemory[i].Array[IndexValue] = StringToInt(SplitValue(Instruction, 3 ));
                                }
                            }
                            if (Debug)cout << "Array Set\n";
                        }
                    }
                }

                if (SplitValue(Instruction, 0 ) == "var" || SplitValue(Instruction, 0 ) == "spr"){
                    FoundInstruction = true;
                    VaribleMemory[VaribleCounter].Name = SplitValue(Instruction, 1 );

                    string VaribleData = SplitValue(Instruction, 2 );
                    int VaribleType = 0;

                    if (Debug)cout << RedText << "VD: " << VaribleData << " ";

                    if (ReadValue(VaribleData , 0 , 0) == "'"){
                        if (Debug)cout << "String Type\n";
                        VaribleType = 1;
                    }
                    else {
                        if (Debug)cout << "Int Type\n";
                        VaribleType = 0;

                    }
                    
                    if (VaribleType == 1){
                        string StoredData = "";
                        for (int i = 0 ; i <= VaribleData.size() ; i ++){
                            if (ReadValue(VaribleData , i , i) != "'"){
                                StoredData += ReadValue(VaribleData , i , i);
                            }
                        }
                        if (Debug)cout << "Parsed String: " << StoredData << "\n"; 
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
                    FoundInstruction = true;
                    for (int i = 0 ; i <= JumpPointCounter ; i ++){
                        if (JumpPoints[i].Name == SplitValue(Instruction, 1)){
                            ParasiteScriptCoreData.ReturnLine = ParasiteScriptCoreData.LineCounter;
                            ParasiteScriptCoreData.LineCounter = JumpPoints[i].LineNumber;
                        }
                    }
                }
                else {
                    if (SplitValue(Instruction, 0 ) == "jump"){   
                        FoundInstruction = true;
                        ParasiteScriptCoreData.LineCounter = StringToInt(SplitValue(Instruction, 1 )) - 2;
                    }
                }

                if (SplitValue(Instruction, 0 ) == "add"){   
                    FoundInstruction = true;
                    int Value1 = PullIntFromMemory(SplitValue(Instruction, 1));
                    int Value2 = 0;

                    if (IsNumber(SplitValue(Instruction, 2))){
                        Value2 = StringToInt(SplitValue(Instruction, 2));
                    }
                    else {
                        Value2 = PullIntFromMemory(SplitValue(Instruction, 2));
                    }

                    StoreIntToMemory(SplitValue(Instruction, 1 ) , (Value1 + Value2));

                    if (Debug)cout << BlueText << "add Result:"<< PullIntFromMemory(SplitValue(Instruction, 1)) << "\n";
                }

                if (SplitValue(Instruction, 0 ) == "sub"){   
                    FoundInstruction = true;
                    int Value1 = PullIntFromMemory(SplitValue(Instruction, 1));
                    int Value2 = 0;

                    if (IsNumber(SplitValue(Instruction, 2))){
                        Value2 = StringToInt(SplitValue(Instruction, 2));
                    }
                    else {
                        Value2 = PullIntFromMemory(SplitValue(Instruction, 2));
                    }

                    StoreIntToMemory(SplitValue(Instruction, 1 ) , (Value1 - Value2));

                    if (Debug)cout << BlueText << "sub Result:"<< PullIntFromMemory(SplitValue(Instruction, 1)) << "\n";
                }

                if (SplitValue(Instruction, 0 ) == "mul"){   
                    FoundInstruction = true;
                    int Value1 = PullIntFromMemory(SplitValue(Instruction, 1));
                    int Value2 = 0;

                    if (IsNumber(SplitValue(Instruction, 2))){
                        Value2 = StringToInt(SplitValue(Instruction, 2));
                    }
                    else {
                        Value2 = PullIntFromMemory(SplitValue(Instruction, 2));
                    }

                    StoreIntToMemory(SplitValue(Instruction, 1 ) , (Value1 * Value2));

                    if (Debug)cout << BlueText << "mul Result:"<< PullIntFromMemory(SplitValue(Instruction, 1)) << "\n";
                }

                if (SplitValue(Instruction, 0 ) == "div"){   
                    FoundInstruction = true;
                    int Value1 = PullIntFromMemory(SplitValue(Instruction, 1));
                    int Value2 = 0;

                    if (IsNumber(SplitValue(Instruction, 2))){
                        Value2 = StringToInt(SplitValue(Instruction, 2));
                    }
                    else {
                        Value2 = PullIntFromMemory(SplitValue(Instruction, 2));
                    }

                    StoreIntToMemory(SplitValue(Instruction, 1 ) , (Value1 / Value2));

                    if (Debug)cout << BlueText << "div Result:"<< PullIntFromMemory(SplitValue(Instruction, 1)) << "\n";
                }

                if (SplitValue(Instruction, 0 ) == "set"){
                    FoundInstruction = true;
                    if (!ScanVaribleMemory(SplitValue(Instruction, 2 ))){
                        string VaribleData = SplitValue(Instruction, 2 );
                        int VaribleType = 0;

                        if (Debug)cout << RedText << "set: " << VaribleData << " ";

                        if (ReadValue(VaribleData , 0 , 0) == "'"){
                            if (Debug)cout << "String Type\n";
                            VaribleType = 1;
                        }
                        else {
                            if (Debug)cout << "Int Type\n";
                            VaribleType = 0;
                        }
                        
                        if (VaribleType == 1){
                            string StoredData = "";
                            for (int i = 0 ; i <= VaribleData.size() ; i ++){
                                if (ReadValue(VaribleData , i , i) != "'"){
                                    StoredData += ReadValue(VaribleData , i , i);
                                }
                            }
                            if (Debug)cout << "Parsed String: " << StoredData << "\n"; 
                            StoreStrtoMemory(SplitValue(Instruction, 1 ) , StoredData);
                        }
                        else {
                            StoreIntToMemory( SplitValue(Instruction, 1 ) , StringToInt(VaribleData));
                        }
                    }
                    else {
                        int IntValue = PullIntFromMemory(SplitValue(Instruction, 2 ));
                        string StringValue = PullStrFromMemory(SplitValue(Instruction, 2 ));

                        StoreIntToMemory(SplitValue(Instruction, 1 ) , IntValue);   
                        StoreStrtoMemory(SplitValue(Instruction, 1 ) , StringValue);

                        if (Debug)cout << RedText << "set: " << IntValue << " \n" ;
                    }
                }
            
                if (SplitValue(Instruction, 0 ) == "cmp"){   
                    FoundInstruction = true;
                    ParasiteScriptCoreData.CompareFlag = true;

                    int V1IValue = PullIntFromMemory(SplitValue(Instruction, 1));
                    string V1Value = PullStrFromMemory(SplitValue(Instruction, 1));
                    

                    int V2IValue = 0; 
                    string V2Value; 

                    if (IsNumber(SplitValue(Instruction, 2))){
                        V2IValue = StringToInt(SplitValue(Instruction, 2));
                    }
                    else {
                        V2IValue = PullIntFromMemory(SplitValue(Instruction, 2));
                        V2Value = PullStrFromMemory(SplitValue(Instruction, 2));
                    }

                    if (V2IValue == 0 && V1IValue == 0){
                        if (V1Value == V2Value){
                            ParasiteScriptCoreData.EqualFlag = true;
                        }
                        else{
                            ParasiteScriptCoreData.NotEqualFlag = true;
                        }
                    }

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

                if ( SplitValue(Instruction, 0 ) == "jifne"){  
                    FoundInstruction = true;
                    if(ParasiteScriptCoreData.NotEqualFlag){
                        for (int i = 0 ; i <= JumpPointCounter ; i ++){
                            if (JumpPoints[i].Name == SplitValue(Instruction, 1)){
                                ParasiteScriptCoreData.ReturnLine = ParasiteScriptCoreData.LineCounter;
                                ParasiteScriptCoreData.LineCounter = JumpPoints[i].LineNumber;
                                ParasiteScriptCoreData.NotEqualFlag = false;
                            }
                        }
                    }
                }

                if (SplitValue(Instruction, 0 ) == "jife"){  
                    FoundInstruction = true;
                    if(ParasiteScriptCoreData.EqualFlag){
                        for (int i = 0 ; i <= JumpPointCounter ; i ++){
                            if (JumpPoints[i].Name == SplitValue(Instruction, 1)){
                                ParasiteScriptCoreData.ReturnLine = ParasiteScriptCoreData.LineCounter;
                                ParasiteScriptCoreData.LineCounter = JumpPoints[i].LineNumber;
                                ParasiteScriptCoreData.EqualFlag = false;
                            }
                        }
                    }
                }

                if (SplitValue(Instruction, 0 ) == "jifg"){  
                    FoundInstruction = true;
                    if(ParasiteScriptCoreData.GreaterFlag){
                        for (int i = 0 ; i <= JumpPointCounter ; i ++){
                            if (JumpPoints[i].Name == SplitValue(Instruction, 1)){
                                ParasiteScriptCoreData.ReturnLine = ParasiteScriptCoreData.LineCounter;
                                ParasiteScriptCoreData.LineCounter = JumpPoints[i].LineNumber;
                                ParasiteScriptCoreData.LesserFlag = false;
                            }
                        }
                    }
                }

                if (SplitValue(Instruction, 0 ) == "jifl"){  
                    FoundInstruction = true;
                    if(ParasiteScriptCoreData.LesserFlag){
                        for (int i = 0 ; i <= JumpPointCounter ; i ++){
                            if (JumpPoints[i].Name == SplitValue(Instruction, 1)){
                                ParasiteScriptCoreData.ReturnLine = ParasiteScriptCoreData.LineCounter;
                                ParasiteScriptCoreData.LineCounter = JumpPoints[i].LineNumber;
                                ParasiteScriptCoreData.LesserFlag = false;
                            }
                        }
                    }
                }

                if (SplitValue(Instruction, 0 ) == "wipe"){  
                    FoundInstruction = true;
                    ParasiteScriptCoreData.LesserFlag = false;
                    ParasiteScriptCoreData.GreaterFlag = false;
                    ParasiteScriptCoreData.EqualFlag = false;
                    ParasiteScriptCoreData.NotEqualFlag = false;
                }

                if (SplitValue(Instruction, 0 ) == "ret"){
                    FoundInstruction = true;
                    if (Debug)cout << GreenText << "ret: Line " <<  ParasiteScriptCoreData.ReturnLine << "\n";
                    ParasiteScriptCoreData.LineCounter = ParasiteScriptCoreData.ReturnLine;
                }


                if (SplitValue(Instruction, 0 ) == "pullinp"){
                    FoundInstruction = true;

                    int InpValue = 0;

                    if (!IsGamepadAvailable(0)){
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
                    }
                    else {
                        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) >= 0.5f){
                            InpValue = 2;
                        }
                        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) <= -0.5f){
                            InpValue = 4;
                        }

                        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) >= 0.5f){
                            InpValue = 3;
                        }
                        if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) <= -0.5f){
                            InpValue = 1;
                        }

                        if (IsGamepadButtonDown(0 , GAMEPAD_BUTTON_LEFT_FACE_UP)){
                            InpValue = 1;
                        }
                        if (IsGamepadButtonDown(0 , GAMEPAD_BUTTON_LEFT_FACE_DOWN)){
                            InpValue = 3;
                        }
                        if (IsGamepadButtonDown(0 , GAMEPAD_BUTTON_LEFT_FACE_RIGHT)){
                            InpValue = 2;
                        }
                        if (IsGamepadButtonDown(0 , GAMEPAD_BUTTON_LEFT_FACE_LEFT)){
                            InpValue = 4;
                        }

                        if (IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)){
                            InpValue = 6;
                        }
                        if (IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT)){
                            InpValue = 7;
                        }

                        if (IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)){
                            InpValue = 5;
                        }
                    }
                    
                    StoreIntToMemory(SplitValue(Instruction, 1 ) , InpValue);
                }

                if (SplitValue(Instruction, 0 ) == "drawspr"){   
                    FoundInstruction = true;
                    int X = 0;
                    int Y = 0;
                    int Scale = 0;
                    int Size = 0;

                    if (IsNumber(SplitValue(Instruction, 2 ))){
                        X = StringToInt(SplitValue(Instruction, 2 ));
                    }
                    else {X = PullIntFromMemory(SplitValue(Instruction, 2 ));}

                    if (IsNumber(SplitValue(Instruction, 3 ))){
                        Y = StringToInt(SplitValue(Instruction, 3 ));
                    }
                    else {Y = PullIntFromMemory(SplitValue(Instruction, 3 ));}

                    if (IsNumber(SplitValue(Instruction, 4 ))){
                        Scale = StringToInt(SplitValue(Instruction, 4 ));
                    }
                    else {Scale = PullIntFromMemory(SplitValue(Instruction, 4 ));}

                    if (IsNumber(SplitValue(Instruction, 5 ))){
                        Size = StringToInt(SplitValue(Instruction, 5 ));
                    }
                    else {Size = PullIntFromMemory(SplitValue(Instruction, 5 ));}

                    for (int x = 0 ; x <= Size - 1 ; x ++){
                        for (int y = 0 ; y <= Size - 1 ; y ++){
                            switch(PullStrFromMemory(SplitValue(Instruction, 1))[y * Size + x]){
                                case L'0':
                                    DrawRectangle( ((x * Scale) + X) * DisplayScale, ((y * Scale) + Y )* DisplayScale , Scale * DisplayScale ,Scale * DisplayScale , PDBlue);
                                    break;
                                case L'1':
                                    DrawRectangle( ((x * Scale) + X) * DisplayScale, ((y * Scale) + Y )* DisplayScale , Scale * DisplayScale ,Scale * DisplayScale , PLBlue);
                                    break;
                                case L'2':
                                    DrawRectangle( ((x * Scale) + X) * DisplayScale, ((y * Scale) + Y )* DisplayScale , Scale * DisplayScale ,Scale * DisplayScale , PDRed);
                                    break;
                                case L'3':
                                    DrawRectangle( ((x * Scale) + X) * DisplayScale, ((y * Scale) + Y )* DisplayScale , Scale * DisplayScale ,Scale * DisplayScale , PLRed);
                                    break;
                                case L'4':
                                    DrawRectangle( ((x * Scale) + X) * DisplayScale, ((y * Scale) + Y )* DisplayScale , Scale * DisplayScale ,Scale * DisplayScale , PDYellow);
                                    break;
                                case L'5':
                                    DrawRectangle( ((x * Scale) + X) * DisplayScale, ((y * Scale) + Y )* DisplayScale , Scale * DisplayScale ,Scale * DisplayScale , PLYellow);
                                    break;
                                case L'6':
                                    DrawRectangle( ((x * Scale) + X) * DisplayScale, ((y * Scale) + Y )* DisplayScale , Scale * DisplayScale ,Scale * DisplayScale , PDPurple);
                                    break;
                                case L'7':
                                    DrawRectangle( ((x * Scale) + X) * DisplayScale, ((y * Scale) + Y )* DisplayScale , Scale * DisplayScale ,Scale * DisplayScale , PLPurple);
                                    break;
                                case L'8':
                                    DrawRectangle( ((x * Scale) + X) * DisplayScale, ((y * Scale) + Y )* DisplayScale , Scale * DisplayScale ,Scale * DisplayScale , PDGreen);
                                    break;
                                case L'9':
                                    DrawRectangle( ((x * Scale) + X) * DisplayScale, ((y * Scale) + Y )* DisplayScale , Scale * DisplayScale ,Scale * DisplayScale , PLGreen);
                                    break;
                            }
                        }
                    }
                }
            }

        }
    }
}
