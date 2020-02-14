#pragma once

class CScene;
class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr)

private:
	CSceneMgr();
	~CSceneMgr();

public:
	HRESULT SceneChange(SCENE_TYPE eCurType, SCENE_TYPE eNextType);
	int Update();
	void LateUpdate();
	void Render();

private:
	void Release();

private:
	CScene*	m_pScene;
};

