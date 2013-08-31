#include "InfoBox.h"

InfoBox::InfoBox(sf::RenderWindow *App, Content *content, sf::Vector2f Pos)
: m_pApp(App)
, m_box(sf::Vector2f(500, 300))
{
	m_box.setPosition(Pos);
	m_box.setOutlineThickness(10);
	m_box.setOutlineColor(sf::Color(250, 150, 100));

	m_text.setFont(content->m_standardFont);
	m_text.setCharacterSize(40);
	m_text.setColor(sf::Color::Black);
	m_text.setPosition(Pos.x + 50, Pos.y + 10);

	setStart();
}

void InfoBox::setStart()
{

	m_text.setString("Rocket Rampage\n\nWAD - move around\nQE - rotate\n\n(Space to start)");
}

void InfoBox::setGameOver(int Score)
{
	std::stringstream ss;
	ss << Score;
	m_text.setString("Game Over!\n\nScore: " + ss.str() + "\n(Space to restart)");
}

void InfoBox::draw()
{
	m_pApp->draw(m_box);
	m_pApp->draw(m_text);
}
