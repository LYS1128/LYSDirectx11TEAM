
#include "Shader_Defines.hpp"


cbuffer Matrices
{
	float4x4		g_WorldMatrix, g_ViewMatrix, g_ProjMatrix;
	float4x4		g_SocketMatrix;
	float4x4		g_EachMatrix;
	float4x4		g_ViewMatrixInv, g_ProjMatrixInv;
}

float3				g_PortalColor;
float				g_ColorTime;
texture2D			g_PortalTexture;

texture2D			g_DiffuseTexture;
texture2D			g_NormalTexture;
texture2D			g_ObjectTexture;
texture2D			g_DepthTexture;
texture2D			g_TargetNormalTexture;
texture2D			g_StencilTexture;

float2				g_size;
float3				g_PlayerPos;
float3				g_fColor3;
float				g_RenderTick;
float				g_Color;//¼öÁ¤ºÎ¼ö±â
float				g_Length;
float				g_LimitLength;
float				g_Disolve;
float				g_R;
float				g_G;
float				g_B;
float				g_fPercent;
float				g_Frame;
bool				g_Spectrum;
bool				g_LightDead;

texture2D			g_EffectTexture;
texture2D			g_WhiteTexture;

texture2D			g_DisolveTexture;
texture2D			g_DisolveTexture2;
texture2D			g_MaskTexture;
texture2D			g_ColorTexture;
texture2D			g_Texture;
int					g_iSpawnX;
int					g_iSpawnY;

float4				g_TransformPos;

textureCUBE			g_FearCubeTexture;
float4				g_WorldLightPos;
float4				g_WorldCamPos;

//ÆÛÁñ
unsigned int		g_PipeColor;
bool				g_bStartRing;
bool				g_bPipe;

//Áö·ÚÃ£±â
unsigned int		g_CntMine;
bool				g_bFail;
bool				g_bRealMine;
bool				g_bFakeMine;

unsigned int		g_Index;
float				g_TrailMask;

sampler DefaultSampler = sampler_state {
	filter = min_mag_mip_linear;
	AddressU = wrap;
	AddressV = wrap;
};

sampler PointSampler = sampler_state {
	filter = min_mag_mip_point;
	AddressU = wrap;
	AddressV = wrap;
};

struct VS_IN
{
	float3		vPosition : POSITION;
	float3		vNormal : NORMAL;
	float2		vTexUV : TEXCOORD;
};


struct VS_OUT_MODEL
{
	float4		vPosition : SV_POSITION;
	float4		vNormal : NORMAL;
	float2		vTexUV : TEXCOORD0;
	float4		vProjPos : TEXCOORD1;
	float4		vWorldPos : TEXCOORD2;
};

struct VS_OUT_MODEL_ENVMAP
{
	float4		vPosition : SV_POSITION;
	float4		vNormal : NORMAL;
	float2		vTexUV : TEXCOORD0;
	float4		vProjPos : TEXCOORD1;
	float4		vWorldPos : TEXCOORD2;
	float3		vLightDir : TEXCOORD3;
	float3		vViewDir : TEXCOORD4;
};

VS_OUT_MODEL VS_MAIN_MODEL(VS_IN In)
{
	VS_OUT_MODEL		Out;

	float4		vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;
	Out.vNormal = normalize(mul(vector(In.vNormal, 0.f), g_WorldMatrix));
	Out.vTexUV = In.vTexUV;	
	Out.vProjPos = vPosition;

	Out.vWorldPos = mul(float4(In.vPosition, 1.f), g_WorldMatrix);

	return Out;
}

VS_OUT_MODEL VS_MAIN_MODEL_DEST(VS_IN In)
{
	VS_OUT_MODEL		Out;

	float4		vPosition = mul(float4(In.vPosition, 1.f), g_EachMatrix);
	vPosition = mul(vPosition, g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;
	Out.vNormal = normalize(mul(vector(In.vNormal, 0.f), g_WorldMatrix));
	Out.vTexUV = In.vTexUV;
	Out.vProjPos = vPosition;

	Out.vWorldPos = mul(float4(In.vPosition, 1.f), g_WorldMatrix);

	return Out;
}

VS_OUT_MODEL VS_MAIN_MODEL_SOCKET(VS_IN In)
{
	VS_OUT_MODEL		Out;

	matrix			matWS, matWSV, matWSVP;

	matWS = mul(g_WorldMatrix, g_SocketMatrix);
	matWSV = mul(matWS, g_ViewMatrix);
	matWSVP = mul(matWSV, g_ProjMatrix);

	Out.vPosition = mul(vector(In.vPosition, 1.f), matWSVP);
	Out.vNormal = normalize(mul(vector(In.vNormal, 0.f), g_WorldMatrix));
	Out.vTexUV = In.vTexUV;	
	Out.vProjPos = Out.vPosition;

	Out.vWorldPos = mul(float4(In.vPosition, 1.f), g_WorldMatrix);

	return Out;
}

VS_OUT_MODEL VS_MAIN_MODEL_7x4(VS_IN In)
{

	VS_OUT_MODEL      Out;

	float4      vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;
	Out.vNormal = normalize(mul(vector(In.vNormal, 0.f), g_WorldMatrix));
	Out.vTexUV = In.vTexUV;
	Out.vProjPos = vPosition;

	Out.vTexUV.x = In.vTexUV.x / 7.f + (1 / 7.f)*g_iSpawnX;
	Out.vTexUV.y = In.vTexUV.y / 4.f + (1 / 4.f)*g_iSpawnY;

	Out.vWorldPos = mul(float4(In.vPosition, 1.f), g_WorldMatrix);

	return Out;
}

VS_OUT_MODEL VS_MAIN_MODEL_6x12(VS_IN In)
{

	VS_OUT_MODEL      Out;

	float4      vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;
	Out.vNormal = normalize(mul(vector(In.vNormal, 0.f), g_WorldMatrix));
	Out.vTexUV = In.vTexUV;
	Out.vProjPos = vPosition;

	Out.vTexUV.x = In.vTexUV.x / 6.f + (1 / 6.f)*g_iSpawnX;
	Out.vTexUV.y = In.vTexUV.y / 12.f + (1 / 12.f)*g_iSpawnY;

	Out.vWorldPos = mul(float4(In.vPosition, 1.f), g_WorldMatrix);

	return Out;
}

VS_OUT_MODEL_ENVMAP VS_MAIN_MODEL_ENVMAP(VS_IN In)
{
	VS_OUT_MODEL_ENVMAP		Out;

	float4		vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;
	Out.vNormal = normalize(mul(vector(In.vNormal, 0.f), g_WorldMatrix));
	Out.vTexUV = In.vTexUV;
	Out.vProjPos = vPosition;

	Out.vWorldPos = mul(float4(In.vPosition, 1.f), g_WorldMatrix);

	Out.vLightDir = normalize(float3(1.f, -2.f, 1.f));
	Out.vViewDir = normalize(Out.vWorldPos.xyz - g_WorldCamPos.xyz);

	return Out;
}

struct PS_IN_MODEL
{
	float4		vPosition : SV_POSITION;
	float4		vNormal : NORMAL;
	float2		vTexUV : TEXCOORD0;
	float4		vProjPos : TEXCOORD1;
	float4		vWorldPos : TEXCOORD2;
};

struct PS_IN_MODEL_ENVMAP
{
	float4		vPosition : SV_POSITION;
	float4		vNormal : NORMAL;
	float2		vTexUV : TEXCOORD0;
	float4		vProjPos : TEXCOORD1;
	float4		vWorldPos : TEXCOORD2;
	float3		vLightDir : TEXCOORD3;
	float3		vViewDir : TEXCOORD4;
};

struct PS_OUT
{
	vector			vDiffuse : SV_TARGET0;
	vector			vNormal : SV_TARGET1;
	vector			vDepth : SV_TARGET2;
	vector			vEmissive : SV_TARGET3;
	vector			vEmissiveGlow : SV_TARGET4;
};

PS_OUT PS_MAIN_MODEL_SSD(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	Out.vDiffuse = vector(0.f, 0.f, 0.f, 0.f);

	float		fViewZ = In.vProjPos.w;

	float2		vUV;

	vUV.x = (In.vProjPos.x / In.vProjPos.w) * 0.5f + 0.5f;
	vUV.y = (In.vProjPos.y / In.vProjPos.w) * -0.5f + 0.5f;

	float4		Stencil = g_StencilTexture.Sample(DefaultSampler, vUV);

	if (Stencil.w == 1.f)
		discard;

	float4		vDepthDesc = g_DepthTexture.Sample(DefaultSampler, vUV);
	float		fTargetViewZ = vDepthDesc.y * 300.f;

	vector			vWorldPos;
	vWorldPos.x = vUV.x * 2.f - 1.f;
	vWorldPos.y = vUV.y * -2.f + 1.f;
	vWorldPos.z = vDepthDesc.x;
	vWorldPos.w = 1.f;

	vWorldPos = vWorldPos * fTargetViewZ;

	vWorldPos = mul(vWorldPos, g_ProjMatrixInv);
	vWorldPos = mul(vWorldPos, g_ViewMatrixInv);

	float2		vNewUV;
	vNewUV.x = (vWorldPos.x - (g_TransformPos.x - 0.5f*g_size.x)) / g_size.x;
	vNewUV.y = ((g_TransformPos.z + 0.5f*g_size.y) - vWorldPos.z) / g_size.y;

	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);

	if (vWorldPos.x <= g_TransformPos.x + 0.5f*g_size.x && vWorldPos.x >= g_TransformPos.x - 0.5f*g_size.x && vWorldPos.z <= g_TransformPos.z + 0.5f*g_size.y && vWorldPos.z >= g_TransformPos.z - 0.5f*g_size.y) {
		if (fTargetViewZ >= fViewZ) {
			Out.vDiffuse = g_Texture.Sample(DefaultSampler, vNewUV);
			vector vTargetNormal = g_TargetNormalTexture.Sample(DefaultSampler, vUV);
			float Cos = dot(Out.vNormal, vTargetNormal) - 0.5f;
			if (Cos < 0)
				discard;
		}
	}

	if (Out.vDiffuse.a < 0.1f)
		discard;

	return Out;
}

