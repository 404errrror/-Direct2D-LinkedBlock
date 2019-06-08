#include "stdafx.h"
#include "InputClass.h"


InputClass::InputClass()
{
}


InputClass::InputClass(const InputClass& other)
{

}


InputClass::~InputClass()
{
}


void InputClass::Initialize()
{
	for (int i = 0; i < 256; i++)
	{
		m_keys[i] = false;
	}

	return;
}


void InputClass::KeyDown(unsigned int input)
{
	m_keys[input] = true;
	return;
}

void InputClass::KeyUp(unsigned int input)
{
	m_keys[input] = false;
	return;
}

bool InputClass::isKeyDown(unsigned int key)
{
	return m_keys[key];
}