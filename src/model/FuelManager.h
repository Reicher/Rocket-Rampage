#pragma once

#include "IManager.h"
#include <memory>

namespace model {

class FuelManager : public IManager
{
public:

	FuelManager( );

	~FuelManager();

	void update(double dt);

private:

	class Impl;

	::std::auto_ptr<Impl> m_apImpl;
};

}
