#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CCollider;
class CModel;
END

BEGIN(Client)

class CReal_Bar final : public CGameObject
{
private:
	explicit CReal_Bar(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CReal_Bar(const CReal_Bar& rhs);
	virtual ~CReal_Bar() = default;

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
	CCollider*			m_pAABBCom = nullptr;//나무
	CCollider*			m_pAABBCom1 = nullptr;//택배박스
	CCollider*			m_pAABBCom2 = nullptr;//떠나기

	CCollider*			m_pSphereCom = nullptr;
	_uint							m_iKeyCount = 0;


private:
	ID3D11ShaderResourceView*		m_pMaskSRV = nullptr;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();
private: // 충돌에관한 함수
	void		WoodCollision();

	void		Layer_Waterdrop_Num_UI(_tchar * pLayerTag);

	void		Real_Bar_UI(_tchar * pLayerTag);
	void		Real_Bar_Making_UI(_tchar * pLayerTag);

	void		Marking_UI_RenderTrue(_bool		isRender);

	void		Infomation_Box();
	void		leave_UI();

	void		Eve_Talk_UI();
public:
	static CReal_Bar* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END