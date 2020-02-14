#include "stdafx.h"
#include "MathMgr.h"


CMathMgr::CMathMgr()
{
}


CMathMgr::~CMathMgr()
{
}

void CMathMgr::MyMatrixIdentity(D3DXMATRIX* pOut)
{
	ZeroMemory(pOut, sizeof(D3DXMATRIX));

	for (int i = 0; i < 4; ++i)
		pOut->m[i][i] = 1.f;
}

void CMathMgr::MyMatrixScaling(D3DXMATRIX* pOut, float x, float y, float z)
{
	MyMatrixIdentity(pOut);

	pOut->_11 = x;
	pOut->_22 = y;
	pOut->_33 = z;
}

void CMathMgr::MyMatrixRotationZ(D3DXMATRIX* pOut, float fRadian)
{
	MyMatrixIdentity(pOut);

	pOut->_11 = cosf(fRadian);
	pOut->_12 = sinf(fRadian);
	pOut->_21 = -sinf(fRadian);
	pOut->_22 = cosf(fRadian);
}

void CMathMgr::MyMatrixTranslation(D3DXMATRIX* pOut, float x, float y, float z)
{
	MyMatrixIdentity(pOut);

	pOut->_41 = x;
	pOut->_42 = y;
	pOut->_43 = z;
}

void CMathMgr::MyTransformCoord(D3DXVECTOR3* pOut, const D3DXVECTOR3* pIn, const D3DXMATRIX* pMat)
{
	D3DXVECTOR4 vTemp;

	vTemp.x = pIn->x;
	vTemp.y = pIn->y;
	vTemp.z = pIn->z;
	vTemp.w = 1.f; // À§Ä¡º¤ÅÍ

	pOut->x = vTemp.x * pMat->_11 + vTemp.y * pMat->_21 + vTemp.z * pMat->_31 + vTemp.w * pMat->_41;
	pOut->y = vTemp.x * pMat->_12 + vTemp.y * pMat->_22 + vTemp.z * pMat->_32 + vTemp.w * pMat->_42;
	pOut->z = vTemp.x * pMat->_13 + vTemp.y * pMat->_23 + vTemp.z * pMat->_33 + vTemp.w * pMat->_43;
}

void CMathMgr::MyTransformNormal(D3DXVECTOR3* pOut, const D3DXVECTOR3* pIn, const D3DXMATRIX* pMat)
{
	D3DXVECTOR4 vTemp;

	vTemp.x = pIn->x;
	vTemp.y = pIn->y;
	vTemp.z = pIn->z;
	vTemp.w = 0.f; // ¹æÇâº¤ÅÍ

	pOut->x = vTemp.x * pMat->_11 + vTemp.y * pMat->_21 + vTemp.z * pMat->_31 + vTemp.w * pMat->_41;
	pOut->y = vTemp.x * pMat->_12 + vTemp.y * pMat->_22 + vTemp.z * pMat->_32 + vTemp.w * pMat->_42;
	pOut->z = vTemp.x * pMat->_13 + vTemp.y * pMat->_23 + vTemp.z * pMat->_33 + vTemp.w * pMat->_43;
}
