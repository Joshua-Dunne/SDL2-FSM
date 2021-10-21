#include "../include/Game.h"

Game::Game() :
    m_gameIsRunning{ false }
{  
}

Game::~Game()
{
    cleanUp();
}

void Game::run()
{
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        //Create window
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get window surface
            screenSurface = SDL_GetWindowSurface( window );
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        }
    }

    loadMedia();

    m_gameIsRunning = true;
    while (m_gameIsRunning)
    {
        processEvents();
        update();
        render();
    }
}

void Game::loadMedia()
{
    // load necessary information here
    // Example: texture = loadFromFile("path", SDL_Surface, TextureData);
}

SDL_Texture* Game::loadFromFile(std::string path, SDL_Texture* tex, TextureData& data)
{
    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());

    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError());
    }
    else
    {
        //Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        //Create texture from surface pixels
        tex = SDL_CreateTextureFromSurface(renderer, loadedSurface);


        if (tex == NULL)
        {
            std::cout << "Unable to create texture from %s! SDL Error: %s\n" << path.c_str() << SDL_GetError() << std::endl;
        }
        else
        {
            //Get image dimensions
            data.width = loadedSurface->w;
            data.height = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return tex;
}

void Game::processEvents()
{
    //std::cout << "Processing Events" << std::endl;
    //While application is running
    while(SDL_PollEvent( &e ) != 0)
    {
        //User requests quit
        if(e.type == SDL_QUIT)
        {
            m_gameIsRunning = false;
        }

        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            processMouse(e.button);
        }
    }
}

void Game::processMouse(SDL_MouseButtonEvent& b)
{
    // process potential mouse events
}

void Game::update()
{
   // std::cout << "Updating" << std::endl;
}

void Game::renderTexture(SDL_Texture* t_tex, TextureData t_data)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad;
    renderQuad.x = t_data.x;
    renderQuad.y = t_data.y;
    renderQuad.w = t_data.width;
    renderQuad.h = t_data.height;
    
    //Render to screen
    SDL_RenderCopy(renderer, t_tex, NULL, &renderQuad);
}

void Game::render()
{
    //std::cout << "Rendering" << std::endl;

    if( window == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_RenderClear(renderer);

        // Render Textures here
        // Example: renderTexture(SDL_Surface, TextureData);

        SDL_RenderPresent(renderer);
    }


}

void Game::cleanUp()
{
    std::cout << "Cleaning up" << std::endl;    

    //Destroy window
    SDL_DestroyWindow( window );
    window = NULL;

    //Quit SDL subsystems
    SDL_Quit();

    //Quit SDL subsystems
    SDL_Quit();
}