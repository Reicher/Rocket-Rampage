#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Content.h"
#include <math.h>

class Planet
{
public:
	Planet(Content *content, sf::RenderWindow *app, float pX, float pY, float size = 0);
	void draw();
	void getClosestSurfacePoint(float &x, float &y);
	float getMass();

	sf::CircleShape m_shape;
	sf::CircleShape m_atmosphere;

	float m_x, m_y;

private:

	sf::RenderWindow  *m_pApp;

};
