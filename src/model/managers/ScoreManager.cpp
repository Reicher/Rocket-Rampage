#include "ScoreManager.h"
#include "../actors/ScoreActor.h"

namespace model {

class ScoreManager::Impl
{
public:

	Impl( IObservable* pObservable, IUniqueId* pUniqueId )
	: m_pObservable( pObservable )
	, m_pUniqueId( pUniqueId )
	, m_pScoreActor( new ScoreActor( m_pUniqueId->getId(), Vector2( 10.0, 10.0 ) ) )
	{
		addScore();
	}

	void update( double dt )
	{
	}

private:

	IObservable* m_pObservable;

	IUniqueId* m_pUniqueId;

	ScoreActor* m_pScoreActor;

	void addScore()
	{
		m_pObservable->notifyObservers( Event( EV_ADD_SCORE, m_pScoreActor ) );
	}

};

ScoreManager::ScoreManager( IObservable* pObservable, IUniqueId* pUniqueId )
: m_apImpl( new Impl( pObservable, pUniqueId ) )
{
}

ScoreManager::~ScoreManager()
{
}

void ScoreManager::update( double dt )
{
	m_apImpl->update( dt );
}

}
