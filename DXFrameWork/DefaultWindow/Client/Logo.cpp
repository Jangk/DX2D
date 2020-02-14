#include "stdafx.h"
#include "Logo.h"


CLogo::CLogo()
	: m_pKeyMgr(CKeyMgr::GetInstance())
{
}


CLogo::~CLogo()
{
	Release();
}

int CLogo::Update()
{
	if (m_pKeyMgr->KeyDown(KEY_RETURN))
	{
		m_pSceneMgr->SceneChange(SCENE_LOGO, SCENE_STAGE);
		return CHANGE_SCENE;
	}

	return NO_EVENT;
}

void CLogo::LateUpdate()
{
}

void CLogo::Render()
{
}

HRESULT CLogo::Initialize()
{
	return S_OK;
}

void CLogo::Release()
{
}

CLogo* CLogo::Create()
{
	CLogo* pInstance = new CLogo;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
