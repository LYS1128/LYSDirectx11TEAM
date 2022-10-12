#pragma once

#include "Base.h"

/* Ư�� �ִϸ��̼��� �����ϴµ� �ʿ��� ���� �ִϸ��̼� ����. */
/* �ִϸ��̼� ���� �ϳ��� ���� ���� Channel�� ������ ������� �� �մ�. */

BEGIN(Engine)

class CChannel final : public CBase
{
private:
	CChannel();
	CChannel(const CChannel& rhs);
	virtual ~CChannel() = default;

public:
	void SetUp_HierarchyNodePtr(class CHierarchyNode* pNode) {
		m_pHierarchyNode = pNode;
		Safe_AddRef(m_pHierarchyNode);
	}

	void Set_CurrentKeyFrame(_uint iKeyFrame) {
		m_iCurrentKeyFrame = iKeyFrame;
	}

public:
	CHierarchyNode* Get_HierarchyNode()
	{
		return m_pHierarchyNode;
	}

	_uint Get_CurrentKeyFrameIndex()
	{
		return m_iCurrentKeyFrame;
	}

public:
	HRESULT NativeConstruct_Prototype(aiNodeAnim* pAIChannel);
	HRESULT NativeConstruct_Prototype(CHANNELDESC* pData);
	HRESULT NativeConstruct();
	void Compute_TransformationMatrix(_double PlayTime);
	CHANNELDESC Get_Data() { return *m_pData; }

private:
	char				m_szName[MAX_PATH] = "";

private:
	CHANNELDESC* m_pData = nullptr;

	_uint							m_iNumKeyFrames = 0;
	_uint							m_iCurrentKeyFrame = 0;
	_uint							m_iLastKeyFrame = 0;

	vector<KEYFRAME*>				m_KeyFrames;
	typedef vector<KEYFRAME*>		KEYFRAMES;

	class CHierarchyNode*			m_pHierarchyNode = nullptr;

private:
	_float4x4						m_TransformationMatrix;
	_bool							m_isCloned = false;
	_bool							m_KeyFinished = false;
private:

	HRESULT Ready_KeyFrames(aiNodeAnim* pAIChannel);
	HRESULT Ready_KeyFrames(CHANNELDESC* pData);

public:

	KEYFRAME Get_LastKeyFrame(_double PlayTime) {
		return *m_KeyFrames[m_iLastKeyFrame];
	}
	void Change_Compute_TransformationMatrix(_double PlayTime, KEYFRAME PreMat);


public:
	static CChannel* Create(aiNodeAnim* pAIChannel);
	static CChannel* Create(CHANNELDESC* pData);
	CChannel* Clone();
	virtual void Free() override;
};

END