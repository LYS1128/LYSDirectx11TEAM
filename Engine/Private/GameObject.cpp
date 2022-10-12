#include "..\Public\GameObject.h"

#include "GameInstance.h"

const _tchar*	CGameObject::m_pTransformTag = TEXT("Com_Transform");

CGameObject::CGameObject(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext)
	: m_pDevice(pDevice), m_pDeviceContext(pDeviceContext)
{
	Safe_AddRef(m_pDeviceContext);
	Safe_AddRef(m_pDevice);
}

CGameObject::CGameObject(const CGameObject & rhs)
	: m_pDevice(rhs.m_pDevice), m_pDeviceContext(rhs.m_pDeviceContext),
	m_pObjectTexture2Com(rhs.m_pObjectTexture2Com),
	m_pObjectTextureCom(rhs.m_pObjectTextureCom)
{
	Safe_AddRef(m_pObjectTextureCom);
	Safe_AddRef(m_pObjectTexture2Com);

	Safe_AddRef(m_pDeviceContext);
	Safe_AddRef(m_pDevice);
}

HRESULT CGameObject::NativeConstruct_Prototype()
{
	m_pObjectTextureCom = CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Object_Texture0.dds"));
	if (nullptr == m_pObjectTextureCom)
		return E_FAIL;

	m_pObjectTexture2Com = CTexture::Create(m_pDevice, m_pDeviceContext, TEXT("../../../Resources/Textures/Effect/Object_Texture1.dds"));
	if (nullptr == m_pObjectTexture2Com)
		return E_FAIL;

	return S_OK;
}
HRESULT CGameObject::NativeConstruct(void * pArg, CTransform::TRANSFORMDESC* pTransformDesc)
{
	if (nullptr != Find_Component(m_pTransformTag))
		return E_FAIL;

	if (pTransformDesc == nullptr) {
		CTransform::TRANSFORMDESC		TransformDesc;
		TransformDesc.SpeedPerSec = 5.0f;
		TransformDesc.RotationPerSec = XMConvertToRadians(90.0f);
		m_pTransformCom = CTransform::Create(m_pDevice, m_pDeviceContext, &TransformDesc);
	}
	else
		m_pTransformCom = CTransform::Create(m_pDevice, m_pDeviceContext, pTransformDesc);

	m_Components.insert(COMPONENTS::value_type(m_pTransformTag, m_pTransformCom));

	Safe_AddRef(m_pTransformCom);
	return S_OK;
}

void CGameObject::Tick(_double TimeDelta)
{
}

void CGameObject::LateTick(_double TimeDelta)
{
}

HRESULT CGameObject::Render()
{
	return S_OK;
}

void CGameObject::Compute_CamDistance()
{
	_vector CameraPos = CPipeLine::GetInstance()->Get_CamPosition();
	_vector MyPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

	m_fCamDistance = XMVectorGetX(XMVector3Length(CameraPos - MyPos));
}

_float CGameObject::Get_Randomfloat(_float _iStart, _float _iEnd)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<_float> dist(_iStart, _iEnd);
	return dist(gen);
}

_uint CGameObject::Get_Randomint(_uint _iStart, _uint _iEnd)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<_uint> dist(_iStart, _iEnd);
	return dist(gen);
}

HRESULT CGameObject::SetUp_Components(const _tchar* pComponentTag, _uint iLevelIndex, const _tchar* pPrototypeTag, CComponent** ppOut, void* pArg)
{
	if (nullptr != Find_Component(pComponentTag))
		return E_FAIL;

	CGameInstance*		pGameInstance = CGameInstance::GetInstance();

	Safe_AddRef(pGameInstance);

	CComponent*	pComponent = pGameInstance->Clone_Component(iLevelIndex, pPrototypeTag, pArg);
	if (nullptr == pComponent)
		return E_FAIL;

	m_Components.insert(COMPONENTS::value_type(pComponentTag, pComponent));

	*ppOut = pComponent;

	Safe_AddRef(pComponent);

	Safe_Release(pGameInstance);

	return S_OK;
}

CComponent * CGameObject::Find_Component(const _tchar * pComponentTag)
{
	auto	iter = find_if(m_Components.begin(), m_Components.end(), CTagFinder(pComponentTag));

	if (iter == m_Components.end())
		return nullptr;

	return iter->second;
}

void CGameObject::Free()
{
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pObjectTextureCom);
	Safe_Release(m_pObjectTexture2Com);

	for (auto& Pair : m_Components)
		Safe_Release(Pair.second);
	m_Components.clear();

	Safe_Release(m_pDeviceContext);
	Safe_Release(m_pDevice);
}
