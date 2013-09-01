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

	sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f pos);

	sf::Sprite m_mainSprite;
	sf::Time m_fuelSec;

	float m_r;

private:
	void handleInput(float dt);
	void handleGravity(float dt, Planet *gravitySource);
	bool touchDown(Planet *gravitySource);
	void slowdown(float dt);

	sf::RenderWindow  *m_pApp;


	sf::Vector2f m_p;
	sf::Vector2f m_v;
	sf::Vector2f m_a;
	sf::Vector2f m_f;

	//Rotation
	float m_vr, m_ar, m_fr;

	float m_speedMulti;
	float m_mass; //not used?

	sf::Sound thrust;

	bool m_slowdown;
};
