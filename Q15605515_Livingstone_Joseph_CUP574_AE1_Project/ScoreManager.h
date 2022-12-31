#pragma once

#include "Structs.h"


enum CurrentLevel {
	LevelOne, LevelTwo
};

static class ScoreManager
{
public:

	static void Initialize();

	static void InitLevel();

	static void AddScore(int score);

	static void SetHighScoreOne(int score);
	static int GetHighScoreOne();

	static void SetHighScoreTwo(int score);
	static int GetHighScoreTwo();

	static int GetScore() { return m_score; }

	static void ActivateKey();
	static bool IsKeyActivate();

	static void Cleanup();

private:

	static string m_save_file;

	static CurrentLevel m_current_level;

	static bool m_key;

	static int m_score;

	static int m_one_high_score;
	static int m_two_high_score;

};