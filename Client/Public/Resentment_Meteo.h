#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CCollider;
class CRenderer;
class CModel;
END

BEGIN(Client)

class CResentment_Meteo final : public CGameObject
{
private:
	explicit CResentment_Meteo(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CResentment_Meteo(const CResentment_Meteo& rhs);
	virtual ~CResentment_Meteo() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;
public:
	void Player_Hit();
private:	
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CModel*				m_pModelCom = nullptr;
	CCollider*			m_pSphereCom = nullptr;
	//CTexture*			m_pDisolveTexCom = nullptr;
private:

	_vector				m_vPosition = _vector();
	_float4				m_fPosition = _float4();

	_double				m_dTimeDelta = 0.0;
	_float				m_fPercent;

	//Ã¤¿¬
	_double				m_Time = 0.0;
	_float				m_fMove = 0.f;
	CGameObject*		m_Blast = nullptr;
	CGameObject*		m_Fire = nullptr;
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

public:
	static CResentment_Meteo* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END