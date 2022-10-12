
#include "Shader_Defines.hpp"

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
int					g_iFrame;

float3					g_fColor3;
float					g_fDisolve;
float					g_fLine;
float					g_fRow;
float					g_fCurrentLine;
float					g_fCurrentRow;
float					g_R;
float					g_G;
float					g_B;
float					g_A;
float					g_fPercent;

vector					g_Color;

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

VS_OUT VS_MAIN_4X4(VS_IN In)
{
	VS_OUT	Out;

	float4		vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;

	Out.vTexUV.x = In.vTexUV.x / 4.f + 1 / 4.f*fmod(g_iFrame, 4);
	Out.vTexUV.y = In.vTexUV.y / 4.f + 1 / 4.f*(g_iFrame / 4);

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

PS_OUT PS_MAIN(PS_IN In) // 글로우 &블러
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vColor.a == 0.f)
		discard;

	Out.vBlur = Out.vColor;

	return Out;
}


PS_OUT PS_MAIN_NONBLUR(PS_IN In)//그냥 쌩블러 
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vColor.a == 0.f)
		discard;

	Out.vBlur = vector(0.f,0.f,0.f,0.f);

	return Out;
}

PS_OUT PS_MAIN_Dis1(PS_IN In) // 글로우 &블러
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);
	vector Dis = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);
	if (Out.vColor.a == 0.f)
		discard;

	if (g_fPercent <= Dis.r)
		discard;

	Out.vBlur = Out.vColor;

	return Out;
}

PS_OUT PS_MAIN_Dis2(PS_IN In) // 글로우 &블러
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);
	vector Dis = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vColor.a == 0.f)
		discard;

	if (g_fPercent <= 1.f - Dis.r)
		discard;

	Out.vBlur = Out.vColor;

	return Out;
}

PS_OUT PS_MAIN_RED(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (Out.vColor.a == 0.f)
		discard;

	Out.vColor.r = 1.f;
	Out.vColor.gb *= 0.1f;

		Out.vBlur = Out.vColor;

	return Out;
}

PS_OUT PS_MAIN_MODEL_SMOKE(PS_IN In)
{
	PS_OUT			Out;

	float2 vUV;
	vUV.x = (In.vTexUV.x - (1.f / g_fLine)*g_fCurrentLine*g_fLine);
	vUV.y = (In.vTexUV.y - (1.f / g_fRow)*g_fCurrentRow*g_fRow);
	Out.vColor = g_Texture.Sample(DefaultSampler, vUV);

	Out.vColor.rgb = Out.vColor.rgb*float3(g_R / 255.f, g_G / 255.f, g_B / 255.f);

	if (Out.vColor.r < 0.4f)
		discard;

	Out.vBlur = Out.vColor;

	return Out;
}

PS_OUT PS_MAIN_FEAR_JUMP_EFFECT(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);
	vector vDisolve = g_Texture.Sample(DefaultSampler, In.vTexUV);
	Out.vColor.a = Out.vColor.a * g_fDisolve / 255.f;
	if (Out.vColor.a == 0.f)
		discard;

	Out.vBlur = vector(0.f, 0.f, 0.f, 0.f);

	return Out;
}

PS_OUT PS_MAIN_FEAR_JUMP_RING(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);
	vector vDisolve = g_Texture.Sample(DefaultSampler, In.vTexUV);
	Out.vColor.a = Out.vColor.a * g_fDisolve / 255.f;

	if (Out.vColor.a == 0.f)
		discard;
	if (Out.vColor.r < 230 / 255.f)
		discard;

	Out.vColor.r = Out.vColor.r * 245 / 255.f;
	Out.vColor.g = Out.vColor.g * 78 / 255.f;
	Out.vColor.b = Out.vColor.b * 0 / 255.f;

	Out.vBlur = Out.vColor;

	return Out;
}

PS_OUT PS_TRAIL(PS_IN In) // 글로우 &블러
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);
	Out.vColor.a -= 0.4f;
	if (Out.vColor.a == 0.f)
		discard;

	Out.vColor.x = Out.vColor.x*g_Color.x;
	Out.vColor.y = Out.vColor.y*g_Color.y;
	Out.vColor.z = Out.vColor.z*g_Color.z;

	Out.vBlur = vector(1.f, 1.f, 1.f, 0.3f);

	return Out;
}


PS_OUT PS_MAIN_WATCH(PS_IN In) // 글로우 &블러
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);
	Out.vColor.a *= 1.f - g_A;
	if (Out.vColor.a == 0.f)
		discard;

	Out.vBlur = Out.vColor;

	return Out;
}

PS_OUT PS_MAIN_BOMB(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);
	Out.vColor.r += 1.f*g_fPercent;
	Out.vColor.g *= 1.f - g_fPercent;
	Out.vColor.b *= 1.f - g_fPercent;

	if (Out.vColor.a < 0.1f)
		discard;

	Out.vBlur = vector(0.f, 0.f, 0.f, 0.f);

	return Out;
}

