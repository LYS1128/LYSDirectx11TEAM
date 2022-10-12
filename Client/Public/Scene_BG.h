#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CScene_BG final : public CUI
{

private:
	explicit CScene_BG(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CScene_BG(const CScene_BG& rhs);
	virtual ~CScene_BG() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

public:
	HRESULT SetUp_Components();

private:
	_bool m_bButton = false;
	_bool m_bFadeEnd = false;
	_bool m_flag = false;
public:
	void Set_FadeEnd(_bool b) {
		m_bFadeEnd = b;
	}
public:
	static CScene_BG* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END