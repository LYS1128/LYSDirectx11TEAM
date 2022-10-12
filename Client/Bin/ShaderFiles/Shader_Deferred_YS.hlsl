
cbuffer Matrices
{
	float4x4		g_WorldMatrix, g_ViewMatrix, g_ProjMatrix;
	float4x4		g_ViewMatrixInv, g_ProjMatrixInv;
	float4x4		g_matLightView, g_matLightProj;
}

cbuffer LightDesc
{
	float4		g_vLightDir;
	float4		g_vLightPos;
	float		g_LightPower;
	float		g_fRange;
	float4		g_vLightDiffuse;
	float4		g_vLightAmbient;
	float4		g_vLightSpecular;
}

cbuffer MaterialDesc
{
	float4		g_vMtrlAmbient = (float4)1.f;
	float4		g_vMtrlSpecular = (float4)1.f;
	float		g_fPower = 30.0f;
}

cbuffer CameraDesc
{
	float4		g_vCamPosition;
}

texture2D		g_Texture;
texture2D		g_NormalTexture;
texture2D		g_DiffuseTexture;
texture2D		g_ShadeTexture;
texture2D		g_DepthTexture;
texture2D		g_SpecularTexture;
texture2D		g_LightDepthTexture;

texture2D		g_EmissiveTexture;
texture2D		g_EmissiveGlowTexture;
texture2D		g_NonLightEmissiveTexture;
texture2D		g_NonLightEmissiveGlowTexture;
texture2D		g_NonLightBlurTexture;
texture2D		g_NonLightGlowTexture;
texture2D		g_ShadowTexture;
texture2D		g_HeightTexture;

texture2D		g_AlphaBlendTexture;
texture2D		g_NonLightTexture;
texture2D		g_BlurTexture;

float			g_RadialTime;
float			g_HazeTime;

texture2D		g_MaskingTexture;
texture2D		g_DistortionTexture;
texture2D		g_WatchTexture;
texture2D		g_NoiseTexture;

texture2D		g_DisolveTexture;
int				g_RenderTick;
texture2D		g_LUTTex;


sampler DefaultSampler = sampler_state {
	filter = min_mag_mip_linear;
	AddressU = wrap;
	AddressV = wrap;
};

sampler ShadowDepthSampler = sampler_state
{
	filter = min_mag_linear_mip_point;
	AddressU = clamp;
	AddressV = clamp;
};

sampler2D g_LUTSam = sampler_state
{
	texture = g_LUTTex;
};

float3 Get_LutColor(float3 colorIN, sampler2D LutSampler) {
	float2 LutSize = float2(0.00390625, 0.0625);
	float4 LutUV;
	colorIN = saturate(colorIN) * 15.0;
	LutUV.w = floor(colorIN.b);
	LutUV.xy = (colorIN.rg + 0.5) * LutSize;
	LutUV.x += LutUV.w * LutSize.y;
	LutUV.z = LutUV.x + LutSize.y;
	return lerp(g_LUTTex.SampleLevel(DefaultSampler, LutUV.xy, LutUV.z).rgb, g_LUTTex.SampleLevel(DefaultSampler, LutUV.zy, LutUV.z).rgb, colorIN.b - LutUV.w);
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
};

struct VS_OUT_HBLUR
{
	float4		vPosition : SV_POSITION;
	float2		vTexUV : TEXCOORD0;
	float2		vHPos1 : TEXCOORD1;
	float2		vHPos2 : TEXCOORD2;
	float2		vHPos3 : TEXCOORD3;
	float2		vHPos4 : TEXCOORD4;
	float2		vHPos5 : TEXCOORD5;
	float2		vHPos6 : TEXCOORD6;
	float2		vHPos7 : TEXCOORD7;
	float2		vHPos8 : TEXCOORD8;
	float2		vHPos9 : TEXCOORD9;
};

struct VS_OUT_WBLUR
{
	float4		vPosition : SV_POSITION;
	float2		vTexUV : TEXCOORD0;
	float2		vWPos1 : TEXCOORD1;
	float2		vWPos2 : TEXCOORD2;
	float2		vWPos3 : TEXCOORD3;
	float2		vWPos4 : TEXCOORD4;
	float2		vWPos5 : TEXCOORD5;
	float2		vWPos6 : TEXCOORD6;
	float2		vWPos7 : TEXCOORD7;
	float2		vWPos8 : TEXCOORD8;
	float2		vWPos9 : TEXCOORD9;
};

struct VS_OUT_HBLUR2
{
	float4		vPosition : SV_POSITION;
	float2		vTexUV : TEXCOORD0;
	float2		vHPos1 : TEXCOORD1;
	float2		vHPos2 : TEXCOORD2;
	float2		vHPos3 : TEXCOORD3;
	float2		vHPos4 : TEXCOORD4;
	float2		vHPos5 : TEXCOORD5;
	float2		vHPos6 : TEXCOORD6;
	float2		vHPos7 : TEXCOORD7;
	float2		vHPos8 : TEXCOORD8;
	float2		vHPos9 : TEXCOORD9;
	float2		vHPos10 : TEXCOORD10;
	float2		vHPos11 : TEXCOORD11;
	float2		vHPos12 : TEXCOORD12;
	float2		vHPos13 : TEXCOORD13;
};

struct VS_OUT_WBLUR2
{
	float4		vPosition : SV_POSITION;
	float2		vTexUV : TEXCOORD0;
	float2		vWPos1 : TEXCOORD1;
	float2		vWPos2 : TEXCOORD2;
	float2		vWPos3 : TEXCOORD3;
	float2		vWPos4 : TEXCOORD4;
	float2		vWPos5 : TEXCOORD5;
	float2		vWPos6 : TEXCOORD6;
	float2		vWPos7 : TEXCOORD7;
	float2		vWPos8 : TEXCOORD8;
	float2		vWPos9 : TEXCOORD9;
	float2		vWPos10 : TEXCOORD10;
	float2		vWPos11 : TEXCOORD11;
	float2		vWPos12 : TEXCOORD12;
	float2		vWPos13 : TEXCOORD13;
};

