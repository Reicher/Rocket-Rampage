#pragma once

#include <memory>
#include "IUniqueId.h"

namespace model {

class UniqueId : public IUniqueId
{
public:
	UniqueId( ActorId startValue );

	~UniqueId();

	ActorId getId();

private:

	class Impl;

	::std::auto_ptr<Impl> m_apImpl;
};

}
