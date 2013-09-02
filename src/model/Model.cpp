#include "Model.h"
#include "IObserver.h"
#include "IManager.h"
#include "actors/FuelActor.h"
#include <list>
#include <vector>

namespace model {

class Model::Impl
{
public:
	Impl()
	: m_actors()
	, m_observers()
	, m_uniqueActorId( 1000 )
	{
	}

	void init()
	{
		addFuel();
	}

	void update( float dt )
	{
		if( dt == 0 )
		{
			return;
		}

		for( Actors::iterator it( m_actors.begin() );
			 it != m_actors.end();
			 ++it )
		{
			( *it )->update( dt );
		}

	}

	void addObserver( IObserver* pObserver )
	{
		m_observers.push_back( pObserver );
	}

	ActorId createId()
	{
		return m_uniqueActorId++;
	}

private:

	typedef ::std::vector<IActor*> Actors;

	Actors m_actors;

	typedef ::std::list<IObserver*> Observers;

	Observers m_observers;

	typedef ::std::list<IManager*> Managers;

	Managers m_managers;

	ActorId m_uniqueActorId;

	void notify( std::string what, IActor* pActor )
	{
		for( Observers::iterator it( m_observers.begin() );
			 it != m_observers.end();
			 ++it )
		{
			( *it )->notify( what, pActor );
		}

	}

	void addFuel()
	{
		IActor* pActor( new FuelActor( createId() ) );

		notify( "addFuel", pActor );

		m_actors.push_back( pActor );
	}

	void addFuelManager()
	{

	}
};

Model::Model()
: m_apImpl( new Impl )
{
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

void Model::addObserver( IObserver* pObserver )
{
	m_apImpl->addObserver( pObserver );
}

ActorId Model::createId()
{
	return m_apImpl->createId();
}

}
