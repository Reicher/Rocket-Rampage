#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include "Content.h"
#include "Planet.h"

class Rocket
{
public:
	Rocket(Content *content, sf::RenderWindow *app);
	void draw();
	void update(float dt, Planet *gravitySource);

	float m_x, m_y;
	sf::Sprite m_mainSprite;

private:
	void handleInput(float dt);
	void handleGravity(float dt, Planet *gravitySource);
	bool handleLlanding(Planet *gravitySource);

	sf::RenderWindow  *m_pApp;

	float m_vx, m_vy;
	float m_ax, m_ay;
	float m_fx, m_fy;

	float m_speedMulti;

	bool m_landed;

	sf::Time m_fuelSec;
	float m_mass; //not used?
};
