#pragma once

#include "IManager.h"
#include <memory>
#include "IObservable.h"
#include "IUniqueId.h"

namespace model {

class FuelManager : public IManager
{
public:

	FuelManager( IObservable* pObservable, IUniqueId* pUniqueId );

	~FuelManager();

	void update( double dt );

private:

	class Impl;

	::std::auto_ptr<Impl> m_apImpl;
};

}
