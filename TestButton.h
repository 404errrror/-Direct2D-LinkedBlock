#pragma once
class TestButton : public GameObject
{
public:
	TestButton();
	~TestButton();

	virtual void Initialize();
	virtual void Release();

	virtual int Start();
	virtual int Update();
	virtual int OnEvent(Event&);


};

