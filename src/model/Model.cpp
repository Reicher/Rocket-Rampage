#include "Model.h"
#include "IObserver.h"
#include "IManager.h"
#include "managers/FuelManager.h"
#include "managers/CosmosManager.h"
#include "managers/ScoreManager.h"
#include "managers/PlayerManager.h"
#include "UniqueId.h"
#include <list>
#include <vector>

namespace model {

class Model::Impl
{
public:
	Impl( IObservable* pObservable )
	: m_pObservable( pObservable )
	, m_observers()
	, m_managers()
	, m_apUniqueId( new UniqueId( 100 ) )
	, m_pPlayerManager( 0 )
	{
	}

	void init()
	{
		createManagers();
	}

	void update( float dt )
	{
		if( dt == 0 )
		{
			return;
		}

		for( Managers::iterator it( m_managers.begin() );
			 it != m_managers.end();
			 ++it )
		{
			( *it )->update( dt );
		}

	}

	void setRocketThrust( bool isOn, int id )
	{
		m_pPlayerManager->setRocketThrust( isOn, id );
	}


	void addObserver( IObserver* pObserver )
	{
		m_observers.push_back( pObserver );
	}

	void notifyObservers( ::std::string what, void* p )
	{
		for( Observers::iterator it( m_observers.begin() );
			 it != m_observers.end();
			 ++it )
		{
			( *it )->notify( what, p );
		}
	}

private:

	IObservable* m_pObservable;

	typedef ::std::list<IObserver*> Observers;

	Observers m_observers;

	typedef ::std::list<IManager*> Managers;

	Managers m_managers;

	::std::auto_ptr<IUniqueId> m_apUniqueId;

	PlayerManager* m_pPlayerManager;

	void createManagers()
	{
		m_managers.push_back( new FuelManager( m_pObservable, m_apUniqueId.get() ) );
		m_managers.push_back( new CosmosManager( m_pObservable, m_apUniqueId.get() ) );
		m_managers.push_back( new ScoreManager( m_pObservable, m_apUniqueId.get() ) );

		m_pPlayerManager = new PlayerManager( m_pObservable, m_apUniqueId.get() );

		m_managers.push_back( m_pPlayerManager );
	}
};

Model::Model()
: m_apImpl()
{
	m_apImpl.reset( new Impl( this ) );
}

Model::~Model()
{
}

void Model::init()
{
	m_apImpl->init();
}

void Model::update( float dt )
{
	return m_apImpl->update( dt );
}

void Model::setRocketThrust( bool isOn, int id )
{
	m_apImpl->setRocketThrust( isOn, id );
}

void Model::addObserver( IObserver* pObserver )
{
	m_apImpl->addObserver( pObserver );
}

void Model::notifyObservers( ::std::string what, void* p )
{
	m_apImpl->notifyObservers( what, p );
}

}
