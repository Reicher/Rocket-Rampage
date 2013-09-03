#pragma once

#include <string>
#include "IActorFwd.h"

namespace model {

class IObserver;

class IObservable
{
public:

	virtual ~IObservable(){}

	virtual void addObserver( IObserver* pObserver ) = 0;

	virtual void notifyObservers( ::std::string what, IActor* pActor ) = 0;
};

}

