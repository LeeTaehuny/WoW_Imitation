#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"

struct VertexInput
{
	float4 pos : POSITION;
	float2 size : SIZE;
	float3 velocity : VELOCITY;
};

struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

struct GeometryInput
{
	float3 pos : POSITION;
	float2 size : SIZE;
	matrix invView : INVVIEW;
	matrix view : VIEW;
	matrix projection : PROJECTION;
};

cbuffer SparkBuffer : register(b10)
{
	float time;
	float duration;
}

GeometryInput VS(VertexInput input)
{
	GeometryInput output;
	
	output.pos = input.pos.xyz + input.velocity * time;
	output.size = input.size;
	output.invView = invView;
	output.view = view;
	output.projection = projection;
	
	
	
	return output;
}

static const float2 TEXCOORD[4] =
{
	float2(0.0f, 1.0f),
	float2(0.0f, 0.0f),
	float2(1.0f, 1.0f),
	float2(1.0f, 0.0f)
};

[maxvertexcount(4)]
void GS(point GeometryInput input[1], inout TriangleStream<PixelInput> output)
{
	float3 up = input[0].invView._21_22_23;
	float3 forward = input[0].pos.xyz - input[0].invView._41_42_43;
	forward = normalize(forward);
	float3 right = normalize(cross(up, forward));
	
	float2 halfSize = input[0].size * 0.5f;
	
	float4 vertices[4];
	vertices[0] = float4(input[0].pos - right * halfSize.x - up * halfSize.y, 1.0f);
	vertices[1] = float4(input[0].pos - right * halfSize.x + up * halfSize.y, 1.0f);
	vertices[2] = float4(input[0].pos + right * halfSize.x - up * halfSize.y, 1.0f);
	vertices[3] = float4(input[0].pos + right * halfSize.x + up * halfSize.y, 1.0f);
	
	PixelInput pixelInput;
	
	[unroll(4)]
	for (int i = 0; i < 4; i++)
	{
		pixelInput.pos = mul(vertices[i], input[0].view);
		pixelInput.pos = mul(pixelInput.pos, input[0].projection);
		
		pixelInput.uv = TEXCOORD[i];

		output.Append(pixelInput);
	}
}

cbuffer StartColorBuffer : register(b11)
{
	float4 startColor;
}

cbuffer EndColorBuffer : register(b12)
{
	float4 endColor;
}

float4 PS(PixelInput input) : SV_TARGET
{		
	float4 color = lerp(startColor, endColor, time / duration);
	
	return diffuseMap.Sample(samp, input.uv) * color;
}