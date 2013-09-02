#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/CircleShape.hpp"

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"

#include <math.h>

namespace sf {
class Texture;
}


class Planet: public sf::Drawable
{
public:
	Planet(const sf::Vector2f& initialPosition, float size = 0);
	Planet(const sf::Texture& planetTexture, const sf::Vector2f& initialPosition, float size = 0);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	float getMass() const;
	float getSize() const;
	sf::Vector2f getPosition() const;

private:
	void initAtmosphere();

	float m_x, m_y;

	sf::CircleShape m_shape;
	sf::CircleShape m_atmosphere;

	sf::Sprite 		m_sprite;

	bool m_textured;
	float m_size;
	int m_smooth;

};
