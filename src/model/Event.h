#pragma once

#include <boost/any.hpp>
#include <memory>

namespace model {

enum EventType
{
	EV_ADD_FUEL,
	EV_ADD_PLANET,
	EV_ADD_SCORE,
	EV_ADD_ROCKET
};

class Event
{
public:

	Event( EventType type, const boost::any& value )
	: m_type( type )
	, m_value( value )
	{
	}

	~Event()
	{
	}

	EventType getType() const
	{
		return m_type;
	}

	const boost::any& getValue() const
	{
		return m_value;
	}

private:

	EventType m_type;

	boost::any m_value;

};

}
