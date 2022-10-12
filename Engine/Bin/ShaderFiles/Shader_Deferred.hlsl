
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
texture2D		g_NonLightTexture;
texture2D		g_AlphaBlendTexture;

texture2D		g_PlayerDistanceTexture;
texture2D		g_DisolveTexture;
int				g_RenderTick;
texture2D			g_LUTTex;

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


VS_OUT_HBLUR VS_DOWN_HBLUR(VS_IN In)
{
	VS_OUT_HBLUR		Out;

	float4		vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;
	Out.vTexUV = In.vTexUV * 4;

	float fWTexelSize = 1.0f / 320;
	float fHTexelSize = 1.0f / 180;

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

VS_OUT VS_DOWNEND(VS_IN In)
{
	VS_OUT		Out;

	float4		vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;
	Out.vTexUV = In.vTexUV / 4;

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

PS_OUT PS_MAIN_DEBUG(PS_IN In)
{
	PS_OUT			Out;

	Out.vColor = g_Texture.Sample(DefaultSampler, In.vTexUV);

	return Out;
}

struct PS_OUT_LIGHT
{
	vector			vShade : SV_TARGET0;
	vector			vSpecular : SV_TARGET1;
};

PS_OUT_LIGHT PS_MAIN_LIGHT_DIRECTIONAL(PS_IN In)
{
	PS_OUT_LIGHT		Out = (PS_OUT_LIGHT)0;

	vector			vNormalDesc = g_NormalTexture.Sample(DefaultSampler, In.vTexUV);
	vector			vDepthDesc = g_DepthTexture.Sample(DefaultSampler, In.vTexUV);
	float			fViewZ = vDepthDesc.y * 300.f;

	vector			vNormal = vector(vNormalDesc.xyz * 2.f - 1.f, 0.f);

	Out.vShade = saturate(dot(normalize(g_vLightDir) * -0.5f, vNormal)) + (g_vLightAmbient * g_vMtrlAmbient);
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

PS_OUT PS_MAIN_BLEND(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	vector			vDiffuse = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV);
	vector			vShade = g_ShadeTexture.Sample(DefaultSampler, In.vTexUV);
	vector			vSpecular = g_SpecularTexture.Sample(DefaultSampler, In.vTexUV);

	Out.vColor = vDiffuse * vShade/* + vSpecular*/;

	if (0.0f == Out.vColor.a)
		discard;

	return Out;
}

PS_OUT PS_MAIN_STAGE_CHANGE(PS_IN In)
{

	PS_OUT			Out = (PS_OUT)0;

	vector vBlurColor = g_Texture.Sample(DefaultSampler, In.vTexUV);
	vector VDiffuseColor = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV * 4);
	vector VNonLightColor = g_NonLightTexture.Sample(DefaultSampler, In.vTexUV * 4);
	vector VAlphaBlendColor = g_AlphaBlendTexture.Sample(DefaultSampler, In.vTexUV * 4);

	if (VNonLightColor.a != 0.f)
		Out.vColor = saturate(VNonLightColor + (vBlurColor)/**0.6f*/);
	else
		Out.vColor = saturate(VDiffuseColor + (vBlurColor)/**0.6f*/);

	vector			vDepthDesc = g_DepthTexture.Sample(DefaultSampler, In.vTexUV * 4);
	float			fViewZ = vDepthDesc.y* 300.f;

	vector			vWorldPos;
	vWorldPos.x = In.vTexUV.x * 4 * 2.f - 1.f;
	vWorldPos.y = In.vTexUV.y * 4 * -2.f + 1.f;
	vWorldPos.z = vDepthDesc.x;
	vWorldPos.w = 1.f;

	vWorldPos = vWorldPos * fViewZ;

	vWorldPos = mul(vWorldPos, g_ProjMatrixInv);
	vWorldPos = mul(vWorldPos, g_ViewMatrixInv);

	vWorldPos = mul(vWorldPos, g_matLightView);
	vWorldPos = mul(vWorldPos, g_matLightProj);
	float2		vNewUV;

	vNewUV.x = (vWorldPos.x / vWorldPos.w) * 0.5f + 0.5f;
	vNewUV.y = (vWorldPos.y / vWorldPos.w) * -0.5f + 0.5f;

	vector		vShadowDepthInfo = g_LightDepthTexture.Sample(ShadowDepthSampler, vNewUV);
	if ((vWorldPos.z / vWorldPos.w) - 0.001f > vShadowDepthInfo.r)
		Out.vColor *= vector(0.3f, 0.3f, 0.3f, 1.f);

	Out.vColor = Out.vColor*(1 - VAlphaBlendColor.a) + (VAlphaBlendColor);

	//LUT
	Out.vColor = float4(Get_LutColor(Out.vColor.rgb, g_LUTSam), Out.vColor.a);

	vector			vPlayerDist = g_PlayerDistanceTexture.Sample(DefaultSampler, In.vTexUV);
	vector			vDissolve = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);

	if (vPlayerDist.x != 0.f) {
		if (g_RenderTick / 255.f <= vPlayerDist.x && g_RenderTick / 255.f <= vDissolve.r)
			discard;
	}

	return Out;
}

