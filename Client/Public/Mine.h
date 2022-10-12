#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

#include "Mine_Manager.h"

BEGIN(Engine)
class CCollider;
class CShader;
class CRenderer;
class CModel;
END

BEGIN(Client)

class CMine final : public CGameObject
{
private:
	explicit CMine(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CMine(const CMine& rhs);
	virtual ~CMine() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	CCollider*			m_pSphereCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CModel*				m_pModelCom = nullptr;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

private:
	_bool m_bFail;
	_bool m_bRealMine;
	_bool m_bFakeMine;
	_uint m_iCntMine;
	_uint m_iIndex;
	_uint m_iMineResetCnt;

	 

public:
	static CMine* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END