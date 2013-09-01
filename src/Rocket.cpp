#include "Rocket.h"


#include "iostream"
using namespace std;

Rocket::Rocket(Content *content, sf::RenderWindow *app)
: m_mainSprite(content->m_rocketTex)
, m_fuelSec(sf::seconds(10.0f))
, m_r(0.0)
, m_pApp(app)
, m_p(350, 0)
, m_v(0, 0)
, m_a(0, 0)
, m_f(0, 0)
, m_vr(0.0)
, m_ar(0.0)
, m_fr(0.0)
, m_speedMulti(2)
, m_mass(11.0)
, thrust( content->m_thrustSound)
, m_slowdown(true)
{
	m_mainSprite.setPosition(m_p);
	m_mainSprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
	m_mainSprite.setOrigin(50.0, 50.0);

	thrust.setVolume(40);
}

void Rocket::draw()
{
	m_pApp->draw(m_mainSprite);
}

void Rocket::stopAll()
{
	m_f = m_a = m_v = sf::Vector2f(0, 0);
}

void Rocket::handleInput(float dt)
{
	bool Thrust = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	bool LeftBooster = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	bool RightBooster = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
	bool CWrotation = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
	bool CCWrotation = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);

	bool HaveFuel = m_fuelSec > sf::seconds(0.0);

	sf::Vector2<float > ori;

	//Black magic
	float rad = m_r * 0.0174532925;
	ori.x = 0 * cos(rad) + 1.0 * sin(rad);
	ori.y = 0 * sin(rad) - 1.0 * cos(rad);

	//Thrust
	if (Thrust && HaveFuel){
		m_f.x += 3.0 * ori.x * m_speedMulti;
		m_f.y += 3.0 * ori.y * m_speedMulti;
		if(thrust.getStatus() != sf::Sound::Playing)
			thrust.play();
	}

	ori.x = 1 * cos(rad);
	ori.y = 1 * sin(rad);

	// Left strafe
	if (RightBooster && HaveFuel)
	{
		m_f.x += 1.0 * ori.x * m_speedMulti;
		m_f.y += 1.0 * ori.y * m_speedMulti;
	}

	// Right strafe
	if (LeftBooster && HaveFuel)
	{
		m_f.x -= 1.0 * ori.x * m_speedMulti;
		m_f.y -= 1.0 * ori.y * m_speedMulti;
	}

	// Clockwise rotation
	if(CWrotation && HaveFuel)
		m_fr += 1.0 * m_speedMulti;

	// Counter Clockwise rotation
	if(CCWrotation && HaveFuel)
		m_fr -= 1.0 * m_speedMulti;

	// If Fuel should be consumed
	if( Thrust || LeftBooster || RightBooster || CWrotation || CCWrotation)
		m_fuelSec -= sf::seconds(dt);

	if(m_fuelSec < sf::seconds(0.0))
		m_fuelSec = sf::seconds(0.0);


}

void Rocket::handleGravity(float dt, Planet *gravitySource)
{
	if(gravitySource == NULL)
		return;

	sf::Vector2f V = gravitySource->getPosition() - m_p;
	float r = sqrt(pow(V.x, 2) + pow(V.y,  2));

	// Newtons universal law of gravity!
	// http://en.wikipedia.org/wiki/Newton%27s_law_of_universal_gravitation
	// With a not so realistic constant G
	float G = 10.0f;
	float Force = G * (m_mass * gravitySource->getMass()) /  pow(r, 2.0f);

	sf::Vector2f unitV = (V / r) * Force;
	m_f += unitV * m_speedMulti;
}

void Rocket::update(float dt, Planet *gravitySource = NULL)
{
	m_f = sf::Vector2f(0.0, 0.0);
	m_fr = 0.0;

	// Fuel is heavy!
	m_mass = 1.0 + m_fuelSec.asSeconds() ;

	if(dt)
		handleInput(dt);

	if( !touchDown(gravitySource) )
		handleGravity(dt, gravitySource);

	//Calculate acceleration
	m_a = m_f / m_mass;

	m_ar = m_fr / m_mass;

	// Calculate speed
	m_v += m_a;

	//rotation
	m_vr += m_ar;

	if(m_slowdown)
		slowdown(dt);

	// Calculate position
	m_p += m_v * dt;
	m_r += m_vr * dt;

	m_mainSprite.move( m_v * dt);
	m_mainSprite.setRotation(m_r);
}

void Rocket::slowdown(float dt)
{
	//slowly take speed down
	float slowdown = 0.999;
	m_v =  m_v * slowdown * (1.0f - dt);
	m_vr *= slowdown * (1.0 - dt);
}

void Rocket::fillFuel(sf::Time fuel)
{
	m_fuelSec += fuel;

	if(m_fuelSec.asSeconds() > 10)
		m_fuelSec = sf::seconds(10.0);
}

bool Rocket::touchDown(Planet *gravitySource = NULL)
{
	if(gravitySource == NULL)
		return false;

	float distance = sqrt( pow(m_p.x - gravitySource->getPosition().x, 2) + pow(m_p.y - gravitySource->getPosition().y , 2) );

	bool landed = distance <= (gravitySource->getSize() + 40);

	if(landed){
		m_v = m_v * -0.70f;
	}

	return landed;
}

void Rocket::setPosition(sf::Vector2f pos)
{
	m_p = pos;
	m_mainSprite.setPosition(m_p);
}

sf::Vector2f Rocket::getPosition() const
{
	return m_p;
}
