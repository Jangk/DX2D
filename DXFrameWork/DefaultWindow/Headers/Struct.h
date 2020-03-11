#pragma once

typedef struct tagInfo
{
	float		fCenterX;	// �̹��� ũ�� 
	float		fCenterY;
	D3DXVECTOR3 vPos;		// ��ġ���� (���п����� ��ġ���Ͷ�� ������ ����)
	D3DXVECTOR3 vDir;		// ���⺤��
	D3DXVECTOR3 vLook;
	D3DXVECTOR3 vSize;
	D3DXMATRIX	matScale;
	D3DXMATRIX	matRotate;
	D3DXMATRIX	matTrans;
	D3DXMATRIX	matGRotate;
	D3DXMATRIX	matParents;
	D3DXMATRIX	matWorld; // ������� = ��(����) * ��(��) * ��(��) * ��(��) * ��(�����)
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
	float			fImageSacle;			// ���� ��� ī�� �̹��� ũ�� 0.25��� ���
	int				iCost;
	int				iAtt;					// ���ݷ� ��ġ
	int				iAttCount;
	int				iDef;					// ���� ��ġ
	int				iSpecial;				// Ư��ȿ�� ��ġ
	int				iNamePositionFix;		// ī�� �̸��� ���ڼ��� ����ؼ� ��ġ �̵�(�߾ӿ� ��ġ�ϱ����ؼ�)
}CARD_INFO;