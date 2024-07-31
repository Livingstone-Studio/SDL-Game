#include "AssetLoader.h"

TTF_Font* AssetLoader::m_retro = nullptr;

SDL_Renderer* AssetLoader::m_renderer = nullptr;

SDL_Texture* AssetLoader::m_debug_sheet = nullptr;

SDL_Texture* AssetLoader::m_gobbie_spritesheet = nullptr;
SDL_Texture* AssetLoader::m_orc_spritesheet = nullptr;
SDL_Texture* AssetLoader::m_slime_spritesheet = nullptr;

SDL_Texture* AssetLoader::m_forgotten_plains_tileset = nullptr;
SDL_Texture* AssetLoader::m_forgotten_plains_tileset_props = nullptr;

SDL_Texture* AssetLoader::m_collectables_spritesheet = nullptr;

SDL_Texture* AssetLoader::m_ui_bars = nullptr;

void AssetLoader::Initialize(SDL_Renderer* renderer)
{
    m_renderer = renderer;
    
    m_retro = TTF_OpenFont("Assets/Fonts/retro/retro.ttf", 32);

    if (m_retro == nullptr) cout << "TTF failed to load font. Error: " << TTF_GetError() << endl;

    m_debug_sheet = LoadImage(renderer, "Assets/Debug/DebugShapes.png");
    
    m_gobbie_spritesheet = LoadImage(renderer, "Assets/SpriteSheets/Minifantasy_CreaturesGoblinAnimations+Shadows.png");
    m_orc_spritesheet = LoadImage(renderer, "Assets/SpriteSheets/Minifantasy_CreaturesWildOrcAnimations+Shadows.png");
    m_slime_spritesheet = LoadImage(renderer, "Assets/SpriteSheets/Minifantasy_CreaturesBlueSlimeAnimations+Shadows.png");
    m_collectables_spritesheet = LoadImage(renderer, "Assets/SpriteSheets/Minifantasy_FarmSeedsAndCrops.png");

    m_forgotten_plains_tileset = LoadImage(renderer, "Assets/Tilesets/Minifantasy_ForgottenPlainsTiles.png");
    m_forgotten_plains_tileset_props = LoadImage(renderer, "Assets/Tilesets/Minifantasy_ForgottenPlainsProps.png");

    m_ui_bars = LoadImage(renderer, "Assets/UI/Minifantasy_GuiBars.png");

}

void AssetLoader::Cleanup()
{
    if (m_retro != nullptr) TTF_CloseFont(m_retro);

    if (m_gobbie_spritesheet != nullptr) SDL_DestroyTexture(m_gobbie_spritesheet);
    if (m_orc_spritesheet != nullptr) SDL_DestroyTexture(m_orc_spritesheet);
    if (m_slime_spritesheet != nullptr) SDL_DestroyTexture(m_slime_spritesheet);

    if (m_forgotten_plains_tileset != nullptr) SDL_DestroyTexture(m_forgotten_plains_tileset);
    if (m_forgotten_plains_tileset_props != nullptr) SDL_DestroyTexture(m_forgotten_plains_tileset_props);

    if (m_collectables_spritesheet != nullptr) SDL_DestroyTexture(m_collectables_spritesheet);

    if (m_ui_bars != nullptr) SDL_DestroyTexture(m_ui_bars);

    if (m_debug_sheet != nullptr) SDL_DestroyTexture(m_debug_sheet);

}

SDL_Texture* AssetLoader::GetCharacterSheet(string name)
{
    if (name == "Gobbie") return m_gobbie_spritesheet;
    else if (name == "Orc") return m_orc_spritesheet;
    else if (name == "Slime") return m_slime_spritesheet;
    else if (name == "grass") return m_forgotten_plains_tileset;
    else if (name == "tree") return m_forgotten_plains_tileset_props;
    else if (name == "Collectables") return m_collectables_spritesheet;
    else if (name == "UIBars") return m_ui_bars;
    else if (name == "Debug") return m_debug_sheet;
    else cout << "No Sheet Found" << endl;

    if (m_collectables_spritesheet == nullptr) cout << name << endl;

    return nullptr;
}

SDL_Texture* AssetLoader::LoadImage(SDL_Renderer* renderer, string filePath)
{
    SDL_Texture* loadedTexture = SDL_CreateTextureFromSurface(renderer, IMG_Load(filePath.c_str()));

    if (!loadedTexture) 
    {
        cout << "Failed to load file on path: " << filePath << endl;
    }

    return loadedTexture;
}