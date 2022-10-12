
#include "Shader_Defines.hpp"
float	g_UVMove;
cbuffer Percent
{
	float g_fPercent;
}

cbuffer	TimeDelta
{
	float g_TimeDelta;
	float g_TimeDelta1;
	float g_TimeDelta2;
}

cbuffer Color
{
	float3 g_fColor;
}

cbuffer Matrices
{
	float4x4		g_WorldMatrix, g_ViewMatrix, g_ProjMatrix;
}

struct VS_IN
{
	float3		vPosition : POSITION;
	float2		vTexUV : TEXCOORD0;
};

struct VS_OUT
{
	float4		vPosition : SV_POSITION;
	float2		vTexUV : TEXCOORD;
	float4		vLocalPos : TEXCOORD1;
};

texture2D			g_Texture;
texture2D			g_HealthMaskTexture;
texture2D			g_DepthTexture;

texture2D			g_ShaderTexture;

texture2D			g_MaskTexture;
texture2D			g_OutLineTexture;

texture2D			g_DissolveTexture;
float				g_iCnt;

uint				g_iFrame;
float				g_fFrame;


sampler DefaultSampler = sampler_state {
	filter = min_mag_mip_linear;
	AddressU = wrap;
	AddressV = wrap;
};


VS_OUT VS_MAIN(VS_IN In)
{
	VS_OUT		Out;

	float4		vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;
	Out.vTexUV = In.vTexUV;
	Out.vLocalPos = vector(In.vPosition, 1.f);

	return Out;
}


struct VS_OUT_SOFT_EFFECT
{
	float4		vPosition : SV_POSITION;
	float2		vTexUV : TEXCOORD;
	float4		vProjPos : TEXCOORD1;
};

VS_OUT_SOFT_EFFECT VS_MAIN_SOFT_EFFECT(VS_IN In)
{
	VS_OUT_SOFT_EFFECT		Out;

	float4		vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;
	Out.vTexUV = In.vTexUV;
	Out.vProjPos = vPosition;

	return Out;
}

VS_OUT_SOFT_EFFECT VS_MAIN_SOFT_EFFECT4X4(VS_IN In)
{
	VS_OUT_SOFT_EFFECT		Out;

	float4		vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;
	Out.vProjPos = vPosition;

	Out.vTexUV.x = In.vTexUV.x / 4.f + 1 / 4.f*fmod(g_iFrame, 4);
	Out.vTexUV.y = In.vTexUV.y / 4.f + 1 / 4.f*(g_iFrame / 4);

	return Out;
}

VS_OUT_SOFT_EFFECT VS_MAIN_SOFT_EFFECT8X4(VS_IN In)
{
	VS_OUT_SOFT_EFFECT		Out;

	float4		vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;
	Out.vProjPos = vPosition;

	Out.vTexUV.x = In.vTexUV.x / 8.f + 1 / 8.f*fmod(g_iFrame, 8);
	Out.vTexUV.y = In.vTexUV.y / 4.f + 1 / 4.f*(g_iFrame / 4);

	return Out;
}

VS_OUT_SOFT_EFFECT VS_MAIN_SOFT_EFFECT4X2(VS_IN In)
{
	VS_OUT_SOFT_EFFECT		Out;

	float4		vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;
	Out.vProjPos = vPosition;

	Out.vTexUV.x = In.vTexUV.x / 4.f + 1 / 4.f*fmod(g_iFrame, 4);
	Out.vTexUV.y = In.vTexUV.y / 2.f + 1 / 2.f*(g_iFrame / 2);

	return Out;
}

VS_OUT_SOFT_EFFECT VS_MAIN_SOFT_EFFECT4X1(VS_IN In)
{
	VS_OUT_SOFT_EFFECT		Out;

	float4		vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;
	Out.vProjPos = vPosition;

	Out.vTexUV.x = In.vTexUV.x / 4.f + 1 / 4.f*fmod(g_iFrame, 4);
	Out.vTexUV.y = In.vTexUV.y / 1.f + 1 / 1.f*(g_iFrame / 1);

	return Out;
}


