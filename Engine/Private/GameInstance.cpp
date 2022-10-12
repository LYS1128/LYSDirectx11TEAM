
#include "../Public/GameInstance.h"


IMPLEMENT_SINGLETON(CGameInstance)

CGameInstance::CGameInstance()
	: m_pGraphic_Device(CGraphic_Device::GetInstance())
	, m_pInput_Device(CInput_Device::GetInstance())
	, m_pLevel_Manager(CLevel_Manager::GetInstance())
	, m_pObject_Manager(CObject_Manager::GetInstance())
	, m_pComponent_Manager(CComponent_Manager::GetInstance())
	, m_pTimer_Manager(CTimer_Manager::GetInstance())
	, m_pPipeLine(CPipeLine::GetInstance())
	, m_pLight_Manager(CLight_Manager::GetInstance())
	, m_pFont_Manager(CFont_Manager::GetInstance())
	, m_pFrustum(CFrustum::GetInstance())
	, m_pNavigation(CNavigation::GetInstance())	
	, m_pTarget_Manager(CTarget_Manager::GetInstance())
	, m_pPicking(CPicking::GetInstance())
{
	Safe_AddRef(m_pPicking);
	Safe_AddRef(m_pTarget_Manager);
	Safe_AddRef(m_pNavigation);
	Safe_AddRef(m_pFrustum);
	Safe_AddRef(m_pFont_Manager);
	Safe_AddRef(m_pLight_Manager);
	Safe_AddRef(m_pPipeLine);
	Safe_AddRef(m_pTimer_Manager);
	Safe_AddRef(m_pComponent_Manager);
	Safe_AddRef(m_pObject_Manager);
	Safe_AddRef(m_pLevel_Manager);
	Safe_AddRef(m_pInput_Device);
	Safe_AddRef(m_pGraphic_Device);

}

HRESULT CGameInstance::Initialize_Engine(HINSTANCE hInst, _uint iNumLevels, CGraphic_Device::GRAPHICDESC GraphicDesc, ID3D11Device** ppDeviceOut, ID3D11DeviceContext** ppDeviceContextOut)
{
	if (nullptr == m_pGraphic_Device ||
		nullptr == m_pInput_Device ||
		nullptr == m_pObject_Manager ||
		nullptr == m_pComponent_Manager)
		return E_FAIL;

	if (FAILED(m_pGraphic_Device->Ready_Graphic_Device(GraphicDesc.hWnd, GraphicDesc.eWinMode, GraphicDesc.iWinCX, GraphicDesc.iWinCY, ppDeviceOut, ppDeviceContextOut)))
		return E_FAIL;

	if (FAILED(m_pInput_Device->InitDevice(hInst, GraphicDesc.hWnd)))
		return E_FAIL;

	if (FAILED(m_pLight_Manager->NativeConstruct(*ppDeviceOut, *ppDeviceContextOut)))
		return E_FAIL;

	if (FAILED(m_pFrustum->NativeConstruct()))
		return E_FAIL;

	if (FAILED(m_pObject_Manager->Reserve_Manager(iNumLevels)))
		return E_FAIL;

	if (FAILED(m_pComponent_Manager->Reserve_Manager(iNumLevels)))
		return E_FAIL;

	if (FAILED(m_pPicking->NativeConstruct(GraphicDesc.hWnd , *ppDeviceOut, *ppDeviceContextOut)))
		return E_FAIL;

	return S_OK;
}



void CGameInstance::Tick_Engine(_double TimeDelta)
{
	if (nullptr == m_pLevel_Manager ||
		nullptr == m_pInput_Device)
		return;

	// 키 입력 관련 처리
	m_pInput_Device->SetUp_InputDeviceState();

	// ObjectMgr Tick and LateTick
	m_pObject_Manager->Tick(TimeDelta);

	m_pPipeLine->Tick();
	m_pFrustum->Transform_ToWorldSpace();

	m_pObject_Manager->LateTick(TimeDelta);

	// LevelMgr Tick
	m_pLevel_Manager->Tick(TimeDelta);
}

HRESULT CGameInstance::Render_Engine()
{
	if (nullptr == m_pLevel_Manager)
		return E_FAIL;

	m_pLevel_Manager->Render();

#ifdef _DEBUG
	//m_pNavigation->Render();
#endif // _DEBUG

	

	return S_OK;
}

