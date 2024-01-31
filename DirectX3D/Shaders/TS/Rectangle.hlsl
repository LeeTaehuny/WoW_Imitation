#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"

Vertex VS(Vertex input)
{
	return input;
}

struct CHullOutput
{
	float edgeTessFactor[4] : SV_TessFactor;
	float insideTessFactor[2] : SV_InsideTessFactor;
};

#define NUM_CONTROL_POINTS 4

cbuffer EdgeInfo : register(b10)
{
	float4 edges;	
}

cbuffer InsideInfo : register(b11)
{	
	float2 inside;
}

CHullOutput CHS(InputPatch<Vertex, NUM_CONTROL_POINTS> input)
{
	CHullOutput output;

	output.edgeTessFactor[0] = edges.x;
	output.edgeTessFactor[1] = edges.y;
	output.edgeTessFactor[2] = edges.z;
	output.edgeTessFactor[3] = edges.w;
	output.insideTessFactor[0] = inside.x;
	output.insideTessFactor[1] = inside.y;

	return output;
}

struct HullOutput
{
	float4 pos : POSITION;
};

[domain("quad")]
[partitioning("integer")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(4)]
[patchconstantfunc("CHS")]
HullOutput HS(InputPatch<Vertex, NUM_CONTROL_POINTS> input, uint i : SV_OutputControlPointID)
{
	HullOutput output;

	output.pos = input[i].pos;

	return output;
}

struct PixelInput
{
	float4 pos : SV_POSITION;
};

[domain("quad")]
PixelInput DS(CHullOutput input, float2 uv : SV_DomainLocation,
	const OutputPatch<HullOutput, NUM_CONTROL_POINTS> patch)
{
	PixelInput output;

	float4 v1 = lerp(patch[0].pos, patch[2].pos, uv.x);
	float4 v2 = lerp(patch[1].pos, patch[3].pos, uv.x);
	
	float4 pos = lerp(v1, v2, 1 - uv.y);
	output.pos = float4(pos.xyz, 1.0f);

	return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
	return float4(1, 1, 0, 1);
}