
#include "Shader_Defines.hpp"


cbuffer Matrices
{
	float4x4		g_WorldMatrix, g_ViewMatrix, g_ProjMatrix;
	float4x4		g_SocketMatrix;
}

texture2D			g_DiffuseTexture;
texture2D			g_DisolveTexture;

float				g_RenderTick;

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
	vector			vEmissive : SV_TARGET1;
	vector			vGlow : SV_TARGET2;
};

PS_OUT PS_MAIN_MODEL(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;

	if (vMtrlDiffuse.a < 0.1f)
		discard;

	if (Out.vDiffuse.r > 170.f / 255.f && Out.vDiffuse.g < 40.f / 255.f && Out.vDiffuse.b < 40.f / 255.f)
		Out.vEmissive = Out.vDiffuse;
	else
		Out.vEmissive = vector(0.f, 0.f, 0.f, 0.f);

	Out.vGlow = Out.vEmissive;

	return Out;
}

PS_OUT PS_MAIN_MODEL_SHIVER(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;

	if (vMtrlDiffuse.a < 0.1f)
		discard;

	if (Out.vDiffuse.r + Out.vDiffuse.g + Out.vDiffuse.b > 2.5f)
		Out.vEmissive = Out.vDiffuse;
	else
		Out.vEmissive = vector(0.f, 0.f, 0.f, 0.f);

	Out.vGlow = Out.vEmissive;

	return Out;
}

PS_OUT PS_MAIN_MODEL_ALL(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;

	if (vMtrlDiffuse.a < 0.1f)
		discard;

	if (Out.vDiffuse.r + Out.vDiffuse.g + Out.vDiffuse.b <= 2.5f)
		Out.vEmissive = Out.vDiffuse;
	else
		Out.vEmissive = vector(0.f, 0.f, 0.f, 0.f);


	Out.vGlow = Out.vEmissive;

	return Out;
}

PS_OUT PS_MAIN_MODEL_PORTALSNOW(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vDissolve = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;

	if (vMtrlDiffuse.a < 0.1f)
		discard;

	if (g_RenderTick / 255.f <= vDissolve.r)
		discard;


	Out.vGlow = Out.vEmissive;

	return Out;
}


PS_OUT PS_MAIN_MODEL_ENEMY_ROUND(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;

	if (vMtrlDiffuse.a < 0.1f)
		discard;


	if (Out.vDiffuse.r <= 0.4f)
		Out.vEmissive = Out.vDiffuse;
	else
		Out.vEmissive = vector(0.f, 0.f, 0.f, 0.f);

	Out.vGlow = Out.vEmissive;

	return Out;
}

float		g_Pressing_Arrow;

PS_OUT PS_Pressing_Arrow(PS_IN_MODEL In) // È°½ò¶§ ¹Ø¿¡ ³ª¿À´Â ÀÌÆåÆ®
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;


	if (In.vTexUV.y < g_Pressing_Arrow)
		discard;

	if (vMtrlDiffuse.a < 0.1f)
		discard;

	return Out;

}

float			g_MoveUV2;

PS_OUT PS_MAIN_MODEL_Arrow_Trail(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	In.vTexUV.x += g_MoveUV2;
	In.vTexUV.y += g_MoveUV2;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;



	if (vMtrlDiffuse.a < 0.1f)
		discard;

	if (Out.vDiffuse.r + Out.vDiffuse.g + Out.vDiffuse.b <= 2.5f)
		Out.vEmissive = Out.vDiffuse;
	else
		Out.vEmissive = vector(0.f, 0.f, 0.f, 0.f);

	Out.vGlow = Out.vEmissive;

	return Out;
}

PS_OUT PS_MAIN_MODEL_MAGIC_SHOCK(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;

	if (vMtrlDiffuse.a < 0.1f)
		discard;

	if (Out.vDiffuse.r >= g_RenderTick)
		Out.vEmissive = Out.vDiffuse;
	else
		Out.vEmissive = vector(0.f, 0.f, 0.f, 0.f);

	Out.vGlow = Out.vEmissive;

	return Out;
}

PS_OUT PS_MAIN_MODEL_BEAM(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	In.vTexUV.y += g_MoveUV2;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector		vDissolve = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;

	if (vMtrlDiffuse.a < 0.1f)
		discard;


	if (g_RenderTick / 255.f >= vDissolve.r)
		discard;


	if (Out.vDiffuse.r + Out.vDiffuse.g + Out.vDiffuse.b > 2.5f)
		Out.vEmissive = Out.vDiffuse;
	else
		Out.vEmissive = vector(0.f, 0.f, 0.f, 0.f);

	//Out.vGlow = Out.vEmissive;

	return Out;
}

PS_OUT PS_MAIN_MODEL_CYLINDEREFFECT(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	In.vTexUV.y += g_MoveUV2;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;

	if (vMtrlDiffuse.a < 0.1f)
		discard;

	//	if (Out.vDiffuse.r + Out.vDiffuse.g + Out.vDiffuse.b <= 2.5f)
	Out.vEmissive = Out.vDiffuse;
	//else
	//	Out.vEmissive = vector(0.f, 0.f, 0.f, 0.f);


	Out.vGlow = Out.vEmissive;

	return Out;
}

PS_OUT PS_MAIN_MODEL_BLAST(PS_IN_MODEL In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector		vMtrlDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vDiffuse = vMtrlDiffuse;

	if (vMtrlDiffuse.a < 0.1f)
		discard;

	if (Out.vDiffuse.r + Out.vDiffuse.g + Out.vDiffuse.b > 2.5f)
		Out.vEmissive = Out.vDiffuse;
	else
		Out.vEmissive = vector(0.f, 0.f, 0.f, 0.f);

	Out.vGlow = Out.vEmissive;


	Out.vDiffuse.a = 0.5f;

	return Out;
}

technique11 DefaultTechnique
{
	pass Model //0
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL();
	}

	pass Model_Shiver_Ring //1
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_SHIVER();
	}
	pass Model_All //2
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_ALL();
	}

	pass Model_PortalSnow //3
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_PORTALSNOW();
	}

	pass Model_ENEMY_ROUND //4
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_ENEMY_ROUND();
	}

	pass Model_Arrow //5
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_Pressing_Arrow();
	}

	pass Model_Arrow_Trailg //6
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_Arrow_Trail();
	}
	pass Model_Arrow_MAGICSHOCK //7
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_MAGIC_SHOCK();
	}


	pass Model_Arrow_BEAM //8
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_BEAM();
	}
	pass Model_Cylinder //9
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_CYLINDEREFFECT();
	}
	pass Model_BLAST //10
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_MODEL();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_BLAST();
	}

}


