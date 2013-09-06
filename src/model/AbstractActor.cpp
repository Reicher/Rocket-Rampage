#include "AbstractActor.h"

namespace model {

class AbstractActor::Impl
{
public:

	Impl( ActorId id, const Vector2& position )
	: m_id( id )
	, m_position( position )
	{
	}

	ActorId getId()
	{
		return m_id;
	}

	Vector2 getPosition() const
	{
		return m_position;
	}

private:

	ActorId m_id;

	Vector2 m_position;

};

AbstractActor::AbstractActor( ActorId id, const Vector2& position )
: m_apImpl( new Impl( id, position ) )
{
}

AbstractActor::~AbstractActor()
{
}

ActorId AbstractActor::getId() const
{
	return m_apImpl->getId();
}

Vector2 AbstractActor::getPosition() const
{
	return m_apImpl->getPosition();
}

}
