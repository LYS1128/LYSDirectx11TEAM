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

class CMeshEffect final : public CGameObject
{
public:
	typedef struct _tagMeshEffectDesc {
		_vector	vPosition{};
	}MESHEFFECTDESC;
private:
	explicit CMeshEffect(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CMeshEffect(const CMeshEffect& rhs);
	virtual ~CMeshEffect() = default;

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
private: /* For. Pattern */
	_bool	bFirstSpawn = true;
	_bool	bTest = false;
	//void Behavior(_double TimeDelta, _uint AnimIndex1, _uint AnimIndex2);
	MESHEFFECTDESC		m_MeshEffctDesc;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ConstantTable();


public:
	static CMeshEffect* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END