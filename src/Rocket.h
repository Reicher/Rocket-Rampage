#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Content.h"

class Rocket
{
public:
	Rocket(Content *content, sf::RenderWindow *app);
	void draw();
	void update(float dt);

private:
	void handleInput();

	sf::Sprite m_mainSprite;
	sf::RenderWindow  *m_pApp;

	float m_x, m_y;
	float m_vx, m_vy;
	float m_ax, m_ay;
	float m_fx, m_fy;

	float m_speedMulti;

	float m_mass; //not used?
};
