#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Content
{
public:
	Content();
	void loadTextures();
	void loadSounds();
	void loadMusic();
	void loadFonts();

	sf::Texture  		m_rocketTex;
	sf::Texture  		m_fuelTex;

	sf::SoundBuffer	 	m_takeFuelSound;
	sf::SoundBuffer	 	m_thrustSound;

	sf::Music 	 		m_mainTheme;

	sf::Font			m_standardFont;
};