VS_OUT VS_MAIN(VS_IN In)
{
	VS_OUT		Out;

	float4		vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;
	Out.vTexUV = In.vTexUV;

	return Out;
}

VS_OUT_WBLUR VS_MAIN_WBLUR(VS_IN In)
{
	VS_OUT_WBLUR		Out;

	float4		vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;
	Out.vTexUV = In.vTexUV;

	float fWTexelSize = 1.0f / 1280;
	float fHTexelSize = 1.0f / 720;

	Out.vWPos1 = In.vTexUV + float2(fWTexelSize * -4.0f, 0.0f);
	Out.vWPos2 = In.vTexUV + float2(fWTexelSize * -3.0f, 0.0f);
	Out.vWPos3 = In.vTexUV + float2(fWTexelSize * -2.0f, 0.0f);
	Out.vWPos4 = In.vTexUV + float2(fWTexelSize * -1.0f, 0.0f);
	Out.vWPos5 = In.vTexUV + float2(fWTexelSize * 0.0f, 0.0f);
	Out.vWPos6 = In.vTexUV + float2(fWTexelSize * 1.0f, 0.0f);
	Out.vWPos7 = In.vTexUV + float2(fWTexelSize * 2.0f, 0.0f);
	Out.vWPos8 = In.vTexUV + float2(fWTexelSize * 3.0f, 0.0f);
	Out.vWPos9 = In.vTexUV + float2(fWTexelSize * 4.0f, 0.0f);

	return Out;
}

VS_OUT_WBLUR2 VS_MAIN_WBLUR_AND_DOWNSAMPLING(VS_IN In)
{
	VS_OUT_WBLUR2		Out;

	float4		vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;
	Out.vTexUV = In.vTexUV * 2;

	float fWTexelSize = 1.0f / 640;
	float fHTexelSize = 1.0f / 360;

	Out.vWPos1 = Out.vTexUV + float2(fWTexelSize * -6.0f, 0.0f);
	Out.vWPos2 = Out.vTexUV + float2(fWTexelSize * -5.0f, 0.0f);
	Out.vWPos3 = Out.vTexUV + float2(fWTexelSize * -4.0f, 0.0f);
	Out.vWPos4 = Out.vTexUV + float2(fWTexelSize * -3.0f, 0.0f);
	Out.vWPos5 = Out.vTexUV + float2(fWTexelSize * -2.0f, 0.0f);
	Out.vWPos6 = Out.vTexUV + float2(fWTexelSize * -1.0f, 0.0f);
	Out.vWPos7 = Out.vTexUV + float2(fWTexelSize * 0.0f, 0.0f);
	Out.vWPos8 = Out.vTexUV + float2(fWTexelSize * 1.0f, 0.0f);
	Out.vWPos9 = Out.vTexUV + float2(fWTexelSize * 2.0f, 0.0f);
	Out.vWPos10 = Out.vTexUV + float2(fWTexelSize * 3.0f, 0.0f);
	Out.vWPos11 = Out.vTexUV + float2(fWTexelSize * 4.0f, 0.0f);
	Out.vWPos12 = Out.vTexUV + float2(fWTexelSize * 5.0f, 0.0f);
	Out.vWPos13 = Out.vTexUV + float2(fWTexelSize * 6.0f, 0.0f);

	return Out;
}

VS_OUT_HBLUR2 VS_MAIN_HBLUR_AND_DOWNSAMPLING(VS_IN In)
{
	VS_OUT_HBLUR2		Out;

	float4		vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;
	Out.vTexUV = In.vTexUV;

	float fWTexelSize = 1.0f / 1280;
	float fHTexelSize = 1.0f / 720;

	Out.vHPos1 = Out.vTexUV + float2(0.0f, fHTexelSize * -6.0f);
	Out.vHPos2 = Out.vTexUV + float2(0.0f, fHTexelSize * -5.0f);
	Out.vHPos3 = Out.vTexUV + float2(0.0f, fHTexelSize * -4.0f);
	Out.vHPos4 = Out.vTexUV + float2(0.0f, fHTexelSize * -3.0f);
	Out.vHPos5 = Out.vTexUV + float2(0.f, fHTexelSize * -2.0f);
	Out.vHPos6 = Out.vTexUV + float2(0.f, fHTexelSize * -1.0f);
	Out.vHPos7 = Out.vTexUV + float2(0.f, fHTexelSize * 0.0f);
	Out.vHPos8 = Out.vTexUV + float2(0.f, fHTexelSize * 1.0f);
	Out.vHPos9 = Out.vTexUV + float2(0.f, fHTexelSize * 2.0f);
	Out.vHPos10 = Out.vTexUV + float2(0.f, fHTexelSize * 3.0f);
	Out.vHPos11 = Out.vTexUV + float2(0.f, fHTexelSize * 4.0f);
	Out.vHPos12 = Out.vTexUV + float2(0.f, fHTexelSize * 5.0f);
	Out.vHPos13 = Out.vTexUV + float2(0.f, fHTexelSize * 6.0f);

	return Out;
}

VS_OUT_HBLUR VS_HBLUR(VS_IN In)
{
	VS_OUT_HBLUR		Out;

	float4		vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;
	Out.vTexUV = In.vTexUV;

	float fWTexelSize = 1.0f / 1280;
	float fHTexelSize = 1.0f / 720;

	Out.vHPos1 = Out.vTexUV + float2(0.0f, fHTexelSize * -4.0f);
	Out.vHPos2 = Out.vTexUV + float2(0.0f, fHTexelSize * -3.0f);
	Out.vHPos3 = Out.vTexUV + float2(0.0f, fHTexelSize * -2.0f);
	Out.vHPos4 = Out.vTexUV + float2(0.0f, fHTexelSize * -1.0f);
	Out.vHPos5 = Out.vTexUV + float2(0.f, fHTexelSize * 0.0f);
	Out.vHPos6 = Out.vTexUV + float2(0.f, fHTexelSize * 1.0f);
	Out.vHPos7 = Out.vTexUV + float2(0.f, fHTexelSize * 2.0f);
	Out.vHPos8 = Out.vTexUV + float2(0.f, fHTexelSize * 3.0f);
	Out.vHPos9 = Out.vTexUV + float2(0.f, fHTexelSize * 4.0f);

	return Out;
}

