#include "ScoreActor.h"
#include "../Vector2.h"
#include <math.h>

namespace model {

class ScoreActor::Impl
{
public:

	Impl( ActorId id, const Vector2& position, IActor* pHomePlanet, IActor* pRocket )
	: m_id( id )
	, m_position( position )
	, m_pHomePlanet( pHomePlanet )
	, m_pRocket( pRocket )
	, m_score( 0 )
	{
	}

	void update(double dt)
	{
		m_score = sqrt( pow( m_pRocket->getX() , 2) + pow( m_pRocket->getY() , 2) ) - m_pHomePlanet->getSize() - 40;
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

	int getScore()
	{
		return m_score;
	}

private:

	ActorId m_id;

	Vector2 m_position;

	IActor* m_pHomePlanet;

	IActor* m_pRocket;

	int m_score;
};

ScoreActor::ScoreActor( ActorId id, const Vector2& position, IActor* pHomePlanet, IActor* pRocket )
: m_apImpl( new Impl( id, position, pHomePlanet, pRocket ) )
{
}

ScoreActor::~ScoreActor()
{
}

void ScoreActor::update(double dt)
{
	m_apImpl->update(dt);
}

ActorId ScoreActor::getId()
{
	return m_apImpl->getId();
}

double ScoreActor::getX()
{
	return m_apImpl->getX();
}

double ScoreActor::getY()
{
	return m_apImpl->getY();
}

double ScoreActor::getRotation()
{
	return 0.0;
}

double ScoreActor::getSize()
{
	return 0.0;
}

int ScoreActor::getScore()
{
	return m_apImpl->getScore();
}

}