PS_OUT PS_MAIN_MODEL_SSD2(PS_IN_MODEL In)
{
	PS_OUT         Out = (PS_OUT)0;

	vector      vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	Out.vDiffuse = vector(0.f, 0.f, 0.f, 0.f);

	float      fViewZ = In.vProjPos.w;

	float2      vUV;

	vUV.x = (In.vProjPos.x / In.vProjPos.w) * 0.5f + 0.5f;
	vUV.y = (In.vProjPos.y / In.vProjPos.w) * -0.5f + 0.5f;

	float4      Stencil = g_StencilTexture.Sample(DefaultSampler, vUV);

	if (Stencil.w == 1.f)
		discard;

	float4      vDepthDesc = g_DepthTexture.Sample(DefaultSampler, vUV);
	float      fTargetViewZ = vDepthDesc.y * 300.f;

	vector         vWorldPos;
	vWorldPos.x = vUV.x * 2.f - 1.f;
	vWorldPos.y = vUV.y * -2.f + 1.f;
	vWorldPos.z = vDepthDesc.x;
	vWorldPos.w = 1.f;

	vWorldPos = vWorldPos * fTargetViewZ;

	vWorldPos = mul(vWorldPos, g_ProjMatrixInv);
	vWorldPos = mul(vWorldPos, g_ViewMatrixInv);

	float2      vNewUV;
	vNewUV.x = (vWorldPos.x - (g_TransformPos.x - 0.5f*g_size.x)) / g_size.x;
	vNewUV.y = ((g_TransformPos.z + 0.5f*g_size.y) - vWorldPos.z) / g_size.y;

	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);

	if (vWorldPos.x <= g_TransformPos.x + 0.5f*g_size.x && vWorldPos.x >= g_TransformPos.x - 0.5f*g_size.x && vWorldPos.z <= g_TransformPos.z + 0.5f*g_size.y && vWorldPos.z >= g_TransformPos.z - 0.5f*g_size.y) {
		if (fTargetViewZ >= fViewZ) {
			Out.vDiffuse = g_Texture.Sample(DefaultSampler, vNewUV);
			vector vTargetNormal = g_TargetNormalTexture.Sample(DefaultSampler, vUV);
			float Cos = dot(Out.vNormal, vTargetNormal) - 0.5f;
			if (Cos < 0)
				discard;
			vector Mask = g_MaskTexture.Sample(DefaultSampler, vNewUV);
			if (Mask.r <= g_fPercent) {
				discard;
			}
		}
	}

	if (Out.vDiffuse.a < 0.1f)
		discard;

	return Out;
}

PS_OUT PS_MAIN_MODEL_ENV(PS_IN_MODEL_ENVMAP In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
	//float Dist = distance(In.vWorldPos, g_PlayerPos)*0.01;
	//Out.vPlayerDist = vector(Dist, 0.f, 0.f, 1.f);
	//Out.vBlur = vector(0.f, 0.f, 0.f, 0.f);

	float2		NewUV = In.vTexUV;
	NewUV.y += g_RenderTick * 0.05f;

	vector Distortion = g_DisolveTexture2.Sample(DefaultSampler, NewUV);

	float fWeight = Distortion.r * 0.05f;

	float3 ViewReflect = reflect(In.vViewDir, In.vNormal);
	float3 EnvColor = g_FearCubeTexture.Sample(DefaultSampler, ViewReflect+float3(fWeight, fWeight, fWeight)).rgb;
	//float3 EnvColor = texCUBE(EnvSampler, ViewReflect).rgb;
	Out.vDiffuse = float4(EnvColor, 1.f);
	//Out.vDiffuse += float4(EnvColor*0.5, 1.f);
	if (vMtrlDiffuse.a < 0.1f)
		discard;

	return Out;
}

PS_OUT PS_MAIN_MODEL(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
	//float Dist = distance(In.vWorldPos, g_PlayerPos)*0.01;
	//Out.vPlayerDist = vector(Dist, 0.f,0.f, 1.f);
	//Out.vBlur = vector(0.f,0.f,0.f,0.f);

	if (vMtrlDiffuse.a < 0.1f)
		discard;

	return Out;
}

float4 g_vSIPos;
PS_OUT PS_MAIN_MODEL_SCREENIMAGE(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);

	//float Dist = distance(In.vWorldPos, g_PlayerPos)*0.01;
	//Out.vPlayerDist = vector(Dist, 0.f,0.f, 1.f);
	//Out.vBlur = vector(0.f,0.f,0.f,0.f);

	if (vMtrlDiffuse.a < 0.1f)
		discard;

	if (In.vWorldPos.y > 31.f)
		discard;

	if (In.vWorldPos.y < 7.f)
		discard;

	return Out;
}

PS_OUT PS_MAIN_MODEL_GREEN(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;


	float2 NewUV = In.vTexUV + float2(0.f, g_RenderTick);
	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, NewUV);

	Out.vDiffuse = vMtrlDiffuse;
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
	//float Dist = distance(In.vWorldPos, g_PlayerPos)*0.01;
	//Out.vPlayerDist = vector(Dist, 0.f,0.f, 1.f);
	//Out.vBlur = vector(0.f,0.f,0.f,0.f);

	if (vMtrlDiffuse.a < 0.1f)
		discard;

	return Out;
}

PS_OUT PS_MAIN_MODEL_TEX(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vMtrlObjTex = g_ObjectTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vMtrlWhite = g_WhiteTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse *vMtrlObjTex + 0.3* vector(1.f - vMtrlWhite.r,1.f- vMtrlWhite.r, 1.f - vMtrlWhite.r,0.f) + 0.3*vector(1.f - vMtrlWhite.g, 1.f - vMtrlWhite.g, 1.f - vMtrlWhite.g, 0.f) + 0.3* vector(1.f - vMtrlWhite.b, 1.f - vMtrlWhite.b, 1.f - vMtrlWhite.b, 0.f);



	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
	//float Dist = distance(In.vWorldPos, g_PlayerPos)*0.01;
	//Out.vPlayerDist = vector(Dist, 0.f, 0.f, 1.f);
	//Out.vBlur = vector(0.f, 0.f, 0.f, 0.f);

	//if (g_RenderTick / 255.f >= vMtrlObjTex.r)
	//	discard;

	if (vMtrlDiffuse.a < 0.1f)
		discard;

	return Out;
}

PS_OUT PS_MAIN_MODEL_LAVA(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	float2		NewUV = In.vTexUV;
	NewUV.y -= g_RenderTick * 0.05f; 
	NewUV.x -= g_RenderTick * 0.01f;

	Out.vDiffuse = g_DiffuseTexture.Sample(DefaultSampler, NewUV);
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);

	if (Out.vDiffuse.a < 0.1f)
		discard;

	if (Out.vDiffuse.g < 0.3f) {
		Out.vEmissive = Out.vDiffuse;
	}

	return Out;
}

PS_OUT PS_MAIN_MODEL_LAVA2(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;
	
	vector Disolve = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);
	vector Mtrl = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	float2		NewUV = In.vTexUV;
	NewUV.y -= g_RenderTick * 0.05f;

	Out.vDiffuse = g_DiffuseTexture.Sample(DefaultSampler, NewUV);
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);

	if (Out.vDiffuse.g <= Disolve.r)
		discard;

	if (Out.vDiffuse.g > 0.5f) {
		Out.vEmissive = Out.vDiffuse;
	}

	if (Out.vDiffuse.a < 0.1f)
		discard;

	return Out;
}

PS_OUT PS_MAIN_MODEL_TEX_EM(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vMtrlObjTex = g_ObjectTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vMtrlWhite = g_WhiteTexture.Sample(DefaultSampler, In.vTexUV);

	float3 DiffuseCol = float3(vMtrlDiffuse.x, vMtrlDiffuse.y, vMtrlDiffuse.z);

	if ((DiffuseCol.x == 0.8f && DiffuseCol.y == 0.8f && DiffuseCol.z == 0.8f) ||
		(DiffuseCol.x == 0.4f && DiffuseCol.y == 0.f && DiffuseCol.z == 0.6f) ||
		(DiffuseCol.x == 0.2f && DiffuseCol.y == 1.f && DiffuseCol.z == 0.2f) ||
		(DiffuseCol.x == 0.2f && DiffuseCol.y == 0.2f && DiffuseCol.z == 1.f) ||
		(DiffuseCol.x == 1.f && DiffuseCol.y == 1.f && DiffuseCol.z == 0.2f) ||
		(DiffuseCol.x == 1.f && DiffuseCol.y == 0.2f && DiffuseCol.z == 0.2f) ||
		(DiffuseCol.x == 1.f && DiffuseCol.y == 0.6f && DiffuseCol.z == 0.8f)) {
		Out.vEmissive = vMtrlDiffuse;
		Out.vEmissiveGlow = vMtrlDiffuse;
	}

	Out.vDiffuse = vMtrlDiffuse *vMtrlObjTex + 0.3* vector(1.f - vMtrlWhite.r, 1.f - vMtrlWhite.r, 1.f - vMtrlWhite.r, 0.f) + 0.3*vector(1.f - vMtrlWhite.g, 1.f - vMtrlWhite.g, 1.f - vMtrlWhite.g, 0.f) + 0.3* vector(1.f - vMtrlWhite.b, 1.f - vMtrlWhite.b, 1.f - vMtrlWhite.b, 0.f);

	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
	//float Dist = distance(In.vWorldPos, g_PlayerPos)*0.01;
	//Out.vPlayerDist = vector(Dist, 0.f, 0.f, 1.f);
	//Out.vBlur = vector(0.f, 0.f, 0.f, 0.f);

	//if (g_RenderTick / 255.f >= vMtrlObjTex.r)
	//	discard;

	if (vMtrlDiffuse.a < 0.1f)
		discard;

	return Out;
}

PS_OUT PS_MAIN_MODEL_TEX_WEM(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vMtrlObjTex = g_ObjectTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vMtrlWhite = g_WhiteTexture.Sample(DefaultSampler, In.vTexUV);

	if (vMtrlDiffuse.x == 0.2f && vMtrlDiffuse.y == 0.2f && vMtrlDiffuse.z == 0.2f) {
		discard;
	}

	Out.vDiffuse = vMtrlDiffuse *vMtrlObjTex + 0.3* vector(1.f - vMtrlWhite.r, 1.f - vMtrlWhite.r, 1.f - vMtrlWhite.r, 0.f) + 0.3*vector(1.f - vMtrlWhite.g, 1.f - vMtrlWhite.g, 1.f - vMtrlWhite.g, 0.f) + 0.3* vector(1.f - vMtrlWhite.b, 1.f - vMtrlWhite.b, 1.f - vMtrlWhite.b, 0.f);

	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
//	float Dist = distance(In.vWorldPos, g_PlayerPos)*0.01;
	//Out.vPlayerDist = vector(Dist, 0.f, 0.f, 1.f);
	//Out.vBlur = vector(0.f, 0.f, 0.f, 0.f);

	//if (g_RenderTick / 255.f >= vMtrlObjTex.r)
	//	discard;

	if (vMtrlDiffuse.a < 0.1f)
		discard;

	return Out;
}

