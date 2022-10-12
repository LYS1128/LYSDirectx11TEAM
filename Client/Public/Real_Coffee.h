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

class CReal_Coffee final : public CGameObject
{
private:
	explicit CReal_Coffee(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CReal_Coffee(const CReal_Coffee& rhs);
	virtual ~CReal_Coffee() = default;

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

private:
	ID3D11ShaderResourceView*		m_pMaskSRV = nullptr;
	_uint							m_iKeyCount = 0;
private:




	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();
private: // 충돌에관한 함수
	void		Collsion();
	void		Real_Coffee_UI(_tchar * pLayerTag);
	//void		leave_UI();

	//void		Smoke_UI();
	void		Spark_Num(_tchar * pLayerTag);

	void		Real_Coffee_Making_UI(_tchar * pLayerTag);
	void		Marking_UI_RenderTrue(_bool		isRender);

	void		Box_list();

	void		leave_UI();


	void		Text_Delete();

	_bool		m_isleave = true;
public:
	static CReal_Coffee* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END