PS_OUT PS_MAIN_REGRET_TRAIL0(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	if (0.2f > Out.vColor.a)
		discard;

	Out.vColor.r *= 194 / 255.f;
	Out.vColor.g *= 204 / 255.f;
	Out.vColor.b *= 35 / 255.f;

	Out.vBlur = vector(194 / 255.f, 204 / 255.f, 35 / 255.f, 1.f);


	return Out;
}

PS_OUT PS_MAIN_REGRET_TRAIL1(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	Out.vColor.a = Out.vColor.r;

	if (0.3f > Out.vColor.a)
		discard;

	Out.vColor.r *= 194 / 255.f;
	Out.vColor.g *= 204 / 255.f;
	Out.vColor.b *= 35 / 255.f;

	Out.vBlur = Out.vColor;

	return Out;
}

PS_OUT PS_MAIN_REGRET_CLONE_TRAIL1(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	Out.vColor.a = Out.vColor.r;

	if (0.3f > Out.vColor.a)
		discard;

	Out.vColor.r *= g_fColor3.r / 255.f;
	Out.vColor.g *= g_fColor3.g / 255.f;
	Out.vColor.b *= g_fColor3.b / 255.f;


	Out.vBlur = Out.vColor;

	return Out;
}

PS_OUT PS_TRAIL_DAGGER(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);
	Out.vColor -= 0.1f;
	if (Out.vColor.a == 0.f)
		discard;

	Out.vColor.x = Out.vColor.x * 170 / 255.f;
	Out.vColor.y = Out.vColor.y * 211 / 255.f;
	Out.vColor.z = Out.vColor.z * 211 / 255.f;

	Out.vBlur = vector(Out.vColor.r, Out.vColor.g, Out.vColor.b, 0.7f);

	return Out;
}

PS_OUT PS_MAIN_RESENTMENT_TRAIL(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);
	vector vDisolve = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);

	if (0.1f > Out.vColor.a)
		discard;

	Out.vBlur = Out.vColor;

	if (g_fDisolve / 255.f > vDisolve.r)
		discard;

	return Out;
}

PS_OUT PS_MAIN_MODEL_SWORD_FIRE(PS_IN In)
{
	PS_OUT			Out;

	float2 vUV;
	vUV.x = (In.vTexUV.x - (1.f / g_fLine)*g_fCurrentLine*g_fLine);
	vUV.y = (In.vTexUV.y - (1.f / g_fRow)*g_fCurrentRow*g_fRow);
	Out.vColor = g_Texture.Sample(DefaultSampler, vUV);

	Out.vColor.a = Out.vColor.r;

	if (0.1f > Out.vColor.a)
		discard;

	Out.vColor.g = Out.vColor.r / 3.f;
	Out.vColor.b = (Out.vColor.r - Out.vColor.g) / 3.f;


	Out.vBlur = vector(Out.vColor.r, Out.vColor.g, Out.vColor.b, 0.3f);

	return Out;
}

PS_OUT PS_LAVA_RECT(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);
	vector	vDisolve = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);

	if (0.1f > Out.vColor.r)
		discard;

	if (vDisolve.r > g_fDisolve / 255.f)
		discard;

	Out.vBlur = vector(Out.vColor.r, Out.vColor.g, Out.vColor.b, 0.3f);

	return Out;
}



technique11 DefaultTechnique
{
	pass DefaultRendering // 0
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN();
	}

	pass NonBlur// 1
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_NONBLUR();
	}

	pass Default8x4 // 2
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_8X4();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN();
	}

	pass Default8x4Red // 3
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_8X4();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_RED();
	}
	pass Meteor_Smoke // 4
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_NXN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_SMOKE();
	}
	pass Fear_Jump_Effect// 5
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_FEAR_JUMP_EFFECT();
	}
	pass Fear_Jump_Ring// 6
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_FEAR_JUMP_RING();
	}

	pass Trail // 7
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_TRAIL();
	}

	pass TestMask // 8
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN();
	}

	pass WatchEffect //9
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_WATCH();
	}

	pass Cut4x4_Bomb //10
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_4X4();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_BOMB();
	}

	pass Regret_Trail0 //11
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_REGRET_TRAIL0();
	}

	pass Regret_Trail1 //12
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_REGRET_TRAIL1();
	}

	pass Regret_Clone_Trail1 //13
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_REGRET_CLONE_TRAIL1();
	}

	pass Dis1 //14
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_Dis1();
	}

	pass Dis2 //15
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_Dis2();
	}

	pass Trail_Dagger // 16
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_TRAIL_DAGGER();
	}

	pass ResentMent_Trail //17
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_RESENTMENT_TRAIL();
	}

	pass Sword_Fire // 18
	{
		SetRasterizerState(RS_Not_Cull);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_NXN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MODEL_SWORD_FIRE();
	}

	pass Lava_Rect//19
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);
		/*	SetDepthStencilState();
		*/

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_LAVA_RECT();
	}
}


