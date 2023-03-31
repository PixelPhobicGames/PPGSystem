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

        for (int i = 2 ; i < argc ; i ++){
            string Argument = argv[i];

            if (Argument == "-D"){
                Debug = true;
            }
            if (Argument == "-Ds"){
                DisplaySpeed = true;
            }
        }
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        if (TimeDelay == 0){
            for (int T = 0 ; T <= InstructionsPerTick ; T++){
                CycleInstruction();
                ParasiteScriptCoreData.LineCounter += 1;
            }
        }
        else {
            TimeDelay --;
        }
        if (DisplaySpeed)DrawText(TextFormat("CPS: %i" , InstructionsPerTick * GetFPS() ) , 0 , 220 , 10 , WHITE);

        EndDrawing();
    }

    if (Debug)cout << "\033[0;37m";

    CloseWindow();
}