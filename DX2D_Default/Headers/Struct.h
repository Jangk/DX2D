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