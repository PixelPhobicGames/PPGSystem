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
        BenchMode = true;

    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        for (int T = 0 ; T <= InstructionsPerTick ; T++){
            CycleInstruction();
            ParasiteScriptCoreData.LineCounter += 1;
        }

        EndDrawing();
    }

    cout << "\033[0;37m";

    CloseWindow();
}