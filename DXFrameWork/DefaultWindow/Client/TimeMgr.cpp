#include "stdafx.h"
#include "TimeMgr.h"

IMPLEMENT_SINGLETON(CTimeMgr)

CTimeMgr::CTimeMgr()
	: m_fDeltaTime(0.f)
{
	// CPU 진동수의 누적 값을 얻어오는 함수. 
	// => 하드웨어가 가지고 있는 고해상도 타이머 값을 얻어오는 함수
	QueryPerformanceCounter(&m_OldTimeOne);
	QueryPerformanceCounter(&m_OldTimeTwo);
	QueryPerformanceCounter(&m_CurTime);

	// 현재 CPU의 진동수(초당 주기)를 얻어오는 함수.
	QueryPerformanceFrequency(&m_CPUTick);
}


CTimeMgr::~CTimeMgr()
{
}

float CTimeMgr::GetDelta() const
{
	return m_fDeltaTime;
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_CurTime);

	// 일정 시간이 지날 때마다 CPU 진동수 갱신
	if (m_CurTime.QuadPart - m_OldTimeTwo.QuadPart > m_CPUTick.QuadPart)
	{
		QueryPerformanceFrequency(&m_CPUTick);
		m_OldTimeTwo = m_CurTime;
	}

	m_fDeltaTime = float(m_CurTime.QuadPart - m_OldTimeOne.QuadPart) / m_CPUTick.QuadPart;
	m_OldTimeOne = m_CurTime;
}
