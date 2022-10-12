#pragma once
#include "Client_Defines.h"
#include "UI.h"
#include "UI_StageEnd_UnLockSprite.h"

BEGIN(Client)

class CUI_StageEnd_Shururuk final : public CUI
{

private:
	explicit CUI_StageEnd_Shururuk(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_StageEnd_Shururuk(const CUI_StageEnd_Shururuk& rhs);
	virtual ~CUI_StageEnd_Shururuk() = default;

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_double TimeDelta) override;
	virtual void LateTick(_double TimeDelta) override;
	virtual HRESULT Render() override;

public:
	HRESULT SetUp_Components();

private:
	_bool m_bButton = false;

	_uint m_iTick = 0;

	CUI_StageEnd_UnLockSprite::SPRITEINFO m_tSpriteInfo;
public:
	static CUI_StageEnd_Shururuk* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END