struct PS_IN
{
	vector			vPosition : SV_POSITION;
	float2			vTexUV : TEXCOORD0;
};

struct PS_OUT
{
	vector			vColor : SV_TARGET0;
};

struct PS_OUT_DEF
{
	vector			vColor : SV_TARGET0;
	vector			vShadow : SV_TARGET1;
	vector			vHeight : SV_TARGET2;
};

struct PS_OUT_BLUR
{
	vector			vColor : SV_TARGET0;
	vector			vGlow : SV_TARGET1;
};

struct PS_OUT_LIGHT
{
	vector			vShade : SV_TARGET0;
	vector			vSpecular : SV_TARGET1;
};

struct PS_IN_HBLUR
{
	float4		vPosition : SV_POSITION;
	float2		vTexUV : TEXCOORD0;
	float2		vHPos1 : TEXCOORD1;
	float2		vHPos2 : TEXCOORD2;
	float2		vHPos3 : TEXCOORD3;
	float2		vHPos4 : TEXCOORD4;
	float2		vHPos5 : TEXCOORD5;
	float2		vHPos6 : TEXCOORD6;
	float2		vHPos7 : TEXCOORD7;
	float2		vHPos8 : TEXCOORD8;
	float2		vHPos9 : TEXCOORD9;
};

struct PS_IN_WBLUR
{
	float4		vPosition : SV_POSITION;
	float2		vTexUV : TEXCOORD0;
	float2		vWPos1 : TEXCOORD1;
	float2		vWPos2 : TEXCOORD2;
	float2		vWPos3 : TEXCOORD3;
	float2		vWPos4 : TEXCOORD4;
	float2		vWPos5 : TEXCOORD5;
	float2		vWPos6 : TEXCOORD6;
	float2		vWPos7 : TEXCOORD7;
	float2		vWPos8 : TEXCOORD8;
	float2		vWPos9 : TEXCOORD9;
};

struct PS_IN_HBLUR2
{
	float4		vPosition : SV_POSITION;
	float2		vTexUV : TEXCOORD0;
	float2		vHPos1 : TEXCOORD1;
	float2		vHPos2 : TEXCOORD2;
	float2		vHPos3 : TEXCOORD3;
	float2		vHPos4 : TEXCOORD4;
	float2		vHPos5 : TEXCOORD5;
	float2		vHPos6 : TEXCOORD6;
	float2		vHPos7 : TEXCOORD7;
	float2		vHPos8 : TEXCOORD8;
	float2		vHPos9 : TEXCOORD9;
	float2		vHPos10 : TEXCOORD10;
	float2		vHPos11 : TEXCOORD11;
	float2		vHPos12 : TEXCOORD12;
	float2		vHPos13 : TEXCOORD13;
};

struct PS_IN_WBLUR2
{
	float4		vPosition : SV_POSITION;
	float2		vTexUV : TEXCOORD0;
	float2		vWPos1 : TEXCOORD1;
	float2		vWPos2 : TEXCOORD2;
	float2		vWPos3 : TEXCOORD3;
	float2		vWPos4 : TEXCOORD4;
	float2		vWPos5 : TEXCOORD5;
	float2		vWPos6 : TEXCOORD6;
	float2		vWPos7 : TEXCOORD7;
	float2		vWPos8 : TEXCOORD8;
	float2		vWPos9 : TEXCOORD9;
	float2		vWPos10 : TEXCOORD10;
	float2		vWPos11 : TEXCOORD11;
	float2		vWPos12 : TEXCOORD12;
	float2		vWPos13 : TEXCOORD13;
};

PS_OUT PS_MAIN_DEBUG(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	return Out;
}

PS_OUT_LIGHT PS_MAIN_LIGHT_DIRECTIONAL(PS_IN In)
{
	PS_OUT_LIGHT		Out = (PS_OUT_LIGHT)0;

	vector			vNormalDesc = g_NormalTexture.Sample(DefaultSampler, In.vTexUV);
	vector			vDepthDesc = g_DepthTexture.Sample(DefaultSampler, In.vTexUV);
	float			fViewZ = vDepthDesc.y * 300.f;

	vector			vNormal = vector(vNormalDesc.xyz * 2.f - 1.f, 0.f);

	Out.vShade = saturate(dot(normalize(g_vLightDir) * -g_LightPower, vNormal)) + (g_vLightAmbient * g_vMtrlAmbient);
	Out.vShade.a = 1.f;

	vector			vReflect = reflect(normalize(g_vLightDir), vNormal);

	vector			vWorldPos;
	vWorldPos.x = In.vTexUV.x * 2.f - 1.f;
	vWorldPos.y = In.vTexUV.y * -2.f + 1.f;
	vWorldPos.z = vDepthDesc.x;
	vWorldPos.w = 1.f;

	vWorldPos = vWorldPos * fViewZ;

	vWorldPos = mul(vWorldPos, g_ProjMatrixInv);
	vWorldPos = mul(vWorldPos, g_ViewMatrixInv);

	vector			vLook = vWorldPos - g_vCamPosition;

	Out.vSpecular = pow(saturate(dot(normalize(vReflect) * -1.f, normalize(vLook))), g_fPower) * (g_vLightSpecular * g_vMtrlSpecular);

	return Out;
}

PS_OUT_LIGHT PS_MAIN_LIGHT_POINT(PS_IN In)


