#include "stdafx.h"
#include "CharSelect.h"
#include "Mouse.h"


CCharSelect::CCharSelect()
	: m_eCurSelChar(CHARACTER_IRONCLAD)
{
}

CCharSelect::~CCharSelect()
{
	Release();
}

int CCharSelect::Update()
{
	m_Mouse = CMouse::GetMousePos();
	IsPicking();
	return 0;
}

void CCharSelect::LateUpdate()
{
}

void CCharSelect::Render()
{
	wstring str;
	wstring strButton;
	TCHAR szFullPath[MAX_STR];
	D3DXMATRIX scale, translation, matWorld;
	float fCenterX;
	float fCenterY;
	const TEX_INFO* pTexInfo;
	
	switch (m_eCurSelChar)
	{
	case CHARACTER_IRONCLAD:
		str = L"ironcladPortrait";
		break;
	case CHARACTER_SILENT:
		str = L"silentPortrait";
		break;
	case CHARACTER_DEFECT:
		str = L"defectPortrait";
		break;
	case CHARACTER_WATCHER:
		str = L"watcherPortrait";
		break;
	}
	
	// 선택된 초상화 띄우기
	pTexInfo = m_pTextureMgr->GetTexInfo(str);
	NULL_CHECK(pTexInfo);
	
	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;
	
	//   캐릭터 선택시 레터 박스 만들려고  y scale 0.8f
	D3DXMatrixScaling(&scale, 1, 0.8f, 1);
	D3DXMatrixTranslation(&translation, WINCX*0.5f, WINCY*0.5f, 1);
	matWorld = scale * translation;
	
	m_pDeviceMgr->GetSprite()->SetTransform(&matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	
	
	for(auto iter : m_vecButton)
	{
		szFullPath[0] = '\0';
		str = L"%sButton";
		swprintf_s(szFullPath, str.c_str(), iter->strCharName.c_str());
		pTexInfo = m_pTextureMgr->GetTexInfo(szFullPath);
		NULL_CHECK(pTexInfo);
	
		fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pTexInfo->tImgInfo.Height * 0.5f;
	
		D3DXMatrixScaling(&scale, 1, 1, 1);
		D3DXMatrixTranslation(&translation, iter->vPos.x, iter->vPos.y, iter->vPos.z);
		matWorld = scale * translation;
	
		m_pDeviceMgr->GetSprite()->SetTransform(&matWorld);
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
			nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}


	pTexInfo = m_pTextureMgr->GetTexInfo(L"ButtonHighLight");
	NULL_CHECK(pTexInfo);
	int iIndex = m_eCurSelChar;
	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;
	
	D3DXMatrixScaling(&scale, 1, 1, 1);
	D3DXMatrixTranslation(&translation, m_vecButton[iIndex]->vPos.x, m_vecButton[iIndex]->vPos.y, m_vecButton[iIndex]->vPos.z + 0.1);
	matWorld = scale * translation;
	
	m_pDeviceMgr->GetSprite()->SetTransform(&matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CCharSelect::Initialize()
{
	LPDIRECT3DDEVICE9 pGraphicDev = m_pDeviceMgr->GetDevice();
	NULL_CHECK_MSG_RETURN(pGraphicDev, L"pGraphicDev is null", E_FAIL);

	// 버튼 하이라이트
	HRESULT hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_SINGLE,
		L"../Resource/CharSelect/highlightButton.png",
		L"ButtonHighLight");

	// 캐릭터 초상화 + 버튼 로딩
	for(int i= 0; i<CHARACTER_END; ++i)
		LoadTextureCharacter(pGraphicDev, (PLAYABLE_CHARACTER)i);
	return S_OK;
}

void CCharSelect::Release()
{
	for_each(m_vecButton.begin(), m_vecButton.end(), SafeDelete<BUTTON_INFO*>);
	m_vecButton.clear();
}

CCharSelect* CCharSelect::Create()
{
	CCharSelect* pInstance = new CCharSelect;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CCharSelect::LoadTextureCharacter(LPDIRECT3DDEVICE9& pGraphicDev, PLAYABLE_CHARACTER eChar)
{
	wstring str;
	wstring path				= L"../Resource/CharSelect/%sPortrait.jpg";
	wstring strObjectKey		= L"%sPortrait";
	TCHAR szFullPath[MAX_STR]	= L"";
	TCHAR szObjectKey[MAX_STR]	= L"";
	
	switch (eChar)
	{
	case CHARACTER_IRONCLAD:
		str = L"ironclad";
		break;
	case CHARACTER_SILENT:
		str = L"silent";
		break;
	case CHARACTER_DEFECT:
		str = L"defect";
		break;
	case CHARACTER_WATCHER:
		str = L"watcher";
		break;
	default:
		MessageBox(g_hWnd, L"정의되지않은 캐릭 생성시도", L"조짐", MB_OK);
		break;
	}

	swprintf_s(szFullPath, path.c_str(), str.c_str());
	swprintf_s(szObjectKey, strObjectKey.c_str(), str.c_str());
	HRESULT hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_SINGLE,
		szFullPath,
		szObjectKey);
	FAILED_CHECK_MSG(hr, L"Character Portrait LoadTexture Failed");


	szFullPath[0]			= L'\0';
	szObjectKey[0]			= L'\0';
	path					= L"../Resource/CharSelect/%sButton.png";
	strObjectKey			= L"%sButton";
	swprintf_s(szFullPath, path.c_str(), str.c_str());
	swprintf_s(szObjectKey, strObjectKey.c_str(), str.c_str());
	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_SINGLE,
		szFullPath,
		szObjectKey);
	FAILED_CHECK_MSG(hr, L"Character Button LoadTexture Failed");

	BUTTON_INFO* info	= new BUTTON_INFO;
	info->vPos			={ (float)(WINCX /(CHARACTER_END + 1)*(eChar + 1)), WINCY * 0.8f, 0.5f};
	info->strCharName	= str.c_str();
	info->eChar			= eChar;
	m_vecButton.push_back(info);
}

void CCharSelect::IsPicking()
{
	RECT rect;
	if (m_Mouse.x < 0)
		return;

	for (auto iter : m_vecButton)
	{
		rect.left		= iter->vPos.x - SELECTBUTTONCX * 0.5f;
		rect.top		= iter->vPos.y - SELECTBUTTONCY * 0.5f;
		rect.right		= iter->vPos.x + SELECTBUTTONCX * 0.5f;
		rect.bottom		= iter->vPos.y + SELECTBUTTONCY * 0.5f;

		if (m_Mouse.x > rect.left &&
			m_Mouse.x < rect.right)
		{
			if (m_Mouse.y > rect.top &&
				m_Mouse.y < rect.bottom)
			{
				m_eCurSelChar = iter->eChar;
				if (m_pKeyMgr->KeyUp(KEY_LBUTTON))
				{
					switch (m_eCurSelChar)
					{
					case CHARACTER_IRONCLAD:
						FAILED_CHECK_MSG(E_FAIL, L"미구현된 캐릭터");
						break;
					case CHARACTER_SILENT:
						m_pSceneMgr->SceneChange(SCENE_CHARECTER_SELECTE, SCENE_WORLD_MAP);
						break;
					case CHARACTER_DEFECT:
						FAILED_CHECK_MSG(E_FAIL, L"미구현된 캐릭터");
						break;
					case CHARACTER_WATCHER:
						FAILED_CHECK_MSG(E_FAIL, L"미구현된 캐릭터");
						break;
					}

				}
				break;
			}
		}
	}
}
