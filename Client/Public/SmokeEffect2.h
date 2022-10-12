#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CTexture;
class CRenderer;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CSmokeEffect2 final : public CGameObject
{
private:
	explicit CSmokeEffect2(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CSmokeEffect2(const CSmokeEffect2& rhs);
	virtual ~CSmokeEffect2() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	CTexture*			m_pTextureCom = nullptr;
	CTexture*			m_pMaskTextureCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CVIBuffer_Rect*		m_pVIBufferCom = nullptr;

	CTransform* Trans = nullptr;
private:
	_uint				m_iTileIndex = 0;
	_double				m_Frame = 0.0;

public:
	HRESULT SetUp_Components();

public:
	static CSmokeEffect2* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END