#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CUI_StageEnd_StagePicture final : public CUI
{
private:
	explicit CUI_StageEnd_StagePicture(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_StageEnd_StagePicture(const CUI_StageEnd_StagePicture& rhs);
	virtual ~CUI_StageEnd_StagePicture() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	CTexture*	m_pMaskTexture = nullptr;
public:
	HRESULT SetUp_Components();

private:
	_bool m_bButton = false;

	_float m_iTickCnt = 0.f;

public:
	static CUI_StageEnd_StagePicture* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END