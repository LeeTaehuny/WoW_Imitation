#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"

LightPixelInput VS(VertexUVNormalTangent input)
{
	LightPixelInput output;
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

GBufferOutput PS(LightPixelInput input) : SV_TARGET
{
	float3 albedo = diffuseMap.Sample(samp, input.uv).rgb;
	float specularIntencity = specularMap.Sample(samp, input.uv).r;
	
	float3 normal = NormalMapping(input.tangent, input.binormal, input.normal, input.uv);
	
	return PackGBuffer(albedo, normal, specularIntencity);

}