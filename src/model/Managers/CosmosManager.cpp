#include "CosmosManager.h"
#include "../actors/PlanetActor.h"
#include "../IActorFwd.h"
#include "../Vector2.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

namespace model {

class CosmosManager::Impl
{
public:
	Impl( IObservable* pObservable, IUniqueId* pUniqueId )
	: m_pObservable( pObservable )
	, m_pUniqueId( pUniqueId )
	, m_actors()
	{
		// Add homeplanet
		addPlanet(Vector2(0, 0), 400, 150);
	}

	void update( double dt )
	{
		for( Actors::iterator it( m_actors.begin() );
			 it != m_actors.end();
			 ++it )
		{
			( *it )->update( dt );
		}
	}

private:

	IObservable* m_pObservable;

	IUniqueId* m_pUniqueId;

	Actors m_actors;

	void addPlanet( Vector2 pos, double size, double atmosphereThickness )
	{
		IActor* pActor( new PlanetActor( m_pUniqueId->getId(), pos.x, pos.y, size, atmosphereThickness ) );

		m_pObservable->notifyObservers( "addPlanet", pActor );

		m_actors.push_back( pActor );
	}

};

CosmosManager::CosmosManager( IObservable* pObservable, IUniqueId* pUniqueId  )
: m_apImpl( new Impl( pObservable, pUniqueId ) )
{
}

CosmosManager::~CosmosManager()
{
}

void CosmosManager::update( double dt )
{
	m_apImpl->update( dt );
}

}

