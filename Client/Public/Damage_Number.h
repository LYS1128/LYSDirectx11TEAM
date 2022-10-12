#pragma once
#include "Client_Defines.h"
#include "UI.h"
#include "Text_Number.h"

BEGIN(Client)

class CDamage_Number final : public CUI
{
public:
	typedef struct tagDamageUIDesc
	{
		_vector vPos;
		_vector vRight;
		_vector vUp;
		_uint  iDamage;
		CText_Number::NUMINFO tNumInfo;
	}DAMAGEUI;
private:
	explicit CDamage_Number(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CDamage_Number(const CDamage_Number& rhs);
	virtual ~CDamage_Number() = default;

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
	DAMAGEUI m_tDamageInfo;

	_float m_fX = 0.f;
	_float m_fY = 0.f;

	_uint m_iCount = 0;
	_uint m_iImsiNumber = 0;

	_uint m_iAlphaTick = 0;
public:
	static CDamage_Number* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END