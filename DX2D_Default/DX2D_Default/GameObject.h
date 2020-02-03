#pragma once
class GameObject
{
public:
	void UpdateRect();
public:
	virtual void Update() = 0;
	virtual void LateUpdate()= 0;
	virtual void Render(HDC hDC) = 0;

private:
	virtual HRESULT Initialize() = 0;
	virtual void Release() = 0;

protected:
	INFO	m_tInfo;
	RECT	m_Rect;
	float	m_fSpeed;
};

