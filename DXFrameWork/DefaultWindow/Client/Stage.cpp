#include "stdafx.h"
#include "Stage.h"
#include "Terrain.h"
#include "Card.h"
#include "AttackCard.h"
#include "SkillCard.h"
#include "PowerCard.h"
#include "Card.h"
#include "Mouse.h"
#include "Player.h"
#include "Monster.h"


CStage::CStage()
{
}


CStage::~CStage()
{
	Release();
}

int CStage::Update()
{
	Input();
	m_pObjectMgr->Update();
	RotateDrawCard();
	if(!m_bIsCardSelect)
		IsPicking();
	return NO_EVENT;
}

void CStage::LateUpdate()
{
	m_pObjectMgr->LateUpdate();
}

void CStage::Render()
{
	// 배경
	D3DXMATRIX matScale;
	D3DXMATRIX matTrans;
	D3DXMATRIX matWorld;
	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"Stage", L"Background", 1);
	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMatrixScaling(&matScale, 1, 1, 1);
	D3DXMatrixTranslation(&matTrans, WINCX*0.5f, WINCY*0.5f, 1);
	matWorld = matScale * matTrans;
	m_pDeviceMgr->GetSprite()->SetTransform(&matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	
	
	m_pObjectMgr->Render();
}

HRESULT CStage::Initialize()
{
	m_bIsCardSelect		= false;
	m_fCardAngleMax		= 50;
	m_iSelectedIndex	= -1;			// 아무것도 선택되지않으면 -1

	m_pObjectMgr->AddObject(OBJECT_PLAYER, CPlayer::Create());
	m_pObjectMgr->AddObject(OBJECT_MONSTER, CMonster::Create());
	
	for (int i = 0; i < DRAW_CARD_MAX; ++i)
	{
		CCard* temp;
		temp = CAttackCard::Create();
		dynamic_cast<CAttackCard*>(temp)->SetCard(ATTACK_CARD_TYPE(i % ATTACK_CARD_END));
		m_vecAllCard.push_back(temp);
		m_pObjectMgr->AddObject(OBJECT_CARD, temp);

		// 현재 턴구현이 안되서 바로 드로우덱에 넣음
		m_vecDrawCard.push_back(m_vecAllCard[i]);
	}
	return S_OK;
}

void CStage::Release()
{
	m_vecAllCard.clear();
	m_vecDeck.clear();
	m_vecDrawCard.clear();
	m_vecTomb.clear();
}

CStage* CStage::Create()
{
	CStage* pInstance = new CStage;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CStage::RotateDrawCard()
{
	// i가 0일떄 0으로 나눠서 에러뜸.
	float fAngle = 0;
	int iHalfSize = m_vecAllCard.size() / 2;
	int iCardDisX = WINCX / (DRAW_CARD_MAX + 2);
	int iCardDisY = 300 / (DRAW_CARD_MAX + 2);


	for (int i = 0; i < m_vecAllCard.size(); ++i)
	{
		if (iHalfSize == 0)
			fAngle = 0;
		else
			fAngle = -m_fCardAngleMax + (abs(m_fCardAngleMax) * 2 / (iHalfSize * 2))*i;
		
		if (iHalfSize > i)
		{
			m_vecDrawCard[i]->SetPos(
				WINCX * 0.5f - (iCardDisX * (iHalfSize - (i + 1))),			// 0번 자리가  x가 0이여서 +1로 위치설정
				WINCY - 100  + (iCardDisY * (iHalfSize - (i + 1))),
				i*0.1f);
		}
		else
		{
			m_vecDrawCard[i]->SetPos(
				WINCX * 0.5f + (iCardDisX * ((i + 1) - iHalfSize)),
				WINCY - 100  + (iCardDisY * (i - iHalfSize)),
				i*0.1f);
		}
		m_vecDrawCard[i]->SetRotate(fAngle);
	}
}

void CStage::IsPicking()
{
	INFO info;
	float fHalfCX = m_vecDrawCard[0]->GetCardX() * 0.5f * m_vecDrawCard[0]->GetImageScale();
	float fHalfCY = m_vecDrawCard[0]->GetCardX() * 0.5f * m_vecDrawCard[0]->GetImageScale();
	float mouseX = CMouse::GetMousePos().x;
	float mouseY = CMouse::GetMousePos().y;


	// 카드 크기 전부 초기화.
	for (int i = 0; i < DRAW_CARD_MAX; ++i)
	{
		m_vecAllCard[i]->SetScale(
			m_vecAllCard[i]->GetImageScale(),
			m_vecAllCard[i]->GetImageScale(),
			0);
	}



	for (int i = 0; i < DRAW_CARD_MAX; ++i)
	{
		info = m_vecDrawCard[i]->GetInfo();
		
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
		{
			m_vecDrawCard[i]->SetPos(info.vPos.x, 600, 0);
			m_vecDrawCard[i]->SetRotate(0);
			m_vecDrawCard[i]->SetScale(m_vecDrawCard[i]->GetImageScale() * 2, m_vecDrawCard[i]->GetImageScale() * 2, 0);
			m_iSelectedIndex = i;
			return;				//가장 먼저된 카드를 선택되게하기위해
		}
	}
	m_iSelectedIndex = -1;
}

void CStage::Input()
{
	if (m_pKeyMgr->KeyDown(KEY_LBUTTON) && m_iSelectedIndex != -1)
	{
		m_vecDrawCard[m_iSelectedIndex]->SetSelect(true);
		m_bIsCardSelect = true;
	}
	if (m_pKeyMgr->KeyDown(KEY_RBUTTON))
	{
		for (int i = 0; i < DRAW_CARD_MAX; ++i)
			m_vecAllCard[i]->SetSelect(false);
		m_bIsCardSelect = false;
	}
}
