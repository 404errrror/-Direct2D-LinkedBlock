#pragma once

class Event
{
public:
	enum Type
	{
		SYSTEM_RESIZE,
		MESSAGE_EVENT,
		BUTTON_CLICK,
		GAMEOBJECT_TRANSFORM_CHANGE,
		ATTACK,
		COLLISION
	};

	Event();
	Event(Type);
	~Event();

	Type GetType();
	virtual void* GetInfo() { return nullptr; }
protected:
	Type m_type;
};

