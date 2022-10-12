#pragma once

#include "GameObject.h"
#include "Client_Defines.h"

BEGIN(Engine)
class CCollider;
class CRenderer;
END

class CBoss_Map_Size : public CGameObject
{
public:
	explicit CBoss_Map_Size(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	explicit CBoss_Map_Size(const CBoss_Map_Size& rhs);
	virtual ~CBoss_Map_Size() = default;

public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta);
	virtual void LateTick(_double TimeDelta);
	virtual HRESULT Render();

private:
	HRESULT SetUp_Components();
	/*_matrix	matNewWorld = _matrix();
	_vector	vColPos = _vector();*/
private:
	/* 사이즈 확인용 */
	CRenderer*			m_pRendererCom = nullptr;
	CCollider*			m_pOBB_ABCom = nullptr;
	CCollider*			m_pOBB_ADCom = nullptr;
	CCollider*			m_pOBB_BCCom = nullptr;
public:
	static CBoss_Map_Size* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