VS_OUT_SOFT_EFFECT VS_MAIN_SOFT_EFFECT4X3(VS_IN In)
{
	VS_OUT_SOFT_EFFECT		Out;

	float4		vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;
	Out.vProjPos = vPosition;

	Out.vTexUV.x = In.vTexUV.x / 4.f + 1 / 4.f*fmod(g_iFrame, 4);
	Out.vTexUV.y = In.vTexUV.y / 3.f + 1 / 3.f*(g_iFrame / 3);

	return Out;
}

VS_OUT_SOFT_EFFECT VS_MAIN_SOFT_EFFECT7X4(VS_IN In)
{
	VS_OUT_SOFT_EFFECT		Out;

	float4		vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;
	Out.vProjPos = vPosition;

	Out.vTexUV.x = In.vTexUV.x / 7.f + 1 / 7.f*fmod(g_iFrame, 7);
	Out.vTexUV.y = In.vTexUV.y / 4.f + 1 / 4.f*(g_iFrame / 4);

	return Out;
}


VS_OUT_SOFT_EFFECT VS_MAIN_SOFT_EFFECT_UI7x4(VS_IN In)
{
	VS_OUT_SOFT_EFFECT		Out;

	float4		vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;
	Out.vProjPos = vPosition;

	Out.vTexUV.x = In.vTexUV.x / 7.f + 1 / 7.f*fmod(g_iFrame, 7);
	Out.vTexUV.y = In.vTexUV.y / 4.f + 1 / 4.f*(g_iFrame / 4);

	return Out;
}

VS_OUT_SOFT_EFFECT VS_MAIN_SOFT_EFFECT8X8(VS_IN In)
{
	VS_OUT_SOFT_EFFECT		Out;

	float4		vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;
	Out.vProjPos = vPosition;

	Out.vTexUV.x = In.vTexUV.x / 8.f + 1 / 8.f*fmod(g_iFrame, 8);
	Out.vTexUV.y = In.vTexUV.y / 8.f + 1 / 8.f*(g_iFrame / 8);


	return Out;
}

VS_OUT_SOFT_EFFECT VS_MAIN_SOFT_EFFECT6X6(VS_IN In)
{
	VS_OUT_SOFT_EFFECT		Out;

	float4		vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;
	Out.vProjPos = vPosition;

	Out.vTexUV.x = In.vTexUV.x / 6.f + 1 / 6.f*fmod(g_iFrame, 6);
	Out.vTexUV.y = In.vTexUV.y / 6.f + 1 / 6.f*(g_iFrame / 6);

	return Out;
}



struct PS_IN
{
	vector			vPosition : SV_POSITION;
	float2			vTexUV : TEXCOORD0;
	float4			vLocalPos : TEXCOORD1;
};

struct PS_OUT
{
	vector			vColor : SV_TARGET0;
	vector			vBlur : SV_TARGET1;
};

PS_OUT PS_MAIN(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);


	return Out;
}

PS_OUT PS_MAIN_STATIC(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vColor.a < 0.2f) {
		discard;
	}

	return Out;
}


float			g_BeamMove;

PS_OUT PS_MAIN_BEAM(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	//In.vTexUV.x += g_BeamMove;
	In.vTexUV.y += g_BeamMove;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	return Out;
}


PS_OUT PS_MAIN_GLOW_BLUR(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	Out.vBlur = Out.vColor;

	return Out;
}

PS_OUT PS_MAIN3(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vColor.a < 0.2f) {
		discard;
	}

	return Out;
}

PS_OUT PS_UI(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vColor.a == 0.f)
		discard;

	return Out;
}

PS_OUT PS_MYCOLOR(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	Out.vColor.r = g_fColor.r;
	Out.vColor.g = g_fColor.y;
	Out.vColor.b = g_fColor.z;

	if (Out.vColor.a == 0.f)
		discard;


	return Out;
}

PS_OUT PS_UI_PERCENT(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);


	if (g_fPercent <= In.vTexUV.x)
		discard;

	return Out;
}

