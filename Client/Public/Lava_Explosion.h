#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CModel;
class CTexture;
class CCollider;
END

BEGIN(Client)

class CLava_Explosion final : public CGameObject
{
public:
	typedef struct tagLavaExplosion {
		_float fDegree;
		_float fDist;
		CTransform* pExplosionTrans;
		_float fDisolveTime;
	}LAVA;


private:
	explicit CLava_Explosion(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CLava_Explosion(const CLava_Explosion& rhs);
	virtual ~CLava_Explosion() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;


private:
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CModel*				m_pModelCom = nullptr;
	CCollider*			m_pSphereCom = nullptr;
private:
	void				Player_Hit();
private:

	_float				m_Frame;
	_float				m_Disolve;
	_float				m_DownFrame;
	_float				m_fDisolveTime;
	_bool				m_bTrace = false;
	_bool				m_bCollied = false;

public:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

public:
	static CLava_Explosion* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END