#pragma once

#include <memory>
#include "../IActor.h"

class Vector2;

namespace model {

class ScoreActor : public IActor
{
public:

	ScoreActor( ActorId id, const Vector2& position, IActor* pHomePlanet, IActor* pRocket );

	~ScoreActor();

	void update(double dt);

	ActorId getId();

	double getX();

	double getY();

	double getRotation();

	double getSize();

	int getScore();

private:

	class Impl;

	::std::auto_ptr<Impl> m_apImpl;

};

}