{
	PS_OUT_LIGHT		Out = (PS_OUT_LIGHT)0;

	vector			vNormalDesc = g_NormalTexture.Sample(DefaultSampler, In.vTexUV);
	vector			vDepthDesc = g_DepthTexture.Sample(DefaultSampler, In.vTexUV);
	float			fViewZ = vDepthDesc.y * 300.f;

	vector			vNormal = vector(vNormalDesc.xyz * 2.f - 1.f, 0.f);

	vector			vWorldPos;
	vWorldPos.x = In.vTexUV.x * 2.f - 1.f;
	vWorldPos.y = In.vTexUV.y * -2.f + 1.f;
	vWorldPos.z = vDepthDesc.x;
	vWorldPos.w = 1.f;

	vWorldPos = vWorldPos * fViewZ;

	vWorldPos = mul(vWorldPos, g_ProjMatrixInv);
	vWorldPos = mul(vWorldPos, g_ViewMatrixInv);

	vector			vLightDir = vWorldPos - g_vLightPos;
	float			fDistance = length(vLightDir);

	float			fAtt = max((g_fRange - fDistance) / g_fRange, 0.f);

	Out.vShade = g_vLightDiffuse * (saturate(dot(normalize(vLightDir) * -1.f, vNormal)) + (g_vLightAmbient * g_vMtrlAmbient)) * fAtt * 0.5f;
	Out.vShade.a = 1.f;

	vector			vReflect = reflect(normalize(vLightDir), vNormal);

	vector			vLook = vWorldPos - g_vCamPosition;

	Out.vSpecular = pow(saturate(dot(normalize(vReflect) * -1.f, normalize(vLook))), g_fPower) * (g_vLightSpecular * g_vMtrlSpecular) * fAtt;

	return Out;
}

PS_OUT_DEF PS_MAIN_DEFERRED(PS_IN In)
{
	PS_OUT_DEF		Out = (PS_OUT_DEF)0;

	vector			vDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector			vShade = g_ShadeTexture.Sample(DefaultSampler, In.vTexUV);
	vector			vSpecular = g_SpecularTexture.Sample(DefaultSampler, In.vTexUV);
	vector			vDepthDesc = g_DepthTexture.Sample(DefaultSampler, In.vTexUV);
	float			fViewZ = vDepthDesc.y* 300.f;

	Out.vColor = vDiffuse * vShade /* + vSpecular*/;

	vector			vWorldPos;
	vWorldPos.x = In.vTexUV.x * 2.f - 1.f;
	vWorldPos.y = In.vTexUV.y * -2.f + 1.f;
	vWorldPos.z = vDepthDesc.x;
	vWorldPos.w = 1.f;

	vWorldPos = vWorldPos * fViewZ;

	vWorldPos = mul(vWorldPos, g_ProjMatrixInv);
	vWorldPos = mul(vWorldPos, g_ViewMatrixInv);

	if (vDiffuse.a != 0.f && vWorldPos.y < 0.f)
		Out.vHeight = vector(-vWorldPos.y/20.f, -vWorldPos.y / 20.f, -vWorldPos.y / 20.f, 1.f);
	else
		Out.vHeight = vector(0.f, 0.f, 0.f, 0.f);

	vWorldPos = mul(vWorldPos, g_matLightView);
	vWorldPos = mul(vWorldPos, g_matLightProj);
	float2		vNewUV;

	vNewUV.x = (vWorldPos.x / vWorldPos.w) * 0.5f + 0.5f;
	vNewUV.y = (vWorldPos.y / vWorldPos.w) * -0.5f + 0.5f;

	vector		vShadowDepthInfo = g_LightDepthTexture.Sample(ShadowDepthSampler, vNewUV);
	if ((vWorldPos.z / vWorldPos.w) - 0.001f > vShadowDepthInfo.r)
		Out.vShadow = vector(0.5f, 0.5f, 0.5f, 1.f);

	return Out;
}

PS_OUT_DEF PS_MAIN_DEFERRED_FOG(PS_IN In)
{
	PS_OUT_DEF		Out = (PS_OUT_DEF)0;

	vector			vDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector			vShade = g_ShadeTexture.Sample(DefaultSampler, In.vTexUV);
	vector			vSpecular = g_SpecularTexture.Sample(DefaultSampler, In.vTexUV);
	vector			vDepthDesc = g_DepthTexture.Sample(DefaultSampler, In.vTexUV);
	float			fViewZ = vDepthDesc.y* 300.f;

	Out.vColor = vDiffuse * vShade /* + vSpecular*/;

	vector			vWorldPos;
	vWorldPos.x = In.vTexUV.x * 2.f - 1.f;
	vWorldPos.y = In.vTexUV.y * -2.f + 1.f;
	vWorldPos.z = vDepthDesc.x;
	vWorldPos.w = 1.f;

	vWorldPos = vWorldPos * fViewZ;

	vWorldPos = mul(vWorldPos, g_ProjMatrixInv);
	vWorldPos = mul(vWorldPos, g_ViewMatrixInv);

	if (vDiffuse.a != 0.f && vWorldPos.y < 0.f)
		Out.vHeight = vector(-vWorldPos.y / 20.f, -vWorldPos.y / 20.f, -vWorldPos.y / 20.f, 1.f);
	else
		Out.vHeight = vector(0.f, 0.f, 0.f, 0.f);

	vWorldPos = mul(vWorldPos, g_matLightView);
	vWorldPos = mul(vWorldPos, g_matLightProj);
	float2		vNewUV;

	vNewUV.x = (vWorldPos.x / vWorldPos.w) * 0.5f + 0.5f;
	vNewUV.y = (vWorldPos.y / vWorldPos.w) * -0.5f + 0.5f;

	vector		vShadowDepthInfo = g_LightDepthTexture.Sample(ShadowDepthSampler, vNewUV);
	if ((vWorldPos.z / vWorldPos.w) - 0.001f > vShadowDepthInfo.r)
		Out.vShadow = vector(0.5f, 0.5f, 0.5f, 1.f);

	vector fogColor = vector(0.1372f, 0.1764f, 0.2470f, 1.f);
	float fogfactor = 1.0 / pow(2.71828, vDepthDesc.x * fViewZ * 0.05);
	if (Out.vColor.a != 0)
		Out.vColor = Out.vColor*fogfactor + (1.0 - fogfactor) * fogColor;


	return Out;
}

