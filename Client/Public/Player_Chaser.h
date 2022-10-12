#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
END

BEGIN(Client)

class CPlayer_Chaser final : public CGameObject
{
private:
	explicit CPlayer_Chaser(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CPlayer_Chaser(const CPlayer_Chaser& rhs);
	virtual ~CPlayer_Chaser() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	CTransform* m_pTargetTrans = nullptr;

public:
	static CPlayer_Chaser* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END