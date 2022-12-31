#include "ScoreManager.h"

#include <fstream>
#include <vector>

string ScoreManager::m_save_file = "Assets/SaveFile.txt";

int ScoreManager::m_score = 0;

int ScoreManager::m_one_high_score = 0;
int ScoreManager::m_two_high_score = 0;

bool ScoreManager::m_key = false;

CurrentLevel ScoreManager::m_current_level;

void ScoreManager::Initialize()
{
	ifstream file(m_save_file);

	vector<string> scoreFile;

	string fileText;

	while (getline(file, fileText))
	{
		scoreFile.push_back(fileText);
	}

	if (scoreFile.size() > 0) 
	{
		m_one_high_score = stoi(scoreFile[0]);
	}
	else 
	{
		m_one_high_score = 0;
	}

	if (scoreFile.size() > 1)
	{
		m_two_high_score = stoi(scoreFile[1]);
	}
	else
	{
		m_two_high_score = 0;
	}
}

void ScoreManager::InitLevel()
{
	m_score = 0;
	m_key = false;
}

void ScoreManager::AddScore(int score)
{
	m_score += score;

	switch (m_current_level) 
	{
	case LevelOne:
		if (m_score > m_one_high_score) m_one_high_score = m_score;
		break;
	case LevelTwo:
		if (m_score > m_two_high_score) m_two_high_score = m_score;
		break;
	}
}

void ScoreManager::SetHighScoreOne(int score)
{
	m_one_high_score = score;
}

int ScoreManager::GetHighScoreOne()
{
	return m_one_high_score;
}

void ScoreManager::SetHighScoreTwo(int score)
{
	m_two_high_score = score;
}

int ScoreManager::GetHighScoreTwo()
{
	return m_two_high_score;
}

void ScoreManager::ActivateKey()
{
	m_key = true;
}

bool ScoreManager::IsKeyActivate()
{
	return m_key;
}

void ScoreManager::Cleanup()
{
	ofstream outFile;

	outFile.open(m_save_file);

	outFile << m_one_high_score << endl;
	outFile << m_two_high_score << endl;

	outFile.close();
}
