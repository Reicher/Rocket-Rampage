#include "ScoreActor.h"

namespace model {

class ScoreActor::Impl
{
public:

	Impl()
	{
	}

	void update(double dt)
	{
	}

	int getScore()
	{
		return 0;
	}
};

ScoreActor::ScoreActor( ActorId id, const Vector2& position )
: AbstractActor( id, position )
, m_apImpl( new Impl() )
{
}

ScoreActor::~ScoreActor()
{
}

void ScoreActor::update(double dt)
{
	m_apImpl->update(dt);
}

int ScoreActor::getScore()
{
	return m_apImpl->getScore();
}

}
