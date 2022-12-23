#include "LevelHandler.h"

vector<string> LevelHandler::m_map;
float LevelHandler::m_environment_scale{ 2 };
Vector2 LevelHandler::m_tile_scaling{ 0.65f, 0.53f };
Vector2 LevelHandler::m_tile_collider_scaling{ 0.25f, 0.25f };

TileInfo LevelHandler::m_plainsTile{ "grass", -10, { "plains", {0,1,0.0f,0,false} , {-5,0,0.0f,0,false}, { 0,0 } }, false };
TileInfo LevelHandler::m_grassTile{ "grass", -10, { "grass", {0,1,0.0f,1,false} , {-5,0,0.0f,0,false}, { 0,0 } }, false };

TileInfo LevelHandler::m_pathTiles[4] = {
    { "grass", -10, { "path", {1,1,0.0f,0,false} , {-5,0,0.0f,0,false}, { 0,0 } }, false },
    { "grass", -10, { "path", {1,1,0.0f,1,false} , {-5,0,0.0f,0,false}, { 0,0 } }, false },
    { "grass", -10, { "path", {2,1,0.0f,0,false} , {-5,0,0.0f,0,false}, { 0,0 } }, false },
    { "grass", -10, { "path", {2,1,0.0f,1,false} , {-5,0,0.0f,0,false}, { 0,0 } }, false }
};

TileInfo LevelHandler::m_waterTiles[7] = { 
    { "grass", -10, { "water", {3,1,0.0f,0,false} , {-5,0,0.0f,0,false}, { 0,0 } }, false },
    { "grass", -10, { "water", {3,1,0.0f,1,false} , {-5,0,0.0f,0,false}, { 0,0 } }, false },
    { "grass", -10, { "water", {4,1,0.0f,0,false} , {-5,0,0.0f,0,false}, { 0,0 } }, false },
    { "grass", -10, { "water", {4,1,0.0f,1,false} , {-5,0,0.0f,0,false}, { 0,0 } }, false },
    { "grass", -10, { "water", {0,1,0.0f,2,false} , {-5,0,0.0f,0,false}, { 0,0 } }, false },
    { "grass", -10, { "water", {0,1,0.0f,3,false} , {-5,0,0.0f,0,false}, { 0,0 } }, false },
    { "grass", -10, { "water", {0,1,0.0f,4,false} , {-5,0,0.0f,0,false}, { 0,0 } }, false }
};

TileInfo LevelHandler::m_riverTiles[3] = { 
    { "grass", -10, { "river", {5,4,5.0f,0,true} , {-5,0,0.0f,0,false}, { 0,0 } }, false },
    { "grass", -10, { "river", {6,4,5.0f,0,true} , {-5,0,0.0f,0,false}, { 0,0 } }, false },
    { "grass", -10, { "river", {7,4,5.0f,0,true} , {-5,0,0.0f,0,false}, { 0,0 } }, false }
};

vector<GameObject*> LevelHandler::CreateLevel(string levelPath)
{
    vector<GameObject*> t;

    ifstream file(levelPath);

    string fileText;

    while (getline(file, fileText)) 
    {
        m_map.push_back(fileText);
    }

    for (int r = 0; r < m_map.size(); r++)
    {
        for (int c = 0; c < m_map[r].length(); c++)
        {
            Transform transform = { ((float)c - m_map[r].length() / 2) * (m_environment_scale * m_tile_scaling.x),
                ((float)r - m_map.size()/2) * (m_environment_scale * -m_tile_scaling.y),
                m_environment_scale, m_environment_scale };

            switch (m_map[r][c])
            {
            case 'P':
                t.push_back(
                    new Prop( transform , m_plainsTile ));
                break;
            case 'G':
                t.push_back(
                    new Prop( transform , m_grassTile));
                break;



            case 'I':
                t.push_back(
                    new Prop( transform ,  m_pathTiles[0]));
                break;
            case 'O':
                t.push_back(
                    new Prop( transform , m_pathTiles[1]));
                break;
            case 'J':
                t.push_back(
                    new Prop( transform ,  m_pathTiles[2]));
                break;
            case 'K':
                t.push_back(
                    new Prop( transform , m_pathTiles[3]));
                break;



            case 'Z':
                t.push_back(
                    new Prop( transform, m_waterTiles[0], true, m_tile_collider_scaling));
                break;
            case 'X':
                t.push_back(
                    new Prop(transform, m_waterTiles[1], true, m_tile_collider_scaling));
                break;
            case 'C':
                t.push_back(
                    new Prop(transform, m_waterTiles[2], true, m_tile_collider_scaling));
                break;
            case 'V':
                t.push_back(
                    new Prop(transform, m_waterTiles[3], true, m_tile_collider_scaling));
                break;
            case 'A':
                t.push_back(
                    new Prop(transform, m_waterTiles[4], true, m_tile_collider_scaling));
                break;
            case 'S':
                t.push_back(
                    new Prop(transform, m_waterTiles[5], true, m_tile_collider_scaling));
                break;
            case 'D':
                t.push_back(
                    new Prop(transform, m_waterTiles[6], true, m_tile_collider_scaling));
                break;



            case 'B':
                t.push_back(
                    new Prop(transform, m_riverTiles[0], true, m_tile_collider_scaling));
                break;
            case 'N':
                t.push_back(
                    new Prop(transform, m_riverTiles[1], true, m_tile_collider_scaling));
                break;
            case 'M':
                t.push_back(
                    new Prop(transform, m_riverTiles[2], true, m_tile_collider_scaling));
                break;



            case 'T':
                t.push_back(
                    new Prop(transform, m_plainsTile));
                
                t.push_back(new Prop({ transform.position , { m_environment_scale * 2, m_environment_scale * 2 } },
                    "tree", 0, { "tree", {0,1,0.0f,0,false} , {1,1,0.0f,0,false}, { 0,0.5f } }, true, false, { 0.075f, 0.05f }));
                break;
            default:
                break;
            }
        }
    }

    return t;
}

void LevelHandler::EditLevel()
{

}

void LevelHandler::CleanupLevel()
{
}

Vector2 LevelHandler::GetBounds()
{
    if (m_map.size() > 0) return { (float)m_map.size(), (float)m_map[0].length() };
    else return { 0,0 };
}