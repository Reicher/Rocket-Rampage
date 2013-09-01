#pragma once

#include <list>
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Audio/Sound.hpp"
#include "Fuel.h"

namespace sf {
class SoundBuffer;
}

class FuelCollection : public sf::Drawable
{
public:

	FuelCollection(const sf::Texture& fuelTexture, const sf::SoundBuffer& takeFuelSoundBuffer);

	void init();

	bool isAnyFuelHit(const sf::Vector2f& rocketLocation);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

	bool isFuelHit(const sf::Vector2f& rocketLocation, const sf::Vector2f& fuelLocation) const;

	sf::Texture m_fuelTexture;

	sf::Sound m_takeFuelSound;

	typedef std::list<Fuel> FuelList;
	typedef FuelList::iterator FuelListIter;
	typedef FuelList::const_iterator FuelListConstIter;
	FuelList m_fuelList;

	float m_threshold;
};
