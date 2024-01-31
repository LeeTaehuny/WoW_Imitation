#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"

struct PixelInput
{
	float4 pos : SV_Position;
};

PixelInput VS(VertexUVNormalTangentBlend input)
{
	PixelInput output;
	
	matrix transform;
	
	[branch]
	if(animType)
		transform = mul(SkinWorld(input.indices, input.weights), world);
	else
		transform = world;
	
	output.pos = mul(input.pos, transform);
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);
	
	return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
	float depth = input.pos.z / input.pos.w;
	
	return float4(depth.xxx, 1);
}