#include "Fuel.h"

Fuel::Fuel(const sf::Texture& fuelTexture,
		   const sf::Vector2f& initialPosition)
: m_fuelSprite(fuelTexture)
{
	m_fuelSprite.setRotation(rand() % 361 );
	m_fuelSprite.setPosition(initialPosition.x, initialPosition.y);
	m_fuelSprite.setOrigin(50.0, 50.0);
	m_fuelSprite.setScale(sf::Vector2f(0.5, 0.5));
}

void Fuel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_fuelSprite, states);
}

const sf::Vector2f& Fuel::getPosition() const
{
	return m_fuelSprite.getPosition();
}

