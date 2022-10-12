#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CModel;
//class CCollider;
END

BEGIN(Client)

class CRanged_Effect2 final : public CGameObject
{
private:
	explicit CRanged_Effect2(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CRanged_Effect2(const CRanged_Effect2& rhs);
	virtual ~CRanged_Effect2() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:	
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;	
	CModel*				m_pModelCom = nullptr;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

private:
	_float				m_fCnt;
	_float				m_fPercent;
	//8.25
	_float				m_fRed;
	_float				m_fGreen;
	_float				m_fBlue;

	_vector vLook;
	_vector vPos;
	_vector vRight;
	_vector vUp;

public:
	static CRanged_Effect2* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END