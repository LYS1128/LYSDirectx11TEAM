#include "..\Public\VIBuffer_Rect_Instance.h"
#include "GameInstance.h"
CVIBuffer_Rect_Instance::CVIBuffer_Rect_Instance(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext)
	: CVIBuffer(pDevice, pDeviceContext)
{
}

//CVIBuffer_Rect_Instance::CVIBuffer_Rect_Instance(const CVIBuffer_Rect_Instance & rhs)
//	: CVIBuffer(rhs)
//	, m_pVBInstance(rhs.m_pVBInstance)
//	, m_iInstanceStride(rhs.m_iInstanceStride)
//	, m_iNumInstance(rhs.m_iNumInstance)
//	, m_SaveParticle(rhs.m_SaveParticle)
//	, m_VBInstSubResourceData(rhs.m_VBInstSubResourceData)
//	, m_VBInstDesc(rhs.m_VBInstDesc)
//{
//	Safe_AddRef(m_pVBInstance);
//}

CVIBuffer_Rect_Instance::CVIBuffer_Rect_Instance(const CVIBuffer_Rect_Instance & rhs)
	: CVIBuffer(rhs)
	, m_iInstanceStride(rhs.m_iInstanceStride)
	, m_iNumInstance(rhs.m_iNumInstance)
	, m_SaveParticle(rhs.m_SaveParticle)
	, m_VBInstSubResourceData(rhs.m_VBInstSubResourceData)
	, m_VBInstDesc(rhs.m_VBInstDesc)
	, m_TotalScale(rhs.m_TotalScale)
	, m_pInstanceVertices(rhs.m_pInstanceVertices)
{

	m_pDevice->CreateBuffer(&m_VBInstDesc, &m_VBInstSubResourceData, &m_pVBInstance);
}


