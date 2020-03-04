#pragma once

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

private:
	void Release();

public:
	CPlayer* GetPlayer();

private:
	list<CGameObject*>	m_ObjectList[OBJECT_END];
};