PS_OUT_DEF PS_MAIN_DEFERRED_HEAT(PS_IN In)
{
	PS_OUT_DEF		Out = (PS_OUT_DEF)0;

	vector			vDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector			vDepthDesc = g_DepthTexture.Sample(DefaultSampler, In.vTexUV);
	float			fViewZ = vDepthDesc.y* 300.f;

	vector			vWorldPos;
	vWorldPos.x = In.vTexUV.x * 2.f - 1.f;
	vWorldPos.y = In.vTexUV.y * -2.f + 1.f;
	vWorldPos.z = vDepthDesc.x;
	vWorldPos.w = 1.f;

	vWorldPos = vWorldPos * fViewZ;

	vWorldPos = mul(vWorldPos, g_ProjMatrixInv);
	vWorldPos = mul(vWorldPos, g_ViewMatrixInv);

	if (vDiffuse.a != 0.f && vWorldPos.y < 0.f)
		Out.vHeight = vector(-vWorldPos.y / 20.f, -vWorldPos.y / 20.f, -vWorldPos.y / 20.f, 1.f);
	else
		Out.vHeight = vector(0.f, 0.f, 0.f, 0.f);

	
	vector			vShade = g_ShadeTexture.Sample(DefaultSampler, In.vTexUV);
	vector			vSpecular = g_SpecularTexture.Sample(DefaultSampler, In.vTexUV);
	Out.vColor = vDiffuse * vShade /* + vSpecular*/;

	vector fogColor = vector(0.6f, 0.f, 0.f, 1.f);
	float fogfactor = 1.f;
	if (vWorldPos.y < 0.f)
		fogfactor = 1.0 / pow(2.71828, (-vWorldPos.y)* 0.1f);

	vWorldPos = mul(vWorldPos, g_matLightView);
	vWorldPos = mul(vWorldPos, g_matLightProj);
	float2		vNewUV;

	vNewUV.x = (vWorldPos.x / vWorldPos.w) * 0.5f + 0.5f;
	vNewUV.y = (vWorldPos.y / vWorldPos.w) * -0.5f + 0.5f;

	vector		vShadowDepthInfo = g_LightDepthTexture.Sample(ShadowDepthSampler, vNewUV);
	if ((vWorldPos.z / vWorldPos.w) - 0.001f > vShadowDepthInfo.r)
		Out.vShadow = vector(0.5f, 0.5f, 0.5f, 1.f);


	if (Out.vColor.a != 0)
		Out.vColor = Out.vColor*fogfactor + (1.0 - fogfactor) * fogColor;


	return Out;
}

PS_OUT PS_MAIN_WBLUR(PS_IN_WBLUR2 In)
{
	float weight0, weight1, weight2, weight3, weight4, weight5, weight6;
	float normalization;

	PS_OUT			Out = (PS_OUT)0;

	Out.vColor = vector(0.0f, 0.0f, 0.0f, 0.0f);

	// 각 픽셀의 기여도에 해당하는 가중치를 정합니다.
	weight0 = 1.0f;
	weight1 = 0.9f;
	weight2 = 0.75f;
	weight3 = 0.55f;
	weight4 = 0.28f;
	weight5 = 0.1f;
	weight6 = 0.08f;
	//weight0 = 0.199471f;
	//weight1 = 0.176033f;
	//weight2 = 0.120985f;
	//weight3 = 0.064759f;
	//weight4 = 0.026995f;

	// 가중치들을 살짝 평균내어 정규화 값을 만듭니다.
	normalization = (weight0 + 0.9f * (weight1 + weight2 + weight3 + weight4 + weight5 + weight6));

	// 가중치들을 정규화합니다.
	weight0 = weight0 / normalization;
	weight1 = weight1 / normalization;
	weight2 = weight2 / normalization;
	weight3 = weight3 / normalization;
	weight4 = weight4 / normalization;
	weight5 = weight5 / normalization;
	weight6 = weight6 / normalization;

	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vWPos1) * weight6;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vWPos2) * weight5;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vWPos3) * weight4;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vWPos4) * weight3;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vWPos5) * weight2;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vWPos6) * weight1;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vWPos7) * weight0;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vWPos8) * weight1;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vWPos9) * weight2;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vWPos10) * weight3;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vWPos11) * weight4;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vWPos12) * weight5;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vWPos13) * weight6;

	if (Out.vColor.a != 0)
		Out.vColor.rgb /= Out.vColor.a;

	return Out;
}

PS_OUT PS_MAIN_WBLUR_BLOOM(PS_IN_WBLUR In)
{
	float weight0, weight1, weight2, weight3, weight4;
	float normalization;

	PS_OUT			Out = (PS_OUT)0;

	Out.vColor = vector(0.0f, 0.0f, 0.0f, 0.0f);

	vector OriginColor = g_Texture.Sample(DefaultSampler, In.vWPos5);

	// 각 픽셀의 기여도에 해당하는 가중치를 정합니다.
	//weight0 = 1.0f;
	//weight1 = 0.9f;
	//weight2 = 0.55f;
	//weight3 = 0.18f;
	//weight4 = 0.1f;

	weight0 = 1.0f;
	weight1 = 0.4f;
	weight2 = 0.2f;
	weight3 = 0.1f;
	weight4 = 0.0f;

	// 가중치들을 살짝 평균내어 정규화 값을 만듭니다.
	normalization = (weight0 + 1.f * (weight1 + weight2 + weight3 + weight4));

	// 가중치들을 정규화합니다.
	weight0 = weight0 / normalization;
	weight1 = weight1 / normalization;
	weight2 = weight2 / normalization;
	weight3 = weight3 / normalization;
	weight4 = weight4 / normalization;

	Out.vColor += g_Texture.Sample(DefaultSampler, In.vWPos1) * weight4;
	Out.vColor += g_Texture.Sample(DefaultSampler, In.vWPos2) * weight3;
	Out.vColor += g_Texture.Sample(DefaultSampler, In.vWPos3) * weight2;
	Out.vColor += g_Texture.Sample(DefaultSampler, In.vWPos4) * weight1;
	Out.vColor += g_Texture.Sample(DefaultSampler, In.vWPos5) * weight0;
	Out.vColor += g_Texture.Sample(DefaultSampler, In.vWPos6) * weight1;
	Out.vColor += g_Texture.Sample(DefaultSampler, In.vWPos7) * weight2;
	Out.vColor += g_Texture.Sample(DefaultSampler, In.vWPos8) * weight3;
	Out.vColor += g_Texture.Sample(DefaultSampler, In.vWPos9) * weight4;

	if (Out.vColor.a != 0)
		Out.vColor.rgb /= Out.vColor.a;

	return Out;
}

