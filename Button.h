#pragma once

class Button : public Component
{
public:
	Button();
	~Button();

	virtual void Initialize(GameObject*);
	virtual void Release();

	virtual int Start();
	virtual int Update();
	virtual int OnEvent(Event&);

	void SetImage(size_t imageId);
	void SetFucusImage(size_t fucusImageId);
	void SetDownImage(size_t downImageId);
	void SetScale(Vector2& scale);

	bool IsEnter() const;

	static std::list<Button*> list;

private:
	size_t m_ImageId;
	size_t m_FocusImageId;
	size_t m_DownImageId;

	Image* m_pImage;
	Transform* m_pTransform;
	BoxCollider* m_pCollider;

	bool m_isDown;
	bool m_isUp;
	bool m_isEnter;
	bool m_isExit;
	bool m_isClick;
};

