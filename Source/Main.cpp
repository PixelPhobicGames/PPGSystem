#include "System.hpp"

int main(int argc, char *argv[])
{

    ParasiteScriptInit();

    
    InitWindow(320 , 240, "PPGSystem");
    SetTargetFPS(30);

    InitAudioDevice();


    if (argc == 1){
        PPGSystem.LoadData();

        StartMenu();
    }
    else {
        LoadScript(argv[1]);
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0 ; i <= ProcessSpeed ; i ++)ParasiteScriptInterperate();

        EndDrawing();
    }

    cout << "\033[0;37m";

    CloseWindow();
}