PS_OUT PS_MAIN_MODEL_TEX2(PS_IN_MODEL In)
{
	PS_OUT         Out = (PS_OUT)0;

	vector      vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector      vMtrlObjTex = g_ObjectTexture.Sample(DefaultSampler, In.vTexUV);
	vector      vMtrlWhite = g_WhiteTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse + 0.1* vector(1.f - vMtrlWhite.r, 1.f - vMtrlWhite.r, 1.f - vMtrlWhite.r, 0.f) + 0.1*vector(1.f - vMtrlWhite.g, 1.f - vMtrlWhite.g, 1.f - vMtrlWhite.g, 0.f) + 0.1* vector(1.f - vMtrlWhite.b, 1.f - vMtrlWhite.b, 1.f - vMtrlWhite.b, 0.f);

	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
	//float Dist = distance(In.vWorldPos, g_PlayerPos)*0.01;
	//Out.vPlayerDist = vector(Dist, 0.f, 0.f, 1.f);
	//Out.vBlur = vector(0.f, 0.f, 0.f, 0.f);

	if (g_RenderTick / 255.f >= vMtrlObjTex.r)
		discard;

	if (vMtrlDiffuse.a < 0.1f)
		discard;

	return Out;
}

PS_OUT PS_MAIN_GAMESTART(PS_IN_MODEL In)
{
	PS_OUT		Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vMtrlObjTex = g_ObjectTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vDissolve = g_EffectTexture.Sample(DefaultSampler, In.vTexUV);


	Out.vDiffuse = vMtrlDiffuse *vMtrlObjTex;

	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
	float Dist = distance(In.vWorldPos, g_PlayerPos)*0.01;
	//Out.vPlayerDist = vector(Dist, 0.f, 0.f, 1.f);
	//Out.vBlur = vector(0.f, 0.f, 0.f, 0.f);

	if (vMtrlDiffuse.a < 0.1f)
		discard;

	if (g_RenderTick / 1020.f >= Dist && g_RenderTick / 45.f >= vDissolve.r)
		discard;

	return Out;
}

PS_OUT PS_MAIN_MODEL_DISSOLVE(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	vector		vDissolve = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
	//float Dist = distance(In.vWorldPos, g_PlayerPos)*0.01;
	//Out.vPlayerDist = vector(Dist, 0.f, 0.f, 1.f);
	//Out.vBlur = vector(0.f, 0.f, 0.f, 0.f);

	if (vMtrlDiffuse.a < 0.1f)
		discard;

	if (g_RenderTick / 255.f >= vDissolve.r)
		discard;

	return Out;
}

PS_OUT PS_MAIN_MODEL_TEX_BLUR(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vMtrlObjTex = g_ObjectTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vMtrlWhite = g_WhiteTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse *vMtrlObjTex + 0.3* vector(1.f - vMtrlWhite.r, 1.f - vMtrlWhite.r, 1.f - vMtrlWhite.r, 0.f) + 0.3*vector(1.f - vMtrlWhite.g, 1.f - vMtrlWhite.g, 1.f - vMtrlWhite.g, 0.f) + 0.3* vector(1.f - vMtrlWhite.b, 1.f - vMtrlWhite.b, 1.f - vMtrlWhite.b, 0.f);



	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
	//float Dist = distance(In.vWorldPos, g_PlayerPos)*0.01;
	//Out.vPlayerDist = vector(Dist, 0.f, 0.f, 1.f);
	//Out.vBlur = Out.vDiffuse;

	if (vMtrlDiffuse.a < 0.1f)
		discard;

	return Out;
}

PS_OUT PS_BUBBLE(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);


	Out.vDiffuse.r -= 0.3f;
	Out.vDiffuse.g -= 0.4f;

	if (vMtrlDiffuse.a < 0.1f)
		discard;
	if (In.vTexUV.y <= g_fPercent)
		discard;
	return Out;
}

PS_OUT PS_MAIN_MODEL_PUZZLE(PS_IN_MODEL In)//ÆÛÁñ
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
	//float Dist = distance(In.vWorldPos, g_PlayerPos)*0.01;
	//Out.vPlayerDist = vector(Dist, 0.f, 0.f, 1.f);

	if (false == g_bStartRing)
	{
		if (Out.vDiffuse.r == 0.f)
		{
			Out.vDiffuse.r = 10 / 255.f;
			Out.vDiffuse.g = 15 / 255.f;
			Out.vDiffuse.b = 18 / 255.f;
		}
		//ÆÄÀÌÇÁ »ö
		if (false == g_bPipe)
		{
			if (Out.vDiffuse.r > 0.9f)
			{
				Out.vDiffuse.r = 37 / 255.f;
				Out.vDiffuse.g = 0 / 255.f;
				Out.vDiffuse.b = 182 / 255.f;
				/*Out.vDiffuse.r = 133 / 255.f;
				Out.vDiffuse.g = 85 / 255.f;
				Out.vDiffuse.b = 255 / 255.f;*/
			}
		}
		else if (true == g_bPipe)
		{
			if (1 == g_PipeColor)
			{
				if (Out.vDiffuse.r > 0.9f)
				{
					Out.vDiffuse.r = 255 / 255.f;
					Out.vDiffuse.g = 179 / 255.f;
					Out.vDiffuse.b = 0 / 255.f;
				}
			}
		}
	}
	else
	{
		if (1 == g_PipeColor)
		{
			if (Out.vDiffuse.r == 0.f)
			{
				Out.vDiffuse.r = 255 / 255.f;
				Out.vDiffuse.g = 179 / 255.f;
				Out.vDiffuse.b = 0 / 255.f;
			}

			if (Out.vDiffuse.r > 0.9f)
			{
				Out.vDiffuse.r = 255 / 255.f;
				Out.vDiffuse.g = 179 / 255.f;
				Out.vDiffuse.b = 0 / 255.f;
			}
		}
	}
	if (255/255.f == Out.vDiffuse.r || 37 /255.f == Out.vDiffuse.r)
	{
		Out.vEmissive = vector(Out.vDiffuse.r, Out.vDiffuse.g, Out.vDiffuse.b,0.2f);
		Out.vEmissiveGlow = Out.vDiffuse;
	}

	return Out;
}

