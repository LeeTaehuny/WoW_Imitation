#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"

struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
	float4 refractionPos : POSITION;
};

PixelInput VS(VertexUV input)
{
	PixelInput output;
	output.pos = mul(input.pos, world);
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);
	
	output.uv = input.uv;
	output.refractionPos = output.pos;
	
	return output;
}

Texture2D refractionMap : register(t11);
Texture2D refractionNormalMap : register(t12);

cbuffer WaterBuffer : register(b10)
{
	float4 color;
	
	float time;
	float speed;
	float wave;
}

float4 PS(PixelInput input) : SV_TARGET
{
	float4 refPos = input.refractionPos;
	
	float2 uv;
	uv.x = refPos.x / refPos.w * 0.5f + 0.5f;
	uv.y = -refPos.y / refPos.w * 0.5f + 0.5f;
	
	input.uv += time * speed;
	
	float4 normal = refractionNormalMap.Sample(samp, input.uv) * 2.0f - 1.0f;
	uv += normal.xy * wave;
	
	return refractionMap.Sample(samp, uv) * color;
}