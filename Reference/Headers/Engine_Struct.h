#pragma once

namespace Engine
{
	typedef struct Save_Paricle_Data {
		int ImageIndex;
		int ShaderIndex;
		float RemoveAlpha;
		XMFLOAT4 Color1;
		XMFLOAT4 Color2;
		XMFLOAT4 Direction;
		bool isRepeat;
		bool isAxisRotation;
		bool isArriveRemove;
		int VectorSize;
		float Duration;
		XMFLOAT2 RandSpeed;
		float Speed;
	}SAVEPARTICLE;

	typedef struct LOADDATA {
		int TileCnt;
		int LandCnt;
		int ObjCnt;
		int PortalCnt;
		int InteractCnt;
	}LOADDATA;

	typedef struct SAVEDESC { //����
		int TagIndex;
		int Number;
		int StageIndex;
		XMFLOAT4X4 WorldMtx;
	}SAVEDESC;

	typedef struct SAVETILE {
		int TagIndex;
		int Number;
		XMFLOAT4X4 WorldMtx;
	}SAVETILE;

	typedef struct SAVEPORTAL {
		int TagIndex;
		int Type;
		int TileIndex;
		int LinkTileIndex;
		XMFLOAT3 LinkPos;
		XMFLOAT3 LinkOutDir;
		XMFLOAT4X4 WorldMtx;
	}SAVEPORTAL;


	typedef struct CELLDESC {
		XMFLOAT3 PointA;
		XMFLOAT3 PointB;
		XMFLOAT3 PointC;
		int Index;
	}CELLDESC;

	typedef struct tagKeyFrame
	{
		XMFLOAT3			vScale;
		XMFLOAT4			vRotation;
		XMFLOAT3			vTranslation;
		double				Time;
	}KEYFRAME;

	typedef struct tagModelMaterial
	{
		class CTexture*		pMaterials[AI_TEXTURE_TYPE_MAX];
	}MODELMATERIAL;

	typedef struct tagLightDesc
	{
		enum TYPE { TYPE_DIRECTIONAL, TYPE_POINT, TYPE_END };
		TYPE			eType;

		// �������� �ʿ��� ����
		XMFLOAT4		vPosition;
		float			fRange;

		// ���Ɽ�� �ʿ��� ����
		XMFLOAT4		vDirection;

		// ���������� �ʿ��� ����
		XMFLOAT4		vDiffuse;
		XMFLOAT4		vAmbient;// = (1.f, 1.f, 1.f, 1.f);
		XMFLOAT4		vSpecular;

	}LIGHTDESC;

	typedef struct tagMaterial
	{
		XMFLOAT4		vDiffuse;
		XMFLOAT4		vAmbient;// = (0.4f, 0.4f, 0.4f, 1.f);
		XMFLOAT4		vSpecular;
		float			fPower;

	}MATERIALDESC;

	typedef struct tagVertex_Non_Anim_Model
	{
		XMFLOAT3		vPosition;
		XMFLOAT3		vNormal;
		XMFLOAT2		vTexUV;
	}VTXNONANIMMODEL;


	typedef struct ENGINE_DLL tagVertex_Non_Anim_Model_Declaration
	{
		static const unsigned int iNumElements;
		static const D3D11_INPUT_ELEMENT_DESC	Elements[3];
	}VTXNONANIMMODEL_DECLARATION;


	typedef struct tagVertex_Normal_Texture
	{
		XMFLOAT3		vPosition;
		XMFLOAT3		vNormal;
		XMFLOAT2		vTexUV;
	}VTXNORTEX;

	typedef struct ENGINE_DLL tagVertex_Normal_Texture_Declaration
	{
		static const unsigned int iNumElements;
		static const D3D11_INPUT_ELEMENT_DESC	Elements[3];
	}VTXNORTEX_DECLARATION;


	typedef struct tagVertex_Matrix
	{
		XMFLOAT4		vRight, vUp, vLook, vTranslation, vDirection;
		XMFLOAT3		vAngle;
		float			fSpeed;
		float			fRotationSpeed;
		double			Time;
		XMFLOAT4		vOriginTrans;
		XMFLOAT3		vOriginAngle;
	}VTXMATRIX;

	typedef struct ENGINE_DLL tagVertex_Instance_Declaration
	{
		static const unsigned int iNumElements;
		static const D3D11_INPUT_ELEMENT_DESC	Elements[6];
	}VTXINSTANCE_DECLARATION;

