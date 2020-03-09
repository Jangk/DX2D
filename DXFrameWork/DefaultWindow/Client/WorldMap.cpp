#include "stdafx.h"
#include "WorldMap.h"
#include "Mouse.h"
#include "Nord.h"


CWorldMap::CWorldMap() 
	: m_pScrollMgr(CScrollMgr::GetInstance()->GetInstance())
{
}


CWorldMap::~CWorldMap()
{
}

int CWorldMap::Update()
{
	if (m_pKeyMgr->KeyDown(KEY_LBUTTON))
		m_pSceneMgr->SceneChange(SCENE_WORLD_MAP, SCENE_STAGE);			// 일단 클릭만하면 씬넘어가게.

	for (int i = 0; i < 4; ++i)
		m_Nord[i]->Update();
	return ScrollScreen();
}

void CWorldMap::LateUpdate()
{
	for (int i = 0; i < 4; ++i)
		m_Nord[i]->LateUpdate();
}

void CWorldMap::Render()
{
	D3DXMATRIX scale, translation, matWorld;
	const TEX_INFO* pTexInfo;
	float fCenterX;
	float fCenterY;
	int iVecSize  = m_vecWorldMap.size();


	for (int i = 0; i < iVecSize; ++i)
	{
		if(0 == i)
			pTexInfo = m_pTextureMgr->GetTexInfo(L"WorldMap", L"Top", 1);
		else if (iVecSize - 1 == i)
			pTexInfo = m_pTextureMgr->GetTexInfo(L"WorldMap", L"Bot", 1);
		else
			pTexInfo = m_pTextureMgr->GetTexInfo(L"WorldMap", L"Mid", 1);

		NULL_CHECK(pTexInfo);
		fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		D3DXMatrixScaling(&scale, m_fImageScaleX, m_fImageScaleY, 0);
		D3DXMatrixTranslation(&translation, m_vecWorldMap[i]->x - CScrollMgr::GetInstance()->GetScrollPos().x,
											m_vecWorldMap[i]->y - CScrollMgr::GetInstance()->GetScrollPos().y,
											m_vecWorldMap[i]->z);
		matWorld = scale * translation;
		m_pDeviceMgr->GetSprite()->SetTransform(&matWorld);
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
			nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	for (int i = 0; i < 4; ++i)
		m_Nord[i]->Render();
}

HRESULT CWorldMap::Initialize()
{
	LPDIRECT3DDEVICE9 pGraphicDev = m_pDeviceMgr->GetDevice();
	NULL_CHECK_MSG_RETURN(pGraphicDev, L"pGraphicDev is null", E_FAIL);

	// top mid bottom 은 크키가 같아서 가능.
	const TEX_INFO* info = m_pTextureMgr->GetTexInfo(L"WorldMap", L"Mid", 1);
	m_fImageScaleX	= 0.5f;						// 월드맵 이미지 배율
	m_fImageScaleY	= 0.5f;
	m_fWorldMapCX	= info->tImgInfo.Width;
	m_fWorldMapCY	= info->tImgInfo.Height;


	// 월드맵 위치 정보
	D3DVECTOR* temp;
	temp	= new D3DVECTOR;
	*temp	= { WINCX * 0.5f, WINCY * 0.3f, 0 };
	m_vecWorldMap.push_back(temp);

	for (int i = 0; i < 1/*월드맵 중간에 추가할 갯수*/; ++i)
	{
		temp	= new D3DVECTOR;
		*temp	= { WINCX * 0.5f, m_vecWorldMap[m_vecWorldMap.size() - 1]->y + m_fWorldMapCY*0.5f ,0 };
		m_vecWorldMap.push_back(temp);
	}
	temp	= new D3DVECTOR;
	*temp	= { WINCX * 0.5f, m_vecWorldMap[m_vecWorldMap.size() - 1]->y + m_fWorldMapCY*0.5f, 0};
	m_vecWorldMap.push_back(temp);

	

	// 잠시 노드 배치.
	for (int i = 0; i < 4; ++i)
	{
		m_Nord[i] = CNord::Create();
		m_Nord[i]->SetPos(
			WINCX * 0.5f, ((float)WINCY + WORLDCY) - (200 * (i + 1)),	0);
		m_Nord[i]->SetNord(NORD_MONSTER);
	}

	return S_OK;
}

void CWorldMap::Release()
{
	for_each(m_vecWorldMap.begin(), m_vecWorldMap.end(), SafeDelete<D3DVECTOR*>);
}

CWorldMap * CWorldMap::Create()
{
	CWorldMap* pInstance = new CWorldMap;
	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	return pInstance;
}

int CWorldMap::ScrollScreen()
{
	float fMoveSpeed = 400.f * m_pTimeMgr->GetDelta();
	D3DVECTOR vScrollPos = m_pScrollMgr->GetScrollPos();

	// 화면 스크롤
	if (0.f + 200.f > CMouse::GetMousePos().y)
		m_pScrollMgr->MoveScrollPos(D3DXVECTOR3(0.f, -fMoveSpeed, 0.f));
	if ((float)WINCY - 200.f < CMouse::GetMousePos().y)
		m_pScrollMgr->MoveScrollPos(D3DXVECTOR3(0.f, fMoveSpeed, 0.f));
	return NO_EVENT;
}