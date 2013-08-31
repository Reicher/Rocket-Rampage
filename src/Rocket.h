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

	void fillFuel(sf::Time fuel);
	void stopAll();

	sf::Sprite m_mainSprite;
	sf::Time m_fuelSec;

	float m_x, m_y;
	float m_r;

private:
	void handleInput(float dt);
	void handleGravity(float dt, Planet *gravitySource);

	sf::RenderWindow  *m_pApp;

	float m_vx, m_vy;
	float m_ax, m_ay;
	float m_fx, m_fy;

	//Rotation
	float m_vr, m_ar, m_fr;

	float m_speedMulti;
	float m_mass; //not used?

	sf::Sound thrust;
};
