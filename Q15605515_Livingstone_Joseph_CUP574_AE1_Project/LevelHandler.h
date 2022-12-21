#pragma once

#include "Structs.h"
#include "AssetLoader.h"
#include "Prop.h"

#include <string>
#include <vector>
#include <fstream>

static class LevelHandler
{
public:

	static vector<GameObject*> CreateLevel(string levelPath);

	static void EditLevel();

	static void CleanupLevel();

	static Vector2 GetBounds();

private:

	static vector<string> m_map;

	static Vector2 m_tile_scaling;
	static Vector2 m_tile_collider_scaling;

	static float m_environment_scale;

	static TileInfo m_plainsTile;
	static TileInfo m_grassTile;

	static TileInfo m_waterTiles[7];
	static TileInfo m_riverTiles[3];

	static TileInfo m_pathTiles[4];

};