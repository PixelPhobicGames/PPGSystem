#include "Parasite/ParasiteScript.hpp"

#include <raylib.h>
#include <string>
#include <stdlib.h>

using namespace std;


class System{

    public:
        Font SystemFont;
        Sound TypingNoise;
        wstring TerminalData = L"";
        wstring TerminalStartText = L" |    PPG SYSTEM V.1.0 |.......................|"; 

        void LoadData(){
            SystemFont = LoadFont("System/Font/Font.ttf");
            TypingNoise = LoadSound("System/Noises/TypingNoise.mp3");
            Image Icon = LoadImage("System/Icon/Icon.png");
            SetWindowIcon(Icon);
        }
};

static System PPGSystem;

static bool StepMode = false;
static bool DisplaySpeed = false;
static bool TerminalRunning = true;
static bool SpriteEditorRunning = false;
static bool TextEditorRunning = false;
static const char* FileName; 

static wchar_t EditorColor = L'2';
static wstring EditorSprite = L"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";


void DisplayTerminal(){

    int CharacterPlace = 0;
    int CharacterLine = 0;

    for (int i = 0 ; i <= PPGSystem.TerminalData.size(); i++){
        char DisplayCharacter = ' ';
        switch (PPGSystem.TerminalData[i])
        {
            case L'A':
                DisplayCharacter = 'A';
                break;
            case L'B':
                DisplayCharacter = 'B';
                break;
            case L'C':
                DisplayCharacter = 'C';
                break;
            case L'D':
                DisplayCharacter = 'D';
                break;
            case L'E':
                DisplayCharacter = 'E';
                break;
            case L'F':
                DisplayCharacter = 'F';
                break;
            case L'G':
                DisplayCharacter = 'G';
                break;
            case L'H':
                DisplayCharacter = 'H';
                break;
            case L'I':
                DisplayCharacter = 'I';
                break;
            case L'J':
                DisplayCharacter = 'J';
                break;
            case L'K':
                DisplayCharacter = 'K';
                break;
            case L'L':
                DisplayCharacter = 'L';
                break;
            case L'M':
                DisplayCharacter = 'M';
                break;
            case L'N':
                DisplayCharacter = 'N';
                break;
            case L'O':
                DisplayCharacter = 'O';
                break;
            case L'P':
                DisplayCharacter = 'P';
                break;
            case L'Q':
                DisplayCharacter = 'Q';
                break;
            case L'R':
                DisplayCharacter = 'R';
                break;
            case L'S':
                DisplayCharacter = 'S';
                break;
            case L'T':
                DisplayCharacter = 'T';
                break;
            case L'U':
                DisplayCharacter = 'U';
                break;
            case L'V':
                DisplayCharacter = 'V';
                break;
            case L'W':
                DisplayCharacter = 'W';
                break;
            case L'X':
                DisplayCharacter = 'X';
                break;
            case L'Y':
                DisplayCharacter = 'Y';
                break;
            case L'Z':
                DisplayCharacter = 'Z';
                break;
            case L' ':
                DisplayCharacter = ' ';
                break;

            case L'(':
                DisplayCharacter = '(';
                break;
            case L')':
                DisplayCharacter = ')';
                break;
            case L'.':
                DisplayCharacter = '.';
                break;
            case L',':
                DisplayCharacter = ',';
                break;
            case L'!':
                DisplayCharacter = '!';
                break;
            case L'?':
                DisplayCharacter = '?';
                break;
            case L'*':
                DisplayCharacter = '*';
                break;
            case L'%':
                DisplayCharacter = '%';
                break;
            case L'/':
                DisplayCharacter = '/';
                break;
            case L':':
                DisplayCharacter = ':';
                break;

            case L'1':
                DisplayCharacter = '1';
                break;
            case L'2':
                DisplayCharacter = '2';
                break;
            case L'3':
                DisplayCharacter = '3';
                break;
            case L'4':
                DisplayCharacter = '4';
                break;
            case L'5':
                DisplayCharacter = '5';
                break;
            case L'6':
                DisplayCharacter = '6';
                break;
            case L'7':
                DisplayCharacter = '7';
                break;
            case L'8':
                DisplayCharacter = '8';
                break;
            case L'9':
                DisplayCharacter = '9';
                break;
            case L'0':
                DisplayCharacter = '0';
                break;

            case L'|':
                DisplayCharacter = ' ';
                CharacterLine ++;
                CharacterPlace = -1;
                break;
            
            default:
                break;
        }
 
        DrawTextEx(PPGSystem.SystemFont, TextFormat("%c", DisplayCharacter), {CharacterPlace * 14 , 12 * CharacterLine}, 15, 1, WHITE);
        CharacterPlace ++;
        
    }
    if (IsKeyPressed(KEY_A))PPGSystem.TerminalData += L'A';
    if (IsKeyPressed(KEY_B))PPGSystem.TerminalData += L'B';
    if (IsKeyPressed(KEY_C))PPGSystem.TerminalData += L'C';
    if (IsKeyPressed(KEY_D))PPGSystem.TerminalData += L'D';
    if (IsKeyPressed(KEY_E))PPGSystem.TerminalData += L'E';
    if (IsKeyPressed(KEY_F))PPGSystem.TerminalData += L'F';
    if (IsKeyPressed(KEY_G))PPGSystem.TerminalData += L'G';
    if (IsKeyPressed(KEY_H))PPGSystem.TerminalData += L'H';
    if (IsKeyPressed(KEY_I))PPGSystem.TerminalData += L'I';
    if (IsKeyPressed(KEY_J))PPGSystem.TerminalData += L'J';
    if (IsKeyPressed(KEY_K))PPGSystem.TerminalData += L'K';
    if (IsKeyPressed(KEY_L))PPGSystem.TerminalData += L'L';
    if (IsKeyPressed(KEY_M))PPGSystem.TerminalData += L'M';
    if (IsKeyPressed(KEY_N))PPGSystem.TerminalData += L'N';
    if (IsKeyPressed(KEY_O))PPGSystem.TerminalData += L'O';
    if (IsKeyPressed(KEY_P))PPGSystem.TerminalData += L'P';
    if (IsKeyPressed(KEY_Q))PPGSystem.TerminalData += L'Q';
    if (IsKeyPressed(KEY_R))PPGSystem.TerminalData += L'R';
    if (IsKeyPressed(KEY_S))PPGSystem.TerminalData += L'S';
    if (IsKeyPressed(KEY_T))PPGSystem.TerminalData += L'T';
    if (IsKeyPressed(KEY_U))PPGSystem.TerminalData += L'U';
    if (IsKeyPressed(KEY_V))PPGSystem.TerminalData += L'V';
    if (IsKeyPressed(KEY_W))PPGSystem.TerminalData += L'W';
    if (IsKeyPressed(KEY_X))PPGSystem.TerminalData += L'X';
    if (IsKeyPressed(KEY_Y))PPGSystem.TerminalData += L'Y';
    if (IsKeyPressed(KEY_Z))PPGSystem.TerminalData += L'Z';
    if (IsKeyPressed(KEY_SPACE))PPGSystem.TerminalData += L' ';
    if (IsKeyPressed(KEY_ENTER))PPGSystem.TerminalData += L'|';

    if (IsKeyPressed(KEY_BACKSPACE))PPGSystem.TerminalData.erase(PPGSystem.TerminalData.size() - 1);

    if (GetKeyPressed() != NULL){
        PlaySound(PPGSystem.TypingNoise);
    }

    bool RunCommand = false;

    for (int i = 0 ; i <= PPGSystem.TerminalData.size(); i++){
        if (PPGSystem.TerminalData[i] == 'R' && PPGSystem.TerminalData[i+1] == 'U' && PPGSystem.TerminalData[i+2] == 'N'){
            i = 0;
            RunCommand = true;
        }

        if (RunCommand){
            if (PPGSystem.TerminalData[i] == 'E' && PPGSystem.TerminalData[i+1] == 'D' && PPGSystem.TerminalData[i+2] == 'I'){
                PPGSystem.TerminalData = L"\0";

                wstring AppName = L"";

                for (int x = i + 5 ; x <= 100; x ++){
                    if (PPGSystem.TerminalData[x] == L'|'){
                        break;
                    }
                    AppName += PPGSystem.TerminalData[x];
                }

                TextEditorRunning = true;
                TerminalRunning = false; // Launch Into App

                FileName = TextFormat("Apps/%ls.ps" ,AppName.c_str());
                break;
            }
            
            if (PPGSystem.TerminalData[i] == 'C' && PPGSystem.TerminalData[i+1] == 'L' && PPGSystem.TerminalData[i+2] == 'S'){
                PPGSystem.TerminalData = L"\0";
            }
            if (PPGSystem.TerminalData[i] == 'E' && PPGSystem.TerminalData[i+1] == 'N' && PPGSystem.TerminalData[i+2] == 'D'){
                exit(0);
            }
            if (PPGSystem.TerminalData[i] == 'S' && PPGSystem.TerminalData[i+1] == 'E' && PPGSystem.TerminalData[i+2] == 'I'){
                SpriteEditorRunning = true; // Launch Into Sprite Editor
                break;
            }
            if (PPGSystem.TerminalData[i] == 'L' && PPGSystem.TerminalData[i+1] == 'O' && PPGSystem.TerminalData[i+2] == 'A'){

                wstring AppName = L"";

                for (int x = i + 5 ; x <= 100; x ++){
                    if (PPGSystem.TerminalData[x] == L'|'){
                        break;
                    }
                    AppName += PPGSystem.TerminalData[x];
                }

                if (Debug)cout << TextFormat("Apps/%ls.ps" ,AppName.c_str());
            
                LoadScript(TextFormat("Apps/%ls.ps" ,AppName.c_str()));
                TerminalRunning = false; // Launch Into App
                break;
            }
            
        }
    }


}

