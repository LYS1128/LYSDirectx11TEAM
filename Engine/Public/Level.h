#pragma once

#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CLevel abstract : public CBase
{
protected:
	explicit CLevel(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	virtual ~CLevel() = default;

public:
	virtual HRESULT NativeConstruct();
	virtual void Tick(_double TimeDelta);
	virtual HRESULT Render();
	HRESULT Load_MapObject(_int LevelIndex, const _tchar* pPrototypeTag);

protected:
	ID3D11Device*			m_pDevice = nullptr;
	ID3D11DeviceContext*	m_pDeviceContext = nullptr;
	

public:
	virtual void Free() override;
};

END