#include "Game.h"

#include "Camera.h"

GameState Game::m_game_state = SMainMenu;

bool Game::m_main_menu = true;

bool Game::m_menu_first_frame = true;

bool Game::m_run;
bool Game::m_debug;

Camera Game::m_camera;

SDL_Window* Game::m_window;
SDL_Renderer* Game::m_renderer;

Game::Game()
{
}

void Game::Execute() 
{
    Setup();

    AppLoop();

    Close();
}

void Game::GameExecute()
{

    GameSetup();

    GameLoop();

    GameClose();
}

void Game::Play()
{ 
    m_run = true;
    m_game_state = Gameplay;
}

void Game::ReturnToMenu()
{
    m_run = false;
    m_game_state = SMainMenu;
    m_menu_first_frame = true;
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

    if (Mix_Init(MIX_INIT_MP3) < 0) 
    {
        cout << "Failed to initialise SDL_Mixer. Error: " << Mix_GetError() << endl;
    }

    if (TTF_Init() < 0)
    {
        cout << "Failed to initialise SDL_TTF. Error: " << TTF_GetError() << endl;
    }

    m_main_menu = true;

    m_window = SDL_CreateWindow( WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);

    Input::Initialize();
    AssetLoader::Initialize(m_renderer);
    AudioManager::Initialize();
    ScoreManager::Initialize();
}

void Game::AppLoop()
{
    while (m_main_menu)
    {
        switch (m_game_state)
        {
        case SMainMenu:

            if (m_menu_first_frame) 
            {
                for (int i = 0; i < m_gameobjects.size(); i++)
                {
                    if (m_gameobjects[i] != nullptr)
                    {
                        m_gameobjects[i]->Delete();
                    }
                }

                m_gameobjects.clear();

                m_camera.SetCameraPosition({ 0,0 });
                m_camera.SetCameraSize({ 0.5f,0.5f });

                m_player_cast = nullptr;

                vector<GameObject*> t = LevelHandler::CreateLevel("Assets/LevelInfo/MainMenu.txt");

                m_gameobjects.insert(m_gameobjects.end(), t.begin(), t.end());

                m_menu_first_frame = false;
            }

            Input::Update();
            Time::Update();

            if (m_camera.GetCanvasState() != HowToPlay && m_camera.GetCanvasState() != LevelSelect) m_camera.SetCanvasState(MainMenu);

            FrameInit();

            for (int i = 0; i < m_gameobjects.size(); i++)
            {
                if (m_gameobjects[i] != nullptr)
                {
                    if (!m_gameobjects[i]->IsInitialized()) m_gameobjects[i]->Start();
                }
            }

            m_camera.Start();

            m_camera.RenderStart(m_renderer, m_gameobjects);

            InputHandler();

            int w, h;
            SDL_GetWindowSize(m_window, &w, &h);
            m_camera.Update({ (float)DEFAULT_WINDOW_WIDTH, (float)DEFAULT_WINDOW_HEIGHT }, { (float)w, (float)h });

            for (int i = 0; i < m_gameobjects.size(); i++)
            {
                if (m_gameobjects[i] != nullptr)
                {
                    m_gameobjects[i]->Update(Time::GetDeltaTime());
                }
            }

            RendererHandler();

            FrameCleanup();

            break;

        case Gameplay:

            GameExecute();

            break;
        }
    }
}

