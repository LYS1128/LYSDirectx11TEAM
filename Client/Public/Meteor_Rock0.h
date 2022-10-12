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

class CMeteor_Rock0 final : public CGameObject
{
public:
	typedef struct _tagRockDesc
	{
		_float3 fPos;
		_vector vUp;
	}ROCKDESC;

private:
	explicit CMeteor_Rock0(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CMeteor_Rock0(const CMeteor_Rock0& rhs);
	virtual ~CMeteor_Rock0() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	CTexture*			m_pTextureCom = nullptr;
	CTexture*			m_pDisolveTexCom = nullptr;
	CTexture*			m_pMaskTexCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CVIBuffer_Rect*		m_pVIBufferCom = nullptr;

private:
	_float4x4			m_ProjMatrix;

	_float					m_fLine;
	_float					m_fRow;
	_float					m_fCurrentLine;
	_float					m_fCurrentRow;

	_float					m_fRed;
	_float					m_fGreen;
	_float					m_fBlue;

	_double				m_dTime;
	_float					m_fCnt;
	_float					m_fMCnt;
	_float					m_fDisolveCnt;
	_bool					m_bDisolve;

	_vector				Metoer_Up;

public:
	HRESULT SetUp_Components();

public:
	static CMeteor_Rock0* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END