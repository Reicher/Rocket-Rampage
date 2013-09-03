#pragma once

#include "../IActor.h"
#include <memory>

namespace model {

class FuelActor : public IActor
{
public:

	FuelActor( ActorId id, double x, double y );

	~FuelActor();

	void update(double dt);

	ActorId getId();

	double getX();

	double getY();

	double getRotation();



private:

	class Impl;

	::std::auto_ptr<Impl> m_apImpl;
};

}