HRESULT CGameInstance::Render_Begin(_float4 vClearColor)
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pGraphic_Device->Clear_BackBuffer_View(vClearColor);
	m_pGraphic_Device->Clear_DepthStencil_View();

	return S_OK;
}

HRESULT CGameInstance::Render_End()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	return m_pGraphic_Device->Present();	
}

HRESULT CGameInstance::Clear_LevelResource(_uint iLevelIndex)
{
	if (nullptr == m_pObject_Manager)
		return E_FAIL;

	if (FAILED(m_pObject_Manager->Clear(iLevelIndex)))
		return E_FAIL;

	return S_OK;
}


CGameObject * CGameInstance::Add_GameObjToLayer(_uint iLevelIndex, const _tchar * pLayerTag, const _tchar * pPrototypeTag, void * pArg)
{
	if (nullptr == m_pObject_Manager)
		return nullptr;

	return m_pObject_Manager->Add_GameObjToLayer(iLevelIndex, pLayerTag, pPrototypeTag, pArg);
}

_long CGameInstance::Get_DIMMoveState(MOUSEMOVESTATE eDIMMState)
{
	if (nullptr == m_pInput_Device)
		return 0;

	return m_pInput_Device->Get_DIMMoveState(eDIMMState);
}

_bool CGameInstance::Key_Pressing(_uchar byKeyID)
{
	if (nullptr == m_pInput_Device)
		return 0;

	return m_pInput_Device->Key_Pressing(byKeyID);
}

_bool CGameInstance::Key_Down(_uchar byKeyID)
{
	if (nullptr == m_pInput_Device)
		return 0;

	return m_pInput_Device->Key_Down(byKeyID);
}

_bool CGameInstance::Key_Up(_uchar byKeyID)
{
	if (nullptr == m_pInput_Device)
		return 0;

	return m_pInput_Device->Key_Up(byKeyID);
}

_bool CGameInstance::Button_Pressing(MOUSEBUTTONSTATE eDIMBState)
{
	if (nullptr == m_pInput_Device)
		return 0;

	return m_pInput_Device->Button_Pressing(eDIMBState);
}

_bool CGameInstance::Button_Down(MOUSEBUTTONSTATE eDIMBState)
{
	if (nullptr == m_pInput_Device)
		return 0;

	return m_pInput_Device->Button_Down(eDIMBState);
}

_bool CGameInstance::Button_Up(MOUSEBUTTONSTATE eDIMBState)
{
	if (nullptr == m_pInput_Device)
		return 0;

	return m_pInput_Device->Button_Up(eDIMBState);
}

HRESULT CGameInstance::Add_Timers(const _tchar * pTimerTag)
{
	if (nullptr == m_pTimer_Manager)
		return E_FAIL;

	return m_pTimer_Manager->Add_Timers(pTimerTag);
}

_double CGameInstance::Compute_TimeDelta(const _tchar * pTimerTag)
{
	if (nullptr == m_pTimer_Manager)
		return 0.0f;

	return m_pTimer_Manager->Compute_TimeDelta(pTimerTag);
}

HRESULT CGameInstance::Open_Level(_uint iLevelIndex, CLevel * pLevel)
{
	if (nullptr == m_pLevel_Manager)
		return E_FAIL;

	return m_pLevel_Manager->OpenLevel(iLevelIndex, pLevel);
}
CGameObject * CGameInstance::Get_GameObject(_uint iLevelIndex, const _tchar * pLayerTag, _uint iIndex)
{
	if (nullptr == m_pObject_Manager)
		return nullptr;

	return m_pObject_Manager->Get_GameObject(iLevelIndex, pLayerTag, iIndex);
}


CComponent * CGameInstance::Get_Component(_uint iLevelIndex, const _tchar * pLayerTag, const _tchar * pComponentTag, _uint iIndex)
{
	if (nullptr == m_pObject_Manager)
		return nullptr;

	return m_pObject_Manager->Get_Component(iLevelIndex, pLayerTag, pComponentTag, iIndex);	
}

HRESULT CGameInstance::Add_Prototype(const _tchar * pPrototypeTag, CGameObject * pPrototype)
{
	if (nullptr == m_pObject_Manager)
		return E_FAIL;

	return m_pObject_Manager->Add_Prototype(pPrototypeTag, pPrototype);
}

HRESULT CGameInstance::Add_GameObjectToLayer(_uint iLevelIndex, const _tchar * pLayerTag, const _tchar * pPrototypeTag, void * pArg)
{
	if (nullptr == m_pObject_Manager)
		return E_FAIL;

	return m_pObject_Manager->Add_GameObjectToLayer(iLevelIndex, pLayerTag, pPrototypeTag, pArg);
}

