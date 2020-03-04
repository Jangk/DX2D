#include "stdafx.h"
#include "FrameMgr.h"
#include "Mouse.h"

IMPLEMENT_SINGLETON(CFrameMgr)

CFrameMgr::CFrameMgr()
	: m_fTimeCount1(0.f), m_fTimeCount2(0.f),
	m_iFpsCount(0), m_szFPS(L""),
	m_pDeviceMgr(CDeviceMgr::GetInstance()),
	m_pTimeMgr(CTimeMgr::GetInstance())
{
	QueryPerformanceCounter(&m_OldTimeOne);
	QueryPerformanceCounter(&m_OldTimeTwo);

	QueryPerformanceFrequency(&m_CPUTick);
}


CFrameMgr::~CFrameMgr()
{
}

bool CFrameMgr::LimitFrame(float fFps)
{
	QueryPerformanceCounter(&m_CurTime);

	// 일정 시간이 지날 때마다 CPU 진동수 갱신
	if (m_CurTime.QuadPart - m_OldTimeTwo.QuadPart > m_CPUTick.QuadPart)
	{
		QueryPerformanceFrequency(&m_CPUTick);
		m_OldTimeTwo = m_CurTime;
	}

	m_fTimeCount1 += float(m_CurTime.QuadPart - m_OldTimeOne.QuadPart) / m_CPUTick.QuadPart;
	m_OldTimeOne = m_CurTime;

	if (1.f / fFps <= m_fTimeCount1)
	{
		m_fTimeCount1 = 0.f;
		return true;
	}

	return false;
}

void CFrameMgr::RenderFPS()
{
	// mouse 가져옴
	D3DXVECTOR3 mouse = CMouse::GetMousePos();
		// FPS 출력
	++m_iFpsCount;

	m_fTimeCount2 += m_pTimeMgr->GetDelta();

	if (1.f <= m_fTimeCount2) // 1초가 지났다.
	{
		swprintf_s(m_szFPS, L"FPS: %d", m_iFpsCount, (int)mouse.x, (int)mouse.y);
		m_fTimeCount2 = 0.f;
		m_iFpsCount = 0;
	}
	swprintf_s(m_szMouse, L"MouseX : %d\nMouseY : %d", (int)mouse.x, (int)mouse.y);
	
	// 다이렉트 폰트 출력
	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, 100.f, 100.f, 0.f);
	m_pDeviceMgr->GetSprite()->SetTransform(&matTrans);

	m_pDeviceMgr->GetFont()->DrawText(
		m_pDeviceMgr->GetSprite(), /* 스프라이트 COM 객체 */
		m_szFPS, /* 출력할 문자열 */
		lstrlen(m_szFPS), /* 문자열 길이 */
		nullptr, /* 사각형 영역 */
		0,
		D3DCOLOR_ARGB(255, 0, 255, 0));

	D3DXMatrixTranslation(&matTrans, 100.f, 120.f, 0.f);
	m_pDeviceMgr->GetSprite()->SetTransform(&matTrans);

	m_pDeviceMgr->GetFont()->DrawText(
		m_pDeviceMgr->GetSprite(), /* 스프라이트 COM 객체 */
		m_szMouse, /* 출력할 문자열 */
		lstrlen(m_szMouse), /* 문자열 길이 */
		nullptr, /* 사각형 영역 */
		0,
		D3DCOLOR_ARGB(255, 0, 255, 0));
}