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
	HRESULT InitCard(); // 처음에 카드를 전부 불러옴.
	int Update();
	void LateUpdate();
	void Render();

private:
	void Release();

private:
	CScene*			m_pScene;
	CDeviceMgr*		m_pDeviceMgr;
	CTextureMgr*	m_pTextureMgr;
};