PS_OUT PS_FADE(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vColor.a == 0.f)
		discard;

	Out.vColor.a = g_fPercent;

	return Out;
}

PS_OUT PS_ABILITYEFFECT(PS_IN In)
{
	PS_OUT			Out;

	float4 v = g_Texture.Sample(DefaultSampler, In.vTexUV);
	float4 Color = float4((101.f / 255.f), (219.f / 255.f), (255.f / 255.f), 1.f);
	float4 Color1 = float4(0.f, 1.f, 0.f, 1.f);

	//Out.vColor = Color1 * ((v.x * g_TimeDelta)/3);
	Out.vColor = Color * (v.y * g_TimeDelta1);
	Out.vColor += Color * (v.z * g_TimeDelta2);
	//Out.vColor.a = 0.5f;



	//if (Out.vColor.r <= 0.3f && Out.vColor.g <= 0.3f && Out.vColor.b <= 0.3f)
	//	discard;



	return Out;
}

PS_OUT PS_MOVETEXTURE(PS_IN In)
{
	PS_OUT			Out;

	In.vTexUV.x -= g_TimeDelta * 0.01;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);
	float Avg = (Out.vColor.x + Out.vColor.y + Out.vColor.z) / 3.f;

	Out.vColor.r = Avg;
	Out.vColor.g = 0.f;
	Out.vColor.b = 0.f;

	//Out.vColor += g_HealthMaskTexture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vColor.a == 0.f)
		discard;



	return Out;
}

PS_OUT PS_MOVETEXTURE_OWNCOLOR(PS_IN In)
{
	PS_OUT			Out;

	In.vTexUV.x -= g_TimeDelta * 0.05;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vColor.a == 0.f)
		discard;

	return Out;
}

PS_OUT PS_CIRCLEITEM(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);
	vector Masking = g_MaskTexture.Sample(DefaultSampler, In.vTexUV);
	vector OutLine = g_OutLineTexture.Sample(DefaultSampler, In.vTexUV);

	if (Masking.a == 0.f)
		discard;

	if (OutLine.a != 0.f)
		Out.vColor += OutLine;

	return Out;
}

struct PS_IN_SOFT_EFFECT
{
	float4		vPosition : SV_POSITION;
	float2		vTexUV : TEXCOORD;
	float4		vProjPos : TEXCOORD1;
};


PS_OUT PS_MAIN_SOFT_EFFECT(PS_IN_SOFT_EFFECT In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	float		fViewZ = In.vProjPos.w;

	float2		vUV;

	vUV.x = (In.vProjPos.x / In.vProjPos.w) * 0.5f + 0.5f;
	vUV.y = (In.vProjPos.y / In.vProjPos.w) * -0.5f + 0.5f;

	float4		vDepthDesc = g_DepthTexture.Sample(DefaultSampler, vUV);
	float		fTargetViewZ = vDepthDesc.y * 300.f;

	Out.vColor.a = max(min(fTargetViewZ - fViewZ, Out.vColor.a), 0.f);


	return Out;
}
PS_OUT PS_MAIN_SOFT_EFFECT_CHOI(PS_IN_SOFT_EFFECT In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	float		fViewZ = In.vProjPos.w;

	float2		vUV;

	vUV.x = (In.vProjPos.x / In.vProjPos.w) * 0.5f + 0.5f;
	vUV.y = (In.vProjPos.y / In.vProjPos.w) * -0.5f + 0.5f;

	float4		vDepthDesc = g_DepthTexture.Sample(DefaultSampler, vUV);
	float		fTargetViewZ = vDepthDesc.y * 300.f;

	Out.vColor.a = max(min(fTargetViewZ - fViewZ, Out.vColor.a), 0.f);

	if (Out.vColor.a < 0.1f)
		discard;


	return Out;
}

