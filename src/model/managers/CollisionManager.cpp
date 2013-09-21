#include "CollisionManager.h"
#include "../IActorFwd.h"

namespace model {

class CollisionManager::Impl
{
public:
	Impl( IObservable* pObservable, PlayerManager* pPlayerManager, FuelManager* pFuelManager )
	: m_pObservable( pObservable )
	, m_pPlayerManager( pPlayerManager )
	, m_pFuelManager( pFuelManager )
	{
	}

	void update( double dt )
	{

	}

private:

	IObservable* m_pObservable;

	PlayerManager* m_pPlayerManager;

	FuelManager* m_pFuelManager;
};

CollisionManager::CollisionManager( IObservable* pObservable, PlayerManager* pPlayerManager, FuelManager* pFuelManager )
: m_apImpl( new Impl( pObservable, pPlayerManager, pFuelManager ) )
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::update( double dt )
{
	m_apImpl->update( dt );
}

} //namespace model

