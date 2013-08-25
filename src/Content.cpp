#include "Content.h"

Content::Content()
{
	loadTextures();
	loadSounds();
	loadMusic();
}

void Content::loadTextures()
{
	m_rocketTex.loadFromFile("../Textures/Rocket.png");
	m_fuelTex.loadFromFile("../Textures/Fuel.png");
}

void Content::loadSounds()
{
	m_takeFuelSound.loadFromFile("../Sounds/takeFuel.wav");
	m_thrustSound.loadFromFile("../Sounds/thrust.wav");
}

void Content::loadMusic()
{
	//m_testMusic.openFromFile("../Music/test.wav");
}