PS_OUT PS_MAIN_SOFT_EFFECT_GLOW(PS_IN_SOFT_EFFECT In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	float		fViewZ = In.vProjPos.w;

	float2		vUV;

	vUV.x = (In.vProjPos.x / In.vProjPos.w) * 0.5f + 0.5f;
	vUV.y = (In.vProjPos.y / In.vProjPos.w) * -0.5f + 0.5f;

	float4		vDepthDesc = g_DepthTexture.Sample(DefaultSampler, vUV);
	float		fTargetViewZ = vDepthDesc.y * 300.f;

	Out.vColor.a = max(min(fTargetViewZ - fViewZ, Out.vColor.a), 0.f);
	Out.vBlur = Out.vColor;

	return Out;
}
VS_OUT_SOFT_EFFECT VS_MAIN_SOFT_EFFECT6X3(VS_IN In)
{
	VS_OUT_SOFT_EFFECT		Out;

	float4		vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;
	Out.vProjPos = vPosition;

	Out.vTexUV.x = In.vTexUV.x / 6.f + 1 / 6.f*fmod(g_iFrame, 6);
	Out.vTexUV.y = In.vTexUV.y / 3.f + 1 / 3.f*(g_iFrame / 3);



	return Out;
}

PS_OUT PS_MAIN_SOFT_EFFECT2(PS_IN_SOFT_EFFECT In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	float		fViewZ = In.vProjPos.w;

	float2		vUV;

	vUV.x = (In.vProjPos.x / In.vProjPos.w) * 0.5f + 0.5f;
	vUV.y = (In.vProjPos.y / In.vProjPos.w) * -0.5f + 0.5f;

	float4		vDepthDesc = g_DepthTexture.Sample(DefaultSampler, vUV);
	float		fTargetViewZ = vDepthDesc.y * 300.f;

	Out.vColor.a = max(min(fTargetViewZ - fViewZ, Out.vColor.a), 0.f);

	if (Out.vColor.a <= 0.3f)
		discard;

	return Out;
}


PS_OUT PS_MAIN_SOFT_EFFECT3(PS_IN_SOFT_EFFECT In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	float		fViewZ = In.vProjPos.w;

	float2		vUV;

	vUV.x = (In.vProjPos.x / In.vProjPos.w) * 0.5f + 0.5f;
	vUV.y = (In.vProjPos.y / In.vProjPos.w) * -0.5f + 0.5f;

	float4		vDepthDesc = g_DepthTexture.Sample(DefaultSampler, vUV);
	float		fTargetViewZ = vDepthDesc.y * 300.f;

	Out.vColor.a = max(min(fTargetViewZ - fViewZ, Out.vColor.a), 0.f);
	Out.vBlur = Out.vColor;

	if (Out.vColor.a == 0.f)
		discard;

	return Out;
}


PS_OUT PS_MAIN2(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);


	return Out;
}

PS_OUT PS_Dissolve(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);
	vector Dissolve = g_DissolveTexture.Sample(DefaultSampler, In.vTexUV);

	if (Dissolve.r > g_iCnt / 255)
		discard;

	return Out;
}

PS_OUT PS_MAIN_Alpha(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vColor.a <= 0.2f)
		discard;
	else
		Out.vColor.a = g_fPercent;

	return Out;
}

PS_OUT PS_MAIN_Alpha22(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	Out.vColor.a = g_fPercent;

	return Out;
}

PS_OUT PS_UI_POS(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vColor.a <= 0.2f)
		discard;
	else
		Out.vColor.a = g_fPercent;


	if (In.vPosition.y < 105.f || In.vPosition.y > 685.f)
		discard;

	return Out;
}

PS_OUT PS_UI_POS_NonAlpha(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (In.vPosition.y < 105.f || In.vPosition.y > 685.f)
		discard;

	return Out;
}

PS_OUT PS_UI_POS_SKETCH(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (In.vPosition.y < 165.f || In.vPosition.y > 650.f)
		discard;

	return Out;
}

PS_OUT PS_UI_POS_SKETCH2(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (In.vPosition.y > 245.f)
		discard;

	return Out;
}

float		g_CloudMove;

PS_OUT PS_UI_XPOS_CUT(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	In.vTexUV.x += g_CloudMove;


	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	return Out;
}



