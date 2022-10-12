#pragma once

#include "Transform.h"

BEGIN(Engine)

class ENGINE_DLL CGameObject abstract : public CBase
{
public:
	enum OBJECTSTATE { STATE_ALIVE, STATE_DEAD, STATE_END };

protected:
	explicit CGameObject(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	CGameObject(const CGameObject& rhs);
	virtual ~CGameObject() = default;

public:
	class CComponent* Get_Component(const _tchar* pComponentTag) {
		return Find_Component(pComponentTag);
	}
	_float Get_CamDistance() const {
		return m_fCamDistance;
	}

public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg, CTransform::TRANSFORMDESC* pTransformDesc = nullptr);
	virtual void Tick(_double TimeDelta);
	virtual void LateTick(_double TimeDelta);
	virtual HRESULT Render();
	virtual HRESULT Render_LightDepth() { return S_OK; }

protected:
	ID3D11Device*			m_pDevice = nullptr;
	ID3D11DeviceContext*	m_pDeviceContext = nullptr;

protected:
	static const _tchar*	m_pTransformTag;
	class CTransform*		m_pTransformCom = nullptr;

	class CTexture*			m_pObjectTextureCom = nullptr;
	class CTexture*			m_pObjectTexture2Com = nullptr;

protected:
	_bool					m_bCut = false;
	_float			m_fCamDistance = 0.f;

protected:
	void Compute_CamDistance();

protected:
	map<const _tchar*, class CComponent*>			m_Components;
	typedef map<const _tchar*, class CComponent*>	COMPONENTS;

protected:
	OBJECTSTATE m_eState = STATE_END;
public:
	OBJECTSTATE Get_State() { return m_eState; }
	void Set_Dead() { m_eState = STATE_DEAD; }
	_float Get_Randomfloat(_float _iStart, _float _iEnd);
	_uint Get_Randomint(_uint _iStart, _uint _iEnd);

protected:
	HRESULT SetUp_Components(const _tchar* pComponentTag, _uint iLevelIndex, const _tchar* pPrototypeTag, CComponent** ppOut, void* pArg = nullptr);

private:
	CComponent* Find_Component(const _tchar* pComponentTag);


public:	
	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END