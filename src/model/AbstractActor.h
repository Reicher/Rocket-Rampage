#pragma once

#include <memory>
#include "IActor.h"
#include "Vector2.h"

namespace model {

class AbstractActor : public IActor
{
public:

	AbstractActor( ActorId id, const Vector2& position );

	virtual ~AbstractActor();

	ActorId getId() const;

	Vector2 getPosition() const;

private:

	class Impl;

	::std::auto_ptr<Impl> m_apImpl;

};

}
