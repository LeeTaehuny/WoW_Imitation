#include "../VertexHeader.hlsli"

struct PixelInput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
};

PixelInput VS(VertexColor input)
{
	PixelInput output;	
	output.pos = mul(input.pos, world);
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);

	output.color = input.color;
	
	return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
	return input.color;
}