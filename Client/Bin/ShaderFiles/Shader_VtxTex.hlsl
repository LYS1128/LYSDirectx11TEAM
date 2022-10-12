
#include "Shader_Defines.hpp"

cbuffer Circle
{
	float2 g_fCenter;
	float g_fRadius;
	bool g_bool;
};

cbuffer SpriteNum
{
	int g_iNum;
}

cbuffer Trail {
	float4 g_TrailColor;
};

cbuffer Percent
{
	float g_fPercent;
	float g_fAlpha;
}

cbuffer ForItemUI
{
	float g_fSour;
	int	  g_iDest;
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

cbuffer ObjPos
{
	float g_fUpPos;
	float g_fDownPos;
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
texture2D			g_DisolveTexture;
texture2D			g_HealthMaskTexture;
texture2D			g_DepthTexture;

texture2D			g_MaskTexture;
texture2D			g_OutLineTexture;

texture2D			g_DistTexture;
texture2D			g_GradTexture;

float					g_fLine;
float					g_fRow;
float					g_fCurrentLine;
float					g_fCurrentRow;
float					g_fDisolve;
float					g_fStart;
float					g_fEnd;

vector				g_Color;

int					g_iFrame;
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

VS_OUT VS_MAIN_NXN(VS_IN In) // Meteor_Effect
{
	VS_OUT		Out;

	float4		vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;

	Out.vTexUV.x = In.vTexUV.x / g_fLine + 1 / g_fLine*g_fCurrentLine;
	Out.vTexUV.y = In.vTexUV.y / g_fRow + 1 / g_fRow*g_fCurrentRow;
	Out.vLocalPos = vector(In.vPosition, 1.f);

	return Out;
}

struct VS_OUT_SOFT_EFFECT
{
	float4		vPosition : SV_POSITION;
	float2		vTexUV : TEXCOORD;
	float4		vProjPos : TEXCOORD1;
};


VS_OUT VS_MAIN_SOFT_EFFECT(VS_IN In)
{
	VS_OUT		Out;

	float4		vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;

	Out.vTexUV.x = In.vTexUV.x / 8.f + 1 / 8.f*fmod(g_iFrame, 8);
	Out.vTexUV.y = In.vTexUV.y / 8.f + 1 / 8.f*(g_iFrame / 8);
	Out.vLocalPos = vector(In.vPosition, 1.f);

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
	Out.vTexUV.y = In.vTexUV.y / 4.f + 1 / 4.f*(g_iFrame / 8);

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


VS_OUT_SOFT_EFFECT VS_MAIN_SOFT_EFFECT6X4(VS_IN In)
{
	VS_OUT_SOFT_EFFECT		Out;

	float4		vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;
	Out.vProjPos = vPosition;

	Out.vTexUV.x = In.vTexUV.x / 6.f + 1 / 6.f*fmod(g_iFrame, 6);
	Out.vTexUV.y = In.vTexUV.y / 4.f + 1 / 4.f*(g_iFrame / 6);

	return Out;
}

VS_OUT VS_MAIN_8X4(VS_IN In)
{
	VS_OUT		Out;

	float4		vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;

	Out.vTexUV.x = In.vTexUV.x / 8.f + 1 / 8.f*fmod(g_iFrame, 8);
	Out.vTexUV.y = In.vTexUV.y / 4.f + 1 / 4.f*(g_iFrame / 8);
	Out.vLocalPos = vector(In.vPosition, 1.f);

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
	vector			vBlur : SV_TARGET4;
};

PS_OUT PS_MAIN(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	return Out;
}

PS_OUT PS_MAIN2(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);



	return Out;
};

PS_OUT PS_UI(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vColor.a == 0.f)
		discard;

	return Out;
}

PS_OUT PS_COLORITEM(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vColor.a == 0.f)
		discard;

	Out.vColor.rgb = g_Color.rgb;
	Out.vColor.a = Out.vColor.a*g_fPercent;

	Out.vBlur = vector(0.f, 0.f, 0.f, 0.f);

	return Out;
}


