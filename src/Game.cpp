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
    // get performance counter before initialization to get starting elapsed time
    Uint64 start = SDL_GetPerformanceCounter();

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

            // enable VSync when creating renderer
            // passing the flag SDL_RENDERER_PRESENTVSYNC to SDL_CreateRenderer()
            // causes subsequent calls to SDL_RenderPresent() to wait before showing the window.
            SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED );
        }
    }

    int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	}

    loadMedia();

    Uint64 end = SDL_GetPerformanceCounter();

    // calculate elapsed time for first frame
	float m_elapsed = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

	// Cap to 60 FPS
	SDL_Delay(floor(16.666f - m_elapsed));

    // This is only done for the first initial wave, as everything else is calculated as the loop progresses


    m_gameIsRunning = true;
    while (m_gameIsRunning)
    {
        Uint32 current = SDL_GetTicks();
        float dT = (current - m_elapsed) / 1000.0f;

        processEvents();
        update(dT);
        render();

        m_elapsed = current;

    }
}

void Game::loadMedia()
{
    // load necessary information here
    // Example: texture = loadFromFile("path", SDL_Surface, TextureData);
    m_playerTex = loadFromFilePNG(PLAYER_SPRITES, m_playerTex, m_playerTexData);

    // player texture data won't be used, but we will keep it for debugging purposes if needed
}

SDL_Texture* Game::loadFromFileBMP(std::string path, SDL_Texture* tex, TextureData& data)
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

SDL_Texture* Game::loadFromFilePNG(std::string path, SDL_Texture* tex, TextureData& data)
{
    SDL_Texture* newTexture{ NULL };

		SDL_Surface* loadedSurface = IMG_Load(path.c_str());

		if (loadedSurface == NULL)
		{
			printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
		}
		else
		{
			newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
			if (newTexture == NULL)
			{
				printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
			}

			SDL_FreeSurface(loadedSurface);
		}

		return newTexture;
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

void Game::update(float dt)
{
   // std::cout << "Updating" << std::endl;
   player.update(dt);
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
        renderTexture(m_playerTex, *player.getAnimatedSpriteFrame());

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