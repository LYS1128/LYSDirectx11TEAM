#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CModel;
END

BEGIN(Client)

class CWater_Line_Effect0 final : public CGameObject
{
public:
	typedef struct tagWaterLineInfo {
		_float Length;
		_vector vPos;
	}WATERLINE;
private:
	explicit CWater_Line_Effect0(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CWater_Line_Effect0(const CWater_Line_Effect0& rhs);
	virtual ~CWater_Line_Effect0() = default;

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

private:
	_float				m_fFrame;
	_float				m_fDisolve;	
	_bool				m_bDeep;

	_vector vLook;
	_vector vPos;
	_vector vRight;
	_vector vUp;

public:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();

public:
	static CWater_Line_Effect0* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END