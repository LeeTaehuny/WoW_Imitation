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

float4 PS(LightPixelInput input) : SV_TARGET
{
	Material material = GetMaterial(input);

	float4 ambient = CalcAmbient(material);

	float3 toLight = normalize(lights[0].direction);
	
	float diffuseIntensity = saturate(dot(material.normal, -toLight));
	float4 finalColor = lights[0].color * diffuseIntensity * mDiffuse + 0.25f;

	return diffuseMap.Sample(samp, input.uv) * finalColor;
}