#pragma once
class CTimeMgr
{
	DECLARE_SINGLETON(CTimeMgr)

private:
	CTimeMgr();
	~CTimeMgr();

public:
	float GetDelta() const;

public:
	void Update();

private:
	LARGE_INTEGER m_OldTimeOne;
	LARGE_INTEGER m_OldTimeTwo;
	LARGE_INTEGER m_CurTime;
	LARGE_INTEGER m_CPUTick;

	float m_fDeltaTime; // 1 프레임당 걸리는 시간.
};

