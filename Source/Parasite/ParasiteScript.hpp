#include "ParasiteScriptData.hpp"

// Parasite Script v.1.0

// Based of Parasites MSScript 

//#define ParasiteEnabled 

#define RedText "\033[4;31m"
#define GreenText "\033[1;32m"
#define BlueText "\033[1;34m"
#define WhiteText "\033[1;37m"

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


auto ParasiteScriptInterperate(){ // Quick Interperater
    bool OriginalInteperater = false;

    for (int i = 0 ; i <= ParasiteScriptCoreData.ProgramSize ; i ++){
    if (ParasiteScriptCoreData.LineCounter != ParasiteScriptCoreData.ProgramSize){

        if (!OriginalInteperater){
            if (SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 ) == "stop"){
                break;
            }

            if (SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 ) == "var" || SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 ) == "spr"){
                VaribleMemory[VaribleCounter].Name = SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 1 );

                string VaribleData = SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 2 );
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

                if (SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 ) == "jumpl"){   
                    for (int i = 0 ; i <= JumpPointCounter ; i ++){
                        if (JumpPoints[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 6 , 9)){
                                ParasiteScriptCoreData.ReturnLine = ParasiteScriptCoreData.LineCounter;
                                ParasiteScriptCoreData.LineCounter = JumpPoints[i].LineNumber;
                        }
                    }
                }
                else {
                    if (SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 ) == "jump"){   
                        ParasiteScriptCoreData.LineCounter = StringToInt(SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 1 )) - 2;
                    }
                }

                if (SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 ) == "addv"){   
                    int Value1 = 0;
                    int Value2 = 0;
                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 1 )){
                            Value1 = VaribleMemory[i].IValue;
                        }
                        if (VaribleMemory[i].Name == SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 2 )){
                            Value2 = VaribleMemory[i].IValue;
                        }
                    }

                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 1 )){
                            VaribleMemory[i].IValue = Value1 + Value2;
                            cout << BlueText << "addv Result:"<< VaribleMemory[i].IValue << "\n";
                        }
                    }
                }

                if (SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 ) == "subv"){   
                    int Value1 = 0;
                    int Value2 = 0;

                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 2 )){
                            Value2 = VaribleMemory[i].IValue;
                        }
                    }


                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 1 )){
                            VaribleMemory[i].IValue = VaribleMemory[i].IValue - Value2;
                            cout << BlueText << "subv Result:"<< VaribleMemory[i].IValue << "\n";
                        }
                    }
                }

                if (SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 ) == "mulv"){   
                    int Value1 = 0;
                    int Value2 = 0;
                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 1 )){
                            Value1 = VaribleMemory[i].IValue;
                        }
                        if (VaribleMemory[i].Name == SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 2 )){
                            Value2 = VaribleMemory[i].IValue;
                        }
                    }

                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 1 )){
                            VaribleMemory[i].IValue = Value1 * Value2;
                            cout << BlueText << "mulv Result:"<< VaribleMemory[i].IValue << "\n";
                        }
                    }
                }

                if (SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 ) == "divv"){   
                    int Value1 = 0;
                    int Value2 = 0;
                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 1 )){
                            Value1 = VaribleMemory[i].IValue;
                        }
                        if (VaribleMemory[i].Name == SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 2 )){
                            Value2 = VaribleMemory[i].IValue;
                        }
                    }

                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 1 )){
                            VaribleMemory[i].IValue = Value1 / Value2;
                            cout << BlueText << "divv Result:"<< VaribleMemory[i].IValue << "\n";
                        }
                    }
                }

                if (SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 ) == "add"){   
                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 1 )){
                            VaribleMemory[i].IValue += StringToInt(SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 2 ));
                            cout << BlueText << "add Result:"<< VaribleMemory[i].IValue << "\n";
                        }
                    }
                }

                if (SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 ) == "sub"){   
                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 1 )){
                            VaribleMemory[i].IValue -= StringToInt(SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 2 ));
                            cout << BlueText << "sub Result:"<< VaribleMemory[i].IValue << "\n";
                        }
                    }
                }

                if (SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 ) == "mul"){   
                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 1 )){
                            VaribleMemory[i].IValue = VaribleMemory[i].IValue * StringToInt(SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 2 ));
                            cout << BlueText << "mul Result:"<< VaribleMemory[i].IValue << "\n";
                        }
                    }
                }

                if (SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 ) == "div"){   
                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 1 )){
                            VaribleMemory[i].IValue = VaribleMemory[i].IValue / StringToInt(SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 2 ));
                            cout << BlueText << "div Result:"<< VaribleMemory[i].IValue << "\n";
                        }
                    }
                }
            
                if (SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 ) == "set"){
                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 1 )){

                            string VaribleData = SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 2 );

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

                if (SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 ) == "setv"){   

                    int InValue = 0;

                    string InStringValue = "";
                

                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 2 )){
                            InValue = VaribleMemory[i].IValue;
                            InStringValue = VaribleMemory[i].Value;
                        }
                    }
                

                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 1 )){
                            VaribleMemory[i].IValue = InValue;   
                            VaribleMemory[i].Value = InStringValue;   

                            cout << RedText << "setv: " << InValue << " \n" ;
                        }
                    }
                }
                
                if (SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 ) == "end"){   
                    exit(0);
                }

                if (SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 ) == "settextsize"){   
                    ParasiteScriptCoreData.TextSize = StringToInt(SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 1 ));
                }

            
                if (SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 ) == "cmpvv"){   
                    ParasiteScriptCoreData.CompareFlag = true;

                    int V1 = false;
                    int V2 = false;
                    string V1Value;
                    string V2Value; 

                    int V1IValue = 0;
                    int V2IValue = 0; 

                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 1 )){
                            V1 = true;
                            if (VaribleMemory[i].IValue != 0){
                                V1IValue = VaribleMemory[i].IValue;
                            }
                            else {
                                V1Value = VaribleMemory[i].Value;
                            }
                        }
                        if (VaribleMemory[i].Name == SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 2 )){
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

                if (SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 ) == "cmpvi"){   
                    ParasiteScriptCoreData.CompareFlag = true;

                    int V1 = false;
                    int V2 = true;

                    int V1IValue = 0;
                    int V2IValue = StringToInt(SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 2 )); 

                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 1 )){
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


                if ( SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 ) == "jifne"){  
                    if(ParasiteScriptCoreData.NotEqualFlag){
                        for (int i = 0 ; i <= JumpPointCounter ; i ++){
                            if (JumpPoints[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 6 , 9)){
                                ParasiteScriptCoreData.ReturnLine = ParasiteScriptCoreData.LineCounter + 2;
                                ParasiteScriptCoreData.LineCounter = JumpPoints[i].LineNumber;
                                ParasiteScriptCoreData.NotEqualFlag = false;
                            }
                        }
                    }
                }

                if (SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 ) == "jife"){  
                    if(ParasiteScriptCoreData.EqualFlag){
                        for (int i = 0 ; i <= JumpPointCounter ; i ++){
                            if (JumpPoints[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 5 , 8)){
                                ParasiteScriptCoreData.ReturnLine = ParasiteScriptCoreData.LineCounter + 2;
                                ParasiteScriptCoreData.LineCounter = JumpPoints[i].LineNumber;
                                ParasiteScriptCoreData.EqualFlag = false;
                            }
                        }
                    }
                }

                if (SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 ) == "jifg"){  
                    if(ParasiteScriptCoreData.GreaterFlag){
                        for (int i = 0 ; i <= JumpPointCounter ; i ++){
                            if (JumpPoints[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 5 , 8)){
                                ParasiteScriptCoreData.ReturnLine = ParasiteScriptCoreData.LineCounter + 2;
                                ParasiteScriptCoreData.LineCounter = JumpPoints[i].LineNumber;
                                ParasiteScriptCoreData.LesserFlag = false;
                            }
                        }
                    }
                }

                if (SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 ) == "jifl"){  
                    if(ParasiteScriptCoreData.LesserFlag){
                        for (int i = 0 ; i <= JumpPointCounter ; i ++){
                            if (JumpPoints[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 5 , 8)){
                                ParasiteScriptCoreData.ReturnLine = ParasiteScriptCoreData.LineCounter + 2;
                                ParasiteScriptCoreData.LineCounter = JumpPoints[i].LineNumber;
                                ParasiteScriptCoreData.LesserFlag = false;
                            }
                        }
                    }
                }

                if (SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 ) == "wipe"){  
                    ParasiteScriptCoreData.LesserFlag = false;
                    ParasiteScriptCoreData.GreaterFlag = false;
                    ParasiteScriptCoreData.EqualFlag = false;
                    ParasiteScriptCoreData.NotEqualFlag = false;
                }

                if (SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 ) == "ret"){
                    cout << GreenText << "ret: Line " <<  ParasiteScriptCoreData.ReturnLine << "\n";
                    ParasiteScriptCoreData.LineCounter = ParasiteScriptCoreData.ReturnLine;
                }


                if (SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 ) == "pullinp"){

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
                        if (VaribleMemory[i].Name == SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 1 )){
                            VaribleMemory[i].IValue = InpValue;
                        }
                    }
                }

                if (SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 ) == "drawspr"){   
                    int X = 0;
                    int Y = 0;
                    int Scale = 1;
                    int Size = 16;

                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 2 )){
                            X = VaribleMemory[i].IValue;
                        }
                        if (VaribleMemory[i].Name == SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 3 )){
                            Y = VaribleMemory[i].IValue;
                        }
                        if (VaribleMemory[i].Name == SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 4 )){
                            Scale = VaribleMemory[i].IValue;
                        }
                        if (VaribleMemory[i].Name == SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 5 )){
                            Size = VaribleMemory[i].IValue;

                        }
                    }

                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 1 )){
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

                if (SplitValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 ) == "tick"){
                    i = ParasiteScriptCoreData.ProgramSize;
                    ParasiteScriptCoreData.LineCounter ++;
                    break;   
                }


        }

    
        if (OriginalInteperater){
            if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 , 3) == "stop"){
                break;
            }

            if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 , 2) == "var" || ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 , 2) == "spr"){
                VaribleMemory[VaribleCounter].Name = ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 4 , 7);
                if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 9 , 9) == "'")VaribleMemory[VaribleCounter].Value = ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 9 , ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter].size());
                else {
                        VaribleMemory[VaribleCounter].IValue = StringToInt(ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 9 , ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter].size()));
                }
                VaribleCounter++;   
                }

                if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 , 4) == "endex"){   
                    for (int i = 0 ; i <= JumpPointCounter ; i ++){
                        if (JumpPoints[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 6 , 9)){
                                ParasiteScriptCoreData.ReturnLine = ParasiteScriptCoreData.LineCounter;
                                ParasiteScriptCoreData.LineCounter = JumpPoints[i].LineNumber;
                        }
                    }
                    i = ParasiteScriptCoreData.ProgramSize;
                }

                if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 , 4) == "jumpl"){   
                    for (int i = 0 ; i <= JumpPointCounter ; i ++){
                        if (JumpPoints[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 6 , 9)){
                                ParasiteScriptCoreData.ReturnLine = ParasiteScriptCoreData.LineCounter;
                                ParasiteScriptCoreData.LineCounter = JumpPoints[i].LineNumber;
                        }
                    }
                }
                else {
                    if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 , 3) == "jump"){   
                        ParasiteScriptCoreData.LineCounter = StringToInt(ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 5 ,ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter].size()-1));
                    }
                }

                if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 , 3) == "addv"){   
                    int Value1 = 0;
                    int Value2 = 0;
                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 5 , 8)){
                            Value1 = VaribleMemory[i].IValue;
                        }
                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 10 , 13)){
                            Value2 = VaribleMemory[i].IValue;
                        }
                    }

                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 5 , 8)){
                            VaribleMemory[i].IValue = Value1 + Value2;
                        }
                    }
                }

                if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 , 3) == "subv"){   
                    int Value1 = 0;
                    int Value2 = 0;
                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 5 , 8)){
                            Value1 = VaribleMemory[i].IValue;
                        }
                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 10 , 13)){
                            Value2 = VaribleMemory[i].IValue;
                        }
                    }

                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 5 , 8)){
                            VaribleMemory[i].IValue = Value1 - Value2;
                        }
                    }
                }

                if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 , 3) == "mulv"){   
                    int Value1 = 0;
                    int Value2 = 0;
                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 5 , 8)){
                            Value1 = VaribleMemory[i].IValue;
                        }
                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 10 , 13)){
                            Value2 = VaribleMemory[i].IValue;
                        }
                    }

                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 5 , 8)){
                            VaribleMemory[i].IValue = Value1 * Value2;
                        }
                    }
                }

                if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 , 3) == "divv"){   
                    int Value1 = 0;
                    int Value2 = 0;
                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 5 , 8)){
                            Value1 = VaribleMemory[i].IValue;
                        }
                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 10 , 13)){
                            Value2 = VaribleMemory[i].IValue;
                        }
                    }

                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 5 , 8)){
                            VaribleMemory[i].IValue = Value1 / Value2;
                        }
                    }
                }

                if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 , 2) == "add"){   
                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 4 , 7)){
                            VaribleMemory[i].IValue += StringToInt(ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 9 , ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter].size() - 1));
                        }
                    }
                }

                if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 , 2) == "sub"){   
                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 4 , 7)){
                            VaribleMemory[i].IValue -= StringToInt(ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 9 , ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter].size() - 1));
                        }
                    }
                }

                if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 , 2) == "mul"){   
                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 4 , 7)){
                            VaribleMemory[i].IValue = VaribleMemory[i].IValue * StringToInt(ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 9 , ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter].size() - 1));
                        }
                    }
                }

                if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 , 2) == "div"){   
                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 4 , 7)){
                            VaribleMemory[i].IValue = VaribleMemory[i].IValue / StringToInt(ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 9 , ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter].size() - 1));
                        }
                    }
                }
            
                if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 , 2) == "set"){   
                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 4 , 7)){
                            VaribleMemory[i].IValue = StringToInt(ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 9 , ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter].size() - 1));
                        }
                    }
                }
                
                if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 , 2) == "end"){   
                    exit(0);
                }

                if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 , 10) == "settextsize"){   
                    ParasiteScriptCoreData.TextSize = StringToInt(ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 12 , ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter].size() - 1));
                }

            
                if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 , 4) == "cmpvv"){   
                    ParasiteScriptCoreData.CompareFlag = true;

                    int V1 = false;
                    int V2 = false;
                    string V1Value;
                    string V2Value; 

                    int V1IValue = 0;
                    int V2IValue = 0; 

                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 6 , 9)){
                            V1 = true;
                            if (VaribleMemory[i].IValue != 0){
                                V1IValue = VaribleMemory[i].IValue;
                            }
                            else {
                                V1Value = VaribleMemory[i].Value;
                            }
                        }
                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 11 , 14)){
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

                if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 , 4) == "cmpvi"){   
                    ParasiteScriptCoreData.CompareFlag = true;

                    int V1 = false;
                    int V2 = true;

                    int V1IValue = 0;
                    int V2IValue = StringToInt(ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 11 , ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter].size())); 

                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 6 , 9)){
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


                if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 , 4) == "jifne"){  
                    if(ParasiteScriptCoreData.NotEqualFlag){
                        for (int i = 0 ; i <= JumpPointCounter ; i ++){
                            if (JumpPoints[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 6 , 9)){
                                ParasiteScriptCoreData.LineCounter = JumpPoints[i].LineNumber;
                                ParasiteScriptCoreData.NotEqualFlag = false;
                            }
                        }
                    }
                }

                if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 , 3) == "jife"){  
                    if(ParasiteScriptCoreData.EqualFlag){
                        for (int i = 0 ; i <= JumpPointCounter ; i ++){
                            if (JumpPoints[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 5 , 8)){
                                ParasiteScriptCoreData.ReturnLine = ParasiteScriptCoreData.LineCounter;
                                ParasiteScriptCoreData.LineCounter = JumpPoints[i].LineNumber;
                                ParasiteScriptCoreData.EqualFlag = false;
                            }
                        }
                    }
                }

                if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 , 3) == "jifg"){  
                    if(ParasiteScriptCoreData.GreaterFlag){
                        for (int i = 0 ; i <= JumpPointCounter ; i ++){
                            if (JumpPoints[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 5 , 8)){
                                ParasiteScriptCoreData.ReturnLine = ParasiteScriptCoreData.LineCounter;
                                ParasiteScriptCoreData.LineCounter = JumpPoints[i].LineNumber;
                                ParasiteScriptCoreData.LesserFlag = false;
                            }
                        }
                    }
                }

                if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 , 3) == "jifl"){  
                    if(ParasiteScriptCoreData.LesserFlag){
                        for (int i = 0 ; i <= JumpPointCounter ; i ++){
                            if (JumpPoints[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 5 , 8)){
                                ParasiteScriptCoreData.ReturnLine = ParasiteScriptCoreData.LineCounter;
                                ParasiteScriptCoreData.LineCounter = JumpPoints[i].LineNumber;
                                ParasiteScriptCoreData.LesserFlag = false;
                            }
                        }
                    }
                }

                if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 , 3) == "wipe"){  
                    ParasiteScriptCoreData.LesserFlag = false;
                    ParasiteScriptCoreData.GreaterFlag = false;
                    ParasiteScriptCoreData.EqualFlag = false;
                    ParasiteScriptCoreData.NotEqualFlag = false;
                }

                if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 , 2) == "ret"){
                    ParasiteScriptCoreData.LineCounter = ParasiteScriptCoreData.ReturnLine;
                }


                if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 , 6) == "pullinp"){

                    int InpValue = 0;

                    if (IsKeyDown(KEY_LEFT)){InpValue = 4;}
                    if (IsKeyDown(KEY_RIGHT)){InpValue = 2;}
                    if (IsKeyDown(KEY_UP)){InpValue = 1;}
                    if (IsKeyDown(KEY_DOWN)){InpValue = 3;}    
                    if (IsKeyDown(KEY_SPACE)){InpValue = 5;}
                    if (IsKeyDown(KEY_A)){InpValue = 6;}
                    if (IsKeyDown(KEY_S)){InpValue = 7;}
                    

                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 8 , 11)){
                            VaribleMemory[i].IValue = InpValue;
                        }
                    }
                }

                if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 , 7) == "drawrect"){
                    int PosX = 0;
                    int PosY = 0;
                    int Width = 50;
                    int Height = 50;

                    Color TextColor = WHITE;

                    

                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 9 , 12)){
                            PosX = VaribleMemory[i].IValue;
                        }

                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 14 , 17)){
                            PosY = VaribleMemory[i].IValue;
                        }

                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 19 , 22)){
                            Width = VaribleMemory[i].IValue;
                        }

                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 24 , 27)){
                            Height = VaribleMemory[i].IValue;
                        }  
                    }

                    if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 29, 31) == "wht"){
                        TextColor = WHITE;
                    }

                    if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 29, 31) == "red"){
                        TextColor = RED;
                    }

                    if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 29, 31) == "blu"){
                        TextColor = BLUE;
                    }

                    if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 29, 31) == "grn"){
                        TextColor = GREEN;
                    }

                    if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 29, 31) == "yel"){
                        TextColor = YELLOW;
                    }

                    if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 29, 31) == "pur"){
                        TextColor = PURPLE;
                    }

                    DrawRectangle(PosX  , PosY  , Width  , Height  , TextColor);

                }

                if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 , 7) == "drawtext"){
                    int PosX = 0;
                    int PosY = 0;
                    Color TextColor;

                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 9 , 12)){
                            PosX = VaribleMemory[i].IValue;
                        }

                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 14 , 17)){
                            PosY = VaribleMemory[i].IValue;
                        }

                    }


                    if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 19 , 21) == "wht"){
                        TextColor = WHITE;
                    }

                    if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 19 , 21) == "red"){
                        TextColor = RED;
                    }

                    if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 19 , 21) == "blu"){
                        TextColor = BLUE;
                    }

                    if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 19 , 21) == "grn"){
                        TextColor = GREEN;
                    }

                    if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 19 , 21) == "yel"){
                        TextColor = YELLOW;
                    }

                    if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 19 , 21) == "pur"){
                        TextColor = PURPLE;
                    }

                    string TextString;

                    if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 23 , 23) == "'"){
                        TextString = ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter], 24 , ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter].size() - 2 );
                    }
                    else {
                        for (int i = 0 ; i <= VaribleCounter; i++){
                            if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 23 , 26)){
                                TextString = ReadValue(VaribleMemory[i].Value, 1, VaribleMemory[i].Value.size());
                            }
                        }
                    }

                    DrawText(TextString.c_str(), PosX , PosY , ParasiteScriptCoreData.TextSize , TextColor );

                }

                if (ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 0 , 6) == "drawspr"){   
                    int X = 0;
                    int Y = 0;
                    int Scale = 1;
                    int Size = 8;

                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 13 , 16)){
                            X = VaribleMemory[i].IValue;
                        }
                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 18 , 21)){
                            Y = VaribleMemory[i].IValue;
                        }
                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 23 , 26)){
                            Scale = VaribleMemory[i].IValue;
                        }
                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 28 , 31)){
                            Size = VaribleMemory[i].IValue;
                        }
                    }

                    for (int i = 0 ; i <= VaribleCounter; i++){
                        if (VaribleMemory[i].Name == ReadValue(ParasiteScriptCoreData.Line[ParasiteScriptCoreData.LineCounter] , 8 , 11)){
                            for (int x = 1 ; x <= Size ; x ++){
                                for (int y = 0 ; y <= Size - 1 ; y ++){
                                    switch(VaribleMemory[i].Value[y * 8 + x]){
                                        case L'0':
                                            DrawRectangle((x * Scale) + X, (y * Scale) + Y , Scale , Scale, BLACK);
                                            break;
                                        case L'1':
                                            DrawRectangle((x * Scale) + X, (y * Scale) + Y , Scale , Scale, WHITE);
                                            break;
                                        case L'2':
                                            DrawRectangle((x * Scale) + X, (y * Scale) + Y , Scale , Scale, RED);
                                            break;
                                        case L'3':
                                            DrawRectangle((x * Scale) + X, (y * Scale) + Y , Scale , Scale, GREEN);
                                            break;
                                        case L'4':
                                            DrawRectangle((x * Scale) + X, (y * Scale) + Y , Scale , Scale, BLUE);
                                            break;
                                        case L'5':
                                            DrawRectangle((x * Scale) + X, (y * Scale) + Y , Scale , Scale, YELLOW);
                                            break;
                                        case L'6':
                                            DrawRectangle((x * Scale) + X, (y * Scale) + Y , Scale , Scale, PURPLE);
                                            break;
                                        case L'7':
                                            DrawRectangle((x * Scale) + X, (y * Scale) + Y , Scale , Scale, PINK);
                                            break;
                                        case L'8':
                                            DrawRectangle((x * Scale) + X, (y * Scale) + Y , Scale , Scale, BROWN);
                                            break;
                                        case L'9':
                                            DrawRectangle((x * Scale) + X, (y * Scale) + Y , Scale , Scale, GRAY);
                                            break;
                                    }
                                }
                            }
                        }
                    }
                }
            }


            ParasiteScriptCoreData.LineCounter ++;

        }
        else{
            for (int i = 0 ; i <= JumpPointCounter ; i ++){
                if (JumpPoints[i].Name == "LOOP"){
                    ParasiteScriptCoreData.ReturnLine = ParasiteScriptCoreData.LineCounter;
                    ParasiteScriptCoreData.LineCounter = JumpPoints[i].LineNumber;
                }
            }
        }
    }
}