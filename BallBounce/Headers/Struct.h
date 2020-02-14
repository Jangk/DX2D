#pragma once

typedef struct tagInfo
{
	D3DXVECTOR3 vPos;	// ��ġ���� (���п����� ��ġ���Ͷ�� ������ ����)
	D3DXVECTOR3 vDir;	// ���⺤��
	D3DXVECTOR3 vLook;
	D3DXMATRIX matWorld; // ������� = ��(����) * ��(��) * ��(��) * ��(��) * ��(�����)

}INFO;

typedef struct tagTextureInfo
{
	LPDIRECT3DTEXTURE9 pTexture;
	D3DXIMAGE_INFO tImgInfo;
}TEX_INFO;

typedef struct tagTileInfo
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSize;
	BYTE byDrawID;
	BYTE byOption;
}TILE_INFO;

typedef struct tagSaveBlockInfo
{
	TILE_INFO tInfo;
	BLOCK_TYPE eBlockType;
}SAVE_INFO;


typedef struct posAndImageSizeInfo
{
	D3DXVECTOR3 vPos;
	RECT m_Rect;
	float fCX;
	float fCY;
}TOTAL_INFO;


class CGameObject;
typedef list<CGameObject*> OBJECT_LIST;

