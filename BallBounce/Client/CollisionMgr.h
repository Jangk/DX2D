#pragma once
class CGameObject;
class CollisionMgr
{
	DECLARE_SINGLETON(CollisionMgr)
public:
	CollisionMgr();
	~CollisionMgr();


public:
	void CollisionBlock(OBJECT_LIST& block);
	bool IntersectRectEx(CGameObject* pDest, CGameObject* pSource, float* pMoveX, float* pMoveY);
private:
};

