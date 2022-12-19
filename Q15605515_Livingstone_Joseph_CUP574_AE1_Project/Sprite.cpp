#include "Sprite.h"

Sprite::Sprite()
	: m_srcRect{ 0, 0, BASE_SPRITE_WIDTH, BASE_SPRITE_HEIGHT }
{
}

Sprite::Sprite(SDL_Renderer* renderer, string imgFile)
	: m_srcRect{ 0, 0, BASE_SPRITE_WIDTH, BASE_SPRITE_HEIGHT }
{
	SetSprite(renderer, imgFile);
}

Sprite::Sprite(SDL_Renderer* renderer, string imgFile, Vector2 srcPos)
	: m_srcRect{ (int)srcPos.x, (int)srcPos.y, BASE_SPRITE_WIDTH, BASE_SPRITE_HEIGHT }
{
	SetSprite(renderer, imgFile);
}

Sprite::~Sprite()
{
	if (m_sprite != nullptr) 
	{
		m_sprite = nullptr;
	}
}

void Sprite::SetSprite()
{
	m_sprite = AssetLoader::GetCharacterSheet(m_name);

	m_srcRect.w = BASE_SPRITE_WIDTH;
	m_srcRect.h = BASE_SPRITE_HEIGHT;

	if (m_sprite)
	{
		SDL_QueryTexture(m_sprite, NULL, NULL, &imageWidth, &imageHeight);
	}
	else
	{
		cout << "Image not set for texture query." << endl;
	}
}

void Sprite::SetSprite(SDL_Renderer* renderer, string name)
{
	m_name = name;
	m_sprite = AssetLoader::GetCharacterSheet(m_name);

	m_srcRect.w = BASE_SPRITE_WIDTH;
	m_srcRect.h = BASE_SPRITE_HEIGHT;

	if (m_sprite)
	{
		SDL_QueryTexture(m_sprite, NULL, NULL, &imageWidth, &imageHeight);
	}
	else 
	{
		cout << "Image not set for texture query." << endl;
	}
}

void Sprite::SetSprite(SDL_Renderer* renderer, string name, Vector2 srcPos)
{
	m_name = name;
	m_sprite = AssetLoader::GetCharacterSheet(m_name);

	m_srcRect.w = BASE_SPRITE_WIDTH;
	m_srcRect.h = BASE_SPRITE_HEIGHT;

	if (m_sprite)
	{
		SDL_QueryTexture(m_sprite, NULL, NULL, &imageWidth, &imageHeight);
	}
	else
	{
		cout << "Image not set for texture query." << endl;
	}
}

SDL_Texture* Sprite::GetSpriteTexture()
{
	if (m_sprite == nullptr) 
	{
		SetSprite();
	}

	return m_sprite;
}

void Sprite::SetDesRect(float x, float y, float xScale, float yScale)
{
	m_desRect.w = BASE_SPRITE_WIDTH * xScale;
	m_desRect.h = BASE_SPRITE_HEIGHT * yScale;
	m_desRect.x = x - m_desRect.w/2;
	m_desRect.y = y - m_desRect.h/2;
}

void Sprite::SetDesRect(Vector2 position, float xScale, float yScale)
{
	SetDesRect(position.x, position.y, xScale, yScale);
}

void Sprite::SetDesRect(float x, float y, Vector2 scale)
{
	SetDesRect(x, y, scale.x, scale.y);
}

void Sprite::SetDesRect(Vector2 position, Vector2 scale)
{
	SetDesRect(position.x, position.y, scale.x, scale.y);
}

void Sprite::SetSrcRect(Vector2 position)
{
	m_srcRect.x = position.x;
	m_srcRect.y = position.y;
	m_srcRect.w = BASE_SPRITE_WIDTH;
	m_srcRect.h = BASE_SPRITE_HEIGHT;
}

void Sprite::Update()
{
}