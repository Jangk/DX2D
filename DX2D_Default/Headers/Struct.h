#pragma once

typedef struct tagInfo
{
	D3DXVECTOR4 vPos;	// ��ġ���� (���п����� ��ġ���Ͷ�� ������ ����)
	D3DXVECTOR4 vDir;	// ���⺤��
	D3DXVECTOR4 vLook;	// ���� ��. �������Ҷ�
	D3DXMATRIX matWorld;// ������� = �� * �� * �� * �� * ��
						//         ������-����-�̵�-����-�θ����
	float fCX, fCY;
}INFO;