#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"

struct VertexInput
{
	float4 pos : POSITION;
	float2 uv : UV;
	
	matrix transform : INSTANCE_TRANSFORM;
};

struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

PixelInput VS(VertexInput input)
{
	PixelInput output;
	output.pos = mul(input.pos, input.transform);
	output.pos = mul(output.pos, world);
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);

	output.uv = input.uv;
	
	return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
	return diffuseMap.Sample(samp, input.uv) * mDiffuse;
}