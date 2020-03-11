#include "stdafx.h"
#include "GameMgr.h"
#include "Card.h"
#include "Player.h"
#include "Monster.h"
#include "TopPanel.h"
#include "Mouse.h"

IMPLEMENT_SINGLETON(CGameMgr)

CGameMgr::CGameMgr():
	m_pDeviceMgr(CDeviceMgr::GetInstance()),
	m_pTextureMgr(CTextureMgr::GetInstance()),
	m_pTimeMgr(CTimeMgr::GetInstance()),
	m_pSceneMgr(CSceneMgr::GetInstance()),
	m_pObjectMgr(CObjectMgr::GetInstance()),
	m_pKeyMgr(CKeyMgr::GetInstance()),
	m_pScrollMgr(CScrollMgr::GetInstance()),
	m_bIsPlayerTurn(TURN_START)
{
	
}

CGameMgr::~CGameMgr()
{
	Release();
}

void CGameMgr::Initialize()
{
	m_SelectCard			= nullptr;				// 아무것도 선택되지 않으면 nullptr
	m_bIsPlayerTurn			= true;
	m_bIsDrawing			= false;
	m_fCardAngleMax			= 50.f;
	m_iDrawMax				= 10;					// 매턴 뽑을 카드 수.
	// 카운터
	m_iDrawCount			= 0;	
	// 프레임
	m_tDrawFrame.fMaxFrame	= 5.f;


	for (auto iter : m_pObjectMgr->GetGameObject(OBJECT_CARD))
		m_vecDeck.push_back(dynamic_cast<CCard*>(iter));
}

void CGameMgr::Update()
{
	CountingFunc();
	UpdateCard();

	switch (m_eTurnPhase)
	{
	case TURN_START:
		swprintf_s(m_szTurnState, L"사일런트 : %s", L"준비");
		DrawDeck();


		// 페이즈 종료 조건
		if (m_iDrawCount == m_iDrawMax && m_bIsDrawing == false)
		{
			m_eTurnPhase = TURN_PLAY;
			m_iDrawCount = 0;
		}
		break;

	case TURN_PLAY:
		swprintf_s(m_szTurnState, L"사일런트 : %s", L"진행");
		if (m_bIsPlayerTurn)
		{
			if (m_vecDrawCard.size() == 0)
				return;
			Input();
			RotateDrawCard();
			IsPickingCard();
		}


		// 페이즈 종료 조건
		if (true)	
			m_eTurnPhase = TURN_PLAY;
		break;

	case TURN_END:
		swprintf_s(m_szTurnState, L"사일런트 : %s", L"종료");


		// 페이즈 종료 조건
		if (true)	
		{
			m_bIsPlayerTurn = !m_bIsPlayerTurn;
			m_eTurnPhase	= TURN_START;
		}
		break;
	}
}

void CGameMgr::Release()
{
	m_vecDeck.clear();
	m_vecDrawCard.clear();
	m_vecTomb.clear();
}

void CGameMgr::RenderState()
{
	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, 30.f, 10.f, 0.f);
	m_pDeviceMgr->GetSprite()->SetTransform(&matTrans);

	m_pDeviceMgr->GetFont()->DrawText(
		m_pDeviceMgr->GetSprite(),
		m_szTurnState,
		lstrlen(m_szTurnState),
		nullptr,
		0,
		D3DCOLOR_ARGB(255, 0, 180, 0));
}



// 카드 피킹 관련
void CGameMgr::IsPickingCard()					// 지저분해서 묶는용도로 사용 (IsPickingObject를 사용함)
{
	if (nullptr != m_SelectCard && m_SelectCard->GetCardInfo().bIsSelect)
		return;

	if (0 == m_vecDrawCard.size())
		return;

	for (auto iter : m_pObjectMgr->GetGameObject(OBJECT_CARD))
	{
		if (IsPickingObject(*iter))
		{
			m_SelectCard = dynamic_cast<CCard*>(iter);
			m_SelectCard->SetPicking(true);
			return;
		}
		else
			m_SelectCard = nullptr;
	}
}

bool CGameMgr::IsPickingObject(CGameObject& target)
{
	INFO info		= target.GetInfo();
	float fHalfCX	= target.GetInfo().fCenterX * 0.5f * target.GetScale().x;
	float fHalfCY	= target.GetInfo().fCenterY * 0.5f * target.GetScale().y;
	float mouseX	= CMouse::GetMousePos().x;
	float mouseY	= CMouse::GetMousePos().y;


	// 기울기(a) 4개 구함.
	float fGradient[4] =
	{
		fHalfCY / fHalfCX,
		-fHalfCY / fHalfCX,
		fHalfCY / fHalfCX,
		-fHalfCY / fHalfCX
	};

		// 점
	D3DXVECTOR3 vPoint[4] =
	{	// 
		D3DXVECTOR3(info.vPos.x - fHalfCX, info.vPos.y + fHalfCY, 0.f),
		D3DXVECTOR3(info.vPos.x + fHalfCX, info.vPos.y + fHalfCY, 0.f),
		D3DXVECTOR3(info.vPos.x + fHalfCX, info.vPos.y - fHalfCY, 0.f),
		D3DXVECTOR3(info.vPos.x - fHalfCX, info.vPos.y - fHalfCY, 0.f)
	};

	// y절편 4개 구함.
	// b = -ax + y
	float fB[4] =
	{
		-fGradient[0] * vPoint[0].x + vPoint[0].y,
		-fGradient[1] * vPoint[1].x + vPoint[1].y,
		-fGradient[2] * vPoint[2].x + vPoint[2].y,
		-fGradient[3] * vPoint[3].x + vPoint[3].y
	};

	if ((0 < fGradient[0] * mouseX + fB[0] - mouseY &&
		0 < fGradient[1] * mouseX + fB[1] - mouseY &&
		0 > fGradient[2] * mouseX + fB[2] - mouseY &&
		0 > fGradient[3] * mouseX + fB[3] - mouseY))
		return true;
	return false;
}

