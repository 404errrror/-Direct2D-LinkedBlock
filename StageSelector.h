#pragma once
class StageSelector
{
public:
	StageSelector();
	~StageSelector();

	static void SetStage(int stage);
	static int GetStage();
private:
	static int m_stage;
};

