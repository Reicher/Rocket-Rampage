#include "PlayerManager.h"
#include "../actors/RocketActor.h"
#include "../IActorFwd.h"
#include "../Vector2.h"

namespace model {

class PlayerManager::Impl
{
public:
	Impl( IObservable* pObservable, IUniqueId* pUniqueId )
	: m_pObservable( pObservable )
	, m_pUniqueId( pUniqueId )
	, m_actors()
	{
		addRocket( Vector2(0, -440) );
	}

	void update( double dt )
	{
		for( RocketActors::iterator it( m_actors.begin() );
			 it != m_actors.end();
			 ++it )
		{
			(*it)->update( dt );
		}
	}

	 void setRocketThrust( bool isOn, int id )
	 {
		 m_actors[id]->setThrustOn( isOn );
	 }

private:

	IObservable* m_pObservable;

	IUniqueId* m_pUniqueId;

	typedef ::std::vector<RocketActor*> RocketActors;

	RocketActors m_actors;

	void addRocket( Vector2 pos )
	{
		RocketActor* pActor( new RocketActor( m_pUniqueId->getId(), pos) );

		m_pObservable->notifyObservers( "addRocket", pActor );

		m_actors.push_back( pActor );
	}
};

PlayerManager::PlayerManager( IObservable* pObservable, IUniqueId* pUniqueId  )
: m_apImpl( new Impl( pObservable, pUniqueId ) )
{
}

PlayerManager::~PlayerManager()
{
}

void PlayerManager::update( double dt )
{
	m_apImpl->update( dt );
}

void PlayerManager::setRocketThrust( bool isOn, int id )
{
	m_apImpl->setRocketThrust( isOn, id );
}

}

