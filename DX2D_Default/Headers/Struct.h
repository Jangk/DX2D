#pragma once

typedef struct tagInfo
{
	D3DXVECTOR3 vPos;	// ��ġ���� (���п����� ��ġ���Ͷ�� ������ ����)
	D3DXVECTOR3 vDir;	// ���⺤��
	D3DXVECTOR3 vLook;	// ���� ��. �������Ҷ�
	D3DXMATRIX matWorld;// ������� = �� * �� * �� * �� * ��
						//         ������-����-�̵�-����-�θ����
	float fCX, fCY;
}INFO;


typedef struct tagTextureInfo
{
	LPDIRECT3DTEXTURE9 pTexture;
	D3DXIMAGE_INFO tImgInfo;
}TEX_INFO;

// TestOnly
struct CUSTOMVERTEX
{	//    x, y, z, ����   == FVF ��Ģ�� ���� �� �� ������� �Ǿ���Ѵ�.
	float x, y, z, rhw;
	DWORD color;
};
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)