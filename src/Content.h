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

	sf::Texture  		m_rocketTex;
	sf::SoundBuffer		m_testSound;
	sf::Music 	 		m_testMusic;
};
