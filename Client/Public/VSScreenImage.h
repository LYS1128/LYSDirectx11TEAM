#pragma once
#include "Client_Defines.h"
#include "GameObject.h"
#include "Ending_Tips.h"
BEGIN(Engine)
class CShader;
class CTexture;
class CRenderer;
class CVIBuffer_Rect;
END

BEGIN(Client)
class CVSScreenImage final : public CGameObject
{

private:
	explicit CVSScreenImage(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CVSScreenImage(const CVSScreenImage& rhs);
	virtual ~CVSScreenImage() = default;

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

public:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

private:
	_float				m_fX, m_fY, m_fSizeX, m_fSizeY;
	_uint				m_iSprite = 0;
	_float m_fPercent = 0.f;

	CEnding_Tips::ENDTIPINFO m_tInfo;

	_bool m_bCheck = false;

public:
	static CVSScreenImage* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END