CLayer* CGameInstance::Find_Layer(_uint iLevelIndex, const _tchar * pLayerTag)
{
	if (nullptr == m_pObject_Manager) {
		MSG_BOX(L"Failed To CGameInstance : Find_Layer_List");
		return nullptr;
	}
	return m_pObject_Manager->Find_Layer(iLevelIndex, pLayerTag);
}

list<CGameObject*>* CGameInstance::Find_Layer_List(_uint iLevelIndex, const _tchar * pLayerTag)
{
	if (nullptr == m_pObject_Manager) {
		MSG_BOX(L"Failed To CGameInstance : Find_Layer_List");
		return nullptr;
	}
	return m_pObject_Manager->Find_Layer_List(iLevelIndex, pLayerTag);
}

_uint CGameInstance::Get_Randomint(_uint _iStart, _uint _iEnd)
{
	if (nullptr == m_pObject_Manager) {
		MSG_BOX(L"Failed To CGameInstance : Get_Randomint");
		return NULL;
	}
	return m_pObject_Manager->Get_Randomint(_iStart, _iEnd);
}

_float CGameInstance::Get_Randomfloat(_float Start, _float End)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<_float> dist(Start, End);
	return dist(gen);
}

HRESULT CGameInstance::Add_Prototype(_uint iLevelIndex, const _tchar * pPrototypeTag, CComponent * pPrototype)
{
	if (nullptr == m_pComponent_Manager)
		return E_FAIL;

	return m_pComponent_Manager->Add_Prototype(iLevelIndex, pPrototypeTag, pPrototype);
}

CComponent * CGameInstance::Clone_Component(_uint iLevelIndex, const _tchar * pPrototypeTag, void * pArg)
{
	if (nullptr == m_pComponent_Manager)
		return nullptr;

	return m_pComponent_Manager->Clone_Component(iLevelIndex, pPrototypeTag, pArg);
}

_matrix CGameInstance::Get_TransformMatrix(CPipeLine::TRANSFORMSTATE eState)
{
	if (nullptr == m_pPipeLine)
		return XMMatrixIdentity();

	return m_pPipeLine->Get_TransformMatrix(eState);	
}

_float4x4 CGameInstance::Get_TransformFloat4x4_TP(CPipeLine::TRANSFORMSTATE eState)
{
	if (nullptr == m_pPipeLine)
		return _float4x4();

	return m_pPipeLine->Get_TransformFloat4x4_TP(eState);
}

_vector CGameInstance::Get_CamPosition()
{
	if (nullptr == m_pPipeLine)
		return XMVectorSet(0.0f, 0.f, 0.f, 1.f);

	return m_pPipeLine->Get_CamPosition();
}

_float4 CGameInstance::Get_CamPositionFloat4()
{
	if (nullptr == m_pPipeLine)
		return _float4(0.0f, 0.f, 0.f, 1.f);

	return m_pPipeLine->Get_CamPositionFloat4();
}

const LIGHTDESC * CGameInstance::Get_LightDesc(_uint iIndex)
{
	if (nullptr == m_pLight_Manager)
		return nullptr;

	return m_pLight_Manager->Get_LightDesc(iIndex);	
}

HRESULT CGameInstance::Add_Lights(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, const LIGHTDESC & LightDesc)
{
	if (nullptr == m_pLight_Manager)
		return E_FAIL;

	return m_pLight_Manager->Add_Lights(pDevice, pDeviceContext, LightDesc);
}

CLight * CGameInstance::Add_Lights_Point(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, const LIGHTDESC & LightDesc)
{
	if (nullptr == m_pLight_Manager)
		return nullptr;

	return m_pLight_Manager->Add_Lights_Point(pDevice, pDeviceContext, LightDesc);
}

HRESULT CGameInstance::Clear_Light()
{
	if (nullptr == m_pLight_Manager)
		return E_FAIL;

	return m_pLight_Manager->Clear_Light();
}

HRESULT CGameInstance::Add_Fonts(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, const _tchar * pFontTag, const _tchar * pFontFilePath)
{
	if (nullptr == m_pFont_Manager)
		return E_FAIL;

	return m_pFont_Manager->Add_Fonts(pDevice, pDeviceContext, pFontTag, pFontFilePath);
}