PS_OUT PS_MAIN_HBLUR_GLOW(PS_IN_HBLUR In)
{
	float weight0, weight1, weight2, weight3, weight4;
	float normalization;

	PS_OUT			Out = (PS_OUT)0;
	Out.vColor = vector(0.0f, 0.0f, 0.0f, 0.0f);

	// 각 픽셀의 기여도에 해당하는 가중치를 정합니다.
	//weight0 = 1.0f;
	//weight1 = 0.9f;
	//weight2 = 0.55f;
	//weight3 = 0.18f;
	//weight4 = 0.1f;

	weight0 = 1.0f;
	weight1 = 0.4f;
	weight2 = 0.2f;
	weight3 = 0.1f;
	weight4 = 0.0f;

	// 가중치들을 살짝 평균내어 정규화 값을 만듭니다.
	normalization = (weight0 + 1.f * (weight1 + weight2 + weight3 + weight4));

	// 가중치들을 정규화합니다.
	weight0 = weight0 / normalization;
	weight1 = weight1 / normalization;
	weight2 = weight2 / normalization;
	weight3 = weight3 / normalization;
	weight4 = weight4 / normalization;

	Out.vColor += g_Texture.Sample(DefaultSampler, In.vHPos1) * weight4;
	Out.vColor += g_Texture.Sample(DefaultSampler, In.vHPos2) * weight3;
	Out.vColor += g_Texture.Sample(DefaultSampler, In.vHPos3) * weight2;
	Out.vColor += g_Texture.Sample(DefaultSampler, In.vHPos4) * weight1;
	Out.vColor += g_Texture.Sample(DefaultSampler, In.vHPos5) * weight0;
	Out.vColor += g_Texture.Sample(DefaultSampler, In.vHPos6) * weight1;
	Out.vColor += g_Texture.Sample(DefaultSampler, In.vHPos7) * weight2;
	Out.vColor += g_Texture.Sample(DefaultSampler, In.vHPos8) * weight3;
	Out.vColor += g_Texture.Sample(DefaultSampler, In.vHPos9) * weight4;

	if (Out.vColor.a != 0)
		Out.vColor.rgb /= Out.vColor.a;

	/*vector vDiffuseColor = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	Out.vColor = saturate(Out.vColor + (vDiffuseColor* 1.f)*(1.f - Out.vColor.a));*/

	return Out;
}



PS_OUT PS_MAIN_DOWN_HBLUR_GLOW(PS_IN_HBLUR2 In)
{
	float weight0, weight1, weight2, weight3, weight4, weight5, weight6;
	float normalization;

	PS_OUT			Out = (PS_OUT)0;
	Out.vColor = vector(0.0f, 0.0f, 0.0f, 0.0f);
	vector Diffuse = g_Texture.Sample(DefaultSampler, In.vHPos5);

	// 각 픽셀의 기여도에 해당하는 가중치를 정합니다.
	weight0 = 1.0f;
	weight1 = 0.9f;
	weight2 = 0.75f;
	weight3 = 0.55f;
	weight4 = 0.28f;
	weight5 = 0.1f;
	weight6 = 0.08f;
	//weight0 = 0.199471f;
	//weight1 = 0.176033f;
	//weight2 = 0.120985f;
	//weight3 = 0.064759f;
	//weight4 = 0.026995f;

	// 가중치들을 살짝 평균내어 정규화 값을 만듭니다.
	normalization = (weight0 + 0.9f * (weight1 + weight2 + weight3 + weight4 + weight5 + weight6));

	// 가중치들을 정규화합니다.
	weight0 = weight0 / normalization;
	weight1 = weight1 / normalization;
	weight2 = weight2 / normalization;
	weight3 = weight3 / normalization;
	weight4 = weight4 / normalization;
	weight5 = weight5 / normalization;
	weight6 = weight6 / normalization;

	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vHPos1) * weight6;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vHPos2) * weight5;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vHPos3) * weight4;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vHPos4) * weight3;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vHPos5) * weight2;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vHPos6) * weight1;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vHPos7) * weight0;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vHPos8) * weight1;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vHPos9) * weight2;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vHPos10) * weight3;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vHPos11) * weight4;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vHPos12) * weight5;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vHPos13) * weight6;

	Out.vColor.rgb /= Out.vColor.a;

	vector vGlowColor = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV * 2);
	Out.vColor.a = Out.vColor.a*(1.f - (Out.vColor.a / 5.f))*0.5f;
	Out.vColor = saturate(Out.vColor + (vGlowColor* 0.5f));

	return Out;
}

PS_OUT PS_MAIN_DOWN_HBLUR_NOTGLOW(PS_IN_HBLUR2 In)
{
	float weight0, weight1, weight2, weight3, weight4, weight5, weight6;
	float normalization;

	PS_OUT			Out = (PS_OUT)0;
	Out.vColor = vector(0.0f, 0.0f, 0.0f, 0.0f);
	vector Diffuse = g_Texture.Sample(DefaultSampler, In.vHPos5);

	// 각 픽셀의 기여도에 해당하는 가중치를 정합니다.
	weight0 = 1.0f;
	weight1 = 0.9f;
	weight2 = 0.75f;
	weight3 = 0.55f;
	weight4 = 0.28f;
	weight5 = 0.1f;
	weight6 = 0.08f;
	//weight0 = 0.199471f;
	//weight1 = 0.176033f;
	//weight2 = 0.120985f;
	//weight3 = 0.064759f;
	//weight4 = 0.026995f;

	// 가중치들을 살짝 평균내어 정규화 값을 만듭니다.
	normalization = (weight0 + 0.9f * (weight1 + weight2 + weight3 + weight4 + weight5 + weight6));

	// 가중치들을 정규화합니다.
	weight0 = weight0 / normalization;
	weight1 = weight1 / normalization;
	weight2 = weight2 / normalization;
	weight3 = weight3 / normalization;
	weight4 = weight4 / normalization;
	weight5 = weight5 / normalization;
	weight6 = weight6 / normalization;

	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vHPos1) * weight6;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vHPos2) * weight5;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vHPos3) * weight4;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vHPos4) * weight3;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vHPos5) * weight2;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vHPos6) * weight1;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vHPos7) * weight0;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vHPos8) * weight1;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vHPos9) * weight2;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vHPos10) * weight3;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vHPos11) * weight4;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vHPos12) * weight5;
	Out.vColor += g_Texture.Sample(ShadowDepthSampler, In.vHPos13) * weight6;

	Out.vColor.rgb /= Out.vColor.a;

	return Out;
}

