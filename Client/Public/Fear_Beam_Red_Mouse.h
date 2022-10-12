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

class CFear_Beam_Red_Mouse final : public CGameObject
{
private:
	explicit CFear_Beam_Red_Mouse(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CFear_Beam_Red_Mouse(const CFear_Beam_Red_Mouse& rhs);
	virtual ~CFear_Beam_Red_Mouse() = default;

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
	CVIBuffer_Rect*		m_pVIBufferCom = nullptr;

	CTransform*			m_pParticleTransform = nullptr;
	CGameObject*		m_pParticle = nullptr;



private:
	SAVEPORTAL			m_PortalData;
	_uint				m_ModelIndex = 0;
	_double				m_Frame = 0.0;

	_bool				m_isOne = true;

	_vector				m_Pos = _vector();

	_matrix				m_MatPos = _matrix();
public:
	HRESULT SetUp_Components();

public:
	static CFear_Beam_Red_Mouse* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END