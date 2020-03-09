#include "stdafx.h"
#include "ObjectMgr.h"
#include "GameObject.h"
#include "Player.h"
#include "Monster.h"
#include "Mouse.h"

IMPLEMENT_SINGLETON(CObjectMgr)

CObjectMgr::CObjectMgr()
{
}


CObjectMgr::~CObjectMgr()
{
	Release();
}

HRESULT CObjectMgr::AddObject(OBJECT_TYPE eType, CGameObject* pObject)
{
	NULL_CHECK_RETURN(pObject, E_FAIL);
	m_ObjectList[eType].push_back(pObject);

	return S_OK;
}

int CObjectMgr::Update()
{
	list<CGameObject*>::iterator iter_begin, iter_end;

	for(int i = 0; i < OBJECT_END; ++i)
	{
		iter_begin = m_ObjectList[i].begin();
		iter_end   = m_ObjectList[i].end();

		for (; iter_begin != iter_end; )
		{
			int iEvent = (*iter_begin)->Update();

			if (DEAD_OBJ == iEvent)
			{
				SafeDelete(*iter_begin);
				iter_begin = m_ObjectList[i].erase(iter_begin);
			}
			else
				++iter_begin;
		}
	}	

	return NO_EVENT;
}

void CObjectMgr::LateUpdate()
{
	for (int i = 0; i < OBJECT_END; ++i)
	{
		for (auto pObject : m_ObjectList[i])
			pObject->LateUpdate();
	}	
}

void CObjectMgr::Render()
{
	for (int i = 0; i < OBJECT_END; ++i)
	{
		for (auto pObject : m_ObjectList[i])
			pObject->Render();
	}
}

void CObjectMgr::Release()
{
	for (int i = 0; i < OBJECT_END; ++i)
	{
		for_each(m_ObjectList[i].begin(), m_ObjectList[i].end(), SafeDelete<CGameObject*>);
		m_ObjectList[i].clear();
	}
}

CPlayer* CObjectMgr::GetPlayer()
{
	return dynamic_cast<CPlayer*>(m_ObjectList[OBJECT_PLAYER].front());
}

const list<CGameObject*>& CObjectMgr::GetCardDeck()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_ObjectList[OBJECT_CARD];
}

bool CObjectMgr::IsPickingMonster()
{
	INFO info;
	float fHalfCX;
	float fHalfCY;
	float mouseX;
	float mouseY;

	for (auto iter : m_ObjectList[OBJECT_MONSTER])
	{
		info	= iter->GetInfo();
		fHalfCX = dynamic_cast<CMonster*>(iter)->GetCharacterInfo().m_fCenterX;
		fHalfCY = dynamic_cast<CMonster*>(iter)->GetCharacterInfo().m_fCenterX;
		mouseX	= CMouse::GetMousePos().x;
		mouseY	= CMouse::GetMousePos().y;

		// 점 ( 직선의 방정식이 아니면 y 반대로 안해도된다)
		D3DXVECTOR3 vPoint[4] =
		{	// 
			D3DXVECTOR3(info.vPos.x - fHalfCX, info.vPos.y - fHalfCY, 0.f),
			D3DXVECTOR3(info.vPos.x + fHalfCX, info.vPos.y - fHalfCY, 0.f),
			D3DXVECTOR3(info.vPos.x + fHalfCX, info.vPos.y + fHalfCY, 0.f),
			D3DXVECTOR3(info.vPos.x - fHalfCX, info.vPos.y + fHalfCY, 0.f)
		};

		if (vPoint[0].x  < mouseX && vPoint[1].x > mouseX &&
			vPoint[0].y < mouseY && vPoint[3].y > mouseY)
		{
			// 카드 효과 발동하게.
			dynamic_cast<CMonster*>(iter)->SetDamage(10);
			return true;
		}
	}
	return false;
}
