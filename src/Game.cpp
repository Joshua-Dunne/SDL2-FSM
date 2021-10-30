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
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        }
    }

    int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
	}

    loadMedia();

    Uint64 end = SDL_GetPerformanceCounter();

    // calculate elapsed time for first frame
	float m_elapsed = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
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
            else
            {
                //Get image dimensions
                data.width = loadedSurface->w;
                data.height = loadedSurface->h;
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

        if (e.type == SDL_KEYDOWN)
	    {
            processKeyPress(e);
	    }

	    if (e.type == SDL_KEYUP)
	    {
            processKeyRelease(e);
	    }

        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            processMouse(e.button);
        }
    }
}

void Game::processMouse(SDL_MouseButtonEvent& b)
{
    // process mouse events
}

// e.key.keysym.sym == SDLK_w
void Game::processKeyPress(SDL_Event& e)
{
    if (e.key.keysym.sym == SDLK_q) {
		DEBUG_MSG("gpp::Events::Event::DIED_EVENT");
		input.setCurrent(gpp::Events::Event::DIED_EVENT);
	}
	// Revieved Event
	else if (e.key.keysym.sym == SDLK_r) {
		DEBUG_MSG("gpp::Events::Event::REVIVED_EVENT");
		input.setCurrent(gpp::Events::Event::REVIVED_EVENT);
	}
	// Running attack
	else if (e.key.keysym.sym == SDLK_z
		&&
		e.key.keysym.sym == SDLK_d
		||
		e.key.keysym.sym == SDLK_d
		&&
		e.key.keysym.sym == SDLK_z
		)
	{
		DEBUG_MSG("gpp::Events::Event::ATTACK_START");
		input.setCurrent(gpp::Events::Event::ATTACK_START_EVENT);
	}
	// Attack
	else if (e.key.keysym.sym == SDLK_z)
	{
		DEBUG_MSG("gpp::Events::Event::ATTACK_START_EVENT");
		input.setCurrent(gpp::Events::Event::ATTACK_START_EVENT);
	}
	// Running Throw attack
	else if (e.key.keysym.sym == SDLK_x
		&&
		e.key.keysym.sym == SDLK_d
		||
		e.key.keysym.sym == SDLK_d
		&&
		e.key.keysym.sym == SDLK_x
		)
	{
		DEBUG_MSG("gpp::Events::Event::THROW_START_EVENT");
		input.setCurrent(gpp::Events::Event::THROW_START_EVENT);
	}
	// Throw Attack
	else if (e.key.keysym.sym == SDLK_x)
	{
		DEBUG_MSG("gpp::Events::Event::THROW_START_EVENT");
		input.setCurrent(gpp::Events::Event::THROW_START_EVENT);
	}
	// Run Right
	else if (e.key.keysym.sym == SDLK_d)
	{
		DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
		input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
	}
	// Climb Up
	else if (e.key.keysym.sym == SDLK_w)
	{
		DEBUG_MSG("gpp::Events::Event::MOVE_UP_START_EVENT");
		input.setCurrent(gpp::Events::Event::MOVE_UP_START_EVENT);
	}
	// Climb Down
	else if (e.key.keysym.sym == SDLK_s)
	{
		DEBUG_MSG("gpp::Events::Event::MOVE_DOWN_START_EVENT");
		input.setCurrent(gpp::Events::Event::MOVE_DOWN_START_EVENT);
	}
	// Hit Bottom of Ladder Event
	else if (e.key.keysym.sym == SDLK_c)
	{
		DEBUG_MSG("gpp::Events::Event::HIT_LADDER_BOTTOM_EVENT");
		input.setCurrent(gpp::Events::Event::HIT_LADDER_BOTTOM_EVENT);
	}
	// Hit Top of Ladder Event
	else if (e.key.keysym.sym == SDLK_t)
	{
		DEBUG_MSG("gpp::Events::Event::HIT_LADDER_TOP_EVENT");
		input.setCurrent(gpp::Events::Event::HIT_LADDER_TOP_EVENT);
	}
	// Jump Run
	if (e.key.keysym.sym == SDLK_SPACE
		&&
		e.key.keysym.sym == SDLK_d
		||
		e.key.keysym.sym == SDLK_d
		&&
		e.key.keysym.sym == SDLK_SPACE
		)
	{
		DEBUG_MSG("gpp::Events::Event::JUMP_UP_EVENT");
		input.setCurrent(gpp::Events::Event::JUMP_UP_EVENT);
	}
	// Jump Event
	else if (e.key.keysym.sym == SDLK_SPACE)
	{
		DEBUG_MSG("gpp::Events::Event::JUMP_UP_EVENT");
		input.setCurrent(gpp::Events::Event::JUMP_UP_EVENT);
	}
	// Running Slide
	else if (e.key.keysym.sym == SDLK_s
		&&
		e.key.keysym.sym == SDLK_d
		||
		e.key.keysym.sym == SDLK_d
		&&
		e.key.keysym.sym == SDLK_s
		)
	{
		DEBUG_MSG("gpp::Events::Event::SLIDE_EVENT");
		input.setCurrent(gpp::Events::Event::SLIDE_EVENT);
	}
	// Hit Ground Event
	else if (e.key.keysym.sym == SDLK_h)
	{
		DEBUG_MSG("gpp::Events::Event::HIT_GROUND_EVENT");
		input.setCurrent(gpp::Events::Event::HIT_GROUND_EVENT);
	}
	// Jump Attack Event
	else if (e.key.keysym.sym == SDLK_h)
	{
		DEBUG_MSG("gpp::Events::Event::HIT_GROUND_EVENT");
		input.setCurrent(gpp::Events::Event::HIT_GROUND_EVENT);
	}
	// Jump Throw Attack Event
	else if (e.key.keysym.sym == SDLK_h)
	{
		DEBUG_MSG("gpp::Events::Event::HIT_GROUND_EVENT");
		input.setCurrent(gpp::Events::Event::HIT_GROUND_EVENT);
	}
}

