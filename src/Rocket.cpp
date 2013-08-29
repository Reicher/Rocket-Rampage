#include "Rocket.h"


#include "iostream"
using namespace std;

Rocket::Rocket(Content *content, sf::RenderWindow *app)
: m_mainSprite(content->m_rocketTex)
, m_fuelSec(sf::seconds(10.0f))
, m_x(350)
, m_y(0)
, m_r(0.0)
, m_pApp(app)
, m_vx(0.0)
, m_vy(0.0)
, m_ax(0.0)
, m_ay(0.0)
, m_fx(0.0)
, m_fy(0.0)
, m_vr(0.0)
, m_ar(0.0)
, m_fr(0.0)
, m_speedMulti(2)
, m_mass(1.0)
, takeFuel(content->m_takeFuelSound)
, thrust( content->m_thrustSound)
{
	m_mainSprite.setPosition(m_x, m_y);
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
	m_fx = m_fy = m_fr = m_ax = m_ay = m_ar = m_vx = m_vy = m_vr = 0.0;
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


	//cout << "angle: " << rad << ", Ori: " << ori.x << ", " << ori.y << endl;

	//Thrust
	if (Thrust && HaveFuel){
		m_fx += 3.0 * ori.x * m_speedMulti;
		m_fy += 3.0 * ori.y * m_speedMulti;
		if(thrust.getStatus() != sf::Sound::Playing)
			thrust.play();
	}

	ori.x = 1 * cos(rad);
	ori.y = 1 * sin(rad);

	// Left strafe
	if (RightBooster && HaveFuel)
	{
		m_fx += 1.0 * ori.x * m_speedMulti;
		m_fy += 1.0 * ori.y * m_speedMulti;
	}

	// Right strafe
	if (LeftBooster && HaveFuel)
	{
		m_fx -= 1.0 * ori.x * m_speedMulti;
		m_fy -= 1.0 * ori.y * m_speedMulti;
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

	float vX = m_x - gravitySource->m_x;
	float vY = m_y - gravitySource->m_y;
	float length = sqrt(pow(vX, 2) + pow(vY,  2));

	float gravConst = -2.0;
	float ix = vX / length * gravConst;
	float iy = vY / length * gravConst;

	m_fx += ix * dt * m_speedMulti;
	m_fy += iy * dt * m_speedMulti;

}

void Rocket::update(float dt, Planet *gravitySource = NULL)
{
	m_fx = 0.0;
	m_fy = 0.0;
	m_fr = 0.0;

	if(dt)
		handleInput(dt);

	//Calculate acceleration
	m_ax = m_fx / m_mass * dt;
	m_ay = m_fy / m_mass * dt;
	m_ar = m_fr / m_mass * dt;

	// Calculate speed
	m_vx += m_ax;
	m_vy += m_ay;

	//rotation
	m_vr += m_ar;

	//slowly take speed down
	const double slowdown = 0.999;
	m_vx *= slowdown * 1.0 - dt;
	m_vy *= slowdown * 1.0 - dt;
	m_vr *= slowdown * 1.0 - dt;

	// Calculate position
	m_x += m_vx;
	m_y += m_vy;
	m_r += m_vr;

	m_mainSprite.setPosition(m_x, m_y);
	m_mainSprite.setRotation(m_r);
}

void Rocket::fillFuel(sf::Time fuel)
{
	m_fuelSec += fuel;

	if(m_fuelSec.asSeconds() > 10)
		m_fuelSec = sf::seconds(10.0);

	//sound of taking barrel, should absolutely be in FuelPowerup
	takeFuel.play();

}
