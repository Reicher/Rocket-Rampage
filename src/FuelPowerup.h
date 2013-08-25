#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Content.h"
#include <math.h>
#include <cstdlib>

class FuelPowerup
{
public:
	FuelPowerup(Content *contnent, sf::RenderWindow *app, sf::Vector2<int> pos);
	void take();
	void draw();
	sf::Vector2<float> getPos() { return m_sprite.getPosition(); }
private:
	sf::Sprite m_sprite;
	sf::RenderWindow *m_pApp;
};