#include "Planet.h"
#include "iostream"

using namespace std;

Planet::Planet(Content *contnent, sf::RenderWindow *app, float pX, float pY, float size)
: m_x(pX)
, m_y(pY)
, m_pApp(app)
{
	m_shape.setRadius(size);
	m_atmosphere.setRadius(size + 150);

	m_shape.setOrigin(size, size);
	m_atmosphere.setOrigin(size+150, size+150);

	m_shape.setFillColor(sf::Color(180, 140, 100));
	m_shape.setOutlineThickness(-10);
	m_shape.setOutlineColor(sf::Color(180, 255, 200));

	m_atmosphere.setFillColor(sf::Color(100, 100, 200));

	float smoothness = 5;
	m_shape.setPointCount(static_cast<int>(size) / smoothness);
	m_atmosphere.setPointCount(static_cast<int>(size) / smoothness);
}

void Planet::draw()
{
	m_pApp->draw(m_atmosphere);
	m_pApp->draw(m_shape);
}

void Planet::getClosestSurfacePoint(float &x, float &y)
{
	float vX = m_x - x;
	float vY = m_y - y;
	float length = sqrt(pow(vX, 2) + pow(vY,  2));

	float ix = vX / length;
	float iy = vY / length;

	length -= m_shape.getRadius();

	x += (ix * length) ;
	y += (iy * length);

}

float Planet::getMass()
{
	return m_shape.getRadius() * 10;
}
