#include "stdafx.h"
#include "Event.h"


Event::Event()
{
}


Event::Event(Type eventType)
{
	m_type = eventType;
}

Event::~Event()
{
}

Event::Type Event::GetType()
{
	return m_type;

}
