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
	// CScene��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CStage* Create();

	// Update ����
	void RotateDrawCard();
	void IsPicking();
	void Input();
	void UpdateCard();
	void StartPlayerTurn();

private:
	// vecAllcard�� ���� �׽�Ʈ������ ���� ���߿��� �Ŵ����� �������� �����Ұ�.
	vector<CCard*> m_vecDeck;			// ��   ī��.  : ��ο쿡 ���Ե� ī��
	vector<CCard*> m_vecDrawCard;		// �ʵ� ī��.  : ���� �տ� ������ִ� ī��
	vector<CCard*> m_vecTomb;			// ���� ī��.  : ���ǰų� ������� ������ ī��.

	bool m_bIsPlayerTurn;
	bool m_bIsCardSelect;
	int m_fCardAngleMax;				// ��ο� ī�� ���� �ִ�ġ
	int m_iSelectedIndex;
};

