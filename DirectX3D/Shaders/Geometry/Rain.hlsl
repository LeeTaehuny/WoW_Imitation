#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"

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

cbuffer RainBuffer : register(b10)
{
	float3 velocity;
	float drawDistance;
	
	float4 color;
	
	float3 origin;
	float time;
	
	float3 size;
}

GeometryInput VS(VertexUV input)
{
	GeometryInput output;
	
	float3 v = velocity;
	v.xz /= input.uv.y * 0.1f;
	output.velocity = v;
	
	float3 displace = time * v;
	input.pos.xyz = origin + (size + (input.pos.xyz + displace) % size) % size - (size * 0.5f);
	
	float alpha = cos(time + (input.pos.x + input.pos.z));
	alpha = saturate(1.5f + alpha / drawDistance * 2.0f);
	
	output.distance = drawDistance;
	output.color = color;
	output.color.a = alpha;
	
	output.pos = input.pos;
	output.size = input.uv;
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
		
		pixelInput.color.a = 0.2f * saturate(1 - pixelInput.pos.z / input[0].distance) * input[0].color.a;

		output.Append(pixelInput);
	}
}

float4 PS(PixelInput input) : SV_TARGET
{	
	return diffuseMap.Sample(samp, input.uv) * input.color;	
}