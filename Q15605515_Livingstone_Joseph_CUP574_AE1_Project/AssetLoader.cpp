#include "AssetLoader.h"

SDL_Renderer* AssetLoader::m_renderer = nullptr;
SDL_Texture* AssetLoader::m_gobbie_spritesheet = nullptr;
SDL_Texture* AssetLoader::m_orc_spritesheet = nullptr;

void AssetLoader::Initialize(SDL_Renderer* renderer)
{
    m_renderer = renderer;
    m_gobbie_spritesheet = LoadImage(renderer, "Assets/SpriteSheets/Minifantasy_CreaturesGoblinAnimations+Shadows.png");
    m_orc_spritesheet = LoadImage(renderer, "Assets/SpriteSheets/Minifantasy_CreaturesWildOrcAnimations+Shadows.png");
}

void AssetLoader::Cleanup()
{
    if (m_gobbie_spritesheet != nullptr) SDL_DestroyTexture(m_gobbie_spritesheet);
    if (m_orc_spritesheet != nullptr) SDL_DestroyTexture(m_orc_spritesheet);
}

SDL_Texture* AssetLoader::GetCharacterSheet(string name)
{
    if (name == "Gobbie") return m_gobbie_spritesheet;
    else if (name == "Orc") return m_orc_spritesheet;

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