PS_OUT PS_COLORITEM2(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vColor.a == 0.f)
		discard;

	Out.vColor.a = Out.vColor.a*g_fPercent;

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

	if (Out.vColor.a <= 0.2f)
		discard;

	if (g_fPercent <= In.vTexUV.x)
		discard;

	return Out;
}

PS_OUT PS_RECYCLE(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vColor.a == 0.f)
		discard;

	Out.vColor.r = 1.f;
	Out.vColor.g = 1.f - g_fPercent;
	Out.vColor.b = 1.f - g_fPercent;

	if (g_fPercent <= In.vTexUV.x)
		discard;

	Out.vColor.a = g_fAlpha;

	return Out;
}

PS_OUT PS_FADE(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vColor.a <= 0.2f)
		discard;

	Out.vColor.a = g_fPercent;


	return Out;
}

PS_OUT PS_MINIMAP(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vColor.a <= 0.2f)
		discard;

	Out.vColor.a = g_fPercent;

	if (g_bool == false)
	{
		float Dis = sqrt(pow(g_fCenter.x - In.vPosition.x, 2) + pow(g_fCenter.y - In.vPosition.y, 2));

		if (Dis > g_fRadius)
			discard;
	}

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

	if (-0.5f + g_fPercent <= In.vLocalPos.x) {
		discard;
	}

	return Out;
}

PS_OUT PS_BOSSHEALTHBAR(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vColor.a == 0.f)
		discard;

	Out.vColor.a *= g_fAlpha;

	if (g_fPercent <= In.vTexUV.x) {
		discard;
	}

	return Out;
}


PS_OUT PS_COLORNUMBER(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vColor.a <= 0.2f)
		discard;

	Out.vColor.r = g_fColor.x;
	Out.vColor.g = g_fColor.y;
	Out.vColor.b = g_fColor.z;

	Out.vColor.a = g_fPercent;


	return Out;
}


PS_OUT PS_MOVETEXTURE2(PS_IN In)
{
	PS_OUT			Out;

	In.vTexUV.x -= g_TimeDelta * 0.1;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vColor.a == 0.f)
		discard;

	return Out;
}

PS_OUT PS_MOVETEXTURE3(PS_IN In)
{
	PS_OUT			Out;

	In.vTexUV.x -= g_TimeDelta * 0.1;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vColor.a == 0.f)
		discard;

	if (-0.5f + g_fPercent <= In.vLocalPos.x) {
		discard;
	}

	return Out;
}

PS_OUT PS_ALPHAPERCENT(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vColor.a == 0.f)
		discard;

	//Out.vColor.r = g_fColor.x;
	//Out.vColor.g = g_fColor.y;
	//Out.vColor.b = g_fColor.z;

	if (g_fPercent <= In.vTexUV.x)
		discard;

	Out.vColor.a = g_fAlpha;

	return Out;
}

PS_OUT PS_MOVETEXTURE_OWNCOLOR(PS_IN In)
{
	PS_OUT			Out;

	float Avg = (Out.vColor.x + Out.vColor.y + Out.vColor.z) / 3.f;

	//In.vTexUV.x -= g_TimeDelta * 0.5;
	In.vTexUV.y += g_TimeDelta * 0.1;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	Out.vColor.a = g_fPercent;



	if (Out.vColor.a == 0.f)
		discard;



	return Out;
}

PS_OUT PS_MOVETEXTUREFORBEAM(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	In.vTexUV.x += g_TimeDelta;

	return Out;
}

PS_OUT PS_COMBINEALPHA(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vColor.a <= 0.1f)
		discard;

	Out.vColor.a *= g_fPercent;

	return Out;
}

PS_OUT PS_ABILITYFRAME(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	//Out.vColor.a = g_fPercent;

	if (Out.vColor.a == 0.f)
		discard;

	return Out;
}

PS_OUT PS_UI_RSBG1(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vColor.a == 0.f)
		discard;

	if (g_fPercent <= In.vTexUV.x)
		discard;

	Out.vColor.a = g_fAlpha;

	return Out;
}

