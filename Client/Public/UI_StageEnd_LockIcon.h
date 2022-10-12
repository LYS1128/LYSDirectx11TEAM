#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CUI_StageEnd_LockIcon final : public CUI
{
public:
	typedef struct tagLockIconInfo
	{
		_bool*	bRender;
		_float*  fX;
		_float*  fY;
		_uint	Index;
	}LOCKICONINFO;
private:
	explicit CUI_StageEnd_LockIcon(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CUI_StageEnd_LockIcon(const CUI_StageEnd_LockIcon& rhs);
	virtual ~CUI_StageEnd_LockIcon() = default;

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

	LOCKICONINFO m_tLockInfo;

	_bool m_bCheck = false;
	_bool m_bCheck2 = false;
	_uint m_iTick = 0;

	_bool m_bOnce = true;
public:
	static CUI_StageEnd_LockIcon* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END