#include "System.hpp"

int main(int argc, char *argv[])
{

    ParasiteScriptInit();

    
    InitWindow(320 , 240, "PPGSystem");
    SetTargetFPS(30);


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

        ParasiteScriptInterperate();

        EndDrawing();
    }

    CloseWindow();
}