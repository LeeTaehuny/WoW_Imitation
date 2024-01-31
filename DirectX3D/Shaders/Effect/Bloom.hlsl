#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"

struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

PixelInput VS(VertexUV input)
{
	PixelInput output;
	output.pos = mul(input.pos, world);
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);

	output.uv = input.uv;
	
	return output;
}

cbuffer ValueBuffer : register(b10)
{
	float threshold;
	float value;
}

float4 PS(PixelInput input) : SV_TARGET
{
	float4 color = diffuseMap.Sample(samp, input.uv);
	float4 bloom = 0.0f;
	
	if (color.r > threshold || color.g > threshold || color.b > threshold)
	{
		bloom = color - threshold;
		bloom *= value;
	}
	
	return color + bloom;
}