PS_OUT PS_MAIN_MODEL_MINE(PS_IN_MODEL In)//Áö·ÚÃ£±â
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
	//float Dist = distance(In.vWorldPos, g_PlayerPos)*0.01;
	//Out.vPlayerDist = vector(Dist, 0.f, 0.f, 1.f);

	//ÀÚ »ö³ª´©ÀÚ
	if (true == g_bFail)
	{
		if (255 / 255.f == Out.vDiffuse.r && 255 / 255.f == Out.vDiffuse.g && 255 / 255.f == Out.vDiffuse.b)
		{
			Out.vDiffuse.r = 0/255.f;
			Out.vDiffuse.g = 0/255.f;
			Out.vDiffuse.b = 0/255.f;
		}
		if (1 / 255.f == Out.vDiffuse.r && 1 / 255.f == Out.vDiffuse.g && 1 / 255.f == Out.vDiffuse.b)
			discard;
		if (10 / 255.f == Out.vDiffuse.r && 10 / 255.f == Out.vDiffuse.g && 10 / 255.f == Out.vDiffuse.b)
			discard;
		if (20 / 255.f == Out.vDiffuse.r && 20 / 255.f == Out.vDiffuse.g && 20 / 255.f == Out.vDiffuse.b)
			discard;
		if (30 / 255.f == Out.vDiffuse.r && 30 / 255.f == Out.vDiffuse.g && 30 / 255.f == Out.vDiffuse.b)
			discard;
		if (40 / 255.f == Out.vDiffuse.r && 40 / 255.f == Out.vDiffuse.g && 40 / 255.f == Out.vDiffuse.b)
			discard;
		if (50 / 255.f == Out.vDiffuse.r && 50 / 255.f == Out.vDiffuse.g && 50 / 255.f == Out.vDiffuse.b)
			discard;
		if (60 / 255.f == Out.vDiffuse.r && 60 / 255.f == Out.vDiffuse.g && 60 / 255.f == Out.vDiffuse.b)
			discard;
		if (70 / 255.f == Out.vDiffuse.r && 70 / 255.f == Out.vDiffuse.g && 70 / 255.f == Out.vDiffuse.b)
			discard;
		if (80 / 255.f == Out.vDiffuse.r && 80 / 255.f == Out.vDiffuse.g && 80 / 255.f == Out.vDiffuse.b)
			discard;
	}
	else
	{
		if (true == g_bRealMine || true == g_bFakeMine)
		{
			if (255 / 255.f == Out.vDiffuse.r && 0 / 255.f == Out.vDiffuse.g && 0 / 255.f == Out.vDiffuse.b)
				discard;
			if (255 / 255.f == Out.vDiffuse.r && 255 / 255.f == Out.vDiffuse.g && 255 / 255.f == Out.vDiffuse.b)
			{
				Out.vDiffuse.r = 255/255.f;
				Out.vDiffuse.g = 179/255.f;
				Out.vDiffuse.b = 0/255.f;
			}
			if (1 / 255.f == Out.vDiffuse.r && 1 / 255.f == Out.vDiffuse.g && 1 / 255.f == Out.vDiffuse.b)
			{
				Out.vDiffuse.r = 255/255.f;
				Out.vDiffuse.g = 179/255.f;
				Out.vDiffuse.b = 0/255.f;
			}
			if (10 / 255.f == Out.vDiffuse.r && 10 / 255.f == Out.vDiffuse.g && 10 / 255.f == Out.vDiffuse.b)
				discard;
			if (20 / 255.f == Out.vDiffuse.r && 20 / 255.f == Out.vDiffuse.g && 20 / 255.f == Out.vDiffuse.b)
				discard;
			if (30 / 255.f == Out.vDiffuse.r && 30 / 255.f == Out.vDiffuse.g && 30 / 255.f == Out.vDiffuse.b)
				discard;
			if (40 / 255.f == Out.vDiffuse.r && 40 / 255.f == Out.vDiffuse.g && 40 / 255.f == Out.vDiffuse.b)
				discard;
			if (50 / 255.f == Out.vDiffuse.r && 50 / 255.f == Out.vDiffuse.g && 50 / 255.f == Out.vDiffuse.b)
				discard;
			if (60 / 255.f == Out.vDiffuse.r && 60 / 255.f == Out.vDiffuse.g && 60 / 255.f == Out.vDiffuse.b)
				discard;
			if (70 / 255.f == Out.vDiffuse.r && 70 / 255.f == Out.vDiffuse.g && 70 / 255.f == Out.vDiffuse.b)
				discard;
			if (80 / 255.f == Out.vDiffuse.r && 80 / 255.f == Out.vDiffuse.g && 80 / 255.f == Out.vDiffuse.b)
				discard;
		}
		if (false == g_bRealMine && false == g_bFakeMine)
		{
			if (255 / 255.f == Out.vDiffuse.r && 0 / 255.f == Out.vDiffuse.g && 0 / 255.f == Out.vDiffuse.b)
				discard;
			if (255 / 255.f == Out.vDiffuse.r && 255 / 255.f == Out.vDiffuse.g && 255 / 255.f == Out.vDiffuse.b)
			{
				Out.vDiffuse.r = 0 / 255.f;
				Out.vDiffuse.g = 0 / 255.f;
				Out.vDiffuse.b = 0 / 255.f;
			}
			if (0 == g_CntMine)
			{
				if (1 / 255.f == Out.vDiffuse.r && 1 / 255.f == Out.vDiffuse.g && 1 / 255.f == Out.vDiffuse.b)
				{
					Out.vDiffuse.r = 37 / 255.f;
					Out.vDiffuse.g = 0 / 255.f;
					Out.vDiffuse.b = 182 / 255.f;
				}
				if (10 / 255.f == Out.vDiffuse.r && 10 / 255.f == Out.vDiffuse.g && 10 / 255.f == Out.vDiffuse.b)
					discard;
				if (20 / 255.f == Out.vDiffuse.r && 20 / 255.f == Out.vDiffuse.g && 20 / 255.f == Out.vDiffuse.b)
					discard;
				if (30 / 255.f == Out.vDiffuse.r && 30 / 255.f == Out.vDiffuse.g && 30 / 255.f == Out.vDiffuse.b)
					discard;
				if (40 / 255.f == Out.vDiffuse.r && 40 / 255.f == Out.vDiffuse.g && 40 / 255.f == Out.vDiffuse.b)
					discard;
				if (50 / 255.f == Out.vDiffuse.r && 50 / 255.f == Out.vDiffuse.g && 50 / 255.f == Out.vDiffuse.b)
					discard;
				if (60 / 255.f == Out.vDiffuse.r && 60 / 255.f == Out.vDiffuse.g && 60 / 255.f == Out.vDiffuse.b)
					discard;
				if (70 / 255.f == Out.vDiffuse.r && 70 / 255.f == Out.vDiffuse.g && 70 / 255.f == Out.vDiffuse.b)
					discard;
				if (80 / 255.f == Out.vDiffuse.r && 80 / 255.f == Out.vDiffuse.g && 80 / 255.f == Out.vDiffuse.b)
					discard;
			}
			else if (1 == g_CntMine)
			{
				if (1 / 255.f == Out.vDiffuse.r && 1 / 255.f == Out.vDiffuse.g && 1 / 255.f == Out.vDiffuse.b)
					discard;
				if (10 / 255.f == Out.vDiffuse.r && 10 / 255.f == Out.vDiffuse.g && 10 / 255.f == Out.vDiffuse.b)
				{
					Out.vDiffuse.r = 37 / 255.f;
					Out.vDiffuse.g = 0 / 255.f;
					Out.vDiffuse.b = 182 / 255.f;
				}
				if (20 / 255.f == Out.vDiffuse.r && 20 / 255.f == Out.vDiffuse.g && 20 / 255.f == Out.vDiffuse.b)
					discard;
				if (30 / 255.f == Out.vDiffuse.r && 30 / 255.f == Out.vDiffuse.g && 30 / 255.f == Out.vDiffuse.b)
					discard;
				if (40 / 255.f == Out.vDiffuse.r && 40 / 255.f == Out.vDiffuse.g && 40 / 255.f == Out.vDiffuse.b)
					discard;
				if (50 / 255.f == Out.vDiffuse.r && 50 / 255.f == Out.vDiffuse.g && 50 / 255.f == Out.vDiffuse.b)
					discard;
				if (60 / 255.f == Out.vDiffuse.r && 60 / 255.f == Out.vDiffuse.g && 60 / 255.f == Out.vDiffuse.b)
					discard;
				if (70 / 255.f == Out.vDiffuse.r && 70 / 255.f == Out.vDiffuse.g && 70 / 255.f == Out.vDiffuse.b)
					discard;
				if (80 / 255.f == Out.vDiffuse.r && 80 / 255.f == Out.vDiffuse.g && 80 / 255.f == Out.vDiffuse.b)
					discard;
			}
			else if (2 == g_CntMine)
			{
				if (1 / 255.f == Out.vDiffuse.r && 1 / 255.f == Out.vDiffuse.g && 1 / 255.f == Out.vDiffuse.b)
					discard;
				if (10 / 255.f == Out.vDiffuse.r && 10 / 255.f == Out.vDiffuse.g && 10 / 255.f == Out.vDiffuse.b)
					discard;
				if (20 / 255.f == Out.vDiffuse.r && 20 / 255.f == Out.vDiffuse.g && 20 / 255.f == Out.vDiffuse.b)
				{
					Out.vDiffuse.r = 37 / 255.f;
					Out.vDiffuse.g = 0 / 255.f;
					Out.vDiffuse.b = 182 / 255.f;
				}
				if (30 / 255.f == Out.vDiffuse.r && 30 / 255.f == Out.vDiffuse.g && 30 / 255.f == Out.vDiffuse.b)
					discard;
				if (40 / 255.f == Out.vDiffuse.r && 40 / 255.f == Out.vDiffuse.g && 40 / 255.f == Out.vDiffuse.b)
					discard;
				if (50 / 255.f == Out.vDiffuse.r && 50 / 255.f == Out.vDiffuse.g && 50 / 255.f == Out.vDiffuse.b)
					discard;
				if (60 / 255.f == Out.vDiffuse.r && 60 / 255.f == Out.vDiffuse.g && 60 / 255.f == Out.vDiffuse.b)
					discard;
				if (70 / 255.f == Out.vDiffuse.r && 70 / 255.f == Out.vDiffuse.g && 70 / 255.f == Out.vDiffuse.b)
					discard;
				if (80 / 255.f == Out.vDiffuse.r && 80 / 255.f == Out.vDiffuse.g && 80 / 255.f == Out.vDiffuse.b)
					discard;
			}
			else if (3 == g_CntMine)
			{
				if (1 / 255.f == Out.vDiffuse.r && 1 / 255.f == Out.vDiffuse.g && 1 / 255.f == Out.vDiffuse.b)
					discard;
				if (10 / 255.f == Out.vDiffuse.r && 10 / 255.f == Out.vDiffuse.g && 10 / 255.f == Out.vDiffuse.b)
					discard;
				if (20 / 255.f == Out.vDiffuse.r && 20 / 255.f == Out.vDiffuse.g && 20 / 255.f == Out.vDiffuse.b)
					discard;
				if (30 / 255.f == Out.vDiffuse.r && 30 / 255.f == Out.vDiffuse.g && 30 / 255.f == Out.vDiffuse.b)
				{
					Out.vDiffuse.r = 37 / 255.f;
					Out.vDiffuse.g = 0 / 255.f;
					Out.vDiffuse.b = 182 / 255.f;
				}
				if (40 / 255.f == Out.vDiffuse.r && 40 / 255.f == Out.vDiffuse.g && 40 / 255.f == Out.vDiffuse.b)
					discard;
				if (50 / 255.f == Out.vDiffuse.r && 50 / 255.f == Out.vDiffuse.g && 50 / 255.f == Out.vDiffuse.b)
					discard;
				if (60 / 255.f == Out.vDiffuse.r && 60 / 255.f == Out.vDiffuse.g && 60 / 255.f == Out.vDiffuse.b)
					discard;
				if (70 / 255.f == Out.vDiffuse.r && 70 / 255.f == Out.vDiffuse.g && 70 / 255.f == Out.vDiffuse.b)
					discard;
				if (80 / 255.f == Out.vDiffuse.r && 80 / 255.f == Out.vDiffuse.g && 80 / 255.f == Out.vDiffuse.b)
					discard;
			}
			else if (4 == g_CntMine)
			{
				if (1 / 255.f == Out.vDiffuse.r && 1 / 255.f == Out.vDiffuse.g && 1 / 255.f == Out.vDiffuse.b)
					discard;
				if (10 / 255.f == Out.vDiffuse.r && 10 / 255.f == Out.vDiffuse.g && 10 / 255.f == Out.vDiffuse.b)
					discard;
				if (20 / 255.f == Out.vDiffuse.r && 20 / 255.f == Out.vDiffuse.g && 20 / 255.f == Out.vDiffuse.b)
					discard;
				if (30 / 255.f == Out.vDiffuse.r && 30 / 255.f == Out.vDiffuse.g && 30 / 255.f == Out.vDiffuse.b)
					discard;
				if (40 / 255.f == Out.vDiffuse.r && 40 / 255.f == Out.vDiffuse.g && 40 / 255.f == Out.vDiffuse.b)
				{
					Out.vDiffuse.r = 37 / 255.f;
					Out.vDiffuse.g = 0 / 255.f;
					Out.vDiffuse.b = 182 / 255.f;
				}
				if (50 / 255.f == Out.vDiffuse.r && 50 / 255.f == Out.vDiffuse.g && 50 / 255.f == Out.vDiffuse.b)
					discard;
				if (60 / 255.f == Out.vDiffuse.r && 60 / 255.f == Out.vDiffuse.g && 60 / 255.f == Out.vDiffuse.b)
					discard;
				if (70 / 255.f == Out.vDiffuse.r && 70 / 255.f == Out.vDiffuse.g && 70 / 255.f == Out.vDiffuse.b)
					discard;
				if (80 / 255.f == Out.vDiffuse.r && 80 / 255.f == Out.vDiffuse.g && 80 / 255.f == Out.vDiffuse.b)
					discard;
			}
			else if (5 == g_CntMine)
			{
				if (1 / 255.f == Out.vDiffuse.r && 1 / 255.f == Out.vDiffuse.g && 1 / 255.f == Out.vDiffuse.b)
					discard;
				if (10 / 255.f == Out.vDiffuse.r && 10 / 255.f == Out.vDiffuse.g && 10 / 255.f == Out.vDiffuse.b)
					discard;
				if (20 / 255.f == Out.vDiffuse.r && 20 / 255.f == Out.vDiffuse.g && 20 / 255.f == Out.vDiffuse.b)
					discard;
				if (30 / 255.f == Out.vDiffuse.r && 30 / 255.f == Out.vDiffuse.g && 30 / 255.f == Out.vDiffuse.b)
					discard;
				if (40 / 255.f == Out.vDiffuse.r && 40 / 255.f == Out.vDiffuse.g && 40 / 255.f == Out.vDiffuse.b)
					discard;
				if (50 / 255.f == Out.vDiffuse.r && 50 / 255.f == Out.vDiffuse.g && 50 / 255.f == Out.vDiffuse.b)
				{
					Out.vDiffuse.r = 37 / 255.f;
					Out.vDiffuse.g = 0 / 255.f;
					Out.vDiffuse.b = 182 / 255.f;
				}
				if (60 / 255.f == Out.vDiffuse.r && 60 / 255.f == Out.vDiffuse.g && 60 / 255.f == Out.vDiffuse.b)
					discard;
				if (70 / 255.f == Out.vDiffuse.r && 70 / 255.f == Out.vDiffuse.g && 70 / 255.f == Out.vDiffuse.b)
					discard;
				if (80 / 255.f == Out.vDiffuse.r && 80 / 255.f == Out.vDiffuse.g && 80 / 255.f == Out.vDiffuse.b)
					discard;
			}
			else if (6 == g_CntMine)
			{
				if (1 / 255.f == Out.vDiffuse.r && 1 / 255.f == Out.vDiffuse.g && 1 / 255.f == Out.vDiffuse.b)
					discard;
				if (10 / 255.f == Out.vDiffuse.r && 10 / 255.f == Out.vDiffuse.g && 10 / 255.f == Out.vDiffuse.b)
					discard;
				if (20 / 255.f == Out.vDiffuse.r && 20 / 255.f == Out.vDiffuse.g && 20 / 255.f == Out.vDiffuse.b)
					discard;
				if (30 / 255.f == Out.vDiffuse.r && 30 / 255.f == Out.vDiffuse.g && 30 / 255.f == Out.vDiffuse.b)
					discard;
				if (40 / 255.f == Out.vDiffuse.r && 40 / 255.f == Out.vDiffuse.g && 40 / 255.f == Out.vDiffuse.b)
					discard;
				if (50 / 255.f == Out.vDiffuse.r && 50 / 255.f == Out.vDiffuse.g && 50 / 255.f == Out.vDiffuse.b)
					discard;
				if (60 / 255.f == Out.vDiffuse.r && 60 / 255.f == Out.vDiffuse.g && 60 / 255.f == Out.vDiffuse.b)
				{
					Out.vDiffuse.r = 37 / 255.f;
					Out.vDiffuse.g = 0 / 255.f;
					Out.vDiffuse.b = 182 / 255.f;
				}
				if (70 / 255.f == Out.vDiffuse.r && 70 / 255.f == Out.vDiffuse.g && 70 / 255.f == Out.vDiffuse.b)
					discard;
				if (80 / 255.f == Out.vDiffuse.r && 80 / 255.f == Out.vDiffuse.g && 80 / 255.f == Out.vDiffuse.b)
					discard;
			}
			else if (7 == g_CntMine)
			{
				if (1 / 255.f == Out.vDiffuse.r && 1 / 255.f == Out.vDiffuse.g && 1 / 255.f == Out.vDiffuse.b)
					discard;
				if (10 / 255.f == Out.vDiffuse.r && 10 / 255.f == Out.vDiffuse.g && 10 / 255.f == Out.vDiffuse.b)
					discard;
				if (20 / 255.f == Out.vDiffuse.r && 20 / 255.f == Out.vDiffuse.g && 20 / 255.f == Out.vDiffuse.b)
					discard;;
				if (30 / 255.f == Out.vDiffuse.r && 30 / 255.f == Out.vDiffuse.g && 30 / 255.f == Out.vDiffuse.b)
					discard;
				if (40 / 255.f == Out.vDiffuse.r && 40 / 255.f == Out.vDiffuse.g && 40 / 255.f == Out.vDiffuse.b)
					discard;
				if (50 / 255.f == Out.vDiffuse.r && 50 / 255.f == Out.vDiffuse.g && 50 / 255.f == Out.vDiffuse.b)
					discard;
				if (60 / 255.f == Out.vDiffuse.r && 60 / 255.f == Out.vDiffuse.g && 60 / 255.f == Out.vDiffuse.b)
					discard;
				if (70 / 255.f == Out.vDiffuse.r && 70 / 255.f == Out.vDiffuse.g && 70 / 255.f == Out.vDiffuse.b)
				{
					Out.vDiffuse.r = 37 / 255.f;
					Out.vDiffuse.g = 0 / 255.f;
					Out.vDiffuse.b = 182 / 255.f;
				}
				if (80 / 255.f == Out.vDiffuse.r && 80 / 255.f == Out.vDiffuse.g && 80 / 255.f == Out.vDiffuse.b)
					discard;
			}
			else
			{
				if (1 / 255.f == Out.vDiffuse.r && 1 / 255.f == Out.vDiffuse.g && 1 / 255.f == Out.vDiffuse.b)
				{

				}
				if (10 / 255.f == Out.vDiffuse.r && 10 / 255.f == Out.vDiffuse.g && 10 / 255.f == Out.vDiffuse.b)
					discard;
				if (20 / 255.f == Out.vDiffuse.r && 20 / 255.f == Out.vDiffuse.g && 20 / 255.f == Out.vDiffuse.b)
					discard;
				if (30 / 255.f == Out.vDiffuse.r && 30 / 255.f == Out.vDiffuse.g && 30 / 255.f == Out.vDiffuse.b)
					discard;
				if (40 / 255.f == Out.vDiffuse.r && 40 / 255.f == Out.vDiffuse.g && 40 / 255.f == Out.vDiffuse.b)
					discard;;
				if (50 / 255.f == Out.vDiffuse.r && 50 / 255.f == Out.vDiffuse.g && 50 / 255.f == Out.vDiffuse.b)
					discard;;
				if (60 / 255.f == Out.vDiffuse.r && 60 / 255.f == Out.vDiffuse.g && 60 / 255.f == Out.vDiffuse.b)
					discard;
				if (70 / 255.f == Out.vDiffuse.r && 70 / 255.f == Out.vDiffuse.g && 70 / 255.f == Out.vDiffuse.b)
					discard;
				if (80 / 255.f == Out.vDiffuse.r && 80 / 255.f == Out.vDiffuse.g && 80 / 255.f == Out.vDiffuse.b)
				{
					Out.vDiffuse.r = 37 / 255.f;
					Out.vDiffuse.g = 0 / 255.f;
					Out.vDiffuse.b = 182 / 255.f;
				}
			}
		}
	}
	if (37/255.f == Out.vDiffuse.r || 255/255.f == Out.vDiffuse.r)
	{
		Out.vEmissive = vector(Out.vDiffuse.r, Out.vDiffuse.g, Out.vDiffuse.b,0.2f);
		Out.vEmissiveGlow = Out.vDiffuse;
	}

	return Out;
}
PS_OUT PS_MAIN_WATCHWORLD(PS_IN_MODEL In)
{
	PS_OUT      Out = (PS_OUT)0;

	vector      vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector      vMtrlObjTex = g_ObjectTexture.Sample(DefaultSampler, In.vTexUV);
	vector      vDissolve = g_EffectTexture.Sample(DefaultSampler, In.vTexUV);


	Out.vDiffuse = vMtrlDiffuse *vMtrlObjTex;

	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
	float Dist = distance(In.vWorldPos, g_PlayerPos)*0.01;


	if (vMtrlDiffuse.a < 0.1f)
		discard;

	if (g_RenderTick / 1020.f >= vDissolve.r - 0.05f)
		Out.vDiffuse = vector(1.f, 1.f, 0.f, 1.f);

	if (g_RenderTick / 1020.f >= vDissolve.r)
		discard;

	return Out;
}

