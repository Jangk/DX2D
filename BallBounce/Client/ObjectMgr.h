#pragma once

class CGameObject;
class CPlayer;
class CObjectMgr
{
	DECLARE_SINGLETON(CObjectMgr)

private:
	CObjectMgr();
	~CObjectMgr();

public:
	HRESULT AddObject(OBJECT_TYPE eType, CGameObject* pObject);
	int Update();
	void LateUpdate();
	void Render();
	CPlayer* GetPlayer();
	void DeleteGroup(OBJECT_TYPE eType);

private:
	void Release();

private:
	list<CGameObject*>	m_ObjectList[OBJECT_END];
	//CollisionMgr* m_pCollisionMgr;
};