HRESULT CVIBuffer_Rect_Instance::NativeConstruct_Prototype(_uint iNumInstance)
{
#pragma region VERTEX_BUFFER
	m_iStride = sizeof(VTXTEX);
	m_iNumVertices = 4;
	m_iNumVBuffers = 2;

	ZeroMemory(&m_VBDesc, sizeof(D3D11_BUFFER_DESC));
	m_VBDesc.ByteWidth = m_iStride * m_iNumVertices;
	m_VBDesc.StructureByteStride = m_iStride;
	m_VBDesc.Usage = D3D11_USAGE_IMMUTABLE;
	m_VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_VBDesc.CPUAccessFlags = 0;
	m_VBDesc.MiscFlags = 0;

	VTXTEX*		pVertices = new VTXTEX[m_iNumVertices];

	pVertices[0].vPosition = _float3(-0.5f, 0.5f, 0.f);
	pVertices[0].vTexUV = _float2(0.0f, 0.0f);

	pVertices[1].vPosition = _float3(0.5f, 0.5f, 0.f);
	pVertices[1].vTexUV = _float2(1.0f, 0.0f);

	pVertices[2].vPosition = _float3(0.5f, -0.5f, 0.f);
	pVertices[2].vTexUV = _float2(1.0f, 1.0f);

	pVertices[3].vPosition = _float3(-0.5f, -0.5f, 0.f);
	pVertices[3].vTexUV = _float2(0.0f, 1.0f);

	ZeroMemory(&m_VBSubResourceData, sizeof(D3D11_SUBRESOURCE_DATA));
	m_VBSubResourceData.pSysMem = pVertices;

	if (FAILED(__super::Create_VertexBuffer()))
		return E_FAIL;

	Safe_Delete_Array(pVertices);
#pragma endregion


#pragma region INSTANCE_BUFFER

	m_iInstanceStride = sizeof(VTXMATRIX);
	m_iNumInstance = iNumInstance;

	ZeroMemory(&m_VBInstDesc, sizeof(D3D11_BUFFER_DESC));
	m_VBInstDesc.ByteWidth = m_iInstanceStride * m_iNumInstance;
	m_VBInstDesc.StructureByteStride = m_iInstanceStride;
	m_VBInstDesc.Usage = D3D11_USAGE_DYNAMIC;
	m_VBInstDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_VBInstDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	m_VBInstDesc.MiscFlags = 0;

	VTXMATRIX*		pInstanceVertices = new VTXMATRIX[m_iNumInstance];

	for (_uint i = 0; i < m_iNumInstance; ++i)
	{
		pInstanceVertices[i].vRight = _float4(1.f, 0.f, 0.f, 0.f);
		pInstanceVertices[i].vUp = _float4(0.f, 1.f, 0.f, 0.f);
		pInstanceVertices[i].vLook = _float4(0.f, 0.f, 1.f, 0.f);
		pInstanceVertices[i].vTranslation = _float4((_float)(rand() % 3), 10.0f, (_float)(rand() % 3), 1.f);
	}

	ZeroMemory(&m_VBInstSubResourceData, sizeof(D3D11_SUBRESOURCE_DATA));
	m_VBInstSubResourceData.pSysMem = pInstanceVertices;

	if (FAILED(m_pDevice->CreateBuffer(&m_VBInstDesc, &m_VBInstSubResourceData, &m_pVBInstance)))
		return E_FAIL;

	Safe_Delete_Array(pInstanceVertices);

#pragma endregion

#pragma region INDEX_BUFFER

	m_iPrimitiveIndicesSize = sizeof(FACELISTINDICES16);
	m_iNumPrimitive = 2 * m_iNumInstance;
	m_iNumIndicesPerPrimitive = 3;
	m_eFormat = DXGI_FORMAT_R16_UINT;
	m_eTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;


	ZeroMemory(&m_IBDesc, sizeof(D3D11_BUFFER_DESC));
	m_IBDesc.ByteWidth = m_iPrimitiveIndicesSize * m_iNumPrimitive;
	m_IBDesc.StructureByteStride = 0;
	m_IBDesc.Usage = D3D11_USAGE_IMMUTABLE;
	m_IBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	m_IBDesc.CPUAccessFlags = 0;
	m_IBDesc.MiscFlags = 0;

	FACELISTINDICES16*		pIndices = new FACELISTINDICES16[m_iNumPrimitive];
	ZeroMemory(pIndices, sizeof(FACELISTINDICES16) * m_iNumPrimitive);

	_uint		iNumFaces = 0;

	for (_uint i = 0; i < m_iNumInstance; ++i)
	{
		pIndices[iNumFaces]._0 = 0;
		pIndices[iNumFaces]._1 = 1;
		pIndices[iNumFaces]._2 = 2;
		++iNumFaces;

		pIndices[iNumFaces]._0 = 0;
		pIndices[iNumFaces]._1 = 2;
		pIndices[iNumFaces]._2 = 3;
		++iNumFaces;
	}

	ZeroMemory(&m_IBSubResourceData, sizeof(D3D11_SUBRESOURCE_DATA));
	m_IBSubResourceData.pSysMem = pIndices;

	if (FAILED(Create_IndexBuffer()))
		return E_FAIL;
#pragma endregion

	Safe_Delete_Array(pIndices);

	return S_OK;
}