PS_OUT PS_MAIN_WATCHWORLD2(PS_IN_MODEL In)
{
	PS_OUT      Out = (PS_OUT)0;

	vector      vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector      vMtrlObjTex = g_ObjectTexture.Sample(DefaultSampler, In.vTexUV);
	vector      vDissolve = g_EffectTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vMtrlWhite = g_WhiteTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse *vMtrlObjTex + 0.3* vector(1.f - vMtrlWhite.r, 1.f - vMtrlWhite.r, 1.f - vMtrlWhite.r, 0.f) + 0.3*vector(1.f - vMtrlWhite.g, 1.f - vMtrlWhite.g, 1.f - vMtrlWhite.g, 0.f) + 0.3* vector(1.f - vMtrlWhite.b, 1.f - vMtrlWhite.b, 1.f - vMtrlWhite.b, 0.f);

	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
	float Dist = distance(In.vWorldPos, g_PlayerPos)*0.01;


	if (vMtrlDiffuse.a < 0.1f)
		discard;

	if (g_RenderTick / 1020.f >= vDissolve.r - 0.05f)
		Out.vDiffuse = vector(1.f, 1.f, 0.f, 1.f);

	if (g_RenderTick / 1020.f >= vDissolve.r)
		discard;

	return Out;
}

PS_OUT PS_MAIN_MODEL_TEX_EM_D(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vMtrlObjTex = g_ObjectTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vMtrlWhite = g_WhiteTexture.Sample(DefaultSampler, In.vTexUV);
	vector      vDissolve = g_EffectTexture.Sample(DefaultSampler, In.vTexUV);

	float3 DiffuseCol = float3(vMtrlDiffuse.x, vMtrlDiffuse.y, vMtrlDiffuse.z);

	if ((DiffuseCol.x == 0.8f && DiffuseCol.y == 0.8f && DiffuseCol.z == 0.8f) ||
		(DiffuseCol.x == 0.4f && DiffuseCol.y == 0.f && DiffuseCol.z == 0.6f) ||
		(DiffuseCol.x == 0.2f && DiffuseCol.y == 1.f && DiffuseCol.z == 0.2f) ||
		(DiffuseCol.x == 0.2f && DiffuseCol.y == 0.2f && DiffuseCol.z == 1.f) ||
		(DiffuseCol.x == 1.f && DiffuseCol.y == 1.f && DiffuseCol.z == 0.2f) ||
		(DiffuseCol.x == 1.f && DiffuseCol.y == 0.2f && DiffuseCol.z == 0.2f)) {
		Out.vEmissive = vMtrlDiffuse;
		Out.vEmissiveGlow = vMtrlDiffuse;
	}

	Out.vDiffuse = vMtrlDiffuse *vMtrlObjTex + 0.3* vector(1.f - vMtrlWhite.r, 1.f - vMtrlWhite.r, 1.f - vMtrlWhite.r, 0.f) + 0.3*vector(1.f - vMtrlWhite.g, 1.f - vMtrlWhite.g, 1.f - vMtrlWhite.g, 0.f) + 0.3* vector(1.f - vMtrlWhite.b, 1.f - vMtrlWhite.b, 1.f - vMtrlWhite.b, 0.f);

	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
	//float Dist = distance(In.vWorldPos, g_PlayerPos)*0.01;
	//Out.vPlayerDist = vector(Dist, 0.f, 0.f, 1.f);
	//Out.vBlur = vector(0.f, 0.f, 0.f, 0.f);

	//if (g_RenderTick / 255.f >= vMtrlObjTex.r)
	//	discard;

	if (vMtrlDiffuse.a < 0.1f)
		discard;

	if (g_RenderTick / 1020.f >= vDissolve.r - 0.05f)
		Out.vDiffuse = vector(1.f, 1.f, 0.f, 1.f);

	if (g_RenderTick / 1020.f >= vDissolve.r)
		discard;

	return Out;
}

