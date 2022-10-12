#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CUI_StageEnd_UnLockSprite final : public CUI
{
public:
	typedef struct tagSpriteInfo
	{
		_float fX;
		_float fY;
		_uint i = 0;
	}SPRITEINFO;
private:
	explicit CUI_StageEnd_UnLockSprite(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_StageEnd_UnLockSprite(const CUI_StageEnd_UnLockSprite& rhs);
	virtual ~CUI_StageEnd_UnLockSprite() = default;

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
	SPRITEINFO m_tSpriteInfo;
public:
	static CUI_StageEnd_UnLockSprite* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END