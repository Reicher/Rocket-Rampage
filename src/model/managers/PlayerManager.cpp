#include "PlayerManager.h"
#include "../actors/RocketActor.h"
#include "../actors/ScoreActor.h"
#include "../managers/CosmosManager.h"
#include "../IActorFwd.h"
#include "../Vector2.h"

namespace model {

class PlayerManager::Impl
{
public:
	Impl( IObservable* pObservable, IUniqueId* pUniqueId, CosmosManager* pCosmosManager )
	: m_pObservable( pObservable )
	, m_pUniqueId( pUniqueId )
	, m_pCosmosManager( pCosmosManager )
	, m_actors()
	, m_rocketActors()
	{
		addRocket( Vector2( 0, -440 ) );
	}

	void update( double dt )
	{
		for( Actors::iterator it( m_actors.begin() );
			 it != m_actors.end();
			 ++it )
		{
			(*it)->update( dt );
		}
	}

	 void setRocketThrust( bool isOn, int id )
	 {
		 m_rocketActors[id]->setThrustOn( isOn );
	 }

	 void setThrustOn( bool isOn, int id )
	 {
		 m_rocketActors[id]->setThrustOn( isOn );
	 }

	 void setBackThrustOn( bool isOn, int id )
	 {
		 m_rocketActors[id]->setBackThrustOn( isOn );
	 }

	 void setLeftThrustOn( bool isOn, int id )
	 {
		 m_rocketActors[id]->setLeftThrustOn( isOn );
	 }

	 void setRightThrustOn( bool isOn, int id )
	 {
		 m_rocketActors[id]->setRightThrustOn( isOn );
	 }

	 void setCRotOn( bool isOn, int id )
	 {
		 m_rocketActors[id]->setCRotOn( isOn );
	 }

	 void setCCWRotOn( bool isOn, int id )
	 {
		 m_rocketActors[id]->setCCWRotOn( isOn );
	 }


private:

	IObservable* m_pObservable;

	IUniqueId* m_pUniqueId;

	CosmosManager* m_pCosmosManager;

	Actors m_actors;

	typedef std::vector<RocketActor*> RocketActors;

	RocketActors m_rocketActors;

	void addRocket( Vector2 pos )
	{
		RocketActor* pRocketActor( new RocketActor( m_pUniqueId->getId(), pos) );

		m_rocketActors.push_back( pRocketActor );

		ScoreActor* pScoreActor( new ScoreActor( m_pUniqueId->getId(), Vector2( 0.0, 0.0 ), m_pCosmosManager->getHomePlanet(), pRocketActor ) );

		m_pObservable->notifyObservers( Event( EV_ADD_ROCKET, pRocketActor ) );

		m_pObservable->notifyObservers( Event( EV_ADD_SCORE, pScoreActor ) );

		m_actors.push_back( pRocketActor );

		m_actors.push_back( pScoreActor );
	}

};

PlayerManager::PlayerManager( IObservable* pObservable, IUniqueId* pUniqueId, CosmosManager* pCosmosManager  )
: m_apImpl( new Impl( pObservable, pUniqueId, pCosmosManager ) )
{
}

PlayerManager::~PlayerManager()
{
}

void PlayerManager::update( double dt )
{
	m_apImpl->update( dt );
}

void PlayerManager::setThrustOn( bool isOn, int id )
{
	m_apImpl->setThrustOn( isOn, id );
}

void PlayerManager::setBackThrustOn( bool isOn, int id )
{
	m_apImpl->setBackThrustOn( isOn, id );
}

void PlayerManager::setLeftThrustOn( bool isOn, int id )
{
	m_apImpl->setLeftThrustOn( isOn, id );
}

void PlayerManager::setRightThrustOn( bool isOn, int id )
{
	m_apImpl->setRightThrustOn( isOn, id );
}

void PlayerManager::setCRotOn( bool isOn, int id )
{
	m_apImpl->setCRotOn( isOn, id );
}

void PlayerManager::setCCWRotOn( bool isOn, int id )
{
	m_apImpl->setCCWRotOn( isOn, id );
}

}

