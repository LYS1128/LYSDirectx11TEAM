#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CModel;
//class CCollider;
END

BEGIN(Client)

class CBubble_Effect final : public CGameObject
{
public:
	typedef struct tagBubbleDesc
	{
		_vector vPos = {};
		_bool	bLava = false;

	}BUBBLE;
private:
	explicit CBubble_Effect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CBubble_Effect(const CBubble_Effect& rhs);
	virtual ~CBubble_Effect() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:

	/*CCollider*			m_pSphereCom = nullptr;*/
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CModel*				m_pModelCom = nullptr;

public:
	_vector Get_Position() { return m_pTransformCom->Get_State(CTransform::STATE_POSITION); }


private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();


private:
	_float	m_fPercent = 0.f;
	_float	m_fPercent2 = 0.f;
	_uint				m_iCnt;

	_bool	m_bCheck = false;
	_bool	m_bLava = false;
	_bool	m_bLava_Explosion = false;
	_double m_dLava = 0.0;
	_uint	m_iLava = 0;
	_bool	m_bLavaRect = false;

	_vector vLook;
	_vector vLavaPos;
	_vector vRight;
	_vector vUp;

public:
	static CBubble_Effect* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END