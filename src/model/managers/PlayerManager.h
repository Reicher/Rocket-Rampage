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

	void setThrustOn( bool thrust, int id );

	void setBackThrustOn( bool backThrust, int id );

	void setLeftThrustOn( bool leftThrust, int id );

	void setRightThrustOn( bool rightThrust, int id );

	void setCRotOn( bool cRot, int id );

	void setCCWRotOn( bool ccwRot, int id );

private:

	class Impl;

	::std::auto_ptr<Impl> m_apImpl;
};

}
