#pragma once
class CDeviceMgr
{
	DECLARE_SINGLETON(CDeviceMgr)

private:
	CDeviceMgr();
	~CDeviceMgr();

public:
	LPDIRECT3DDEVICE9 GetDevice() const;
	LPD3DXSPRITE GetSprite() const;

public:
	HRESULT InitDevice(DISPLAY_MODE eMode);
	void Render_Begin();
	void Render_End();
	void Release();

private:
	// IDirect3D9�� ������
	// IDirect3D9: ��ġ�� �����ϰ� IDirect3DDevice9�� �����ϴ� COM��ü.
	LPDIRECT3D9			m_pSDK;

	// IDirect3DDevice9�� ������
	// IDirect3DDevice9: �׷��� ī�带 �����ϱ� ���� COM��ü.
	LPDIRECT3DDEVICE9	m_pGraphicDev;

	// ID3DXSprite�� ������
	// ID3DXSprite: DirectX���� 2D �ؽ�ó�� �ս��� �������ϵ��� �����ִ� COM��ü.
	LPD3DXSPRITE m_pSprite;

	// COM (Component Object Model)
	// ��ǰ �����ϵ� ���α׷��� ����!
	// ����ũ�μ���Ʈ���� ������ ���α׷��� ��.
};

