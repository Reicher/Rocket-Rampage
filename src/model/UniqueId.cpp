#include "UniqueId.h"

namespace model {

class UniqueId::Impl
{
public:
	Impl( ActorId startValue )
	: m_current( startValue )
	{
	}

	ActorId getId()
	{
		return m_current++;
	}

private:

	ActorId m_current;
};

UniqueId::UniqueId( ActorId startValue  )
: m_apImpl( new Impl( startValue ) )
{
}

UniqueId::~UniqueId()
{
}

ActorId UniqueId::getId()
{
	return m_apImpl->getId();
}

}
