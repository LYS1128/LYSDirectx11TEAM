#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CModel;
END

BEGIN(Client)

class CLavaFlow_Part final : public CGameObject
{
public:
	typedef struct tagTreasureRayInfo {
		_vector vPos;
	}TREASURERAYINFO;

private:
	explicit CLavaFlow_Part(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CLavaFlow_Part(const CLavaFlow_Part& rhs);
	virtual ~CLavaFlow_Part() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:	
	CTexture*			m_pTextureCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;	
	CModel*				m_pModelCom = nullptr;

private:
	_int				m_Number = -1;
	double				m_Time = 0.0;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();
	

public:
	static CLavaFlow_Part* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END