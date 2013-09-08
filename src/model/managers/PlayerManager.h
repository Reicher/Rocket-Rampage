#pragma once

#include <memory>
#include <math.h>

#include "../IManager.h"
#include "../IObservable.h"
#include "../IUniqueId.h"

namespace model {

class PlayerManager : public IManager
{
public:

	PlayerManager( IObservable* pObservable, IUniqueId* pUniqueId );

	~PlayerManager();

	void update( double dt );

private:

	class Impl;

	::std::auto_ptr<Impl> m_apImpl;
};

}
