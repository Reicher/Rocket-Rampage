#pragma once

#include <memory>
#include <math.h>

#include "../IManager.h"
#include "../IObservable.h"
#include "../IUniqueId.h"

#include "FuelManager.h"
#include "PlayerManager.h"

namespace model {

class CollisionManager : public IManager
{
public:

	CollisionManager( IObservable* pObservable, PlayerManager* pPlayerManager, FuelManager* pFuelManager );

	~CollisionManager();

	void update( double dt );

private:

	class Impl;

	::std::auto_ptr<Impl> m_apImpl;
};

}
