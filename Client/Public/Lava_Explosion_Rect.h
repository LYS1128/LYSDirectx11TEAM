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

class CLava_Explosion_Rect final : public CGameObject
{
public:
	typedef struct _tagExplosionDesc
	{
		_float				fDegree = 0.f;
		_float				fDist = 0.f;
		_float				fYPos = 0.f;
		_uint				iIndex = 0;
		_float				Scale = 0.f;
		class CTransform*	pTransform = nullptr;
	}EXPLOSIONDESC;

private:
	explicit CLava_Explosion_Rect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CLava_Explosion_Rect(const CLava_Explosion_Rect& rhs);
	virtual ~CLava_Explosion_Rect() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	void	FireScript9x5();
	

private:
	CTexture*			m_pTextureCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CVIBuffer_Rect*		m_pVIBufferCom = nullptr;
	CTexture*			m_pDisolveTexCom = nullptr;

private:
	SAVEPORTAL			m_PortalData;
	_uint				m_ModelIndex = 0;
	_double				m_Frame = 0.0;
	CTransform*			m_pResentTrans = nullptr;

	_bool				m_bLava;
	_double				m_dLava;
	_uint				m_iLava;
	_float				m_fLine;
	_float				m_fRow;
	_float				m_fCurrentLine;
	_float				m_fCurrentRow;
	_float				m_DownFrame;
	_uint				m_iIndex;
	_float				m_fDisolve = 0.f;
	_float				m_fAlpha = 0.f;
	_bool				m_bDisolve = false;



public:
	HRESULT SetUp_Components();

public:
	static CLava_Explosion_Rect* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END