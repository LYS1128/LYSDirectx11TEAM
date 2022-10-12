#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CCollider;
class CShader;
class CRenderer;
class CModel;
END

BEGIN(Client)

class CWeapon : public CGameObject
{
public:
	typedef struct tagSocketDesc
	{
		class CModel*	pModelCom = nullptr;	
		const char*		pBoneNameLeft = nullptr;
		const char*		pBoneNameRight = nullptr;

	}SOCKETDESC;


protected:
	explicit CWeapon(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CWeapon(const CWeapon& rhs);
	virtual ~CWeapon() = default;

public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg) ;
	virtual void Tick(_double TimeDelta) ;
	virtual void LateTick(_double TimeDelta) ;
	virtual HRESULT Render() ;

protected:
	CTransform*			m_pPlayerTransform = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;	
	
protected:
	_float4x4*			m_pLeftSocketMatrix;
	_float4x4*			m_pRightSocketMatrix;
	_float4x4			m_PivotMatrix;
	_float4x4			m_pLeftWorldMat;
	_float4x4			m_pRightWorldMat;

protected:


public:
	_float4x4 Get_LeftWorldMat() { return  m_pLeftWorldMat; }
	_float4x4 Get_RightWorldMat() { return  m_pRightWorldMat; }

public:
	void Set_HandInfo(EQUIP_HAND Hand) { m_eHand = Hand; }

protected:
	EQUIP_HAND m_eHand = EH_LEFT;

protected:
	CModel*				m_pLeftModelCom[EM_END]{};
	CModel*				m_pRightModelCom[EM_END]{};

protected:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable(_bool bLeft);

public:
	static CWeapon* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END