PS_OUT PS_UI_RSBG2(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vColor.a == 0.f)
		discard;

	if (g_fPercent >= In.vTexUV.x)
		discard;

	Out.vColor.a = g_fAlpha;

	return Out;
}

PS_OUT PS_MYALPHA(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vColor.a <= 0.2f)
		discard;

	Out.vColor.a = g_fPercent;

	return Out;
}

PS_OUT PS_COLTIMERENDER(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (g_fPercent <= In.vTexUV.y) {
		discard;
	}

	if (Out.vColor.a <= 0.2f)
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

PS_OUT PS_INVENTORYICON(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);
	vector Masking = g_MaskTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vColor.a = g_fPercent;

	if (Masking.a == 0.f)
		discard;

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

PS_OUT PS_MAIN_SOFT_EFFECT_BLUR(PS_IN_SOFT_EFFECT In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vColor.a <= 0.1f)
		discard;
	return Out;
}

PS_OUT PS_MAIN_SOFT_EFFECT2(PS_IN_SOFT_EFFECT In)
{
	PS_OUT			Out;

	float2		NewUV = In.vTexUV;
	NewUV.y += g_fFrame * 0.03f;

	Out.vColor = g_Texture.Sample(DefaultSampler, NewUV);

	float		fViewZ = In.vProjPos.w;

	float2		vUV;

	vUV.x = (In.vProjPos.x / In.vProjPos.w) * 0.5f + 0.5f;
	vUV.y = (In.vProjPos.y / In.vProjPos.w) * -0.5f + 0.5f;

	float4		vDepthDesc = g_DepthTexture.Sample(DefaultSampler, vUV);
	float		fTargetViewZ = vDepthDesc.y * 300.f;

	vector Mask = g_MaskTexture.Sample(DefaultSampler, In.vTexUV);

	if (Mask.r < 0.3f)
		Out.vColor.a = 0.f;
	else
		Out.vColor.a = max(min(fTargetViewZ - fViewZ, Out.vColor.a), 0.f) * 0.4f;


	return Out;
}

PS_OUT PS_MAIN_COLOR(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);
	Out.vColor.x = Out.vColor.x*g_Color.x;
	Out.vColor.y = Out.vColor.y*g_Color.y;
	Out.vColor.z = Out.vColor.z*g_Color.z;
	return Out;
}

PS_OUT PS_MAIN_BOMB(PS_IN_SOFT_EFFECT In)
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

	if (Out.vColor.a == 0.f)
		discard;

	Out.vColor.a = Out.vColor.a*g_fPercent;

	return Out;
}

PS_OUT PS_MAIN_LOADINGSKY(PS_IN In)
{
	PS_OUT			Out;

	float2		NewUV = In.vTexUV;
	NewUV.y += g_fFrame * 0.1f;
	float2		NewUV2 = In.vTexUV;
	NewUV2.y += g_fFrame * 0.05f;

	vector Dist = g_DistTexture.Sample(DefaultSampler, NewUV);

	float fWeight = Dist.r * 0.05f;

	Out.vColor = g_Texture.Sample(DefaultSampler, NewUV2 + fWeight);

	Out.vColor.a = g_fFrame / 25.5f;

	return Out;
}

PS_OUT PS_MAIN_MODEL_ROCK(PS_IN In)
{
	PS_OUT			Out;

	float2 vUV;
	vUV.x = (In.vTexUV.x - (1.f / g_fLine)*g_fCurrentLine*g_fLine);
	vUV.y = (In.vTexUV.y - (1.f / g_fRow)*g_fCurrentRow*g_fRow);
	Out.vColor = g_Texture.Sample(DefaultSampler, vUV);


	if (Out.vColor.r < 0.1f)
		discard;

	if (g_fDisolve / 255.f > Out.vColor.r)
		discard;

	return Out;
}

