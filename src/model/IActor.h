#pragma once

namespace model {

typedef long ActorId;

//! Interface for all actors in the model.
class IActor
{
public:

	virtual ~IActor(){}

	virtual void update(double dt) = 0;

	virtual ActorId getId() = 0;

	virtual double getX() = 0;

	virtual double getY() = 0;

	virtual double getRotation() = 0;
};

}
