#pragma once

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

private:
	list<CGameObject*>	m_ObjectList[OBJECT_END];
};

