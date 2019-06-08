#include "stdafx.h"
#include "MessageEvent.h"


MessageEvent::MessageEvent(size_t& messageId)
{
	m_type = Type::MESSAGE_EVENT;
	m_pMessageId = new size_t(messageId);
}


MessageEvent::MessageEvent(std::string message)
{
	m_type = Type::MESSAGE_EVENT;
	m_pMessageId = new size_t(g_hasher(message));
}

MessageEvent::~MessageEvent()
{
}


void MessageEvent::Release()
{
	delete m_pMessageId;
}


void* MessageEvent::GetInfo()
{
	return m_pMessageId;
}