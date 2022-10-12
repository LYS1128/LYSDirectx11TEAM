
#include "Shader_Defines.hpp"

struct BoneMatrix
{
	float4x4		BoneMatrices[256];
};

cbuffer Matrices
{
	float4x4		g_WorldMatrix, g_ViewMatrix, g_ProjMatrix;
	BoneMatrix		g_BoneMatrices;
}

vector				g_CamDirection;
float3				g_RimColor;
struct VS_IN
{
	float3		vPosition : POSITION;
	float3		vNormal : NORMAL;
	float2		vTexUV : TEXCOORD;
	uint4		vBlendIndex : BLENDINDEX;
	float4		vBlendWeight : BLENDWEIGHT;
};

struct VS_OUT
{
	float4		vPosition : SV_POSITION;
	float4		vNormal : NORMAL;
	float2		vTexUV : TEXCOORD0;
	float4		vProjPos : TEXCOORD1;
};

struct VS_OUT_RIM
{
	float4		vPosition : SV_POSITION;
	float4		vNormal : NORMAL;
	float2		vTexUV : TEXCOORD0;
	float4		vProjPos : TEXCOORD1;
	float4		vWorldPos : TEXCOORD2;
};

texture2D			g_DiffuseTexture;
texture2D			g_DisolveTexture;

float				g_RenderTick;
float				g_RenderTick2;

vector				g_Color;

sampler DefaultSampler = sampler_state {
	filter = min_mag_mip_linear;
	AddressU = wrap;
	AddressV = wrap;
};


VS_OUT VS_MAIN(VS_IN In)
{
	VS_OUT		Out;

	float		fWeightW = 1.f - (In.vBlendWeight.x + In.vBlendWeight.y + In.vBlendWeight.z);

	float4x4	BoneMatrix =
		g_BoneMatrices.BoneMatrices[In.vBlendIndex.x] * In.vBlendWeight.x +
		g_BoneMatrices.BoneMatrices[In.vBlendIndex.y] * In.vBlendWeight.y +
		g_BoneMatrices.BoneMatrices[In.vBlendIndex.z] * In.vBlendWeight.z +
		g_BoneMatrices.BoneMatrices[In.vBlendIndex.w] * fWeightW;


	float4x4	matWV, matWVP;

	matWV = mul(g_WorldMatrix, g_ViewMatrix);
	matWVP = mul(matWV, g_ProjMatrix);

	vector		vPosition = mul(float4(In.vPosition, 1.f), BoneMatrix);
	Out.vPosition = mul(vPosition, matWVP);

	vector		vNormal = mul(float4(In.vNormal, 0.f), BoneMatrix);
	Out.vNormal = normalize(mul(vNormal, g_WorldMatrix));

	Out.vTexUV = In.vTexUV;

	Out.vProjPos = Out.vPosition;

	return Out;
}

VS_OUT_RIM VS_MAIN_RIM(VS_IN In)
{
	VS_OUT_RIM		Out;

	float		fWeightW = 1.f - (In.vBlendWeight.x + In.vBlendWeight.y + In.vBlendWeight.z);

	float4x4	BoneMatrix =
		g_BoneMatrices.BoneMatrices[In.vBlendIndex.x] * In.vBlendWeight.x +
		g_BoneMatrices.BoneMatrices[In.vBlendIndex.y] * In.vBlendWeight.y +
		g_BoneMatrices.BoneMatrices[In.vBlendIndex.z] * In.vBlendWeight.z +
		g_BoneMatrices.BoneMatrices[In.vBlendIndex.w] * fWeightW;


	float4x4	matWV, matWVP;

	matWV = mul(g_WorldMatrix, g_ViewMatrix);
	matWVP = mul(matWV, g_ProjMatrix);

	vector		vPosition = mul(float4(In.vPosition, 1.f), BoneMatrix);
	Out.vPosition = mul(vPosition, matWVP);

	vector		vNormal = mul(float4(In.vNormal, 0.f), BoneMatrix);
	Out.vNormal = normalize(mul(vNormal, g_WorldMatrix));

	Out.vTexUV = In.vTexUV;

	Out.vProjPos = Out.vPosition;
	Out.vWorldPos = mul(vPosition, g_WorldMatrix);

	return Out;
}

struct PS_IN
{
	vector			vPosition : SV_POSITION;
	float4			vNormal : NORMAL;
	float2			vTexUV : TEXCOORD0;
	float4			vProjPos : TEXCOORD1;
};

struct PS_IN_RIM
{
	vector			vPosition : SV_POSITION;
	float4			vNormal : NORMAL;
	float2			vTexUV : TEXCOORD0;
	float4			vProjPos : TEXCOORD1;
	float4			vWorldPos : TEXCOORD2;
};

struct PS_OUT
{
	vector			vDiffuse : SV_TARGET0;
	vector			vNormal : SV_TARGET1;
	vector			vDepth : SV_TARGET2;
	vector			vEmissive : SV_TARGET3;
	vector			vGlow : SV_TARGET4;
	vector			vNotSSD : SV_TARGET5;
};

