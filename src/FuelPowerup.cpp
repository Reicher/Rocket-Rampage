#include "FuelPowerup.h"

#include <iostream>

FuelPowerup::FuelPowerup(Content *content, sf::RenderWindow *app, sf::Vector2<int> pos)
: m_pApp(app)
, m_sprite(content->m_fuelTex)
, takeFuel(content->m_takeFuelSound)
, m_taken(false)
{
	m_sprite.setRotation(rand() % 361 );
	m_sprite.setPosition(pos.x, pos.y);
	m_sprite.setOrigin(50.0, 50.0);
	m_sprite.setScale(sf::Vector2f(0.5, 0.5));
}

void FuelPowerup::draw() const
{
	if(!m_taken) // if not allready taken
		m_pApp->draw(m_sprite);

}

void FuelPowerup::take()
{
	m_taken = true;

	//sound of taking barrel
	takeFuel.play();
}

bool FuelPowerup::ReadyToBeRemoved() const
{
	return m_taken && (takeFuel.getStatus() == sf::Sound::Stopped);
}

