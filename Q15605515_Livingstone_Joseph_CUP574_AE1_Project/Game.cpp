#include "Game.h"

bool Game::m_run;

SDL_Window* Game::m_window;
SDL_Renderer* Game::m_renderer;

Game::Game()
{
}

int Game::Execute()
{
    Setup();

    GameLoop();

    Close();

    return 0;
}

void Game::Setup()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
    {
        // Error
        cout << "Failed to intialise SDL. Error: " << SDL_GetError() << endl;
    }

    if (IMG_Init(IMG_INIT_PNG) < 0) 
    {
        // Error
        cout << "Failed to intialise SDL_Image. Error: " << SDL_GetError() << endl;
    }

    m_run = true;

    Input::Initialize();

    m_window = SDL_CreateWindow( WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);

    AssetLoader::Initialize(m_renderer);

    m_gameobjects.push_back(new Player({ 0, 0, 5, 5 }));
    
    m_player_cast = static_cast<Player*>(m_gameobjects[0]);

}

void Game::FrameInit()
{
    for (int i = 0; i < m_gameobjects.size(); i++)
    {
        if (m_gameobjects[i] != nullptr)
        {
            if (!m_gameobjects[i]->IsInitialized()) m_gameobjects[i]->Start();
        }
    }

    m_camera.RenderStart(m_renderer, m_gameobjects);
}

void Game::GameLoop()
{
    while (m_run) 
    {
        FrameInit();

        Input::Update();
        Time::Update();

        InputHandler();

        EventHandler();

        RendererHandler();

        FrameCleanup();
    }
}

void Game::FrameCleanup()
{
    for (int i = 0; i < m_gameobjects.size(); i++)
    {
        if (m_gameobjects[i] != nullptr)
        {
            if (m_gameobjects[i]->MarkedForDeletion())
            {
                delete m_gameobjects[i];

                m_gameobjects[i] = nullptr;

                vector<GameObject*>::iterator it = m_gameobjects.begin() + i;

                m_gameobjects.erase(it);
            }
        }
        else if (m_gameobjects[i] == nullptr)
        {
            vector<GameObject*>::iterator it = m_gameobjects.begin() + i;

            m_gameobjects.erase(it);
        }
    }
}

void Game::InputHandler()
{
    m_run = Input::EventHandler();
    
    if (Input::GetKeyDown(SDL_SCANCODE_F11) && !m_fullscreen)
    {
        SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
        m_fullscreen = true;
    }
    else if (Input::GetKeyDown(SDL_SCANCODE_F11) && m_fullscreen)
    {
        SDL_SetWindowFullscreen(m_window, 0);
        m_fullscreen = false;
    }

    if (Input::GetKeyDown(SDL_SCANCODE_O))
    {
        SpawnEnemy();
    }
    else if (Input::GetKeyDown(SDL_SCANCODE_P))
    {
        KillEnemy();
    }

    if (m_player_cast != nullptr) m_player_cast->InputUpdate(Time::GetDeltaTime());
}

void Game::EventHandler()
{
    int w, h;
    SDL_GetWindowSize(m_window, &w, &h);
    m_camera.Update({ (float)w, (float)h });

    m_camera.Follow(m_gameobjects[0], Time::GetDeltaTime());

    for (int i = 0; i < m_gameobjects.size(); i++)
    {
        if (m_gameobjects[i] != nullptr)
        {
            m_gameobjects[i]->Update(Time::GetDeltaTime());
        }
    }
}

void Game::RendererHandler()
{
    SDL_RenderClear(m_renderer);

    m_camera.RenderUpdate(m_renderer, m_gameobjects);

    SDL_SetRenderDrawColor(m_renderer, 113, 232, 2, 155);

    SDL_RenderPresent(m_renderer);
}

void Game::Close()
{
    Input::Cleanup();
    AssetLoader::Cleanup();

    for (int i = 0; i < m_gameobjects.size(); i++)
    {
        if (m_gameobjects[i] != nullptr)
        {
            delete m_gameobjects[i];
            m_gameobjects[i] = nullptr;
        }
    }

    m_gameobjects.clear();

    SDL_DestroyWindow(m_window);

    m_window = nullptr;

    SDL_DestroyRenderer(m_renderer);

    m_renderer = nullptr;

    SDL_Quit();

}

// TEMP
void Game::SpawnEnemy()
{
    m_gameobjects.push_back(new Enemy({ 20, -10, 5, 5 }));
    Enemy* cast = static_cast<Enemy*>(m_gameobjects[m_gameobjects.size()-1]);

    if (cast != nullptr) cast->SetTarget(m_gameobjects[0]);
}

void Game::KillEnemy()
{
    Enemy* cast = static_cast<Enemy*>(m_gameobjects[m_gameobjects.size()-1]);

    if (cast != nullptr && m_gameobjects.size() - 1 != 0) cast->Delete();
}
