#pragma once

#include <memory>
#include <math.h>

#include "../IManager.h"
#include "../IObservable.h"
#include "../IUniqueId.h"

namespace model {

class IActor;

//! Manager for planets, asteroids, stars'n  shit
class CosmosManager : public IManager
{
public:

	CosmosManager( IObservable* pObservable, IUniqueId* pUniqueId );

	~CosmosManager();

	void update( double dt );

	IActor* getHomePlanet() const;

private:

	class Impl;

	::std::auto_ptr<Impl> m_apImpl;
};

}
