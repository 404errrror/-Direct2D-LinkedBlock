#pragma once
class TestCharacter : public GameObject
{
public:
	TestCharacter();
	~TestCharacter();

	virtual void Initialize();
	virtual void Release();

	virtual int Start();
	virtual int Update();
	virtual int OnEvent(Event&);

	int key;
private:
	float speed;

	void MoveFunc();
	void MoveFunc2();
};

