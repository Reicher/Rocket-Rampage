#include "Planet.h"
#include "iostream"

using namespace std;

Planet::Planet(const sf::Vector2f& initialPosition, float size)
: m_x(initialPosition.x)
, m_y(initialPosition.y)
, m_textured(false)
, m_size(size)
, m_smooth(5)
{
	m_shape.setRadius(m_size);
	m_shape.setOrigin(m_size, m_size);

	m_shape.setFillColor(sf::Color(180, 140, 100));
	m_shape.setOutlineThickness(-10);
	m_shape.setOutlineColor(sf::Color(180, 255, 200));

	m_shape.setPointCount(static_cast<int>(m_size) / m_smooth);

	initAtmosphere();
}

Planet::Planet(const sf::Texture& planetTexture, const sf::Vector2f& initialPosition, float size)
: m_x(initialPosition.x)
, m_y(initialPosition.y)
, m_sprite(planetTexture)
, m_textured(true)
, m_size(size)
, m_smooth(5)
{
	sf::Vector2f scale;
	scale.x = m_size / ( m_sprite.getGlobalBounds().width/2);
	scale.y = m_size / ( m_sprite.getGlobalBounds().height/2);

	m_sprite.setScale( scale );
	m_sprite.setOrigin(0, 0);
	m_sprite.setPosition(-m_size, -m_size);

	initAtmosphere();
}

void Planet::initAtmosphere()
{
	float thickness = 150;

	m_atmosphere.setRadius(m_size + thickness);
	m_atmosphere.setOrigin(m_size + thickness, m_size + thickness);
	m_atmosphere.setFillColor(sf::Color(100, 100, 200));
	m_atmosphere.setPointCount(static_cast<int>(m_size) / m_smooth);


}

void Planet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_atmosphere, states);

	if(m_textured)
		target.draw(m_sprite, states);
	else
		target.draw(m_shape, states);
}

float Planet::getMass() const
{
	return m_size * 10;
}

float Planet::getSize() const
{
	return m_size;
}
