#pragma once
class GameObject
{
public:
	void UpdateRect();
	void SetPos(float x, float y, float z);
	const INFO GetInfo();
public:
	virtual void Update() = 0;
	virtual void LateUpdate()= 0;
	virtual void Render() = 0;

private:
	virtual HRESULT Initialize() = 0;
	virtual void Release() = 0;

protected:
	INFO	m_tInfo;
	RECT	m_Rect;

	float	m_fSpeed;
	float	m_fAngle;
};