PS_OUT PS_MAIN_MODEL_7x4(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	float2 vUV;
	vUV.x = (In.vTexUV.x - (1.f / 7.f)*g_iSpawnX)* 7.f;
	vUV.y = (In.vTexUV.y - (1.f / 4.f)*g_iSpawnY)*4.f;
	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vMtrlColor = g_Texture.Sample(DefaultSampler, vUV);

	Out.vDiffuse.rgb = vMtrlColor.rgb;
	Out.vDiffuse.a = vMtrlDiffuse.a;
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
	//float Dist = distance(In.vWorldPos, g_PlayerPos)*0.01;
	//Out.vPlayerDist = vector(Dist, 0.f, 0.f, 1.f);
	//Out.vBlur = vector(0.f, 0.f, 0.f, 0.f);

	if (vMtrlDiffuse.a < 0.1f)
		discard;

	return Out;
}

PS_OUT PS_MAIN_MODEL_6x12(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	float2 vUV;
	vUV.x = (In.vTexUV.x - (1 / 6.f)*g_iSpawnX)* 6.f;
	vUV.y = (In.vTexUV.y - (1 / 12.f)*g_iSpawnY)*12.f;
	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vMtrlColor = g_Texture.Sample(DefaultSampler, vUV);

	Out.vDiffuse.rgb = vMtrlColor.rgb;
	Out.vDiffuse.a = vMtrlDiffuse.a;
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
	//float Dist = distance(In.vWorldPos, g_PlayerPos)*0.01;
	//Out.vPlayerDist = vector(Dist, 0.f, 0.f, 1.f);
	//Out.vBlur = vector(0.f, 0.f, 0.f, 0.f);

	if (vMtrlDiffuse.a < 0.1f)
		discard;

	return Out;
}

PS_OUT PS_MAIN_MODEL_LAND(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vMtrlObjTex = g_ObjectTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vMtrlWhite = g_WhiteTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vDissolve = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse *vMtrlObjTex + 0.3* vector(1.f - vMtrlWhite.r, 1.f - vMtrlWhite.r, 1.f - vMtrlWhite.r, 0.f) + 0.3*vector(1.f - vMtrlWhite.g, 1.f - vMtrlWhite.g, 1.f - vMtrlWhite.g, 0.f) + 0.3* vector(1.f - vMtrlWhite.b, 1.f - vMtrlWhite.b, 1.f - vMtrlWhite.b, 0.f);

	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
	//float Dist = distance(In.vWorldPos, g_PlayerPos)*0.01;
	//Out.vPlayerDist = vector(Dist, 0.f, 0.f, 1.f);
	//Out.vBlur = vector(0.f, 0.f, 0.f, 0.f);

	if (vMtrlDiffuse.a < 0.1f)
		discard;

	if (vDissolve.r < 0.3f)
		Out.vDiffuse.a = vDissolve.r;
	else
		Out.vDiffuse.a = 1.f;

	return Out;
}

PS_OUT PS_MAIN_MODEL_ROCK(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vMtrlObjTex = g_ObjectTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vMtrlWhite = g_WhiteTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vDissolve = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse *vMtrlObjTex + 0.3* vector(1.f - vMtrlWhite.r, 1.f - vMtrlWhite.r, 1.f - vMtrlWhite.r, 0.f) + 0.3*vector(1.f - vMtrlWhite.g, 1.f - vMtrlWhite.g, 1.f - vMtrlWhite.g, 0.f) + 0.3* vector(1.f - vMtrlWhite.b, 1.f - vMtrlWhite.b, 1.f - vMtrlWhite.b, 0.f);

	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
	//float Dist = distance(In.vWorldPos, g_PlayerPos)*0.01;
	//Out.vPlayerDist = vector(Dist, 0.f, 0.f, 1.f);
	//Out.vBlur = vector(0.f, 0.f, 0.f, 0.f);

	if (g_RenderTick >= vMtrlObjTex.r)
		discard;

	Out.vDiffuse.r = Out.vDiffuse.r + g_Color;
	Out.vDiffuse.g = Out.vDiffuse.g - g_Color;
	Out.vDiffuse.b = Out.vDiffuse.b - g_Color;

	if (vMtrlDiffuse.a < 0.1f)
		discard;

	return Out;
}

PS_OUT PS_MAIN_MODEL_DISSOLVE_PARTICLE_EFFECT(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	vector		vDissolve = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
	//float Dist = distance(In.vWorldPos, g_PlayerPos)*0.01;
	//Out.vPlayerDist = vector(Dist, 0.f, 0.f, 1.f);
	//Out.vBlur = Out.vDiffuse;

	if (g_RenderTick / 255.f - g_Length / 255.f >= vDissolve.r)
		discard;

	if (g_RenderTick / 255.f + g_Length / 255.f <= vDissolve.r)
		discard;

	if (false == g_Spectrum)
	{
		if (1.f == Out.vDiffuse.r)
			Out.vDiffuse.r = g_R / 255.f;
		if (1.f == Out.vDiffuse.g)
			Out.vDiffuse.g = g_G / 255.f;
		if (1.f == Out.vDiffuse.b)
			Out.vDiffuse.b = g_B / 255.f;
	}

	return Out;
}

PS_OUT PS_MAIN_MODEL_DISSOLVE_MELEE_EFFECT(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	vector		vDissolve = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
	//float Dist = distance(In.vWorldPos, g_PlayerPos)*0.01;
	//Out.vPlayerDist = vector(Dist, 0.f, 0.f, 1.f);
	//Out.vBlur = vector(0.f, 0.f, 0.f, 0.f);

	Out.vDiffuse.r = Out.vDiffuse.r*(g_R / 255.f);
	Out.vDiffuse.g = Out.vDiffuse.g*(g_G / 255.f);
	Out.vDiffuse.b = Out.vDiffuse.b*(g_B / 255.f);

	Out.vDiffuse.a = Out.vDiffuse.a*g_RenderTick / 255.f;

	return Out;
}

PS_OUT PS_MAIN_MODEL_COLOR_CONTROL_EFFECT(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
	//float Dist = distance(In.vWorldPos, g_PlayerPos)*0.01;
	//Out.vPlayerDist = vector(Dist, 0.f, 0.f, 1.f);
	//Out.vBlur = vector(0.f, 0.f, 0.f, 0.f);

	Out.vDiffuse.r = Out.vDiffuse.r*(g_R / 255.f);
	Out.vDiffuse.g = Out.vDiffuse.g*(g_G / 255.f);
	Out.vDiffuse.b = Out.vDiffuse.b*(g_B / 255.f);

	Out.vDiffuse.r = Out.vDiffuse.r*g_RenderTick / 255.f;
	Out.vDiffuse.g = Out.vDiffuse.g*g_RenderTick / 255.f;
	Out.vDiffuse.b = Out.vDiffuse.b*g_RenderTick / 255.f;

	if (Out.vDiffuse.r < 0.3f)
		discard;

	return Out;
}

PS_OUT PS_MAIN_MODEL_METEOR_EFFECT(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vDissolve = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
	//Out.vBlur = vector(0.f, 0.f, 0.f, 0.f);
	Out.vDiffuse.a = Out.vDiffuse.r;
	Out.vDiffuse.r = Out.vDiffuse.r + (1 - Out.vDiffuse.r)*(g_R / 255.f);
	Out.vDiffuse.g = Out.vDiffuse.g + (1 - Out.vDiffuse.g)*(g_G / 255.f);
	Out.vDiffuse.b = Out.vDiffuse.b + (1 - Out.vDiffuse.b)*(g_B / 255.f);
	
	if (g_RenderTick / 255.f >= vDissolve.r)
		discard;

	if (Out.vDiffuse.a == 0.f)
		discard;

	return Out;
}


PS_OUT PS_MAIN_MODEL_FALLING(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	vector		vDissolve = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vDissolve2 = g_DisolveTexture2.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
	//float Dist = distance(In.vWorldPos, g_PlayerPos)*0.01;
	//Out.vPlayerDist = vector(Dist, 0.f, 0.f, 1.f);
	//Out.vBlur = vector(0.f, 0.f, 0.f, 0.f);


	/*Out.vDiffuse.r = Out.vDiffuse.r*(g_R / 255.f);
	Out.vDiffuse.g = Out.vDiffuse.g*(g_G / 255.f);
	Out.vDiffuse.b = Out.vDiffuse.b*(g_B / 255.f);*/
	//Out.vDiffuse.a = Out.vDiffuse.a*(g_R / 255.f);

	if (g_RenderTick / 255.f >= vDissolve.r)
		discard;
	if (g_G / 255.f >= vDissolve2.r)
		discard;

	//Out.vBlur = Out.vDiffuse;

	return Out;
}

PS_OUT PS_MAIN_MODEL_DISOLVE_PRIMALSSCREAM(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	vector		vDissolve = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
	//float Dist = distance(In.vWorldPos, g_PlayerPos)*0.01;
	//Out.vPlayerDist = vector(Dist, 0.f, 0.f, 1.f);
	//Out.vBlur = vector(0.f, 0.f, 0.f, 0.f);



	Out.vDiffuse.a = Out.vDiffuse.a*(g_R / 255.f);

	if (g_RenderTick / 255.f >= vDissolve.r)
		discard;

	return Out;
}

