#pragma once

#include "Client_Defines.h"
#include "Level.h"

/* �ε����� �����ش�. */
/* . �δ��� �ε��Ҽ��ֵ���. �δ���ü���� */
/* �δ����� ������ �� ����. */
BEGIN(Client)

class CLevel_Loading final : public CLevel
{
private:
	explicit CLevel_Loading(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual ~CLevel_Loading() = default;

public:
	virtual HRESULT NativeConstruct(LEVEL eNextLevel);
	virtual void Tick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	LEVEL			m_eNextLevel = LEVEL_END;
	class CLoader*	m_pLoader = nullptr;
	class CLoader2*	m_pLoader2 = nullptr;
	class CLoader3*	m_pLoader3 = nullptr;
	class CLoader4*	m_pLoader4 = nullptr;
	class CGameObject_Loader*	m_pGObjLoader = nullptr;

	_bool m_bGamePlay = true, m_bCity = true, m_bLava = true;
	_bool m_bOnce = true;

	_bool m_bCheck = false;
public:
	static CLevel_Loading* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut, LEVEL eNextLevel);
	virtual void Free() override;
};

END