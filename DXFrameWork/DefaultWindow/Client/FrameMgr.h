#pragma once
class CFrameMgr
{
	DECLARE_SINGLETON(CFrameMgr)

private:
	CFrameMgr();
	~CFrameMgr();

public:
	bool LimitFrame(float fFps);
	void RenderFPS();

private:
	LARGE_INTEGER m_OldTimeOne;
	LARGE_INTEGER m_OldTimeTwo;
	LARGE_INTEGER m_CurTime;
	LARGE_INTEGER m_CPUTick;

	float			m_fTimeCount1;
	float			m_fTimeCount2;

	int				m_iFpsCount;
	TCHAR			m_szFPS[MIN_STR];

	CDeviceMgr*		m_pDeviceMgr;
	CTimeMgr*		m_pTimeMgr;
};