static int SpriteEditorSize = 7;
static int SpriteEditorWidth = 16;

static bool SpriteEditorLines = true;
static bool Booting = true;
static int BootDelay = 90;
static int TextCounter = 0;

void BootScreen(){
    wstring BootScreenText = L"BOOTING PPGSYSTEM..";

    if (BootDelay != 0){
        PPGSystem.TerminalData += BootScreenText[TextCounter];
        if (TextCounter != 18)TextCounter ++;

        BootDelay --;


        if (BootDelay == 1){
            TextCounter = 0;
            PPGSystem.TerminalData = L'\0';
            BootDelay --;
        }
        
    }
    else {
        if (Booting){
            PPGSystem.TerminalData += PPGSystem.TerminalStartText[TextCounter];
            if (TextCounter != 47)TextCounter ++;
            else {
                Booting = false;
            }
        }
    }
}

void StartMenu(){
    while (TerminalRunning)
    {
        BeginDrawing();
        ClearBackground(BLACK);

        if (TextEditorRunning){
            DisplayTerminal();
        }

        if (!SpriteEditorRunning){
            DisplayTerminal();
            BootScreen();
        }
        else {
            for (int x = 0 ; x <= SpriteEditorSize ; x ++){
                for (int y = 0 ; y <= SpriteEditorSize ; y ++){
                    switch (EditorSprite[y * (SpriteEditorSize + 1) + x])
                    {
                        case L'0':
                            DrawRectangle((x *  SpriteEditorWidth  ) + 15, (y *  SpriteEditorWidth  ) + 15, SpriteEditorWidth ,  SpriteEditorWidth , PDBlue);
                            break;
                        case L'1':
                            DrawRectangle((x *  SpriteEditorWidth  ) + 15, (y *  SpriteEditorWidth  ) + 15, SpriteEditorWidth ,  SpriteEditorWidth , PLBlue);
                            break;
                        case L'2':
                            DrawRectangle((x *  SpriteEditorWidth  ) + 15, (y *  SpriteEditorWidth  ) + 15, SpriteEditorWidth ,  SpriteEditorWidth , PDRed);
                            break;
                        case L'3':
                            DrawRectangle((x *  SpriteEditorWidth  ) + 15, (y *  SpriteEditorWidth  ) + 15, SpriteEditorWidth ,  SpriteEditorWidth , PLRed);
                            break;
                        case L'4':
                            DrawRectangle((x *  SpriteEditorWidth  ) + 15, (y *  SpriteEditorWidth  ) + 15, SpriteEditorWidth ,  SpriteEditorWidth , PDYellow);
                            break;
                        case L'5':
                            DrawRectangle((x *  SpriteEditorWidth  ) + 15, (y *  SpriteEditorWidth  ) + 15, SpriteEditorWidth ,  SpriteEditorWidth , PLYellow);
                            break;
                        case L'6':
                            DrawRectangle((x *  SpriteEditorWidth  ) + 15, (y *  SpriteEditorWidth  ) + 15, SpriteEditorWidth ,  SpriteEditorWidth , PDPurple);
                            break;
                        case L'7':
                            DrawRectangle((x *  SpriteEditorWidth  ) + 15, (y *  SpriteEditorWidth  ) + 15, SpriteEditorWidth ,  SpriteEditorWidth , PLPurple);
                            break;
                        case L'8':
                            DrawRectangle((x *  SpriteEditorWidth  ) + 15, (y *  SpriteEditorWidth  ) + 15, SpriteEditorWidth ,  SpriteEditorWidth , PDGreen);
                            break;
                        case L'9':
                            DrawRectangle((x *  SpriteEditorWidth  ) + 15, (y *  SpriteEditorWidth  ) + 15, SpriteEditorWidth ,  SpriteEditorWidth , PLGreen);
                            break;

                        default:
                            if (SpriteEditorLines)DrawRectangle((x *  SpriteEditorWidth  ) + 15, (y *  SpriteEditorWidth  ) + 15, SpriteEditorWidth ,  SpriteEditorWidth , PINK);
                            break;
                    }

                    if (SpriteEditorLines)DrawRectangleLines((x *  SpriteEditorWidth  ) + 15, (y *  SpriteEditorWidth  ) + 15, SpriteEditorWidth ,  SpriteEditorWidth , WHITE);

                    DrawRectangleLines( 15, 15, (SpriteEditorWidth * SpriteEditorSize + SpriteEditorWidth) ,  (SpriteEditorWidth * SpriteEditorSize + SpriteEditorWidth)  , WHITE);
                }
            }

            if (IsMouseButtonDown(0)){
                EditorSprite[(((GetMouseY() - 15) /  SpriteEditorWidth )) * (SpriteEditorSize + 1) + (((GetMouseX() - 15) /  SpriteEditorWidth))] = EditorColor;
            }

            if (IsKeyPressed(KEY_ONE))EditorColor = L'1';
            if (IsKeyPressed(KEY_TWO))EditorColor = L'2';
            if (IsKeyPressed(KEY_THREE))EditorColor = L'3';
            if (IsKeyPressed(KEY_FOUR))EditorColor = L'4';
            if (IsKeyPressed(KEY_FIVE))EditorColor = L'5';
            if (IsKeyPressed(KEY_SIX))EditorColor = L'6';
            if (IsKeyPressed(KEY_SEVEN))EditorColor = L'7';
            if (IsKeyPressed(KEY_EIGHT))EditorColor = L'8';
            if (IsKeyPressed(KEY_NINE))EditorColor = L'9';
            if (IsKeyPressed(KEY_ZERO))EditorColor = L'0';
            if (IsKeyPressed(KEY_MINUS))EditorColor = L'+';
            if (IsKeyPressed(KEY_ENTER))wcout << EditorSprite << "\n";

            if (IsKeyPressed(KEY_A)){
                SpriteEditorSize --;

                EditorSprite = L"\0";

                for (int i = 0 ; i <= ((SpriteEditorSize + 1 ) * (SpriteEditorSize + 1)); i ++){
                    EditorSprite += L'+';
                }
            }

            if (IsKeyPressed(KEY_S)){
                SpriteEditorSize ++;

                EditorSprite = L"\0";

                for (int i = 0 ; i <= ((SpriteEditorSize + 1) * (SpriteEditorSize + 1) - 1); i ++){
                    EditorSprite += L'+';
                }
            }

            if (IsKeyPressed(KEY_Z)){
                SpriteEditorWidth --;
            }

            if (IsKeyPressed(KEY_X)){
                SpriteEditorWidth ++;
            }
            if (IsKeyPressed(KEY_D)){
                if (SpriteEditorLines){
                    SpriteEditorLines = false;
                }
                else {
                    SpriteEditorLines = true;
                }
            }

            DrawRectangle(198 , 18 , 24 *  3.75, 10 , BLACK);
            DrawTextEx(PPGSystem.SystemFont , TextFormat("Sprite Size: %i" ,SpriteEditorSize + 1) , { 200 , 20 } , 8 , 1 , WHITE );

            
        }

        if (IsKeyDown(KEY_ESCAPE)){
            TerminalRunning = false;
        }


        EndDrawing();
    }
}