#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CVIBuffer_Rect;
class CTexture;
END

BEGIN(Client)

class CAttack_Ring final : public CGameObject
{
private:
	explicit CAttack_Ring(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CAttack_Ring(const CAttack_Ring& rhs);
	virtual ~CAttack_Ring() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:	
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;	
	CTexture*			m_pTextureCom = nullptr;
	CVIBuffer_Rect*		m_pVIBufferCom = nullptr;



private:
	HRESULT SetUp_Components();
	

private:
	_float				m_fPercent;
	_float				m_fCnt;

	_double				m_dTime;
	
	_vector vLook;
	_vector vPos;
	_vector vRight;
	_vector vUp;

public:
	static CAttack_Ring* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END