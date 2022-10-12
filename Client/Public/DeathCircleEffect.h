#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CDeathCircleEffect final : public CUI
{
private:
	explicit CDeathCircleEffect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CDeathCircleEffect(const CDeathCircleEffect& rhs);
	virtual ~CDeathCircleEffect() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

public:
	HRESULT SetUp_Components();
	
private:
	_bool			m_bFirst = true;
	_float			m_fScale = 1.f;
	_float			m_fAlpha = 1.f;
	_float			m_fCount = 0.f;

public:
	static CDeathCircleEffect* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END