#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CTexture;
class CRenderer;
class CVIBuffer_Rect;
class CModel;
END

BEGIN(Client)

class CSword_Fire final : public CGameObject
{
public:
	typedef struct _tagFireDesc
	{
		class CModel*		pModelCom = nullptr;
		const char*			pBoneName = nullptr;	
		_float				fYPos;
		_uint				iIndex;
		_float				Scale;
		class CTransform*	pTransform = nullptr;
		_bool				bLeft = false;
		_float				CurrentX;
		_float				CurrentY;
	}FIREDESC;
private:
	explicit CSword_Fire(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CSword_Fire(const CSword_Fire& rhs);
	virtual ~CSword_Fire() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	void	FireScript6x10();
	void	FireScript6x4();


private:
	CTexture*			m_pTextureCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	CVIBuffer_Rect*		m_pVIBufferCom = nullptr;

private:
	_float4x4				m_ProjMatrix;
	_float4x4*				m_pSocketMatrix;
	_float4x4				m_PivotMatrix;
	_matrix				m_pWorldMat;

	CTransform*			m_pResentmentTrans = nullptr;

	_float					m_fLine;
	_float					m_fRow;
	_float					m_fCurrentLine;
	_float					m_fCurrentRow;
	_float					m_fYPos;
	_uint					m_iIndex;

	_float					m_fRed;
	_float					m_fGreen;
	_float					m_fBlue;

	_double					m_dTime;
	_float					m_fCnt;
	_float					m_fMCnt;
	_float					m_fDisolveCnt;
	_bool					m_bDisolve;
	_bool					m_bLeft;

public:
	HRESULT SetUp_Components();

public:
	static CSword_Fire* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END