#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CModel;
class CCollider;
END

BEGIN(Client)

class CReal_House final : public CGameObject
{
private:
	explicit CReal_House(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CReal_House(const CReal_House& rhs);
	virtual ~CReal_House() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;
public:
	void			Set_SleepTexture(_bool		Sleep) { m_isSleepText = Sleep; }
private:	
	CTexture*			m_pTextureCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;	
	CModel*				m_pModelCom = nullptr;	
	CCollider*			m_pAABBCom = nullptr;//나무
	CCollider*			m_pAABBCom1 = nullptr;//택배박스
	CCollider*			m_pAABBCom2 = nullptr;//떠나기
	CCollider*			m_pAABBCom3 = nullptr;//침대
	
	CCollider*			m_pSphereCom = nullptr;


	_uint				 m_iFadeTime = 0;
	_bool				 m_isSleep = false;
	_bool				 m_isSleepText = true;

	_bool				m_isOpenGameplay = true;

	_float				m_fRenderTick = 0.f;

	_uint				m_iKeyCount = 0;
	_bool				m_isExclamationmarkOff = true;


	_double m_dTime = 0.0;
	_uint	m_iFalling = 0;
private:
	ID3D11ShaderResourceView*		m_pMaskSRV = nullptr;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();
private:
	void		Layer_LightNum_UI(_tchar * pLayerTag);

	void		Collision();

	void		Layer_RealWorld_UI(_tchar * pLayerTag);
	void		Layer_RealWorld_Making_UI(_tchar* pLayerTag);
	
	void		Marking_UI_RenderTrue(_bool		isRender);
	void		leave_UI();
	
	void		Scroll_UI();
	void		Falling_Start(_double TimeDelta);
	_bool		m_bLie;
	_bool		m_isleave = true;
public:
	static CReal_House* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END