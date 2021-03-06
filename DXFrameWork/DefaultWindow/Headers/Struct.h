#pragma once

typedef struct tagInfo
{
	float		fCenterX;	// 이미지 크기 
	float		fCenterY;
	D3DXVECTOR3 vPos;		// 위치벡터 (수학에서는 위치벡터라는 개념이 없음)
	D3DXVECTOR3 vDir;		// 방향벡터
	D3DXVECTOR3 vLook;
	D3DXVECTOR3 vSize;
	D3DXMATRIX	matScale;
	D3DXMATRIX	matRotate;
	D3DXMATRIX	matTrans;
	D3DXMATRIX	matGRotate;
	D3DXMATRIX	matParents;
	D3DXMATRIX	matWorld; // 월드행렬 = 스(케일) * 자(전) * 이(동) * 공(전) * 부(모행렬)
}INFO;

typedef struct tagTextureInfo
{
	LPDIRECT3DTEXTURE9 pTexture;
	D3DXIMAGE_INFO tImgInfo;
	int iImageMax;
}TEX_INFO;

typedef struct tagTileInfo
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSize;
	BYTE byDrawID;
	BYTE byOption;
}TILE_INFO;

typedef struct tagFrame
{
	float fCurFrame;
	float fMaxFrame;
}FRAME;


typedef struct tagSelectButtonInfo
{
	D3DXVECTOR3 vPos;
	PLAYABLE_CHARACTER eChar;
	wstring strCharName;
}BUTTON_INFO;

typedef struct tagCharacterInfo
{
	bool	bIsPlayer;
	int		iCurHP;
	int		iMaxHP;
	int		iSheild;
	int		iCurCost;
	int		iMaxCost;
	int		iGold;
}CHARACTER_INFO;

typedef struct tagCardInfo
{
	CARD_TYPE		eCardType;
	TARGET_TYPE		eTargetType;
	TCHAR			szHead[MIN_STR];
	TCHAR			szType[MIN_STR];
	TCHAR			szInfo[MID_STR];
	bool			bIsSelect;
	bool			bIsRender;
	float			fImageSacle;			// 현재 모든 카드 이미지 크기 0.25배로 사용
	int				iCost;
	int				iAtt;					// 공격력 수치
	int				iAttCount;
	int				iDef;					// 방어력 수치
	int				iSpecial;				// 특수효과 수치
	int				iNamePositionFix;		// 카드 이름에 글자수에 비례해서 위치 이동(중앙에 배치하기위해서)
}CARD_INFO;