HRESULT CVIBuffer_Rect_Instance::NativeConstruct_Prototype(_tchar * FilePath)
{
	_ulong		dwByte = 0;
	//CREATE_ALWAYS
	m_isProtoType = true;
	HANDLE		hFile = CreateFile(FilePath, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (0 == hFile || hFile == INVALID_HANDLE_VALUE) {
		MSGBOX("FAILDE CLIENT FILE !!!");
		return E_FAIL;
	}

	ReadFile(hFile, &m_SaveParticle, sizeof(m_SaveParticle), &dwByte, nullptr);
	m_iNumInstance = m_SaveParticle.VectorSize;


	//VTXMATRIX*		pInstanceVertices = new VTXMATRIX[m_iNumInstance];
	m_pInstanceVertices = new VTXMATRIX[m_iNumInstance];

	vector<VTXMATRIX> BuffData;
	BuffData.resize(m_iNumInstance);

	ReadFile(hFile, BuffData.data(), sizeof(VTXMATRIX)*m_iNumInstance, &dwByte, nullptr);

	ReadFile(hFile, &m_TotalScale, sizeof(_float3), &dwByte, nullptr);
	if (dwByte == 0) {
		m_TotalScale = _float3(1.f, 1.f, 1.f);
	}

	for (_uint i = 0; i < m_iNumInstance; i++)
		m_pInstanceVertices[i] = BuffData[i];


#pragma region VERTEX_BUFFER
	m_iStride = sizeof(VTXTEX);
	m_iNumVertices = 4;
	m_iNumVBuffers = 2;

	ZeroMemory(&m_VBDesc, sizeof(D3D11_BUFFER_DESC));
	m_VBDesc.ByteWidth = m_iStride * m_iNumVertices;
	m_VBDesc.StructureByteStride = m_iStride;
	m_VBDesc.Usage = D3D11_USAGE_IMMUTABLE;
	m_VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_VBDesc.CPUAccessFlags = 0;
	m_VBDesc.MiscFlags = 0;

	VTXTEX*		pVertices = new VTXTEX[m_iNumVertices];

	pVertices[0].vPosition = _float3(-0.5f, 0.5f, 0.f);
	pVertices[0].vTexUV = _float2(0.0f, 0.0f);

	pVertices[1].vPosition = _float3(0.5f, 0.5f, 0.f);
	pVertices[1].vTexUV = _float2(1.0f, 0.0f);

	pVertices[2].vPosition = _float3(0.5f, -0.5f, 0.f);
	pVertices[2].vTexUV = _float2(1.0f, 1.0f);

	pVertices[3].vPosition = _float3(-0.5f, -0.5f, 0.f);
	pVertices[3].vTexUV = _float2(0.0f, 1.0f);

	ZeroMemory(&m_VBSubResourceData, sizeof(D3D11_SUBRESOURCE_DATA));
	m_VBSubResourceData.pSysMem = pVertices;

	if (FAILED(__super::Create_VertexBuffer()))
		return E_FAIL;

	Safe_Delete_Array(pVertices);
#pragma endregion


#pragma region INSTANCE_BUFFER

	m_iInstanceStride = sizeof(VTXMATRIX);
	m_iNumInstance = m_iNumInstance;

	ZeroMemory(&m_VBInstDesc, sizeof(D3D11_BUFFER_DESC));
	m_VBInstDesc.ByteWidth = m_iInstanceStride * m_iNumInstance;
	m_VBInstDesc.StructureByteStride = m_iInstanceStride;
	m_VBInstDesc.Usage = D3D11_USAGE_DYNAMIC;
	m_VBInstDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_VBInstDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	m_VBInstDesc.MiscFlags = 0;

	ZeroMemory(&m_VBInstSubResourceData, sizeof(D3D11_SUBRESOURCE_DATA));
	m_VBInstSubResourceData.pSysMem = m_pInstanceVertices;

	if (FAILED(m_pDevice->CreateBuffer(&m_VBInstDesc, &m_VBInstSubResourceData, &m_pVBInstance)))
		return E_FAIL;

#pragma endregion

#pragma region INDEX_BUFFER

	m_iPrimitiveIndicesSize = sizeof(FACELISTINDICES16);
	m_iNumPrimitive = 2 * m_iNumInstance;
	m_iNumIndicesPerPrimitive = 3;
	m_eFormat = DXGI_FORMAT_R16_UINT;
	m_eTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;


	ZeroMemory(&m_IBDesc, sizeof(D3D11_BUFFER_DESC));
	m_IBDesc.ByteWidth = m_iPrimitiveIndicesSize * m_iNumPrimitive;
	m_IBDesc.StructureByteStride = 0;
	m_IBDesc.Usage = D3D11_USAGE_IMMUTABLE;
	m_IBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	m_IBDesc.CPUAccessFlags = 0;
	m_IBDesc.MiscFlags = 0;

	FACELISTINDICES16*		pIndices = new FACELISTINDICES16[m_iNumPrimitive];
	ZeroMemory(pIndices, sizeof(FACELISTINDICES16) * m_iNumPrimitive);

	_uint		iNumFaces = 0;

	for (_uint i = 0; i < m_iNumInstance; ++i)
	{
		pIndices[iNumFaces]._0 = 0;
		pIndices[iNumFaces]._1 = 1;
		pIndices[iNumFaces]._2 = 2;
		++iNumFaces;

		pIndices[iNumFaces]._0 = 0;
		pIndices[iNumFaces]._1 = 2;
		pIndices[iNumFaces]._2 = 3;
		++iNumFaces;
	}

	ZeroMemory(&m_IBSubResourceData, sizeof(D3D11_SUBRESOURCE_DATA));
	m_IBSubResourceData.pSysMem = pIndices;

	if (FAILED(Create_IndexBuffer()))
		return E_FAIL;
#pragma endregion
	Safe_Delete_Array(pIndices);
	return S_OK;
}

HRESULT CVIBuffer_Rect_Instance::NativeConstruct(void * pArg)
{

	return S_OK;
}

HRESULT CVIBuffer_Rect_Instance::Update(_double TimeDelta)
{
	if (nullptr == m_pDeviceContext)
		return E_FAIL;

	D3D11_MAPPED_SUBRESOURCE			SubResource;
	_bool flag = false;
	m_pDeviceContext->Map(m_pVBInstance, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &SubResource);

	for (_uint i = 0; i < m_iNumInstance; ++i)
	{
		if (m_isCreate == false) {
			((VTXMATRIX*)SubResource.pData)[i].Time = 0.f;
			((VTXMATRIX*)SubResource.pData)[i].vTranslation = ((VTXMATRIX*)SubResource.pData)[i].vOriginTrans;
			((VTXMATRIX*)SubResource.pData)[i].vAngle = ((VTXMATRIX*)SubResource.pData)[i].vOriginAngle;
		}

		_vector vAxisRotation = XMVector3Normalize(XMLoadFloat3(&((VTXMATRIX*)SubResource.pData)[i].vAngle));
		_vector vDir = XMVector3Normalize(XMLoadFloat4(&((VTXMATRIX*)SubResource.pData)[i].vDirection));
		_vector	vPosition = XMLoadFloat4(&((VTXMATRIX*)SubResource.pData)[i].vTranslation);

		if (XMVectorGetX(XMVector3Length(vAxisRotation)) > 0) {
			vDir = XMVector3Normalize(Rotate_Direction(TimeDelta, vDir, &((VTXMATRIX*)SubResource.pData)[i].vAngle, ((VTXMATRIX*)SubResource.pData)[i].fRotationSpeed));
		}

		vPosition += vDir * ((VTXMATRIX*)SubResource.pData)[i].fSpeed * (_float)TimeDelta;
		XMStoreFloat4(&((VTXMATRIX*)SubResource.pData)[i].vTranslation, vPosition);

		((VTXMATRIX*)SubResource.pData)[i].Time += TimeDelta * (((VTXMATRIX*)SubResource.pData)[i].fSpeed);

		if (m_SaveParticle.isArriveRemove == true) {
			_vector vPos = XMLoadFloat4(&m_SaveParticle.Direction) - XMLoadFloat4(&((VTXMATRIX*)SubResource.pData)[i].vTranslation);
			XMVectorSetW(vPos, 0.f);
			if (XMVectorGetX(XMVector3Length(vPos)) < 0.5f)
				((VTXMATRIX*)SubResource.pData)[i].vTranslation.w = 0.f;
		}

		if (((VTXMATRIX*)SubResource.pData)[i].Time > m_SaveParticle.Duration && m_SaveParticle.isRepeat == false) {
			((VTXMATRIX*)SubResource.pData)[i].vTranslation.w = 0.f;
		}
		else
			flag = true;
		if (((VTXMATRIX*)SubResource.pData)[i].Time > m_SaveParticle.Duration && m_SaveParticle.isRepeat == true) {
			((VTXMATRIX*)SubResource.pData)[i].Time = 0.0;
			((VTXMATRIX*)SubResource.pData)[i].vTranslation = ((VTXMATRIX*)SubResource.pData)[i].vOriginTrans;
			((VTXMATRIX*)SubResource.pData)[i].vAngle = ((VTXMATRIX*)SubResource.pData)[i].vOriginAngle;
			_float Speed = CGameInstance::GetInstance()->Get_Randomfloat(m_SaveParticle.RandSpeed.x, m_SaveParticle.RandSpeed.y);
			((VTXMATRIX*)SubResource.pData)[i].fSpeed = m_SaveParticle.Speed + Speed;
		}
	}

	m_pDeviceContext->Unmap(m_pVBInstance, 0);
	if (m_isCreate == false)
		m_isCreate = true;

	if (m_SaveParticle.isRepeat == false && flag == false)
		return E_FAIL;

	return S_OK;
}

_vector CVIBuffer_Rect_Instance::Rotate_Direction(_double Timedelta, _vector Dir, _float3 * vRotate, _float Speed)
{
	_vector vLook = Dir;
	_vector AxisY = XMVectorSet(0.f, 1.f, 0.f, 0.f);
	if (XMVectorGetY(vLook) > 0.f && XMVectorGetX(vLook) == 0.f && XMVectorGetZ(vLook) == 0.f) {
		AxisY = XMVectorSet(0.f, 0.f, 1.f, 0.f);
	}
	_vector vRight = XMVector3Cross(AxisY, vLook);
	_vector vUp = XMVector3Cross(vLook, vRight);

	_matrix Mtx = XMMatrixIdentity();
	Mtx.r[0] = vRight;
	Mtx.r[1] = vUp;
	Mtx.r[2] = vLook;

	if (vRotate->x != 0) {
		Mtx *= XMMatrixRotationAxis(vRight, vRotate->x);
		if (vRotate->x > 0)
			vRotate->x += (_float)Timedelta * Speed;
		else
			vRotate->x += -(_float)Timedelta * Speed;
	}
	if (vRotate->y != 0) {
		Mtx *= XMMatrixRotationAxis(vUp, vRotate->y);
		if (vRotate->y > 0)
			vRotate->y += (_float)Timedelta * Speed;
		else
			vRotate->y += -(_float)Timedelta * Speed;
	}
	if (vRotate->z != 0) {
		Mtx *= XMMatrixRotationAxis(vLook, vRotate->z);
		if (vRotate->z > 0)
			vRotate->z += (_float)Timedelta * Speed;
		else
			vRotate->z += -(_float)Timedelta * Speed;
	}

	return Mtx.r[2];
}

HRESULT CVIBuffer_Rect_Instance::Render()
{
	if (nullptr == m_pDeviceContext)
		return E_FAIL;

	ID3D11Buffer*	pVertexBuffers[] = {
		m_pVB,
		m_pVBInstance
	};

	_uint			iStrides[] = {
		m_iStride,
		m_iInstanceStride

	};

	_uint			iOffset[] = {
		0, 0
	};

	m_pDeviceContext->IASetVertexBuffers(0, m_iNumVBuffers, pVertexBuffers, iStrides, iOffset);
	m_pDeviceContext->IASetIndexBuffer(m_pIB, m_eFormat, 0);
	m_pDeviceContext->IASetPrimitiveTopology(m_eTopology);

	m_pDeviceContext->DrawIndexedInstanced(6, m_iNumInstance, 0, 0, 0);

	return S_OK;
}

CVIBuffer_Rect_Instance * CVIBuffer_Rect_Instance::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, _uint iNumInstance)
{
	CVIBuffer_Rect_Instance*	pInstance = new CVIBuffer_Rect_Instance(pDevice, pDeviceContext);

	if (FAILED(pInstance->NativeConstruct_Prototype(iNumInstance)))
	{
		MSG_BOX(TEXT("Failed to Created CVIBuffer_Rect_Instance"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CVIBuffer_Rect_Instance * CVIBuffer_Rect_Instance::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pDeviceContext, _tchar * FilePath)
{
	CVIBuffer_Rect_Instance*	pInstance = new CVIBuffer_Rect_Instance(pDevice, pDeviceContext);

	if (FAILED(pInstance->NativeConstruct_Prototype(FilePath)))
	{
		MSG_BOX(TEXT("Failed to Created CVIBuffer_Rect_Instance"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CVIBuffer_Rect_Instance::Clone(void * pArg)
{
	CVIBuffer_Rect_Instance*	pInstance = new CVIBuffer_Rect_Instance(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CVIBuffer_Rect_Instance"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CVIBuffer_Rect_Instance::Free()
{
	__super::Free();
	Safe_Release(m_pVBInstance);
	if (m_isProtoType == true)
		Safe_Delete_Array(m_pInstanceVertices);
}
