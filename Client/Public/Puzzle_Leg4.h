#pragma once

#include "Client_Defines.h"
#include "GameObject.h"
#include "Puzzle_Manager.h"

BEGIN(Engine)
class CCollider;
class CShader;
class CRenderer;
class CModel;
END

BEGIN(Client)

class CPuzzle_Leg4 final : public CGameObject
{
private:
	explicit CPuzzle_Leg4(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CPuzzle_Leg4(const CPuzzle_Leg4& rhs);
	virtual ~CPuzzle_Leg4() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

//public:
//	_bool Get_bPlayerTouch() { return m_bPlayerTouch; }
//	_vector Get_LinkedPortalPos() { return m_vLinkedPortalPos; }

private:	
	CCollider*			m_pAABBCom[2] = {};
	CCollider*			m_pSphereCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;	
	CModel*				m_pModelCom = nullptr;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();	

private:
	_vector m_vPos;
	_uint m_iPipeColor;
	_bool m_bPipe;
	_bool m_bSwitch;
	_uint m_iDegree;
	_uint m_iDir = 0;
	_uint m_iStartDir;
	_bool m_bStartRing;
	_uint m_iIndex;
	_uint m_Level;
//	_bool				m_bPlayerTouch = false;
//	_vector				m_vLinkedPortalPos = XMVectorSet(40.f,0.f,20.f,1.f);

public:
	static CPuzzle_Leg4* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END