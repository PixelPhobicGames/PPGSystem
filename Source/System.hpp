#include "Parasite/ParasiteScript.hpp"

#include <raylib.h>
#include <string>
#include <stdlib.h>

using namespace std;


class System{

    public:
        Font SystemFont;
        wstring TerminalData = L" |    PPG SYSTEM V.1.0 |.......................|";

        void LoadData(){
            SystemFont = LoadFont("System/Font/Font.ttf");
        }
};

static System PPGSystem;


static bool TerminalRunning = true;
static bool SpriteEditorRunning = false;

static wchar_t EditorColor = L'2';
static wstring EditorSprite = L"0000000000000000000000000000000000000000000000000000000000000000";

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
 
        DrawTextEx(PPGSystem.SystemFont, FormatText("%c", DisplayCharacter), {CharacterPlace * 14 , 12 * CharacterLine}, 15, 1, WHITE);
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

    bool RunCommand = false;

    for (int i = 0 ; i <= PPGSystem.TerminalData.size(); i++){
        if (PPGSystem.TerminalData[i] == 'R' && PPGSystem.TerminalData[i+1] == 'U' && PPGSystem.TerminalData[i+2] == 'N'){
            i = 0;
            RunCommand = true;
        }

        if (RunCommand){
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

                cout << FormatText("Apps/%ls.ps" ,AppName.c_str());
            
                LoadScript(FormatText("Apps/%ls.ps" ,AppName.c_str()));
                TerminalRunning = false; // Launch Into App
                break;
            }
            
        }
    }


}

void StartMenu(){
    while (TerminalRunning)
    {
        BeginDrawing();
        ClearBackground(BLACK);

        if (!SpriteEditorRunning){
            DisplayTerminal();
        }
        else {
            for (int x = 0 ; x <= 7 ; x ++){
                for (int y = 0 ; y <= 7 ; y ++){
                    switch (EditorSprite[y * 8 + x])
                    {
                        case L'0':
                            DrawRectangle((x * 16 ) + 20, (y * 16 ) + 20, 16 , 16 , BLACK);
                            break;
                        case L'1':
                            DrawRectangle((x * 16 ) + 20, (y * 16 ) + 20, 16 , 16 , WHITE);
                            break;
                        case L'2':
                            DrawRectangle((x * 16 ) + 20, (y * 16 ) + 20, 16 , 16 , RED);
                            break;
                        case L'3':
                            DrawRectangle((x * 16 ) + 20, (y * 16 ) + 20, 16 , 16 , GREEN);
                            break;
                        case L'4':
                            DrawRectangle((x * 16 ) + 20, (y * 16 ) + 20, 16 , 16 , BLUE);
                            break;
                        case L'5':
                            DrawRectangle((x * 16 ) + 20, (y * 16 ) + 20, 16 , 16 , YELLOW);
                            break;
                        case L'6':
                            DrawRectangle((x * 16 ) + 20, (y * 16 ) + 20, 16 , 16 , PURPLE);
                            break;
                        case L'7':
                            DrawRectangle((x * 16 ) + 20, (y * 16 ) + 20, 16 , 16 , PINK);
                            break;
                        case L'8':
                            DrawRectangle((x * 16 ) + 20, (y * 16 ) + 20, 16 , 16 , BROWN);
                            break;
                        case L'9':
                            DrawRectangle((x * 16 ) + 20, (y * 16 ) + 20, 16 , 16 , GRAY);
                            break;

                        default:
                            break;
                    }

                    DrawRectangleLines((x * 16 ) + 20, (y * 16 ) + 20, 16 , 16 , WHITE);
                }
            }

            if (IsMouseButtonDown(0)){
                EditorSprite[(((GetMouseY() - 20) / 16 )) * 8 + (((GetMouseX() - 20) / 16))] = EditorColor;

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
                if (IsKeyPressed(KEY_ENTER))wcout << EditorSprite << "\n";
            }

            DrawTextEx(PPGSystem.SystemFont , FormatText("%ls" ,EditorSprite.c_str()) , { 0 , 200 } , 8 , 1 , WHITE );

            
        }

        if (IsKeyPressed(KEY_ESCAPE)){
            TerminalRunning = false;
        }


        EndDrawing();
    }
}