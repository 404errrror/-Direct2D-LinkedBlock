#pragma once
#include "Event.h"
class MessageEvent :
	public Event
{
public:
	MessageEvent(size_t& messageId);
	MessageEvent(std::string message);
	~MessageEvent();

	void Release();
	virtual void* GetInfo();

	size_t* m_pMessageId;
};

