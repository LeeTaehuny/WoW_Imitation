#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"

struct VertexInput
{
	float4 pos : POSITION;
	float2 size : SIZE;
	float2 random : RANDOM;
};

struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
	float4 color : COLOR;
};

struct GeometryInput
{
	float4 pos : SV_POSITION;
	float2 size : SIZE;
	matrix invView : INVVIEW;
	matrix view : VIEW;
	matrix projection : PROJECTION;
	float distance : DISTANCE;
	float4 color : COLOR;
	float3 velocity : VELOCITY;
};

cbuffer SnowBuffer : register(b10)
{
	float3 velocity;
	float drawDistance;
	
	float4 color;
	
	float3 origin;
	float time;
	
	float3 size;
	float turbulence;
}

GeometryInput VS(VertexInput input)
{
	GeometryInput output;
	
	float3 displace = time * velocity;
	
	input.pos.x += cos(time - input.random.x) * turbulence;
	input.pos.z += cos(time - input.random.y) * turbulence;
	
	input.pos.xyz = origin + (size + (input.pos.xyz + displace) % size) % size - (size * 0.5f);
	
	output.velocity = velocity;
	output.distance = drawDistance;	
	output.color = color;	
	output.pos = input.pos;
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
	float3 up = normalize(-input[0].velocity);
	float3 forward = input[0].pos.xyz - input[0].invView._41_42_43;
	forward = normalize(forward);
	float3 right = normalize(cross(up, forward));
	
	float2 halfSize = input[0].size * 0.5f;
	
	float4 vertices[4];
	vertices[0] = float4(input[0].pos.xyz - right * halfSize.x - up * halfSize.y, 1.0f);
	vertices[1] = float4(input[0].pos.xyz - right * halfSize.x + up * halfSize.y, 1.0f);
	vertices[2] = float4(input[0].pos.xyz + right * halfSize.x - up * halfSize.y, 1.0f);
	vertices[3] = float4(input[0].pos.xyz + right * halfSize.x + up * halfSize.y, 1.0f);
	
	PixelInput pixelInput;
	pixelInput.color = input[0].color;
	
	[unroll(4)]
	for (int i = 0; i < 4; i++)
	{
		pixelInput.pos = mul(vertices[i], input[0].view);
		pixelInput.pos = mul(pixelInput.pos, input[0].projection);
		
		pixelInput.uv = TEXCOORD[i];
		
		pixelInput.color.a = saturate(1 - pixelInput.pos.z / input[0].distance) * 0.5f;

		output.Append(pixelInput);
	}
}

float4 PS(PixelInput input) : SV_TARGET
{
	return diffuseMap.Sample(samp, input.uv) * input.color;	
}