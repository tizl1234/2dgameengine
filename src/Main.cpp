#include <iostream>
#include "./Constants.h"
#include "./Game.h"

int main (int argc, char *args[]) {
    // TO-DO:
    Game *game = new Game(); 

    game->Initialize(WINDOW_WIDTH, WINDOW_HIGHT);

    while (game->IsRunning()) {
        game->ProcessInput();
        game->Update();
        game->Render();
    }

    game->Destroy();
    
    return 0;
}