#pragma once

#include "Client_Defines.h"
#include "PushOutObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CModel;
class CCollider;
END

BEGIN(Client)

class CDestruct final : public CPushOutObject
{
private:
	explicit CDestruct(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CDestruct(const CDestruct& rhs);
	virtual ~CDestruct() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render_LightDepth() override;
	virtual HRESULT Render() override;

private:
	class CTransform*		m_pEachTransformCom[9]{};
	void	Colliding(_uint _Level, _tchar * _Layer, _tchar * _ColliderCom);
private:
	CTexture*			m_pTextureCom = nullptr;
	CCollider*			m_pSphereCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CModel*				m_pModelCom[9]{};

public:
	_bool Get_bPlayerTouch() { return m_bPlayerTouch; }
	_vector Get_Position() { return m_pTransformCom->Get_State(CTransform::STATE_POSITION); }

public:
	void Set_Open(_bool Open) { m_bOpen = Open; }

private:
	_bool				m_bPlayerTouch = false;

	_bool				m_bOpen = false;
	_float				m_fPercent = 0.f;
	_bool				m_bAttacked = false;

	_bool				m_bFallDown;
	_vector				m_vCenterPos;
	_vector				m_vPos[9] = {};
	_vector				m_vLook[9] = {};
	_vector				m_vTargetLook;
	_vector				RotationAxis;
	_vector				DestructLook;
	_uint				m_iCnt;
	_float				m_fDisolveCnt;
	_bool				m_bDisolve;
	_bool				m_bColor;
	_float				m_fColorCnt;
	_bool				m_bCollapse;
	_uint				m_iCurrentCellIndex = 0;

	CTransform*			pTrans = nullptr;
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable(_uint Num);

public:
	static CDestruct* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END