void Game::GameSetup()
{
    for (int i = 0; i < m_gameobjects.size(); i++)
    {
        if (m_gameobjects[i] != nullptr)
        {
            m_gameobjects[i]->Delete();
        }
    }

    m_gameobjects.clear();

    m_run = true;

    m_gameobjects.push_back(new Player({ 0, 0, 5, 5 }));
    
    m_player_cast = dynamic_cast<Player*>(m_gameobjects[0]);

    vector<GameObject*> t;

    switch (ScoreManager::GetLevel()) 
    {
    case LevelOne:
        t = LevelHandler::CreateLevel("Assets/LevelInfo/Level_One.txt");
        break;
    case LevelTwo:
        t = LevelHandler::CreateLevel("Assets/LevelInfo/Level_Two.txt");
        break;
    }

    m_gameobjects.insert(m_gameobjects.end(), t.begin(), t.end());

    for (int i = 0; i < m_gameobjects.size(); i++) 
    {
        Orc* orccast = dynamic_cast<Orc*>(m_gameobjects[i]);

        if (orccast != nullptr) orccast->SetTarget(m_player_cast);

        Slime* slimecast = dynamic_cast<Slime*>(m_gameobjects[i]);

        if (slimecast != nullptr) slimecast->SetTarget(m_player_cast);
    }

    m_camera.InitializePlayerHUD(m_player_cast);

    ScoreManager::InitLevel();

    m_camera.SetCanvasState(HUD);
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

    m_camera.Start();

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
    bool game_state = Input::EventHandler();

    m_main_menu = game_state;
    m_run = game_state;

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

    if (Input::GetKeyDown(SDL_SCANCODE_N) && m_debug && m_player_cast != nullptr)
    {
        m_player_cast->ToggleNoClip();
    }

    if (Input::GetKeyDown(SDL_SCANCODE_I) && m_debug)
    {
        SpawnOrc();
    }
    else if (Input::GetKeyDown(SDL_SCANCODE_O) && m_debug)
    {
        SpawnSlime();
    }
    else if (Input::GetKeyDown(SDL_SCANCODE_P) && m_debug)
    {
        KillEnemy();
    }

    if (m_player_cast != nullptr)
    {
        if (!m_player_cast->MarkedForDeletion()) m_player_cast->InputUpdate(Time::GetDeltaTime());
    }
}

void Game::EventHandler()
{
    int w, h;
    SDL_GetWindowSize(m_window, &w, &h);
    m_camera.Update( { (float)DEFAULT_WINDOW_WIDTH, (float)DEFAULT_WINDOW_HEIGHT }, { (float)w, (float)h });

    if (m_player_cast != nullptr) m_camera.Follow(m_player_cast, Time::GetDeltaTime());

    // Collision Update
    for (int j = 0; j < m_gameobjects.size(); j++)
    {
        if (m_gameobjects[j] != nullptr)
        {
            m_gameobjects[j]->CollisionCheck(m_gameobjects);
        }
    }

    // Update
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

    if (m_debug) m_camera.RenderDebug(m_renderer, m_gameobjects);

    m_camera.RenderUpdateUI(m_renderer, m_camera);

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);

    SDL_RenderPresent(m_renderer);
}

void Game::GameClose()
{
    for (int i = 0; i < m_gameobjects.size(); i++)
    {
        if (m_gameobjects[i] != nullptr)
        {
            delete m_gameobjects[i];
            m_gameobjects[i] = nullptr;
        }
    }

    m_gameobjects.clear();
}

void Game::Close()
{
    Input::Cleanup();
    AssetLoader::Cleanup();
    AudioManager::Cleanup();
    ScoreManager::Cleanup();

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

    TTF_Quit();

    IMG_Quit();

    SDL_Quit();

}

// DEBUG

void Game::SpawnOrc()
{
    m_gameobjects.push_back(new Orc({ 0, 0, 5, 5 }));
    Orc* cast = dynamic_cast<Orc*>(m_gameobjects[m_gameobjects.size() - 1]);

    if (cast != nullptr) cast->SetTarget(m_player_cast);
}

void Game::SpawnSlime()
{
    m_gameobjects.push_back(new Slime({ 0, 0, 5, 5 }));
    Slime* cast = dynamic_cast<Slime*>(m_gameobjects[m_gameobjects.size()-1]);

    if (cast != nullptr) cast->SetTarget(m_player_cast);
}

void Game::KillEnemy()
{
    Enemy* cast = dynamic_cast<Enemy*>(m_gameobjects[m_gameobjects.size()-1]);

    if (cast != nullptr && m_gameobjects.size() - 1 != 0) cast->Delete();
}