PS_OUT PS_MAIN_MODEL_PRIMALSCREAM_EFFECT(PS_IN In)
{
	PS_OUT			Out;

	vector vDiffuse = g_Texture.Sample(DefaultSampler, In.vTexUV);

	Out.vColor = vDiffuse;

	Out.vColor.a = Out.vColor.a*g_fStart / 255.f;

	if (g_fEnd < 180.f)
		Out.vColor.a = Out.vColor.a + g_fEnd;

	if (g_fEnd / 255.f < Out.vColor.r)
		discard;

	return Out;
}

PS_OUT PS_MAIN_PORTALINSIDE_NORMAL(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	Out.vColor.a = Out.vColor.r;

	if (0.f == Out.vColor.a)
		discard;

	Out.vColor.rgb += 0.2f;

	return Out;
}

PS_OUT PS_MAIN_PORTALINSIDE_RED(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	Out.vColor.a = Out.vColor.r;

	if (0.f == Out.vColor.a)
		discard;

	Out.vColor.r += 0.4f;
	Out.vColor.gb *= 0.1f;

	return Out;
}

PS_OUT PS_SCENE_BG(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	Out.vColor.a *= g_fPercent;

	if (Out.vColor.a == 0.f)
		discard;

	return Out;
}

PS_OUT PS_SHADOW_FEAR(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);
	Out.vColor.a *= g_fAlpha;

	if (Out.vColor.a == 0.0f)
		discard;

	return Out;
}

PS_OUT PS_MAIN_MODEL_STONE_TRACE(PS_IN In)
{
	PS_OUT			Out;

	float2 vUV;
	vUV.x = (In.vTexUV.x - (1.f / g_fLine)*g_fCurrentLine*g_fLine);
	vUV.y = (In.vTexUV.y - (1.f / g_fRow)*g_fCurrentRow*g_fRow);
	Out.vColor = g_Texture.Sample(DefaultSampler, vUV);

	Out.vColor.a = Out.vColor.r;

	if (0.f == Out.vColor.a)
		discard;

	Out.vColor.r *= 21 / 255.f;
	Out.vColor.g *= 9 / 255.f;
	Out.vColor.b *= 7 / 255.f;

	return Out;
}

PS_OUT PS_ATTACK_RING(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (0.f == Out.vColor.a)
		discard;

	Out.vColor.g = 0.2f;
	Out.vColor.b = 0.6f;

	Out.vColor.a *= g_fDisolve / 255.f;

	return Out;
}

PS_OUT PS_MAIN_MODEL_LAVA_EXPLOSION(PS_IN In)
{
	PS_OUT			Out;

	float2 vUV;
	vUV.x = (In.vTexUV.x - (1.f / g_fLine)*g_fCurrentLine*g_fLine);
	vUV.y = (In.vTexUV.y - (1.f / g_fRow)*g_fCurrentRow*g_fRow);
	Out.vColor = g_Texture.Sample(DefaultSampler, vUV);


	if (0.2f > Out.vColor.r)
		discard;

	if (Out.vColor.g < 122 / 255.f)
	{
		Out.vColor.r *= 1.3f;
		Out.vColor.g *= 0.5f;
	}



	Out.vColor.b = Out.vColor.g *0.5f;



	//Out.vBlur = vector(Out.vColor.r, Out.vColor.g, Out.vColor.b, 0.1f);

	return Out;
}

PS_OUT PS_MAIN_MODEL_LAVA_EXPLOSION2(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);
	vector vDisolve = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);

	if (0.8f< Out.vColor.r)
		discard;

	Out.vColor.r *= 0.1f;
	Out.vColor.g *= 0.1f;
	Out.vColor.b *= 0.1f;

	Out.vColor.a *= g_fAlpha / 255.f;

	if (g_fDisolve / 255.f < vDisolve.r)
		discard;


	//Out.vBlur = vector(Out.vColor.r, Out.vColor.g, Out.vColor.b, 0.1f);

	return Out;
}

