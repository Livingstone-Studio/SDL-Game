#include "LevelCreator.h"

Vector2 LevelHandler::m_level_dimensions = { 0,0 };

vector<GameObject*> LevelHandler::CreateLevel(string levelPath)
{
    vector<GameObject*> t;

    ifstream file(levelPath);

    string fileText;

    int row = 0;
    while (getline(file, fileText)) 
    {
        for (int column = 0; column < fileText.size(); column++) 
        {
            switch (fileText[column])
            {
            case 'G':
                t.push_back(new Prop({(float)column,(float)row, 5, 5},"grass", -10, { "grass", {0,1,0.0f,0,false} , {-5,0,0.0f,0,false} }));
                break;
            case 'T':
                t.push_back(new Prop({ (float)column,(float)row, 5, 5 }, "grass", -10, { "grass", {0,1,0.0f,0,false} , {-5,0,0.0f,0,false} }));
                t.push_back(new Prop({ (float)column,(float)row, 5, 5 }, "tree", 10, { "tree", {1,1,0.0f,4,false} , {-5,0,0.0f,0,false} }));
                break;
            default:
                break;
            }

            m_level_dimensions.y = (float)column;
        }
        row++;
        m_level_dimensions.x = (float)row;
    }

    return t;
}

void LevelHandler::CleanupLevel()
{
}