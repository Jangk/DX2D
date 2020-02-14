#include "stdafx.h"
#include "ObjectMgr.h"
#include "GameObject.h"
#include "Player.h"

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
		iter_end = m_ObjectList[i].end();

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
	CollisionMgr::GetInstance()->CollisionBlock(m_ObjectList[OBJECT_TERRAIN]);
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

CPlayer* CObjectMgr::GetPlayer()
{
	if(0 == m_ObjectList[OBJECT_PLAYER].size())
		return nullptr;
	return dynamic_cast<CPlayer*>(m_ObjectList[OBJECT_PLAYER].front());
}

void CObjectMgr::Release()
{
	for (int i = 0; i < OBJECT_END; ++i)
	{
		for_each(m_ObjectList[i].begin(), m_ObjectList[i].end(), SafeDelete<CGameObject*>);
		m_ObjectList[i].clear();
	}
}

void CObjectMgr::DeleteGroup(OBJECT_TYPE eType)
{
	for_each(m_ObjectList[eType].begin(), m_ObjectList[eType].end(), SafeDelete<CGameObject*>);
	m_ObjectList[eType].clear();
}