PS_OUT PS_UVMOVE(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	In.vTexUV.y += g_UVMove;

	g_Texture.Sample(DefaultSampler, In.vTexUV);

	return Out;
}

PS_OUT PS_Dissolve2(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);
	vector Dissolve = g_DissolveTexture.Sample(DefaultSampler, In.vTexUV);

	if (Dissolve.r < g_iCnt / 255)
		discard;

	return Out;
}

float			g_MoveUV2;


PS_OUT PS_Dissolve_Arrow(PS_IN In)
{
	PS_OUT			Out;

	float fY = In.vTexUV.y;

	In.vTexUV.y -= g_MoveUV2;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	vector Color = g_Texture.Sample(DefaultSampler, In.vTexUV);

	Out.vColor.a = saturate(Out.vColor.x - 0.2);

	if (Out.vColor.a < 0.1f)
		discard;

	if (Out.vColor.a > fY)
		Out.vColor.a = fY;

	return Out;
}

float		g_Pressing_Arrow;

PS_OUT PS_Pressing_Arrow(PS_IN In) // 활쏠때 밑에 나오는 이펙트
{
	PS_OUT			Out;

	//In.vTexUV.y = g_Pressing_Arrow;

	if (In.vTexUV.y < g_Pressing_Arrow)
		discard;


	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vColor.a <= 0.1f)
		discard;


	return Out;
}


PS_OUT PS_MAIN_TEST_MOVEUV(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	In.vTexUV.y += g_MoveUV2;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);


	return Out;
}

PS_OUT PS_MAIN_MOVEUV_SHADOW_BEAM(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);
	vector Dissolve = g_DissolveTexture.Sample(DefaultSampler, In.vTexUV);

	In.vTexUV.y += g_MoveUV2;

	if (Dissolve.r > g_iCnt / 255)
		discard;

	//Out.vBlur = Out.vColor;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);


	return Out;
}


//PS_OUT PS_MAIN(PS_IN In) // 글로우 &블러
//{
//	PS_OUT			Out;
//
//	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);
//
//	if (Out.vColor.a == 0.f)
//		discard;
//
//	Out.vBlur = Out.vColor;
//
//	return Out;
//}
PS_OUT PS_MAIN_SOFT_EFFECT_BOMB(PS_IN_SOFT_EFFECT In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	float		fViewZ = In.vProjPos.w;

	float2		vUV;

	vUV.x = (In.vProjPos.x / In.vProjPos.w) * 0.5f + 0.5f;
	vUV.y = (In.vProjPos.y / In.vProjPos.w) * -0.5f + 0.5f;

	float4		vDepthDesc = g_DepthTexture.Sample(DefaultSampler, vUV);
	float		fTargetViewZ = vDepthDesc.y * 300.f;

	Out.vColor.a = max(min(fTargetViewZ - fViewZ, Out.vColor.a), 0.f);

	if (Out.vColor.a < 0.1f)
		discard;

	return Out;
}

PS_OUT PS_MAIN_FLOOR_EFFECT(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vColor.a <= 0.2f)
		discard;

	Out.vColor.a = g_fPercent;

	return Out;
}

PS_OUT PS_MAIN_YS2(PS_IN In)
{
	PS_OUT			Out;
	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);
	vector Color = g_Texture.Sample(DefaultSampler, In.vTexUV);
	Out.vColor.b = Color.r;

	if (Out.vColor.a < 0.1f)
		discard;

	return Out;
}

PS_OUT PS_MAIN_YS3(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);
	vector Color = g_Texture.Sample(DefaultSampler, In.vTexUV);
	Out.vColor.r = Color.b;
	Out.vColor.b = Color.r;

	if (Out.vColor.a < 0.1f)
		discard;

	return Out;
}