// 카드 정렬 관련
void CGameMgr::RotateDrawCard()
{
	// i가 0일떄 0으로 나눠서 에러뜸.
	float fAngle = 0;
	unsigned int iCardDisX = WINCX / (DRAW_CARD_MAX + 10);				// 중앙 부터 동일 비율로 배치하기위해서
	unsigned int iCardDisY = 300 / (DRAW_CARD_MAX + 10);
	float iHalfSize = (float)(m_vecDrawCard.size() / 2);

	int iCount = 0;
	for (auto iter : m_vecDrawCard)
	{
		if (iHalfSize == 0)
			fAngle = 0;
		else
			fAngle = -m_fCardAngleMax + (abs(m_fCardAngleMax) * 2 / (iHalfSize * 2))*iCount;

		if (iHalfSize > iCount)
		{
			iter->SetPos(
				(float)WINCX * 0.5f - (iCardDisX * (iHalfSize - (iCount + 1))),			// 0번 자리가  x가 0이여서 +1로 위치설정
				(float)WINCY - 100  + (iCardDisY * (iHalfSize  - (iCount + 1))),
				(float)iCount*0.1f);
		}
		else
		{
			iter->SetPos(
				(float)WINCX * 0.5f + (iCardDisX * ((iCount + 1) - iHalfSize)),
				(float)WINCY - 100  + (iCardDisY *  (iCount - iHalfSize)),
				(float)iCount*0.1f);
		}
		iter->SetRotate(fAngle);
		++iCount;
	}
}

void CGameMgr::UpdateCard()
{
	for (auto iter : m_vecDrawCard)
	{
		iter->SetRender(true);
		iter->SetPicking(false);
	}
	for (auto iter : m_vecTomb)
		iter->SetRender(false);
}

// 기타
void CGameMgr::Input()
{
	if (nullptr == m_SelectCard)
		return;

	if (m_pKeyMgr->KeyDown(KEY_LBUTTON))
	{	
		if (m_SelectCard->GetCardInfo().bIsSelect)
		{
			list<CGameObject*> TargetList = m_pObjectMgr->GetGameObject(OBJECT_MONSTER);
			TargetList.push_back(m_pObjectMgr->GetGameObject(OBJECT_PLAYER).front());
			
			for (auto iter : TargetList)
			{
				if (IsPickingObject(*iter))			
				{	// 유효한 대상인지 확인
					if (m_SelectCard->ActivateCard(dynamic_cast<CCharacter*>(iter)))
					{
						m_vecTomb.push_back(m_SelectCard);
						m_vecDrawCard.erase(find(m_vecDrawCard.begin(), m_vecDrawCard.end(), m_SelectCard));
						m_SelectCard->SetSelect(false);
						m_SelectCard = nullptr;
					}
					break;
				}
			}
		}
		else
			m_SelectCard->SetSelect(true);
	}
	
	
	if (m_pKeyMgr->KeyDown(KEY_RBUTTON))
		m_SelectCard->SetSelect(false);
}

void CGameMgr::DrawDeck()
{
	if (m_iDrawMax > m_iDrawCount && false == m_bIsDrawing)
	{
		m_bIsDrawing = true;
		m_vecDeck[m_iDrawCount]->SetPos(100, WINCY-200, 0);
		m_vecDrawCard.push_back(m_vecDeck[m_iDrawCount]);
	}
	
	if (m_bIsDrawing)
		m_vecDrawCard[m_iDrawCount]->MoveTo(D3DXVECTOR3(WINCX *0.5f, WINCY - 100, 0), (float)0.1* m_tDrawFrame.fCurFrame);
}

void CGameMgr::CountingFunc()
{	// 카드 뽑기 애니메이션 ?
	if (m_bIsDrawing)
	{
		m_tDrawFrame.fCurFrame += m_tDrawFrame.fMaxFrame * m_pTimeMgr->GetDelta() * 2.f;
		if (m_tDrawFrame.fMaxFrame <= m_tDrawFrame.fCurFrame)
		{
			m_tDrawFrame.fCurFrame = 0.f;
			RotateDrawCard();
			m_bIsDrawing = false;
			m_iDrawCount++;
		}
	}
}