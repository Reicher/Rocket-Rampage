#include "FuelActor.h"

namespace model {

class FuelActor::Impl
{
public:
	Impl( ActorId id, double x, double y )
	: m_id( id )
	, m_x( x )
	, m_y( y )
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
		return 0.0;
	}

private:

	ActorId m_id;

	double m_x;

	double m_y;
};

FuelActor::FuelActor( ActorId id, double x, double y )
: m_apImpl( new Impl( id, x, y ) )
{
}

FuelActor::~FuelActor()
{
}

void FuelActor::update( double dt )
{
	m_apImpl->update( dt );
}

ActorId FuelActor::getId()
{
	return m_apImpl->getId();
}

double FuelActor::getX()
{
	return m_apImpl->getX();
}

double FuelActor::getY()
{
	return m_apImpl->getY();
}

double FuelActor::getRotation()
{
	return m_apImpl->getRotation();
}

double FuelActor::getSize()
{
	return m_apImpl->getSize();
}

}

