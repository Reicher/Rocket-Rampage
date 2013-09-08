#include "RocketActor.h"

namespace model {

class RocketActor::Impl
{
public:
	Impl( ActorId id, Vector2 position )
	: m_id( id )
	, m_position(position)
	, m_rotation(0.0)
	, m_size(1.0)
	, m_thrust( false )
	{
	}

	void update( double dt )
	{
		if( m_thrust )
		{
			m_position.y -= dt * 1000;
		}
	}

	ActorId getId()
	{
		return m_id;
	}

	double getX()
	{
		return m_position.x;
	}

	double getY()
	{
		return m_position.y;
	}

	double getRotation()
	{
		return m_rotation;
	}

	double getSize()
	{
		return m_size;
	}

	void setThrustOn( bool thrust )
	{
		m_thrust = thrust;
	}

private:

	ActorId m_id;

	Vector2 m_position;

	double m_rotation;
	double m_size;

	bool m_thrust;
};

RocketActor::RocketActor( ActorId id, Vector2 position )
: m_apImpl( new Impl( id, position ) )
{
}

RocketActor::~RocketActor()
{
}

void RocketActor::update( double dt )
{
	m_apImpl->update( dt );
}

ActorId RocketActor::getId()
{
	return m_apImpl->getId();
}

double RocketActor::getX()
{
	return m_apImpl->getX();
}

double RocketActor::getY()
{
	return m_apImpl->getY();
}

double RocketActor::getRotation()
{
	return m_apImpl->getRotation();
}

double RocketActor::getSize()
{
	return m_apImpl->getSize();
}

void RocketActor::setThrustOn( bool thrust )
{
	m_apImpl->setThrustOn( thrust );
}

}

