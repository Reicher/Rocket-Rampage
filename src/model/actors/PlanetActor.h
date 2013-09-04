#pragma once

#include "../IActor.h"
#include <memory>

namespace model {

class PlanetActor : public IActor
{
public:

	PlanetActor( ActorId id, double x, double y, double size, double atmosphereThickness = 0.0 );

	~PlanetActor();

	void update(double dt);

	ActorId getId();

	double getX();

	double getY();

	double getRotation();

	double getSize();

	double getAtmosphereThickness();

private:

	class Impl;

	::std::auto_ptr<Impl> m_apImpl;
};

}
