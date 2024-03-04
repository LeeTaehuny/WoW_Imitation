#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"

struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

cbuffer ColorBuffer : register(b5)
{
	float4 color;
}

PixelInput VS(VertexUV input)
{
	PixelInput output;
	output.pos = mul(input.pos, world);
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);

	output.uv = input.uv;
	
	return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
	float4 tex = diffuseMap.Sample(samp, input.uv);

	return tex * color;
}