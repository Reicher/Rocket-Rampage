#pragma once

#include "Event.h"

namespace model {

class IObserver;

class IObservable
{
public:

	virtual ~IObservable(){}

	virtual void addObserver( IObserver* pObserver ) = 0;

	virtual void notifyObservers( const Event& e ) = 0;
};

}

