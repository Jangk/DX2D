#pragma once
class CMathMgr
{
private:
	CMathMgr();
	~CMathMgr();

public:
	// 항등행렬 함수
	static void MyMatrixIdentity(D3DXMATRIX* pOut);

	// 크기행렬 함수
	static void MyMatrixScaling(D3DXMATRIX* pOut, float x, float y, float z);

	// Z축 회전 행렬 함수
	static void MyMatrixRotationZ(D3DXMATRIX* pOut, float fRadian);

	// 이동행렬 함수
	static void MyMatrixTranslation(D3DXMATRIX* pOut, float x, float y, float z);

	static void MyTransformCoord(D3DXVECTOR3* pOut, const D3DXVECTOR3* pIn, const D3DXMATRIX* pMat);
	static void MyTransformNormal(D3DXVECTOR3* pOut, const D3DXVECTOR3* pIn, const D3DXMATRIX* pMat);
};

