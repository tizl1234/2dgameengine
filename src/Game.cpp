#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "Entity.h"
#include "Component.h"
#include "EntityManager.h"
#include "AssetManager.h"
#include "../lib/glm/glm.hpp"
#include "./Components/TransformComponent.h"
#include "./Components/SpriteComponent.h"
#include "./Components/KeyboardControlComponent.h"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;

Game::Game() {
    isRunning = false;
}

Game::~Game() {

}

bool Game::IsRunning() const {
    return isRunning;
}

void Game::Initialize(int width, int heigth) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializng SDL." << std::endl;
        return;
    }
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        heigth,
        SDL_WINDOW_BORDERLESS
    );

    if (!window) {
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cerr << "Error creating renderer." << std::endl;
        return;
    }

    LoadLevel(0);

    isRunning = true;

    return;
}

void Game::LoadLevel(int levelNumber) {
    /*Start including assets to the AssetManager here*/
    assetManager->AddTexture("tank-image", std::string("./assets/images/tank-big-right.png").c_str());
    assetManager->AddTexture("chopper-image", std::string("./assets/images/chopper-spritesheet.png").c_str());
    assetManager->AddTexture("radar-image", std::string("./assets/images/radar.png").c_str());
    /*Start including entities and theirs components*/
    Entity& tank(manager.AddEntity("tank"));
    tank.AddComponent<TransformComponent>(0,0,20,20,32, 32, 1);
    tank.AddComponent<SpriteComponent>("tank-image");

    Entity& chopper(manager.AddEntity("chopper"));
    chopper.AddComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
    chopper.AddComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
    chopper.AddComponent<KeyboardControlComponent>("up", "right", "down", "left", "space");

    Entity& radar(manager.AddEntity("radar"));
    radar.AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
    radar.AddComponent<SpriteComponent>("radar-image", 8, 150, false, true);
}

void Game::ProcessInput() {
    SDL_PollEvent(&event);

    switch(event.type) {
        case SDL_QUIT: {
            isRunning = false;
            break;
        }
        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                isRunning = false;
            }
        }
        default:{
            break;
        }
    }
}

void Game::Update() {
    //Sleep until we reach target frame time in ms
    int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);
    // Only sleep if we are too fast to process this frame
    if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) {
        SDL_Delay(timeToWait);
    }

    // delta time is the difference from last frame converted to seconds
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
    // Clamp deltaTime to a max value
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
    //Sets the new ticks fro the current frame to be used in the next pass
    ticksLastFrame = SDL_GetTicks();
    
    //Make EntityManager to call updates on all entities
    manager.Update(deltaTime);
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    if (manager.HasNoEntities()) {
        return;
    }

    manager.Render();

    SDL_RenderPresent(renderer);
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}