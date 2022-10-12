#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CModel;
class CCollider;
class CVIBuffer_Trail;
END

BEGIN(Client)

class CMeleePiercing final : public CGameObject
{
public:
	enum MOVESTATE{STATE_IDLE, STATE_MOVE, STATE_ATTACK, STATE_END};

private:
	explicit CMeleePiercing(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CMeleePiercing(const CMeleePiercing& rhs);
	virtual ~CMeleePiercing() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	void Update_State(_double TimeDelta);

private:	
	CTexture*			m_pTextureCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CCollider*			m_pSphereCom = nullptr;
	CModel*				m_pModelCom = nullptr;
	CTransform*		m_PlayerTrans = nullptr;

private:
	_bool m_isAttack = false;
	_float m_AttackLength = 5.f;
	_vector m_AttackDest = _vector();
	_vector m_tempPos = _vector();
	_float m_Lerp = 0.f;
	_bool m_Lerpflag = false;
	_bool m_isCoolTime = false;
	_double m_AccCoolTime = 0.0;
	_double m_CoolTime = 0.8f;

	_float m_Speed = 1.f;
	_float m_AccTime = 0.f;
	MOVESTATE m_State = STATE_IDLE;
	_vector	m_PrevPlayerPos = _vector();

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();
	

public:
	static CMeleePiercing* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END