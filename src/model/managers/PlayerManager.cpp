#include "PlayerManager.h"
#include "../actors/RocketActor.h"
#include "../actors/ScoreActor.h"
#include "../actors/PlanetActor.h"
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
		// I have completely ditched the m_actor here..
		// dont really know how to use it
		for( RocketActors::iterator it( m_rocketActors.begin() );
			 it != m_rocketActors.end();
			 ++it )
		{
			handleGravity(*it);
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

	void handleGravity(RocketActor* rocket)
	{
		Vector2 pos = Vector2(rocket->getX(), rocket->getY());
		float G = 100.0;

		IActor* homePlanet = m_pCosmosManager->getHomePlanet();
		double mass = homePlanet->getSize();

		Vector2 V = Vector2(homePlanet->getX(), homePlanet->getY()) - pos;
		double distance = V.getLength();

		double forceBetween = G * (rocket->getMass() * mass) /  pow(distance, 2);
		V.normalize();
		V = V * forceBetween;

		rocket->setForce(V);
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

