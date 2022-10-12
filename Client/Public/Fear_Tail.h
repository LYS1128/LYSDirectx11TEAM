#pragma once

#include "Client_Defines.h"
#include "Enemy.h"

BEGIN(Engine)
class CShader;
class CCollider;
class CRenderer;
class CModel;
END

BEGIN(Client)

class CFear_Tail final : public CGameObject
{
public:

	typedef struct _tagTailDesc	{
		_vector	_Position{};
		_vector _Look{};
		_float	_Radian;

	}TAILDESC;
private:
	explicit CFear_Tail(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CFear_Tail(const CFear_Tail& rhs);
	virtual ~CFear_Tail() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;
public:
	void Player_Hit();
private:	
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CModel*				m_pModelCom = nullptr;
	CCollider*			m_pSphereCom = nullptr;
	CTexture*			m_pDisolveTexCom = nullptr;
private:
	CTransform*			m_pTransform = nullptr;
	_vector				m_vPosition{};
	_float4				m_fPosition{};
	TAILDESC			m_TailDesc;
	_double				m_dTimeDelta = 0.0;
	_float				m_fPercent;
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

public:
	static CFear_Tail* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END