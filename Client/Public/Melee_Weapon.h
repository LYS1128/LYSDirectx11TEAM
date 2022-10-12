#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CModel;
END

BEGIN(Client)

class CMelee_Weapon final : public CGameObject
{

public:
	enum WP_TYPE
	{
		SWORD, SPEAR, WP_END
	};

	typedef struct tagSocketDesc
	{
		class CModel*		pModelCom = nullptr;
		class CTransform*	pTransform = nullptr;
		const char*			pBoneName = nullptr;
		WP_TYPE				pWP_TYPE = SWORD;

	}SOCKETDESC;

private:
	explicit CMelee_Weapon(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CMelee_Weapon(const CMelee_Weapon& rhs);
	virtual ~CMelee_Weapon() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:	
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;	
	CModel*				m_pModelCom[WP_END]{};

private:
	SOCKETDESC			m_SocketDesc;
	_float4x4*			m_pSocketMatrix;
	_float4x4			m_PivotMatrix;
	WP_TYPE				m_WPTYPE = SWORD;
	class CTransform*	m_pTargetTransform = nullptr;
	_uint				m_iMonsterType = 0;
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

	

public:
	static CMelee_Weapon* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END