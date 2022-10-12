#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CEnding_Text final : public CUI
{
public:
	typedef struct tagEndingTextInfo
	{
		_float fX;
		_float fY;
		_uint  Index;
	}ENDINFO;
private:
	explicit CEnding_Text(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	explicit CEnding_Text(const CEnding_Text& rhs);
	virtual ~CEnding_Text() = default;

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
	ENDINFO m_tEndInfo;

	_double m_EndTime = 0.0;
public:
	static CEnding_Text* Create(ID3D11Device* pDeviceOut, ID3D11DeviceContext* pDeviceContextOut);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END