#pragma once

typedef struct tagInfo
{
	D3DXVECTOR4 vPos;	// 위치벡터 (수학에서는 위치벡터라는 개념이 없음)
	D3DXVECTOR4 vDir;	// 방향벡터
	D3DXVECTOR4 vLook;	// 기준 점. 각도구할때
	D3DXMATRIX matWorld;// 월드행렬 = 스 * 자 * 이 * 공 * 부
						//         스케일-자전-이동-공전-부모행렬
	float fCX, fCY;
}INFO;