#include "FuelPowerup.h"

FuelPowerup::FuelPowerup(Content *contnent, sf::RenderWindow *app, sf::Vector2<int> pos)
: m_sprite(contnent->m_fuelTex)
, m_pApp(app)
{
	m_sprite.setRotation(rand() % 361 );
	m_sprite.setPosition(pos.x, pos.y);
	m_sprite.setOrigin(50.0, 50.0);
	m_sprite.setScale(sf::Vector2f(0.5, 0.5));
}

void FuelPowerup::draw()
{
	m_pApp->draw(m_sprite);
}

void FuelPowerup::take()
{

}
