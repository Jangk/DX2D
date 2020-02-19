#include "stdafx.h"
#include "WorldMap.h"
#include "Mouse.h"


//해야할것 
//1. 월드맵 맵 스크롤 적용받게할것
//2. 월드맵이 top mid bot 연결되게 해야됨 (3개 크기가 모두 동일)

CWorldMap::CWorldMap() 
	: m_pScrollMgr(CScrollMgr::GetInstance()->GetInstance())
{
}


CWorldMap::~CWorldMap()
{
}

int CWorldMap::Update()
{
	float fMoveSpeed = 200.f * m_pTimeMgr->GetDelta();

	if (0.f + 200.f > CMouse::GetMousePos().y)
		CScrollMgr::MoveScrollPos(D3DXVECTOR3(0.f, -fMoveSpeed, 0.f));
	if ((float)WINCY -200.f < CMouse::GetMousePos().y)
		CScrollMgr::MoveScrollPos(D3DXVECTOR3(0.f, fMoveSpeed, 0.f));
	return NO_EVENT;
}

void CWorldMap::LateUpdate()
{
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
			pTexInfo = m_pTextureMgr->GetTexInfo(L"WorldMapTop");
		else if (iVecSize - 1 == i)
			pTexInfo = m_pTextureMgr->GetTexInfo(L"WorldMapBot");
		else
			pTexInfo = m_pTextureMgr->GetTexInfo(L"WorldMapMid");
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
}

HRESULT CWorldMap::Initialize()
{
	LPDIRECT3DDEVICE9 pGraphicDev = m_pDeviceMgr->GetDevice();
	NULL_CHECK_MSG_RETURN(pGraphicDev, L"pGraphicDev is null", E_FAIL);

	// 버튼 하이라이트
	HRESULT hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_SINGLE,
		L"../Resource/WorldMap/mapTop.png",
		L"WorldMapTop");
	FAILED_CHECK_MSG_RETURN(hr, L"월드맵 top 로드 실패", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_SINGLE,
		L"../Resource/WorldMap/mapMid.png",
		L"WorldMapMid");
	FAILED_CHECK_MSG_RETURN(hr, L"월드맵 Mid 로드 실패", E_FAIL);

	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_SINGLE,
		L"../Resource/WorldMap/mapBot.png",
		L"WorldMapBot");
	FAILED_CHECK_MSG_RETURN(hr, L"월드맵 Bot 로드 실패", E_FAIL);

	// top mid bottom 은 크키가 같아서 가능.
	const TEX_INFO* info = m_pTextureMgr->GetTexInfo(L"WorldMapMid");
	m_fImageScaleX	= 0.5f;
	m_fImageScaleY	= 0.5f;
	m_fWorldMapCX	= info->tImgInfo.Width;
	m_fWorldMapCY	= info->tImgInfo.Height;


	// 월드맵 위치 정보
	D3DVECTOR* temp;
	temp	= new D3DVECTOR;
	*temp	= { WINCX * 0.5f, WINCY * 0.5f, 0 };
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
	return S_OK;
}

void CWorldMap::Release()
{
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
