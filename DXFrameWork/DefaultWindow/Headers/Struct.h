#pragma once

typedef struct tagInfo
{
	D3DXVECTOR3 vPos;	// 위치벡터 (수학에서는 위치벡터라는 개념이 없음)
	D3DXVECTOR3 vDir;	// 방향벡터
	D3DXVECTOR3 vLook;
	D3DXVECTOR3 vSize;
	D3DXMATRIX matScale;
	D3DXMATRIX matRotate;
	D3DXMATRIX matTrans;
	D3DXMATRIX matGRotate;
	D3DXMATRIX matParents;
	D3DXMATRIX matWorld; // 월드행렬 = 스(케일) * 자(전) * 이(동) * 공(전) * 부(모행렬)

}INFO;

typedef struct tagTextureInfo
{
	LPDIRECT3DTEXTURE9 pTexture;
	D3DXIMAGE_INFO tImgInfo;
	int iImageMax;
}TEX_INFO;

typedef struct tagTileInfo
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSize;
	BYTE byDrawID;
	BYTE byOption;
}TILE_INFO;

typedef struct tagFrame
{
	float fCurFrame;
	float fMaxFrame;
}FRAME;


typedef struct tagSelectButtonInfo
{
	D3DXVECTOR3 vPos;
	PLAYABLE_CHARACTER eChar;
	wstring strCharName;
}BUTTON_INFO;

