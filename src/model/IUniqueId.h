#pragma once

#include "IActor.h"

namespace model {

class IUniqueId
{
public:

	virtual ~IUniqueId(){}

	virtual ActorId getId() = 0;
};

}
