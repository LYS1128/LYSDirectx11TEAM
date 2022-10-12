#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CTexture;
class CVIBuffer_Point_Instance;
END

BEGIN(Client)

class CPoint_Effect3 final : public CGameObject
{
private:
	explicit CPoint_Effect3(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CPoint_Effect3(const CPoint_Effect3& rhs);
	virtual ~CPoint_Effect3() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	CRenderer*						m_pRendererCom = nullptr;
	CShader*						m_pShaderCom = nullptr;
	CTexture*						m_pTextureCom = nullptr;
	CVIBuffer_Point_Instance*		m_pVIBufferCom = nullptr;

private:
	_uint m_iShaderIndex = 0;
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

public:
	static CPoint_Effect3* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END