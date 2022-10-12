#pragma once

#include "Client_Defines.h"
#include "PushOutObject.h"

BEGIN(Engine)
class CCollider;
class CShader;
class CRenderer;
class CModel;
class CVIBuffer_Rect;
class CTexture;
END

BEGIN(Client)

class CPortal final : public CPushOutObject
{
private:
	explicit CPortal(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CPortal(const CPortal& rhs);
	virtual ~CPortal() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render_LightDepth() override;
	virtual HRESULT Render() override;

public:
	_bool Get_bPlayerTouch() { return m_bPlayerTouch; }
	_vector Get_LinkedPortalPos() { return m_vLinkedPortalPos; }
	SAVEPORTAL Get_PortalData() { return m_PortalData; }
	_bool Get_TileClear() { return m_bTileClear; }
	_uint Get_Option() { return m_iOption; }
	void Set_Option(_uint Option) { m_iOption = Option; }
	void Set_KeyOpen(_bool Open) { m_bKey = Open; }
	void Set_BombOpen(_bool Open) { m_bBombOpen = Open; }

private:
	CCollider*			m_pSphereCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;
	vector<CModel*>		m_Models;
	CModel*				m_OptionModelCom = nullptr;
	CTexture*			m_TextureCom = nullptr;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();
	void SetUp_Portal_Color();

private:
	SAVEPORTAL			m_PortalData;
	_uint				m_ModelIndex = 0;
	_bool				m_bPlayerTouch = false;
	_vector				m_vLinkedPortalPos = XMVectorSet(40.f, 0.f, 20.f, 1.f);
	_bool				m_bTileClear = true;
	_bool				m_bClose = false;
	_double				m_dTime = 0.0;

	//추가한 부분
	_uint				m_iOption = 0; //0: 기본 1: 열쇠로 잠김 2: 바위로 잠김
	_bool				m_bKeyOpen = false; //1번옵션포탈만 사용
	_bool				m_bBombOpen = false; //2번옵션포탈만 사용
	_bool				m_bInsideEffect = false;

	//
	_float3				m_Color = _float3(0.f, 0.f, 0.f);
	_float				m_ColorTime = 0.f;
	_bool				m_Colorflag = false;

	_bool				m_bActive = true;

	_bool				m_bKey = false;
	_uint				m_iKeyPath = 0;
	_float				m_bPercent = 0.f;

public:
	static CPortal* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END