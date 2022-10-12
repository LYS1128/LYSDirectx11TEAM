#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CUI_SubAbility_Coltime final : public CUI
{
public:
	typedef struct tagAbilityColInfo
	{
		_float fX;
		_float fY;
		_float fColtime;
		_uint iIndex;
	}ABILCOLTIMEINFO;
private:
	explicit CUI_SubAbility_Coltime(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_SubAbility_Coltime(const CUI_SubAbility_Coltime& rhs);
	virtual ~CUI_SubAbility_Coltime() = default;

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

	ABILCOLTIMEINFO m_tAbilColInfo;
	_float m_fColtime = 0.f;
	_uint  m_iColtime = 0;
	_float m_fMaxColtime = 0.f;
	_bool  m_bLetsGo = false;
	_bool  m_bCheck = false;
public:
	static CUI_SubAbility_Coltime* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END