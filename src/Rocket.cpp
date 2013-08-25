#include "Rocket.h"

#include "iostream"
using namespace std;

Rocket::Rocket(Content *content, sf::RenderWindow *app)
: m_mainSprite(content->m_rocketTex)
, m_pApp(app)
, m_x(350)
, m_y(0)
, m_vx(0.0)
, m_vy(0.0)
, m_ax(0.0)
, m_ay(0.0)
, m_fx(0.0)
, m_fy(0.0)
, m_fuelSec(sf::seconds(100.0f))
, m_mass(1.0)
, m_speedMulti(30000)
, m_landed(false)
{
	m_mainSprite.setPosition(m_x, m_y);
	m_mainSprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
}

void Rocket::draw()
{
	m_pApp->draw(m_mainSprite);
}

void Rocket::handleInput(float dt)
{
	bool Thrust = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	bool LeftBooster = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	bool RightBooster = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
	bool HaveFuel = m_fuelSec > sf::seconds(0.0);

	//Thrust
	if (Thrust && HaveFuel)
		m_fy -= 3.0 * m_speedMulti;

	// Left strafe
	if (RightBooster && HaveFuel)
		m_fx += 1.0 * m_speedMulti;

	// Right strafe
	if (LeftBooster && HaveFuel)
		m_fx -= 1.0 * m_speedMulti;

	// If Fuel should be consumed
	if( Thrust || LeftBooster || RightBooster)
		m_fuelSec -= sf::seconds(dt);

	if(m_fuelSec < sf::seconds(0.0))
		m_fuelSec = sf::seconds(0.0);


	//cout << "Fuel:" << m_fuelSec.asSeconds() << ", " << endl;

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
	const double slowdown = 0.9999;
	m_fx = 0.0;
	m_fy = 0.0;

	 if( !handleLlanding( gravitySource ) )
		//handleGravity(dt, gravitySource );

	handleInput(dt);

	cout << "Force: " << m_fy << ", ";


	//Calculate acceleration
	m_ax = m_fx / m_mass * dt;
	m_ay = m_fy / m_mass * dt;

	// Calculate speed
	if(m_ax || m_ay){
		m_vx += m_ax * dt;
		m_vy += m_ay * dt;
	}else{
		m_vx *= slowdown * 1.0 - dt;
		m_vy *= slowdown * 1.0 - dt;
	}
	//cout << "Speed: " << m_vx << ", ";

	// Calculate position
	if(m_vx || m_vy)
	{
		m_x += m_vx * dt;
		m_y += m_vy * dt;
	}
	//cout << "x: " << m_x;
	//cout << " y: " << m_y;


	//cout << endl;
	m_mainSprite.setPosition(m_x, m_y);
}

bool Rocket::handleLlanding(Planet *gravitySource)
{
	float vX = m_x + 5+- gravitySource->m_x;
	float vY = m_y + 100 - gravitySource->m_y;
	float length = sqrt(pow(vX, 2) + pow(vY,  2)) - gravitySource->m_shape.getRadius();

	if(length < 1.0)
	{
		if(!m_landed)
		{
			m_vx = m_vy = 0;
		}
		cout << "Landed!" << endl;;

		if(m_vx > 100 || m_vy > 100)
			cout << "DEAD!";

		m_landed = true;
	}else{
		m_landed = false;
		cout << "in space" << endl;
	}

	return m_landed;
}
