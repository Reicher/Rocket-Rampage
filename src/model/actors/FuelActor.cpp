#include "FuelActor.h"

namespace model {

class FuelActor::Impl
{
public:
	Impl( ActorId id )
	: m_id( id )
	, x( 0 )
	, y( 0 )
	{
	}

	void update( double dt )
	{
		x += dt;
		y += dt;
	}

	ActorId getId()
	{
		return m_id;
	}

	double getX()
	{
		return x;
	}

	double getY()
	{
		return y;
	}

	double getRotation()
	{
		return 0.0;
	}

private:

	ActorId m_id;

	double x,y;
};

FuelActor::FuelActor( ActorId id )
: m_apImpl( new Impl( id ) )
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

}