PS_OUT PS_MAIN_STAGE_CHANGE_END(PS_IN In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector vBlurColor = g_Texture.Sample(DefaultSampler, In.vTexUV);
	vector VDiffuseColor = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV * 4);
	vector VNonLightColor = g_NonLightTexture.Sample(DefaultSampler, In.vTexUV * 4);
	vector VAlphaBlendColor = g_AlphaBlendTexture.Sample(DefaultSampler, In.vTexUV * 4);

	if (VNonLightColor.a != 0.f)
		Out.vColor = saturate(VNonLightColor + (vBlurColor)/**0.6f*/);
	else
		Out.vColor = saturate(VDiffuseColor + (vBlurColor)/**0.6f*/);

	vector			vDepthDesc = g_DepthTexture.Sample(DefaultSampler, In.vTexUV * 4);
	float			fViewZ = vDepthDesc.y* 300.f;

	vector			vWorldPos;
	vWorldPos.x = In.vTexUV.x * 4 * 2.f - 1.f;
	vWorldPos.y = In.vTexUV.y * 4 * -2.f + 1.f;
	vWorldPos.z = vDepthDesc.x;
	vWorldPos.w = 1.f;

	vWorldPos = vWorldPos * fViewZ;

	vWorldPos = mul(vWorldPos, g_ProjMatrixInv);
	vWorldPos = mul(vWorldPos, g_ViewMatrixInv);

	vWorldPos = mul(vWorldPos, g_matLightView);
	vWorldPos = mul(vWorldPos, g_matLightProj);
	float2		vNewUV;

	vNewUV.x = (vWorldPos.x / vWorldPos.w) * 0.5f + 0.5f;
	vNewUV.y = (vWorldPos.y / vWorldPos.w) * -0.5f + 0.5f;

	vector		vShadowDepthInfo = g_LightDepthTexture.Sample(ShadowDepthSampler, vNewUV);
	if ((vWorldPos.z / vWorldPos.w) - 0.001f > vShadowDepthInfo.r)
		Out.vColor *= vector(0.3f, 0.3f, 0.3f, 1.f);

	Out.vColor = Out.vColor*(1 - VAlphaBlendColor.a) + (VAlphaBlendColor);

	//LUT
	Out.vColor = float4(Get_LutColor(Out.vColor.rgb, g_LUTSam), Out.vColor.a);

	vector			vPlayerDist = g_PlayerDistanceTexture.Sample(DefaultSampler, In.vTexUV);
	vector			vDissolve = g_DisolveTexture.Sample(DefaultSampler, In.vTexUV);

	if (vPlayerDist.x != 0.f) {
		if (g_RenderTick / 255.f <= vPlayerDist.x && g_RenderTick / 255.f <= vDissolve.r)
			discard;
	}


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

PS_OUT PS_MAIN_DOWN_HBLUR(PS_IN_HBLUR In)
{
	float weight0, weight1, weight2, weight3, weight4;
	float normalization;

	PS_OUT			Out = (PS_OUT)0;
	Out.vColor = vector(0.0f, 0.0f, 0.0f, 0.0f);
	vector Diffuse = g_Texture.Sample(DefaultSampler, In.vHPos5);

	// 각 픽셀의 기여도에 해당하는 가중치를 정합니다.
	weight0 = 1.0f;
	weight1 = 0.9f;
	weight2 = 0.55f;
	weight3 = 0.18f;
	weight4 = 0.1f;

	// 가중치들을 살짝 평균내어 정규화 값을 만듭니다.
	normalization = (weight0 + 0.5f * (weight1 + weight2 + weight3 + weight4));

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

	Out.vColor.rgb /= Out.vColor.a;

	//Out.vColor.rgb /= Out.vColor.a;
	return Out;
}