PS_OUT PS_TRAIL_MODIFIER(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	Out.vColor.x *= g_TrailColor.x;
	Out.vColor.y *= g_TrailColor.y;
	Out.vColor.z *= g_TrailColor.z;
	Out.vColor.a *= g_TrailColor.a;

	if (0.f == Out.vColor.a)
		discard;

	return Out;
}
//BOOL BlendEnable;
//D3D11_BLEND SrcBlend;
//D3D11_BLEND DestBlend;
//D3D11_BLEND_OP BlendOp;
//D3D11_BLEND SrcBlendAlpha;
//D3D11_BLEND DestBlendAlpha;
//D3D11_BLEND_OP BlendOpAlpha;
//UINT8 RenderTargetWriteMask;


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
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
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
		PixelShader = compile ps_5_0 PS_MAIN_COLOR();
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

	pass MoveingTextureRendering2 // 12
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MOVETEXTURE2();
	}

	pass AlphaRendering2 // 13
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MYALPHA();
	}

	pass AbilityFrameRendering // 14
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_ABILITYFRAME();
	}

	pass Main2 // 15
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

	pass ColorNumberRendering // 16
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_COLORNUMBER();
	}

	pass RecycleRendering // 17
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_RECYCLE();
	}

	pass SoftEffect8x4 // 18
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_SOFT_EFFECT8X4();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_SOFT_EFFECT();
	}

	pass InventoryIconRendering // 19
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_INVENTORYICON();
	}

	pass ColorItem // 20
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_COLORITEM();
	}

	pass Bomb // 21
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_SOFT_EFFECT8X4();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_BOMB();
	}

	pass MinimapRendering  // 22
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MINIMAP();
	}

	pass LoadingSky // 23
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_LOADINGSKY();
	}
	pass SoftEffect8x8 // 24
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_SOFT_EFFECT8X8();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_SOFT_EFFECT();
	}

	pass SoftEffect2 // 25
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_SOFT_EFFECT2();
	}

	pass DeathCircleEfffect //26
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_COLORITEM2();
	}

	pass SoftEffect6x6 // 27
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_SOFT_EFFECT6X6();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_SOFT_EFFECT_BLUR();
	}
	pass SoftEffect6x4 // 28
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_SOFT_EFFECT6X4();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_SOFT_EFFECT_BLUR();
	}

	pass Ect // 29
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_SOFT_EFFECT();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN();
	}

	pass RSBG2 // 30
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_UI_RSBG2();
	}

	pass PS_ALPHAPERCENT // 31
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_ALPHAPERCENT();
	}

	pass CombineAlpha // 32
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_COMBINEALPHA();
	}

	pass RSBG1 // 33
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_UI_RSBG1();
	}

	pass BossHealthBarRendering // 34
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_BOSSHEALTHBAR();
	}

	pass Beam // 35
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_SOFT_EFFECT();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MOVETEXTUREFORBEAM();
	}

	pass ColtimeRendering // 36
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_COLTIMERENDER();
	}
	pass Meteor_Rock // 37
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_NXN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_ROCK();
	}
	pass PrimalsScream_Effect // 38
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_PRIMALSCREAM_EFFECT();
	}
	pass MoveingTextureRendering3 // 39
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MOVETEXTURE3();
	}
	pass Portal_Inside_Normal // 40
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_8X4();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_PORTALINSIDE_NORMAL();
	}
	pass Portal_Inside_Red // 41
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_8X4();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_PORTALINSIDE_RED();
	}

	pass Scene_BG // 42
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_SCENE_BG();
	}

	pass Fear_Shadow//43
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_SHADOW_FEAR();
	}

	pass Stone_Trace // 44
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_NXN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_STONE_TRACE();
	}
	pass Attack_Ring//45
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_ATTACK_RING();
	}

	pass Lava_Explosion // 46
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_NXN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_LAVA_EXPLOSION();
	}
	pass Lava_Explosion2 // 47
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_LAVA_EXPLOSION2();
	}

	pass Trail_Modifier//48
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_TRAIL_MODIFIER();
	}
}


