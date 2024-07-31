#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer()
	: m_srcRect{ 0, 0, BASE_IMG_WIDTH, BASE_IMG_HEIGHT }
{
}

SpriteRenderer::SpriteRenderer(SDL_Renderer* renderer, string imgFile)
	: m_srcRect{ 0, 0, BASE_IMG_WIDTH, BASE_IMG_HEIGHT }
{
	SetSpriteSheet(renderer, imgFile);
}

void SpriteRenderer::SetSpriteSheet(SDL_Renderer* renderer, string imgFile)
{ 
	m_spritesheet = AssetLoader::LoadImage(renderer, imgFile);

	if (m_spritesheet) 
	{
		SDL_QueryTexture(m_spritesheet, NULL, NULL, &m_spritesheetWidth, &m_spritesheetHeight);
	}

}

SDL_Texture* SpriteRenderer::GetSpriteSheet()
{
	return m_spritesheet;
}

void SpriteRenderer::SetSprite(int  row, int column)
{
	if (!m_spritesheet)
	{
		cout << "Couldn't set sprite as no spritesheet." << endl;
		return;
	}

	if (column >= 0 && column < GetTotalSheetColumns()) 
	{
		m_currentColumn = column;
		m_srcRect.x = m_currentColumn * BASE_IMG_WIDTH;
	}
	if (row >= 0 && row < GetTotalSheetRows())
	{
		m_currentRow = row;
		m_srcRect.y = m_currentRow * BASE_IMG_HEIGHT;
	}

	m_srcRect.w = BASE_IMG_WIDTH;
	m_srcRect.h = BASE_IMG_HEIGHT;
}

void SpriteRenderer::SetDesRect(float x, float y, float xScale, float yScale)
{ 
	m_desRect.x = x; 
	m_desRect.y = y; 
	m_desRect.w = BASE_IMG_WIDTH * xScale; 
	m_desRect.h = BASE_IMG_HEIGHT * yScale;
}

void SpriteRenderer::Update()
{
	m_animTimer += Time::GetDeltaTime();

	if (m_animTimer >= 0.1f) 
	{
		if (m_currentColumn + 1 >= GetTotalSheetColumns()) 
		{
			m_currentColumn = 0;
		}

		SetSprite(m_currentRow, m_currentColumn+1);

		m_animTimer = 0.0f;
	}


	if (Input::GetKey(SDL_SCANCODE_W))
	{
		switch (m_currentRow)
		{
		case 0:
			m_currentRow = 2;
			break;
		case 1:
			m_currentRow = 3;
			break;
		case 2:
			m_currentRow = 2;
			break;
		case 3:
			m_currentRow = 3;
			break;
		}
		SetSprite(m_currentRow, m_currentColumn);
	}
	if (Input::GetKey(SDL_SCANCODE_S))
	{
		switch (m_currentRow)
		{
		case 0:
			m_currentRow = 0;
			break;
		case 1:
			m_currentRow = 1;
			break;
		case 2:
			m_currentRow = 0;
			break;
		case 3:
			m_currentRow = 1;
			break;
		}
		SetSprite(m_currentRow, m_currentColumn);
	}
	if (Input::GetKey(SDL_SCANCODE_A))
	{
		switch (m_currentRow)
		{
		case 0:
			m_currentRow = 1;
			break;
		case 1:
			m_currentRow = 1;
			break;
		case 2:
			m_currentRow = 3;
			break;
		case 3:
			m_currentRow = 3;
			break;
		}
		SetSprite(m_currentRow, m_currentColumn);
	}
	if (Input::GetKey(SDL_SCANCODE_D))
	{
		switch (m_currentRow) 
		{
		case 0:
			m_currentRow = 0;
			break;
		case 1:
			m_currentRow = 0;
			break;
		case 2:
			m_currentRow = 2;
			break;
		case 3:
			m_currentRow = 2;
			break;
		}
		SetSprite(m_currentRow, m_currentColumn);
	}

	if (!(Input::GetKey(SDL_SCANCODE_W) || Input::GetKey(SDL_SCANCODE_S) || Input::GetKey(SDL_SCANCODE_A) || Input::GetKey(SDL_SCANCODE_D))) 
	{
		SetSprite(m_currentRow, 0);
	}

}

int SpriteRenderer::GetTotalSheetRows() 
{
	return m_spritesheetHeight / BASE_IMG_HEIGHT;
}

int SpriteRenderer::GetTotalSheetColumns()
{
	return m_spritesheetWidth / BASE_IMG_WIDTH;
}