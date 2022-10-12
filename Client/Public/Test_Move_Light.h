#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CTexture;
class CRenderer;
class CVIBuffer_Rect;
class CLight;
END

BEGIN(Client)

class CTest_Move_Light final : public CGameObject
{
public:
	typedef struct _tagUI
	{
		_vector Pos;
		_uint	Option;
	}LIGHT;


private:
	explicit CTest_Move_Light(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CTest_Move_Light(const CTest_Move_Light& rhs);
	virtual ~CTest_Move_Light() = default;

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

private:
	_float				m_Frame = 1.0f;
	_double				Time = 0.0;
	_uint				Rand = rand();
	CLight*				m_pLight = nullptr;
	CLight*				m_pLight2 = nullptr;

	_vector				m_vPos = _vector();

	_uint				m_iOption = 0;
public:
	HRESULT SetUp_Components();

public:
	static CTest_Move_Light* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END