#pragma once

typedef struct tagInfo
{
	D3DXVECTOR3 vPos;	// 위치벡터 (수학에서는 위치벡터라는 개념이 없음)
	D3DXVECTOR3 vDir;	// 방향벡터
	D3DXVECTOR3 vLook;	// 기준 점. 각도구할때
	float fCX, fCY;
}INFO;