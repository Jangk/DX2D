#include "stdafx.h"
#include "Editor.h"
#include "Block.h"

Editor::Editor() :m_pKeyMgr(CKeyMgr::GetInstance()),
m_pDeviceMgr(CDeviceMgr::GetInstance()),
m_pObjectMgr(CObjectMgr::GetInstance()),
m_iSelector(0)
{
	
}

Editor::~Editor()
{
	Release();
}

int Editor::Update()
{
	GetMousePos();
	Input();
	return 0;
}

void Editor::LateUpdate()
{
}

void Editor::Render()
{
	for (auto iter : m_vecBlock)
		iter->Render();
}

HRESULT Editor::Initialize()
{
	LPDIRECT3DDEVICE9 pGraphicDev = m_pDeviceMgr->GetDevice();
	NULL_CHECK_MSG_RETURN(pGraphicDev, L"pGraphicDev is null", E_FAIL);

	 Block Object;
	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../Texture/Block/Block%d.png",
		L"Terrain",
		L"Block",
		5);
	FAILED_CHECK_MSG_RETURN(hr, L"Block LoadTexture Failed", E_FAIL);

	Block* block;
	for (int i = 0; i < WINCY / BLOCKCY; ++i)
	{
		for (int j = 0; j < WINCX / BLOCKCX; ++j)
		{
			block = Block::Create();
			block->SetBlock(BLOCK_EMPTY);
			block->SetPos(j*BLOCKCY + 15, i* BLOCKCX + 15, 0);
			m_vecBlock.push_back(block);
		}
	}
	return S_OK;
}

void Editor::Release()
{
	for_each(m_vecBlock.begin(), m_vecBlock.end(), SafeDelete<Block*>);
	m_vecBlock.clear();
}

Editor* Editor::Create()
{
	Editor* pInstance = new Editor;
	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	return pInstance;
}

void Editor::Input()
{
	if (m_pKeyMgr->KeyDown(KEY_S))
	{
		if (FileIOMgr::GetInstance()->SaveEditor(L"../Data/Block.dat", m_vecBlock))
			MessageBox(nullptr, L"���� ����!", L"", MB_OK);
		else
			MessageBox(nullptr, L"���� ����!", L"", MB_OK);
	}

	if (m_pKeyMgr->KeyDown(KEY_L))
	{
		if (FileIOMgr::GetInstance()->LoadEditor(L"../Data/Block.dat", m_vecBlock))
			MessageBox(nullptr, L"�ҷ����� ����!", L"", MB_OK);
		else
			MessageBox(nullptr, L"�ҷ����� ����!", L"", MB_OK);
	}


	if (m_pKeyMgr->KeyDown(KEY_LBUTTON))
	{
		GetMousePos();
		// ���콺 ��ŷ
		int i = m_ptMousePos.y / BLOCKCY; // ��
		int j = m_ptMousePos.x / BLOCKCX; // ��
		int iIndex = i * (WINCX / BLOCKCX) + j;

		if (0 > iIndex || (int)m_vecBlock.size() <= iIndex)
			return;

		m_vecBlock[iIndex]->SetBlock((BLOCK_TYPE)m_iSelector);
	}

	if (m_pKeyMgr->KeyDown(KEY_RBUTTON))
	{
		++m_iSelector; 
		if (m_iSelector > 5)
			m_iSelector = 0;
	}

}

void Editor::GetMousePos()
{
	GetCursorPos(&m_ptMousePos);
	ScreenToClient(g_hWnd, &m_ptMousePos);
}
