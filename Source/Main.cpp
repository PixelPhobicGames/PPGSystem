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

        if (BenchMode){
            TimeCounter ++;

            if (TimeCounter == 30 * 5){
                cout << "Average Speed: " << (CycleCounter / TimeCounter) / 30 << " \n";
                cout << "Cycle Score: " << (CycleCounter) / 30 * 5 << " \n";
                exit(0);
            }
        }
        for (int i = 0 ; i <= ProcessSpeed ; i ++)ParasiteScriptInterperate();

        EndDrawing();
    }

    cout << "\033[0;37m";

    CloseWindow();
}