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

	static void CleanupLevel();

private:

	static Vector2 m_level_dimensions;
};