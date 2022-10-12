#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CModel;
END

BEGIN(Client)

class CPuzzle_Water final : public CGameObject
{
public:
	typedef struct tagPuzzleWater {
		_vector vPos;
	}PUZZLEWATERINFO;

private:
	explicit CPuzzle_Water(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CPuzzle_Water(const CPuzzle_Water& rhs);
	virtual ~CPuzzle_Water() = default;

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
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();
	

private:
	_float				m_fPercent;
	_float				m_fLength;
	_bool				m_iDegree;
	_double			m_dFalling;
	_double			m_dScaling;
	//_float				m_fRed;
	//_float				m_fGreen;
	//_float				m_fBlue;


public:
	static CPuzzle_Water* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END