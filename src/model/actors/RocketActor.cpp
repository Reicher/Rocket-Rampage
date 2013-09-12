#include "RocketActor.h"

#include "math.h"

#include <iostream>

namespace model {

class RocketActor::Impl
{
public:
	Impl( ActorId id, Vector2 position )
	: m_id( id )
	, m_position(position)
	, m_v(0, 0)
	, m_a(0, 0)
	, m_f(0, 0)
	, m_rotation(0.0)
	, m_vr(0.0)
	, m_ar(0.0)
	, m_fr(0.0)
	, m_size(1.0)
	, m_mass(1.0)
	, m_thrust( false )
	, m_rightThrust( false )
	, m_leftThrust( false )
	, m_backThrust( false )
	, m_cRot( false )
	, m_ccwRot( false )
	, m_fuel(10.0)
	{
	}

	void manipulate(double dt)
	{
		double speedMulti = 1.0;
		bool haveFuel = m_fuel > 0;

		//Black magic
		Vector2 ori;
		float rad = m_rotation * 0.0174532925;
		ori.x = 0 * cos(rad) + 1.0 * sin(rad);
		ori.y = 0 * sin(rad) - 1.0 * cos(rad);

		//Thrust
		if (m_thrust && haveFuel){
			m_f += ori * 3.0 * speedMulti;
			m_fuel -= dt;
			// Player thrust sound
		}

		ori.x = 1 * cos(rad);
		ori.y = 1 * sin(rad);

		// Left strafe
		if (m_rightThrust && haveFuel)
		{
			m_f += ori * 1.0f * speedMulti;
			m_fuel -= dt;
		}

		// Right strafe
		if (m_leftThrust && haveFuel)
		{
			m_f -= ori * 1.0f * speedMulti;
			m_fuel -= dt;
		}

		// Clockwise rotation
		if(m_cRot && haveFuel){
			m_fr += 1.0 * speedMulti;
			m_fuel -= dt;
		}

		// Counter Clockwise rotation
		if(m_ccwRot && haveFuel){
			m_fr -= 1.0 * speedMulti;
			m_fuel -= dt;
		}

		if(m_fuel < 0)
			m_fuel = 0.0;
	}

	void update( double dt )
	{
		m_f = Vector2(0.0, 0.0);
		m_fr = 0.0;

		// Fuel is heavy!
		double currentMass = m_mass + m_fuel ;

		manipulate(dt);

		//Calculate acceleration
		m_a = m_f / currentMass;
		m_ar = m_fr / currentMass;

		// Calculate speed
		m_v += m_a;

		//rotation
		m_vr += m_ar;

		// Calculate position
		m_position += m_v * dt;
		m_rotation += m_vr * dt;
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

	void setBackThrustOn( bool backThrust )
	{
		m_backThrust = backThrust;
	}

	void setLeftThrustOn( bool leftThrust )
	{
		m_leftThrust = leftThrust;
	}

	void setRightThrustOn( bool rightThrust )
	{
		m_rightThrust = rightThrust;
	}

	void setCRotOn( bool cRot )
	{
		m_cRot = cRot;
	}

	void setCCWRotOn( bool ccwRot )
	{
		m_ccwRot= ccwRot;
	}


private:

	ActorId m_id;

	Vector2 m_position;
	Vector2 m_v;
	Vector2 m_a;
	Vector2 m_f;

	double m_rotation;
	double m_vr;
	double m_ar;
	double m_fr;

	double m_size;
	double m_mass;

	bool m_thrust;
	bool m_rightThrust;
	bool m_leftThrust;
	bool m_backThrust;
	bool m_cRot;
	bool m_ccwRot;

	double m_fuel;
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
	m_apImpl->setThrustOn(thrust );
}

void RocketActor::setBackThrustOn( bool backThrust )
{
	m_apImpl->setBackThrustOn(backThrust );
}

void RocketActor::setLeftThrustOn( bool leftThrust )
{
	m_apImpl->setLeftThrustOn(leftThrust );
}

void RocketActor::setRightThrustOn( bool rightThrust )
{
	m_apImpl->setRightThrustOn(rightThrust );
}

void RocketActor::setCRotOn( bool cRot )
{
	m_apImpl->setCRotOn(cRot );
}

void RocketActor::setCCWRotOn( bool ccwRot )
{
	m_apImpl->setCCWRotOn(ccwRot );
}

}