	typedef struct tagVertex_Point
	{
		XMFLOAT3		vPosition;
		XMFLOAT2		vPSize;
	}VTXPOINT;

	typedef struct tagVertex_Anim_Model
	{
		XMFLOAT3		vPosition;
		XMFLOAT3		vNormal;
		XMFLOAT2		vTexUV;
		XMUINT4			vBlendIndex; /* �� ������ ������ �ִ� ���� �ε�����(�ִ� �װ�)*/
		XMFLOAT4		vBlendWeight; /* �� ��(�ִ� �װ�)�� �������� �ִ� ����(0.0 ~ 1.0) */
	}VTXANIMMODEL;

	typedef struct ENGINE_DLL tagVertex_Anim_Model_Declaration
	{
		static const unsigned int iNumElements;
		static const D3D11_INPUT_ELEMENT_DESC	Elements[5];
	}VTXANIMMODEL_DECLARATION;

	typedef struct tagVertex_Cube
	{
		XMFLOAT3		vPosition;
		XMFLOAT3		vTexUV;
	}VTXCUBE;

	typedef struct ENGINE_DLL tagVertex_Cube_Declaration
	{
		static const unsigned int iNumElements;
		static const D3D11_INPUT_ELEMENT_DESC	Elements[2];
	}VTXCUBE_DECLARATION;


	typedef struct tagVertex_Color
	{
		XMFLOAT3		vPosition;
		XMFLOAT4		vColor;
	}VTXCOL;

	typedef struct ENGINE_DLL tagVertex_Color_Declaration
	{
		static const unsigned int iNumElements;
		static const D3D11_INPUT_ELEMENT_DESC	Elements[2];
	}VTXCOL_DECLARATION;


	typedef struct tagVertex_Texture
	{
		XMFLOAT3		vPosition;
		XMFLOAT2		vTexUV;
	}VTXTEX;

	typedef struct ENGINE_DLL tagVertex_Texture_Declaration
	{
		static const unsigned int iNumElements;
		static const D3D11_INPUT_ELEMENT_DESC	Elements[2];
	}VTXTEX_DECLARATION;

	typedef struct tagVertex_Cube_Texture
	{
		XMFLOAT3		vPosition;
		XMFLOAT3		vTexUV;
	}VTXCUBETEX;

	typedef struct tagFaceListIndices32
	{
		unsigned long		_0, _1, _2;
	}FACELISTINDICES32;


	typedef struct tagFaceListIndices16
	{
		unsigned short		_0, _1, _2;
	}FACELISTINDICES16;

	typedef struct HIERARCHYDESC {
		char szName[70];
		int Index;
		int ParentIndex;
		XMFLOAT4X4 TPTransform;
		int Depth;
	}HIERARCHYDESC;

	typedef struct MESHCONTAINERDESC {
		int eType;
		int NumVertices;
		int NumPrimitive;
		int MaterialIndex;
		XMFLOAT4X4 Pivot;
		XMFLOAT3* VtxPosition;  //vertices
		XMFLOAT3* VtxNormal;
		XMFLOAT2* VtxTexUV;
		int* Indices; //NumPrimitive
		int NumBone; //�ִϸ��̼��� ���
		char MeshName[100];	//�ִϸ��̼�������
		int* NumMeshNode; //~��° �� ���� ����� ��������� �̸��� ������ �ε��� üũ
		int* NumWeights;
		XMFLOAT4X4* BoneOffsetMatrix; //Bone
		XMUINT4* BlendIndex; /* �� ������ ������ �ִ� ���� �ε�����(�ִ� �װ�)*/
		XMFLOAT4* BlendWeight; /* �� ��(�ִ� �װ�)�� �������� �ִ� ����(0.0 ~ 1.0) */
	}MESHCONTAINERDESC;

	typedef struct MATERIALSDESC {
		int MatIndex;
		int TexType;
		char FilePath[100];
	}MATERIALSDESC;

	typedef struct CHANNELDESC {
		char NodeName[100];
		int NumKeyFrames;
		KEYFRAME* KeyFrame;
	}CHANNELDESC;

	typedef struct ANIMATIONDESC {
		char Name[100];
		double Duration;
		double TickPerSecond;
		int NumChannels;
		int* NumChannelNode;
		CHANNELDESC* ChannelDesc;
	}ANIMATIONDESC;

	typedef struct MODELDATADESC {
		int NumChildren;
		int NumMeshContainers;
		int NumMataerails;
		int NumAnimations;
		int NumNodes;
		int NumMatData;
	}MODELDATADESC;
}
