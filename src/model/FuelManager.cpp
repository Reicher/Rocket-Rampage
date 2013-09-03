#include "FuelManager.h"
#include "actors/FuelActor.h"
#include "IActorFwd.h"

namespace model {

class FuelManager::Impl
{
public:
	Impl( IObservable* pObservable, IUniqueId* pUniqueId )
	: m_pObservable( pObservable )
	, m_pUniqueId( pUniqueId )
	, m_actors()
	{
		addFuel( 50, 50 );
		addFuel( 200, 100 );
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

	void addFuel( double x, double y )
	{
		IActor* pActor( new FuelActor( m_pUniqueId->getId(), x, y ) );

		m_pObservable->notifyObservers( "addFuel", pActor );

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

