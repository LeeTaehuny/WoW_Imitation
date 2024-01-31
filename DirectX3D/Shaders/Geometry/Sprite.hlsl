#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"

struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

struct GeometryInput
{
	float4 pos : SV_POSITION;
	float2 size : SIZE;
	matrix invView : INVVIEW;
	matrix view : VIEW;
	matrix projection : PROJECTION;
};

GeometryInput VS(VertexUV input)
{
	GeometryInput output;
	
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
	float3 up = input[0].invView._21_22_23;
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
	
	[unroll(4)]
	for (int i = 0; i < 4; i++)
	{
		pixelInput.pos = mul(vertices[i], input[0].view);
		pixelInput.pos = mul(pixelInput.pos, input[0].projection);
		
		pixelInput.uv = TEXCOORD[i];

		output.Append(pixelInput);
	}
}

cbuffer SpriteBuffer : register(b10)
{
	float2 maxFrame;
	float2 curFrame;
}

float4 PS(PixelInput input) : SV_TARGET
{
	float2 uv = (input.uv / maxFrame) + (curFrame / maxFrame);
	
	return diffuseMap.Sample(samp, uv);
}