#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"

struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
	float3 viewPos : POSITION0;
	float3 worldPos : POSITION1;
	float4 alpha : ALPHA;
};


PixelInput VS(VertexUVNormalTangentAlpha input)
{
	PixelInput output;
	output.pos = mul(input.pos, world);
	
	output.viewPos = invView._41_42_43;
	output.worldPos = output.pos;
	
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);

	output.uv = input.uv;
	
	output.normal = mul(input.normal, (float3x3) world);
	output.tangent = mul(input.tangent, (float3x3) world);
	output.binormal = cross(output.normal, output.tangent);
	
	output.alpha = input.alpha;
	
	return output;
}

cbuffer BrushBuffer : register(b10)
{
	int type;
	float3 pickingPos;
	
	float range;
	float3 color;
}

float4 BrushColor(float3 pos)
{
	if (type == 0 || type == 1)
	{
		float2 direction = pos.xz - pickingPos.xz;
		
		float distance = length(direction);

		if (distance <= range)
			return float4(color, 0);
	}
	else if (type == 2)
	{
		float size = range * 0.5f;
		
		if (abs(pos.x - pickingPos.x) < size
			&& abs(pos.z - pickingPos.z) < size)
		{
			return float4(color, 0);
		}
	}
	
	return float4(0, 0, 0, 0);
}

Texture2D secondDiffuseMap : register(t11);
Texture2D thirdDiffuseMap : register(t12);

float4 PS(PixelInput input) : SV_TARGET
{
	float4 albedo = diffuseMap.Sample(samp, input.uv);
	
	float4 second = secondDiffuseMap.Sample(samp, input.uv);
	float4 thrid = thirdDiffuseMap.Sample(samp, input.uv);
	
	albedo = lerp(albedo, second, input.alpha.r);
	albedo = lerp(albedo, thrid, input.alpha.g);
	
	Material material;
	material.normal = NormalMapping(input.tangent,
		input.binormal, input.normal, input.uv);		
	material.diffuseColor = albedo;
	material.specularIntensity = specularMap.Sample(samp, input.uv);
	material.viewPos = input.viewPos;
	material.worldPos = input.worldPos;
	
	float4 color = CalcDirectional(material, lights[0]);
	float4 ambient = CalcAmbient(material);
	float4 emissive = CalcEmissive(material);
	float4 brush = BrushColor(input.worldPos);
	
	return color + ambient + emissive + brush;
}