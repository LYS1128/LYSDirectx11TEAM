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

class CSpawnEffect2 final : public CLandObject
{
private:
	explicit CSpawnEffect2(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CSpawnEffect2(const CSpawnEffect2& rhs);
	virtual ~CSpawnEffect2() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	CTexture*			m_pTextureCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;	
	CModel*				m_pModelCom = nullptr;

	_float			m_SpawnX = 0.f;
	_float			m_SpawnY = 0.f;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();	

public:
	static CSpawnEffect2* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END