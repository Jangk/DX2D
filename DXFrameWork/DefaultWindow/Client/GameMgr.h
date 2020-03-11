#pragma once
class CCard;
class CGameMgr
{
	DECLARE_SINGLETON(CGameMgr)
private:
	CGameMgr();
public:
	~CGameMgr();

public:
	void Initialize();
	void Update();
	void Release();
	void RenderState();


private:
	void RotateDrawCard();
	void IsPickingCard();
	void Input();
	void UpdateCard();
	void DrawDeck();
	void CountingFunc();

public:
	bool IsPickingObject(CGameObject& target);


private:
	CDeviceMgr*		m_pDeviceMgr;
	CTextureMgr*	m_pTextureMgr;
	CTimeMgr*		m_pTimeMgr;
	CSceneMgr*		m_pSceneMgr;
	CObjectMgr*		m_pObjectMgr;
	CKeyMgr*		m_pKeyMgr;
	CScrollMgr*		m_pScrollMgr;

	// vecAllcard�� ���� �׽�Ʈ������ ���� ���߿��� �Ŵ����� �������� �����Ұ�.
	vector<CCard*>	m_vecDeck;			// ��   ī��.  : ��ο쿡 ���Ե� ī��
	vector<CCard*>	m_vecDrawCard;		// �ʵ� ī��.  : ���� �տ� ������ִ� ī��
	vector<CCard*>	m_vecTomb;			// ���� ī��.  : ���ǰų� ������� ������ ī��.
	CCard*			m_SelectCard;		// ���õ� ī��.


	// ��� ����
	TURN_PHASE		m_eTurnPhase;
	TCHAR			m_szTurnState[MIN_STR];
	bool			m_bIsPlayerTurn;
	bool			m_bIsDrawing;


	// �ִ�ġ/ī���� ����
	float			m_fCardAngleMax;	// ��ο� ī�� ���� �ִ�ġ
	int				m_iDrawMax;			// ���� ī�� ��.
	int				m_iDrawCount;
	
	// ������ 
	FRAME			m_tDrawFrame;
};