PS_OUT PS_MAIN_MODEL_DISOLVE_TORNADO(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	vector		vDissolve = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vDissolve2 = g_DisolveTexture2.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse.rgb = vMtrlDiffuse.rgb;
	Out.vDiffuse.a = vDissolve2.r;
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);

	if (g_RenderTick / 255.f <= (Out.vDiffuse.r + Out.vDiffuse.g + Out.vDiffuse.b) / 3)
		discard;


	if (g_R / 255.f >= vDissolve.r)
		discard;


	Out.vDiffuse.a = Out.vDiffuse.a*g_Disolve / 255.f;

	if (0.4f >  vDissolve2.r)
		discard;

	return Out;
}

PS_OUT PS_MAIN_MODEL_DISOLVE_TREASURE_RAY(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	vector		vDissolve = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
	//float Dist = distance(In.vWorldPos, g_PlayerPos)*0.01;
	//Out.vPlayerDist = vector(Dist, 0.f, 0.f, 1.f);
	//Out.vBlur = vector(0.f, 0.f, 0.f, 0.f);

	Out.vDiffuse.a = Out.vDiffuse.a*g_RenderTick / 255.f;

	if (0.1f > Out.vDiffuse.a)
		discard;

	return Out;
}

PS_OUT PS_MAIN_MODEL_Tail_Trail(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vColorTex = g_ColorTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vDisolveTex = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
	//float Dist = distance(In.vWorldPos, g_PlayerPos)*0.01;
	//Out.vPlayerDist = vector(Dist, 0.f, 0.f, 1.f);
	//Out.vBlur = vector(0.f, 0.f, 0.f, 0.f);
	Out.vDiffuse = vMtrlDiffuse;

	Out.vDiffuse.rgb = vMtrlDiffuse.rgb * vColorTex.rgb;
	if (0.1f > vMtrlDiffuse.r)
		discard;

	if (vDisolveTex.r > g_RenderTick / 255.f)
		discard;

	return Out;
}

PS_OUT PS_MAIN_MODEL_FEAR_TAIL(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vDisolveTex = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
	//float Dist = distance(In.vWorldPos, g_PlayerPos)*0.01;
//	Out.vPlayerDist = vector(Dist, 0.f, 0.f, 1.f);
	//Out.vBlur = vector(0.f, 0.f, 0.f, 0.f);
	Out.vDiffuse = vMtrlDiffuse;

	if (0.6f > vDisolveTex.r)
		discard;

	if (0.9f < Out.vDiffuse.r)
		discard;

	if (vDisolveTex.r < g_RenderTick / 255.f)
		discard;

	return Out;
}

PS_OUT PS_MAIN_MODEL_WEAPON_TRAIL0(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vDisolveTex = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);

	float2		NewUV = In.vTexUV;
	NewUV.x += g_TrailMask;
	vector		vMaskTex = g_MaskTexture.Sample(DefaultSampler, NewUV);

	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);

	Out.vDiffuse = vMtrlDiffuse;

	if (136 / 255.f > vMaskTex.r)
	{
		vMaskTex.r = 0.f;
		vMaskTex.g = 0.f;
		vMaskTex.b = 0.f;
	}
	else
	{
		vMaskTex.r = 1.f;
		vMaskTex.g = 1.f;
		vMaskTex.b = 1.f;
	}

	Out.vDiffuse.r = vMtrlDiffuse.r* vMaskTex.r;
	Out.vDiffuse.g = vMtrlDiffuse.g* vMaskTex.g;
	Out.vDiffuse.b = vMtrlDiffuse.b* vMaskTex.b;

	if (vMtrlDiffuse.r < 136 / 255.f)
		discard;

	if (vDisolveTex.r > g_LimitLength / 255.f)
		discard;

	if (vDisolveTex.r < g_Length / 255.f)
		discard;

	if (Out.vDiffuse.r < g_RenderTick / 255.f)
		discard;

	return Out;
}

PS_OUT PS_MAIN_MODEL_PRIMALS_WAVE0(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vDisolveTex2 = g_DisolveTexture2.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);

	Out.vDiffuse.a = vDisolveTex2.r;
	Out.vDiffuse.a = Out.vDiffuse.a*g_RenderTick / 255.f;



	return Out;
}

PS_OUT PS_MAIN_MODEL_PRIMALS_DISTOTION(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vDisolveTex = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);
	Out.vDiffuse = vMtrlDiffuse;
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);

	Out.vDiffuse.a = vDisolveTex.r;

	if (g_RenderTick / 255.f < vMtrlDiffuse.r)
		discard;

	Out.vDiffuse.a = Out.vDiffuse.a*g_Disolve / 255.f;

	return Out;
}

PS_OUT PS_MAIN_MODEL_WATER_LINE(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	float2		NewUV = In.vTexUV;
	NewUV.x += g_Length;
	NewUV.y += g_Length;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, NewUV);

	Out.vDiffuse = vMtrlDiffuse;
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);

	if (0.9f > Out.vDiffuse.r)
		discard;

	Out.vDiffuse.a = Out.vDiffuse.a*g_Disolve / 255.f;

	return Out;
}

PS_OUT PS_MAIN_MODEL_MELEE_WEAPON(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);

	if (225 / 255.f == vMtrlDiffuse.r && 234 / 255.f == vMtrlDiffuse.g && 246 / 255.f == vMtrlDiffuse.b)
	{
		Out.vEmissive = vector(0.6f, 0.f, 0.f, 1.f);
		Out.vEmissiveGlow = vector(1.f, 1.f, 1.f, 1.f);
	}

	return Out;
}

PS_OUT PS_MAIN_MODEL_PORTAL(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;


	if (0 == g_Index)
	{
		vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

		Out.vDiffuse = vMtrlDiffuse;
		Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
		Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
	}
	else
	{
		vector		vMtrlDiffuse = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);
		vector		vDisolve = g_DisolveTexture2.Sample(DefaultSampler, In.vTexUV);

		Out.vDiffuse = vMtrlDiffuse;
		Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
		Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);

		if (160 / 255.f<vMtrlDiffuse.r && 150 / 255.f>vMtrlDiffuse.g)
		{
			if (1 == g_Index)
			{
				Out.vEmissive = vector(73 / 255.f, 38 / 255.f, 225 / 255.f, 1.f);
				Out.vEmissiveGlow = vector(1.f, 1.f, 1.f, 1.f);
			}
			if (2 == g_Index)
			{
				Out.vEmissive = vector(22 / 255.f, 241 / 255.f, 29 / 255.f, 1.f);
				Out.vEmissiveGlow = vector(1.f, 1.f, 1.f, 1.f);
			}
			if (3 == g_Index)
			{
				Out.vEmissive = vector(255 / 255.f, 0 / 255.f, 0 / 255.f, 1.f);
				Out.vEmissiveGlow = vector(1.f, 1.f, 1.f, 1.f);
			}
			if (g_RenderTick / 255.f < vDisolve.r)
				discard;
		}
	}
	return Out;
}

PS_OUT PS_MAIN_MODEL_PORTAL_DISTOTION(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);

	Out.vDiffuse.a = vMtrlDiffuse.r;

	return Out;
}

PS_OUT PS_MAIN_MODEL_PORTAL_MESH_EFFECT(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	float2		NewUV = In.vTexUV;
	NewUV.x -= g_Frame*3.f;
	NewUV.y -= g_Frame;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, NewUV);
	vector		vDisolveTex = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);

	//vDisolveTex.a *= (1-g_RenderTick/255.f);

	Out.vDiffuse = vMtrlDiffuse;
	Out.vDiffuse.a = vMtrlDiffuse.r*(1 - g_RenderTick / 255.f);

	if (0.2f > Out.vDiffuse.a)
		discard;
	else
		Out.vDiffuse.rgb += 0.4f;

	if (g_RenderTick / 255.f > vDisolveTex.r)
		discard;


	return Out;
}

PS_OUT PS_MAIN_MODEL_TEX_FOUNT(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vMtrlObjTex = g_ObjectTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vMtrlWhite = g_WhiteTexture.Sample(DefaultSampler, In.vTexUV);

	float3 DiffuseCol = float3(vMtrlDiffuse.x, vMtrlDiffuse.y, vMtrlDiffuse.z);


	Out.vDiffuse = vMtrlDiffuse *vMtrlObjTex + 0.3* vector(1.f - vMtrlWhite.r, 1.f - vMtrlWhite.r, 1.f - vMtrlWhite.r, 0.f) + 0.3*vector(1.f - vMtrlWhite.g, 1.f - vMtrlWhite.g, 1.f - vMtrlWhite.g, 0.f) + 0.3* vector(1.f - vMtrlWhite.b, 1.f - vMtrlWhite.b, 1.f - vMtrlWhite.b, 0.f);

	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);

	if ((DiffuseCol.x == 1.f && DiffuseCol.y == 0.2f && DiffuseCol.z == 0.2f) || (DiffuseCol.x == 0.2f && DiffuseCol.y == 0.2f && DiffuseCol.z == 1.0f)) {
		if (g_LightDead) {
			Out.vDiffuse = vector(0.2f, 0.2f, 0.2f, 1.f);
			Out.vEmissive = vector(0.f,0.f,0.f,0.f);
			Out.vEmissiveGlow = vector(0.f, 0.f, 0.f, 0.f);
		}
		else {
			Out.vEmissive = vMtrlDiffuse;
			Out.vEmissiveGlow = vMtrlDiffuse * g_fPercent;
		}
	}


	if (vMtrlDiffuse.a < 0.1f)
		discard;

	return Out;
}

PS_OUT PS_MAIN_MODEL_TEX_D(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vMtrlObjTex = g_ObjectTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vMtrlWhite = g_WhiteTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse *vMtrlObjTex + 0.3* vector(1.f - vMtrlWhite.r, 1.f - vMtrlWhite.r, 1.f - vMtrlWhite.r, 0.f) + 0.3*vector(1.f - vMtrlWhite.g, 1.f - vMtrlWhite.g, 1.f - vMtrlWhite.g, 0.f) + 0.3* vector(1.f - vMtrlWhite.b, 1.f - vMtrlWhite.b, 1.f - vMtrlWhite.b, 0.f);



	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
	//float Dist = distance(In.vWorldPos, g_PlayerPos)*0.01;
	//Out.vPlayerDist = vector(Dist, 0.f, 0.f, 1.f);
	//Out.vBlur = vector(0.f, 0.f, 0.f, 0.f);

	if (g_RenderTick / 255.f >= vMtrlObjTex.r)
		discard;

	if (vMtrlDiffuse.a < 0.1f)
		discard;

	return Out;
}

