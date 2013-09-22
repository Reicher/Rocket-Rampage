#pragma once

#include "../IActor.h"
#include "../Vector2.h"
#include <memory>

namespace model {

class RocketActor : public IActor
{
public:

	RocketActor( ActorId id, Vector2 pos );

	~RocketActor();

	void update(double dt);

	ActorId getId();

	double getX();

	double getY();

	double getRotation();

	double getSize();

	void setThrustOn( bool thrust );

	void setBackThrustOn( bool backThrust );

	void setLeftThrustOn( bool leftThrust );

	void setRightThrustOn( bool rightThrust );

	void setCRotOn( bool cRot );

	void setCCWRotOn( bool ccwRot );

	double getFuel( );

	double getMass();

	void setForce(Vector2 force);


private:

	class Impl;

	::std::auto_ptr<Impl> m_apImpl;
};

}
