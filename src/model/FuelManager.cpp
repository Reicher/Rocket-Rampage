#include "FuelManager.h"

namespace model {

class FuelManager::Impl
{
public:
	Impl( )
	{
	}

	void update( double dt )
	{
	}

private:

};

FuelManager::FuelManager(  )
: m_apImpl( new Impl( ) )
{
}

FuelManager::~FuelManager()
{
}

void FuelManager::update( double dt )
{
	m_apImpl->update( dt );
}

}

