#pragma once

#include <memory>
#include "../IManager.h"
#include "../IObservable.h"
#include "../IUniqueId.h"

namespace model {

class ScoreManager : public IManager
{
public:

	ScoreManager( IObservable* pObservable, IUniqueId* pUniqueId );

	~ScoreManager();

	void update( double dt );

private:

	class Impl;

	::std::auto_ptr<Impl> m_apImpl;

};

}
