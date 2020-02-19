#pragma once
class CScrollMgr
{
	DECLARE_SINGLETON(CScrollMgr)

private:
	CScrollMgr();
	~CScrollMgr();

public:
	static const D3DXVECTOR3& GetScrollPos();

public:
	static void MoveScrollPos(const D3DXVECTOR3& vMove);

private:
	static D3DXVECTOR3 m_vScrollPos;
};

