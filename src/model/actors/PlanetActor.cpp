#include "PlanetActor.h"

namespace model {

class PlanetActor::Impl
{
public:
	Impl( ActorId id, double x, double y, double size, double atmosphereThickness )
	: m_id( id )
	, m_x( x )
	, m_y( y )
	, m_size(size)
	, m_atmosphereThickness(atmosphereThickness)
	{
	}

	void update( double dt )
	{
		m_x += dt;
		m_y += dt;
	}

	ActorId getId()
	{
		return m_id;
	}

	double getX()
	{
		return m_x;
	}

	double getY()
	{
		return m_y;
	}

	double getRotation()
	{
		return 0.0;
	}

	double getSize()
	{
		return m_size;
	}

	double getAtmosphereThickness()
	{
		return m_atmosphereThickness;
	}

private:

	ActorId m_id;

	double m_x;

	double m_y;

	double m_size;

	double m_atmosphereThickness;
};

PlanetActor::PlanetActor( ActorId id, double x, double y,  double size, double atmosphereThickness /* = 0.0 */)
: m_apImpl( new Impl( id, x, y, size,  atmosphereThickness) )
{
}

PlanetActor::~PlanetActor()
{
}

void PlanetActor::update( double dt )
{
	m_apImpl->update( dt );
}

ActorId PlanetActor::getId()
{
	return m_apImpl->getId();
}

double PlanetActor::getX()
{
	return m_apImpl->getX();
}

double PlanetActor::getY()
{
	return m_apImpl->getY();
}

double PlanetActor::getRotation()
{
	return m_apImpl->getRotation();
}

double PlanetActor::getSize()
{
	return m_apImpl->getSize();
}

double PlanetActor::getAtmosphereThickness()
{
	return m_apImpl->getAtmosphereThickness();
}

}

