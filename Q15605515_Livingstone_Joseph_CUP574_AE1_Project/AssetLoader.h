#pragma once

#include <SDL_image.h>
#include <string>
#include <iostream>

using namespace std;
static class AssetLoader
{
public:

	static void Initialize(SDL_Renderer* renderer);

	static void Cleanup();

	static SDL_Texture* GetCharacterSheet(string name);

private:

	static SDL_Renderer* m_renderer;

	static SDL_Texture* LoadImage(SDL_Renderer* renderer, string filePath);

	static SDL_Texture* m_debug_sheet;

	static SDL_Texture* m_gobbie_spritesheet;
	static SDL_Texture* m_orc_spritesheet;
	static SDL_Texture* m_slime_spritesheet;

	static SDL_Texture* m_forgotten_plains_tileset;
	static SDL_Texture* m_forgotten_plains_tileset_props;
};