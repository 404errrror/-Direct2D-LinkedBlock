#pragma once
#include "GameObject.h"
class RectRotateEffect :
	public GameObject
{
public:
	enum EffectType
	{
		TYPE_NONE,
		TYPE_FADEOUT,
		TYPE_FADEOUT_MANY,
		TYPE_DEFAULT
	};

	RectRotateEffect	();
	~RectRotateEffect	();

	virtual void Initialize	();
	virtual void Release	();

	virtual int Start	();
	virtual int Update	();
	virtual int OnEvent	(Event&);

	void SetType	(EffectType);
	void SetColor	(D2D1_COLOR_F);
	void FadeOut	(float fadeOutSpeed = 1);

private:
	void FadeOutEffect();
	void DefaultEffect();

	Transform* m_pTransform;
	D2D1_COLOR_F m_baseColor;

	GameObject* m_rectArr;
	D2D1_COLOR_F* m_colorArr;
	EffectType m_type;
	bool m_isFadeOut;
	float m_fadeOutSpeed;
	int m_amount;
	int m_defaultSpeed;
	float m_totalTime;
};