PS_OUT PS_PORTAL_COLOR(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vMtrlObjTex = g_ObjectTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vMtrlWhite = g_WhiteTexture.Sample(DefaultSampler, In.vTexUV);

	vector      SetColor = float4(g_PortalColor.x, g_PortalColor.y, g_PortalColor.z, 1.f);

	Out.vEmissive = (1 - g_ColorTime) * SetColor;
	Out.vEmissiveGlow = (1 - g_ColorTime) * SetColor * 0.5f;
	Out.vDiffuse = (g_ColorTime * vMtrlDiffuse) + ((1 - g_ColorTime) * SetColor);

	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);

	if (vMtrlDiffuse.a < 0.1f)
		discard;

	return Out;
}

PS_OUT PS_PORTALTEXTURE_COLOR(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vMtrlObjTex = g_PortalTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vMtrlWhite = g_WhiteTexture.Sample(DefaultSampler, In.vTexUV);

	vector      SetColor = float4(g_PortalColor.x, g_PortalColor.y, g_PortalColor.z, 1.f);

	Out.vDiffuse = vMtrlObjTex;

	if (Out.vDiffuse.r == 1.f && Out.vDiffuse.g == 0.f && Out.vDiffuse.b == 0.f) {
		Out.vEmissive = (1 - g_ColorTime) * SetColor;
		Out.vEmissiveGlow = (1 - g_ColorTime) * SetColor * 0.5f;
		Out.vDiffuse = (g_ColorTime * vMtrlObjTex) + ((1 - g_ColorTime) * SetColor);
	}

	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);


	if (vMtrlDiffuse.a < 0.1f)
		discard;

	return Out;
}

PS_OUT PS_REGRET_BLADE(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	float2		NewUV = In.vTexUV;
	NewUV.y -= g_Frame;
	vector		vDisolve = g_DisolveTexture.Sample(DefaultSampler, NewUV);

	Out.vDiffuse = vMtrlDiffuse;
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);

	Out.vDiffuse.a = vMtrlDiffuse.r;

	if (0.6f > vMtrlDiffuse.r)
	{
		Out.vDiffuse.a = vMtrlDiffuse.r*(vDisolve.r+0.5f);
	}
	Out.vDiffuse.r *= g_fColor3.r / 255.f;
	Out.vDiffuse.g *= g_fColor3.g / 255.f;
	Out.vDiffuse.b *= g_fColor3.b / 255.f;

	if (0.3f > Out.vDiffuse.a)
		discard;


	Out.vEmissive = Out.vDiffuse;
	Out.vEmissiveGlow = Out.vEmissive;

	return Out;
}
PS_OUT PS_REGRET_BULLET_TRAIL(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	float2		NewUV = In.vTexUV;
	NewUV.y -= g_Frame;
	vector		vDisolve = g_DisolveTexture.Sample(DefaultSampler, NewUV);

	Out.vDiffuse = vMtrlDiffuse;
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);

	Out.vDiffuse.a = vMtrlDiffuse.r*vDisolve.r;

	Out.vDiffuse.r *= 194 / 255.f;
	Out.vDiffuse.g *= 204 / 255.f;
	Out.vDiffuse.b *= 35 / 255.f;

	if (0.1f > Out.vDiffuse.a)
		discard;


	Out.vEmissive = Out.vDiffuse;
	Out.vEmissiveGlow = Out.vEmissive;

	return Out;
}
PS_OUT PS_REGRET_BULLET(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);

	if (108 / 255.f == Out.vDiffuse.r)
	{
		Out.vEmissive = vector(Out.vDiffuse.r, Out.vDiffuse.g, Out.vDiffuse.b, 0.5f);
		Out.vEmissiveGlow = Out.vEmissive;
	}


	return Out;
}

PS_OUT PS_MAIN_MODEL_MELEE_WEAPON_DAGGER(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);

	if (225 / 255.f == vMtrlDiffuse.r && 234 / 255.f == vMtrlDiffuse.g && 246 / 255.f == vMtrlDiffuse.b)
	{
		Out.vEmissive = vector(170 / 255.f, 211 / 255.f, 211 / 255.f, 1.f);
		Out.vEmissiveGlow = vector(1.f, 1.f, 1.f, 1.f);
	}

	return Out;
}

PS_OUT PS_MAIN_MODEL_WAVE_STONE(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vDisolve = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);

	Out.vDiffuse = vMtrlDiffuse;



	if (g_RenderTick / 255.f > vDisolve.r)
		discard;

	return Out;
}

PS_OUT PS_RESENTMENT_BLADE(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	float2		NewUV = In.vTexUV;
	NewUV.y -= g_Frame;
	vector		vDisolve = g_DisolveTexture.Sample(DefaultSampler, NewUV);

	Out.vDiffuse = vMtrlDiffuse;
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);

	Out.vDiffuse.a = vMtrlDiffuse.r;

	if (0.7f > vMtrlDiffuse.r)
	{
		Out.vDiffuse.a = (vMtrlDiffuse.r + 0.2f)*(vDisolve.r + 0.5f);
	}
	Out.vDiffuse.g = Out.vDiffuse.r;

	if (Out.vDiffuse.g < 122.f)
		Out.vDiffuse.r = Out.vDiffuse.g*2.f;
	else
		Out.vDiffuse.r = 255.f;

	if (Out.vDiffuse.g > 0.8f)
		Out.vDiffuse.b = Out.vDiffuse.g / 2.f;
	else
		Out.vDiffuse.b = (Out.vDiffuse.r - Out.vDiffuse.g) / 2.f;

	if (0.4f > Out.vDiffuse.a)
		discard;


	Out.vEmissive = Out.vDiffuse;
	Out.vEmissiveGlow = Out.vEmissive;

	return Out;
}

PS_OUT PS_RESENTMENT_LAVA_EXPLOSION(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);

	if (Out.vDiffuse.g < 122 / 255.f)
	{
		Out.vDiffuse.r *= 1.3f;
		Out.vDiffuse.g *= 0.5f;
	}



	Out.vDiffuse.b = Out.vDiffuse.g *0.5f;

	/*Out.vEmissive = vector(Out.vDiffuse.r, Out.vDiffuse.g, Out.vDiffuse.b, 0.7f);
	Out.vEmissiveGlow = Out.vEmissive;*/

	return Out;
}


technique11 DefaultTechnique
{
	pass Model //0
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL();
	}

	pass Model_Socket //1
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL_SOCKET();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL();
	}

	pass ModelTex //2
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_TEX();
	}

	pass GameStart //3
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_GAMESTART();
	}

	pass Dissolve //4
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_DISSOLVE();
	}

	pass ModelTex_Blur //5
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_DISSOLVE();
	}

	pass ModelPuzzle//6(ÆÛÁñ)
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_PUZZLE();
	}

	pass ModelMine//7(Áö·ÚÃ£±â)
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_MINE();
	}

	pass Model7x4 //8
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL_7x4();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_7x4();
	}

	pass Model6x12 //9
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL_6x12();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_6x12();
	}

	pass ModelTex_Land //10
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_LAND();
	}

	pass ModelTex_Dest //11
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL_DEST();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_TEX();
	}
	pass ModelRock//12
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL_DEST();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_ROCK();
	}

	pass Model_MeshParticle //13
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_DISSOLVE_PARTICLE_EFFECT();
	}

	pass Model_MeleeEffect //14
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_DISSOLVE_MELEE_EFFECT();
	}

	pass Model_MeteorEffect1 //15
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_COLOR_CONTROL_EFFECT();
	}

	pass Model_MeteorEffect2//16
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_METEOR_EFFECT();
	}
	pass Dissolve_Falling //17
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_FALLING();
	}

	pass Model_Blend //18
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL();
	}
	pass Dissolve_PrimalsScream //19
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_DISOLVE_PRIMALSSCREAM();
	}

	pass Dissolve_Tornado //20
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_DISOLVE_TORNADO();
	}

	pass Dissolve_Treasure_Ray//21
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_DISOLVE_TREASURE_RAY();
	}

	pass ModelTex2 //22
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_TEX2();
	}
	pass Model_MeshPuzzleWater //23
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_DISSOLVE_PARTICLE_EFFECT();
	}

	pass Model_Env //24
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL_ENVMAP();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_ENV();
	}

	pass ModelTex_WhiteEmissive //25
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_TEX_WEM();
	}
	pass Model_Tail_Trail //26
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_Tail_Trail();
	}
	pass Model_Fear_Tail//27
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_FEAR_TAIL();
	}

	pass Model_Weapon_Trail0//28
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_WEAPON_TRAIL0();
	}

	pass Model_Green //29
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_GREEN();
	}

	pass ModelTexEM //30
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_TEX_EM();
	}
	pass Model_Primals_Wave0//31
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_PRIMALS_WAVE0();
	}

	pass Model_Primals_Distotion//32
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_PRIMALS_DISTOTION();
	}

	pass Model_Water_Line0//33
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_WATER_LINE();
	}

	pass Model_MeleeSocket //34
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL_SOCKET();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_MELEE_WEAPON();
	}

	pass Model_Portal //35
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_PORTAL();
	}

	pass Model_Portal_Distotion //36
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_PORTAL_DISTOTION();
	}

	pass Model_Portal_Mesh_Effect //37
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_PORTAL_MESH_EFFECT();
	}

	pass ModelTexFount //38
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_TEX_FOUNT();
	}

	pass LavaCenter //39
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_LAVA();
	}

	pass LavaCenter2 //40
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_LAVA2();
	}

	pass ModelTex_D //41
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_TEX_D();
	}

	pass PortalColor //42
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_PORTAL_COLOR();
	}

	pass WatchWorld // 43
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_WATCHWORLD();
	}

	pass PortalTexColor //44
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_PORTALTEXTURE_COLOR();
	}

	pass ModelSsd //45
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_SSD();
	}

	pass WatchWorld2 // 46
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_WATCHWORLD2();
	}

	pass ModelTexEM_Disolove //47
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_TEX_EM_D();
	}

	pass Bubble //48
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_BUBBLE();
	}

	pass Regret_Blade //49
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_REGRET_BLADE();
	}

	pass Regret_Bullet_Trail //50
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_REGRET_BULLET_TRAIL();
	}

	pass Regret_Bullet //51
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_REGRET_BULLET();
	}

	pass ModelSsd2 //52
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_SSD2();
	}

	pass Model_MeleeSocket_Dagger //53
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL_SOCKET();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_MELEE_WEAPON_DAGGER();
	}

	pass Model_Wave_Stone //54
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_WAVE_STONE();
	}

	pass Resentment_Blade //55
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_RESENTMENT_BLADE();
	}

	pass ScreenImage //56
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_SCREENIMAGE();
	}

	pass Resentment_Lava_Explosion //57
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_RESENTMENT_LAVA_EXPLOSION();
	}

}


