#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"

VertexUV VS(VertexUV input)
{
	input.pos = mul(input.pos, world);
	
	return input;
}

struct CHullOutput
{
	float edgeTessFactor[4] : SV_TessFactor;
	float insideTessFactor[2] : SV_InsideTessFactor;
};

#define NUM_CONTROL_POINTS 4

cbuffer TerrainBuffer : register(b10)
{
	float minDistance;
	float maxDistance;
	float minQuality;
	float maxQuality;
}

float CalcTessFactor(float3 pos)
{
	float d = distance(pos, invView._41_42_43);
	float f = saturate((d - maxDistance) / (minDistance - maxDistance));

	return lerp(minQuality, maxQuality, f);
}

CHullOutput CHS(InputPatch<VertexUV, NUM_CONTROL_POINTS> input)
{
	CHullOutput output;

	float3 e0 = (input[0].pos + input[2].pos).xyz * 0.5f;
	float3 e1 = (input[0].pos + input[1].pos).xyz * 0.5f;
	float3 e2 = (input[1].pos + input[3].pos).xyz * 0.5f;
	float3 e3 = (input[2].pos + input[3].pos).xyz * 0.5f;
	
	output.edgeTessFactor[0] = CalcTessFactor(e0);
	output.edgeTessFactor[1] = CalcTessFactor(e1);
	output.edgeTessFactor[2] = CalcTessFactor(e2);
	output.edgeTessFactor[3] = CalcTessFactor(e3);
	
	float3 center = (e0 + e2) * 0.5f;
	
	output.insideTessFactor[0] = CalcTessFactor(center);
	output.insideTessFactor[1] = CalcTessFactor(center);

	return output;
}

struct HullOutput
{
	float4 pos : POSITION;
	float2 uv : UV;
};

[domain("quad")]
[partitioning("integer")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(4)]
[patchconstantfunc("CHS")]
HullOutput HS(InputPatch<VertexUV, NUM_CONTROL_POINTS> input, uint i : SV_OutputControlPointID)
{
	HullOutput output;

	output.pos = input[i].pos;
	output.uv = input[i].uv;

	return output;
}

struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

cbuffer HeightBuffer : register(b10)
{
	float heightScale;
}

Texture2D heightMap : register(t0);

[domain("quad")]
PixelInput DS(CHullOutput input, float2 uv : SV_DomainLocation,
	const OutputPatch<HullOutput, NUM_CONTROL_POINTS> patch)
{
	PixelInput output;

	float4 v1 = lerp(patch[0].pos, patch[1].pos, uv.x);
	float4 v2 = lerp(patch[2].pos, patch[3].pos, uv.x);	
	float4 pos = lerp(v1, v2, uv.y);
	
	float2 uv1 = lerp(patch[0].uv, patch[1].uv, uv.x);
	float2 uv2 = lerp(patch[2].uv, patch[3].uv, uv.x);
	float2 texCoord = lerp(uv1, uv2, uv.y);
	
	pos.y = heightMap.SampleLevel(samp, texCoord, 0).r * heightScale;

	output.pos = float4(pos.xyz, 1.0f);
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);
	
	output.uv = texCoord;
	
	return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
	return diffuseMap.Sample(samp, input.uv);
}