HRESULT CGameInstance::Render_Fonts(const _tchar * pFontTag, const _tchar * pText, _float2 vPosition, _fvector vColor)
{
	if (nullptr == m_pFont_Manager)
		return E_FAIL;

	return m_pFont_Manager->Render_Fonts(pFontTag, pText, vPosition, vColor);
}

_bool CGameInstance::isInFrustum_WorldSpace(_vector vWorldPos, _float fRange)
{
	if (nullptr == m_pFrustum)
		return false;

	return m_pFrustum->isIn_WorldSpace(vWorldPos, fRange);
}

HRESULT CGameInstance::Initialize_Navigation(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, const _tchar * pNavigationData, CTransform* pTransform)
{
	if (nullptr == m_pNavigation)
		return E_FAIL;

	return m_pNavigation->Initialize(pDevice, pDeviceContext, pNavigationData, pTransform);
}

HRESULT CGameInstance::Add_ObjectCellIndex(_uint iIndex)
{
	if (nullptr == m_pNavigation)
		return E_FAIL;

	return m_pNavigation->Add_ObjectCellIndex(iIndex);
}

vector<class CCell*>* CGameInstance::Get_vecCell()
{
	if (nullptr == m_pNavigation)
		return nullptr;
	return m_pNavigation->Get_vecCell();
}

CCell * CGameInstance::Get_Cell(_uint iIndex)
{
	if (nullptr == m_pNavigation)
		return nullptr;
	return m_pNavigation->Get_Cell(iIndex);
}

_vector CGameInstance::Get_RandomCellCenter()
{
	if (nullptr == m_pNavigation)
		return XMVectorSet(0.f, 0.f, 0.f, 1.f);

	return m_pNavigation->Get_RandomCellCenter();
}

ID3D11ShaderResourceView * CGameInstance::Get_RenderTargetSRV(const _tchar * pTargetTag) const
{
	if (nullptr == m_pTarget_Manager)
		return nullptr;

	return m_pTarget_Manager->Get_SRV(pTargetTag);	
}

HRESULT CGameInstance::Picking_Initialize(HWND hWnd, ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext)
{
	if (nullptr == m_pPicking)
		return E_FAIL;

	return m_pPicking->NativeConstruct(hWnd, pDevice, pDeviceContext);
}

void CGameInstance::Picking_Update()
{
	if (nullptr == m_pPicking)
		return;

	m_pPicking->Update_ToTransform();
}

const _float3 & CGameInstance::Get_WorldRayPos()
{
	if (nullptr == m_pPicking)
		return _float3(0.f,0.f,0.f);

	return m_pPicking->Get_WorldRayPos();
}

const _float3 & CGameInstance::Get_WorldRay()
{
	if (nullptr == m_pPicking)
		return  _float3(0.f, 0.f, 0.f);

	return m_pPicking->Get_WorldRay();
}


void CGameInstance::Release_Engine()
{
	CGameInstance::GetInstance()->DestroyInstance();

	CLevel_Manager::GetInstance()->DestroyInstance();
	
	CObject_Manager::GetInstance()->DestroyInstance();

	CComponent_Manager::GetInstance()->DestroyInstance();

	CTarget_Manager::GetInstance()->DestroyInstance();

	CTimer_Manager::GetInstance()->DestroyInstance();

	CInput_Device::GetInstance()->DestroyInstance();

	CPipeLine::GetInstance()->DestroyInstance();

	CLight_Manager::GetInstance()->DestroyInstance();

	CFont_Manager::GetInstance()->DestroyInstance();

	CFrustum::GetInstance()->DestroyInstance();

	CNavigation::GetInstance()->DestroyInstance();

	CPicking::GetInstance()->DestroyInstance();

	CGraphic_Device::GetInstance()->DestroyInstance();
}

void CGameInstance::Free()
{
	Safe_Release(m_pPicking);
	Safe_Release(m_pTarget_Manager);
	Safe_Release(m_pNavigation);
	Safe_Release(m_pFrustum);
	Safe_Release(m_pFont_Manager);
	Safe_Release(m_pLight_Manager);
	Safe_Release(m_pPipeLine);
	Safe_Release(m_pTimer_Manager);
	Safe_Release(m_pComponent_Manager);
	Safe_Release(m_pObject_Manager);
	Safe_Release(m_pLevel_Manager);
	Safe_Release(m_pInput_Device);
	Safe_Release(m_pGraphic_Device);
}
