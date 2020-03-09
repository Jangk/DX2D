#pragma once
#include "Scene.h"
class CCard;
class CStage : public CScene
{
private:
	CStage();

public:
	virtual ~CStage();

public:
	// CScene을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CStage* Create();

	// Update 영역
	void RotateDrawCard();
	void IsPicking();
	void Input();
	void UpdateCard();
	void StartPlayerTurn();

private:
	// vecAllcard는 지금 테스트용으로 쓰고 나중에는 매니저나 딴곳에서 관리할것.
	vector<CCard*> m_vecDeck;			// 덱   카드.  : 드로우에 포함될 카드
	vector<CCard*> m_vecDrawCard;		// 필드 카드.  : 현재 손에 들어져있는 카드
	vector<CCard*> m_vecTomb;			// 무덤 카드.  : 사용되거나 턴종료시 버려진 카드.

	bool m_bIsPlayerTurn;
	bool m_bIsCardSelect;
	int m_fCardAngleMax;				// 드로우 카드 기울기 최대치
	int m_iSelectedIndex;
};