PS_OUT_BLUR PS_MAIN_EMISSIVEACC(PS_IN In)
{
	PS_OUT_BLUR			Out = (PS_OUT_BLUR)0;

	vector vEmissive = g_EmissiveTexture.Sample(DefaultSampler, In.vTexUV);
	vector vEmissiveGlow = g_EmissiveGlowTexture.Sample(DefaultSampler, In.vTexUV);
	vector vNonLightEmissive = g_NonLightEmissiveTexture.Sample(DefaultSampler, In.vTexUV);
	vector vNonLightEmissiveGlow = g_NonLightEmissiveGlowTexture.Sample(DefaultSampler, In.vTexUV);
	vector vNonLightBlur = g_NonLightBlurTexture.Sample(DefaultSampler, In.vTexUV);
	vector vNonLightGlow = g_NonLightGlowTexture.Sample(DefaultSampler, In.vTexUV);


	Out.vColor = vEmissive;

	if (vNonLightEmissive.a != 0.f)
		Out.vColor = vNonLightEmissive;

	if (vNonLightBlur.a != 0.f)
		Out.vColor = vNonLightBlur;

	Out.vGlow = vEmissiveGlow;

	if (vNonLightEmissiveGlow.a != 0.f)
		Out.vGlow = vNonLightEmissiveGlow;

	if (vNonLightGlow.a != 0.f)
		Out.vGlow = vNonLightGlow;

	return Out;
}

PS_OUT PS_MAIN_MERGE(PS_IN In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector vDiffuseColor = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector vNonLightColor = g_NonLightTexture.Sample(DefaultSampler, In.vTexUV);
	vector vAlphaBlendColor = g_AlphaBlendTexture.Sample(DefaultSampler, In.vTexUV);
	vector vBlurColor = g_BlurTexture.Sample(DefaultSampler, In.vTexUV / 2);
	vector vShadowColor = g_ShadowTexture.Sample(DefaultSampler, In.vTexUV / 2);

	Out.vColor = vDiffuseColor;
	if (vShadowColor.a != 0.f)
		Out.vColor = saturate(Out.vColor*vector((1.f - vShadowColor.a*0.5f), (1.f - vShadowColor.a*0.5f), (1.f - vShadowColor.a*0.5f), 1.f));

	Out.vColor = saturate(Out.vColor*(1.f - vAlphaBlendColor.a) + (vAlphaBlendColor));

	if (vNonLightColor.a != 0.f)
		Out.vColor = vNonLightColor;

	Out.vColor = saturate(Out.vColor*(1.f - vBlurColor.a) + (vBlurColor));


	return Out;
}

PS_OUT PS_MAIN_MERGE_HAZE(PS_IN In)
{
	PS_OUT			Out = (PS_OUT)0;

	float2 NewUV = In.vTexUV;	
	float fWeight = 0.f;
	NewUV.y += g_HazeTime;
	vector Distortion = g_NoiseTexture.Sample(DefaultSampler, NewUV);
	vector vHeight = g_HeightTexture.Sample(DefaultSampler, In.vTexUV);
	fWeight = Distortion.r * 0.05f*(pow(2.f, -0.05 * vHeight.x *20.f) - 1.f);

	vector vDiffuseColor = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV + fWeight);
	vector vNonLightColor = g_NonLightTexture.Sample(DefaultSampler, In.vTexUV);
	vector vAlphaBlendColor = g_AlphaBlendTexture.Sample(DefaultSampler, In.vTexUV);
	vector vBlurColor = g_BlurTexture.Sample(DefaultSampler, In.vTexUV / 2);
	vector vShadowColor = g_ShadowTexture.Sample(DefaultSampler, In.vTexUV / 2);
	

	Out.vColor = vDiffuseColor;
	if (vShadowColor.a != 0.f)
		Out.vColor = saturate(Out.vColor*vector((1.f - vShadowColor.a*0.5f), (1.f - vShadowColor.a*0.5f), (1.f - vShadowColor.a*0.5f), 1.f));

	Out.vColor = saturate(Out.vColor*(1.f - vAlphaBlendColor.a) + (vAlphaBlendColor));

	if (vNonLightColor.a != 0.f)
		Out.vColor = vNonLightColor;

	Out.vColor = saturate(Out.vColor*(1.f - vBlurColor.a) + (vBlurColor));


	return Out;
}

PS_OUT PS_MAIN_LIGHTDEBUG(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);
	Out.vColor.gb = Out.vColor.r;
	Out.vColor.a = 1.f;

	return Out;
}

PS_OUT PS_MAIN_FINAL(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	vector			vPriority = g_Texture.Sample(DefaultSampler, In.vTexUV);

	vector			vMask = g_MaskingTexture.Sample(DefaultSampler, In.vTexUV);

	float fWeight = 0.f;

	if (vMask.a != 0.f) {
		vector			vDist = g_DistortionTexture.Sample(DefaultSampler, In.vTexUV);
		fWeight = vDist.r * 0.05f * vMask.a;
	}

	vector			vMerge = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV + fWeight);

	Out.vColor = saturate(vPriority*(1 - vMerge.a) + (vMerge));

	//LUT
	Out.vColor = float4(Get_LutColor(Out.vColor.rgb, g_LUTSam), Out.vColor.a);



	return Out;
}

PS_OUT PS_MAIN_FINAL_NOEFFECT(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	return Out;
}

PS_OUT PS_MAIN_FINAL_RADIAL(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	float focusPower = 10.0 * ((-2.f / 0.0225f)*pow(g_RadialTime - 0.15, 2) + 2.f);
	int focusDetail = 7;

	float2  focus = In.vTexUV - float2(0.5f, 0.5f);

	vector outColor;
	outColor = vector(0, 0, 0, 1);

	for (int i = 0; i<focusDetail; i++) {
		float power = 1.0 - focusPower * (1.0 / 1280.0) * float(i);
		outColor.rgb += g_Texture.Sample(DefaultSampler, focus * power + float2(0.5f, 0.5f)).rgb;
	}

	outColor.rgb *= 1.0 / float(focusDetail);
	Out.vColor.rgb = outColor.rgb;

	return Out;
}

