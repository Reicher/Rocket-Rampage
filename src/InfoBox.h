#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>

#include "Content.h"

class InfoBox
{
public:
	InfoBox(sf::RenderWindow *App, Content *content, sf::Vector2f Pos);
	void draw();

	void setStart();
	void setGameOver(int Score);

private:
	sf::RenderWindow *m_pApp;

	sf::RectangleShape m_box;
	sf::Text m_text;

};
