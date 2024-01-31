#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"

LightPixelInput VS(VertexUVNormalTangentBlend input)
{
	LightPixelInput output;
	matrix transform;
	
	[branch]
	if (animType)
		transform = mul(SkinWorld(input.indices, input.weights), world);
	else
		transform = world;
	
	output.pos = mul(input.pos, transform);
	
	output.viewPos = invView._41_42_43;
	output.worldPos = output.pos;
	
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);

	output.uv = input.uv;
	
	output.normal = mul(input.normal, (float3x3) transform);
	output.tangent = mul(input.tangent, (float3x3) transform);
	output.binormal = cross(output.normal, output.tangent);
	
	return output;
}

cbuffer FogBuffer : register(b10)
{
	float4 fogColor;
	float fogStart;
	float fogRandom;
}

float4 PS(LightPixelInput input) : SV_TARGET
{
	float fogFactor = saturate((input.pos.z - fogStart) / fogRandom);
	float4 color = CalcLights(input);
	
	return lerp(fogColor, color, fogFactor);

}