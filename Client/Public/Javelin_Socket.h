#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CModel;
END

BEGIN(Client)

class CJavelin_Socket final : public CGameObject
{
public:
	typedef struct tagSocketDesc
	{
		class CModel*	pModelCom = nullptr;	
		const char*		pBoneName = nullptr;
		class CTransform* pTransform = nullptr;
		
	}SOCKETDESC;
private:
	explicit CJavelin_Socket(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CJavelin_Socket(const CJavelin_Socket& rhs);
	virtual ~CJavelin_Socket() = default;

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
	SOCKETDESC			m_SocketDesc;
	class CTransform*	m_pMyTransform = nullptr;
	_float4x4*			m_pSocketMatrix;
	_float4x4			m_PivotMatrix;
	_bool				m_bOn = false;
private:
	ID3D11ShaderResourceView*		m_pMaskSRV = nullptr;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();
	_uint				m_iMonsterType = 0;
	

public:
	static CJavelin_Socket* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END