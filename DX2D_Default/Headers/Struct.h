#pragma once

typedef struct tagInfo
{
	D3DXVECTOR3 vPos;	// 위치벡터 (수학에서는 위치벡터라는 개념이 없음)
	D3DXVECTOR3 vDir;	// 방향벡터
	D3DXVECTOR3 vLook;	// 기준 점. 각도구할때
	D3DXMATRIX matWorld;// 월드행렬 = 스 * 자 * 이 * 공 * 부
						//         스케일-자전-이동-공전-부모행렬
	float fCX, fCY;
}INFO;


typedef struct tagTextureInfo
{
	LPDIRECT3DTEXTURE9 pTexture;
	D3DXIMAGE_INFO tImgInfo;
}TEX_INFO;

// TestOnly
struct CUSTOMVERTEX
{	//    x, y, z, 깊이   == FVF 규칙에 의해 꼭 이 순서대로 되어야한다.
	float x, y, z, rhw;
	DWORD color;
};
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)