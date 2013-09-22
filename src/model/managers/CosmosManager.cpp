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
	, m_pHomePlanet(new PlanetActor(m_pUniqueId->getId(), 0.0, 0.0, 400, 150))
	, m_actors()
	{
		// Add home planet
		addHomePlanet();
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

	IActor* getHomePlanet() const
	{
		return m_pHomePlanet;
	}

	std::vector<IActor*> getAll()
	{
		return m_actors;
	}

private:

	IObservable* m_pObservable;

	IUniqueId* m_pUniqueId;

	PlanetActor* m_pHomePlanet;

	Actors m_actors;

	void addHomePlanet()
	{
		m_pObservable->notifyObservers( Event( EV_ADD_PLANET, m_pHomePlanet ) );

		m_actors.push_back( m_pHomePlanet );
	}

	void addPlanet( Vector2 pos, double size, double atmosphereThickness )
	{
		IActor* pActor( new PlanetActor( m_pUniqueId->getId(), pos.x, pos.y, size, atmosphereThickness ) );

		m_pObservable->notifyObservers( Event( EV_ADD_PLANET, pActor ) );

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

IActor* CosmosManager::getHomePlanet() const
{
	return m_apImpl->getHomePlanet();
}

std::vector<IActor*> CosmosManager::getAll() const
{
	return m_apImpl->getAll();
}

}

