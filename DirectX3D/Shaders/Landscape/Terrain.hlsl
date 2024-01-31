#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"

//Texture2D heightMap : register(b10);

LightPixelInput VS(VertexUVNormalTangent input)
{
	LightPixelInput output;
	
	//float4 height = heightMap.Load(int3(input.pos.x, input.pos.z, 0));
	//input.pos.y = height.x;
	
	output.pos = mul(input.pos, world);
	
	output.viewPos = invView._41_42_43;
	output.worldPos = output.pos;
	
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);

	output.uv = input.uv;
	
	output.normal = mul(input.normal, (float3x3) world);
	output.tangent = mul(input.tangent, (float3x3) world);
	output.binormal = cross(output.normal, output.tangent);
	
	return output;
}

Texture2D alphaMap : register(t10);
Texture2D secondMap : register(t11);
Texture2D thirdMap : register(t12);

float4 PS(LightPixelInput input) : SV_TARGET
{
	float4 albedo = diffuseMap.Sample(samp, input.uv);
	float4 alpha = alphaMap.Sample(samp, input.uv);
	float4 second = secondMap.Sample(samp, input.uv);
	float4 thrid = thirdMap.Sample(samp, input.uv);
	
	albedo = lerp(albedo, second, alpha.r);
	albedo = lerp(albedo, thrid, alpha.g);
	
	Material material = GetMaterial(input);
	material.diffuseColor = albedo;
	
	
	float4 color = CalcDirectional(material, lights[0]);
	float4 ambient = CalcAmbient(material);
	float4 emissive = CalcEmissive(material);
	
	return color + ambient + emissive;
}