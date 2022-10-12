#pragma once

#include "Client_Defines.h"
#include "Base.h"

BEGIN(Client)

class CLoader4 final : public CBase
{
private:
	explicit CLoader4(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual ~CLoader4() = default;

public:
	CRITICAL_SECTION Get_CriticalSection() {
		return m_CriticalSection;
	}

	LEVEL Get_LevelIndex() {
		return m_eLevel;
	}

	_bool Get_Finished() const {
		return m_isFinished;
	}

	const _tchar* Get_LoadingText() const {
		return m_szLoading;
	}

public:
	HRESULT NativeConstruct(LEVEL eLevel);
	HRESULT Loading_ForGamePlayLevel();

	//Real
	HRESULT Loading_ForRealityLevel();
	HRESULT Loading_ForRealityBarLevel();
	HRESULT Loading_ForRealityPark();
	HRESULT Loading_ForRealityCoffee();
	//Real

	HRESULT Loading_ForBossFearLevel();
private:
	LEVEL			m_eLevel = LEVEL_END;
	_bool			m_isFinished = false;
	_tchar			m_szLoading[MAX_PATH] = TEXT("");

private:
	ID3D11Device*			m_pDevice = nullptr;
	ID3D11DeviceContext*	m_pDeviceContext = nullptr;
	HANDLE				m_hThread = 0;
	CRITICAL_SECTION	m_CriticalSection;

public:
	static CLoader4* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut, LEVEL eLevel);
	virtual void Free() override;
};

END