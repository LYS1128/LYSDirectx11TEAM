
#include "Shader_Defines.hpp"


cbuffer Matrices
{
	float4x4		g_WorldMatrix, g_ViewMatrix, g_ProjMatrix;
	float4x4		g_SocketMatrix;
}

texture2D			g_DiffuseTexture;
texture2D			g_DiffuseTexture2;
texture2D			g_DisolveTexture;

float				g_RenderTick;
float				g_UVCount;
float				g_DeadTick;

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

struct PS_IN_MODEL
{
	float4		vPosition : SV_POSITION;
	float4		vNormal : NORMAL;
	float2		vTexUV : TEXCOORD0;
	float4		vProjPos : TEXCOORD1;
	float4		vWorldPos : TEXCOORD2;
};

struct PS_OUT
{
	vector			vDiffuse : SV_TARGET0;
	vector			vGlow : SV_TARGET1;
};

PS_OUT PS_MAIN_MODEL(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;
	Out.vGlow = Out.vDiffuse;

	if (vMtrlDiffuse.a < 0.1f)
		discard;

	return Out;
}

PS_OUT PS_MAIN_NONGLOW(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;
	Out.vGlow = vector(0.f, 0.f, 0.f, 0.f);

	if (vMtrlDiffuse.a < 0.1f)
		discard;

	return Out;
}

PS_OUT PS_MAIN_MODEL_STATICFIELD(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vMtrlDiffuse2 = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV + float2(0.5f,0.5f));
	vector		vLine = g_DiffuseTexture2.Sample(DefaultSampler, In.vTexUV);
	vector		vDissolve = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);

	vMtrlDiffuse2.r = 1.f;
	vMtrlDiffuse2.g = 0.5f;

	if (g_RenderTick / 255.f >= vDissolve.r)
		vMtrlDiffuse.a = 0.f;

	if ((255.f - g_RenderTick) / 255.f >= vDissolve.r)
		vMtrlDiffuse2.a = 0.f;

	if ((In.vTexUV.x < 0.5f - 0.25f*g_UVCount && In.vTexUV.x >= 0.25f - 0.25f*g_UVCount) || (In.vTexUV.x < 1.f - 0.25f*g_UVCount && In.vTexUV.x >= 0.75f - 0.25f*g_UVCount) || g_RenderTick < 250.f)
		vLine.a = 0.f;


	Out.vDiffuse = vMtrlDiffuse + vMtrlDiffuse2 + vLine;

	//Out.vGlow = Out.vDiffuse;
	Out.vGlow = Out.vDiffuse;

	if (g_DeadTick / 255.f >= vDissolve.r)
		Out.vDiffuse.a = 0.f;

	if (Out.vDiffuse.a < 0.1f)
		discard;

	return Out;
}

PS_OUT PS_MAIN_MODEL_METEOR_TRAIL(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	vector vDisolve = vMtrlDiffuse;
	Out.vGlow = vector(0.f, 0.f, 0.f, 0.f);
	float3 vColor1 = float3(255 / 255.f, 15 / 255.f, 0);
	float3 vColor2 = float3(255 / 255.f, 190 / 255.f, 0);

	Out.vDiffuse = vMtrlDiffuse;
	Out.vDiffuse.a = vMtrlDiffuse.r;
	Out.vDiffuse.rgb = Out.vDiffuse.rgb*vColor1 + (1 - Out.vDiffuse.rgb)*vColor2;

	if (g_RenderTick / 255.f <= vDisolve.r)
		discard;

	return Out;

}

PS_OUT PS_MAIN_MODEL_GREEN(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;
	Out.vDiffuse.r = Out.vDiffuse.r + (1.f - Out.vDiffuse.r)*(g_RenderTick);
	Out.vDiffuse.g = Out.vDiffuse.g*0.5f + (1.f - g_RenderTick)*(Out.vDiffuse.g)*0.5f;
	Out.vDiffuse.b = Out.vDiffuse.b*0.5f + (1.f - g_RenderTick)*(Out.vDiffuse.b)*0.5f;

	Out.vGlow = vector(0.f, 0.f, 0.f, 0.f);

	if (vMtrlDiffuse.a < 0.1f)
		discard;

	Out.vDiffuse.a = In.vTexUV.y;

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
	
	pass Model_StaticField //1
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_STATICFIELD();
	}
	pass Model_MeteorTrail //2
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_METEOR_TRAIL();
	}

	pass Model_GreenShield //3
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_GREEN();
	}

	pass ModelNonGlow //4
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_NONGLOW();
	}
}


