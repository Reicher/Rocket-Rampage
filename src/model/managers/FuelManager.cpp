#include "FuelManager.h"
#include "../actors/FuelActor.h"
#include "../IActorFwd.h"
#include "../Vector2.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

namespace model {

class FuelManager::Impl
{
public:
	Impl( IObservable* pObservable, IUniqueId* pUniqueId )
	: m_pObservable( pObservable )
	, m_pUniqueId( pUniqueId )
	, m_actors()
	, m_threshold(50)
	{
		// initialize random seed:
		srand (time(NULL));

		init();
		addFuel( Vector2( 50, 50 ));
		addFuel( Vector2( 200, 100 ));
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

	// Distance threshold for reaching fuel
	float m_threshold;

	// Places fuel in layers around origo
	void init()
	{
		m_actors.clear();

		float distLayers = 1000;
		float radius = 1000;

		for (int layer = 1; layer < 10; ++layer)
		{
			radius += distLayers;

			for (float rad = 0; rad < 2*M_PI; rad += (800.0 / radius))
			{
				Vector2 pos;
				pos.x = (radius * cos(rad)) + (rand() % 400);
				pos.y = (radius * sin(rad)) + (rand() % 400);;
				addFuel( pos );
			}
		}
	}

	bool isFuelHit(const Vector2& rocketLocation, const Vector2& fuelLocation) const
	{
		const double distance = sqrt(pow(rocketLocation.x - fuelLocation.x , 2) + pow(rocketLocation.y - fuelLocation.y, 2));
		return distance <= m_threshold;
	}

	bool isAnyFuelHit(const Vector2& rocketLocation)
	{
		for( Actors::iterator it( m_actors.begin() );
			 it != m_actors.end();
			 ++it )
		{
			Vector2 pos((*it)->getX(), (*it)->getY());
			if (isFuelHit(rocketLocation, pos))
			{
				m_actors.erase(it);
				// Make Sound
				return true;
			}
		}
		return false;
	}

	void addFuel( Vector2 pos )
	{
		IActor* pActor( new FuelActor( m_pUniqueId->getId(), pos.x, pos.y ) );

		m_pObservable->notifyObservers( Event( EV_ADD_FUEL, pActor ) );

		m_actors.push_back( pActor );
	}

};

FuelManager::FuelManager( IObservable* pObservable, IUniqueId* pUniqueId  )
: m_apImpl( new Impl( pObservable, pUniqueId ) )
{
}

FuelManager::~FuelManager()
{
}

void FuelManager::update( double dt )
{
	m_apImpl->update( dt );
}

}

