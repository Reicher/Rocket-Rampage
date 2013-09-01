#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"

namespace sf {
class Texture;
}

class Fuel : public sf::Drawable
{
public:

	Fuel(const sf::Texture& fuelTexture, const sf::Vector2f& initialPosition);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	const sf::Vector2f& getPosition() const;

private:

	sf::Sprite m_fuelSprite;
};
