#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CCollider;
END

BEGIN(Client)

class CLucidInfo final : public CGameObject
{
public:
	typedef struct tagLucidInfo
	{
		EQUIP_INDEX eType = E_END;
		_float3 ePostion = _float3(0.f, 0.5f, 0.f);
		_float eRadius = 1.f;
		_uint eDamage = 1;
	}LUCIDINFO;
private:
	explicit CLucidInfo(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CLucidInfo(const CLucidInfo& rhs);
	virtual ~CLucidInfo() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	CCollider* m_pSphereCom = nullptr;
	_uint	m_iDamage = 1;
	EQUIP_INDEX m_eType = E_END;
	_uint	m_iCombo = 0;
	_uint	m_iTickCount = 0;
	_double m_CoolTime = 0.0;
	_bool	m_bSetCool = false;

public:
	_bool Collsion_Sphere(CCollider* pTargetCollider); //{ m_pSphereCom->Collsion_Sphere(pTargetCollider); }
	void Update(_fmatrix WorldMatrix); //{ m_pSphereCom->Update(WorldMatrix); }
	void Render_Col(); //{ m_pSphereCom->Render(); }
	void Set_Active(_bool Active); //{ m_pSphereCom->Set_Active(Active); }

public:
	void Plus_Time(_double Time) { m_CoolTime += Time; }
	void Set_Time_Zero() { m_CoolTime = 0.0; }
	_double Get_Time() { return m_CoolTime; }

	_bool Get_Cool() { return m_bSetCool; }
	void Set_Cool(_bool b) { m_bSetCool = b; }

	EQUIP_INDEX Get_Type() { return m_eType; }
	_uint Get_Damage() { return m_iDamage; }

	_uint Get_Combo() { return m_iCombo; }
	void Plus_Combo() { ++m_iCombo; }
	void Set_Combo(_uint i) { m_iCombo = i; }

	_uint Get_TickCount() { return m_iTickCount; }
	void Set_TickCount(_uint Count) { m_iTickCount = Count; }
	void Plus_TickCount() { ++m_iTickCount; }

public:
	static CLucidInfo* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END