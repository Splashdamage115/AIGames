#include "AnimatedSprite.h"
#include "Game.h"

void AnimatedSprite::update()
{
	m_currentFrameTime -= Game::deltaTime;

	if (m_currentFrameTime <= 0.f)
	{
		m_currentFrameTime = m_waitTimeBetweenFrames;
		m_selectedRegion++;
		if (m_selectedRegion >= static_cast<int>(m_renderRegions.size()))
		{
			m_selectedRegion = 0;
		}
		m_sprite.setTextureRect(m_renderRegions.at(m_selectedRegion));
	}
}
