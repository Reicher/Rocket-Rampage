#include "FuelCollection.h"
#include <math.h>

FuelCollection::FuelCollection(const sf::Texture& fuelTexture, const sf::SoundBuffer& takeFuelSoundBuffer)
: m_fuelTexture(fuelTexture)
, m_takeFuelSound(takeFuelSoundBuffer)
, m_fuelList()
, m_threshold(50)
{
}

void FuelCollection::init()
{
	m_fuelList.clear();

	float distLayers = 1000;
	float radius = 1000;

	for (int layer = 1; layer < 10; ++layer)
	{
		radius += distLayers;

		for (float rad = 0; rad < 2*M_PI; rad += (800.0 / radius))
		{
			float x = (radius * cos(rad)) + (rand() % 400);
			float y = (radius * sin(rad)) + (rand() % 400);;

			m_fuelList.push_back(Fuel(m_fuelTexture, sf::Vector2f(x, y)));
		}
	}
}

bool FuelCollection::isAnyFuelHit(const sf::Vector2f& rocketLocation)
{
	for (FuelListIter it = m_fuelList.begin(), itEnd = m_fuelList.end();
		 it != itEnd;
		 ++it)
	{
		if (isFuelHit(rocketLocation, it->getPosition()))
		{
			m_fuelList.erase(it);
			m_takeFuelSound.play();
			return true;
		}
	}

	return false;
}

void FuelCollection::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (FuelListConstIter it = m_fuelList.begin(), itEnd = m_fuelList.end();
		 it != itEnd;
		 ++it)
	{
		target.draw(*it, states);
	}
}

bool FuelCollection::isFuelHit(const sf::Vector2f& rocketLocation, const sf::Vector2f& fuelLocation) const
{
	const double distance = sqrt(pow(rocketLocation.x - fuelLocation.x , 2) + pow(rocketLocation.y - fuelLocation.y, 2));
	return distance <= m_threshold;
}