PS_OUT PS_MAIN_FINAL_WATCH(PS_IN In)
{
	PS_OUT			Out;

	vector Distortion = g_WatchTexture.Sample(DefaultSampler, In.vTexUV);
	float fWeight = 0.f;
	fWeight = Distortion.r * 0.03f;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV + fWeight);
	Out.vColor += vector(0.f, 0.f, 0.2f, 0.f);

	return Out;
}

PS_OUT PS_MAIN_FINAL_HAZE(PS_IN In)
{
	PS_OUT			Out;
	float2 NewUV = In.vTexUV;
	vector Distortion;
	float fWeightX = 0.f;
	float fWeightY = 0.f;
	if (NewUV.y >= 0.8f) {
		NewUV.y += g_HazeTime;
		Distortion = g_NoiseTexture.Sample(DefaultSampler, NewUV);
		fWeightY = 0.f;
		fWeightY = Distortion.r * 0.05f*pow(In.vTexUV.y, 50);
	}
	else if (NewUV.y <= 0.2f) {
		NewUV.y -= g_HazeTime;
		Distortion = g_NoiseTexture.Sample(DefaultSampler, NewUV);
		fWeightY = 0.f;
		fWeightY = Distortion.r * 0.05f*pow(1.f - In.vTexUV.y, 50);
	}

	if (NewUV.x >= 0.8f) {
		NewUV.x += g_HazeTime;
		Distortion = g_NoiseTexture.Sample(DefaultSampler, NewUV);
		fWeightX = 0.f;
		fWeightX = Distortion.r * 0.05f*pow(In.vTexUV.x, 50);
	}
	else if (NewUV.x <= 0.2f) {
		NewUV.x -= g_HazeTime;
		Distortion = g_NoiseTexture.Sample(DefaultSampler, NewUV);
		fWeightX = 0.f;
		fWeightX = Distortion.r * 0.05f*pow(1.f - In.vTexUV.x, 50);
	}

	Out.vColor = g_Texture.Sample(DefaultSampler, float2(In.vTexUV.x + fWeightX, In.vTexUV.y + fWeightY));
	return Out;
}


PS_OUT PS_MAIN_FINAL_OPENUI(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	float focusPower = 15.0;
	int focusDetail = 7;

	float2  focus = In.vTexUV - float2(0.5f, 0.5f);

	vector outColor;
	outColor = vector(0, 0, 0, 1);

	for (int i = 0; i<focusDetail; i++) {
		float power = 1.0 - focusPower * (1.0 / 1280.0) * float(i);
		outColor.rgb += g_Texture.Sample(DefaultSampler, focus * power + float2(0.5f, 0.5f)).rgb;
	}

	outColor.rgb *= 1.0 / float(focusDetail);
	Out.vColor.rgb = outColor.rgb;

	return Out;
}

RasterizerState	RS_Default
{
	FillMode = Solid;
	FrontCounterClockwise = false;
	CullMode = back;
};

BlendState BS_NonBlend
{
	BlendEnable[0] = false;
	BlendEnable[1] = false;
};

BlendState BS_LightBlend
{
	BlendEnable[0] = true;
	BlendEnable[1] = true;
	SrcBlend = one;
	DestBlend = one;
	Blendop = add;

	/*BlendEnable[0] = true;
	SrcBlend[0] = one;
	DestBlend[0] = one;
	Blendop[0] = add;*/

	//BlendEnable[1] = true;
	//SrcBlend[1] = one;
	//DestBlend[1] = one;
	//Blendop[1] = add;

};

BlendState BS_AlphaBlend
{
	BlendEnable[0] = true;
	SrcBlend[0] = Src_Alpha;
	DestBlend[0] = Inv_Src_Alpha;
	BlendOp[0] = Add;
	SrcBlendAlpha[0] = One;
	DestBlendAlpha[0] = Zero;
	BlendOpAlpha[0] = Add;

};

DepthStencilState DSS_Default
{
	DepthEnable = true;
	DepthWriteMask = all;
	DepthFunc = less_equal;
};

DepthStencilState DSS_NonZTestAndWrite
{
	DepthEnable = false;
	DepthWriteMask = zero;
};

technique11 DefaultTechnique
{

	pass Debug_RenderTarget //0
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_DEBUG();
	}

	pass Light_Directional //1
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_LIGHT_DIRECTIONAL();
	}

	pass Light_Point //2
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_LightBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_LIGHT_POINT();
	}

	pass DeferredAcc //3
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_DEFERRED();
	}

	pass DownAndWBlur //4
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_WBLUR_AND_DOWNSAMPLING();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_WBLUR();
	}

	pass DownAndHBlurAndGlow //5
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_HBLUR_AND_DOWNSAMPLING();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_DOWN_HBLUR_GLOW();
	}

	pass Merge //6
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MERGE();
	}

	pass WBlurAndBloom //7
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_WBLUR();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_WBLUR_BLOOM();
	}

	pass HBlurAndGlow //8
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_HBLUR();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_HBLUR_GLOW();
	}

	pass Final //9
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_FINAL();
	}

	pass Final_NoEffect //10
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_FINAL_NOEFFECT();
	}

	pass Final_Radial //11
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_FINAL_RADIAL();
	}

	pass EmissiveACC //12
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_EMISSIVEACC();
	}

	pass DeferredAcc_Fog //13
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_DEFERRED_FOG();
	}

	pass Final_Watch //14
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_FINAL_WATCH();
	}

	pass Final_OpenUI //15
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_FINAL_OPENUI();
	}

	pass Final_Haze //16
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_FINAL_HAZE();
	}

	pass DeferredAcc_Heat //17
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_DEFERRED_HEAT();
	}

	pass DownAndHBlurAndNotGlow //18
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_HBLUR_AND_DOWNSAMPLING();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_DOWN_HBLUR_NOTGLOW();
	}

	pass MergeH //19
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_MERGE_HAZE();
	}
}
