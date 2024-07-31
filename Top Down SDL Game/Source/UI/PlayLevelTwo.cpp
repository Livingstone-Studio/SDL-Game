#include "PlayLevelTwo.h"
#include "../Application/Game.h"

PlayLevelTwo::PlayLevelTwo()
	: PlayButton()
{
	m_text_scaling = { 2,2 };
}

PlayLevelTwo::PlayLevelTwo(AnchorPosition anchorPoint, Transform animDES, Transform animOneSRC, Transform animTwoSRC)
	: PlayButton(anchorPoint, animDES, animOneSRC, animTwoSRC)
{
	m_text_scaling = { 4,1 };
}

void PlayLevelTwo::RenderUpdate(SDL_Renderer* renderer, Camera camera)
{
	if (m_render_initialized && !m_deletion && m_active)
	{
		Transform t = m_transform;

		t.scale = m_scale;

		m_gfx.RenderUpdate(renderer, camera.ConvertToUISpace(m_anchor_point, t));

		RenderText(renderer, camera, "Play Level Two");
	}
}

void PlayLevelTwo::PressButton()
{
	ScoreManager::SetLevel(LevelTwo);
	Game::Play();
}