PS_OUT PS_MAIN_WBLUR(PS_IN_WBLUR In)
{
	float weight0, weight1, weight2, weight3, weight4;
	float normalization;

	PS_OUT			Out = (PS_OUT)0;
	
	Out.vColor = vector(0.0f, 0.0f, 0.0f, 0.0f);


	// 각 픽셀의 기여도에 해당하는 가중치를 정합니다.
	weight0 = 1.0f;
	weight1 = 0.9f;
	weight2 = 0.55f;
	weight3 = 0.18f;
	weight4 = 0.1f;

	// 가중치들을 살짝 평균내어 정규화 값을 만듭니다.
	normalization = (weight0 + 0.5f * (weight1 + weight2 + weight3 + weight4));

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

	Out.vColor.rgb /= Out.vColor.a;

	vector VDiffuseColor = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV * 4);

	Out.vColor = saturate(Out.vColor + (VDiffuseColor* 1.f));

	return Out;
}

PS_OUT PS_MAIN_FINAL(PS_IN In)
{
	PS_OUT			Out = (PS_OUT)0;

	vector vBlurColor = g_Texture.Sample(DefaultSampler, In.vTexUV);
	vector VDiffuseColor = g_DiffuseTexture.Sample(DefaultSampler, In.vTexUV * 4);
	vector VNonLightColor = g_NonLightTexture.Sample(DefaultSampler, In.vTexUV * 4);
	vector VAlphaBlendColor = g_AlphaBlendTexture.Sample(DefaultSampler, In.vTexUV * 4);

	Out.vColor = VDiffuseColor;

	vector			vDepthDesc = g_DepthTexture.Sample(DefaultSampler, In.vTexUV * 4);
	float			fViewZ = vDepthDesc.y* 300.f;



	vector			vWorldPos;
	vWorldPos.x = In.vTexUV.x * 4 * 2.f - 1.f;
	vWorldPos.y = In.vTexUV.y * 4 * -2.f + 1.f;
	vWorldPos.z = vDepthDesc.x;
	vWorldPos.w = 1.f;

	vWorldPos = vWorldPos * fViewZ;

	vWorldPos = mul(vWorldPos, g_ProjMatrixInv);
	vWorldPos = mul(vWorldPos, g_ViewMatrixInv);

	vWorldPos = mul(vWorldPos, g_matLightView);
	vWorldPos = mul(vWorldPos, g_matLightProj);
	float2		vNewUV;

	vNewUV.x = (vWorldPos.x / vWorldPos.w) * 0.5f + 0.5f;
	vNewUV.y = (vWorldPos.y / vWorldPos.w) * -0.5f + 0.5f;

	vector		vShadowDepthInfo = g_LightDepthTexture.Sample(ShadowDepthSampler, vNewUV);
	if ((vWorldPos.z / vWorldPos.w) - 0.001f > vShadowDepthInfo.r)
		Out.vColor *= vector(0.5f, 0.5f, 0.5f, 1.f);

	//Out.vColor = saturate(Out.vColor*(1 - VAlphaBlendColor.a) + (VAlphaBlendColor));
	if (VNonLightColor.a != 0.f)
		Out.vColor = saturate(Out.vColor*(1 - VNonLightColor.a) + (VNonLightColor));
	
		Out.vColor = saturate(Out.vColor*(1 - vBlurColor.a) + (vBlurColor));

	//LUT
	Out.vColor = float4(Get_LutColor(Out.vColor.rgb, g_LUTSam), Out.vColor.a);

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

	pass Blend //3
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_BLEND();
	}

	pass Stage_Change //4
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_DOWNEND();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_STAGE_CHANGE();
	}
	pass LightDebug_RenderTarget //5
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_Default, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_LIGHTDEBUG();
	}

	pass DownSamplng //6
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_DOWN_HBLUR();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_DOWN_HBLUR();
	}

	pass DownSamplngTwo //7
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_MAIN_WBLUR();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_WBLUR();
	}

	pass DownSamplngEnd //8
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_AlphaBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_DOWNEND();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_FINAL();
	}

	pass Stage_Change_End //9
	{
		SetRasterizerState(RS_Default);
		SetDepthStencilState(DSS_NonZTestAndWrite, 0);
		SetBlendState(BS_NonBlend, vector(1.f, 1.f, 1.f, 1.f), 0xffffffff);

		VertexShader = compile vs_5_0 VS_DOWNEND();
		GeometryShader = NULL;
		PixelShader = compile ps_5_0 PS_MAIN_STAGE_CHANGE_END();
	}
}
