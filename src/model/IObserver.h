#pragma once

#include "Event.h"

namespace model {

class IObserver
{
public:

	virtual ~IObserver(){}

	virtual void notify( const Event& e  ) = 0;
};

}