void Game::processKeyRelease(SDL_Event& e)
{
	// Run and Stop Attack
	if (e.key.keysym.sym == SDLK_z
		&&
		e.key.keysym.sym == SDLK_d)
	{
		DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
		input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
	}
	// Stop Attack
	else if(e.key.keysym.sym == SDLK_z)
	{
		DEBUG_MSG("gpp::Events::Event::ATTACK_STOP_EVENT");
		input.setCurrent(gpp::Events::Event::ATTACK_STOP_EVENT);
	}
	// Run and Stop Throw Attack
	else if (e.key.keysym.sym == SDLK_x
		&&
		e.key.keysym.sym == SDLK_d)
	{
		DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
		input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
	}
	// Stop Throw Attack
	else if (e.key.keysym.sym == SDLK_x)
	{
		DEBUG_MSG("gpp::Events::Event::THROW_STOP_EVENT");
		input.setCurrent(gpp::Events::Event::THROW_STOP_EVENT);
	}
	// Stop Running Right
	else if (e.key.keysym.sym == SDLK_d)
	{
		DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_STOP_EVENT");
		input.setCurrent(gpp::Events::Event::RUN_RIGHT_STOP_EVENT);
	}
	// Stop Slide
	else if (e.key.keysym.sym == SDLK_s
		&&
		e.key.keysym.sym == SDLK_d)
	{
		DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
		input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
	}
	// Stop Moving Up
	else if (e.key.keysym.sym == SDLK_w)
	{
		DEBUG_MSG("gpp::Events::Event::MOVE_UP_STOP_EVENT");
		input.setCurrent(gpp::Events::Event::MOVE_UP_STOP_EVENT);
	}
	// Stop Moving Down
	else if (e.key.keysym.sym == SDLK_s)
	{
		DEBUG_MSG("gpp::Events::Event::MOVE_DOWN_STOP_EVENT");
		input.setCurrent(gpp::Events::Event::MOVE_DOWN_STOP_EVENT);
	}
}

void Game::update(float dt)
{
   // std::cout << "Updating" << std::endl;
   player.handleInput(input);
   player.move(m_velocity * dt);
   player.update(dt);
}

void Game::renderTexture(SDL_Texture* t_tex, TextureData t_texdata)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad;
    renderQuad.x = t_texdata.x;
    renderQuad.y = t_texdata.y;
    renderQuad.w = t_texdata.width;
    renderQuad.h = t_texdata.height;

    SDL_FRect fRenderQuad;
    fRenderQuad.x = player.m_pos.x;
    fRenderQuad.y = player.m_pos.y;
    fRenderQuad.w = t_texdata.width; 
    fRenderQuad.h = t_texdata.height;

    //Render to screen
    SDL_RenderCopyF(renderer, t_tex, &renderQuad, &fRenderQuad);
    SDL_RenderDrawRectF(renderer, &fRenderQuad);
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