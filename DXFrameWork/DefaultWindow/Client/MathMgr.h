#pragma once
class CMathMgr
{
private:
	CMathMgr();
	~CMathMgr();

public:
	// �׵���� �Լ�
	static void MyMatrixIdentity(D3DXMATRIX* pOut);

	// ũ����� �Լ�
	static void MyMatrixScaling(D3DXMATRIX* pOut, float x, float y, float z);

	// Z�� ȸ�� ��� �Լ�
	static void MyMatrixRotationZ(D3DXMATRIX* pOut, float fRadian);

	// �̵���� �Լ�
	static void MyMatrixTranslation(D3DXMATRIX* pOut, float x, float y, float z);

	static void MyTransformCoord(D3DXVECTOR3* pOut, const D3DXVECTOR3* pIn, const D3DXMATRIX* pMat);
	static void MyTransformNormal(D3DXVECTOR3* pOut, const D3DXVECTOR3* pIn, const D3DXMATRIX* pMat);
};

