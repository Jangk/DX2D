#include "stdafx.h"
#include "TimeMgr.h"

IMPLEMENT_SINGLETON(CTimeMgr)

CTimeMgr::CTimeMgr()
	: m_fDeltaTime(0.f)
{
	// CPU �������� ���� ���� ������ �Լ�. 
	// => �ϵ��� ������ �ִ� ���ػ� Ÿ�̸� ���� ������ �Լ�
	QueryPerformanceCounter(&m_OldTimeOne);
	QueryPerformanceCounter(&m_OldTimeTwo);
	QueryPerformanceCounter(&m_CurTime);

	// ���� CPU�� ������(�ʴ� �ֱ�)�� ������ �Լ�.
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

	// ���� �ð��� ���� ������ CPU ������ ����
	if (m_CurTime.QuadPart - m_OldTimeTwo.QuadPart > m_CPUTick.QuadPart)
	{
		QueryPerformanceFrequency(&m_CPUTick);
		m_OldTimeTwo = m_CurTime;
	}


	m_fDeltaTime = float(m_CurTime.QuadPart - m_OldTimeOne.QuadPart) / m_CPUTick.QuadPart;
	m_OldTimeOne = m_CurTime;
}