PS_OUT PS_MAIN(PS_IN In)
{
	PS_OUT			Out;

	Out.vDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vDiffuse.a < 0.5f)
		discard;

	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);

	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.f, 0.0f, 0.f);
	Out.vNotSSD = vector(1.f, 1.f, 1.f, 1.f);
	return Out;
}

PS_OUT PS_MINEEMISSIVE(PS_IN In)
{
	PS_OUT			Out;

	Out.vDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vDiffuse.a < 0.5f)
		discard;

	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);

	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.f, 0.0f, 0.f);
	if (Out.vDiffuse.r == 1.0 && Out.vDiffuse.g == 0.2f && Out.vDiffuse.b == 0.2f)
		Out.vEmissive = Out.vDiffuse;
	else
		Out.vEmissive = vector(0.f, 0.f, 0.f, 0.f);

	Out.vGlow = Out.vEmissive;
	Out.vNotSSD = vector(1.f, 1.f, 1.f, 1.f);
	return Out;
}

PS_OUT PS_MAIN_WHITE(PS_IN In)
{
	PS_OUT			Out;

	Out.vDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	Out.vDiffuse.xyz = 1.f;

	if (Out.vDiffuse.a < 0.5f)
		discard;

	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);

	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.f, 0.0f, 0.f);
	Out.vNotSSD = vector(1.f, 1.f, 1.f, 1.f);
	return Out;
}

PS_OUT PS_MAIN_GOWHITE(PS_IN In)
{
	PS_OUT			Out;

	Out.vDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	Out.vDiffuse.x = Out.vDiffuse.x + (1 - Out.vDiffuse.x) * g_RenderTick;
	Out.vDiffuse.y = Out.vDiffuse.y + (1 - Out.vDiffuse.y) * g_RenderTick;
	Out.vDiffuse.z = Out.vDiffuse.z + (1 - Out.vDiffuse.z) * g_RenderTick;

	if (Out.vDiffuse.a < 0.5f)
		discard;

	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);

	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.f, 0.0f, 0.f);
	Out.vNotSSD = vector(1.f, 1.f, 1.f, 1.f);
	return Out;
}

PS_OUT PS_MAIN_DAMAGED(PS_IN In)
{
	PS_OUT			Out;

	Out.vDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	Out.vDiffuse.x = 1.f;

	if (Out.vDiffuse.a < 0.5f)
		discard;

	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);

	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.f, 0.0f, 0.f);
	Out.vNotSSD = vector(1.f, 1.f, 1.f, 1.f);
	return Out;
}

PS_OUT PS_EMISSIVE_TEST(PS_IN In)
{
	PS_OUT			Out;

	Out.vDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vDiffuse.a < 0.5f)
		discard;

	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);

	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.f, 0.0f, 0.f);

	if (Out.vDiffuse.r > 170.f / 255.f && Out.vDiffuse.g < 40.f / 255.f && Out.vDiffuse.b < 40.f / 255.f)
		Out.vEmissive = Out.vDiffuse;
	else
		Out.vEmissive = vector(0.f, 0.f, 0.f, 0.f);

	Out.vGlow = Out.vEmissive;
	Out.vNotSSD = vector(1.f, 1.f, 1.f, 1.f);
	return Out;
}

PS_OUT PS_RIMLIGHTWHITE(PS_IN_RIM In)
{
	PS_OUT			Out;

	Out.vDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector vDisolve = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);

	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.f, 0.0f, 0.f);

	if (Out.vDiffuse.a < 0.5f)
		discard;


	vector ToCam = normalize(g_CamDirection - In.vWorldPos);

	float rimWidth = 0.5f;

	float RimLightColor = smoothstep(1.0f - rimWidth, 1.0f, 1 - max(0, dot(In.vNormal, ToCam)));

	if (dot(ToCam, In.vNormal) < 0.5f) {
		Out.vDiffuse.x = g_RimColor.x;
		Out.vDiffuse.y = g_RimColor.y;
		Out.vDiffuse.z = g_RimColor.z;
	}

	Out.vDiffuse.a = 1.f;

	Out.vNotSSD = vector(1.f, 1.f, 1.f, 1.f);
	Out.vEmissive = vector(Out.vDiffuse.r, Out.vDiffuse.g, Out.vDiffuse.b, 0.f);
	Out.vGlow = vector(0.f, 0.f, 0.f, 0.f);

	if (g_RenderTick / 255.f > vDisolve.r)
		discard;
	return Out;
}

PS_OUT PS_MAIN_MODEL_DISSOLVE_REDRIM(PS_IN_RIM In)
{
	PS_OUT			Out = (PS_OUT)0;

	Out.vDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	vector		vDissolve = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);


	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);

	if (Out.vDiffuse.a < 0.1f)
		discard;

	vector ToCam = normalize(g_CamDirection - In.vWorldPos);

	float rimWidth = 0.8f;

	float RimLightColor = smoothstep(1.0f - rimWidth, 1.0f, 1 - max(0, dot(In.vNormal, ToCam)));

	Out.vDiffuse += RimLightColor*vector(1.f, 0.f, 0.f, 0.f);

	if (g_RenderTick / 255.f >= vDissolve.r)
		discard;

	Out.vNotSSD = vector(1.f, 1.f, 1.f, 1.f);
	Out.vEmissive = vector(0.f, 0.f, 0.f, 0.f);
	Out.vGlow = vector(0.f, 0.f, 0.f, 0.f);
	return Out;
}

