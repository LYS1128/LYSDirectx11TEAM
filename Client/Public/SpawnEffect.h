#pragma once

#include "Client_Defines.h"
#include "LandObject.h"

BEGIN(Engine)
class CCollider;
class CTexture;
class CShader;
class CRenderer;
class CModel;
END

BEGIN(Client)

class CSpawnEffect final : public CLandObject
{
private:
	explicit CSpawnEffect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CSpawnEffect(const CSpawnEffect& rhs);
	virtual ~CSpawnEffect() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	CCollider*			m_pSphereCom = nullptr;
	CTexture*			m_pTextureCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;	
	CModel*				m_pModelCom = nullptr;

	_uint			m_SpawnX = 0;
	_uint			m_SpawnY = 0;
	CGameObject*	 Particle = nullptr;
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();	

public:
	static CSpawnEffect* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END