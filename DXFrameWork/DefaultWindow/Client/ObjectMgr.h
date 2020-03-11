#pragma once

class CPlayer;
class CCard;
class CGameObject;
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
	const list<CGameObject*> GetGameObject(OBJECT_TYPE eType);
	void DeleteGruop(OBJECT_TYPE eType);

private:
	list<CGameObject*>	m_ObjectList[OBJECT_END];
};

