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
}

void Content::loadSounds()
{
	//m_testSound.loadFromFile("../Sounds/test.wav");
}

void Content::loadMusic()
{
	//m_testMusic.openFromFile("../Music/test.wav");
}
