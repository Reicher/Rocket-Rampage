#pragma once

#include <memory>
#include "../AbstractActor.h"

namespace model {

class ScoreActor : public AbstractActor
{
public:

	ScoreActor( ActorId id, const Vector2& position );

	~ScoreActor();

	void update(double dt);

	int getScore();

private:

	class Impl;

	::std::auto_ptr<Impl> m_apImpl;

};

}
