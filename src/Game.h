#ifndef GAME_H
#define GANE_H

#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>

class Game {
    private:
        bool isRunning;
        SDL_Window *winfow;
        SDL_Renderer *renderer;
    public:
        Game();
        ~Game();
        bool IsRunning() const;
        void Initialize(int width, int height);
        void ProcessInput();
        void Update();
        void Render();
        void Destroy();


};

#endif