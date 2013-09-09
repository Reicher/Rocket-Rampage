#pragma once

#include <memory>
#include <math.h>

#include "../IManager.h"
#include "../IObservable.h"
#include "../IUniqueId.h"

namespace model {

class CosmosManager;

class PlayerManager : public IManager
{
public:

	PlayerManager( IObservable* pObservable, IUniqueId* pUniqueId, CosmosManager* pCosmosManager );

	~PlayerManager();

	void update( double dt );

	void setRocketThrust( bool isOn, int id );

private:

	class Impl;

	::std::auto_ptr<Impl> m_apImpl;
};

}
