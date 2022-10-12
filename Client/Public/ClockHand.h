#pragma once

#include "Client_Defines.h"
#include "LandObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CCollider;
class CModel;
END

BEGIN(Client)

class CClockHand final : public CLandObject
{
	enum STATE {
		LAP_1, TICK_1, IDLE
	};
private:
	explicit CClockHand(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CClockHand(const CClockHand& rhs);
	virtual ~CClockHand() = default;

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

	CGameObject*		m_pClockSSD = nullptr;
private:
	_uint				m_iAnimationIndex = 0;
	_float				m_fRenderTick = 0.f;
	_float				m_fRedTick = 0.f;
	_bool				bbb = false;
	_double				ttime = 0;
	void DotFailed();
	_matrix Get_NewMatrix(const char * pNodeName);
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();
	
	_double				m_Time = 0.0;
	_uint				m_iMove = 0;
public:
	static CClockHand* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END