#include "stdafx.h"
#ifndef __MYMATH_H__



static D3DXVECTOR3 MyLerp(D3DXVECTOR3 start, D3DXVECTOR3 end, float fSpeed)
{
	return start + (end - start) * fSpeed;
}
#endif // !__MYMATH_H__