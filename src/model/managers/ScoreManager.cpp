#include "ScoreManager.h"

namespace model {

class ScoreManager::Impl
{
public:

	Impl( IObservable* pObservable, IUniqueId* pUniqueId )
	: m_pObservable( pObservable )
	, m_pUniqueId( pUniqueId )
	{
	}

	void update( double dt )
	{
	}

private:

	IObservable* m_pObservable;

	IUniqueId* m_pUniqueId;

	void addScoreMeter()
	{
		// TODO: Add a ScoreActor and notify the view.
	}

};

ScoreManager::ScoreManager( IObservable* pObservable, IUniqueId* pUniqueId )
: m_apImpl( new Impl( pObservable, pUniqueId ) )
{
}

ScoreManager::~ScoreManager()
{
}

void ScoreManager::update( double dt )
{
	m_apImpl->update( dt );
}

}
