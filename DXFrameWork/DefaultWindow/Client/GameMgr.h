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

	// vecAllcard는 지금 테스트용으로 쓰고 나중에는 매니저나 딴곳에서 관리할것.
	vector<CCard*>	m_vecDeck;			// 덱   카드.  : 드로우에 포함될 카드
	vector<CCard*>	m_vecDrawCard;		// 필드 카드.  : 현재 손에 들어져있는 카드
	vector<CCard*>	m_vecTomb;			// 무덤 카드.  : 사용되거나 턴종료시 버려진 카드.
	CCard*			m_SelectCard;		// 선택된 카드.


	// 기능 변수
	TURN_PHASE		m_eTurnPhase;
	TCHAR			m_szTurnState[MIN_STR];
	bool			m_bIsPlayerTurn;
	bool			m_bIsDrawing;


	// 최대치/카운터 변수
	float			m_fCardAngleMax;	// 드로우 카드 기울기 최대치
	int				m_iDrawMax;			// 뽑을 카드 수.
	int				m_iDrawCount;
	
	// 프레임 
	FRAME			m_tDrawFrame;
};