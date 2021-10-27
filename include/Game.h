#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "../include/TextureData.h"
#include "../include/Defines.h"
#include "../include/Player.h"

class Game
{
public:

    Game();
    ~Game();
    void run();

private:

    //Loads media
    void loadMedia();

    SDL_Texture* loadFromFile(std::string path, SDL_Texture* tex, TextureData& data);
    void renderTexture(SDL_Texture* t_tex, TextureData t_data);  

    //Frees media and shuts down SDL
    void close();

    void processEvents();
    void processMouse(SDL_MouseButtonEvent& b);
    void update(float dt);
    void render();

    void cleanUp();

    bool m_gameIsRunning;

    float m_elapsed;

    //Event handler
    SDL_Event e;

    //Screen dimension constants
    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 720;

    //The window we'll be rendering to
    SDL_Window* window = NULL;

     //The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    // Used to render images to a window
    SDL_Renderer* renderer = NULL;

    Player player;

    SDL_Texture* m_playerTex = NULL;
    TextureData m_playerTexData;
};