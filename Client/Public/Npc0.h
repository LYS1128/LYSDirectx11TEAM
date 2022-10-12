#pragma once

#include "Client_Defines.h"
#include "LandObject.h"

BEGIN(Engine)
class CShader;
class CCollider;
class CRenderer;
class CModel;
END

BEGIN(Client)

class CNpc0 final : public CLandObject
{
public:

private:
	explicit CNpc0(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CNpc0(const CNpc0& rhs);
	virtual ~CNpc0() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;
	HRESULT Render_LightDepth();

	void			Set_Anim(_uint	iAnimationIndex) { m_iAnimationIndex = iAnimationIndex; }
	void			Set_CurrentIndex(_uint Index) { m_iCurrentCellIndex = Index; }
private:
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CModel*				m_pModelCom = nullptr;
	

private:
	_uint				m_iCurrentCellIndex = 0;

private:	/* For .Animation */
	_uint				m_iAnimationIndex = 0;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

public:
	static CNpc0* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END