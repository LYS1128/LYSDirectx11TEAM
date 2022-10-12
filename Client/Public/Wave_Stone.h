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

class CWave_Stone final : public CGameObject
{
public:
	typedef struct tagStone {
		_float fDegree;
		_float fDist;
		_float fRotationDegree;
		CTransform* pResentTrans;
		_float fDisolveTime;
	}STONE;


private:
	explicit CWave_Stone(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CWave_Stone(const CWave_Stone& rhs);
	virtual ~CWave_Stone() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;
private:
	void				Player_Hit();

private:
	CTexture*			m_pDisolveTexCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CModel*				m_pModelCom = nullptr;
	CCollider*			m_pSphereCom = nullptr;
private:
	_float				m_Frame;
	_float				m_Disolve;
	_float				m_fDisolveTime;
	_bool				m_bTrace = false;

public:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

public:
	static CWave_Stone* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END