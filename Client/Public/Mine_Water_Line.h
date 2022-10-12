#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CModel;
END

BEGIN(Client)

class CMine_Water_Line final : public CGameObject
{
public:
	typedef struct tagWaterLineInfo {
		_vector vPos;
	}WATERLINE;
private:
	explicit CMine_Water_Line(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CMine_Water_Line(const CMine_Water_Line& rhs);
	virtual ~CMine_Water_Line() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

public:
	void Set_Deep() { m_bDeep = true; }

private:
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CModel*				m_pModelCom = nullptr;
	CTexture*			m_pTextureCom = nullptr;

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
	static CMine_Water_Line* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END