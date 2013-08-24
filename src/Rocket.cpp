#include "Rocket.h"

#include "iostream"
using namespace std;

Rocket::Rocket(Content *content, sf::RenderWindow *app)
: m_mainSprite(content->m_rocketTex)
, m_pApp(app)
, m_x(300)
, m_y(300)
, m_vx(0.0)
, m_vy(0.0)
, m_ax(0.0)
, m_ay(0.0)
, m_fx(0.0)
, m_fy(0.0)
, m_speedMulti(20000)
, m_mass(1.0)
{
	m_mainSprite.setPosition(m_x, m_y);
}

void Rocket::draw()
{
	m_pApp->draw(m_mainSprite);
}

void Rocket::handleInput()
{
	bool Thrust = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	bool LeftBooster = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	bool RightBooster = sf::Keyboard::isKeyPressed(sf::Keyboard::D);


	//Thrust
	if (Thrust){
		m_fy = -30.0 * m_speedMulti;
	}else
		m_fy = 0.0;

	// Left strafe
	if (RightBooster){
		m_fx = 10.0 * m_speedMulti;
	}

	// Right strafe
	if (LeftBooster){
		m_fx = -10.0 * m_speedMulti;
	}

	if( LeftBooster == RightBooster)
		m_fx = 0.0;


	cout << "Force: " << m_fx << ", ";
}

void Rocket::update(float dt)
{
	const double slowdown = 0.9999;

	handleInput();

	//Calculate acceleration
	m_ax = m_fx / m_mass * dt;
	m_ay = m_fy / m_mass * dt;
	cout << "Acc: " << m_ax << ", ";


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
	//cout << "Pos: " << m_x;


	cout << endl;
	m_mainSprite.setPosition(m_x, m_y);
}