technique11 DefaultTechnique
{
	/* Pass를 나누는 기준 == 그릴려고하는 리소스에게 어떤 셰이더 세트 효과를 줄것인지?! */

	/* 명암 + 그림자 + 노멀 */
	pass DefaultRendering // 0
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN();
	}

	pass SoftEffect // 1
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_SOFT_EFFECT();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_SOFT_EFFECT();
	}

	pass UIRendering // 2
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_UI();
	}

	pass UIPercentRendering // 3
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_UI_PERCENT();
	}

	pass FadeRendering // 4
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_FADE();
	}

	pass DefaultAlphaRendering // 5
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN();
	}

	pass MyColorRendering // 6
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MYCOLOR();
	}

	pass MoveingTextureRendering // 7
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MOVETEXTURE();
	}

	pass OwnColorMovingTextureRendering // 8
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MOVETEXTURE_OWNCOLOR();
	}

	pass AbiityEffectRenering // 9
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_ABILITYEFFECT();
	}

	pass DefaultRendering_NotCull //10
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN();
	}

	pass CircleItem //11
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_CIRCLEITEM();
	}
	pass Che_Alpha //12
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_Alpha();
	}

	pass Che_Alpha2 //13
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_UI_POS();
	}
	pass Che_Alpha3 //14
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_UI_POS_NonAlpha();
	}


	pass Che_Alpha5 // 15
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN2();
	}

	pass Che_Dissolve // 16
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_Dissolve();
	}

	pass Che_Alpha6 // 17
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_UVMOVE();
	}

	pass Che_XPOS // 18
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_UI_XPOS_CUT();
	}


	pass Che_Sketch // 19
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_UI_POS_SKETCH();
	}

	pass Che_Sketch2 //20
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_UI_POS_SKETCH2();
	}

	pass Che_Sketch3  //21
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_Dissolve2();
	}

	pass Cut7x4 //22
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN_SOFT_EFFECT7X4();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_SOFT_EFFECT();
	}


	pass Move_Test //23
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_TEST_MOVEUV();
	}

	pass Arrow_Alpha //24
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_Dissolve_Arrow();
	}

	pass Cut6x6 //25
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN_SOFT_EFFECT6X6();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_SOFT_EFFECT();
	}

	pass Cut4x4 // 26
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_SOFT_EFFECT4X4();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_SOFT_EFFECT();
	}

	pass Che_Alpha_Round // 27
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN3();
	}

	pass Cut8x8 // 28
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN_SOFT_EFFECT8X8();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_SOFT_EFFECT2();
	}

	pass DefaultGlowAlpha // 29
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN();
	}

	//VS_MAIN_SOFT_EFFECT4X3
	pass Cut4x3 // 30
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_SOFT_EFFECT4X3();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_SOFT_EFFECT_GLOW();
	}

	//VS_MAIN_SOFT_EFFECT4X1
	pass Cut4x1 // 31
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_SOFT_EFFECT4X1();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_SOFT_EFFECT_GLOW();
	}


	pass Cut6x3 // 32
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_SOFT_EFFECT6X3();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_SOFT_EFFECT3();
	}

	pass Arrow_Alpha2 //33
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_Pressing_Arrow();
	}

	pass Cut8x4 // 34
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_SOFT_EFFECT8X4();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_SOFT_EFFECT();
	}

	pass DefaultGlowAlpha_Beam // 35
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_BEAM();
	}

	pass Cut4x4_CHOI // 26번수정->36
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_SOFT_EFFECT4X4();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_SOFT_EFFECT_CHOI();
	}

	pass DefaultGlowAlpha_STATIC // 37
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_STATIC();
	}

	//VS_MAIN_SOFT_EFFECT4X2
	pass Cut4x2 // 38
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_SOFT_EFFECT4X2();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_SOFT_EFFECT_CHOI();
	}

	//
	pass Shadow_beam //39
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MOVEUV_SHADOW_BEAM();
	}

	pass Cut4x4_Bomb // 40
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_SOFT_EFFECT4X4();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_SOFT_EFFECT_BOMB();
	}

	pass FLOOR_EFFECT // 41
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_FLOOR_EFFECT();
	}

	pass YS_Alpha2 // 42
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_YS2();
	}

	pass YS_Alpha3 // 43
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_YS3();
	}
}


