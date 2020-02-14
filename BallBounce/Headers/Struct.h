#pragma once

typedef struct tagInfo
{
	D3DXVECTOR3 vPos;	// 위치벡터 (수학에서는 위치벡터라는 개념이 없음)
	D3DXVECTOR3 vDir;	// 방향벡터
	D3DXVECTOR3 vLook;
	D3DXMATRIX matWorld; // 월드행렬 = 스(케일) * 자(전) * 이(동) * 공(전) * 부(모행렬)

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

