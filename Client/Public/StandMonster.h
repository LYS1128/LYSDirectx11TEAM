#pragma once

#include "Client_Defines.h"
#include "LandObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CCollider;
class CModel;
END

BEGIN(Client)

class CStandMonster  : public CLandObject
{
protected:
	explicit CStandMonster(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CStandMonster(const CStandMonster& rhs);
	HRESULT NativeConstruct(void * pArg);
	virtual ~CStandMonster() = default;



protected:
	CCollider*			m_pAABBCom = nullptr;
	CCollider*			m_pOBBCom = nullptr;
	CRenderer*			m_pRendererCom = nullptr;
	CShader*			m_pShaderCom = nullptr;	
	CModel*				m_pModelCom = nullptr;
protected: /* For. Pattern */
	//_bool	bFirstSpawn = true;
	void Behavior(_double TimeDelta, _uint AnimIndex1, _uint AnimIndex2);
protected:	/* For .Animation */
	_uint				m_iAnimationIndex;

public:
	static CStandMonster* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END