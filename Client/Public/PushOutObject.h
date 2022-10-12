#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CModel;
class CCollider;
END

BEGIN(Client)

class CPushOutObject : public CGameObject
{
protected:
	explicit CPushOutObject(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CPushOutObject(const CPushOutObject& rhs);
	virtual ~CPushOutObject() = default;

public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta);
	virtual void LateTick(_double TimeDelta);
	virtual HRESULT Render();
	virtual HRESULT Render_LightDepth() { return S_OK; };

public:
	_bool Get_DeadCheck() { return m_bDeadCheck; }
	_int Get_TileIndex() { return m_Number;}
	_float3 Get_ColSize() { return m_fColSize; }
	void Set_DeadCheck(_bool bCheck) { m_bDeadCheck = bCheck; }
	void Set_TileIndex(_uint Index) { m_Number = Index; }
	void Set_ColSize(_float3 Size) { m_fColSize = Size; }

protected:
	CCollider*			m_pAABBCom = nullptr;
	_bool				m_bDeadCheck = false;
	_int				m_Number = -1;
	_float3				m_fColSize{};

public:
	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END