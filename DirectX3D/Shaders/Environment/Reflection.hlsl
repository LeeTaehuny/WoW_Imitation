#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"

struct PixelInput
{
	float4 pos : SV_POSITION;
	float4 reflectionPos : POSITION;
};

cbuffer ReflectionBuffer : register(b10)
{
	matrix reflectionView;
}

PixelInput VS(VertexUV input)
{
	PixelInput output;
	output.pos = mul(input.pos, world);
	
	output.reflectionPos = mul(output.pos, reflectionView);
	output.reflectionPos = mul(output.reflectionPos, projection);
	
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);
	
	return output;
}

Texture2D reflectionMap : register(t10);

float4 PS(PixelInput input) : SV_TARGET
{
	float4 refPos = input.reflectionPos;
	
	float2 uv;
	uv.x = refPos.x / refPos.w * 0.5f + 0.5f;
	uv.y = -refPos.y / refPos.w * 0.5f + 0.5f;
	
	return reflectionMap.Sample(samp, uv);
}