PS_OUT PS_MAIN_MODEL_DISSOLVE(PS_IN In)
{
	PS_OUT			Out = (PS_OUT)0;

	Out.vDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	vector		vDissolve = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);


	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.0f, 0.f, 0.f);
	//float Dist = distance(In.vWorldPos, g_PlayerPos)*0.01;
	//Out.vPlayerDist = vector(Dist, 0.f, 0.f, 1.f);
	//Out.vBlur = vector(0.f, 0.f, 0.f, 0.f);

	if (Out.vDiffuse.a < 0.1f)
		discard;

	if (g_RenderTick / 255.f >= vDissolve.r)
		discard;
	Out.vNotSSD = vector(1.f, 1.f, 1.f, 1.f);
	return Out;
}

PS_OUT PS_MAIN_REGRET(PS_IN In)
{
	PS_OUT			Out;

	Out.vDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	vector		vDissolve = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vDiffuse.a < 0.5f)
		discard;

	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);

	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.f, 0.0f, 0.f);

	if (255 / 255.f == Out.vDiffuse.r && 255 / 255.f == Out.vDiffuse.g && 255 / 255.f == Out.vDiffuse.b)
	{
		Out.vEmissive = vector(194 / 255.f, 204 / 255.f, 35 / 255.f, 0.5f);
		Out.vGlow = Out.vEmissive;
	}
	else
	{
		Out.vEmissive = vector(Out.vDiffuse.r, Out.vDiffuse.g, Out.vDiffuse.b, 0.f);
		Out.vGlow = vector(0.f, 0.f, 0.f, 0.f);
	}

	if (g_RenderTick / 255.f >= vDissolve.r)
		discard;

	Out.vNotSSD = vector(1.f, 1.f, 1.f, 1.f);

	return Out;
}

PS_OUT PS_CLONE2_RIMLIGHT(PS_IN_RIM In)
{
	PS_OUT			Out;

	Out.vDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector vDisolve = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);

	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.f, 0.0f, 0.f);

	if (Out.vDiffuse.a < 0.5f)
		discard;

	Out.vDiffuse.b *= 0.4f;

	Out.vDiffuse.r = Out.vDiffuse.b;
	Out.vDiffuse.g = Out.vDiffuse.b;

	vector ToCam = normalize(g_CamDirection - In.vWorldPos);

	float rimWidth = 0.5f;

	float RimLightColor = smoothstep(1.0f - rimWidth, 1.0f, 1 - max(0, dot(In.vNormal, ToCam)));

	if (dot(ToCam, In.vNormal) < 0.5f) {
		Out.vDiffuse.x = g_RimColor.x;
		Out.vDiffuse.y = g_RimColor.y;
		Out.vDiffuse.z = g_RimColor.z;
	}

	Out.vDiffuse.a = 1.f;

	Out.vNotSSD = vector(1.f, 1.f, 1.f, 1.f);
	Out.vEmissive = vector(Out.vDiffuse.r, Out.vDiffuse.g, Out.vDiffuse.b, 0.f);
	Out.vGlow = vector(0.f, 0.f, 0.f, 0.f);

	if (g_RenderTick2 / 255.f > vDisolve.r)
		discard;
	return Out;
}


PS_OUT PS_MAIN_MELEE(PS_IN In)
{
	PS_OUT         Out;

	Out.vDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	vector      vDissolve = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vDiffuse.a < 0.5f)
		discard;

	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);

	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w, In.vProjPos.w / 300.f, 0.0f, 0.f);

	if (Out.vDiffuse.r == 1.f &&Out.vDiffuse.g == 1.f &&Out.vDiffuse.b == 1.f)
	{
		Out.vDiffuse = g_Color;
		Out.vEmissive = g_Color;
		Out.vGlow = g_Color;
	}
	else
	{
		Out.vEmissive = vector(0.f, 0.f, 0.f, 0.f);
		Out.vGlow = vector(0.f, 0.f, 0.f, 0.f);
	}

	return Out;
}

technique11 DefaultTechnique
{
	pass DefaultRendering // 0
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN();
	}

	pass AllWhite // 1
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_WHITE();
	}

	pass Damaged // 2
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_DAMAGED();
	}

	pass EmissiveTest //3
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_EMISSIVE_TEST();
	}

	pass MineEmissiveRendering // 4
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MINEEMISSIVE();
	}

	pass OnlyRim // 5
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_RIM();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_RIMLIGHTWHITE();
	}

	pass Disolve_Player // 6
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_DISSOLVE();
	}

	pass Regret // 7
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_REGRET();
	}

	pass GoWhite // 8
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_GOWHITE();
	}

	pass Clone2 // 9
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_RIM();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_CLONE2_RIMLIGHT();
	}

	pass Resentment // 10
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_RIM();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_DISSOLVE_REDRIM();
	}

	pass Melee // 11
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MELEE();
	}
}


