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

	void setThrustOn( bool isOn, int id )
	{
		m_pPlayerManager->setThrustOn( isOn, id );
	}

	void setBackThrustOn( bool isOn, int id )
	{
		m_pPlayerManager->setBackThrustOn( isOn, id );
	}

	void setLeftThrustOn( bool isOn, int id )
	{
		m_pPlayerManager->setLeftThrustOn( isOn, id );
	}

	void setRightThrustOn( bool isOn, int id )
	{
		m_pPlayerManager->setRightThrustOn( isOn, id );
	}

	void setCRotOn( bool isOn, int id )
	{
		m_pPlayerManager->setCRotOn( isOn, id );
	}

	void setCCWRotOn( bool isOn, int id )
	{
		m_pPlayerManager->setCCWRotOn( isOn, id );
	}


	void addObserver( IObserver* pObserver )
	{
		m_observers.push_back( pObserver );
	}

	void notifyObservers( const Event& e )
	{
		for( Observers::iterator it( m_observers.begin() );
			 it != m_observers.end();
			 ++it )
		{
			( *it )->notify( e );
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

		CosmosManager* pCosmosManager = new CosmosManager( m_pObservable, m_apUniqueId.get() );

		m_managers.push_back( pCosmosManager );

		m_pPlayerManager = new PlayerManager( m_pObservable, m_apUniqueId.get(), pCosmosManager );

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

void Model::setThrustOn( bool isOn, int id )
{
	m_apImpl->setThrustOn( isOn, id );
}

void Model::setBackThrustOn( bool isOn, int id )
{
	m_apImpl->setBackThrustOn( isOn, id );
}

void Model::setLeftThrustOn( bool isOn, int id )
{
	m_apImpl->setLeftThrustOn( isOn, id );
}

void Model::setRightThrustOn( bool isOn, int id )
{
	m_apImpl->setRightThrustOn( isOn, id );
}

void Model::setCRotOn( bool isOn, int id )
{
	m_apImpl->setCRotOn( isOn, id );
}

void Model::setCCWRotOn( bool isOn, int id )
{
	m_apImpl->setCCWRotOn( isOn, id );
}

void Model::addObserver( IObserver* pObserver )
{
	m_apImpl->addObserver( pObserver );
}

void Model::notifyObservers( const Event& e )
{
	m_apImpl->notifyObservers( e );
}

}
